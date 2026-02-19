#include "gtest/gtest.h"

#include "mathpp/math.h"

TEST(dense_matrix_equality_operator, given_f_dense_matrixes_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = a == b;
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality_operator, given_f_dense_matrixes_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{2, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = a == b;
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_compare, given_f_dense_matrixes_and_precision_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{2, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = compare
    // assert
    ASSERT_FALSE(result);
}