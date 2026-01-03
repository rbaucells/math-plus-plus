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
    constexpr Matrix<4, 4> a = {{1, 2, 2, 1}, {1, 9, 8, 12}, {1, 2, 3, 4}, {7, 3, 2, 1}};
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

TEST(MatrixGeneral, inverse_1x1_real) {
    // arrange
    constexpr Matrix<1, 1> a = {{5}};
    constexpr Matrix<1, 1> expected = {{1.0f / 5.0f}};
    // act
    const Matrix<1, 1> inverse = a.inverse();
    // assert
    ASSERT_TRUE(inverse.equals(expected, 0.001f));
}

TEST(MatrixGeneral, inverse_2x2_real) {
    // arrange
    constexpr Matrix<2, 2> a = {{2, 1}, {1, 3}};
    constexpr Matrix<2, 2> expected = {{3.0f / 5.0f, -1.0f / 5.0f}, {-1.0f / 5.0f, 2.0f / 5.0f}};
    // act
    const Matrix<2, 2> inverse = a.inverse();
    // assert
    ASSERT_TRUE(inverse.equals(expected, 0.001f));
}

TEST(MatrixGeneral, inverse_3x3_real) {
    // arrange
    constexpr Matrix<3, 3> a = {{0, -3, -2}, {1, -4, -2}, {-3, 4, 1}};
    constexpr Matrix<3, 3> expected = {{4, -5, -2}, {5, -6, -2}, {-8, 9, 3}};
    // act
    const Matrix<3, 3> inverse = a.inverse();
    // assert
    ASSERT_TRUE(inverse.equals(expected, 0.001f));
}

TEST(MatrixGeneral, inverse_random_real) {
    // run until we get a matrix that isn't singular
    while (true) {
        // arrange
        const Matrix<3, 3> a = Matrix<3, 3>::random(-1, 1);

        // if matrix is singular, try again
        if (compare(a.determinant(), 0))
            continue;

        const Matrix<3, 3> identity = Matrix<3, 3>::identity();
        // act
        const Matrix<3, 3> inverse = a.inverse();
        // assert
        const Matrix<3, 3> aInverse = a * inverse;
        const Matrix<3, 3> inverseA = inverse * a;

        ASSERT_TRUE(aInverse.equals(identity, 0.001f));
        ASSERT_TRUE(inverseA.equals(identity, 0.001));
        break;
    }
}

TEST(MatrixGeneral, inverse_1x1_complex) {
    // arrange
    constexpr Matrix<1, 1, std::complex<float>> a = {{{{2.0f, 3.0f}}}};
    constexpr Matrix<1, 1, std::complex<float>> expected = {{{{2.0f / 13.0f, -3.0f / 13.0f}}}};
    // act
    const Matrix<1, 1, std::complex<float>> inverse = a.inverse();
    // assert
    ASSERT_TRUE(inverse.equals(expected, 0.001f));
}

TEST(MatrixGeneral, inverse_2x2_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{{1, 1}, {2, -1}}, {{3, 0}, {4, 2}}};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{0.02061f, -0.45361f}, {0.17526f, 0.14433f}}, {{0.123711f, 0.27835f}, {0.05155f, -0.13402f}}};
    // act
    const Matrix<2, 2, std::complex<float>> inverse = a.inverse();
    // assert
    ASSERT_TRUE(inverse.equals(expected, 0.001f));
}

TEST(MatrixGeneral, inverse_3x3_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{1, 1}, {0, -1}, {2, 0}}, {{3, 2}, {-1, 1}, {1, -1}}, {{0, 2}, {1, 0}, {4, -2}}};
    constexpr Matrix<3, 3, std::complex<float>> expected = {{{0.26923f, 0.11539f}, {0.15385f, -0.153845f}, {-0.11538f, -0.03846f}}, {{0, 0.53846f}, {-0.07692f, -0.23077f}, {0.15385f, -0.15385f}}, {{0.15385f, -0.19231f}, {-0.03846f, -0.03846f}, {0.11538f, 0.15385f}}};
    // act
    const Matrix<3, 3, std::complex<float>> inverse = a.inverse();
    // assert
    ASSERT_TRUE(inverse.equals(expected, 0.001f));
}

TEST(MatrixGeneral, inverse_random_complex) {
    // arrange
    while (true) {
        const Matrix<3, 3, std::complex<float>> a = Matrix<3, 3, std::complex<float>>::random(-1, 1);
        if (compare(a.determinant(), std::complex<float>(0, 0)))
            continue;
        const Matrix<3, 3, std::complex<float>> identity = Matrix<3, 3, std::complex<float>>::identity();
        // act
        const Matrix<3, 3, std::complex<float>> inverse = a.inverse();
        // assert
        const Matrix<3, 3, std::complex<float>> aInverse = a * inverse;
        const Matrix<3, 3, std::complex<float>> inverseA = inverse * a;
        ASSERT_TRUE(aInverse.equals(identity, 0.001f));
        ASSERT_TRUE(inverseA.equals(identity, 0.001f));
        break;
    }
}

