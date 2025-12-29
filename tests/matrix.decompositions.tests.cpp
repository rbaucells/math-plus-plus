#include <gtest/gtest.h>
#include "math++/math.h"

TEST(MatrixDecompositions, lu_decomp_square) {
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

TEST(MatrixDecompositions, lu_decomp_square_zero_column) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 1, 3}, {0, 4, 7}, {0, 7, 9}};
    // act
    auto [l, u] = a.fullLuDecomposition(true);
    const Matrix<3, 3> calculatedA = l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, fail_lu_decomp_square_zero_column) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 1, 3}, {0, 4, 7}, {0, 7, 9}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_decomp_square_zero_pivot_no_skip) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 1, 3}, {1, 4, 7}, {2, 7, 9}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_decomp_square_zero_pivot_with_skip) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 1, 3}, {1, 4, 7}, {2, 7, 9}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition(true));
}


TEST(MatrixDecompositions, lu_decomp_tall) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 1}, {4, 4}, {6, 7}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {2, 1, 0}, {3, 2, 1}};
    constexpr Matrix<2, 3> expectedU = {{2, 1}, {0, 2}, {0, 0}};
    // act
    auto [l, u] = a.fullLuDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, lu_decomp_tall_zero_column) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 0}, {4, 0}, {6, 0}};
    // act
    auto [l, u] = a.fullLuDecomposition(true);
    const Matrix<2, 3> calculatedA = l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, fail_lu_decomp_tall_zero_column) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 0}, {4, 0}, {6, 0}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_decomp_tall_zero_pivot_no_skip) {
    // arrange
    constexpr Matrix<2, 3> a = {{0, 4}, {4, 5}, {6, 4}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_decomp_tall_zero_pivot_with_skip) {
    // arrange
    constexpr Matrix<2, 3> a = {{0, 4}, {4, 5}, {6, 4}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition(true));
}


TEST(MatrixDecompositions, lu_decomp_wide) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 1, 3}, {4, 4, 7}};
    constexpr Matrix<2, 2> expectedL = {{1, 0}, {2, 1}};
    constexpr Matrix<3, 2> expectedU = {{2, 1, 3}, {0, 2, 1}};
    // act
    auto [l, u] = a.fullLuDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, lu_decomp_wide_zero_column) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 0, 3}, {4, 0, 7}};
    // act
    auto [l, u] = a.fullLuDecomposition(true);
    const Matrix<3, 2> calculatedA = l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
}

TEST(MatrixDecompositions, fail_lu_decomp_wide_zero_column) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 0, 3}, {4, 0, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_decomp_wide_zero_pivot_no_skip) {
    // arrange
    constexpr Matrix<3, 2> a = {{0, 5, 3}, {4, 6, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition());
}

TEST(MatrixDecompositions, fail_lu_decomp_wide_zero_pivot_with_skip) {
    // arrange
    constexpr Matrix<3, 2> a = {{0, 5, 3}, {4, 6, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLuDecomposition(true));
}

TEST(MatrixDecompositions, ldu_decomp_square) {
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

TEST(MatrixDecompositions, fail_ldu_decomp_square_zero_pivot) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 1, 3}, {1, 4, 7}, {2, 7, 9}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLduDecomposition());
}

