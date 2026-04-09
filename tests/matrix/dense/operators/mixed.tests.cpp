#include "gtest/gtest.h"
#include "mathpp/math.h"

TEST(dense_matrix_mixed_operator, given_f_dense_matrices_should_return_a_plus_b_minus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<float> c = {{-5, 1, 7}, {-22, 56, 2}, {9, 4, 7}};
    const DenseMatrix<float> expected = {{8, 6, 4}, {27, -44, 35}, {6, 6, 9}};
    // act
    const DenseMatrix<float> result = a + b - c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed_operator, given_f_dense_matrices_should_return_a_minus_b_plus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<float> c = {{-5, 1, 7}, {-22, 56, 2}, {9, 4, 7}};
    const DenseMatrix<float> expected = {{-6, -2, 2}, {-19, 54, -23}, {8, 10, 9}};
    // act
    const DenseMatrix<float> result = a - b + c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}