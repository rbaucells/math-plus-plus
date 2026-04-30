#include "gtest/gtest.h"

#include "mathpp/math.h"

#pragma region sparse_vector_like
TEST(sparse_vector_like, given_sparse_vector_should_return_true) {
    static_assert(sparse_vector_like<SparseVector<float>>, "sparse_vector_like is wrong, 'SparseVector<float>' should be sparse_vector_like");
}

TEST(sparse_vector_like, given_sparse_vector_view_should_return_true) {
    static_assert(sparse_vector_like<SparseVectorView<float>>, "sparse_vector_like is wrong, 'SparseVectorView<float>' should be sparse_vector_like");
}

TEST(sparse_vector_like, given_custom_sparse_vector_should_return_true) {
    static_assert(sparse_vector_like<CustomSparseVector<float>>, "sparse_vector_like is wrong, 'CustomSparseVector<float>' should be sparse_vector_like");
}

TEST(sparse_vector_like, given_float_should_return_false) {
    static_assert(!sparse_vector_like<float>, "sparse_vector_like is wrong, 'float' should not be sparse_vector_like");
}

TEST(sparse_vector_like, given_dense_vector_should_return_false) {
    static_assert(!sparse_vector_like<DenseVector<float>>, "sparse_vector_like is wrong, 'DenseVector<float>' should not be sparse_vector_like");
}
#pragma endregion
#pragma region sparse_vector
TEST(sparse_vector, given_sparse_vector_should_return_true) {
    static_assert(sparse_vector<SparseVector<float>>, "sparse_vector is wrong, 'SparseVector<float>' should be sparse_vector");
}

TEST(sparse_vector, given_sparse_vector_view_should_return_false) {
    static_assert(!sparse_vector<SparseVectorView<float>>, "sparse_vector is wrong, 'SparseVectorView<float>' should not be sparse_vector");
}

TEST(sparse_vector, given_custom_sparse_vector_should_return_false) {
    static_assert(!sparse_vector<CustomSparseVector<float>>, "sparse_vector is wrong, 'CustomSparseVector<float>' should not be sparse_vector");
}
#pragma endregion
#pragma region sparse_vector_view
TEST(sparse_vector_view, given_sparse_vector_view_should_return_true) {
    static_assert(sparse_vector_view<SparseVectorView<float>>, "sparse_vector_view is wrong, 'SparseVectorView<float>' should be sparse_vector_view");
}

TEST(sparse_vector_view, given_sparse_vector_should_return_false) {
    static_assert(!sparse_vector_view<SparseVector<float>>, "sparse_vector_view is wrong, 'SparseVector<float>' should not be sparse_vector_view");
}

TEST(sparse_vector_view, given_custom_sparse_vector_should_return_false) {
    static_assert(!sparse_vector_view<CustomSparseVector<float>>, "sparse_vector_view is wrong, 'CustomSparseVector<float>' should not be sparse_vector_view");
}
#pragma endregion
#pragma region custom_sparse_vector
TEST(custom_sparse_vector, given_custom_sparse_vector_should_return_true) {
    static_assert(custom_sparse_vector<CustomSparseVector<float>>, "custom_sparse_vector is wrong, 'CustomSparseVector<float>' should be custom_sparse_vector");
}

TEST(custom_sparse_vector, given_sparse_vector_should_return_false) {
    static_assert(!custom_sparse_vector<SparseVector<float>>, "custom_sparse_vector is wrong, 'SparseVector<float>' should not be custom_sparse_vector");
}

TEST(custom_sparse_vector, given_sparse_vector_view_should_return_false) {
    static_assert(!custom_sparse_vector<SparseVectorView<float>>, "custom_sparse_vector is wrong, 'SparseVectorView<float>' should not be custom_sparse_vector");
}
#pragma endregion
#pragma region underlying_type
TEST(underlying_type, given_sparse_vector_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<SparseVector<float>>, float>, "underlying_type_t is wrong, 'SparseVector<float>' should be 'float'");
}

TEST(underlying_type, given_sparse_vector_view_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<SparseVectorView<float>>, float>, "underlying_type_t is wrong, 'SparseVectorView<float>' should be 'float'");
}

TEST(underlying_type, given_custom_sparse_vector_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<CustomSparseVector<float>>, float>, "underlying_type_t is wrong, 'CustomSparseVector<float>' should be 'float'");
}
#pragma endregion
#pragma region assert_same_size
TEST(assert_same_size, given_same_sized_sparse_vectors_templated_on_float_should_not_throw) {
    // arrange
    const SparseVector<float> a(3);
    const SparseVector<float> b(3);
    const SparseVector<float> c(3);
    // act / assert
    ASSERT_NO_THROW(assert_same_size(a, b, c));
}

TEST(assert_same_size, given_same_sized_sparse_vectors_templated_on_float_int_and_complex_float_should_not_throw) {
    // arrange
    const SparseVector<float> a(3);
    const SparseVector<int> b(3);
    const SparseVector<std::complex<float>> c(3);
    // act / assert
    ASSERT_NO_THROW(assert_same_size(a, b, c));
}

TEST(assert_same_size, given_different_sized_sparse_vectors_templated_on_float_should_throw) {
    // arrange
    const SparseVector<float> a(3);
    const SparseVector<float> b(4);
    const SparseVector<float> c(5);
    // act / assert
    ASSERT_THROW(assert_same_size(a, b, c), InvalidDimensionException);
}

TEST(assert_same_size, given_different_sized_sparse_vectors_templated_on_float_int_and_complex_float_should_throw) {
    // arrange
    const SparseVector<float> a(3);
    const SparseVector<int> b(4);
    const SparseVector<std::complex<float>> c(5);
    // act / assert
    ASSERT_THROW(assert_same_size(a, b, c), InvalidDimensionException);
}
#pragma endregion