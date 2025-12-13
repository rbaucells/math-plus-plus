#include <gtest/gtest.h>
#include "math++/math.h"

TEST(MatrixChecks, row_echelon_square) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 3, 1}, {0, 0, 5}, {0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_square_zero_row) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 3, 1}, {0, 0, 0}, {0, 0, 5}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_square_pivots) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 0, 1}, {5, 4, 0}, {0, 0, 5}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_wide) {
    // arrange
    constexpr Matrix<5, 4> a = {{1, 6, 7, 7, 1}, {0, 9, 2, 1, 1}, {0, 0, 0, 2, 2}, {0, 0, 0, 0, 1}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_wide_zero_row) {
    // arrange
    constexpr Matrix<5, 4> a = {{1, 6, 7, 7, 1}, {0, 9, 2, 1, 1}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_wide_pivots) {
    // arrange
    constexpr Matrix<5, 4> a = {{1, 6, 7, 7, 1}, {0, 0, 2, 1, 1}, {4, 2, 0, 0, 0}, {0, 0, 0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, row_echelon_tall) {
    // arrange
    constexpr Matrix<2, 3> a = {{3, 4}, {0, 1}, {0, 0}};
    // act / assert
    ASSERT_TRUE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_tall_zero_row) {
    // arrange
    constexpr Matrix<2, 3> a = {{3, 4}, {0, 0}, {1, 2}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, not_row_echelon_tall_pivots) {
    // arrange
    constexpr Matrix<2, 3> a = {{0, 4}, {0, 3}, {0, 0}};
    // act / assert
    ASSERT_FALSE(a.isRowEchelon());
}

TEST(MatrixChecks, positive_definite) {
    // arrange
    constexpr Matrix<2, 2> m = {{2, -1}, {-1, 2}};
    // act / assert
    ASSERT_TRUE(m.isPositiveDefinite());
    ASSERT_TRUE(m.isPositiveSemiDefinite());
    ASSERT_FALSE(m.isNegativeDefinite());
    ASSERT_FALSE(m.isNegativeSemiDefinite());
}

TEST(MatrixChecks, positive_semi_definite) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, -1}, {-1, 1}};
    // act / assert
    ASSERT_TRUE(m.isPositiveSemiDefinite());
    ASSERT_FALSE(m.isPositiveDefinite());
    ASSERT_FALSE(m.isNegativeDefinite());
    ASSERT_FALSE(m.isNegativeSemiDefinite());
}

TEST(MatrixChecks, negative_definite) {
    // arrange
    constexpr Matrix<2, 2> m = {{-2, -1}, {-1, -2}};
    // act / assert
    ASSERT_TRUE(m.isNegativeDefinite());
    ASSERT_TRUE(m.isNegativeSemiDefinite());
    ASSERT_FALSE(m.isPositiveDefinite());
    ASSERT_FALSE(m.isPositiveSemiDefinite());
}

TEST(MatrixChecks, negative_semi_definite) {
    // arrange
    constexpr Matrix<2, 2> m = {{-1, 0}, {0, 0}};
    // act / assert
    ASSERT_TRUE(m.isNegativeSemiDefinite());
    ASSERT_FALSE(m.isNegativeDefinite());
    ASSERT_FALSE(m.isPositiveDefinite());
    ASSERT_FALSE(m.isPositiveSemiDefinite());
}

TEST(MatrixChecks, indefinite) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, 2}, {2, -3}};
    // act / assert
    ASSERT_FALSE(m.isPositiveDefinite());
    ASSERT_FALSE(m.isPositiveSemiDefinite());
    ASSERT_FALSE(m.isNegativeDefinite());
    ASSERT_FALSE(m.isNegativeSemiDefinite());
}