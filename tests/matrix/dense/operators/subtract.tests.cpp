#include "gtest/gtest.h"

#include "mathpp/math.h"

TEST(dense_matrix_subtraction_operator, given_f_dense_matrices_should_return_difference) {
    // arrange
    const DenseMatrix<float> a = {{10, 20, 30}, {40, 50, 60}, {70, 80, 90}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<float> c = {{-5, 1, 7}, {-22, 56, 2}, {9, 4, 7}};
    const DenseMatrix<float> expected = {{13, 14, 15}, {61, -13, 27}, {53, 74, 76}};
    // act
    const DenseMatrix<float> diff = a - b - c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
}

TEST(dense_matrix_subtraction_operator, given_cf_dense_matrices_should_return_difference) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{10, 80}, {10, 20}, {20, 20}}, {{20, 20}, {20, 80}, {10, 10}}, {{15, 20}, {15, 15}, {30, 40}}};
    const DenseMatrix<std::complex<float>> b = {{{3, 67}, {2, 4}, {7, 7}}, {{9, 12}, {3, 64}, {3, 5}}, {{2, 2}, {0, 0}, {9, 2}}};
    const DenseMatrix<std::complex<float>> c = {{{3, 6}, {3, 3}, {1, 6}}, {{8, 4}, {4, 1}, {5, 1}}, {{0, 7}, {8, 5}, {3, 21}}};
    const DenseMatrix<std::complex<float>> expected = {{{4, 7}, {5, 13}, {12, 7}}, {{3, 4}, {13, 15}, {2, 4}}, {{13, 11}, {7, 10}, {18, 17}}};
    // act
    const DenseMatrix<std::complex<float>> diff = a - b - c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
}

TEST(dense_matrix_subtraction_operator, given_f_and_cf_dense_matrices_should_return_difference) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{10, 10}, {10, 10}, {10, 10}}, {{10, 10}, {10, 10}, {10, 10}}, {{10, 10}, {10, 10}, {10, 10}}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 3}, {8, 2, 7}};
    const DenseMatrix<std::complex<float>> c = {{{1, 1}, {1, 1}, {1, 1}}, {{1, 1}, {1, 1}, {1, 1}}, {{1, 1}, {1, 1}, {1, 1}}};
    const DenseMatrix<std::complex<float>> expected = {{{7, 9}, {4, 9}, {1, 9}}, {{8, 9}, {2, 9}, {6, 9}}, {{1, 9}, {7, 9}, {2, 9}}};
    // act
    const DenseMatrix<std::complex<float>> diff = a - b - c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
}

TEST(dense_matrix_subtraction, given_f_dense_matrices_should_return_difference) {
    // arrange
    const DenseMatrix<float> a = {{10, 20, 30}, {40, 50, 60}, {70, 80, 90}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<float> c = {{-5, 1, 7}, {-22, 56, 2}, {9, 4, 7}};
    const DenseMatrix<float> expected = {{13, 14, 15}, {61, -13, 27}, {53, 74, 76}};
    // act
    const DenseMatrix<float> diff = subtract(a, b, c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
}

TEST(dense_matrix_subtraction, given_cf_dense_matrices_should_return_difference) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{10, 80}, {10, 20}, {20, 20}}, {{20, 20}, {20, 80}, {10, 10}}, {{15, 20}, {15, 15}, {30, 40}}};
    const DenseMatrix<std::complex<float>> b = {{{3, 67}, {2, 4}, {7, 7}}, {{9, 12}, {3, 64}, {3, 5}}, {{2, 2}, {0, 0}, {9, 2}}};
    const DenseMatrix<std::complex<float>> c = {{{3, 6}, {3, 3}, {1, 6}}, {{8, 4}, {4, 1}, {5, 1}}, {{0, 7}, {8, 5}, {3, 21}}};
    const DenseMatrix<std::complex<float>> expected = {{{4, 7}, {5, 13}, {12, 7}}, {{3, 4}, {13, 15}, {2, 4}}, {{13, 11}, {7, 10}, {18, 17}}};
    // act
    const DenseMatrix<std::complex<float>> diff = subtract(a, b, c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
}

TEST(dense_matrix_subtraction, given_f_and_cf_dense_matrices_should_return_difference) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{10, 10}, {10, 10}, {10, 10}}, {{10, 10}, {10, 10}, {10, 10}}, {{10, 10}, {10, 10}, {10, 10}}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 3}, {8, 2, 7}};
    const DenseMatrix<std::complex<float>> c = {{{1, 1}, {1, 1}, {1, 1}}, {{1, 1}, {1, 1}, {1, 1}}, {{1, 1}, {1, 1}, {1, 1}}};
    const DenseMatrix<std::complex<float>> expected = {{{7, 9}, {4, 9}, {1, 9}}, {{8, 9}, {2, 9}, {6, 9}}, {{1, 9}, {7, 9}, {2, 9}}};
    // act
    const DenseMatrix<std::complex<float>> diff = subtract(a, b, c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
}
