#include "gtest/gtest.h"

#include "mathpp/matrix.h"

TEST(equality_operator, given_f_sparse_matrices_should_return_true) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    const CSCSparseMatrix<float> b(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    const CSCSparseMatrix<float> c(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_sparse_matrices_should_return_false) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {3, 2, 1}, {9, 2, 2}});
    const CSCSparseMatrix<float> b(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    const CSCSparseMatrix<float> c(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_cf_sparse_matrices_should_return_true) {
    // arrange
    const CSCSparseMatrix<std::complex<float>> a(3, 3, {{{1, 2}, 0, 0}, {{7, 8}, 2, 1}, {{13, 14}, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> b(3, 3, {{{1, 2}, 0, 0}, {{7, 8}, 2, 1}, {{13, 14}, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> c(3, 3, {{{1, 2}, 0, 0}, {{7, 8}, 2, 1}, {{13, 14}, 2, 2}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_cf_sparse_matrices_should_return_false) {
    // arrange
    const CSCSparseMatrix<std::complex<float>> a(3, 3, {{{1, 2}, 0, 0}, {{7, 8}, 2, 1}, {{13, 14}, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> b(3, 3, {{{1, 2}, 0, 0}, {{7, 8}, 2, 1}, {{13, 14}, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> c(3, 3, {{{1, 2}, 0, 0}, {{7, 8}, 2, 1}, {{13, 15}, 2, 2}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_f_and_cf_sparse_matrices_should_return_true) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> b(3, 3, {{{1, 0}, 0, 0}, {{6, 0}, 2, 1}, {{9, 0}, 2, 2}});
    const CSCSparseMatrix<float> c(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_and_cf_sparse_matrices_should_return_false) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> b(3, 3, {{{1, 0}, 0, 0}, {{4, 0}, 2, 1}, {{9, 0}, 2, 2}});
    const CSCSparseMatrix<float> c(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_f_sparse_matrices_and_precision_should_return_true) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    const CSCSparseMatrix<float> b(3, 3, {{1, 0, 0}, {6.1f, 2, 1}, {9, 2, 2}});
    const CSCSparseMatrix<float> c(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_sparse_matrices_and_precision_should_return_false) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    const CSCSparseMatrix<float> b(3, 3, {{1, 0, 0}, {6.1f, 2, 1}, {9, 2, 2}});
    const CSCSparseMatrix<float> c(3, 3, {{1, 0, 0}, {5.9f, 2, 1}, {9, 2, 2}});
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_cf_sparse_matrices_and_precision_should_return_true) {
    // arrange
    const CSCSparseMatrix<std::complex<float>> a(3, 3, {{{1, 2}, 0, 0}, {{7, 8}, 2, 1}, {{13, 14}, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> b(3, 3, {{{1, 2}, 0, 0}, {{7, 8.1f}, 2, 1}, {{13, 14}, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> c(3, 3, {{{1, 2}, 0, 0}, {{7, 8}, 2, 1}, {{13, 14}, 2, 2}});
    // act
    const bool result = (a == b == c) + Precision(0.11f);
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_cf_sparse_matrices_and_precision_should_return_false) {
    // arrange
    const CSCSparseMatrix<std::complex<float>> a(3, 3, {{{1, 2}, 0, 0}, {{7.1f, 8}, 2, 1}, {{13, 14}, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> b(3, 3, {{{1, 2}, 0, 0}, {{7, 8}, 2, 1}, {{13, 14}, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> c(3, 3, {{{0.9f, 2}, 0, 0}, {{7, 8}, 2, 1}, {{13, 14}, 2, 2}});
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_f_and_cf_sparse_matrices_and_precision_should_return_true) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {6, 2, 1}, {9.1f, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> b(3, 3, {{{1, 0}, 0, 0}, {{6, 0.1f}, 2, 1}, {{9, 0}, 2, 2}});
    const CSCSparseMatrix<float> c(3, 3, {{1, 0, 0}, {6, 2, 1}, {9, 2, 2}});
    // act
    const bool result = (a == b == c) + Precision(0.11f);
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_and_cf_sparse_matrices_and_precision_should_return_false) {
    // arrange
    const CSCSparseMatrix<float> a(3, 3, {{1, 0, 0}, {6, 2, 1}, {9.1f, 2, 2}});
    const CSCSparseMatrix<std::complex<float>> b(3, 3, {{{1, 0}, 0, 0}, {{4, 0.1f}, 2, 1}, {{9, 0}, 2, 2}});
    const CSCSparseMatrix<float> c(3, 3, {{1, 0, 0}, {6, 2, 1}, {8.9f, 2, 2}});
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}
