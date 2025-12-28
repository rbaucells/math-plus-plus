#include <gtest/gtest.h>
#include "math++/math.h"

TEST(MatrixGeneral, swap_row) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    constexpr Matrix<3, 3> expected = {{7, 8, 9}, {4, 5, 6}, {1, 2, 3}};
    // act
    const Matrix<3, 3> swapped = m.swapRows(0, 2);
    // assert
    ASSERT_TRUE(swapped == expected);
}

TEST(MatrixGeneral, swap_column) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    constexpr Matrix<3, 3> expected = {{3, 2, 1}, {6, 5, 4}, {9, 8, 7}};
    // act
    const Matrix<3, 3> swapped = m.swapColumns(0, 2);
    // assert
    ASSERT_TRUE(swapped == expected);
}

TEST(MatrixGeneral, determinant_1x1) {
    // arrange
    constexpr Matrix<1, 1> a = {{5}};
    // act
    const float det = a.determinant();
    // assert
    ASSERT_FLOAT_EQ(det, 5);
}

TEST(MatrixGeneral, determinant_2x2) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    // act
    const float det = a.determinant();
    // assert
    ASSERT_FLOAT_EQ(det, -2);
}

TEST(MatrixGeneral, determinant_3x3) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 2, 3}, {4, 5, 4}, {6, 1, 2}};
    // act
    const float det = a.determinant();
    // assert
    ASSERT_FLOAT_EQ(det, -40);
}

TEST(MatrixGeneral, determinant_4x4_laplace) {
    // arrange
    const Matrix<4, 4> a = {{1, 2, 2, 1}, {1, 9, 8, 12}, {1, 2, 3, 4}, {7, 3, 2, 1}};
    // act
    const float det = a.determinant();
    // assert
    ASSERT_FLOAT_EQ(det, 133);
}

TEST(MatrixGeneral, determinant_4x4_lu) {
    // arrange
    constexpr Matrix<4, 4> a = {{1, 2, 2, 1}, {1, 9, 8, 12}, {1, 2, 3, 4}, {7, 3, 2, 1}};
    // act
    const float det = a.determinant(Matrix<4, 4>::DeterminantAlgorithm::lu);
    // assert
    ASSERT_FLOAT_EQ(det, 133);
}

TEST(MatrixGeneral, determinant_4x4_triangular) {
    // arrange
    constexpr Matrix<4, 4> a = {{1, 4, 5, 2}, {0, 2, 5, 7}, {0, 0, 1, 5}, {0, 0, 0, 4}};
    // act
    const float det = a.determinant(Matrix<4, 4>::DeterminantAlgorithm::triangular);
    // assert
    ASSERT_FLOAT_EQ(det, 8);
}

TEST(MatrixGeneral, inverse_1x1) {
    // arrange
    constexpr Matrix<1, 1> a = {{5}};
    constexpr Matrix<1, 1> expected = {{1.f / 5.f}};
    // act
    const Matrix<1, 1> inverse = a.inverse();
    // assert
    ASSERT_TRUE(inverse == expected);
}

TEST(MatrixGeneral, inverse_2x2) {
    // arrange
    constexpr Matrix<2, 2> a = {{2, 1}, {1, 3}};
    constexpr Matrix<2, 2> expected = {{3.f / 5.f, -1.f / 5.f}, {-1.f / 5.f, 2.f / 5.f}};
    // act
    const Matrix<2, 2> inverse = a.inverse();
    // assert
    ASSERT_TRUE(inverse == expected);
}

TEST(MatrixGeneral, inverse_3x3) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, -3, -2}, {1, -4, -2}, {-3, 4, 1}};
    constexpr Matrix<3, 3> expected = {{4, -5, -2}, {5, -6, -2}, {-8, 9, 3}};
    // act
    const Matrix<3, 3> inverse = a.inverse();
    // assert
    ASSERT_TRUE(inverse.equals(expected, 0.01));
}

TEST(MatrixGeneral, inverse_random) {
    // run until we get a matrix that isnt singular
    while (true) {
        // arrange
        const Matrix<3, 3> a = Matrix<3, 3>::random();

        // if matrix is singular, try again
        if (compare(a.determinant(), 0))
            continue;

        const Matrix<3, 3> identity = Matrix<3, 3>::identity();
        // act
        const Matrix<3, 3> inverse = a.inverse();
        // assert
        const Matrix<3, 3> aInverse = a * inverse;
        const Matrix<3, 3> inverseA = inverse * a;

        ASSERT_TRUE(aInverse.equals(identity, 0.1));
        ASSERT_TRUE(inverseA.equals(identity, 0.1));
        break;
    }
}

