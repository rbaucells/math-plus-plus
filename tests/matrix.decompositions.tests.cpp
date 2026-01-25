#include <gtest/gtest.h>
#include "math++/math.h"

#pragma region LU
TEST(MatrixDecompositions, lu_square_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{2, 1, 3}, {4, 4, 7}, {6, 7, 9}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {2, 1, 0}, {3, 2, 1}};
    constexpr Matrix<3, 3> expectedU = {{2, 1, 3}, {0, 2, 1}, {0, 0, -2}};
    // act
    auto [l, u] = a.fullLuDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, lu_square_zero_column_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 1, 3}, {0, 4, 7}, {0, 7, 9}};
    // act
    auto [l, u] = a.fullLuDecomposition(true);
    const Matrix<3, 3> calculatedA = l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, fail_lu_square_zero_column_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 1, 3}, {0, 4, 7}, {0, 7, 9}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_square_zero_pivot_no_skip_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 1, 3}, {1, 4, 7}, {2, 7, 9}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_square_zero_pivot_with_skip_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 1, 3}, {1, 4, 7}, {2, 7, 9}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition(true));
}


TEST(MatrixDecompositions, lu_tall_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 1}, {4, 4}, {6, 7}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {2, 1, 0}, {3, 2, 1}};
    constexpr Matrix<3, 2> expectedU = {{2, 1}, {0, 2}, {0, 0}};
    // act
    auto [l, u] = a.fullLuDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, lu_tall_zero_column_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 0}, {4, 0}, {6, 0}};
    // act
    auto [l, u] = a.fullLuDecomposition(true);
    const Matrix<3, 2> calculatedA = l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, fail_lu_tall_zero_column_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 0}, {4, 0}, {6, 0}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_tall_zero_pivot_no_skip_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{0, 4}, {4, 5}, {6, 4}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_tall_zero_pivot_with_skip_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{0, 4}, {4, 5}, {6, 4}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition(true));
}


TEST(MatrixDecompositions, lu_wide_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 1, 3}, {4, 4, 7}};
    constexpr Matrix<2, 2> expectedL = {{1, 0}, {2, 1}};
    constexpr Matrix<2, 3> expectedU = {{2, 1, 3}, {0, 2, 1}};
    // act
    auto [l, u] = a.fullLuDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, lu_wide_zero_column_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 0, 3}, {4, 0, 7}};
    // act
    auto [l, u] = a.fullLuDecomposition(true);
    const Matrix<2, 3> calculatedA = l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, fail_lu_wide_zero_column_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 0, 3}, {4, 0, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_wide_zero_pivot_no_skip_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{0, 5, 3}, {4, 6, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_wide_zero_pivot_with_skip_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{0, 5, 3}, {4, 6, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition(true));
}

TEST(MatrixDecompositions, lu_square_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 2}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}, {{-11, 11}, {4, 0}, {9, -3}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedL = {{{1, 0}, {0, 0}, {0, 0}}, {{1.4f, -2.8f}, {1, 0}, {0, 0}}, {{2.2f, 6.6f}, {-0.95405f, 0.62432f}, {1, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedU = {{{1, 2}, {3, -4}, {5, 6}}, {{0, 0}, {16, 22}, {-23.8f, 15.6f}}, {{0, 0}, {0, 0}, {24.633f, -19.4578f}}};
    // act
    auto [l, u] = a.fullLuDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, lu_square_zero_column_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{0, 0}, {9, 8}, {0, 10}}, {{0, 0}, {4, 0}, {9, -3}}};
    // act
    auto [l, u] = a.fullLuDecomposition(true);
    const Matrix<3, 3, std::complex<float>> calculatedA = l * u;
    // assert
    ASSERT_TRUE(calculatedA.equals(a, 0.001f));
}

TEST(MatrixDecompositions, fail_lu_square_zero_column_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{0, 0}, {9, 8}, {0, 10}}, {{0, 0}, {4, 0}, {9, -3}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_square_zero_pivot_no_skip_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}, {{-11, 11}, {4, 0}, {9, -3}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_square_zero_pivot_with_skip_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}, {{-11, 11}, {4, 0}, {9, -3}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition(true));
}

