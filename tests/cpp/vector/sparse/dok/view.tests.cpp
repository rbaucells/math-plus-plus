#include "../../../telemetry.tests.h"
#include "gtest/gtest.h"

#include <complex>
#include <cstddef>

#include "mathpp/implementation/common/compare.h"
#include "mathpp/implementation/vector/common/asserts.h"
#include "mathpp/implementation/vector/sparse/common/operators/compare.h"
#include "mathpp/implementation/vector/sparse/dok/vector.h"
#include "mathpp/implementation/vector/sparse/dok/view.h"

#pragma region owner_constructor
TEST(dok_sparse_vector_view_owner_constructor, given_dok_sparse_vector_and_n_and_offset_should_construct) {
    // arrange
    const DokSparseVector<double> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const DokSparseVector<double> expected(3, {{2, 1}});
    // act
    TelemetryTests::start();
    const DokSparseVectorView<double> view(a, 3, 1);
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
TEST(dok_sparse_vector_view_get, given_index_to_nonzero_should_return_value) {
    // arrange
    DokSparseVector<long> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const DokSparseVectorView<long> view(a, 3, 1);
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

TEST(dok_sparse_vector_view_get, given_index_to_zero_should_return_zero) {
    // arrange
    const DokSparseVector<long> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const DokSparseVectorView<long> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const long val = view.get(0);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(val, 0));
    TelemetryTests::asserts({});
}

TEST(dok_sparse_vector_view_get, given_invalid_index_should_throw_1) {
    // arrange
    const DokSparseVector<long> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const DokSparseVectorView<long> view(a, 3, 1);
    // act / assert
    TelemetryTests::start();
    ASSERT_THROW([[maybe_unused]] const long val = view.get(3), InvalidIndexException);
    TelemetryTests::end();
    TelemetryTests::asserts({});
}

TEST(dok_sparse_vector_view_get, given_invalid_owner_index_should_throw_2) {
    // arrange
    const DokSparseVector<long> a(4, {{1, 0}, {2, 2}});
    const DokSparseVectorView<long> view(a, 3, 2);
    // act / assert
    TelemetryTests::start();
    ASSERT_THROW([[maybe_unused]] const long val = view.get(2), InvalidIndexException);
    TelemetryTests::end();
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region nnz
TEST(dok_sparse_vector_view_nnz, given_dok_sparse_vector_view_should_return_nnz_view) {
    // arrange
    const DokSparseVector<long> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const DokSparseVectorView<long> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const std::size_t nnz = view.nnz();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(nnz, 1));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region n
TEST(dok_sparse_vector_view_n, given_dok_sparse_vector_view_should_return_n) {
    // arrange
    const DokSparseVector<float> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const DokSparseVectorView<float> view(a, 3, 1);
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
TEST(dok_sparse_vector_view_offset, given_dok_sparse_vector_view_should_return_offset) {
    // arrange
    const DokSparseVector<float> a(7, {{1, 0}, {2, 2}, {3, 5}});
    const DokSparseVectorView<float> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const std::size_t offset = view.offset();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(offset, 1));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region map
TEST(dok_sparse_vector_view_map, given_dok_sparse_vector_view_with_nonzero_offset_should_return_map_object) {
    // arrange
    const DokSparseVector<float> a(7, {{9, 1}, {7, 2}, {8, 3}, {12, 6}});
    const DokSparseVectorView<float> view(a, 4, 2);
    // act
    const auto map = view.map();
    // assert
    ASSERT_TRUE(compare(map.size(), 2));
    ASSERT_TRUE(map.contains(0));
    ASSERT_TRUE(map.contains(1));
    ASSERT_TRUE(!map.contains(2));
    ASSERT_TRUE(compare(Precision(0.001f), map.at(0), 7));
    ASSERT_TRUE(compare(Precision(0.001f), map.at(1), 8));

    const std::map<std::size_t, float> expected = {{0, 7.0f}, {1, 8.0f}};
    auto it = expected.begin();
    for (const auto [key, value] : map) {
        ASSERT_TRUE(compare(key, it->first));
        ASSERT_TRUE(compare(Precision(0.001f), value, it->second));
        ++it;
    }
}

TEST(dok_sparse_vector_view_map, given_dok_sparse_vector_view_with_zero_offset_should_return_map_object) {
    // arrange
    const DokSparseVector<float> a(7, {{9, 1}, {7, 2}, {8, 3}, {12, 6}});
    const DokSparseVectorView<float> view(a, 3, 0);
    // act
    const auto map = view.map();
    // assert
    ASSERT_TRUE(compare(map.size(), 2));
    ASSERT_TRUE(map.contains(1));
    ASSERT_TRUE(map.contains(2));
    ASSERT_TRUE(!map.contains(0));
    ASSERT_TRUE(!map.contains(3));
    ASSERT_TRUE(compare(Precision(0.001f), map.at(1), 9));
    ASSERT_TRUE(compare(Precision(0.001f), map.at(2), 7));

    const std::map<std::size_t, float> expected = {{1, 9.0f}, {2, 7.0f}};
    auto it = expected.begin();
    for (const auto [key, value] : map) {
        ASSERT_TRUE(compare(key, it->first));
        ASSERT_TRUE(compare(Precision(0.001f), value, it->second));
        ++it;
    }
}

TEST(dok_sparse_vector_view_map, given_dok_sparse_vector_view_with_full_size_and_zero_offset_should_return_map_object) {
    // arrange
    const DokSparseVector<float> a(7, {{9, 1}, {7, 2}, {8, 3}, {12, 6}});
    const DokSparseVectorView<float> view(a, 7, 0);
    // act
    const auto map = view.map();
    // assert
    ASSERT_TRUE(compare(map.size(), 4));
    ASSERT_TRUE(map.contains(1));
    ASSERT_TRUE(map.contains(2));
    ASSERT_TRUE(map.contains(3));
    ASSERT_TRUE(map.contains(6));
    ASSERT_TRUE(!map.contains(0));
    ASSERT_TRUE(compare(Precision(0.001f), map.at(1), 9));
    ASSERT_TRUE(compare(Precision(0.001f), map.at(2), 7));
    ASSERT_TRUE(compare(Precision(0.001f), map.at(3), 8));
    ASSERT_TRUE(compare(Precision(0.001f), map.at(6), 12));

    const std::map<std::size_t, float> expected = {{1, 9.0f}, {2, 7.0f}, {3, 8.0f}, {6, 12.0f}};
    auto it = expected.begin();
    for (const auto [key, value] : map) {
        ASSERT_TRUE(compare(key, it->first));
        ASSERT_TRUE(compare(Precision(0.001f), value, it->second));
        ++it;
    }
}
#pragma endregion
#pragma region owner
TEST(dok_sparse_vector_view_owner, given_dok_sparse_vector_should_return_owner) {
    // arrange
    const DokSparseVector<std::complex<int>> a(7, {{{1, 0}, 0}, {{2, 3}, 2}});
    const DokSparseVectorView<std::complex<int>> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const DokSparseVector<std::complex<int>>& owner = view.owner();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(&owner == &a);
    TelemetryTests::asserts({});
}
#pragma endregion
