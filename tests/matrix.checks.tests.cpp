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

TEST(MatrixChecks, positive_defnite_sylvesters)
{
    // arrange
    constexpr Matrix<2, 2> m = {{4, -2}, {3, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::sylvester));
}

TEST(MatrixChecks, not_positive_defnite_sylvesters)
{
    // arrange
    constexpr Matrix<2, 2> m = {{-2, 1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::sylvester));
}

TEST(MatrixChecks, positive_defnite_ldl)
{
    // arrange
    constexpr Matrix<2, 2> m = {{2, 1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::ldl));
}

TEST(MatrixChecks, not_positive_defnite_ldl)
{
    // arrange
    constexpr Matrix<2, 2> m = {{-2, 1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::ldl));
}

TEST(MatrixChecks, positive_defnite_cholesky)
{
    // arrange
    constexpr Matrix<2, 2> m = {{2, 1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::cholesky));
}

TEST(MatrixChecks, not_positive_defnite_cholesky)
{
    // arrange
    constexpr Matrix<2, 2> m = {{-2, 1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::cholesky));
}

TEST(MatrixChecks, positive_defnite_pivots)
{
    // arrange
    constexpr Matrix<2, 2> m = {{2, 1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::pivots));
}

TEST(MatrixChecks, not_positive_defnite_pivots)
{
    // arrange
    constexpr Matrix<2, 2> m = {{-2, 1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::pivots));
}

TEST(MatrixChecks, positive_defnite_sylvesters_non_symmetric)
{
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::sylvester_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_sylvesters_non_symmetric)
{
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::sylvester_non_symmetric));
}

TEST(MatrixChecks, positive_defnite_ldl_non_symmetric)
{
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::ldl_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_ldl_non_symmetric)
{
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::ldl_non_symmetric));
}

TEST(MatrixChecks, positive_defnite_cholesky_non_symmetric)
{
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::cholesky_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_cholesky_non_symmetric)
{
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::cholesky_non_symmetric));
}

TEST(MatrixChecks, positive_defnite_pivots_non_symmetric)
{
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, 3}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::pivots_non_symmetric));
}

TEST(MatrixChecks, not_positive_defnite_pivots_non_symmetric)
{
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {1, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite(Matrix<2, 2>::PositiveDefiniteAlgorithm::pivots_non_symmetric));
}

// symmetrical checks
TEST(MatrixChecks, symmetrical_real)
{
    // arrange
    constexpr Matrix<3, 3> m = {{1, 2, 3}, {2, 4, 5}, {3, 5, 6}};
    // act / assert
    ASSERT_TRUE(m.isSymmetrical());
}

TEST(MatrixChecks, not_symmetrical_real)
{
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {2, 1, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(m.isSymmetrical());
}

TEST(MatrixChecks, symmetrical_complex)
{
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 0}, {2, 1}}, {{2, 1}, {3, 0}}};
    // act / assert
    ASSERT_TRUE(m.isSymmetrical());
}

TEST(MatrixChecks, not_symmetrical_complex)
{
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 0}, {2, -1}}, {{2, 1}, {3, 0}}};
    // act / assert
    ASSERT_FALSE(m.isSymmetrical());
}

TEST(MatrixChecks, symmetrical_1x1)
{
    // arrange
    constexpr Matrix<1, 1> m = {{5}};
    // act / assert
    ASSERT_TRUE(m.isSymmetrical());
}

// isSkewSymmetrical tests
TEST(MatrixChecks, skew_symmetrical_real)
{
    // arrange
    constexpr Matrix<3, 3> m = {{0, -2, -3}, {2, 0, -5}, {3, 5, 0}};
    // act / assert
    ASSERT_TRUE(m.isSkewSymmetrical());
}

TEST(MatrixChecks, not_skew_symmetrical_real_offdiag)
{
    // arrange
    constexpr Matrix<3, 3> m = {{0, -2, -3}, {2, 0, -4}, {3, 5, 0}};
    // act / assert
    ASSERT_FALSE(m.isSkewSymmetrical());
}

TEST(MatrixChecks, skew_symmetrical_complex)
{
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{0, 0}, {-2, -1}}, {{2, 1}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(m.isSkewSymmetrical());
}