TEST(MatrixDecompositions, lu_tall_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{1, 2}, {3, -4}}, {{7, 0}, {9, 8}}, {{-11, 11}, {4, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedL = {{{1, 0}, {0, 0}, {0, 0}}, {{1.4f, -2.8f}, {1, 0}, {0, 0}}, {{2.2f, 6.6f}, {-0.95405f, 0.62432f}, {1, 0}}};
    constexpr Matrix<3, 2, std::complex<float>> expectedU = {{{1, 2}, {3, -4}}, {{0, 0}, {16, 22}}, {{0, 0}, {0, 0}}};
    // act
    auto [l, u] = a.fullLuDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, lu_tall_zero_column_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{1, 2}, {3, -4}}, {{7, 0}, {9, 8}}, {{-11, 11}, {4, 0}}};
    // act
    auto [l, u] = a.fullLuDecomposition(true);
    const Matrix<3, 2, std::complex<float>> calculatedA = l * u;
    // assert
    ASSERT_TRUE(calculatedA.equals(a, 0.001f));
}

TEST(MatrixDecompositions, fail_lu_tall_zero_column_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{0, 0}, {3, -4}}, {{0, 0}, {9, 8}}, {{0, 0}, {4, 0}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_tall_zero_pivot_no_skip_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{0, 0}, {3, -4}}, {{7, 0}, {9, 8}}, {{-11, 11}, {4, 0}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_tall_zero_pivot_with_skip_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{0, 0}, {3, -4}}, {{7, 0}, {9, 8}}, {{-11, 11}, {4, 0}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition(true));
}

TEST(MatrixDecompositions, lu_wide_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{1, 2}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedL = {{{1, 0}, {0, 0}}, {{1.4f, -2.8f}, {1, 0}}};
    constexpr Matrix<2, 3, std::complex<float>> expectedU = {{{1, 2}, {3, -4}, {5, 6}}, {{0, 0}, {16, 22}, {-23.8f, 15.6f}}};
    // act
    auto [l, u] = a.fullLuDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, lu_wide_zero_column_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{0, 0}, {9, 8}, {0, 10}}};
    // act
    auto [l, u] = a.fullLuDecomposition(true);
    const Matrix<2, 3, std::complex<float>> calculatedA = l * u;
    // assert
    ASSERT_TRUE(calculatedA.equals(a, 0.001f));
}

TEST(MatrixDecompositions, fail_lu_wide_zero_column_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{0, 0}, {9, 8}, {0, 10}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_wide_zero_pivot_no_skip_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_wide_zero_pivot_with_skip_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition(true));
}

#pragma endregion

#pragma region LDU
TEST(MatrixDecompositions, ldu_square_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{2, 1, 3}, {4, 4, 7}, {6, 7, 9}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {2, 1, 0}, {3, 2, 1}};
    constexpr Matrix<3, 3> expectedD = {{2, 0, 0}, {0, 2, 0}, {0, 0, -2}};
    constexpr Matrix<3, 3> expectedU = {{1, 0.5f, 3.0f / 2.0f}, {0, 1, 0.5f}, {0, 0, 1}};
    // act
    auto [l, d, u] = a.fullLduDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(d.equals(expectedD, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, fail_ldu_square_zero_pivot_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 1, 3}, {1, 4, 7}, {2, 7, 9}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLduDecomposition());
}

TEST(MatrixDecompositions, ldu_tall_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 1}, {4, 4}, {6, 7}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {2, 1, 0}, {3, 2, 1}};
    constexpr Matrix<3, 3> expectedD = {{2, 0, 0}, {0, 2, 0}, {0, 0, 0}};
    constexpr Matrix<3, 2> expectedU = {{1, 0.5f}, {0, 1}, {0, 0}};
    // act
    auto [l, d, u] = a.fullLduDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(d.equals(expectedD, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, fail_ldu_tall_zero_pivot_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{0, 4}, {4, 5}, {6, 4}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLduDecomposition());
}


