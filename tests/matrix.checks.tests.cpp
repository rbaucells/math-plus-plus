#include <gtest/gtest.h>
#include "math++/math.h"

TEST(MatrixChecks, row_echelon_square_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 3, 1}, {0, 0, 5}, {0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_square_real_zero_row) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 3, 1}, {0, 0, 0}, {0, 0, 5}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_square_real_pivots) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 0, 1}, {5, 4, 0}, {0, 0, 5}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_square_real_require_ones) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 2, 3}, {0, 1, 4}, {0, 0, 1}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_square_real_require_ones) {
    // arrange
    constexpr Matrix<3, 3> a = {{2, 2, 3}, {0, 3, 4}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, row_echelon_wide_real) {
    // arrange
    constexpr Matrix<4, 5> a = {{1, 6, 7, 7, 1}, {0, 9, 2, 1, 1}, {0, 0, 0, 2, 2}, {0, 0, 0, 0, 1}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_wide_real_zero_row) {
    // arrange
    constexpr Matrix<4, 5> a = {{1, 6, 7, 7, 1}, {0, 9, 2, 1, 1}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_wide_real_pivots) {
    // arrange
    constexpr Matrix<4, 5> a = {{1, 6, 7, 7, 1}, {0, 0, 2, 1, 1}, {4, 2, 0, 0, 0}, {0, 0, 0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_wide_real_require_ones) {
    // arrange
    constexpr Matrix<4, 5> a = {{1, 2, 0, 0, 5}, {0, 1, 3, 0, 0}, {0, 0, 1, 4, 0}, {0, 0, 0, 0, 1}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_wide_real_require_ones) {
    // arrange
    constexpr Matrix<4, 5> a = {{2, 1, 0, 0, 0}, {0, 1, 3, 0, 0}, {0, 0, 1, 0, 4}, {0, 0, 0, 0, 0}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, row_echelon_tall_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{3, 4}, {0, 1}, {0, 0}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_tall_real_zero_row) {
    // arrange
    constexpr Matrix<3, 2> a = {{3, 4}, {0, 0}, {1, 2}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_tall_real_pivots) {
    // arrange
    constexpr Matrix<3, 2> a = {{0, 4}, {0, 3}, {0, 0}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_tall_real_require_ones) {
    // arrange
    constexpr Matrix<3, 2> a = {{1, 2}, {0, 1}, {0, 0}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_tall_real_require_ones) {
    // arrange
    constexpr Matrix<3, 2> a = {{3, 2}, {0, 1}, {0, 0}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, row_echelon_square_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, -2}, {2, 2}, {0, 1}}, {{0, 0}, {0, 0}, {5, 5}}, {{0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_square_complex_zero_row) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, 2}, {3, 1}, {1, 0.5f}}, {{0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {5, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_square_complex_pivots) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{0, 0}, {0, 0}, {1, 1}}, {{5, 3}, {4, 0}, {0, 0}}, {{0, 0}, {0, 0}, {2, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_square_complex_require_ones) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 0}, {2, 0}, {3, 0}}, {{0, 0}, {1, 0}, {4, 1}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_square_complex_require_ones) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{2, 0}, {1, 0}, {0, 0}}, {{0, 0}, {1, 0}, {3, 0}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, row_echelon_wide_complex) {
    // arrange
    constexpr Matrix<4, 5, std::complex<float>> a = {{{1, 0}, {2, 1}, {0, 0}, {4, 0}, {0, 0}}, {{0, 0}, {0, 0}, {3, 2}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {5, 1}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_wide_complex_zero_row) {
    // arrange
    constexpr Matrix<4, 5, std::complex<float>> a = {{{1, 0}, {0, 0}, {2, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {3, 1}, {0, 0}, {0, 0}, {4, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_wide_complex_pivots) {
    // arrange
    constexpr Matrix<4, 5, std::complex<float>> a = {{{0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {2, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {3, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_wide_complex_require_ones) {
    // arrange
    constexpr Matrix<4, 5, std::complex<float>> a = {{{1, 0}, {2, 0}, {0, 0}, {0, 0}, {1, 1}}, {{0, 0}, {1, 0}, {3, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}, {2, 1}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_wide_complex_require_ones) {
    // arrange
    constexpr Matrix<4, 5, std::complex<float>> a = {{{3, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {1, 0}, {2, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}, {0, 0}, {4, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, row_echelon_tall_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{3, 0}, {1, 2}}, {{0, 0}, {4, 1}}, {{0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_tall_complex_zero_row) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{2, 1}, {3, 0}}, {{0, 0}, {0, 0}}, {{0, 0}, {5, 2}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_tall_complex_pivots) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{0, 0}, {1, 0}}, {{2, 0}, {0, 0}}, {{0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_tall_complex_require_ones) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{1, 0}, {2, 1}}, {{0, 0}, {1, 0}}, {{0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_tall_complex_require_ones) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{2, 0}, {1, 0}}, {{0, 0}, {1, 0}}, {{0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, reduced_row_echelon_square_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_real_one) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 0, 0}, {0, 6, 0}, {0, 0, 5}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_real_pivots) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 0, 0}, {0, 0, 1}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_real_columns) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 4, 0}, {2, 1, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_real_zero_row) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 0, 0}, {0, 0, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_tall_real) {
    // arrange
    constexpr Matrix<4, 3> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_real_one) {
    // arrange
    constexpr Matrix<4, 3> a = {{4, 0, 0}, {0, 6, 0}, {0, 0, 5}, {0, 0, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_real_pivots) {
    // arrange
    constexpr Matrix<4, 3> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_real_columns) {
    // arrange
    constexpr Matrix<4, 3> a = {{1, 4, 0}, {2, 1, 0}, {0, 0, 1}, {0, 7, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_real_zero_row) {
    // arrange
    constexpr Matrix<4, 3> a = {{1, 0, 0}, {0, 0, 0}, {0, 0, 1}, {0, 0, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_wide_real) {
    // arrange
    constexpr Matrix<3, 4> a = {{1, 0, 0, 0}, {0, 1, 0, 1}, {0, 0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_real_one) {
    // arrange
    constexpr Matrix<3, 4> a = {{4, 0, 0, 0}, {0, 6, 0, 0}, {0, 0, 5, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_real_pivots) {
    // arrange
    constexpr Matrix<3, 4> a = {{1, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_real_columns) {
    // arrange
    constexpr Matrix<3, 4> a = {{1, 0, 2, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_real_zero_row) {
    // arrange
    constexpr Matrix<3, 4> a = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_square_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_complex_one) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, 0}, {0, 0}, {0, 0}}, {{0, 0}, {6, 0}, {0, 0}}, {{0, 0}, {0, 0}, {5, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_complex_pivots) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_complex_columns) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 0}, {4, 0}, {0, 0}}, {{2, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_complex_zero_row) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_tall_complex) {
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_complex_one) {
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{4, 0}, {0, 0}, {0, 0}}, {{0, 0}, {6, 0}, {0, 0}}, {{0, 0}, {0, 0}, {5, 0}}, {{0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_complex_pivots) {
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_complex_columns) {
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{1, 0}, {4, 0}, {0, 0}}, {{2, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {7, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_complex_zero_row) {
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_wide_complex) {
    // arrange
    constexpr Matrix<3, 4, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {1, 0}, {0, 0}, {1, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_complex_one) {
    // arrange
    constexpr Matrix<3, 4, std::complex<float>> a = {{{4, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {6, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {5, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_complex_pivots) {
    // arrange
    constexpr Matrix<3, 4, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_complex_columns) {
    // arrange
    constexpr Matrix<3, 4, std::complex<float>> a = {{{1, 0}, {0, 0}, {2, 0}, {0, 0}}, {{0, 0}, {1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_complex_zero_row) {
    // arrange
    constexpr Matrix<3, 4, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}


TEST(MatrixChecks, positive_defnite_real_sylvesters) {
    // arrange
    constexpr Matrix<2, 2> m = {{4, -2}, {3, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::sylvester));
}

TEST(MatrixChecks, not_positive_defnite_real_sylvesters) {
    // arrange
    constexpr Matrix<2, 2> m = {{-2, 1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::sylvester));
}

TEST(MatrixChecks, positive_defnite_real_ldl) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, 1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::ldl));
}

TEST(MatrixChecks, not_positive_defnite_real_ldl) {
    // arrange
    constexpr Matrix<2, 2> m = {{-2, 1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::ldl));
}

TEST(MatrixChecks, positive_defnite_real_cholesky) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, 1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::cholesky));
}

TEST(MatrixChecks, not_positive_defnite_real_cholesky) {
    // arrange
    constexpr Matrix<2, 2> m = {{-2, 1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::cholesky));
}

TEST(MatrixChecks, positive_defnite_real_pivots) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, 1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::pivots));
}

TEST(MatrixChecks, not_positive_defnite_real_pivots) {
    // arrange
    constexpr Matrix<2, 2> m = {{-2, 1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::pivots));
}

TEST(MatrixChecks, positive_defnite_real_sylvesters_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::sylvester_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_real_sylvesters_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::sylvester_non_symmetric));
}

TEST(MatrixChecks, positive_defnite_real_ldl_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::ldl_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_real_ldl_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::ldl_non_symmetric));
}

TEST(MatrixChecks, positive_defnite_real_cholesky_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::cholesky_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_real_cholesky_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::cholesky_non_symmetric));
}

TEST(MatrixChecks, positive_defnite_real_pivots_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::pivots_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_real_pivots_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::pivots_non_symmetric));
}

TEST(MatrixChecks, positive_defnite_complex_sylvesters) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, -1}, {4, 0}}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::sylvester));
}

TEST(MatrixChecks, not_positive_defnite_complex_sylvesters) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 0}, {2, 1}}, {{2, -1}, {3, 0}}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::sylvester));
}

TEST(MatrixChecks, positive_defnite_complex_ldl) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, -1}, {4, 0}}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::ldl));
}

TEST(MatrixChecks, not_positive_defnite_complex_ldl) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 0}, {2, 1}}, {{2, -1}, {3, 0}}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::ldl));
}

TEST(MatrixChecks, positive_defnite_complex_cholesky) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, -1}, {4, 0}}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::cholesky));
}

