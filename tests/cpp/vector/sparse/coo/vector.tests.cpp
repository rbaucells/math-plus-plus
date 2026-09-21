#include "../../../telemetry.tests.h"
#include "gtest/gtest.h"

#include <array>
#include <complex>
#include <cstddef>
#include <utility>
#include <span>
#include <tuple>

#include "mathpp/implementation/common/compare.h"
#include "mathpp/implementation/vector/common/asserts.h"
#include "mathpp/implementation/vector/sparse/common/operators/compare.h"
#include "mathpp/implementation/vector/sparse/coo/vector.h"
#include "simple_coo_sparse_vector_like.h"

#pragma region default_constructor
TEST(coo_sparse_vector_default_constructor, given_coo_sparse_vector_should_default_construct) {
    // act
    TelemetryTests::start();
    const CooSparseVector<float> a;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(compare(a.nnz(), 0));
    ASSERT_TRUE(a.rawValues() == nullptr);
    ASSERT_TRUE(a.rawIndices() == nullptr);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region sized_constructor
TEST(coo_sparse_vector_sized_constructor, given_n_should_construct) {
    // act
    TelemetryTests::start();
    const CooSparseVector<int> a(4);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 4));
    ASSERT_TRUE(compare(a.nnz(), 0));
    ASSERT_TRUE(a.rawValues() != nullptr);
    ASSERT_TRUE(a.rawIndices() != nullptr);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region initializer_list_constructor