TEST(MatrixDecompositions, ldu_wide_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 1, 3}, {4, 4, 7}};
    constexpr Matrix<2, 2> expectedL = {{1, 0}, {2, 1}};
    constexpr Matrix<2, 2> expectedD = {{2, 0}, {0, 2}};
    constexpr Matrix<2, 3> expectedU = {{1, 0.5f, 3.0f / 2.0f}, {0, 1, 0.5f}};
    // act
    auto [l, d, u] = a.fullLduDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(d.equals(expectedD, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, fail_ldu_wide_zero_pivot_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{0, 5, 3}, {4, 6, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLduDecomposition());
}

TEST(MatrixDecompositions, ldu_square_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 2}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}, {{-11, 11}, {4, 0}, {9, -3}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedL = {{{1, 0}, {0, 0}, {0, 0}}, {{1.4f, -2.8f}, {1, 0}, {0, 0}}, {{2.2f, 6.6f}, {-0.95405f, 0.62432f}, {1, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedD = {{{1, 2}, {0, 0}, {0, 0}}, {{0, 0}, {16, 22}, {0, 0}}, {{0, 0}, {0, 0}, {24.633f, -19.4578f}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedU = {{{1, 0}, {-1, -2}, {3.4, -0.8}}, {{0, 0}, {1, 0}, {-0.0508, 1.044}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act
    auto [l, d, u] = a.fullLduDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(d.equals(expectedD, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, fail_ldu_square_zero_pivot_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}, {{-11, 11}, {4, 0}, {9, -3}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLduDecomposition());
}

TEST(MatrixDecompositions, ldu_wide_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{1, 2}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedL = {{{1, 0}, {0, 0}}, {{1.4f, -2.8f}, {1, 0}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedD = {{{1, 2}, {0, 0}}, {{0, 0}, {16, 22}}};
    constexpr Matrix<2, 3, std::complex<float>> expectedU = {{{1, 0}, {-1, -2}, {3.4, -0.8}}, {{0, 0}, {1, 0}, {-0.0508, 1.044}}};
    // act
    auto [l, d, u] = a.fullLduDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(d.equals(expectedD, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, fail_ldu_wide_zero_pivot_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLduDecomposition());
}

TEST(MatrixDecompositions, ldu_tall_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{1, 2}, {3, -4}}, {{7, 0}, {9, 8}}, {{-11, 11}, {4, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedL = {{{1, 0}, {0, 0}, {0, 0}}, {{1.4f, -2.8f}, {1, 0}, {0, 0}}, {{2.2f, 6.6f}, {-0.95405f, 0.62432f}, {1, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedD = {{{1, 2}, {0, 0}, {0, 0}}, {{0, 0}, {16, 22}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}}};
    constexpr Matrix<3, 2, std::complex<float>> expectedU = {{{1, 0}, {-1, -2}}, {{0, 0}, {1, 0}}, {{0, 0}, {0, 0}}};
    // act
    auto [l, d, u] = a.fullLduDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(d.equals(expectedD, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, fail_ldu_tall_zero_pivot_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{0, 0}, {3, -4}}, {{7, 0}, {9, 8}}, {{-11, 11}, {4, 0}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLduDecomposition());
}

#pragma endregion

#pragma region LUP
TEST(MatrixDecompositions, lup_square_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{2, 1, 3}, {4, 4, 7}, {6, 7, 9}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {1.0f / 3.0f, 1, 0}, {2.0f / 3.0f, 0.5f, 1}};
    constexpr Matrix<3, 3> expectedU = {{6, 7, 9}, {0, -4.0f / 3.0f, 0}, {0, 0, 1}};
    constexpr Matrix<3, 3> expectedP = {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}};
    constexpr int expectedNumRowSwaps = 2;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({.numRowSwaps = &numRowSwaps});
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
    ASSERT_TRUE(p.equals(expectedP, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, lup_square_zero_column_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{2, 1, 0}, {4, 4, 0}, {6, 7, 0}};
    constexpr int expectedNumRowSwaps = 2;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({true, &numRowSwaps});
    const Matrix<3, 3> calculatedA = p.transpose() * l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, fail_lup_square_zero_column_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{2, 1, 0}, {4, 4, 0}, {6, 7, 0}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupDecomposition());
}


TEST(MatrixDecompositions, lup_tall_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 1}, {4, 4}, {6, 7}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {1.0f / 3.0f, 1, 0}, {2.0f / 3.0f, 0.5f, 1}};
    constexpr Matrix<3, 2> expectedU = {{6, 7}, {0, -4.0f / 3.0f}, {0, 0}};
    constexpr Matrix<3, 3> expectedP = {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}};
    constexpr int expectedNumRowSwaps = 2;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({.numRowSwaps = &numRowSwaps});
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
    ASSERT_TRUE(p.equals(expectedP, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, lup_tall_zero_column_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{0, 1}, {0, 4}, {0, 7}};
    constexpr int expectedNumRowSwaps = 1;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({true, &numRowSwaps});
    const Matrix<3, 2> calculatedA = p.transpose() * l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, fail_lup_tall_zero_column_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{0, 1}, {0, 4}, {0, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupDecomposition());
}


TEST(MatrixDecompositions, lup_wide_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 1, 3}, {4, 4, 7}};
    constexpr Matrix<2, 2> expectedL = {{1, 0}, {0.5f, 1}};
    constexpr Matrix<2, 3> expectedU = {{4, 4, 7}, {0, -1, -0.5f}};
    constexpr Matrix<2, 2> expectedP = {{0, 1}, {1, 0}};
    constexpr int expectedNumRowSwaps = 1;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({.numRowSwaps = &numRowSwaps});
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
    ASSERT_TRUE(p.equals(expectedP, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, lup_wide_zero_column_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{0, 1, 3}, {0, 4, 7}};
    constexpr int expectedNumRowSwaps = 0;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({true, &numRowSwaps});
    const Matrix<2, 3> calculatedA = p.transpose() * l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, fail_lup_wide_zero_column_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{0, 1, 3}, {0, 4, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupDecomposition());
}

TEST(MatrixDecompositions, lup_square_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 2}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}, {{-11, 11}, {4, 0}, {9, -3}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedL = {{{1, 0}, {0, 0}, {0, 0}}, {{-0.318182f, -0.318182f}, {1, 0}, {0, 0}}, {{0.045455f, -0.136364f}, {-0.016096f, -0.321754f}, {1, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedU = {{{-11, 11}, {4, 0}, {9, -3}}, {{0, 0}, {10.272727f, 9.272727f}, {3.818182f, 11.909091f}}, {{0, 0}, {0, 0}, {1.229664f, 8.783843f}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedP = {{{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {1, 0}, {0, 0}}, {{1, 0}, {0, 0}, {0, 0}}};
    constexpr int expectedNumRowSwaps = 1;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({.numRowSwaps = &numRowSwaps});
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
    ASSERT_TRUE(p.equals(expectedP, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, lup_square_zero_column_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 2}, {3, -4}, {0, 0}}, {{7, 0}, {9, 8}, {0, 0}}, {{-11, 11}, {4, 0}, {0, 0}}};
    constexpr int expectedNumRowSwaps = 1;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({true, &numRowSwaps});
    const Matrix<3, 3, std::complex<float>> calculatedA = p.transpose() * l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, fail_lup_square_zero_column_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 2}, {3, -4}, {0, 0}}, {{7, 0}, {9, 8}, {0, 0}}, {{-11, 11}, {4, 0}, {0, 0}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupDecomposition());
}

TEST(MatrixDecompositions, lup_tall_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{1, 2}, {3, -4}}, {{7, 0}, {9, 8}}, {{-11, 11}, {4, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedL = {{{1, 0}, {0, 0}, {0, 0}}, {{-0.318182f, -0.318182f}, {1, 0}, {0, 0}}, {{0.045455f, -0.136364f}, {-0.016096f, -0.321754f}, {1, 0}}};
    constexpr Matrix<3, 2, std::complex<float>> expectedU = {{{-11, 11}, {4, 0}}, {{0, 0}, {10.272727f, 9.272727f}}, {{0, 0}, {0, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedP = {{{0, 0}, {0, 0}, {1, 0}}, {{0, 0}, {1, 0}, {0, 0}}, {{1, 0}, {0, 0}, {0, 0}}};
    constexpr int expectedNumRowSwaps = 1;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({.numRowSwaps = &numRowSwaps});
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
    ASSERT_TRUE(p.equals(expectedP, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, lup_tall_zero_column_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{0, 0}, {3, -4}}, {{0, 0}, {9, 8}}, {{0, 0}, {4, 0}}};
    constexpr int expectedNumRowSwaps = 0;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({true, &numRowSwaps});
    const Matrix<3, 2, std::complex<float>> calculatedA = p.transpose() * l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, fail_lup_tall_zero_column_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{0, 0}, {3, -4}}, {{0, 0}, {9, 8}}, {{0, 0}, {4, 0}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupDecomposition());
}

TEST(MatrixDecompositions, lup_wide_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{1, 2}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedL = {{{1, 0}, {0, 0}}, {{0.142857f, 0.285714f}, {1, 0}}};
    constexpr Matrix<2, 3, std::complex<float>> expectedU = {{{7, 0}, {9, 8}, {0, 10}}, {{0, 0}, {4, -7.714286f}, {7.857143f, 4.571428f}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedP = {{{0, 0}, {1, 0}}, {{1, 0}, {0, 0}}};
    constexpr int expectedNumRowSwaps = 1;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({.numRowSwaps = &numRowSwaps});
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
    ASSERT_TRUE(p.equals(expectedP, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, lup_wide_zero_column_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{0, 0}, {9, 8}, {0, 10}}};
    constexpr int expectedNumRowSwaps = 0;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({true, &numRowSwaps});
    const Matrix<2, 3, std::complex<float>> calculatedA = p.transpose() * l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, fail_lup_wide_zero_column_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{0, 0}, {3, -4}, {5, 6}}, {{0, 0}, {9, 8}, {0, 10}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupDecomposition());
}

#pragma endregion

#pragma region LUPQ
TEST(MatrixDecompositions, lupq_square_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{2, 1, 3}, {4, 4, 7}, {6, 7, 9}};
    constexpr int expectedNumRowSwaps = 1;
    constexpr int expectedNumColumnSwaps = 1;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({.numRowSwaps = &numRowSwaps, .numColumnSwaps = &numColumnSwaps});
    const Matrix<3, 3> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, lupq_square_zero_section_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 2, 3}, {2, 4, 6}, {4, 8, 12}};
    constexpr int expectedNumRowSwaps = 1;
    constexpr int expectedNumColumnSwaps = 1;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({true, &numRowSwaps, &numColumnSwaps});
    const Matrix<3, 3> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, fail_lupq_square_zero_section_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 2, 3}, {2, 4, 6}, {4, 8, 12}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupqDecomposition());
}


TEST(MatrixDecompositions, lupq_tall_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 1}, {4, 4}, {6, 7}};
    constexpr int expectedNumRowSwaps = 1;
    constexpr int expectedNumColumnSwaps = 1;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({.numRowSwaps = &numRowSwaps, .numColumnSwaps = &numColumnSwaps});
    const Matrix<3, 2> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, lupq_tall_zero_section_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{1, 2}, {2, 4}, {3, 6}};
    constexpr int expectedNumRowSwaps = 1;
    constexpr int expectedNumColumnSwaps = 1;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({true, &numRowSwaps, &numColumnSwaps});
    const Matrix<3, 2> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, fail_lupq_tall_zero_section_real) {
    // arrange
    constexpr Matrix<3, 2> a = {{1, 2}, {2, 4}, {3, 6}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupqDecomposition());
}


TEST(MatrixDecompositions, lupq_wide_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 1, 3}, {4, 4, 7}};
    constexpr int expectedNumRowSwaps = 1;
    constexpr int expectedNumColumnSwaps = 1;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({.numRowSwaps = &numRowSwaps, .numColumnSwaps = &numColumnSwaps});
    const Matrix<2, 3> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, lupq_wide_zero_section_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{1, 2, 3}, {2, 4, 6}};
    constexpr int expectedNumRowSwaps = 1;
    constexpr int expectedNumColumnSwaps = 1;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({true, &numRowSwaps, &numColumnSwaps});
    const Matrix<2, 3> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, fail_lupq_wide_zero_section_real) {
    // arrange
    constexpr Matrix<2, 3> a = {{1, 2, 3}, {2, 4, 6}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupqDecomposition());
}

TEST(MatrixDecompositions, lupq_square_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 2}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}, {{-11, 11}, {4, 0}, {9, -3}}};
    constexpr int expectedNumRowSwaps = 2;
    constexpr int expectedNumColumnSwaps = 2;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({.numRowSwaps = &numRowSwaps, .numColumnSwaps = &numColumnSwaps});
    const Matrix<3, 3, std::complex<float>> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, lupq_square_zero_section_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{2, 4}, {6, 8}, {10, 12}}, {{4, 8}, {12, 16}, {20, 24}}};
    constexpr int expectedNumRowSwaps = 1;
    constexpr int expectedNumColumnSwaps = 1;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({true, &numRowSwaps, &numColumnSwaps});
    const Matrix<3, 3, std::complex<float>> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, fail_lupq_square_zero_section_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{2, 4}, {6, 8}, {10, 12}}, {{4, 8}, {12, 16}, {20, 24}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupqDecomposition());
}