TEST(MatrixChecks, not_positive_defnite_complex_cholesky) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 0}, {2, 1}}, {{2, -1}, {3, 0}}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::cholesky));
}

TEST(MatrixChecks, positive_defnite_complex_pivots) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, -1}, {4, 0}}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::pivots));
}

TEST(MatrixChecks, not_positive_defnite_complex_pivots) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 0}, {2, 1}}, {{2, -1}, {3, 0}}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::pivots));
}

TEST(MatrixChecks, positive_defnite_complex_sylvesters_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, 1}, {4, 0}}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::sylvester_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_complex_sylvesters_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, 1}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::sylvester_non_symmetric));
}

TEST(MatrixChecks, positive_defnite_complex_ldl_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, 1}, {4, 0}}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::ldl_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_complex_ldl_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, 1}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::ldl_non_symmetric));
}

TEST(MatrixChecks, positive_defnite_complex_cholesky_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, 1}, {4, 0}}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::cholesky_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_complex_cholesky_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, 1}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::cholesky_non_symmetric));
}

TEST(MatrixChecks, positive_defnite_complex_pivots_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, 1}, {4, 0}}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::pivots_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_complex_pivots_non_symmetric) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {2, 1}}, {{2, 1}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2, std::complex<float>>::PositiveDefiniteAlgorithm::pivots_non_symmetric));
}