TEST(MatrixGeneral, row_echelon_form) {
    // arrange
    constexpr Matrix<3, 4> m = {{2, 1, -1, 8}, {-3, -1, 2, -11}, {-2, 1, 2, -3}};

    // act
    const Matrix<3, 4> ref = m.toRowEchelon();

    // assert
    ASSERT_TRUE(m.isRowEchelonOfThis(ref));
}

TEST(MatrixChecks, row_echelon_skip_pivot_column) {
    // arrange
    constexpr Matrix<3, 3> m = {{{0, 2, 2}, {0, 3.0, 4.0}, {0, 5, 6.0}}};

    // act
    const Matrix<3, 3> ref = m.toRowEchelon();

    // assert
    ASSERT_TRUE(m.isRowEchelonOfThis(ref));
}

TEST(MatrixGeneral, reduced_row_echelon_form) {
    // arrange
    constexpr Matrix<3, 4> m = {{2, 1, -1, 8}, {-3, -1, 2, -11}, {-2, 1, 2, -3}};
    constexpr Matrix<3, 4> expected = {{1, 0, 0, 2}, {0, 1, 0, 3}, {0, 0, 1, -1}};

    // act
    const Matrix<3, 4> rref = m.toReducedRowEchelon();

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
    const Vector<3> x = u.backwardSubstitution(b);
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

TEST(MatrixGeneral, hermitian_part) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{1, 0}, {4, -1}}, {{4, 1}, {7, 0}}};
    // act
    const Matrix<2, 2, std::complex<float>> hermitianPart = m.hermitianPart();
    // assert
    ASSERT_TRUE(hermitianPart == expected);
}

TEST(MatrixGeneral, anti_hermitian_part) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> m = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{0, 2}, {-1, 5}}, {{1, 5}, {0, 8}}};
    // act
    const Matrix<2, 2, std::complex<float>> hermitianPart = m.antiHermitianPart();
    // assert
    ASSERT_TRUE(hermitianPart == expected);
}

