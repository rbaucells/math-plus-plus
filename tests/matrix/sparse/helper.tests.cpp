#include "gtest/gtest.h"

#include "mathpp/matrix.h"

#pragma region sparse_matrix_like
TEST(sparse_matrix_like, given_sparse_matrix_should_return_true) {
    static_assert(sparse_matrix_like<SparseMatrix<float>>, "sparse_matrix_like is wrong, 'SparseMatrix<float>' should be sparse_matrix_like");
}

TEST(sparse_matrix_like, given_sparse_matrix_view_should_return_true) {
    static_assert(sparse_matrix_like<SparseMatrixView<float>>, "sparse_matrix_like is wrong, 'SparseMatrixView<float>' should be sparse_matrix_like");
}

TEST(sparse_matrix_like, given_custom_sparse_matrix_should_return_true) {
    static_assert(sparse_matrix_like<CustomSparseMatrix<float>>, "sparse_matrix_like is wrong, 'CustomSparseMatrix<float>' should be sparse_matrix_like");
}

TEST(sparse_matrix_like, given_float_should_return_false) {
    static_assert(!sparse_matrix_like<float>, "sparse_matrix_like is wrong, 'float' should not be sparse_matrix_like");
}

TEST(sparse_matrix_like, given_dense_matrix_should_return_false) {
    static_assert(!sparse_matrix_like<DenseMatrix<float>>, "sparse_matrix_like is wrong, 'DenseMatrix<float>' should not be sparse_matrix_like");
}
#pragma endregion
#pragma region sparse_matrix
TEST(sparse_matrix, given_sparse_matrix_should_return_true) {
    static_assert(sparse_matrix<SparseMatrix<float>>, "sparse_matrix is wrong, 'SparseMatrix<float>' should be sparse_matrix");
}

TEST(sparse_matrix, given_sparse_matrix_view_should_return_false) {
    static_assert(!sparse_matrix<SparseMatrixView<float>>, "sparse_matrix is wrong, 'SparseMatrixView<float>' should not be sparse_matrix");
}

TEST(sparse_matrix, given_custom_sparse_matrix_should_return_false) {
    static_assert(!sparse_matrix<CustomSparseMatrix<float>>, "sparse_matrix is wrong, 'CustomSparseMatrix<float>' should not be sparse_matrix");
}
#pragma endregion
#pragma region sparse_matrix_view
TEST(sparse_matrix_view, given_sparse_matrix_view_should_return_true) {
    static_assert(sparse_matrix_view<SparseMatrixView<float>>, "sparse_matrix_view is wrong, 'SparseMatrixView<float>' should be sparse_matrix_view");
}

TEST(sparse_matrix_view, given_sparse_matrix_should_return_false) {
    static_assert(!sparse_matrix_view<SparseMatrix<float>>, "sparse_matrix_view is wrong, 'SparseMatrix<float>' should not be sparse_matrix_view");
}

TEST(sparse_matrix_view, given_custom_sparse_matrix_should_return_false) {
    static_assert(!sparse_matrix_view<CustomSparseMatrix<float>>, "sparse_matrix_view is wrong, 'CustomSparseMatrix<float>' should not be sparse_matrix_view");
}
#pragma endregion
#pragma region custom_sparse_matrix
TEST(custom_sparse_matrix, given_custom_sparse_matrix_should_return_true) {
    static_assert(custom_sparse_matrix<CustomSparseMatrix<float>>, "custom_sparse_matrix is wrong, 'CustomSparseMatrix<float>' should be custom_sparse_matrix");
}

TEST(custom_sparse_matrix, given_sparse_matrix_should_return_false) {
    static_assert(!custom_sparse_matrix<SparseMatrix<float>>, "custom_sparse_matrix is wrong, 'SparseMatrix<float>' should not be custom_sparse_matrix");
}

TEST(custom_sparse_matrix, given_sparse_matrix_view_should_return_false) {
    static_assert(!custom_sparse_matrix<SparseMatrixView<float>>, "custom_sparse_matrix is wrong, 'SparseMatrixView<float>' should not be custom_sparse_matrix");
}
#pragma endregion
#pragma region underlying_type
TEST(underlying_type, given_sparse_matrix_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<SparseMatrix<float>>, float>, "underlying_type_t is wrong, 'SparseMatrix<float>' should be 'float'");
}

TEST(underlying_type, given_sparse_matrix_view_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<SparseMatrixView<float>>, float>, "underlying_type_t is wrong, 'SparseMatrixView<float>' should be 'float'");
}

TEST(underlying_type, given_custom_sparse_matrix_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<CustomSparseMatrix<float>>, float>, "underlying_type_t is wrong, 'CustomSparseMatrix<float>' should be 'float'");
}
#pragma endregion
#pragma region assert_same_dimensions
TEST(assert_same_dimensions, given_sparse_matrices_templated_on_float_of_same_dimensions_should_not_throw) {
    // arrange
    const SparseMatrix<float> a(3, 3);
    const SparseMatrix<float> b(3, 3);
    const SparseMatrix<float> c(3, 3);
    // act / assert
    ASSERT_NO_THROW(assert_same_dimensions(a, b, c));
}

TEST(assert_same_dimensions, given_sparse_matrices_templated_on_float_int_and_complex_float_of_same_dimensions_should_not_throw) {
    // arrange
    const SparseMatrix<float> a(3, 3);
    const SparseMatrix<int> b(3, 3);
    const SparseMatrix<std::complex<float>> c(3, 3);
    // act / assert
    ASSERT_NO_THROW(assert_same_dimensions(a, b, c));
}

TEST(assert_same_dimensions, given_sparse_matrices_templated_on_float_of_same_dimensions_should_throw) {
    // arrange
    const SparseMatrix<float> a(3, 3);
    const SparseMatrix<float> b(3, 4);
    const SparseMatrix<float> c(4, 3);
    // act / assert
    ASSERT_THROW(assert_same_dimensions(a, b, c), InvalidDimensionException);
}

TEST(assert_same_dimensions, given_sparse_matrices_templated_on_float_int_and_complex_float_of_different_dimensions_should_throw) {
    // arrange
    const SparseMatrix<float> a(3, 3);
    const SparseMatrix<int> b(3, 4);
    const SparseMatrix<std::complex<float>> c(4, 3);
    // act / assert
    ASSERT_THROW(assert_same_dimensions(a, b, c), InvalidDimensionException);
}
#pragma endregion
#pragma region assert_square
TEST(assert_square, given_square_sparse_matrix_templated_on_float_should_return_true) {
    // arrange
    const SparseMatrix<float> a(3, 3);
    // act / assert
    ASSERT_NO_THROW(assert_square(a));
}

TEST(assert_square, given_square_sparse_matrix_templated_on_complex_float_should_return_true) {
    // arrange
    const SparseMatrix<std::complex<float>> a(3, 3);
    // act / assert
    ASSERT_NO_THROW(assert_square(a));
}

TEST(assert_square, given_non_square_sparse_matrix_templated_on_float_should_return_false) {
    // arrange
    const SparseMatrix<float> a(4, 3);
    // act / assert
    ASSERT_THROW(assert_square(a), InvalidDimensionException);
}

TEST(assert_square, given_non_square_sparse_matrix_templated_on_complex_float_should_return_false) {
    // arrange
    const SparseMatrix<std::complex<float>> a(3, 4);
    // act / assert
    ASSERT_THROW(assert_square(a), InvalidDimensionException);
}
#pragma endregion