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

    DenseMatrixView<DenseMatrix<float>> d(a, 2, 2, 1, 1);
    DenseMatrixView<DenseMatrix<float>> e(b, 1, 2, 0, 1);
    DenseMatrixView<DenseMatrix<float>> f(c, 3, 1, 1, 0);
}

TEST(debugger_tests, custom_dense_matrices) {
    float data[] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
    CustomDenseMatrix<float> a(data, 3, 3, 3);

    float data2[] = {1, 4, 2, 5, 3, 6};
    CustomDenseMatrix<float> b(data2, 2, 3, 2);

    float data3[] = {1, 3, 5, 2, 4, 6};
    CustomDenseMatrix<float> c(data3, 3, 2, 3);
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

TEST(debugger_tests, custom_sparse_matrices) {
    std::size_t* colOffsets = new std::size_t[4];
    colOffsets[0] = 0;
    colOffsets[1] = 2;
    colOffsets[2] = 3;
    colOffsets[3] = 4;

    std::size_t* rowIndices = new std::size_t[4];
    rowIndices[0] = 0;
    rowIndices[1] = 2;
    rowIndices[2] = 1;
    rowIndices[3] = 2;

    float* values = new float[4];
    values[0] = 5;
    values[1] = 3;
    values[2] = 8;
    values[3] = 6;

    std::size_t nnz = 4;
    CSCCustomSparseMatrix<float> a(3, 3, colOffsets, rowIndices, values, nnz);

    std::size_t* colOffsets2 = new std::size_t[3];
    colOffsets2[0] = 0;
    colOffsets2[1] = 1;
    colOffsets2[2] = 3;

    std::size_t* rowIndices2 = new std::size_t[3];
    rowIndices2[0] = 1;
    rowIndices2[1] = 0;
    rowIndices2[2] = 2;

    float* values2 = new float[3];
    values2[0] = 4;
    values2[1] = 7;
    values2[2] = 9;

    std::size_t nnz2 = 3;
    CSCCustomSparseMatrix<float> b(3, 3, colOffsets2, rowIndices2, values2, nnz2);

    std::size_t* colOffsets3 = new std::size_t[4];
    colOffsets3[0] = 0;
    colOffsets3[1] = 1;
    colOffsets3[2] = 2;
    colOffsets3[3] = 4;

    std::size_t* rowIndices3 = new std::size_t[4];
    rowIndices3[0] = 0;
    rowIndices3[1] = 1;
    rowIndices3[2] = 0;
    rowIndices3[3] = 1;

    float* values3 = new float[4];
    values3[0] = 1;
    values3[1] = 2;
    values3[2] = 5;
    values3[3] = 3;

    std::size_t nnz3 = 4;
    CSCCustomSparseMatrix<float> c(3, 3, colOffsets3, rowIndices3, values3, nnz3);
}

TEST(debugger_tests, dense_vectors) {
    DenseVector<float> a = {1, 2, 3};
}

TEST(debugger_tests, dense_vector_views) {
    DenseVector<float> a = {1, 2, 3};

    DenseVectorView<DenseVector<float>> b(a, 2, 0);
}

TEST(debugger_tests, custom_dense_vectors) {
    float data[] = {1, 2, 3};
    CustomDenseVector<float> a(data, 3, 1);
}

TEST(debugger_tests, sparse_vectors) {
    CooSparseVector<float> a(5, {{1, 0}, {3, 2}, {5, 4}});
}

TEST(debugger_tests, sparse_vector_views) {
    CooSparseVector<float> a(5, {{1, 0}, {3, 2}, {5, 4}});

    CooSparseVectorView<float> b(a, 3, 1);
}

TEST(debugger_tests, custom_sparse_vectors) {
    float* values = new float[3];
    values[0] = 1;
    values[1] = 3;
    values[2] = 5;

    std::size_t* indices = new std::size_t[3];
    indices[0] = 0;
    indices[1] = 2;
    indices[2] = 4;

    std::size_t nnz = 3;
    CooCustomSparseVector<float> a(5, values, indices, nnz);
}
