#include <gtest/gtest.h>

#include "../src/matrix/dense/matrix.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(refactor, DenseMatrix1) {
    const DenseMatrix<float> a = {{1, 2}, {3, 4}, {5, 6}};
    const DenseMatrix<float> b = {{6, 5}, {4, 3}, {2, 1}};
    const DenseMatrix<float> c = {{3, 4}, {2, 1}, {9, 9}};

    const DenseMatrix<float> d = a + b + c;
    // const DenseMatrix<float> e = Mathpp::add(a, b, c);
}