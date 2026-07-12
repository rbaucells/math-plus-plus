#include "gtest/gtest.h"

#include "mathpp/all.h"

TEST(debugger_tests, dense_matrices) {
    // square dense matrix
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // wide dense matrix
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}};
    // tall dense matrix
    const DenseMatrix<float> c = {{1, 2}, {3, 4}, {5, 6}};
}

TEST(debugger_tests, dense_matrice_views) {
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}};
    const DenseMatrix<float> c = {{1, 2}, {3, 4}, {5, 6}};

    // square dense matrix view
    const DenseMatrixView<float> d(a, 2, 2, 1, 1);
    // wide dense matrix view
    const DenseMatrixView<float> e(b, 1, 2, 0, 1);
    // tall dense matrix view
    const DenseMatrixView<float> f(c, 3, 1, 1, 0);
}

TEST(debugger_tests, csc_sparse_matrices) {
    // square csc sparse matrix
    const CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {5, 1, 1}, {6, 2, 1}, {8, 1, 2}});
    // wide csc sparse matrix
    const CSCSparseMatrix<float> b(2, 3, {{1, 0, 0}, {4, 0, 1}, {5, 1, 1}});
    // tall csc sparse matrix
    const CSCSparseMatrix<float> c(3, 2, {{1, 0, 0}, {5, 1, 1}, {8, 1, 2}});
}

TEST(debugger_tests, csc_sparse_matrice_views) {
    const CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {5, 1, 1}, {6, 2, 1}, {8, 1, 2}});
    const CSCSparseMatrix<float> b(2, 3, {{1, 0, 0}, {4, 0, 1}, {5, 1, 1}});
    const CSCSparseMatrix<float> c(3, 2, {{1, 0, 0}, {5, 1, 1}, {8, 1, 2}});

    // square csc sparse matrix view
    const CSCSparseMatrixView<float> d(a, 2, 2, 0, 1);
    // wide csc sparse matrix view
    const CSCSparseMatrixView<float> e(b, 1, 2, 0, 1);
    // tall csc sparse matrix view
    const CSCSparseMatrixView<float> f(c, 3, 1, 1, 0);
}

TEST(debugger_tests, csr_sparse_matrices) {
    // square csr sparse matrix
    const CSRSparseMatrix<float> a(3, 3, {{1, 0, 0}, {5, 1, 1}, {6, 2, 1}, {8, 1, 2}});
    // wide csr sparse matrix
    const CSRSparseMatrix<float> b(2, 3, {{1, 0, 0}, {4, 0, 1}, {5, 1, 1}});
    // tall csr sparse matrix
    const CSRSparseMatrix<float> c(3, 2, {{1, 0, 0}, {5, 1, 1}, {8, 1, 2}});
}

TEST(debugger_tests, csr_sparse_matrice_views) {
    const CSRSparseMatrix<float> a(3, 3, {{1, 0, 0}, {5, 1, 1}, {6, 2, 1}, {8, 1, 2}});
    const CSRSparseMatrix<float> b(2, 3, {{1, 0, 0}, {4, 0, 1}, {5, 1, 1}});
    const CSRSparseMatrix<float> c(3, 2, {{1, 0, 0}, {5, 1, 1}, {8, 1, 2}});

    // square csr sparse matrix view
    const CSRSparseMatrixView<float> d(a, 2, 2, 0, 1);
    // wide csr sparse matrix view
    const CSRSparseMatrixView<float> e(b, 1, 2, 0, 1);
    // tall csr sparse matrix view
    const CSRSparseMatrixView<float> f(c, 3, 1, 1, 0);
}

TEST(debugger_tests, dense_vectors) {
    const DenseVector<float> a = {1, 2, 3};
}

TEST(debugger_tests, dense_vector_views) {
    const DenseVector<float> a = {1, 2, 3};

    const DenseVectorView<float> b(a, 2, 0);
}

TEST(debugger_tests, coo_sparse_vectors) {
    const CooSparseVector<float> a(5, {{1, 0}, {3, 2}, {5, 4}});
}

TEST(debugger_tests, coo_sparse_vector_views) {
    const CooSparseVector<float> a(5, {{1, 0}, {3, 2}, {5, 4}});

    const CooSparseVectorView<float> b(a, 3, 1);
}

TEST(debugger_tests, dok_sparse_vectors) {
    const DokSparseVector<float> a(5, {{1, 0}, {3, 2}, {5, 4}});
}

TEST(debugger_tests, dok_sparse_vector_views) {
    const DokSparseVector<float> a(5, {{1, 0}, {3, 2}, {5, 4}});

    const DokSparseVectorView<float> b(a, 3, 1);
}