TEST(MatrixDecompositions, ldu_decomp_tall) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 1}, {4, 4}, {6, 7}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {2, 1, 0}, {3, 2, 1}};
    constexpr Matrix<3, 3> expectedD = {{2, 0, 0}, {0, 2, 0}, {0, 0, 0}};
    constexpr Matrix<2, 3> expectedU = {{1, 0.5f}, {0, 1}, {0, 0}};
    // act
    auto [l, d, u] = a.fullLduDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(d.equals(expectedD, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, fail_ldu_decomp_tall_zero_pivot) {
    // arrange
    constexpr Matrix<2, 3> a = {{0, 4}, {4, 5}, {6, 4}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLduDecomposition());
}


TEST(MatrixDecompositions, ldu_decomp_wide) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 1, 3}, {4, 4, 7}};
    constexpr Matrix<2, 2> expectedL = {{1, 0}, {2, 1}};
    constexpr Matrix<2, 2> expectedD = {{2, 0}, {0, 2}};
    constexpr Matrix<3, 2> expectedU = {{1, 0.5f, 3.0f / 2.0f}, {0, 1, 0.5f}};
    // act
    auto [l, d, u] = a.fullLduDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(d.equals(expectedD, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, fail_ldu_decomp_wide_zero_pivot) {
    // arrange
    constexpr Matrix<3, 2> a = {{0, 5, 3}, {4, 6, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLduDecomposition());
}


TEST(MatrixDecompositions, lup_decomp_square) {
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

TEST(MatrixDecompositions, lup_decomp_square_zero_column) {
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

TEST(MatrixDecompositions, fail_lup_decomp_square_zero_column) {
    // arrange
    constexpr Matrix<3, 3> a = {{2, 1, 0}, {4, 4, 0}, {6, 7, 0}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupDecomposition());
}


TEST(MatrixDecompositions, lup_decomp_tall) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 1}, {4, 4}, {6, 7}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {1.0f / 3.0f, 1, 0}, {2.0f / 3.0f, 0.5f, 1}};
    constexpr Matrix<2, 3> expectedU = {{6, 7}, {0, -4.0f / 3.0f}, {0, 0}};
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

TEST(MatrixDecompositions, lup_decomp_tall_zero_column) {
    // arrange
    constexpr Matrix<2, 3> a = {{0, 1}, {0, 4}, {0, 7}};
    constexpr int expectedNumRowSwaps = 1;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({true, &numRowSwaps});
    const Matrix<2, 3> calculatedA = p.transpose() * l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, fail_lup_decomp_tall_zero_column) {
    // arrange
    constexpr Matrix<2, 3> a = {{0, 1}, {0, 4}, {0, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupDecomposition());
}


TEST(MatrixDecompositions, lup_decomp_wide) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 1, 3}, {4, 4, 7}};
    constexpr Matrix<2, 2> expectedL = {{1, 0}, {0.5f, 1}};
    constexpr Matrix<3, 2> expectedU = {{4, 4, 7}, {0, -1, -0.5f}};
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

TEST(MatrixDecompositions, lup_decomp_wide_zero_column) {
    // arrange
    constexpr Matrix<3, 2> a = {{0, 1, 3}, {0, 4, 7}};
    constexpr int expectedNumRowSwaps = 0;
    // act
    int numRowSwaps = 0;
    auto [l, u, p] = a.fullLupDecomposition({true, &numRowSwaps});
    const Matrix<3, 2> calculatedA = p.transpose() * l * u;
    // assert
    ASSERT_TRUE(a.equals(calculatedA, 0.001f));
    ASSERT_EQ(numRowSwaps, expectedNumRowSwaps);
}

TEST(MatrixDecompositions, fail_lup_decomp_wide_zero_column) {
    // arrange
    constexpr Matrix<3, 2> a = {{0, 1, 3}, {0, 4, 7}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupDecomposition());
}



TEST(MatrixDecompositions, lupq_decomp_square) {
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

TEST(MatrixDecompositions, lupq_decomp_square_zero_section) {
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

TEST(MatrixDecompositions, fail_lupq_decomp_square_zero_section) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 2, 3}, {2, 4, 6}, {4, 8, 12}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupqDecomposition());
}


TEST(MatrixDecompositions, lupq_decomp_tall) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 1}, {4, 4}, {6, 7}};
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

TEST(MatrixDecompositions, lupq_decomp_tall_zero_section) {
    // arrange
    constexpr Matrix<2, 3> a = {{1, 2}, {2, 4}, {3, 6}};
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

TEST(MatrixDecompositions, fail_lupq_decomp_tall_zero_section) {
    // arrange
    constexpr Matrix<2, 3> a = {{1, 2}, {2, 4}, {3, 6}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupqDecomposition());
}


TEST(MatrixDecompositions, lupq_decomp_wide) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 1, 3}, {4, 4, 7}};
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

TEST(MatrixDecompositions, lupq_decomp_wide_zero_section) {
    // arrange
    constexpr Matrix<3, 2> a = {{1, 2, 3}, {2, 4, 6}};
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

TEST(MatrixDecompositions, fail_lupq_decomp_wide_zero_section) {
    // arrange
    constexpr Matrix<3, 2> a = {{1, 2, 3}, {2, 4, 6}};
    // act / assert
    ASSERT_ANY_THROW(a.fullLupqDecomposition());
}

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

TEST(MatrixDecompositions, fail_cholesky_real_psd) {
    // arrange
    constexpr Matrix<3, 3> a = {{3, 1, 2}, {1, 3, 2}, {2, 2, 2}};
    // act / assert
    ASSERT_THROW(a.choleskyDecomposition(), NotPositiveDefinite);
}

TEST(MatrixDecompositions, fail_cholesky_real_not_symmetric) {
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

TEST(MatrixDecompositions, fail_cholesky_complex_psd) {
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