TEST(MatrixDecompositions, lupq_tall_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{1, 2}, {3, -4}}, {{7, 0}, {9, 8}}, {{-11, 11}, {4, 0}}};
    constexpr int expectedNumRowSwaps = 1;
    constexpr int expectedNumColumnSwaps = 1;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({.numRowSwaps = &numRowSwaps, .numColumnSwaps = &numColumnSwaps});
    const Matrix<3, 2, std::complex<float>> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, lupq_tall_zero_section_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{1, 2}, {3, 4}}, {{2, 4}, {6, 8}}, {{4, 8}, {12, 16}}};
    constexpr int expectedNumRowSwaps = 1;
    constexpr int expectedNumColumnSwaps = 1;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({true, &numRowSwaps, &numColumnSwaps});
    const Matrix<3, 2, std::complex<float>> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, fail_lupq_tall_zero_section_complex) {
    // arrange
    constexpr Matrix<3, 2, std::complex<float>> a = {{{1, 2}, {3, 4}}, {{2, 4}, {6, 8}}, {{4, 8}, {12, 16}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupqDecomposition());
}

TEST(MatrixDecompositions, lupq_wide_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{1, 2}, {3, -4}, {5, 6}}, {{7, 0}, {9, 8}, {0, 10}}};
    constexpr int expectedNumRowSwaps = 1;
    constexpr int expectedNumColumnSwaps = 1;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({.numRowSwaps = &numRowSwaps, .numColumnSwaps = &numColumnSwaps});
    const Matrix<2, 3, std::complex<float>> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, lupq_wide_zero_section_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{2, 4}, {6, 8}, {10, 12}}};
    constexpr int expectedNumRowSwaps = 1;
    constexpr int expectedNumColumnSwaps = 1;
    // act
    int numRowSwaps = 0;
    int numColumnSwaps = 0;
    auto [l, u, p, q] = a.fullLupqDecomposition({true, &numRowSwaps, &numColumnSwaps});
    const Matrix<2, 3, std::complex<float>> calculatedA = p.transpose() * l * u * q.transpose();
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
    ASSERT_EQ(numColumnSwaps, expectedNumColumnSwaps);
}

