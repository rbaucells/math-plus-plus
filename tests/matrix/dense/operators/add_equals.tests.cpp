#include "gtest/gtest.h"

#include "mathpp/matrix/dense/operators.h"

TEST(dense_matrix_addition_assignment_operator, given_f_dense_matrices_should_add_assign) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<float> c = {{-5, 1, 7}, {-22, 56, 2}, {9, 4, 7}};
    const DenseMatrix<float> expected = {{-2, 8, 18}, {-17, 68, 39}, {24, 14, 23}};
    // act
    a += b + c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
}

TEST(dense_matrix_addition_assignment_operator, given_cf_dense_matrices_should_add_assign) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{2, 6}, {3, 6}, {0, 8}}, {{2, 1}, {3, 7}, {1, 0}}, {{4, 7}, {3, 3}, {5, 9}}};
    const DenseMatrix<std::complex<float>> b = {{{3, 67}, {2, 4}, {7, 7}}, {{9, 12}, {3, 64}, {3, 5}}, {{2, 2}, {0, 0}, {9, 2}}};
    const DenseMatrix<std::complex<float>> c = {{{3, 6}, {3, 3}, {1, 6}}, {{8, 4}, {4, 1}, {5, 1}}, {{0, 7}, {8, 5}, {3, 21}}};
    const DenseMatrix<std::complex<float>> expected = {{{8, 79}, {8, 13}, {8, 21}}, {{19, 17}, {10, 72}, {9, 6}}, {{6, 16}, {11, 8}, {17, 32}}};
    // act
    a += b + c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
}

TEST(dense_matrix_addition_assignment_operator, given_f_and_cf_dense_matrices_should_add_assign) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{2, 6}, {3, 6}, {0, 8}}, {{2, 1}, {3, 7}, {1, 0}}, {{4, 7}, {3, 3}, {5, 9}}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<std::complex<float>> c = {{{3, 6}, {3, 3}, {1, 6}}, {{8, 4}, {4, 1}, {5, 1}}, {{0, 7}, {8, 5}, {3, 21}}};
    const DenseMatrix<std::complex<float>> expected = {{{7, 12}, {11, 9}, {9, 14}}, {{11, 5}, {14, 8}, {37, 1}}, {{12, 14}, {13, 8}, {15, 30}}};
    // act
    a += b + c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
}

TEST(dense_matrix_addition_assignment, given_f_dense_matrices_should_add_assign) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<float> c = {{-5, 1, 7}, {-22, 56, 2}, {9, 4, 7}};
    const DenseMatrix<float> expected = {{-2, 8, 18}, {-17, 68, 39}, {24, 14, 23}};
    // act
    add_assign(a, b + c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
}

TEST(dense_matrix_addition_assignment, given_cf_dense_matrices_should_add_assign) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{2, 6}, {3, 6}, {0, 8}}, {{2, 1}, {3, 7}, {1, 0}}, {{4, 7}, {3, 3}, {5, 9}}};
    const DenseMatrix<std::complex<float>> b = {{{3, 67}, {2, 4}, {7, 7}}, {{9, 12}, {3, 64}, {3, 5}}, {{2, 2}, {0, 0}, {9, 2}}};
    const DenseMatrix<std::complex<float>> c = {{{3, 6}, {3, 3}, {1, 6}}, {{8, 4}, {4, 1}, {5, 1}}, {{0, 7}, {8, 5}, {3, 21}}};
    const DenseMatrix<std::complex<float>> expected = {{{8, 79}, {8, 13}, {8, 21}}, {{19, 17}, {10, 72}, {9, 6}}, {{6, 16}, {11, 8}, {17, 32}}};
    // act
    add_assign(a, b + c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
}

TEST(dense_matrix_addition_assignment, given_f_and_cf_dense_matrices_should_add_assign) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{2, 6}, {3, 6}, {0, 8}}, {{2, 1}, {3, 7}, {1, 0}}, {{4, 7}, {3, 3}, {5, 9}}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<std::complex<float>> c = {{{3, 6}, {3, 3}, {1, 6}}, {{8, 4}, {4, 1}, {5, 1}}, {{0, 7}, {8, 5}, {3, 21}}};
    const DenseMatrix<std::complex<float>> expected = {{{7, 12}, {11, 9}, {9, 14}}, {{11, 5}, {14, 8}, {37, 1}}, {{12, 14}, {13, 8}, {15, 30}}};
    // act
    add_assign(a, b + c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
}

TEST(dense_matrix_addition_assignment, given_rectangular_dense_matrices_should_add_assign) {
    // arrange
    DenseMatrix<float> a = {{1, 10}, {2, 20}, {3, 30}, {4, 40}};
    const DenseMatrix<float> b = {{5, 50}, {6, 60}, {7, 70}, {8, 80}};
    const DenseMatrix<float> expected = {{6, 60}, {8, 80}, {10, 100}, {12, 120}};
    // act
    add_assign(a, b);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
}
