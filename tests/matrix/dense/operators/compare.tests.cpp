#include "gtest/gtest.h"

#include "mathpp/math.h"

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