TEST(MatrixGeneral, transpose_real_square) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    constexpr Matrix<3, 3> expected = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    // act
    const Matrix<3, 3> transpose = a.transpose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, transpose_real_wide) {
    // arrange
    constexpr Matrix<3, 4> a = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    constexpr Matrix<4, 3> expected = {{1, 5, 9}, {2, 6, 10}, {3, 7, 11}, {4, 8, 12}};
    // act
    const Matrix<4, 3> transpose = a.transpose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, transpose_real_tall) {
    // arrange
    constexpr Matrix<4, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    constexpr Matrix<3, 4> expected = {{1, 4, 7, 10}, {2, 5, 8, 11}, {3, 6, 9, 12}};
    // act
    const Matrix<3, 4> transpose = a.transpose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, transpose_complex_square) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{2, 3}, {-1, 4}, {5, -1}}, {{0, -3}, {4, 0}, {-2, 6}}, {{7, -5}, {-8, 1}, {1, 2}}};
    constexpr Matrix<3, 3, std::complex<float>> expected = {{{2, 3}, {0, -3}, {7, -5}}, {{-1, 4}, {4, 0}, {-8, 1}}, {{5, -1}, {-2, 6}, {1, 2}}};
    // act
    const Matrix<3, 3, std::complex<float>> transpose = a.transpose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, transpose_complex_wide) {
    // arrange
    constexpr Matrix<3, 4, std::complex<float>> a = {{{1, 1}, {-2, 3}, {4, 0}, {0, -5}}, {{-3, 2}, {6, -1}, {-7, 4}, {8, 0}}, {{0, 9}, {-10, 5}, {11, -3}, {-12, 0}}};
    constexpr Matrix<4, 3, std::complex<float>> expected = {{{1, 1}, {-3, 2}, {0, 9}}, {{-2, 3}, {6, -1}, {-10, 5}}, {{4, 0}, {-7, 4}, {11, -3}}, {{0, -5}, {8, 0}, {-12, 0}}};
    // act
    const Matrix<4, 3, std::complex<float>> transpose = a.transpose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, transpose_complex_tall) {
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{-1, 2}, {3, 0}, {0, -4}}, {{5, -1}, {-6, 7}, {8, 0}}, {{-9, 0}, {10, -2}, {-11, 5}}, {{0, 12}, {-13, 0}, {14, -3}}};
    constexpr Matrix<3, 4, std::complex<float>> expected = {{{-1, 2}, {5, -1}, {-9, 0}, {0, 12}}, {{3, 0}, {-6, 7}, {10, -2}, {-13, 0}}, {{0, -4}, {8, 0}, {-11, 5}, {14, -3}}};
    // act
    const Matrix<3, 4, std::complex<float>> transpose = a.transpose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, conjugate_transpose_real_square) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    constexpr Matrix<3, 3> expected = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    // act
    const Matrix<3, 3> transpose = a.conjugateTranspose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, conjugate_transpose_real_wide) {
    // arrange
    constexpr Matrix<3, 4> a = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    constexpr Matrix<4, 3> expected = {{1, 5, 9}, {2, 6, 10}, {3, 7, 11}, {4, 8, 12}};
    // act
    const Matrix<4, 3> transpose = a.conjugateTranspose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, conjugate_transpose_real_tall) {
    // arrange
    constexpr Matrix<4, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    constexpr Matrix<3, 4> expected = {{1, 4, 7, 10}, {2, 5, 8, 11}, {3, 6, 9, 12}};
    // act
    const Matrix<3, 4> transpose = a.conjugateTranspose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, conjugate_transpose_complex_square) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> a = {{{2, 3}, {-1, 4}, {5, -1}}, {{0, -3}, {4, 0}, {-2, 6}}, {{7, -5}, {-8, 1}, {1, 2}}};
    constexpr Matrix<3, 3, std::complex<float>> expected = {{{2, -3}, {0, 3}, {7, 5}}, {{-1, -4}, {4, 0}, {-8, -1}}, {{5, 1}, {-2, -6}, {1, -2}}};
    // act
    const Matrix<3, 3, std::complex<float>> transpose = a.conjugateTranspose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, conjugate_transpose_complex_wide) {
    // arrange
    constexpr Matrix<3, 4, std::complex<float>> a = {{{1, 1}, {-2, 3}, {4, 0}, {0, -5}}, {{-3, 2}, {6, -1}, {-7, 4}, {8, 0}}, {{0, 9}, {-10, 5}, {11, -3}, {-12, 0}}};
    constexpr Matrix<4, 3, std::complex<float>> expected = {{{1, -1}, {-3, -2}, {0, -9}}, {{-2, -3}, {6, 1}, {-10, -5}}, {{4, 0}, {-7, -4}, {11, 3}}, {{0, 5}, {8, 0}, {-12, 0}}};
    // act
    const Matrix<4, 3, std::complex<float>> transpose = a.conjugateTranspose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, conjugate_transpose_complex_tall) {
    // arrange
    constexpr Matrix<4, 3, std::complex<float>> a = {{{-1, 2}, {3, 0}, {0, -4}}, {{5, -1}, {-6, 7}, {8, 0}}, {{-9, 0}, {10, -2}, {-11, 5}}, {{0, 12}, {-13, 0}, {14, -3}}};
    constexpr Matrix<3, 4, std::complex<float>> expected = {{{-1, -2}, {5, 1}, {-9, 0}, {0, -12}}, {{3, 0}, {-6, -7}, {10, 2}, {-13, 0}}, {{0, 4}, {8, 0}, {-11, -5}, {14, 3}}};
    // act
    const Matrix<3, 4, std::complex<float>> transpose = a.conjugateTranspose();
    // assert
    ASSERT_TRUE(transpose.equals(expected, 0.001f));
}

TEST(MatrixGeneral, random_real_float) {
    // arrange
    const Matrix<2, 2> a = Matrix<2, 2>::random(0.0f, 4.0f);
    // act / assert
    for (int c = 0; c < 2; c++) {
        for (int r = 0; r < 2; r++) {
            ASSERT_GE(a[c][r], 0.0f);
            ASSERT_LE(a[c][r], 4.0f);
        }
    }
}

TEST(MatrixGeneral, random_real_int) {
    // arrange
    const Matrix<2, 2, int> a = Matrix<2, 2>::random(0, 4);
    // act / assert
    for (int c = 0; c < 2; c++) {
        for (int r = 0; r < 2; r++) {
            ASSERT_GE(a[c][r], 0);
            ASSERT_LE(a[c][r], 4);
        }
    }
}

TEST(MatrixGeneral, random_complex_float) {
    // arrange
    const Matrix<2, 2, std::complex<float>> a = Matrix<2, 2, std::complex<float>>::random(0.0f, 4.0f);
    // act / assert
    for (int c = 0; c < 2; c++) {
        for (int r = 0; r < 2; r++) {
            ASSERT_GE(a[c][r].real(), 0.0f);
            ASSERT_LE(a[c][r].real(), 4.0f);
            ASSERT_GE(a[c][r].imag(), 0.0f);
            ASSERT_LE(a[c][r].imag(), 4.0f);
        }
    }
}

TEST(MatrixGeneral, random_complex_int) {
    // arrange
    const Matrix<2, 2, std::complex<int>> a = Matrix<2, 2, std::complex<int>>::random(0, 4);
    // act / assert
    for (int c = 0; c < 2; c++) {
        for (int r = 0; r < 2; r++) {
            ASSERT_GE(a[c][r].real(), 0);
            ASSERT_LE(a[c][r].real(), 4);
            ASSERT_GE(a[c][r].imag(), 0);
            ASSERT_LE(a[c][r].imag(), 4);
        }
    }
}