TEST(MatrixChecks, symmetrical_real) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, 2}, {2, 3}};
    // act / assert
    ASSERT_TRUE(m.isSymmetrical());
}

TEST(MatrixChecks, not_symmetrical_real) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, 0}, {2, 3}};
    // act / assert
    ASSERT_FALSE(m.isSymmetrical());
}

TEST(MatrixChecks, skew_symmetrical_real) {
    // arrange
    constexpr Matrix<2, 2> m = {{0, -2}, {2, 0}};
    // act / assert
    ASSERT_TRUE(m.isSkewSymmetrical());
}

TEST(MatrixChecks, not_skew_symmetrical_real) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, -2}, {2, 0}};
    // act / assert
    ASSERT_FALSE(m.isSkewSymmetrical());
}

TEST(MatrixChecks, hermitian_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 0}, {2, -1}}, {{2, 1}, {3, 0}}};
    // act / assert
    ASSERT_TRUE(m.isHermitian());
}

TEST(MatrixChecks, not_hermitian_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 0}, {2, 0}}, {{2, 1}, {3, 0}}};
    // act / assert
    ASSERT_FALSE(m.isHermitian());
}

TEST(MatrixChecks, skew_hermitian_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{0, 0}, {0, 1}}, {{0, 1}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(m.isSkewHermitian());
}

TEST(MatrixChecks, not_skew_hermitian_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{2, 0}, {0, 1}}, {{0, 1}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(m.isSkewHermitian());
}

