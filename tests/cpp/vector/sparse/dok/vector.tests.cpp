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
#include "mathpp/implementation/vector/sparse/dok/vector.h"
#include "simple_dok_sparse_vector_like.h"

#pragma region default_constructor
TEST(dok_sparse_vector_default_constructor, given_dok_sparse_vector_should_default_construct) {
    // act
    TelemetryTests::start();
    const DokSparseVector<float> a;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(compare(a.nnz(), 0));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region sized_constructor
TEST(dok_sparse_vector_sized_constructor, given_n_should_construct) {
    // act
    TelemetryTests::start();
    const DokSparseVector<int> a(4);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 4));
    ASSERT_TRUE(compare(a.nnz(), 0));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region initializer_list_constructor
TEST(dok_sparse_vector_initializer_list_constructor, given_n_and_initializer_list_should_construct) {
    // arrange
    DokSparseVector<float> expected(7);
    expected.set(1, 2);
    expected.set(3, 4);
    expected.set(5, 6);
    // act
    TelemetryTests::start();
    const DokSparseVector<float> a(7, {{2, 1}, {4, 3}, {6, 5}});
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1});
}
#pragma endregion
#pragma region range_constructor
TEST(dok_sparse_vector_range_constructor, given_n_and_range_should_construct) {
    // arrange
    const std::array<std::tuple<double, std::size_t>, 3> range = {{{1.5, 0}, {3.5, 2}, {5.5, 4}}};
    DokSparseVector<double> expected(6);
    expected.set(0, 1.5);
    expected.set(2, 3.5);
    expected.set(4, 5.5);
    // act
    TelemetryTests::start();
    const DokSparseVector<double> a(6, range);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), a, expected));
    TelemetryTests::asserts({.allocations = 1});
}
#pragma endregion
#pragma region copy_constructor_from_same_type
TEST(dok_sparse_vector_copy_constructor_from_same_type, given_dok_sparse_vector_should_copy) {
    // arrange
    const DokSparseVector<float> expected(6, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const DokSparseVector<float> b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region copy_constructor_from_diff_type
TEST(dok_sparse_vector_copy_constructor_from_diff_type, given_dok_sparse_vector_should_copy) {
    // arrange
    const DokSparseVector<int> expected(6, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const DokSparseVector<std::complex<double>> b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), b, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region copy_constructor_from_like
TEST(dok_sparse_vector_copy_constructor_from_like, given_dok_sparse_vector_like_should_copy) {
    // arrange
    const SimpleDokSparseVectorLike<float> expected(6, {{2, 1}, {4, 3}});
    DokSparseVector<float> expectedVector(6);
    expectedVector.set(1, 2);
    expectedVector.set(3, 4);
    // act
    TelemetryTests::start();
    const DokSparseVector<float> b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expectedVector));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region move_constructor
TEST(dok_sparse_vector_move_constructor, given_dok_sparse_vector_should_move) {
    // arrange
    DokSparseVector<long double> a(6, {{2, 1}, {4, 3}});
    const DokSparseVector<long double> expected(6, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const DokSparseVector<long double> b = std::move(a);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(compare(a.nnz(), 0));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.move_constructs = 1});
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type
TEST(dok_sparse_vector_copy_assignment_operator_from_same_type, given_dok_sparse_vector_of_same_nnz_should_copy_assign) {
    // arrange
    const DokSparseVector<float> expected(6, {{2, 1}, {4, 3}});
    DokSparseVector<float> b(4, {{8, 0}, {9, 2}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}

TEST(dok_sparse_vector_copy_assignment_operator_from_same_type, given_dok_sparse_vector_of_diff_nnz_should_copy_assign) {
    // arrange
    const DokSparseVector<float> expected(6, {{2, 1}, {4, 3}, {6, 5}});
    DokSparseVector<float> b(4, {{8, 0}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}

TEST(dok_sparse_vector_copy_assignment_operator_from_same_type, given_self_should_do_nothing) {
    // arrange
    DokSparseVector<float> b(6, {{2, 1}, {4, 3}});
    // act
    const auto beforeBegin = b.map().begin();
    const auto beforeEnd = b.map().end();
    TelemetryTests::start();
    b = b;
    TelemetryTests::end();
    const auto afterBegin = b.map().begin();
    const auto afterEnd = b.map().end();
    // assert
    ASSERT_TRUE(beforeBegin == afterBegin);
    ASSERT_TRUE(beforeEnd == afterEnd);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region copy_assignment_operator_from_diff_type
TEST(dok_sparse_vector_copy_assignment_operator_from_diff_type, given_dok_sparse_vector_of_same_nnz_should_copy_assign) {
    // arrange
    const DokSparseVector<short> expected(6, {{2, 1}, {4, 3}});
    DokSparseVector<std::complex<float>> b(4, {{8, 0}, {9, 2}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}

TEST(dok_sparse_vector_copy_assignment_operator_from_diff_type, given_dok_sparse_vector_of_diff_nnz_should_copy_assign) {
    // arrange
    const DokSparseVector<int> expected(6, {{2, 1}, {4, 3}, {6, 5}});
    DokSparseVector<std::complex<double>> b(4, {{8, 0}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}
#pragma endregion
#pragma region copy_assignment_operator_from_like
TEST(dok_sparse_vector_copy_assignment_operator_from_like, given_dok_sparse_vector_like_of_same_nnz_should_copy_assign) {
    // arrange
    const SimpleDokSparseVectorLike<float> expected(6, {{2, 1}, {4, 3}});
    const DokSparseVector<float> expectedVector(6, {{2, 1}, {4, 3}});
    DokSparseVector<float> b(4, {{8, 0}, {9, 2}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expectedVector));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}

TEST(dok_sparse_vector_copy_assignment_operator_from_like, given_dok_sparse_vector_like_of_diff_nnz_should_copy_assign) {
    // arrange
    const SimpleDokSparseVectorLike<float> expected(6, {{2, 1}, {4, 3}, {6, 5}});
    const DokSparseVector<float> expectedVector(6, {{2, 1}, {4, 3}, {6, 5}});
    DokSparseVector<float> b(4, {{8, 0}});
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expectedVector));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}
#pragma endregion
#pragma region move_assignment_operator
TEST(dok_sparse_vector_move_assignment_operator, given_dok_sparse_vector_should_move_assign) {
    // arrange
    DokSparseVector<float> a(6, {{2, 1}, {4, 3}});
    const DokSparseVector<float> expected(6, {{2, 1}, {4, 3}});
    DokSparseVector<float> b(4, {{8, 0}});
    // act
    TelemetryTests::start();
    b = std::move(a);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(compare(a.nnz(), 0));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.move_assigns = 1, .deallocations = 1});
}

TEST(dok_sparse_vector_move_assignment_operator, given_self_should_do_nothing) {
    // arrange
    DokSparseVector<float> b(6, {{2, 1}, {4, 3}});
    // act
    const auto beforeBegin = b.map().begin();
    const auto beforeEnd = b.map().end();
    TelemetryTests::start();
    b = std::move(b);
    TelemetryTests::end();
    const auto afterBegin = b.map().begin();
    const auto afterEnd = b.map().end();
    // assert
    ASSERT_TRUE(beforeBegin == afterBegin);
    ASSERT_TRUE(beforeEnd == afterEnd);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region get
TEST(dok_sparse_vector_get, given_index_to_nonzero_should_return_value) {
    // arrange
    DokSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const float val = a.get(3);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), val, 4));
    TelemetryTests::asserts({});
}

TEST(dok_sparse_vector_get, given_index_to_zero_should_return_zero) {
    // arrange
    const DokSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const float val = a.get(2);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), val, 0));
    TelemetryTests::asserts({});
}

TEST(dok_sparse_vector_get, given_invalid_index_should_throw) {
    // arrange
    const DokSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act / assert
    TelemetryTests::start();
    ASSERT_THROW([[maybe_unused]] const float val = a.get(5), InvalidIndexException);
    TelemetryTests::end();
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region set
TEST(dok_sparse_vector_set, given_index_to_zero_should_set_value) {
    // arrange
    DokSparseVector<float> a(5, {{1, 0}, {2, 2}, {4, 3}});
    // act
    TelemetryTests::start();
    a.set(3, 67);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.get(3), 67));
    const auto& map = a.map();
    ASSERT_TRUE(compare(map.at(0), 1));
    ASSERT_TRUE(compare(map.at(2), 2));
    ASSERT_TRUE(compare(map.at(3), 67));
    TelemetryTests::asserts({.allocations = 1});
}

TEST(dok_sparse_vector_set, given_index_to_nonzero_should_insert_value) {
    // arrange
    DokSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    a.set(2, 67);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.nnz(), 3));
    ASSERT_TRUE(compare(a.get(2), 67));
    const auto& map = a.map();
    ASSERT_TRUE(compare(map.at(1), 2));
    ASSERT_TRUE(compare(map.at(2), 67));
    ASSERT_TRUE(compare(map.at(3), 4));
    TelemetryTests::asserts({.allocations = 1});
}

