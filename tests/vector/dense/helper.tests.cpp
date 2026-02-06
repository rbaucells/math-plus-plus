#include "gtest/gtest.h"

#include "mathpp/math.h"

#pragma region dense_vector_base
TEST(dense_vector_base, given_dense_vector_should_return_true) {
    static_assert(dense_vector_base<DenseVector<float>>, "dense_vector_base is wrong, 'DenseVector<float>' should be dense_vector_base");
}

TEST(dense_vector_base, given_dense_vector_view_should_return_true) {
    static_assert(dense_vector_base<DenseVectorView<float>>, "dense_vector_base is wrong, 'DenseVectorView<float>' should be dense_vector_base");
}

TEST(dense_vector_base, given_custom_dense_vector_should_return_true) {
    static_assert(dense_vector_base<CustomDenseVector<float>>, "dense_vector_base is wrong, 'CustomDenseVector<float>' should be dense_vector_base");
}

TEST(dense_vector_base, given_float_should_return_false) {
    static_assert(!dense_vector_base<float>, "dense_vector_base is wrong, 'float' should not be dense_vector_base");
}

TEST(dense_vector_base, given_sparse_vector_should_return_false) {
    static_assert(!dense_vector_base<SparseVector<float>>, "dense_vector_base is wrong, 'SparseVector<float>' should not be dense_vector_base");
}
#pragma endregion
#pragma region dense_vector
TEST(dense_vector, given_dense_vector_should_return_true) {
    static_assert(dense_vector<DenseVector<float>>, "dense_vector is wrong, 'DenseVector<float>' should be dense_vector");
}

TEST(dense_vector, given_dense_vector_view_should_return_false) {
    static_assert(!dense_vector<DenseVectorView<float>>, "dense_vector is wrong, 'DenseVectorView<float>' should not be dense_vector");
}

TEST(dense_vector, given_custom_dense_vector_should_return_false) {
    static_assert(!dense_vector<CustomDenseVector<float>>, "dense_vector is wrong, 'CustomDenseVector<float>' should not be dense_vector");
}

TEST(dense_vector, given_dense_vector_base_should_return_false) {
    static_assert(!dense_vector<DenseVectorBase<float>>, "dense_vector is wrong, 'DenseVectorBase<float>' should not be dense_vector");
}
#pragma endregion
#pragma region dense_vector_view
TEST(dense_vector_view, given_dense_vector_view_should_return_true) {
    static_assert(dense_vector_view<DenseVectorView<float>>, "dense_vector_view is wrong, 'DenseVectorView<float>' should be dense_vector_view");
}

TEST(dense_vector_view, given_dense_vector_should_return_false) {
    static_assert(!dense_vector_view<DenseVector<float>>, "dense_vector_view is wrong, 'DenseVector<float>' should not be dense_vector_view");
}

TEST(dense_vector_view, given_custom_dense_vector_should_return_false) {
    static_assert(!dense_vector_view<CustomDenseVector<float>>, "dense_vector_view is wrong, 'CustomDenseVector<float>' should not be dense_vector_view");
}

TEST(dense_vector_view, given_dense_vector_base_should_return_false) {
    static_assert(!dense_vector_view<DenseVectorBase<float>>, "dense_vector_view is wrong, 'DenseVectorBase<float>' should not be dense_vector_view");
}
#pragma endregion
#pragma region custom_dense_vector
TEST(custom_dense_vector, given_custom_dense_vector_should_return_true) {
    static_assert(custom_dense_vector<CustomDenseVector<float>>, "custom_dense_vector is wrong, 'CustomDenseVector<float>' should be custom_dense_vector");
}

TEST(custom_dense_vector, given_dense_vector_should_return_false) {
    static_assert(!custom_dense_vector<DenseVector<float>>, "custom_dense_vector is wrong, 'DenseVector<float>' should not be custom_dense_vector");
}

TEST(custom_dense_vector, given_dense_vector_view_should_return_false) {
    static_assert(!custom_dense_vector<DenseVectorView<float>>, "custom_dense_vector is wrong, 'DenseVectorView<float>' should not be custom_dense_vector");
}

TEST(custom_dense_vector, given_dense_vector_base_should_return_false) {
    static_assert(!custom_dense_vector<DenseVectorBase<float>>, "custom_dense_vector is wrong, 'DenseVectorBase<float>' should not be custom_dense_vector");
}
#pragma endregion
#pragma region underlying_type
TEST(underlying_type, given_dense_vector_base_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<DenseVectorBase<float>>, float>, "underlying_type_t is wrong, 'DenseVectorBase<float>' should be 'float'");
}

TEST(underlying_type, given_dense_vector_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<DenseVector<float>>, float>, "underlying_type_t is wrong, 'DenseVector<float>' should be 'float'");
}

TEST(underlying_type, given_dense_vector_view_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<DenseVectorView<float>>, float>, "underlying_type_t is wrong, 'DenseVectorView<float>' should be 'float'");
}

TEST(underlying_type, given_custom_dense_vector_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<CustomDenseVector<float>>, float>, "underlying_type_t is wrong, 'CustomDenseVector<float>' should be 'float'");
}
#pragma endregion
#pragma region assert_same_size
TEST(assert_same_size, given_same_sized_dense_vectors_templated_on_float_should_not_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> b = {1, 2, 3};
    const DenseVector<float> c = {1, 2, 3};
    // act / assert
    ASSERT_NO_THROW(assert_same_size(a, b, c));
}

TEST(assert_same_size, given_same_sized_dense_vectors_templated_on_float_int_and_complex_float_should_not_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<int> b = {1, 2, 3};
    const DenseVector<std::complex<float>> c = {{1, 2}, {3, 4}, {5, 6}};
    // act / assert
    ASSERT_NO_THROW(assert_same_size(a, b, c));
}

TEST(assert_same_size, given_different_sized_dense_vectors_templated_on_float_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> b = {1, 2, 3, 4};
    const DenseVector<float> c = {1, 2, 3, 4, 5};
    // act / assert
    ASSERT_THROW(assert_same_size(a, b, c), InvalidDimensionException);
}

TEST(assert_same_size, given_different_sized_dense_vectors_templated_on_float_int_and_complex_float_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<int> b = {1, 2, 3, 4};
    const DenseVector<std::complex<float>> c = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    // act / assert
    ASSERT_THROW(assert_same_size(a, b, c), InvalidDimensionException);
}
#pragma endregion