// is unitary
TEST(MatrixChecks, unitary) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{M_SQRT1_2, 0}, {M_SQRT1_2, 0}}, {{M_SQRT1_2, 0}, {-M_SQRT1_2, 0}}};
    // act / assert
    ASSERT_TRUE(m.isUnitary());
}

// not unitary
TEST(MatrixChecks, not_unitary) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 0}, {2, 0}}, {{3, 0}, {4, 0}}};
    // act / assert
    ASSERT_FALSE(m.isUnitary());
}

// is special unitary
TEST(MatrixChecks, special_unitary) {
    // arrange
    const Matrix<3, 3, std::complex<float>> m ={{
        {{-0.89437066f, 0.01997656f}, {0.0354747f, 0.08419308f}, {0.2191827f, 0.37856845f}},
        {{-0.10881489f, 0.19099076f}, {-0.94075669f, 0.01870152f}, {-0.2550478f, -0.03549051f}},
        {{0.20721771f, -0.32930948f}, {-0.32496967f, 0.0259787f}, {0.86095186f, 0.03313305f}}
    }};
    // act / assert
    ASSERT_TRUE(m.isSpecialUnitary());
}

// not special unitary because its determinant isnt 1
TEST(MatrixChecks, not_special_unitary_det) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{ {0, 1}, {1, 0} }, { {1, 0}, {0, 1} }};
    // act / assert
    ASSERT_FALSE(m.isSpecialUnitary());
}

// not special unitary because it isnt unitary
TEST(MatrixChecks, not_special_unitary_not_unitary) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{ {1, 0}, {2, 0} }, { {3, 0}, {4, 0} }};
    // act / assert
    ASSERT_FALSE(m.isSpecialUnitary());
}

// is orthogonal
TEST(MatrixChecks, orthogonal) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, 0}, {0, 1}};
    // act / assert
    ASSERT_TRUE(m.isOrthogonal());
}

// not orthogonal
TEST(MatrixChecks, not_orthogonal) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, 2}, {0, 1}};
    // act / assert
    ASSERT_FALSE(m.isOrthogonal());
}

// is special orthogonal
TEST(MatrixChecks, special_orthogonal) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, 0}, {0, 1}};
    // act / assert
    ASSERT_TRUE(m.isSpecialOrthogonal());
}

// not special orthogonal because its det isnt 1
TEST(MatrixChecks, not_special_orthogonal_det) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, 0}, {0, -1}};
    // act / assert
    ASSERT_FALSE(m.isSpecialOrthogonal());
}

// not special orthogonal because it isnt orthogonal
TEST(MatrixChecks, not_special_orthogonal_not_orthogonal) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, 0}, {2, 1}};
    // act / assert
    ASSERT_FALSE(m.isSpecialOrthogonal());
}

TEST(MatrixChecks, semi_orthogonal_wide) {
    // arrange
    constexpr Matrix<2, 3> m = {{1, 0, 0}, {0, 1, 0}};
    // act / assert
    ASSERT_TRUE(m.isSemiOrthogonal());
}

TEST(MatrixChecks, not_semi_orthogonal_wide) {
    // arrange
    constexpr Matrix<2, 3> m = {{1, 1, 0}, {0, 1, 0}};
    // act / assert
    ASSERT_FALSE(m.isSemiOrthogonal());
}

TEST(MatrixChecks, semi_orthogonal_tall) {
    // arrange
    constexpr Matrix<3, 2> m = {{1, 0}, {0, 1}, {0, 0}};
    // act / assert
    ASSERT_TRUE(m.isSemiOrthogonal());
}

TEST(MatrixChecks, not_semi_orthogonal_tall) {
    // arrange
    constexpr Matrix<3, 2> m = {{1, 0}, {1, 1}, {0, 0}};
    // act / assert
    ASSERT_FALSE(m.isSemiOrthogonal());
}

TEST(MatrixChecks, upper_trianglular_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 4, 3}, {0, 2, 5}, {0, 0, 3}};
    // act / assert
    ASSERT_TRUE(m.isUpperTriangular());
}

TEST(MatrixChecks, not_upper_trianglular_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 2, 3}, {0, 2, 4}, {1, 0, 3}};
    // act / assert
    ASSERT_FALSE(m.isUpperTriangular());
}

