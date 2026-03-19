#include "gtest/gtest.h"
#include "mathpp/math.h"

int main(int argc, char** argv) {
    DenseVector<int> e = {1, 2, 3, 4, 5};
    DenseVector<int>& f = e;
    DenseVector<int>* g = &e;

    DenseVectorView<int> h(e, 3, 1);
    DenseVectorView<int>& hh = h;
    DenseVectorView<int>* hhh = &h;

    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    CustomDenseVector<float> i(data, 3, 3);
    CustomDenseVector<float>& ii = i;
    CustomDenseVector<float>* iii = &i;

    SparseVector<float> j(5, {{2, 1}, {4, 3}, {5, 4}});
    SparseVector<float>& k = j;
    SparseVector<float>* l = &j;

    SparseVectorView<float> m(j, 3, 1);
    SparseVectorView<float>& mm = m;
    SparseVectorView<float>* mmm = &m;

    float* values = new float[2];
    values[0] = 1;
    values[1] = 3;
    int* indices = new int[2];
    indices[0] = 0;
    indices[1] = 2;
    int nnz = 2;

    CustomSparseVector<float> n(3, values, indices, nnz);
    CustomSparseVector<float>& nn = n;
    CustomSparseVector<float>* nnn = &n;

    nnn->set(1, 5);

    DenseMatrix<float> o = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float>& p = o;
    DenseMatrix<float>* q = &o;

    DenseMatrixView<float> r(o, 2, 2, 1, 1);
    DenseMatrixView<float>& s = r;
    DenseMatrixView<float>* t = &r;

    float values2[] = {1,2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    CustomDenseMatrix<float> u(values2, 3, 3, 4);
    CustomDenseMatrix<float>& v = u;
    CustomDenseMatrix<float>* w = &u;

    SparseMatrix<float> x(3,3, {{2, 1, 0}, {4, 0, 1}, {6, 2, 2}});
    SparseMatrix<float>& y = x;
    SparseMatrix<float>* z = &x;

    SparseMatrixView<float> xx(x, 2, 3, 0, 1);
    SparseMatrixView<float>& xxx = xx;
    SparseMatrixView<float>* xzx = &xx;

    int* colOffsets = new int[4];
    colOffsets[0] = 0;
    colOffsets[1] = 1;
    colOffsets[2] = 2;
    colOffsets[3] = 3;

    int* rowIndices = new int[3];
    rowIndices[0] = 0;
    rowIndices[1] = 1;
    rowIndices[2] = 2;

    float* values3 = new float[3];
    values3[0] = 2;
    values3[1] = 4;
    values3[2] = 6;

    int nnz3 = 3;

    CustomSparseMatrix<float> czx(3, 3, colOffsets, rowIndices, values3, nnz3);
    CustomSparseMatrix<float>& cfzx = czx;
    CustomSparseMatrix<float>* czfsdx = &czx;

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
