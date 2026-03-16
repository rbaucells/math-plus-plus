#include "gtest/gtest.h"
#include "mathpp/math.h"

int main(int argc, char** argv) {
    DenseMatrix a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float>& b = a;
    DenseMatrix<int>* c = &a;
    const DenseMatrix<float>* d = &b;

    DenseVector e = {1, 2, 3, 4, 5};
    const DenseVector<float>& f = e;
    DenseVector<int>* g = &e;
    const DenseVector<float>* h = &f;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
