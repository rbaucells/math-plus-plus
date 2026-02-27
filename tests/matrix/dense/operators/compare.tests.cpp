#include "gtest/gtest.h"

#include "mathpp/math.h"

TEST(equality_operator, given_f_dense_matrices_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_dense_matrices_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {3, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_cf_dense_matrices_should_return_true) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> b = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_cf_dense_matrices_should_return_false) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> b = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {3, 4}, {5, 7}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}