TEST(MatrixDecompositions, fail_lupq_wide_zero_section_complex) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{2, 4}, {6, 8}, {10, 12}}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupqDecomposition());
}

#pragma endregion

#pragma region Cholesky
TEST(MatrixDecompositions, cholesky_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 12, -16}, {12, 37, -43}, {-16, -43, 98}};
    constexpr Matrix<3, 3> expectedL = {{2, 0, 0}, {6, 1, 0}, {-8, 5, 3}};
    constexpr Matrix<3, 3> expectedLt = {{2, 6, -8}, {0, 1, 5}, {0, 0, 3}};
    // act
    auto [l, lt] = a.choleskyDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(lt.equals(expectedLt, 0.001f));
}

TEST(MatrixDecompositions, cholesky_real_psd_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{3, 1, 2}, {1, 3, 2}, {2, 2, 2}};
    // act
    auto [l, lt] = a.choleskyDecomposition({.allowPositiveSemiDefinite = true});
    const Matrix<3, 3> calculatedA = l * lt;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, cholesky_real_not_symmetric_skip_checks_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 12, -16}, {12, 37, -43}, {-15, -43, 98}};
    // act / assert
    ASSERT_NO_THROW(a.choleskyDecomposition({.skipChecks = true}));
}

TEST(MatrixDecompositions, fail_cholesky_real_psd_not_allowed_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{3, 1, 2}, {1, 3, 2}, {2, 2, 2}};
    // act / assert
    ASSERT_THROW(a.choleskyDecomposition(), NotPositiveDefinite);
}

