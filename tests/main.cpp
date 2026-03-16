#include "gtest/gtest.h"
#include "mathpp/math.h"

int main(int argc, char** argv) {
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9.345}};
    const DenseMatrix<float>& b = a;
    DenseMatrix<float>* c = &a;
    const DenseMatrix<float>* d = &b;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}