TEST(MatrixChecks, not_skew_symmetrical_complex_mismatch)
{
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{0, 0}, {-2, -2}}, {{2, 1}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(m.isSkewSymmetrical());
}

TEST(MatrixChecks, skew_symmetrical_1x1_zero)
{
    // arrange
    constexpr Matrix<1, 1> m = {{0}};
    // act / assert
    ASSERT_TRUE(m.isSkewSymmetrical());
}

TEST(MatrixChecks, not_skew_symmetrical_1x1_nonzero)
{
    // arrange
    constexpr Matrix<1, 1> m = {{1}};
    // act / assert
    ASSERT_FALSE(m.isSkewSymmetrical());
}

// isHermitian tests
TEST(MatrixChecks, hermitian_real)
{
    // arrange
    constexpr Matrix<3, 3> m = {{1, 2, 3}, {2, 4, 5}, {3, 5, 6}};
    // act / assert
    ASSERT_TRUE(m.isHermitian());
}

TEST(MatrixChecks, not_hermitian_real)
{
    // arrange
    constexpr Matrix<3, 3> m = {{1, 0, 0}, {2, 1, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(m.isHermitian());
}

TEST(MatrixChecks, hermitian_complex)
{
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 0}, {2, 1}}, {{2, -1}, {3, 0}}};
    // act / assert
    ASSERT_TRUE(m.isHermitian());
}

TEST(MatrixChecks, not_hermitian_complex)
{
    // arrange (symmetric but not hermitian)
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 0}, {2, 1}}, {{2, 1}, {3, 0}}};
    // act / assert
    ASSERT_FALSE(m.isHermitian());
}

TEST(MatrixChecks, hermitian_1x1_real)
{
    // arrange
    constexpr Matrix<1, 1, std::complex<float>> m = {{{2, 0}}};
    // act / assert
    ASSERT_TRUE(m.isHermitian());
}

TEST(MatrixChecks, not_hermitian_1x1_complex_imag)
{
    // arrange
    constexpr Matrix<1, 1, std::complex<float>> m = {{{0, 1}}};
    // act / assert
    ASSERT_FALSE(m.isHermitian());
}

// isSkewHermitian tests
TEST(MatrixChecks, skew_hermitian_real)
{
    // arrange (real skew-hermitian == skew-symmetric)
    constexpr Matrix<3, 3> m = {{0, -2, -3}, {2, 0, -5}, {3, 5, 0}};
    // act / assert
    ASSERT_TRUE(m.isSkewHermitian());
}

TEST(MatrixChecks, not_skew_hermitian_real_offdiag)
{
    // arrange
    constexpr Matrix<3, 3> m = {{0, -2, -3}, {2, 0, -4}, {3, 5, 0}};
    // act / assert
    ASSERT_FALSE(m.isSkewHermitian());
}

TEST(MatrixChecks, skew_hermitian_complex)
{
    // arrange: A[0,1] = {2,1}, A[1,0] = -conj({2,1}) = {-2,1}
    constexpr Matrix<2, 2, std::complex<float>> m = {{{0, 0}, {2, 1}}, {{-2, 1}, {0, 0}}};
    // act / assert
    ASSERT_TRUE(m.isSkewHermitian());
}

TEST(MatrixChecks, not_skew_hermitian_complex_mismatch)
{
    // arrange: mismatch in the skew-Hermitian relation
    constexpr Matrix<2, 2, std::complex<float>> m = {{{0, 0}, {2, 1}}, {{2, -1}, {0, 0}}};
    // act / assert
    ASSERT_FALSE(m.isSkewHermitian());
}

TEST(MatrixChecks, skew_hermitian_1x1_imag)
{
    // arrange: purely imaginary scalar is skew-Hermitian
    constexpr Matrix<1, 1, std::complex<float>> m = {{{0, 1}}};
    // act / assert
    ASSERT_TRUE(m.isSkewHermitian());
}

TEST(MatrixChecks, not_skew_hermitian_1x1_nonpureimag)
{
    // arrange: general complex scalar not purely imaginary
    constexpr Matrix<1, 1, std::complex<float>> m = {{{1, 1}}};
    // act / assert
    ASSERT_FALSE(m.isSkewHermitian());
}
