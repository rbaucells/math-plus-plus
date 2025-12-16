#include <gtest/gtest.h>
#include "math++/math.h"

// TEST(MatrixChecks, debugger_tests) {
//     // Integer types
//     constexpr Matrix<3, 3, short> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//     constexpr Matrix<3, 3, unsigned short> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//
//     constexpr Matrix<3, 3, int> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//     constexpr Matrix<3, 3, unsigned int> d = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//
//     constexpr Matrix<3, 3, long> e = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//     constexpr Matrix<3, 3, unsigned long> f = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//
//     constexpr Matrix<3, 3, long long> g = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//     constexpr Matrix<3, 3, unsigned long long> h = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//
//     // Floating-point types
//     constexpr Matrix<3, 3, float> i = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9}};
//     constexpr Matrix<3, 3, double> j = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9}};
//     constexpr Matrix<3, 3, long double> k = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9}};
//
//     // Complex of floating types
//     constexpr Matrix<3, 3, std::complex<float>> l = {
//         {{1.1, 0}, {2.2, 0}, {3.3, 0}},
//         {{4.4, 0}, {5.5, 0}, {6.6, 0}},
//         {{7.7, 0}, {8.8, 0}, {9.9, 0}}
//     };
//
//     constexpr Matrix<3, 3, std::complex<double>> m = {
//         {{1, 0}, {2, 0}, {3, 0}},
//         {{4, 0}, {5, 0}, {6, 0}},
//         {{7, 0}, {8, 0}, {9, 0}}
//     };
//
//     constexpr Matrix<3, 3, std::complex<long double>> n = {
//         {{1, 0}, {2, 0}, {3, 0}},
//         {{4, 0}, {5, 0}, {6, 0}},
//         {{7, 0}, {8, 0}, {9, 0}}
//     };
//
//     // Complex of integer types
//     constexpr Matrix<3, 3, std::complex<short>> o = {
//         {{1, 0}, {2, 0}, {3, 0}},
//         {{4, 0}, {5, 0}, {6, 0}},
//         {{7, 0}, {8, 0}, {9, 0}}
//     };
//
//     constexpr Matrix<3, 3, std::complex<unsigned short>> p = {
//         {{1, 0}, {2, 0}, {3, 0}},
//         {{4, 0}, {5, 0}, {6, 0}},
//         {{7, 0}, {8, 0}, {9, 0}}
//     };
//
//     constexpr Matrix<3, 3, std::complex<int>> q = {
//         {{1, 0}, {2, 0}, {3, 0}},
//         {{4, 0}, {5, 0}, {6, 0}},
//         {{7, 0}, {8, 0}, {9, 0}}
//     };
//
//     constexpr Matrix<3, 3, std::complex<unsigned int>> r = {
//         {{1, 0}, {2, 0}, {3, 0}},
//         {{4, 0}, {5, 0}, {6, 0}},
//         {{7, 0}, {8, 0}, {9, 0}}
//     };
//
//     constexpr Matrix<3, 3, std::complex<long>> s = {
//         {{1, 0}, {2, 0}, {3, 0}},
//         {{4, 0}, {5, 0}, {6, 0}},
//         {{7, 0}, {8, 0}, {9, 0}}
//     };
//
//     constexpr Matrix<3, 3, std::complex<unsigned long>> t = {
//         {{1, 0}, {2, 0}, {3, 0}},
//         {{4, 0}, {5, 0}, {6, 0}},
//         {{7, 0}, {8, 0}, {9, 0}}
//     };
//
//     constexpr Matrix<3, 3, std::complex<long long>> u = {
//         {{1, 0}, {2, 0}, {3, 0}},
//         {{4, 0}, {5, 0}, {6, 0}},
//         {{7, 0}, {8, 0}, {9, 0}}
//     };
//
//     constexpr Matrix<3, 3, std::complex<unsigned long long>> v = {
//         {{1, 0}, {2, 0}, {3, 0}},
//         {{4, 0}, {5, 0}, {6, 0}},
//         {{7, 0}, {8, 0}, {9, 0}}
//     };
// }

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

