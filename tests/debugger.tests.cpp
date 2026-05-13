#include "gtest/gtest.h"

#include "mathpp/all.h"

TEST(debugger_tests, dense_matrices) {
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}};
    DenseMatrix<float> c = {{1, 2}, {3, 4}, {5, 6}};
}

TEST(debugger_tests, dense_matrice_views) {
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}};
    DenseMatrix<float> c = {{1, 2}, {3, 4}, {5, 6}};

    DenseMatrixView<float> d(a, 2, 2, 1, 1);
    DenseMatrixView<float> e(b, 1, 2, 0, 1);
    DenseMatrixView<float> f(c, 3, 1, 1, 0);
}

TEST(debugger_tests, sparse_matrices) {
    CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {5, 1, 1}, {6, 2, 1}, {8, 1, 2}});
    CSCSparseMatrix<float> b(3, 2, {{1, 0, 0}, {5, 1, 1}, {8, 1, 2}});
    CSCSparseMatrix<float> c(2, 3, {{1, 0, 0}, {4, 0, 1}, {5, 1, 1}});
}

TEST(debugger_tests, sparse_matrice_views) {
    CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {5, 1, 1}, {6, 2, 1}, {8, 1, 2}});
    CSCSparseMatrix<float> b(3, 2, {{1, 0, 0}, {5, 1, 1}, {8, 1, 2}});
    CSCSparseMatrix<float> c(2, 3, {{1, 0, 0}, {4, 0, 1}, {5, 1, 1}});

    CSCSparseMatrixView<float> d(a, 2, 2, 0, 1);
    CSCSparseMatrixView<float> e(b, 3, 1, 1, 0);
    CSCSparseMatrixView<float> f(c, 1, 2, 0, 1);
}

TEST(debugger_tests, dense_vectors) {
    DenseVector<float> a = {1, 2, 3};
}

TEST(debugger_tests, dense_vector_views) {
    DenseVector<float> a = {1, 2, 3};

    DenseVectorView<float> b(a, 2, 0);
}

TEST(debugger_tests, sparse_vectors) {
    CooSparseVector<float> a(5, {{1, 0}, {3, 2}, {5, 4}});
}

TEST(debugger_tests, sparse_vector_views) {
    CooSparseVector<float> a(5, {{1, 0}, {3, 2}, {5, 4}});

    CooSparseVectorView<float> b(a, 3, 1);
}
