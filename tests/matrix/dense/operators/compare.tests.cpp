#include "gtest/gtest.h"

#include "mathpp/math.h"

TEST(a, b) {
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6.002f}, {7, 8, 9}};

    const bool result = (a == b == c) + Precision(0.001f);
    const bool result1 = a == b == c == Precision(0.001f);

    if (result || result1) {
        std::cout << "True";
    }
}