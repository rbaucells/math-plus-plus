#include "gtest/gtest.h"

#include "mathpp/matrix/sparse/csc/core.h"
#include "mathpp/matrix/dense/core.h"

#pragma region sparse_matrix_like
TEST(sparse_matrix_like, given_sparse_matrix_should_return_true) {
    static_assert(sparse_matrix_like<CSCSparseMatrix<float>>, "sparse_matrix_like is wrong, 'SparseMatrix<float>' should be sparse_matrix_like");
}

TEST(sparse_matrix_like, given_sparse_matrix_view_should_return_true) {
    static_assert(sparse_matrix_like<CSCSparseMatrixView<float>>, "sparse_matrix_like is wrong, 'SparseMatrixView<float>' should be sparse_matrix_like");
}

TEST(sparse_matrix_like, given_custom_sparse_matrix_should_return_true) {
    static_assert(sparse_matrix_like<CSCCustomSparseMatrix<float>>, "sparse_matrix_like is wrong, 'CustomSparseMatrix<float>' should be sparse_matrix_like");
}

TEST(sparse_matrix_like, given_float_should_return_false) {
    static_assert(!sparse_matrix_like<float>, "sparse_matrix_like is wrong, 'float' should not be sparse_matrix_like");
}

TEST(sparse_matrix_like, given_dense_matrix_should_return_false) {
    static_assert(!sparse_matrix_like<DenseMatrix<float>>, "sparse_matrix_like is wrong, 'DenseMatrix<float>' should not be sparse_matrix_like");
}
#pragma endregion
#pragma region csc_sparse_matrix
TEST(csc_sparse_matrix, given_csc_sparse_matrix_should_return_true) {
    static_assert(csc_sparse_matrix<CSCSparseMatrix<float>>, "csc_sparse_matrix is wrong, 'SparseMatrix<float>' should be csc_sparse_matrix");
}

TEST(csc_sparse_matrix, given_csc_sparse_matrix_view_should_return_false) {
    static_assert(!csc_sparse_matrix<CSCSparseMatrixView<float>>, "csc_sparse_matrix is wrong, 'SparseMatrixView<float>' should not be csc_sparse_matrix");
}

TEST(csc_sparse_matrix, given_custom_csc_sparse_matrix_should_return_false) {
    static_assert(!csc_sparse_matrix<CSCCustomSparseMatrix<float>>, "csc_sparse_matrix is wrong, 'CustomSparseMatrix<float>' should not be csc_sparse_matrix");
}
#pragma endregion
#pragma region csc_sparse_matrix_view
TEST(csc_sparse_matrix_view, given_csc_sparse_matrix_view_should_return_true) {
    static_assert(csc_sparse_matrix_view<CSCSparseMatrixView<float>>, "csc_sparse_matrix_view is wrong, 'SparseMatrixView<float>' should be csc_sparse_matrix_view");
}

TEST(csc_sparse_matrix_view, given_csc_sparse_matrix_should_return_false) {
    static_assert(!csc_sparse_matrix_view<CSCSparseMatrix<float>>, "csc_sparse_matrix_view is wrong, 'SparseMatrix<float>' should not be csc_sparse_matrix_view");
}

TEST(csc_sparse_matrix_view, given_custom_csc_sparse_matrix_should_return_false) {
    static_assert(!csc_sparse_matrix_view<CSCCustomSparseMatrix<float>>, "csc_sparse_matrix_view is wrong, 'CustomSparseMatrix<float>' should not be csc_sparse_matrix_view");
}
#pragma endregion
#pragma region custom_csc_sparse_matrix
TEST(custom_csc_sparse_matrix, given_custom_csc_sparse_matrix_should_return_true) {
    static_assert(csc_custom_sparse_matrix<CSCCustomSparseMatrix<float>>, "custom_csc_sparse_matrix is wrong, 'CustomSparseMatrix<float>' should be custom_csc_sparse_matrix");
}