TEST(coo_sparse_vector_initializer_list_constructor, given_n_and_initializer_list_should_construct) {
    // arrange
    CooSparseVector<float> expected(7);
    expected.set(1, 2);
    expected.set(3, 4);
    expected.set(5, 6);
    // act
    TelemetryTests::start();
    const CooSparseVector<float> a(7, {{2, 1}, {4, 3}, {6, 5}});
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1});
}
#pragma endregion
#pragma region range_constructor
TEST(coo_sparse_vector_range_constructor, given_n_and_range_should_construct) {
    // arrange
    const std::array<std::tuple<double, std::size_t>, 3> range = {{{1.5, 0}, {3.5, 2}, {5.5, 4}}};
    CooSparseVector<double> expected(6);
    expected.set(0, 1.5);
    expected.set(2, 3.5);
    expected.set(4, 5.5);
    // act
    TelemetryTests::start();
    const CooSparseVector<double> a(6, range);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), a, expected));
    TelemetryTests::asserts({.allocations = 1});
}
#pragma endregion
#pragma region copy_constructor_from_same_type
TEST(coo_sparse_vector_copy_constructor_from_same_type, given_coo_sparse_vector_should_copy) {
    // arrange
    const CooSparseVector<float> expected(6, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const CooSparseVector<float> b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region copy_constructor_from_diff_type
TEST(coo_sparse_vector_copy_constructor_from_diff_type, given_coo_sparse_vector_should_copy) {
    // arrange
    const CooSparseVector<int> expected(6, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const CooSparseVector<std::complex<double>> b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), b, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region copy_constructor_from_like
TEST(coo_sparse_vector_copy_constructor_from_like, given_coo_sparse_vector_like_should_copy) {
    // arrange
    const SimpleCooSparseVectorLike<float> expected(6, {{2, 1}, {4, 3}});
    CooSparseVector<float> expectedVector(6);
    expectedVector.set(1, 2);
    expectedVector.set(3, 4);
    // act
    TelemetryTests::start();
    const CooSparseVector<float> b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expectedVector));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region move_constructor
TEST(coo_sparse_vector_move_constructor, given_coo_sparse_vector_should_move) {
    // arrange
    CooSparseVector<long double> a(6, {{2, 1}, {4, 3}});
    const CooSparseVector<long double> expected(6, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const CooSparseVector<long double> b = std::move(a);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(compare(a.nnz(), 0));
    ASSERT_TRUE(a.rawValues() == nullptr);
    ASSERT_TRUE(a.rawIndices() == nullptr);
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.move_constructs = 1});
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type
TEST(coo_sparse_vector_copy_assignment_operator_from_same_type, given_coo_sparse_vector_of_same_nnz_should_copy_assign) {
    // arrange
    const CooSparseVector<float> expected(6, {{2, 1}, {4, 3}});
    CooSparseVector<float> b(4, {{8, 0}, {9, 2}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1});
}

TEST(coo_sparse_vector_copy_assignment_operator_from_same_type, given_coo_sparse_vector_of_diff_nnz_should_copy_assign) {
    // arrange
    const CooSparseVector<float> expected(6, {{2, 1}, {4, 3}, {6, 5}});
    CooSparseVector<float> b(4, {{8, 0}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 2, .deallocations = 2});
}

TEST(coo_sparse_vector_copy_assignment_operator_from_same_type, given_self_should_do_nothing) {
    // arrange
    CooSparseVector<float> b(6, {{2, 1}, {4, 3}});
    // act
    const float* valuesBefore = b.rawValues();
    const std::size_t* indicesBefore = b.rawIndices();
    TelemetryTests::start();
    b = b;
    TelemetryTests::end();
    const float* valuesAfter = b.rawValues();
    const std::size_t* indicesAfter = b.rawIndices();
    // assert
    ASSERT_TRUE(valuesBefore == valuesAfter);
    ASSERT_TRUE(indicesBefore == indicesAfter);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region copy_assignment_operator_from_diff_type
TEST(coo_sparse_vector_copy_assignment_operator_from_diff_type, given_coo_sparse_vector_of_same_nnz_should_copy_assign) {
    // arrange
    const CooSparseVector<int> expected(6, {{2, 1}, {4, 3}});
    CooSparseVector<std::complex<float>> b(4, {{8, 0}, {9, 2}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1});
}

TEST(coo_sparse_vector_copy_assignment_operator_from_diff_type, given_coo_sparse_vector_of_diff_nnz_should_copy_assign) {
    // arrange
    const CooSparseVector<int> expected(6, {{2, 1}, {4, 3}, {6, 5}});
    CooSparseVector<std::complex<float>> b(4, {{8, 0}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 2, .deallocations = 2});
}
#pragma endregion
#pragma region copy_assignment_operator_from_like
TEST(coo_sparse_vector_copy_assignment_operator_from_like, given_coo_sparse_vector_like_of_same_nnz_should_copy_assign) {
    // arrange
    const SimpleCooSparseVectorLike<float> expected(6, {{2, 1}, {4, 3}});
    const CooSparseVector<float> expectedVector(6, {{2, 1}, {4, 3}});
    CooSparseVector<float> b(4, {{8, 0}, {9, 2}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expectedVector));
    TelemetryTests::asserts({.copy_assigns = 1});
}

TEST(coo_sparse_vector_copy_assignment_operator_from_like, given_coo_sparse_vector_like_of_diff_nnz_should_copy_assign) {
    // arrange
    const SimpleCooSparseVectorLike<float> expected(6, {{2, 1}, {4, 3}, {6, 5}});
    const CooSparseVector<float> expectedVector(6, {{2, 1}, {4, 3}, {6, 5}});
    CooSparseVector<float> b(4, {{8, 0}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expectedVector));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 2, .deallocations = 2});
}
#pragma endregion
#pragma region move_assignment_operator
TEST(coo_sparse_vector_move_assignment_operator, given_coo_sparse_vector_should_move_assign) {
    // arrange
    CooSparseVector<float> a(6, {{2, 1}, {4, 3}});
    const CooSparseVector<float> expected(6, {{2, 1}, {4, 3}});
    CooSparseVector<float> b(4, {{8, 0}});
    // act
    TelemetryTests::start();
    b = std::move(a);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(compare(a.nnz(), 0));
    ASSERT_TRUE(a.rawValues() == nullptr);
    ASSERT_TRUE(a.rawIndices() == nullptr);
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.move_assigns = 1, .deallocations = 2});
}