TEST(MatrixGeneral, row_echelon_form) {
    // arrange
    constexpr Matrix<4, 3> m = {{2, 1, -1, 8}, {-3, -1, 2, -11}, {-2, 1, 2, -3}};

    // act
    const Matrix<4, 3> ref = m.toRowEchelon();

    // assert
    ASSERT_TRUE(m.isRowEchelonOfThis(ref));
}

TEST(MatrixChecks, row_echelon_skip_pivot_column) {
    // arrange
    constexpr Matrix<3, 3> m = {{{0, 2, 2},{0, 3.0, 4.0},{0, 5, 6.0}}};

    // act
    const Matrix<3, 3> ref = m.toRowEchelon();

    // assert
    ASSERT_TRUE(m.isRowEchelonOfThis(ref));
}

TEST(MatrixGeneral, reduced_row_echelon_form) {
    // arrange
    constexpr Matrix<4, 3> m = {{2, 1, -1, 8}, {-3, -1, 2, -11}, {-2, 1, 2, -3}};
    constexpr Matrix<4, 3> expected = {{1, 0, 0, 2}, {0, 1, 0, 3}, {0, 0, 1, -1}};

    // act
    const Matrix<4, 3> rref = m.toReducedRowEchelon();

    // assert
    ASSERT_TRUE(rref.equals(expected, 0.1));
}

TEST(MatrixChecks, reduced_row_echelon_skip_pivot_column) {
    // arrange
    constexpr Matrix<3, 3> m = {{{0, 1, 2}, {0, 3.0, 4.0}, {0, 5, 6.0}}};
    constexpr Matrix<3, 3> expected = {{{0, 1, 0}, {0, 0, 1}, {0, 0, 0}}};

    // act
    const Matrix<3, 3> rref = m.toReducedRowEchelon();

    // assert
    ASSERT_TRUE(rref.equals(expected, 0.01));
}

TEST(MatrixGeneral, forward_substitution) {
    // arrange
    constexpr Matrix<2, 2> l = {{1, 0}, {2, 3}};
    constexpr Vector<2> b = {4, 11};
    constexpr Vector<2> expected = {4, 1};
    // act
    const Vector<2> x = l.forwardSubstitution(b);
    // assert
    ASSERT_TRUE(x == expected);
}

TEST(MatrixGeneral, backward_substitution) {
    // arrange
    constexpr Matrix<3, 3> u = {{1, -2, 1}, {0, 1, 6}, {0, 0, 1}};
    constexpr Vector<3> b = {4, -1, 2};
    constexpr Vector<3> expected = {-24, -13, 2};
    // act
    const Vector<3> x = u.backwardsSubstitution(b);
    // assert
    ASSERT_TRUE(x == expected);
}

TEST(MatrixGeneral, solve_linear_system_inverse) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 1, 1}, {0, 2, 5}, {2, 5, -1}};
    constexpr Vector<3> b = {6, -4, 27};
    constexpr Vector<3> expected = {5, 3, -2};
    // act
    const Vector<3> x = a.solveLinearSystem(b, Matrix<3, 3>::LinearSystemAlgorithm::inverse);
    // assert
    ASSERT_TRUE(x.equals(expected, 0.1));
}

TEST(MatrixGeneral, solve_linear_system_lu) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 1, 1}, {0, 2, 5}, {2, 5, -1}};
    constexpr Vector<3> b = {6, -4, 27};
    constexpr Vector<3> expected = {5, 3, -2};
    // act
    const Vector<3> x = a.solveLinearSystem(b, Matrix<3, 3>::LinearSystemAlgorithm::lu_factorization);
    // assert
    ASSERT_TRUE(x == expected);
}

TEST(MatrixGeneral, solve_linear_system_rr) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 1, 1}, {0, 2, 5}, {2, 5, -1}};
    constexpr Vector<3> b = {6, -4, 27};
    constexpr Vector<3> expected = {5, 3, -2};
    // act
    const Vector<3> x = a.solveLinearSystem(b, Matrix<3, 3>::LinearSystemAlgorithm::row_reduction);
    // assert
    ASSERT_TRUE(x == expected);
}

TEST(MatrixGeneral, symmetric_part) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> expected = {{1, 2.5f}, {2.5f, 4}};
    // act
    const Matrix<2, 2> symmetricPart = m.symmetricPart();
    // assert
    ASSERT_TRUE(symmetricPart == expected);
}

TEST(MatrixGeneral, anti_symmetric_part) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> expected = {{0, -0.5f}, {0.5f, 0}};
    // act
    const Matrix<2, 2> symmetricPart = m.antiSymmetricPart();
    // assert
    ASSERT_TRUE(symmetricPart == expected);
}