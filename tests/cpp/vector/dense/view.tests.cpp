#include "../../telemetry.tests.h"
#include "gtest/gtest.h"

#include "mathpp/implementation/common/compare.h"
#include "mathpp/implementation/vector/dense/view.h"
#include "mathpp/implementation/vector/dense/operators/compare.h"

#pragma region owner_constructor
TEST(dense_vector_view_owner_constructor, given_dense_vector_and_n_and_offset_should_construct) {
    // arrange
    const DenseVector<double> a = {1, 2, 3, 4, 5};
    const DenseVector<double> expected = {2, 3, 4};
    // act
    TelemetryTests::start();
    const DenseVectorView<double> view(a, 3, 1);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(view.n(), 3));
    ASSERT_TRUE(compare(view.offset(), 1));
    ASSERT_TRUE(&view.owner() == &a);
    ASSERT_TRUE(compare(Precision(0.001), view, expected));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region indexing_operator
TEST(dense_vector_view_indexing_operator, given_valid_index_should_return_const_ref) {
    // arrange
    DenseVector<long> a = {1, 2, 3, 4, 5};
    const DenseVectorView<long> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const long& ref = view[1];
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(ref, 3));
    a[2] = 67;
    ASSERT_TRUE(compare(ref, 67));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region get
TEST(dense_vector_view_get, given_valid_index_should_return_value) {
    // arrange
    DenseVector<long> a = {1, 2, 3, 4, 5};
    const DenseVectorView<long> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const long val = view.get(1);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(val, 3));
    a[2] = 67;
    ASSERT_TRUE(compare(view.get(1), 67));
    TelemetryTests::asserts({});
}

TEST(dense_vector_view_get, given_invalid_index_should_throw_1) {
    // arrange
    DenseVector<long> a = {1, 2, 3, 4, 5};
    const DenseVectorView<long> view(a, 3, 1);
    // act / assert
    ASSERT_THROW(view.get(3), InvalidIndexException);
}

TEST(dense_vector_view_get, given_invalid_index_should_throw_2) {
    // arrange
    DenseVector<long> a = {1, 2, 3, 4, 5};
    const DenseVectorView<long> view(a, 3, 1);
    // act / assert
    ASSERT_THROW(view.get(4), InvalidIndexException);
}
#pragma endregion
#pragma region set
TEST(dense_vector_view_set, given_valid_index_should_throw) {
    // arrange
    DenseVector<long> a = {1, 2, 3, 4, 5};
    DenseVectorView<long> view(a, 3, 1);
    // act / assert
    ASSERT_THROW(view.set(0, 5), InvalidOperationException);
}

TEST(dense_vector_view_set, given_invalid_index_should_throw) {
    // arrange
    DenseVector<long> a = {1, 2, 3, 4, 5};
    DenseVectorView<long> view(a, 3, 1);
    // act / assert
    ASSERT_THROW(view.set(3, 5), InvalidOperationException);
}
#pragma endregion
#pragma region offset
TEST(dense_vector_view_offset, given_dense_vector_view_should_return_offset) {
    // arrange
    DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const std::size_t offset = view.offset();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(offset, 1));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region n
TEST(dense_vector_view_n, given_dense_vector_view_should_return_n) {
    // arrange
    DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> view(a, 3, 1);
    // act
    TelemetryTests::start();
    const std::size_t n = view.n();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(n, 3));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region owner
TEST(dense_vector_view_owner, given_dense_vector_should_return_owner) {
    // arrange
    const DenseVector<std::complex<int>> a = {{1, 0}, {2, 3}, {4, 67}, {3, 6}, {3, 1}};
    const DenseVectorView<std::complex<int>> view(a, 3, 1);
    // act
    const DenseVector<std::complex<int>>& owner = view.owner();
    // assert
    ASSERT_TRUE(&owner == &a);
}
#pragma endregion