TEST(custom_csc_sparse_matrix, given_csc_sparse_matrix_should_return_false) {
    static_assert(!csc_custom_sparse_matrix<CSCSparseMatrix<float>>, "custom_csc_sparse_matrix is wrong, 'SparseMatrix<float>' should not be custom_csc_sparse_matrix");
}

TEST(custom_csc_sparse_matrix, given_csc_sparse_matrix_view_should_return_false) {
    static_assert(!csc_custom_sparse_matrix<CSCSparseMatrixView<float>>, "custom_csc_sparse_matrix is wrong, 'SparseMatrixView<float>' should not be custom_csc_sparse_matrix");
}
#pragma endregion
#pragma region underlying_type
TEST(underlying_type, given_sparse_matrix_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<CSCSparseMatrix<float>>, float>, "underlying_type_t is wrong, 'SparseMatrix<float>' should be 'float'");
}

TEST(underlying_type, given_sparse_matrix_view_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<CSCSparseMatrixView<float>>, float>, "underlying_type_t is wrong, 'SparseMatrixView<float>' should be 'float'");
}

TEST(underlying_type, given_custom_sparse_matrix_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<CSCCustomSparseMatrix<float>>, float>, "underlying_type_t is wrong, 'CustomSparseMatrix<float>' should be 'float'");
}
#pragma endregion
#pragma region assert_same_dimensions
TEST(assert_same_dimensions, given_sparse_matrices_templated_on_float_of_same_dimensions_should_not_throw) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3);
    const CSCSparseMatrix<float> b(3, 3);
    const CSCSparseMatrix<float> c(3, 3);
    // act / assert
    ASSERT_NO_THROW(assert_same_dimensions(a, b, c));
}

TEST(assert_same_dimensions, given_sparse_matrices_templated_on_float_int_and_complex_float_of_same_dimensions_should_not_throw) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3);
    const CSCSparseMatrix<int> b(3, 3);
    const CSCSparseMatrix<std::complex<float>> c(3, 3);
    // act / assert
    ASSERT_NO_THROW(assert_same_dimensions(a, b, c));
}

TEST(assert_same_dimensions, given_sparse_matrices_templated_on_float_of_same_dimensions_should_throw) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3);
    const CSCSparseMatrix<float> b(3, 4);
    const CSCSparseMatrix<float> c(4, 3);
    // act / assert
    ASSERT_THROW(assert_same_dimensions(a, b, c), InvalidDimensionException);
}

TEST(assert_same_dimensions, given_sparse_matrices_templated_on_float_int_and_complex_float_of_different_dimensions_should_throw) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3);
    const CSCSparseMatrix<int> b(3, 4);
    const CSCSparseMatrix<std::complex<float>> c(4, 3);
    // act / assert
    ASSERT_THROW(assert_same_dimensions(a, b, c), InvalidDimensionException);
}
#pragma endregion
#pragma region assert_square
TEST(assert_square, given_square_sparse_matrix_templated_on_float_should_return_true) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3);
    // act / assert
    ASSERT_NO_THROW(assert_square(a));
}

TEST(assert_square, given_square_sparse_matrix_templated_on_complex_float_should_return_true) {
    // arrange
    const CSCSparseMatrix<std::complex<float>> a(3, 3);
    // act / assert
    ASSERT_NO_THROW(assert_square(a));
}

TEST(assert_square, given_non_square_sparse_matrix_templated_on_float_should_return_false) {
    // arrange
    const CSCSparseMatrix<float> a(4, 3);
    // act / assert
    ASSERT_THROW(assert_square(a), InvalidDimensionException);
}

TEST(assert_square, given_non_square_sparse_matrix_templated_on_complex_float_should_return_false) {
    // arrange
    const CSCSparseMatrix<std::complex<float>> a(3, 4);
    // act / assert
    ASSERT_THROW(assert_square(a), InvalidDimensionException);
}
#pragma endregion