TEST(coo_sparse_vector_move_assignment_operator, given_self_should_do_nothing) {
    // arrange
    CooSparseVector<float> b(6, {{2, 1}, {4, 3}});
    // act
    const float* valuesBefore = b.rawValues();
    const std::size_t* indicesBefore = b.rawIndices();
    TelemetryTests::start();
    b = std::move(b);
    TelemetryTests::end();
    const float* valuesAfter = b.rawValues();
    const std::size_t* indicesAfter = b.rawIndices();
    // assert
    ASSERT_TRUE(valuesBefore == valuesAfter);
    ASSERT_TRUE(indicesBefore == indicesAfter);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region get
TEST(coo_sparse_vector_get, given_index_to_nonzero_should_return_value) {
    // arrange
    CooSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const float val = a.get(3);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), val, 4));
    TelemetryTests::asserts({});
}

TEST(coo_sparse_vector_get, given_index_to_zero_should_return_zero) {
    // arrange
    const CooSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const float val = a.get(2);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), val, 0));
    TelemetryTests::asserts({});
}

TEST(coo_sparse_vector_get, given_invalid_index_should_throw) {
    // arrange
    const CooSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act / assert
    TelemetryTests::start();
    ASSERT_THROW([[maybe_unused]] const float val = a.get(5), InvalidIndexException);
    TelemetryTests::end();
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region set
TEST(coo_sparse_vector_set, given_index_to_zero_should_set_value) {
    // arrange
    CooSparseVector<float> a(5, {{1, 0}, {2, 2}, {4, 3}});
    // act
    TelemetryTests::start();
    a.set(3, 67);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.get(3), 67));
    std::size_t* aIndices = a.rawIndices();
    float* aValues = a.rawValues();
    ASSERT_TRUE(compare(aIndices[0], 0));
    ASSERT_TRUE(compare(aIndices[1], 2));
    ASSERT_TRUE(compare(aIndices[2], 3));
    ASSERT_TRUE(compare(aValues[0], 1));
    ASSERT_TRUE(compare(aValues[1], 2));
    ASSERT_TRUE(compare(aValues[2], 67));
    TelemetryTests::asserts({});
}

TEST(coo_sparse_vector_set, given_index_to_nonzero_should_insert_value) {
    // arrange
    CooSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    a.set(2, 67);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.nnz(), 3));
    ASSERT_TRUE(compare(a.get(2), 67));
    std::size_t* aIndices = a.rawIndices();
    float* aValues = a.rawValues();
    ASSERT_TRUE(compare(aIndices[0], 1));
    ASSERT_TRUE(compare(aIndices[1], 2));
    ASSERT_TRUE(compare(aIndices[2], 3));
    ASSERT_TRUE(compare(aValues[0], 2));
    ASSERT_TRUE(compare(aValues[1], 67));
    ASSERT_TRUE(compare(aValues[2], 4));
    TelemetryTests::asserts({.allocations = 2, .deallocations = 2});
}

TEST(coo_sparse_vector_set, given_index_to_nonzero_and_zero_value_should_remove_value) {
    // arrange
    CooSparseVector<float> a(5, {{1, 0}, {2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    a.set(1, 0);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.nnz(), 2));
    ASSERT_TRUE(compare(a.get(1), 0));
    std::size_t* aIndices = a.rawIndices();
    float* aValues = a.rawValues();
    ASSERT_TRUE(compare(aIndices[0], 0));
    ASSERT_TRUE(compare(aIndices[1], 3));
    ASSERT_TRUE(compare(aValues[0], 1));
    ASSERT_TRUE(compare(aValues[1], 4));
    TelemetryTests::asserts({.allocations = 2, .deallocations = 2});
}

TEST(coo_sparse_vector_set, given_index_to_zero_and_zero_value_should_do_nothing) {
    // arrange
    CooSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    a.set(2, 0);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.nnz(), 2));
    std::size_t* aIndices = a.rawIndices();
    float* aValues = a.rawValues();
    ASSERT_TRUE(compare(aIndices[0], 1));
    ASSERT_TRUE(compare(aIndices[1], 3));
    ASSERT_TRUE(compare(aValues[0], 2));
    ASSERT_TRUE(compare(aValues[1], 4));
    TelemetryTests::asserts({});
}

