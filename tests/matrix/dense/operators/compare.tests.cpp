#include "gtest/gtest.h"

#include "mathpp/matrix.h"

TEST(dense_matrix_equality_operator, given_f_dense_matrices_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality_operator, given_f_dense_matrices_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {3, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality_operator, given_cf_dense_matrices_should_return_true) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> b = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality_operator, given_cf_dense_matrices_should_return_false) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> b = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {3, 4}, {5, 7}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality_operator, given_f_and_cf_dense_matrices_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<std::complex<float>> b = {{{1, 0}, {2, 0}, {3, 0}}, {{4, 0}, {5, 0}, {6, 0}}, {{7, 0}, {8, 0}, {9, 0}}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality_operator, given_f_and_cf_dense_matrices_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<std::complex<float>> b = {{{1, 0}, {2, 0}, {4, 0}}, {{4, 0}, {5, 0}, {6, 0}}, {{7, 0}, {8, 0}, {9, 0}}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality_operator, given_f_dense_matrices_and_precision_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2.1f, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality_operator, given_f_dense_matrices_and_precision_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {3, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2.1f, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 1.9f, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality_operator, given_cf_dense_matrices_and_precision_should_return_true) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> b = {{{1, 2}, {3, 4.1f}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality_operator, given_cf_dense_matrices_and_precision_should_return_false) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> b = {{{1, 2}, {3.1f, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {2.9f, 4}, {5, 7}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality_operator, given_f_and_cf_dense_matrices_and_precision_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3.1f}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<std::complex<float>> b = {{{1, 0}, {2, 0}, {3, 0}}, {{4, 0}, {5, 0}, {6, 0}}, {{7, 0}, {8, 0}, {9, 0}}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality_operator, given_f_and_cf_dense_matrices_and_precision_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3.1f}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<std::complex<float>> b = {{{1, 0}, {2, 0}, {4, 0}}, {{4, 0}, {5, 0}, {6, 0}}, {{7, 0}, {8, 0}, {9, 0}}};
    const DenseMatrix<float> c = {{1, 2, 2.9f}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality, given_f_dense_matrices_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = compare(a, b, c);
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality, given_f_dense_matrices_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {3, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = compare(a, b, c);
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality, given_cf_dense_matrices_should_return_true) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> b = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const bool result = compare(a, b, c);
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality, given_cf_dense_matrices_should_return_false) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> b = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {3, 4}, {5, 7}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const bool result = compare(a, b, c);
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality, given_f_and_cf_dense_matrices_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<std::complex<float>> b = {{{1, 0}, {2, 0}, {3, 0}}, {{4, 0}, {5, 0}, {6, 0}}, {{7, 0}, {8, 0}, {9, 0}}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = compare(a, b, c);
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality, given_f_and_cf_dense_matrices_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<std::complex<float>> b = {{{1, 0}, {2, 0}, {4, 0}}, {{4, 0}, {5, 0}, {6, 0}}, {{7, 0}, {8, 0}, {9, 0}}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = compare(a, b, c);
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality, given_f_dense_matrices_and_precision_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2.1f, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = compare(Precision(0.1f), a, b, c);
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality, given_f_dense_matrices_and_precision_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {3, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2.1f, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 1.9f, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = compare(Precision(0.1f), a, b, c);
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality, given_cf_dense_matrices_and_precision_should_return_true) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> b = {{{1, 2}, {3, 4.1f}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const bool result = compare(Precision(0.1f), a, b, c);
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality, given_cf_dense_matrices_and_precision_should_return_false) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> b = {{{1, 2}, {3.1f, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {2.9f, 4}, {5, 7}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const bool result = compare(Precision(0.1f), a, b, c);
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality, given_f_and_cf_dense_matrices_and_precision_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3.1f}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<std::complex<float>> b = {{{1, 0}, {2, 0}, {3, 0}}, {{4, 0}, {5, 0}, {6, 0}}, {{7, 0}, {8, 0}, {9, 0}}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = compare(Precision(0.1f), a, b, c);
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality, given_f_and_cf_dense_matrices_and_precision_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3.1f}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<std::complex<float>> b = {{{1, 0}, {2, 0}, {4, 0}}, {{4, 0}, {5, 0}, {6, 0}}, {{7, 0}, {8, 0}, {9, 0}}};
    const DenseMatrix<float> c = {{1, 2, 2.9f}, {4, 5, 6}, {7, 8, 9}};
    // act
    const bool result = compare(Precision(0.1f), a, b, c);
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality, given_rectangular_dense_matrices_should_compare_correctly) {
    // arrange
    const DenseMatrix<float> a = {{1, 10}, {2, 20}, {3, 30}, {4, 40}};
    const DenseMatrix<std::complex<float>> b = {{{1, 0}, {10, 0}}, {{2, 0}, {20, 0}}, {{3, 0}, {30, 0}}, {{4, 0}, {40, 0}}};
    const DenseMatrix<float> c = {{1, 10}, {2, 20}, {3, 30}, {4, 41}};
    // act
    const bool equal_result = compare(a, b);
    const bool precision_result = compare(Precision(0.5f), a, c);
    // assert
    ASSERT_TRUE(equal_result);
    ASSERT_FALSE(precision_result);
}
