#include <gtest/gtest.h>
#include "math++/math.h"

// TEST(MatrixDecompositions, lup_decomp_square) {
//     // arrange
//     constexpr Matrix<3, 3> a = {{2, 1, 3}, {4, 4, 7}, {6, 7, 9}};
//     constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {1.0f / 3.0f, 1, 0}, {2.0f / 3.0f, 0.5f, 1}};
//     constexpr Matrix<3, 3> expectedU = {{6, 7, 9}, {0, -4.0f / 3.0f, 0}, {0, 0, 1}};
//     constexpr Matrix<3, 3> expectedP = {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}};
//     // act
//     auto [l, u, p] = a.lupDecomposition();
//     // assert
//     ASSERT_TRUE(l.equals(expectedL, 0.001f));
//     ASSERT_TRUE(u.equals(expectedU, 0.001f));
//     ASSERT_TRUE(p.equals(expectedP, 0.001f));
// }
//
// TEST(MatrixDecompositions, lup_decomp_tall) {
//     // arrange
//     constexpr Matrix<2, 3> a = {{2, 1}, {4, 4}, {6, 7}};
//     constexpr Matrix<2, 3> expectedL = {{1, 0}, {1.0f / 3.0f, 1}, {2.0f / 3.0f, 0.5f}};
//     constexpr Matrix<2, 2> expectedU = {{6, 7}, {0, -4.0f / 3.0f}};
//     constexpr Matrix<3, 3> expectedP = {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}};
//     // act
//     auto [l, u, p] = a.lupDecomposition();
//     // assert
//     ASSERT_TRUE(l.equals(expectedL, 0.001f));
//     ASSERT_TRUE(u.equals(expectedU, 0.001f));
//     ASSERT_TRUE(p.equals(expectedP, 0.001f));
// }
//
// TEST(MatrixDecompositions, lup_decomp_wide) {
//     // arrange
//     constexpr Matrix<3, 2> a = {{2, 1, 3}, {4, 4, 7}};
//     constexpr Matrix<2, 2> expectedL = {{1, 0}, {0.5f, 1}};
//     constexpr Matrix<3, 2> expectedU = {{4, 4, 7}, {0, -1, -0.5f}};
//     constexpr Matrix<2, 2> expectedP = {{0, 1}, {1, 0}};
//     // act
//     auto [l, u, p] = a.lupDecomposition();
//     // assert
//     ASSERT_TRUE(l.equals(expectedL, 0.001f));
//     ASSERT_TRUE(u.equals(expectedU, 0.001f));
//     ASSERT_TRUE(p.equals(expectedP, 0.001f));
// }

TEST(MatrixDecompositions, lu_decomp_square) {
    // arrange
    constexpr Matrix<3, 3> a = {{2, 1, 3}, {4, 4, 7}, {6, 7, 9}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {2, 1, 0}, {3, 2, 1}};
    constexpr Matrix<3, 3> expectedU = {{2, 1, 3}, {0, 2, 1}, {0, 0, -2}};
    // act
    auto [l, u] = a.luDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, lu_decomp_square_zero_column) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, 1, 3}, {0, 4, 7}, {0, 7, 9}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {0, 1, 0}, {0, 1.75f, 1}};
    constexpr Matrix<3, 3> expectedU = {{0, 1, 3}, {0, 4, 7}, {0, 0, -3.25}};
    // act
    auto [l, u] = a.luDecomposition(true);
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, lu_decomp_tall) {
    // arrange
    constexpr Matrix<2, 3> a = {{2, 1}, {4, 4}, {6, 7}};
    constexpr Matrix<3, 3> expectedL = {{1, 0, 0}, {2, 1, 0}, {3, 2, 1}};
    constexpr Matrix<2, 3> expectedU = {{2, 1}, {0, 2}, {0, 0}};
    // act
    auto [l, u] = a.luDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}

TEST(MatrixDecompositions, lu_decomp_wide) {
    // arrange
    constexpr Matrix<3, 2> a = {{2, 1, 3}, {4, 4, 7}};
    constexpr Matrix<2, 2> expectedL = {{1, 0}, {2, 1}};
    constexpr Matrix<3, 2> expectedU = {{2, 1, 3}, {0, 2, 1}};
    // act
    auto [l, u] = a.luDecomposition();
    // assert
    ASSERT_TRUE(l.equals(expectedL, 0.001f));
    ASSERT_TRUE(u.equals(expectedU, 0.001f));
}