TEST(MatrixDecompositions, fail_cholesky_real_not_symmetric_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 12, -16}, {12, 37, -43}, {-15, -43, 98}};
    // act / assert
    ASSERT_THROW(a.choleskyDecomposition(), NotSymmetricOrHermitian);
}

TEST(MatrixDecompositions, cholesky_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, 0}, {2, 2}, {1, 0}}, {{2, -2}, {9, 0}, {1, -1}}, {{1, 0}, {1, 1}, {5, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedL = {{{2, 0}, {0, 0}, {0, 0}}, {{1, -1}, {2.64575f, 0}, {0, 0}}, {{0.5f, 0}, {0.18898f, 0.18898f}, {2.163f, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedLt = {{{2, 0}, {1, 1}, {0.5f, 0}}, {{0, 0}, {2.64575f, 0}, {0.18898f, -0.18898f}}, {{0, 0}, {0, 0}, {2.163f, 0}}};
    // act
    auto [l, lt] = a.choleskyDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(lt.equals(expectedLt, 0.001f));
}

TEST(MatrixDecompositions, cholesky_complex_psd) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{2, 0}, {1, 1}, {0, 0}}, {{1, -1}, {2, 0}, {0, 1}}, {{0, 0}, {0, -1}, {1, 0}}};
    // act
    auto [l, lt] = a.choleskyDecomposition({.allowPositiveSemiDefinite = true});
    const Matrix<3, 3, std::complex<float>> calculatedA = l * lt;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, cholesky_complex_not_hermitian_skip_checks) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, 0}, {2, 3}, {1, 0}}, {{2, -2}, {9, 0}, {1, -1}}, {{1, 0}, {1, 1}, {5, 0}}};
    // act / assert
    ASSERT_NO_THROW(a.choleskyDecomposition({.skipChecks = true}));
}