TEST(coo_sparse_vector_set, given_invalid_index_should_throw) {
    // arrange
    CooSparseVector<float> a(5);
    // act / assert
    TelemetryTests::start();
    ASSERT_THROW(a.set(5, 67), InvalidIndexException);
    TelemetryTests::end();
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region nnz
TEST(coo_sparse_vector_nnz, given_coo_sparse_vector_should_return_nnz) {
    // arrange
    const CooSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const std::size_t nnz = a.nnz();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(nnz, 2));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region n
TEST(coo_sparse_vector_n, given_coo_sparse_vector_should_return_n) {
    // arrange
    const CooSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const std::size_t n = a.n();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(n, 5));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region raw_values
TEST(coo_sparse_vector_raw_values, given_coo_sparse_vector_should_return_raw_values) {
    // arrange
    CooSparseVector<int> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    int* values = a.rawValues();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(values != nullptr);
    ASSERT_TRUE(compare(values[0], 2));
    values[0] = 67;
    ASSERT_TRUE(compare(a.get(1), 67));
    TelemetryTests::asserts({});
}

TEST(coo_sparse_vector_raw_values, given_const_coo_sparse_vector_should_return_const_raw_values) {
    // arrange
    const CooSparseVector<int> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const int* values = a.rawValues();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(values != nullptr);
    ASSERT_TRUE(compare(values[1], 4));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region raw_indices
TEST(coo_sparse_vector_raw_indices, given_coo_sparse_vector_should_return_raw_indices) {
    // arrange
    CooSparseVector<int> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    std::size_t* indices = a.rawIndices();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(indices != nullptr);
    ASSERT_TRUE(compare(indices[0], 1));
    indices[0] = 0;
    ASSERT_TRUE(compare(a.get(0), 2));
    TelemetryTests::asserts({});
}

TEST(coo_sparse_vector_raw_indices, given_const_coo_sparse_vector_should_return_const_raw_indices) {
    // arrange
    const CooSparseVector<int> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const std::size_t* indices = a.rawIndices();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(indices != nullptr);
    ASSERT_TRUE(compare(indices[1], 3));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region values
TEST(coo_sparse_vector_values, given_coo_sparse_vector_should_return_values) {
    // arrange
    CooSparseVector<int> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const std::span<int> values = a.values();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(values[0], 2));
    ASSERT_TRUE(compare(values[1], 4));
    values[1] = 67;
    ASSERT_TRUE(compare(a.get(3), 67));
    TelemetryTests::asserts({});
}

TEST(coo_sparse_vector_values, given_const_coo_sparse_vector_should_return_const_values) {
    // arrange
    const CooSparseVector<int> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const std::span<const int> values = a.values();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(values[0], 2));
    ASSERT_TRUE(compare(values[1], 4));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region indices
TEST(coo_sparse_vector_indices, given_coo_sparse_vector_should_return_indices) {
    // arrange
    CooSparseVector<int> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const std::span<std::size_t> indices = a.indices();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(indices[0], 1));
    ASSERT_TRUE(compare(indices[1], 3));
    indices[1] = 67;
    ASSERT_TRUE(compare(a.rawIndices()[1], 67));
    TelemetryTests::asserts({});
}

TEST(coo_sparse_vector_indices, given_const_coo_sparse_vector_should_return_const_indices) {
    // arrange
    const CooSparseVector<int> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const std::span<const std::size_t> indices = a.indices();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(indices[0], 1));
    ASSERT_TRUE(compare(indices[1], 3));
    TelemetryTests::asserts({});
}
#pragma endregion