TEST(MatrixChecks, upper_trianglular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,1}, {0,0} }, { {0,0}, {2,0}, {0,1} }, { {0,0}, {0,0}, {3,0} }};
    // act / assert
    ASSERT_TRUE(m.isUpperTriangular());
}

TEST(MatrixChecks, not_upper_trianglular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {2,1}, {0,0} }, { {0.5,0}, {2,0}, {0,1} }, { {0,0}, {0,0}, {3,0} }};
    // act / assert
    ASSERT_FALSE(m.isUpperTriangular());
}

TEST(MatrixChecks, lower_trianglular_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {2, 3, 0}, {4, 5, 6}};
    // act / assert
    ASSERT_TRUE(m.isLowerTriangular());
}

TEST(MatrixChecks, not_lower_trianglular_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {2, 3, 1}, {4, 5, 6}};
    // act / assert
    ASSERT_FALSE(m.isLowerTriangular());
}

TEST(MatrixChecks, lower_trianglular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {0,0} }, { {2,1}, {3,0}, {0,0} }, { {4,0}, {5,1}, {6,0} }};
    // act / assert
    ASSERT_TRUE(m.isLowerTriangular());
}

TEST(MatrixChecks, not_lower_trianglular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {0,0} }, { {2,0}, {3,1}, {1,0} }, { {4,0}, {5,0}, {6,0} }};
    // act / assert
    ASSERT_FALSE(m.isLowerTriangular());
}

TEST(MatrixChecks, diagonal_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    // act / assert
    ASSERT_TRUE(m.isDiagonal());
}

TEST(MatrixChecks, not_diagonal_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {0, 2, 1}, {0, 0, 3}};
    // act / assert
    ASSERT_FALSE(m.isDiagonal());
}

TEST(MatrixChecks, diagonal_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {0,0} }, { {0,0}, {2,1}, {0,0} }, { {0,0}, {0,0}, {3,0} }};
    // act / assert
    ASSERT_TRUE(m.isDiagonal());
}

TEST(MatrixChecks, not_diagonal_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {0,0} }, { {0,0}, {2,0}, {1,1} }, { {0,0}, {0,0}, {3,0} }};
    // act / assert
    ASSERT_FALSE(m.isDiagonal());
}

TEST(MatrixChecks, upper_unitriangular_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 2, 3}, {0, 1, 4}, {0, 0, 1}};
    // act / assert
    ASSERT_TRUE(m.isUpperUnitriangular());
}

TEST(MatrixChecks, not_upper_unitriangular_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{2, 2, 3}, {0, 1, 4}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(m.isUpperUnitriangular());
}


TEST(MatrixChecks, upper_unitriangular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {2,1}, {3,0} }, { {0,0}, {1,0}, {4,1} }, { {0,0}, {0,0}, {1,0} }};
    // act / assert
    ASSERT_TRUE(m.isUpperUnitriangular());
}

TEST(MatrixChecks, not_upper_unitriangular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {2,0}, {2,1}, {3,0} }, { {0,0}, {1,0}, {4,1} }, { {0,0}, {0,0}, {1,0} }};
    // act / assert
    ASSERT_FALSE(m.isUpperUnitriangular());
}

TEST(MatrixChecks, lower_unitriangular_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_TRUE(m.isLowerUnitriangular());
}

TEST(MatrixChecks, not_lower_unitriangular_real) {
    // arrange: diagonal element not one
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {0, 2, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(m.isLowerUnitriangular());
}

TEST(MatrixChecks, lower_unitriangular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {0,0} }, { {0,0}, {1,0}, {0,0} }, { {0,0}, {0,0}, {1,0} }};
    // act / assert
    ASSERT_TRUE(m.isLowerUnitriangular());
}

TEST(MatrixChecks, not_lower_unitriangular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {0,0} }, { {0,0}, {2,0}, {0,0} }, { {0,0}, {0,0}, {1,0} }};
    // act / assert
    ASSERT_FALSE(m.isLowerUnitriangular());
}

TEST(MatrixChecks, strictly_upper_triangular_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{0, 1, 2}, {0, 0, 3}, {0, 0, 0}};
    // act / assert
    ASSERT_TRUE(m.isStrictlyUpperTriangular());
}

TEST(MatrixChecks, not_strictly_upper_triangular_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{0, 1, 2}, {0, 1, 3}, {0, 0, 0}};
    // act / assert
    ASSERT_FALSE(m.isStrictlyUpperTriangular());
}