TEST(MatrixChecks, reduced_row_echelon_square) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_one) {
    // arrange
    constexpr Matrix<3, 3> a = {{4, 0, 0}, {0, 6, 0}, {0, 0, 5}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_pivots) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 0, 0}, {0, 0, 1}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_columns) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 4, 0}, {2, 1, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_square_zero_row) {
    // arrange
    constexpr Matrix<3, 3> a = {{1, 0, 0}, {0, 0, 0}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_tall) {
    // arrange
    constexpr Matrix<3, 4> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_one) {
    // arrange
    constexpr Matrix<3, 4> a = {{4, 0, 0}, {0, 6, 0}, {0, 0, 5}, {0, 0, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_pivots) {
    // arrange
    constexpr Matrix<3, 4> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_columns) {
    // arrange
    constexpr Matrix<3, 4> a = {{1, 4, 0}, {2, 1, 0}, {0, 0, 1}, {0, 7, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_tall_zero_row) {
    // arrange
    constexpr Matrix<3, 4> a = {{1, 0, 0}, {0, 0, 0}, {0, 0, 1}, {0, 0, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, reduced_row_echelon_wide) {
    // arrange
    constexpr Matrix<4, 3> a = {{1, 0, 0, 0}, {0, 1, 0, 1}, {0, 0, 0, 0}};
    // act / assert
    ASSERT_TRUE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_one) {
    // arrange
    constexpr Matrix<4, 3> a = {{4, 0, 0, 0}, {0, 6, 0, 0}, {0, 0, 5, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_pivots) {
    // arrange
    constexpr Matrix<4, 3> a = {{1, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_columns) {
    // arrange
    constexpr Matrix<4, 3> a = {{1, 0, 2, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

TEST(MatrixChecks, not_reduced_row_echelon_wide_zero_row) {
    // arrange
    constexpr Matrix<4, 3> a = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}};
    // act / assert
    ASSERT_FALSE(a.isReducedRowEchelon());
}

// TEST(MatrixChecks, positive_definite) {
//     // arrange
//     constexpr Matrix<2, 2> m = {{2, -1}, {-1, 2}};
//     // act / assert
//     ASSERT_TRUE(m.isPositiveDefinite());
// }
//
// TEST(MatrixChecks, positive_semi_definite) {
//     // arrange
//     constexpr Matrix<2, 2> m = {{1, -1}, {-1, 1}};
//     // act / assert
//     ASSERT_TRUE(m.isPositiveSemiDefinite());
//     ASSERT_FALSE(m.isPositiveDefinite());
//     ASSERT_FALSE(m.isNegativeDefinite());
//     ASSERT_FALSE(m.isNegativeSemiDefinite());
// }
//
// TEST(MatrixChecks, negative_definite) {
//     // arrange
//     constexpr Matrix<2, 2> m = {{-2, -1}, {-1, -2}};
//     // act / assert
//     ASSERT_TRUE(m.isNegativeDefinite());
//     ASSERT_TRUE(m.isNegativeSemiDefinite());
//     ASSERT_FALSE(m.isPositiveDefinite());
//     ASSERT_FALSE(m.isPositiveSemiDefinite());
// }
//
// TEST(MatrixChecks, negative_semi_definite) {
//     // arrange
//     constexpr Matrix<2, 2> m = {{-1, 0}, {0, 0}};
//     // act / assert
//     ASSERT_TRUE(m.isNegativeSemiDefinite());
//     ASSERT_FALSE(m.isNegativeDefinite());
//     ASSERT_FALSE(m.isPositiveDefinite());
//     ASSERT_FALSE(m.isPositiveSemiDefinite());
// }
//
// TEST(MatrixChecks, indefinite) {
//     // arrange
//     constexpr Matrix<2, 2> m = {{1, 2}, {2, -3}};
//     // act / assert
//     ASSERT_FALSE(m.isPositiveDefinite());
//     ASSERT_FALSE(m.isPositiveSemiDefinite());
//     ASSERT_FALSE(m.isNegativeDefinite());
//     ASSERT_FALSE(m.isNegativeSemiDefinite());
// }
