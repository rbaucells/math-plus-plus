#include "gtest/gtest.h"
#include "mathpp/math.h"

int main(int argc, char** argv) {
    DenseMatrix a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float>& b = a;
    DenseMatrix<int>* c = &a;
    const DenseMatrixView<int> d(a, 2, 2, 0, 0);

    DenseVector e = {1, 2, 3, 4, 5};

    e[2] = 10;

    const DenseVector<float>& f = e;
    DenseVector<int>* g = &e;
    const DenseVectorView<int> h(e, 3, 1);

    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    CustomDenseVector<float> i(nullptr, 3, 3);

    SparseVector<float> j(3);
    SparseVector<float>& k = j;
    SparseVector<float>* l = &j;

    j.set(1, 2);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
