#include "gtest/gtest.h"

#include "mathpp/vector.h"

#pragma region sparse_vector_like
TEST(sparse_vector_like, given_sparse_vector_should_return_true) {
    static_assert(sparse_vector_like<CooSparseVector<float>>, "sparse_vector_like is wrong, 'SparseVector<float>' should be sparse_vector_like");
}

TEST(sparse_vector_like, given_sparse_vector_view_should_return_true) {
    static_assert(sparse_vector_like<CooSparseVectorView<float>>, "sparse_vector_like is wrong, 'SparseVectorView<float>' should be sparse_vector_like");
}

TEST(sparse_vector_like, given_custom_sparse_vector_should_return_true) {
    static_assert(sparse_vector_like<CooCustomSparseVector<float>>, "sparse_vector_like is wrong, 'CustomSparseVector<float>' should be sparse_vector_like");
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
    static_assert(coo_sparse_vector<CooSparseVector<float>>, "sparse_vector is wrong, 'SparseVector<float>' should be sparse_vector");
}

TEST(sparse_vector, given_sparse_vector_view_should_return_false) {
    static_assert(!coo_sparse_vector<CooSparseVectorView<float>>, "sparse_vector is wrong, 'SparseVectorView<float>' should not be sparse_vector");
}

TEST(sparse_vector, given_custom_sparse_vector_should_return_false) {
    static_assert(!coo_sparse_vector<CooCustomSparseVector<float>>, "sparse_vector is wrong, 'CustomSparseVector<float>' should not be sparse_vector");
}
#pragma endregion
#pragma region sparse_vector_view
TEST(sparse_vector_view, given_sparse_vector_view_should_return_true) {
    static_assert(coo_sparse_vector_view<CooSparseVectorView<float>>, "sparse_vector_view is wrong, 'SparseVectorView<float>' should be sparse_vector_view");
}

TEST(sparse_vector_view, given_sparse_vector_should_return_false) {
    static_assert(!coo_sparse_vector_view<CooSparseVector<float>>, "sparse_vector_view is wrong, 'SparseVector<float>' should not be sparse_vector_view");
}

TEST(sparse_vector_view, given_custom_sparse_vector_should_return_false) {
    static_assert(!coo_sparse_vector_view<CooCustomSparseVector<float>>, "sparse_vector_view is wrong, 'CustomSparseVector<float>' should not be sparse_vector_view");
}
#pragma endregion
#pragma region custom_sparse_vector
TEST(custom_sparse_vector, given_custom_sparse_vector_should_return_true) {
    static_assert(coo_custom_sparse_vector<CooCustomSparseVector<float>>, "custom_sparse_vector is wrong, 'CustomSparseVector<float>' should be custom_sparse_vector");
}

TEST(custom_sparse_vector, given_sparse_vector_should_return_false) {
    static_assert(!coo_custom_sparse_vector<CooSparseVector<float>>, "custom_sparse_vector is wrong, 'SparseVector<float>' should not be custom_sparse_vector");
}

TEST(custom_sparse_vector, given_sparse_vector_view_should_return_false) {
    static_assert(!coo_custom_sparse_vector<CooSparseVectorView<float>>, "custom_sparse_vector is wrong, 'SparseVectorView<float>' should not be custom_sparse_vector");
}
#pragma endregion
#pragma region underlying_type
TEST(underlying_type, given_sparse_vector_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<CooSparseVector<float>>, float>, "underlying_type_t is wrong, 'SparseVector<float>' should be 'float'");
}

TEST(underlying_type, given_sparse_vector_view_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<CooSparseVectorView<float>>, float>, "underlying_type_t is wrong, 'SparseVectorView<float>' should be 'float'");
}

TEST(underlying_type, given_custom_sparse_vector_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<CooCustomSparseVector<float>>, float>, "underlying_type_t is wrong, 'CustomSparseVector<float>' should be 'float'");
}
#pragma endregion
#pragma region assert_same_size
TEST(assert_same_size, given_same_sized_sparse_vectors_templated_on_float_should_not_throw) {
    // arrange
    const CooSparseVector<float> a(3);
    const CooSparseVector<float> b(3);
    const CooSparseVector<float> c(3);
    // act / assert
    ASSERT_NO_THROW(assert_same_size(a, b, c));
}

TEST(assert_same_size, given_same_sized_sparse_vectors_templated_on_float_int_and_complex_float_should_not_throw) {
    // arrange
    const CooSparseVector<float> a(3);
    const CooSparseVector<int> b(3);
    const CooSparseVector<std::complex<float>> c(3);
    // act / assert
    ASSERT_NO_THROW(assert_same_size(a, b, c));
}

TEST(assert_same_size, given_different_sized_sparse_vectors_templated_on_float_should_throw) {
    // arrange
    const CooSparseVector<float> a(3);
    const CooSparseVector<float> b(4);
    const CooSparseVector<float> c(5);
    // act / assert
    ASSERT_THROW(assert_same_size(a, b, c), InvalidDimensionException);
}

TEST(assert_same_size, given_different_sized_sparse_vectors_templated_on_float_int_and_complex_float_should_throw) {
    // arrange
    const CooSparseVector<float> a(3);
    const CooSparseVector<int> b(4);
    const CooSparseVector<std::complex<float>> c(5);
    // act / assert
    ASSERT_THROW(assert_same_size(a, b, c), InvalidDimensionException);
}
#pragma endregion