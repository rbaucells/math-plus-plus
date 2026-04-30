#include "gtest/gtest.h"

#include "mathpp/math.h"

TEST(dense_matrix_multiplication_operator, given_f_dense_matrices_should_return_product) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}};
    const DenseMatrix<float> b = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    const DenseMatrix<float> expected = {{1124, 1312, 1500}, {2546, 2968, 3390}};
    // act
    const DenseMatrix<float> product = a * b * c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
}

TEST(dense_matrix_multiplication_operator, given_cf_dense_matrices_should_return_product) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, -6}}, {{7, 8}, {9, 10}, {0, 11}}, {{12, -13}, {14, 0}, {15, 16}}};
    const DenseMatrix<std::complex<float>> b = {{{3, 0}, {4, 17}, {4, -2}}, {{9, 0}, {2, 0}, {1, 0}}, {{0, 4}, {0, 12}, {0, 0}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 18}, {2, 17}, {3, 16}}, {{4, 15}, {5, 14}, {6, 13}}, {{8, 12}, {9, 11}, {10, 10}}};
    const DenseMatrix<std::complex<float>> expected = {{{-2297, 2338}, {-2019, 2390}, {-1741, 2442}}, {{-5359, -628}, {-5157, -204}, {-4955, 220}}, {{-3640, 4512}, {-3124, 4550}, {-2608, 4588}}};
    // act
    const DenseMatrix<std::complex<float>> product = a * b * c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
}

TEST(dense_matrix_multiplication_operator, given_f_and_cf_dense_matrices_should_return_product) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, -6}}, {{7, 8}, {9, 10}, {0, 11}}, {{12, -13}, {14, 0}, {15, 16}}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<std::complex<float>> c = {{{1, 18}, {2, 17}, {3, 16}}, {{4, 15}, {5, 14}, {6, 13}}, {{8, 12}, {9, 11}, {10, 10}}};
    const DenseMatrix<std::complex<float>> expected = {{{1884, 2199}, {1983, 1956}, {2082, 1713}}, {{-5877, 4764}, {-5238, 5049}, {-4599, 5334}}, {{-1503, 10731}, {-555, 10395}, {393, 10059}}};
    // act
    const DenseMatrix<std::complex<float>> product = a * b * c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
}

TEST(dense_matrix_multiplication, given_f_dense_matrices_should_return_product) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}};
    const DenseMatrix<float> b = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    const DenseMatrix<float> expected = {{1124, 1312, 1500}, {2546, 2968, 3390}};
    // act
    const DenseMatrix<float> product = multiply(a, multiply(b, c));
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
}

TEST(dense_matrix_multiplication, given_cf_dense_matrices_should_return_product) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, -6}}, {{7, 8}, {9, 10}, {0, 11}}, {{12, -13}, {14, 0}, {15, 16}}};
    const DenseMatrix<std::complex<float>> b = {{{3, 0}, {4, 17}, {4, -2}}, {{9, 0}, {2, 0}, {1, 0}}, {{0, 4}, {0, 12}, {0, 0}}};
    const DenseMatrix<std::complex<float>> c = {{{1, 18}, {2, 17}, {3, 16}}, {{4, 15}, {5, 14}, {6, 13}}, {{8, 12}, {9, 11}, {10, 10}}};
    const DenseMatrix<std::complex<float>> expected = {{{-2297, 2338}, {-2019, 2390}, {-1741, 2442}}, {{-5359, -628}, {-5157, -204}, {-4955, 220}}, {{-3640, 4512}, {-3124, 4550}, {-2608, 4588}}};
    // act
    const DenseMatrix<std::complex<float>> product = multiply(a, multiply(b, c));
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
}

TEST(dense_matrix_multiplication, given_f_and_cf_dense_matrices_should_return_product) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, -6}}, {{7, 8}, {9, 10}, {0, 11}}, {{12, -13}, {14, 0}, {15, 16}}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<std::complex<float>> c = {{{1, 18}, {2, 17}, {3, 16}}, {{4, 15}, {5, 14}, {6, 13}}, {{8, 12}, {9, 11}, {10, 10}}};
    const DenseMatrix<std::complex<float>> expected = {{{1884, 2199}, {1983, 1956}, {2082, 1713}}, {{-5877, 4764}, {-5238, 5049}, {-4599, 5334}}, {{-1503, 10731}, {-555, 10395}, {393, 10059}}};
    // act
    const DenseMatrix<std::complex<float>> product = multiply(a, multiply(b, c));
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
}