TEST(MatrixChecks, strictly_upper_triangular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {0,0}, {1,1}, {2,0} }, { {0,0}, {0,0}, {3,1} }, { {0,0}, {0,0}, {0,0} }};
    // act / assert
    ASSERT_TRUE(m.isStrictlyUpperTriangular());
}

TEST(MatrixChecks, not_strictly_upper_triangular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {0,0}, {1,0}, {2,0} }, { {0,0}, {1,0}, {3,0} }, { {0,0}, {0,0}, {0,0} }};
    // act / assert
    ASSERT_FALSE(m.isStrictlyUpperTriangular());
}

TEST(MatrixChecks, strictly_lower_triangular_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{0, 0, 0}, {1, 0, 0}, {2, 3, 0}};
    // act / assert
    ASSERT_TRUE(m.isStrictlyLowerTriangular());
}

TEST(MatrixChecks, not_strictly_lower_triangular_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{0, 0, 0}, {1, 1, 0}, {2, 3, 0}};
    // act / assert
    ASSERT_FALSE(m.isStrictlyLowerTriangular());
}


TEST(MatrixChecks, strictly_lower_triangular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {0,0}, {0,0}, {0,0} }, { {1,1}, {0,0}, {0,0} }, { {2,0}, {3,1}, {0,0} }};
    // act / assert
    ASSERT_TRUE(m.isStrictlyLowerTriangular());
}

TEST(MatrixChecks, not_strictly_lower_triangular_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {0,0}, {0,0}, {0,0} }, { {1,0}, {1,0}, {0,0} }, { {2,0}, {3,0}, {0,0} }};
    // act / assert
    ASSERT_FALSE(m.isStrictlyLowerTriangular());
}

TEST(MatrixChecks, frobenius_matrix_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {0, 1, 0}, {0, 5, 1}};
    // act / assert
    ASSERT_TRUE(m.isFrobenius());
}

TEST(MatrixChecks, not_frobenius_matrix_real_two_nonzero_columns) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {0, 1, 0}, {5, 6, 1}};
    // act / assert
    ASSERT_FALSE(m.isFrobenius());
}

TEST(MatrixChecks, not_frobenius_matrix_real_non_one_pivot) {
    // arrange
    constexpr Matrix<3, 3> m = {{2, 0, 0}, {0, 1, 0}, {0, 6, 1}};
    // act / assert
    ASSERT_FALSE(m.isFrobenius());
}

TEST(MatrixChecks, not_frobenius_matrix_real_nonzero) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 4}, {0, 1, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(m.isFrobenius());
}

TEST(MatrixChecks, frobenius_matrix_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {0,0} }, { {0,0}, {1,0}, {0,0} }, { {0,5}, {0,0}, {1,0} }};
    // act / assert
    ASSERT_TRUE(m.isFrobenius());
}

TEST(MatrixChecks, not_frobenius_matrix_complex_two_nonzero_columns) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {0,0} }, { {0,0}, {1,0}, {0,0} }, { {5,0}, {6,0}, {1,0} }};
    // act / assert
    ASSERT_FALSE(m.isFrobenius());
}

TEST(MatrixChecks, not_frobenius_matrix_complex_non_one_pivot) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {2,0}, {0,0}, {0,0} }, { {0,0}, {1,0}, {0,0} }, { {0,6}, {0,0}, {1,0} }};
    // act / assert
    ASSERT_FALSE(m.isFrobenius());
}

TEST(MatrixChecks, not_frobenius_matrix_complex_nonzero) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {4,0} }, { {0,0}, {1,0}, {0,0} }, { {0,0}, {0,0}, {1,0} }};
    // act / assert
    ASSERT_FALSE(m.isFrobenius());
}

TEST(MatrixChecks, upper_hessenberg_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 6, 5}, {3, 1, 4}, {0, 2, 1}};
    // act / assert
    ASSERT_TRUE(m.isUpperHessenberg());
}

TEST(MatrixChecks, not_upper_hessenberg_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {0, 1, 0}, {2, 0, 1}};
    // act / assert
    ASSERT_FALSE(m.isUpperHessenberg());
}

TEST(MatrixChecks, upper_hessenberg_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {6,1}, {5,0} }, { {3,0}, {1,0}, {4,1} }, { {0,0}, {2,0}, {1,0} }};
    // act / assert
    ASSERT_TRUE(m.isUpperHessenberg());
}