TEST(MatrixDecompositions, fail_cholesky_complex_psd_not_allowed) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{2, 0}, {1, 1}, {0, 0}}, {{1, -1}, {2, 0}, {0, 1}}, {{0, 0}, {0, -1}, {1, 0}}};
    // act / assert
    ASSERT_THROW(a.choleskyDecomposition(), NotPositiveDefinite);
}

TEST(MatrixDecompositions, fail_cholesky_complex_not_hermitian) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, 0}, {2, 3}, {1, 0}}, {{2, -2}, {9, 0}, {1, -1}}, {{1, 0}, {1, 1}, {5, 0}}};
    // act / assert
    ASSERT_THROW(a.choleskyDecomposition(), NotSymmetricOrHermitian);
}

#pragma endregion

#pragma region Pivoted Cholesky

TEST(MatrixDecompositions, pivoted_cholesky_real_pd) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 12, -16}, {12, 37, -43}, {-16, -43, 98}};
    // act
    auto [l, lt, p, pt] = a.pivotedCholeskyDecomposition();
    const Matrix<3, 3> calculatedA = pt * l * lt * p;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, pivoted_cholesky_real_psd) {
    // arrange
    constexpr Matrix<3, 3> a = {{3, 1, 2}, {1, 3, 2}, {2, 2, 2}};
    // act
    auto [l, lt, p, pt] = a.pivotedCholeskyDecomposition();
    const Matrix<3, 3> calculatedA = pt * l * lt * p;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, fail_pivoted_cholesky_real_not_symmetric) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 12, -16}, {12, 37, -43}, {-15, -43, 98}};
    // act / assert
    ASSERT_THROW(a.pivotedCholeskyDecomposition(), NotSymmetricOrHermitian);
}

TEST(MatrixDecompositions, pivoted_cholesky_complex_pd) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, 0}, {2, 2}, {1, 0}}, {{2, -2}, {9, 0}, {1, -1}}, {{1, 0}, {1, 1}, {5, 0}}};
    // act
    auto [l, lt, p, pt] = a.pivotedCholeskyDecomposition();
    const Matrix<3, 3, std::complex<float>> calculatedA = pt * l * lt * p;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, pivoted_cholesky_complex_psd) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{2, 0}, {1, 1}, {0, 0}}, {{1, -1}, {2, 0}, {0, 1}}, {{0, 0}, {0, -1}, {1, 0}}};
    // act
    auto [l, lt, p, pt] = a.pivotedCholeskyDecomposition();
    const Matrix<3, 3, std::complex<float>> calculatedA = pt * l * lt * p;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, fail_pivoted_cholesky_complex_not_hermitian) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, 0}, {2, 3}, {1, 0}}, {{2, -2}, {9, 0}, {1, -1}}, {{1, 0}, {1, 1}, {5, 0}}};
    // act / assert
    ASSERT_THROW(a.pivotedCholeskyDecomposition(), NotSymmetricOrHermitian);
}

