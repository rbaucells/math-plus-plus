#include "gtest/gtest.h"
#include "mathpp/math.h"

int main(int argc, char** argv) {
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9.345}};
    DenseMatrix<int> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> c = {{{1, 2}, 2, 3}, {4, 5, 6}, {7, 8, 9.345}};
    DenseMatrix<std::complex<int>> d = {{{1, 2}, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}