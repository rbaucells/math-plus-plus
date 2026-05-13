#include "gtest/gtest.h"

#include "mathpp/vector/dense/core.h"
#include "mathpp/vector/dense/operators.h"

#pragma region constructor
TEST(dense_vector_view_constructor, given_f_dense_vector_should_construct) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVector<float> expected = {2, 3, 4};
    // act
    const DenseVectorView<float> view = DenseVectorView<float>(a, 3, 1);
    // assert
    ASSERT_TRUE((compare(view.n(), 3)));
    ASSERT_TRUE((compare(view.offset(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), view, expected)));
}

TEST(dense_vector_view_constructor, given_cf_dense_vector_should_construct) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    const DenseVector<std::complex<float>> expected = {{3, 4}, {5, 6}, {7, 8}};
    // act
    const DenseVectorView<std::complex<float>> view = DenseVectorView<std::complex<float>>(a, 3, 1);
    // assert
    ASSERT_TRUE((compare(view.n(), 3)));
    ASSERT_TRUE((compare(view.offset(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), view, expected)));
}
#pragma endregion
#pragma region copy_constructor
TEST(dense_vector_view_copy_constructor, given_f_dense_vector_view_should_copy) {
    // arrange
    const DenseVector<float> v = {1, 2, 3, 4, 5};
    const DenseVectorView<float> view(v, 3, 2);
    // act
    const DenseVectorView<float> newView = view;
    // assert
    ASSERT_TRUE((compare(newView.n(), 3)));
    ASSERT_TRUE((compare(newView.offset(), 2)));
    ASSERT_TRUE(&view.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), view, newView)));
}

TEST(dense_vector_view_copy_constructor, given_cf_dense_vector_view_should_copy) {
    // arrange
    const DenseVector<std::complex<float>> v = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    const DenseVectorView<std::complex<float>> view(v, 3, 2);
    // act
    const DenseVectorView<std::complex<float>> newView = view;
    // assert
    ASSERT_TRUE((compare(newView.n(), 3)));
    ASSERT_TRUE((compare(newView.offset(), 2)));
    ASSERT_TRUE(&view.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), view, newView)));
}
#pragma endregion
#pragma region indexing_operator
TEST(dense_vector_view_indexing_operator, given_index_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[2], InvalidOperationException);
}

TEST(dense_vector_view_indexing_operator, given_big_index_should_throw_1) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}

TEST(dense_vector_view_indexing_operator, given_big_index_should_throw_2) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}
#pragma endregion
#pragma region const_indexing_operator
TEST(dense_vector_view_const_indexing_operator, given_index_should_return_const_reference_f) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVectorView<float> v(a, 3, 2);
    // act
    const float& v0 = v[0];
    const float& v1 = v[1];
    const float& v2 = v[2];
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), v0, 3)));
    ASSERT_TRUE((compare(Precision(0.001f), v1, 4)));
    ASSERT_TRUE((compare(Precision(0.001f), v2, 5)));
}

TEST(dense_vector_view_const_indexing_operator, given_index_should_return_const_reference_cf) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    const DenseVectorView<std::complex<float>> v(a, 3, 2);
    // act
    const std::complex<float>& v0 = v[0];
    const std::complex<float>& v1 = v[1];
    const std::complex<float>& v2 = v[2];
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), v0, std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), v1, std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), v2, std::complex<float>(9, 10))));
}

TEST(dense_vector_view_const_indexing_operator, given_big_index_should_throw_1) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}

TEST(dense_vector_view_const_indexing_operator, given_big_index_should_throw_2) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}
#pragma endregion
#pragma region offset
TEST(dense_vector_view_offset, should_return_offset) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVectorView<float> v(a, 3, 1);
    constexpr int expected = 1;
    // act
    const int offset = v.offset();
    // assert
    ASSERT_TRUE((compare(offset, expected)));
}
#pragma endregion
#pragma region owner
TEST(dense_vector_view_owner, should_return_owner) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVectorView<float> v(a, 3, 1);
    // act
    const DenseVector<float>& owner = v.owner();
    // assert
    ASSERT_TRUE(&owner == &a);
}
#pragma endregion