TEST(MatrixChecks, not_upper_hessenberg_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {0,0} }, { {0,0}, {1,0}, {0,0} }, { {2,0}, {0,0}, {1,0} }};
    // act / assert
    ASSERT_FALSE(m.isUpperHessenberg());
}

TEST(MatrixChecks, unreduced_upper_hessenberg_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 2, 3}, {5, 1, 4}, {0, 6, 1}};
    // act / assert
    ASSERT_TRUE(m.isUnreducedUpperHessenberg());
}

TEST(MatrixChecks, not_unreduced_upper_hessenberg_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 2, 3}, {0, 1, 4}, {0, 6, 1}};
    // act / assert
    ASSERT_FALSE(m.isUnreducedUpperHessenberg());
}

TEST(MatrixChecks, unreduced_upper_hessenberg_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {2,0}, {3,0} }, { {5,0}, {1,0}, {4,0} }, { {0,0}, {6,0}, {1,0} }};
    // act / assert
    ASSERT_TRUE(m.isUnreducedUpperHessenberg());
}

TEST(MatrixChecks, not_unreduced_upper_hessenberg_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {2,0}, {3,0} }, { {0,0}, {1,0}, {4,0} }, { {0,0}, {6,0}, {1,0} }};
    // act / assert
    ASSERT_FALSE(m.isUnreducedUpperHessenberg());
}

TEST(MatrixChecks, lower_hessenberg_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 3, 0}, {6, 1, 2}, {5, 4, 1}};
    // act / assert
    ASSERT_TRUE(m.isLowerHessenberg());
}

TEST(MatrixChecks, not_lower_hessenberg_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 2}, {0, 1, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(m.isLowerHessenberg());
}

TEST(MatrixChecks, lower_hessenberg_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {3,0}, {0,0} }, { {6,0}, {1,0}, {2,1} }, { {5,0}, {4,0}, {1,0} }};
    // act / assert
    ASSERT_TRUE(m.isLowerHessenberg());
}

TEST(MatrixChecks, not_lower_hessenberg_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {2,0} }, { {0,0}, {1,0}, {0,0} }, { {0,0}, {0,0}, {1,0} }};
    // act / assert
    ASSERT_FALSE(m.isLowerHessenberg());
}

TEST(MatrixChecks, unreduced_lower_hessenberg_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 5, 0}, {2, 1, 6}, {3, 4, 1}};
    // act / assert
    ASSERT_TRUE(m.isUnreducedLowerHessenberg());
}

TEST(MatrixChecks, not_unreduced_lower_hessenberg_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 5, 0}, {4, 1, 0}, {3, 4, 1}};
    // act / assert
    ASSERT_FALSE(m.isUnreducedLowerHessenberg());
}

TEST(MatrixChecks, unreduced_lower_hessenberg_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {5,0}, {0,0} }, { {2,0}, {1,0}, {6,0} }, { {3,0}, {4,0}, {1,0} }};
    // act / assert
    ASSERT_TRUE(m.isUnreducedLowerHessenberg());
}

TEST(MatrixChecks, not_unreduced_lower_hessenberg_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {0,0} }, { {2,0}, {1,0}, {6,0} }, { {3,0}, {4,0}, {1,0} }};
    // act / assert
    ASSERT_FALSE(m.isUnreducedLowerHessenberg());
}

TEST(MatrixChecks, tridiagonal_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 2, 0}, {3, 4, 5}, {0, 6, 7}};
    // act / assert
    ASSERT_TRUE(m.isTridiagonal());
}

TEST(MatrixChecks, not_tridiagonal_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {0, 1, 0}, {1, 0, 1}};
    // act / assert
    ASSERT_FALSE(m.isTridiagonal());
}

TEST(MatrixChecks, tridiagonal_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {2,0}, {0,0} }, { {3,0}, {4,0}, {5,0} }, { {0,0}, {6,0}, {7,0} }};
    // act / assert
    ASSERT_TRUE(m.isTridiagonal());
}

TEST(MatrixChecks, not_tridiagonal_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{ {1,0}, {0,0}, {0,0} }, { {0,0}, {1,0}, {0,0} }, { {1,0}, {0,0}, {1,0} }};
    // act / assert
    ASSERT_FALSE(m.isTridiagonal());
}

// isRowEchelonOfThis isnt implemented properly yet