#pragma endregion

#pragma region LDL
TEST(MatrixDecompositions, ldl_real_pd) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 12, -16}, {12, 37, -43}, {-16, -43, 98}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {3, 1, 0}, {-4, 5, 1}};
    constexpr Matrix<3, 3> expectedD = {{4, 0, 0}, {0, 1, 0}, {0, 0, 9}};
    constexpr Matrix<3, 3> expectedLt = {{1, 3, -4}, {0, 1, 5}, {0, 0, 1}};
    // act
    auto [l,d, lt] = a.ldlDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(d.equals(expectedD, 0.001f));
    ASSERT_TRUE(lt.equals(expectedLt, 0.001f));
}

TEST(MatrixDecompositions, ldl_real_psd) {
    // arrange
    constexpr Matrix<3, 3> a = {{3, 1, 2}, {1, 3, 2}, {2, 2, 2}};
    // act
    auto [l,d, lt] = a.ldlDecomposition(true);
    const Matrix<3, 3> calculatedA = l * d * lt;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, fail_ldl_real_psd_not_allowed) {
    // arrange
    constexpr Matrix<3, 3> a = {{3, 1, 2}, {1, 3, 2}, {2, 2, 2}};
    // act / assert
    ASSERT_THROW(a.ldlDecomposition(), NotPositiveDefinite);
}

TEST(MatrixDecompositions, fail_ldl_real_not_symmetric) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 12, -16}, {12, 37, -43}, {-15, -43, 98}};
    // act / assert
    ASSERT_THROW(a.ldlDecomposition(), NotSymmetricOrHermitian);
}

TEST(MatrixDecompositions, ldl_complex_pd) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, 0}, {2, 2}, {1, 0}}, {{2, -2}, {9, 0}, {1, -1}}, {{1, 0}, {1, 1}, {5, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedL = {{{1, 0}, {0, 0}, {0, 0}}, {{0.5f, -0.5f}, {1, 0}, {0, 0}}, {{0.25f, 0}, {0.0714f, 0.0714f}, {1, 0}}};
    constexpr Matrix<3, 3, std::complex<float>> expectedD = {{4, 0, 0}, {0, 7, 0}, {0, 0, 4.6786f}};
    constexpr Matrix<3, 3, std::complex<float>> expectedLt = {{{1, 0}, {0.5f, 0.5f}, {0.25f, 0}}, {{0, 0}, {1, 0}, {0.0714f, -0.0714f}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act
    auto [l,d, lt] = a.ldlDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(d.equals(expectedD, 0.001f));
    ASSERT_TRUE(lt.equals(expectedLt, 0.001f));
}

TEST(MatrixDecompositions, ldl_complex_psd) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{2, 0}, {1, 1}, {0, 0}}, {{1, -1}, {2, 0}, {0, 1}}, {{0, 0}, {0, -1}, {1, 0}}};
    // act
    auto [l,d, lt] = a.ldlDecomposition(true);
    const Matrix<3, 3, std::complex<float>> calculatedA = l * d * lt;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, fail_ldl_complex_psd_not_allowed) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{2, 0}, {1, 1}, {0, 0}}, {{1, -1}, {2, 0}, {0, 1}}, {{0, 0}, {0, -1}, {1, 0}}};
    // act / assert
    ASSERT_THROW(a.ldlDecomposition(), NotPositiveDefinite);
}

TEST(MatrixDecompositions, fail_ldl_complex_not_hermitian) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{4, 0}, {2, 3}, {1, 0}}, {{2, -2}, {9, 0}, {1, -1}}, {{1, 0}, {1, 1}, {5, 0}}};
    // act / assert
    ASSERT_THROW(a.ldlDecomposition(), NotSymmetricOrHermitian);
}
#pragma endregion
