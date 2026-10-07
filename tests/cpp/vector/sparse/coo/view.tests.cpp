#include "../../../telemetry.tests.h"
#include "gtest/gtest.h"

#include <complex>
#include <cstddef>

#include "mathpp/implementation/common/compare.h"
#include "mathpp/implementation/vector/common/asserts.h"
#include "mathpp/implementation/vector/sparse/common/operators/compare.h"
#include "mathpp/implementation/vector/sparse/coo/vector.h"
#include "mathpp/implementation/vector/sparse/coo/view.h"

#pragma region owner_constructor
TEST(coo_sparse_vector_view_owner_constructor, given_coo_sparse_vector_and_n_and_offset_should_construct) {
    // arrange
    const CooSparseVector<double> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const CooSparseVector<double> expected(3, {{2, 1}});
    // act
    TelemetryTests::start();
    const CooSparseVectorView<double> view(a, 3, 1);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(view.n(), 3));
    ASSERT_TRUE(compare(view.offset(), 1));
    ASSERT_TRUE(&view.owner() == &a);
    ASSERT_TRUE(compare(Precision(0.001), view, expected));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region get
TEST(coo_sparse_vector_view_get, given_index_to_nonzero_should_return_value) {
    // arrange
    CooSparseVector<long> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const CooSparseVectorView<long> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const long val = view.get(1);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(val, 2));
    a.set(2, 67);
    ASSERT_TRUE(compare(view.get(1), 67));
    TelemetryTests::asserts({});
}

TEST(coo_sparse_vector_view_get, given_index_to_zero_should_return_zero) {
    // arrange
    const CooSparseVector<long> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const CooSparseVectorView<long> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const long val = view.get(0);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(val, 0));
    TelemetryTests::asserts({});
}

TEST(coo_sparse_vector_view_get, given_invalid_index_should_throw_1) {
    // arrange
    const CooSparseVector<long> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const CooSparseVectorView<long> view(a, 3, 1);
    // act / assert
    TelemetryTests::start();
    ASSERT_THROW([[maybe_unused]] const long val = view.get(3), InvalidIndexException);
    TelemetryTests::end();
    TelemetryTests::asserts({});
}

TEST(coo_sparse_vector_view_get, given_invalid_owner_index_should_throw_2) {
    // arrange
    const CooSparseVector<long> a(4, {{1, 0}, {2, 2}});
    const CooSparseVectorView<long> view(a, 3, 2);
    // act / assert
    TelemetryTests::start();
    ASSERT_THROW([[maybe_unused]] const long val = view.get(2), InvalidIndexException);
    TelemetryTests::end();
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region nnz
TEST(coo_sparse_vector_view_nnz, given_coo_sparse_vector_view_should_return_nnz_view) {
    // arrange
    const CooSparseVector<long> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const CooSparseVectorView<long> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const std::size_t nnz = view.nnz();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(nnz, 1));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region indices
TEST(coo_sparse_vector_view_indices, given_coo_sparse_vector_view_should_return_indices_view) {
    // arrange
    const CooSparseVector<long> a(8, {{1, 0}, {2, 2}, {3, 4}, {4, 7}});
    const CooSparseVectorView<long> view(a, 4, 1);
    // act
    TelemetryTests::start();
    const auto indices = view.indices();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(indices[0], 1));
    ASSERT_TRUE(compare(indices[1], 3));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region values
TEST(coo_sparse_vector_view_values, given_coo_sparse_vector_view_should_return_values_view) {
    // arrange
    const CooSparseVector<long> a(8, {{1, 0}, {2, 2}, {3, 4}, {4, 7}});
    const CooSparseVectorView<long> view(a, 4, 1);
    // act
    TelemetryTests::start();
    const auto values = view.values();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(values[0], 2));
    ASSERT_TRUE(compare(values[1], 3));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region n
TEST(coo_sparse_vector_view_n, given_coo_sparse_vector_view_should_return_n) {
    // arrange
    const CooSparseVector<float> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const CooSparseVectorView<float> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const std::size_t n = view.n();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(n, 3));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region offset
TEST(coo_sparse_vector_view_offset, given_coo_sparse_vector_view_should_return_offset) {
    // arrange
    const CooSparseVector<float> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const CooSparseVectorView<float> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const std::size_t offset = view.offset();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(offset, 1));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region owner
TEST(coo_sparse_vector_view_owner, given_coo_sparse_vector_should_return_owner) {
    // arrange
    const CooSparseVector<std::complex<int>> a(7, {{{1, 0}, 0}, {{2, 3}, 2}});
    const CooSparseVectorView<std::complex<int>> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const CooSparseVector<std::complex<int>>& owner = view.owner();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(&owner == &a);
    TelemetryTests::asserts({});
}
#pragma endregion