TEST(dok_sparse_vector_set, given_index_to_nonzero_and_zero_value_should_remove_value) {
    // arrange
    DokSparseVector<float> a(5, {{1, 0}, {2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    a.set(1, 0);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.nnz(), 2));
    ASSERT_TRUE(compare(a.get(1), 0));
    const auto& map = a.map();
    ASSERT_TRUE(compare(map.at(0), 1));
    ASSERT_TRUE(compare(map.at(3), 4));
    TelemetryTests::asserts({.deallocations = 1});
}

TEST(dok_sparse_vector_set, given_index_to_zero_and_zero_value_should_do_nothing) {
    // arrange
    DokSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    a.set(2, 0);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.nnz(), 2));
    const auto& map = a.map();
    ASSERT_TRUE(compare(map.at(1), 2));
    ASSERT_TRUE(compare(map.at(3), 4));
    TelemetryTests::asserts({});
}

TEST(dok_sparse_vector_set, given_invalid_index_should_throw) {
    // arrange
    DokSparseVector<float> a(5);
    // act / assert
    TelemetryTests::start();
    ASSERT_THROW(a.set(5, 67), InvalidIndexException);
    TelemetryTests::end();
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region nnz
TEST(dok_sparse_vector_nnz, given_dok_sparse_vector_should_return_nnz) {
    // arrange
    const DokSparseVector<float> a(5, {{2, 1}, {4, 3}});
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
TEST(dok_sparse_vector_n, given_dok_sparse_vector_should_return_n) {
    // arrange
    const DokSparseVector<float> a(5, {{2, 1}, {4, 3}});
    // act
    TelemetryTests::start();
    const std::size_t n = a.n();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(n, 5));
    TelemetryTests::asserts({});
}
#pragma endregion
