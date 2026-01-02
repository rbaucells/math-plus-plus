#include <gtest/gtest.h>
#include "math++/math.h"

TEST(MatrixChecks, row_echelon_square_real)
{
    // arrange
    constexpr Matrix<3, 3> a = {{4, 3, 1}, {0, 0, 5}, {0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_square_real_zero_row)
{
    // arrange
    constexpr Matrix<3, 3> a = {{4, 3, 1}, {0, 0, 0}, {0, 0, 5}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_square_real_pivots)
{
    // arrange
    constexpr Matrix<3, 3> a = {{0, 0, 1}, {5, 4, 0}, {0, 0, 5}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_square_real_require_ones)
{
    // arrange
    constexpr Matrix<3, 3> a = {{1, 2, 3}, {0, 1, 4}, {0, 0, 1}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_square_real_require_ones)
{
    // arrange
    constexpr Matrix<3, 3> a = {{2, 2, 3}, {0, 3, 4}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, row_echelon_wide_real)
{
    // arrange
    constexpr Matrix<4, 5> a = {{1, 6, 7, 7, 1}, {0, 9, 2, 1, 1}, {0, 0, 0, 2, 2}, {0, 0, 0, 0, 1}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_wide_real_zero_row)
{
    // arrange
    constexpr Matrix<4, 5> a = {{1, 6, 7, 7, 1}, {0, 9, 2, 1, 1}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_wide_real_pivots)
{
    // arrange
    constexpr Matrix<4, 5> a = {{1, 6, 7, 7, 1}, {0, 0, 2, 1, 1}, {4, 2, 0, 0, 0}, {0, 0, 0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_wide_real_require_ones)
{
    // arrange
    constexpr Matrix<4, 5> a = {{1, 2, 0, 0, 5}, {0, 1, 3, 0, 0}, {0, 0, 1, 4, 0}, {0, 0, 0, 0, 1}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_wide_real_require_ones)
{
    // arrange
    constexpr Matrix<4, 5> a = {{2, 1, 0, 0, 0}, {0, 1, 3, 0, 0}, {0, 0, 1, 0, 4}, {0, 0, 0, 0, 0}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, row_echelon_tall_real)
{
    // arrange
    constexpr Matrix<3, 2> a = {{3, 4}, {0, 1}, {0, 0}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_tall_real_zero_row)
{
    // arrange
    constexpr Matrix<3, 2> a = {{3, 4}, {0, 0}, {1, 2}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_tall_real_pivots)
{
    // arrange
    constexpr Matrix<3, 2> a = {{0, 4}, {0, 3}, {0, 0}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_tall_real_require_ones)
{
    // arrange
    constexpr Matrix<3, 2> a = {{1, 2}, {0, 1}, {0, 0}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_tall_real_require_ones)
{
    // arrange
    constexpr Matrix<3, 2> a = {{3, 2}, {0, 1}, {0, 0}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, row_echelon_square_complex)
{
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, -2}, {2, 2}, {0, 1}}, {{0, 0}, {0, 0}, {5, 5}}, {{0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_square_complex_zero_row)
{
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, 2}, {3, 1}, {1, 0.5f}}, {{0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {5, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_square_complex_pivots)
{
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{0, 0}, {0, 0}, {1, 1}}, {{5, 3}, {4, 0}, {0, 0}}, {{0, 0}, {0, 0}, {2, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_square_complex_require_ones)
{
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 0}, {2, 0}, {3, 0}}, {{0, 0}, {1, 0}, {4, 1}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_square_complex_require_ones)
{
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{2, 0}, {1, 0}, {0, 0}}, {{0, 0}, {1, 0}, {3, 0}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, row_echelon_wide_complex)
{
    // arrange
    constexpr Matrix<4, 5, std::complex<float>> a = {{{1, 0}, {2, 1}, {0, 0}, {4, 0}, {0, 0}}, {{0, 0}, {0, 0}, {3, 2}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {5, 1}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_wide_complex_zero_row)
{
    // arrange
    constexpr Matrix<4, 5, std::complex<float>> a = {{{1, 0}, {0, 0}, {2, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {3, 1}, {0, 0}, {0, 0}, {4, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_wide_complex_pivots)
{
    // arrange
    constexpr Matrix<4, 5, std::complex<float>> a = {{{0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {2, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {3, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_wide_complex_require_ones)
{
    // arrange
    constexpr Matrix<4, 5, std::complex<float>> a = {{{1, 0}, {2, 0}, {0, 0}, {0, 0}, {1, 1}}, {{0, 0}, {1, 0}, {3, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}, {2, 1}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_wide_complex_require_ones)
{
    // arrange
    constexpr Matrix<4, 5, std::complex<float>> a = {{{3, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {1, 0}, {2, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}, {0, 0}, {4, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, row_echelon_tall_complex)
{
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{3, 0}, {1, 2}}, {{0, 0}, {4, 1}}, {{0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_tall_complex_zero_row)
{
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{2, 1}, {3, 0}}, {{0, 0}, {0, 0}}, {{0, 0}, {5, 2}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_tall_complex_pivots)
{
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{0, 0}, {1, 0}}, {{2, 0}, {0, 0}}, {{0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_tall_complex_require_ones)
{
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{1, 0}, {2, 1}}, {{0, 0}, {1, 0}}, {{0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon(true));
}

TEST(MatrixChecks, not_row_echelon_tall_complex_require_ones)
{
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{2, 0}, {1, 0}}, {{0, 0}, {1, 0}}, {{0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon(true));
}

TEST(MatrixChecks, reduced_row_echelon_square_real)
{
    // arrange
    constexpr Matrix<3, 3> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_real_one)
{
    // arrange
    constexpr Matrix<3, 3> a = {{4, 0, 0}, {0, 6, 0}, {0, 0, 5}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_real_pivots)
{
    // arrange
    constexpr Matrix<3, 3> a = {{1, 0, 0}, {0, 0, 1}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_real_columns)
{
    // arrange
    constexpr Matrix<3, 3> a = {{1, 4, 0}, {2, 1, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_real_zero_row)
{
    // arrange
    constexpr Matrix<3, 3> a = {{1, 0, 0}, {0, 0, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_tall_real)
{
    // arrange
    constexpr Matrix<4, 3> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_real_one)
{
    // arrange
    constexpr Matrix<4, 3> a = {{4, 0, 0}, {0, 6, 0}, {0, 0, 5}, {0, 0, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_real_pivots)
{
    // arrange
    constexpr Matrix<4, 3> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_real_columns)
{
    // arrange
    constexpr Matrix<4, 3> a = {{1, 4, 0}, {2, 1, 0}, {0, 0, 1}, {0, 7, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_real_zero_row)
{
    // arrange
    constexpr Matrix<4, 3> a = {{1, 0, 0}, {0, 0, 0}, {0, 0, 1}, {0, 0, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_wide_real)
{
    // arrange
    constexpr Matrix<3, 4> a = {{1, 0, 0, 0}, {0, 1, 0, 1}, {0, 0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_real_one)
{
    // arrange
    constexpr Matrix<3, 4> a = {{4, 0, 0, 0}, {0, 6, 0, 0}, {0, 0, 5, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_real_pivots)
{
    // arrange
    constexpr Matrix<3, 4> a = {{1, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_real_columns)
{
    // arrange
    constexpr Matrix<3, 4> a = {{1, 0, 2, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_real_zero_row)
{
    // arrange
    constexpr Matrix<3, 4> a = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_square_complex)
{
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_complex_one)
{
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, 0}, {0, 0}, {0, 0}}, {{0, 0}, {6, 0}, {0, 0}}, {{0, 0}, {0, 0}, {5, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_complex_pivots)
{
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_complex_columns)
{
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 0}, {4, 0}, {0, 0}}, {{2, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_complex_zero_row)
{
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_tall_complex)
{
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_complex_one)
{
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{4, 0}, {0, 0}, {0, 0}}, {{0, 0}, {6, 0}, {0, 0}}, {{0, 0}, {0, 0}, {5, 0}}, {{0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_complex_pivots)
{
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_complex_columns)
{
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{1, 0}, {4, 0}, {0, 0}}, {{2, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {7, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_complex_zero_row)
{
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_wide_complex)
{
    // arrange
    constexpr Matrix<3, 4, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {1, 0}, {0, 0}, {1, 0}}, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_complex_one)
{
    // arrange
    constexpr Matrix<3, 4, std::complex<float>> a = {{{4, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {6, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {5, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_complex_pivots)
{
    // arrange
    constexpr Matrix<3, 4, std::complex<float>> a = {{{1, 0}, {0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_complex_columns)
{
    // arrange
    constexpr Matrix<3, 4, std::complex<float>> a = {{{1, 0}, {0, 0}, {2, 0}, {0, 0}}, {{0, 0}, {1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_complex_zero_row)
{
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
