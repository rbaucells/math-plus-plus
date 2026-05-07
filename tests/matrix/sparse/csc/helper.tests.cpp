#include "gtest/gtest.h"

#include "mathpp/matrix/sparse/csc/core.h"

#pragma region csc_sparse_matrix_like
TEST(csc_sparse_matrix_like, given_csc_sparse_matrix_should_return_true) {
    static_assert(csc_sparse_matrix_like<CSCSparseMatrix<float>>, "csc_sparse_matrix_like is wrong, 'CSCSparseMatrix<float>' should be csc_sparse_matrix_like");
}

TEST(csc_sparse_matrix_like, given_csc_sparse_matrix_view_should_return_true) {
    static_assert(csc_sparse_matrix_like<CSCSparseMatrixView<float>>, "csc_sparse_matrix_like is wrong, 'CSCSparseMatrixView<float>' should be csc_sparse_matrix_like");
}

TEST(csc_sparse_matrix_like, given_csc_custom_sparse_matrix_should_return_true) {
    static_assert(csc_sparse_matrix_like<CSCCustomSparseMatrix<float>>, "csc_sparse_matrix_like is wrong, 'CSCCustomSparseMatrix<float>' should be csc_sparse_matrix_like");
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
