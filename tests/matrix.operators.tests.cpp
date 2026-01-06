#include <gtest/gtest.h>
#include "math++/math.h"

TEST(MatrixOperators, copy_assignment_same_type_real) {
    // arrange
    constexpr Matrix<2, 2> expected = {{1, 2}, {3, 4}};
    // act
    Matrix<2, 2> b;
    b = expected;
    // assert
    ASSERT_TRUE(b.equals(expected, 0.001f));
}

TEST(MatrixOperators, copy_assignment_same_type_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    // act
    Matrix<2, 2, std::complex<float>> b;
    b = expected;
    // assert
    ASSERT_TRUE(b.equals(expected, 0.001f));
}

TEST(MatrixOperators, copy_assignment_diff_type) {
    // arrange
    constexpr Matrix<2, 2> expected = {{1, 2}, {3, 4}};
    // act
    Matrix<2, 2, std::complex<float>> b;
    b = expected;
    // assert
    ASSERT_TRUE(b.equals(expected, 0.001f));
}

TEST(MatrixOperators, equal_same_type_real) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{1, 2}, {3, 4}};
    // act / assert
    ASSERT_TRUE(a == b);
    ASSERT_TRUE(b == a);
    ASSERT_FALSE(a != b);
    ASSERT_FALSE(b != a);
}

TEST(MatrixOperators, not_equal_same_type_real) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 4}, {6, 8}};
    // act / assert
    ASSERT_FALSE(a == b);
    ASSERT_FALSE(b == a);
    ASSERT_TRUE(a != b);
    ASSERT_TRUE(b != a);
}

TEST(MatrixOperators, equal_same_type_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    // act / assert
    ASSERT_TRUE(a == b);
    ASSERT_TRUE(b == a);
    ASSERT_FALSE(a != b);
    ASSERT_FALSE(b != a);
}

TEST(MatrixOperators, not_equal_same_type_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{2, 4}, {6, 8}}, {{10, 12}, {14, 16}}};
    // act / assert
    ASSERT_FALSE(a == b);
    ASSERT_FALSE(b == a);
    ASSERT_TRUE(a != b);
    ASSERT_TRUE(b != a);
}

TEST(MatrixOperators, equal_diff_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{1, 0}, {2, 0}}, {{3, 0}, {4, 0}}};
    // act / assert
    ASSERT_TRUE(a == b);
    ASSERT_TRUE(b == a);
    ASSERT_FALSE(a != b);
    ASSERT_FALSE(b != a);
}

TEST(MatrixOperators, not_equal_diff_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    // act / assert
    ASSERT_FALSE(a == b);
    ASSERT_FALSE(b == a);
    ASSERT_TRUE(a != b);
    ASSERT_TRUE(b != a);
}

TEST(MatrixOperators, addition_same_type_real) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 4}, {6, 8}};
    constexpr Matrix<2, 2> expected = {{3, 6}, {9, 12}};
    // act
    const Matrix<2, 2> ab = a + b;
    const Matrix<2, 2> ba = b + a;
    // assert
    ASSERT_TRUE(ab.equals(expected, 0.001f));
    ASSERT_TRUE(ba.equals(expected, 0.001f));
}

TEST(MatrixOperators, addition_same_type_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{{1, 0}, {0, 2}}, {{3, 1}, {1, 4}}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{0, 1}, {2, 2}}, {{6, 7}, {0, 0}}};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{1, 1}, {2, 4}}, {{9, 8}, {1, 4}}};
    // act
    const Matrix<2, 2, std::complex<float>> ab = a + b;
    const Matrix<2, 2, std::complex<float>> ba = b + a;
    // assert
    ASSERT_TRUE(ab.equals(expected, 0.001f));
    ASSERT_TRUE(ba.equals(expected, 0.001f));
}

TEST(MatrixOperators, addition_diff_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{0, 1}, {2, 2}}, {{6, 7}, {0, 0}}};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{1, 1}, {4, 2}}, {{9, 7}, {4, 0}}};
    // act
    const Matrix<2, 2, std::complex<float>> ab = a + b;
    const Matrix<2, 2, std::complex<float>> ba = b + a;
    // assert
    ASSERT_TRUE(ab.equals(expected, 0.001f));
    ASSERT_TRUE(ba.equals(expected, 0.001f));
}

TEST(MatrixOperators, subtraction_same_type_real) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 4}, {6, 8}};
    constexpr Matrix<2, 2> expectedAb = {{-1, -2}, {-3, -4}};
    constexpr Matrix<2, 2> expectedBa = {{1, 2}, {3, 4}};
    // act
    const Matrix<2, 2> ab = a - b;
    const Matrix<2, 2> ba = b - a;
    // assert
    ASSERT_TRUE(ab.equals(expectedAb, 0.001f));
    ASSERT_TRUE(ba.equals(expectedBa, 0.001f));
}

TEST(MatrixOperators, subtraction_same_type_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{{1, 0}, {0, 2}}, {{3, 1}, {1, 4}}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{0, 1}, {2, 2}}, {{6, 7}, {0, 0}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedAb = {{{1, -1}, {-2, 0}}, {{-3, -6}, {1, 4}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedBa = {{{-1, 1}, {2, 0}}, {{3, 6}, {-1, -4}}};
    // act
    const Matrix<2, 2, std::complex<float>> ab = a - b;
    const Matrix<2, 2, std::complex<float>> ba = b - a;
    // assert
    ASSERT_TRUE(ab.equals(expectedAb, 0.001f));
    ASSERT_TRUE(ba.equals(expectedBa, 0.001f));
}

TEST(MatrixOperators, subtraction_diff_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{0, 1}, {2, 2}}, {{6, 7}, {0, 0}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedAb = {{{1, -1}, {0, -2}}, {{-3, -7}, {4, 0}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedBa = {{{-1, 1}, {0, 2}}, {{3, 7}, {-4, 0}}};
    // act
    const Matrix<2, 2, std::complex<float>> ab = a - b;
    const Matrix<2, 2, std::complex<float>> ba = b - a;
    // assert
    ASSERT_TRUE(ab.equals(expectedAb, 0.001f));
    ASSERT_TRUE(ba.equals(expectedBa, 0.001f));
}

TEST(MatrixOperators, multiplication_same_type_real) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 4}, {6, 8}};
    constexpr Matrix<2, 2> expected = {{14, 20}, {30, 44}};
    // act
    const Matrix<2, 2> ab = a * b;
    const Matrix<2, 2> ba = b * a;
    // assert
    ASSERT_TRUE(ab.equals(expected, 0.001f));
    ASSERT_TRUE(ba.equals(expected, 0.001f));
}

TEST(MatrixOperators, multiplication_same_type_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{{1, 0}, {0, 2}}, {{3, 1}, {1, 4}}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{0, 1}, {2, 2}}, {{6, 7}, {0, 0}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedAb = {{{-14, 13}, {2, 2}}, {{-23, 34}, {4, 8}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedBa = {{{4, 9}, {-8, 10}}, {{6, 7}, {-14, 12}}};
    // act
    const Matrix<2, 2, std::complex<float>> ab = a * b;
    const Matrix<2, 2, std::complex<float>> ba = b * a;
    // assert
    ASSERT_TRUE(ab.equals(expectedAb, 0.001f));
    ASSERT_TRUE(ba.equals(expectedBa, 0.001f));
}

TEST(MatrixOperators, multiplication_diff_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{0, 1}, {2, 2}}, {{6, 7}, {0, 0}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedAb = {{{12, 15}, {2, 2}}, {{24, 31}, {6, 6}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedBa = {{{6, 7}, {8, 10}}, {{6, 7}, {12, 14}}};
    // act
    const Matrix<2, 2, std::complex<float>> ab = a * b;
    const Matrix<2, 2, std::complex<float>> ba = b * a;
    // assert
    ASSERT_TRUE(ab.equals(expectedAb, 0.001f));
    ASSERT_TRUE(ba.equals(expectedBa, 0.001f));
}

TEST(MatrixOperators, scalar_multiplication_same_type_real) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr float s = 2.0f;
    constexpr Matrix<2, 2> expected = {{2, 4}, {6, 8}};
    // act
    const Matrix<2, 2> as = a * s;
    const Matrix<2, 2> sa = s * a;
    // assert
    ASSERT_TRUE(as.equals(expected, 0.001f));
    ASSERT_TRUE(sa.equals(expected, 0.001f));
}

TEST(MatrixOperators, scalar_multiplication_same_type_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{{1, 0}, {0, 2}}, {{3, 1}, {1, 4}}};
    constexpr std::complex<float> s = {2, 1};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{2, 1}, {-2, 4}}, {{5, 5}, {-2, 9}}};
    // act
    const Matrix<2, 2, std::complex<float>> as = a * s;
    const Matrix<2, 2, std::complex<float>> sa = s * a;
    // assert
    ASSERT_TRUE(as.equals(expected, 0.001f));
    ASSERT_TRUE(sa.equals(expected, 0.001f));
}

TEST(MatrixOperators, scalar_multiplication_diff_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr float c = 2;
    constexpr std::complex<float> d = {2, 3};
    constexpr Matrix<2, 2, std::complex<float>> expectedAd = {{{2, 3}, {4, 6}}, {{6, 9}, {8, 12}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedBc = {{{2, 4}, {6, 8}}, {{10, 12}, {14, 16}}};
    // act
    const Matrix<2, 2, std::complex<float>> ad = a * d;
    const Matrix<2, 2, std::complex<float>> da = d * a;
    const Matrix<2, 2, std::complex<float>> bc = b * c;
    const Matrix<2, 2, std::complex<float>> cd = c * b;
    // assert
    ASSERT_TRUE(ad.equals(expectedAd, 0.001f));
    ASSERT_TRUE(da.equals(expectedAd, 0.001f));
    ASSERT_TRUE(bc.equals(expectedBc, 0.001f));
    ASSERT_TRUE(cd.equals(expectedBc, 0.001f));
}

TEST(MatrixOperators, scalar_division_same_type_real) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr float s = 2.0f;
    constexpr Matrix<2, 2> expected = {{0.5f, 1.0f}, {1.5f, 2.0f}};
    // act
    const Matrix<2, 2> as = a / s;
    // assert
    ASSERT_TRUE(as.equals(expected, 0.001f));
}

TEST(MatrixOperators, scalar_division_same_type_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{{1, 0}, {0, 2}}, {{3, 1}, {1, 4}}};
    constexpr std::complex<float> s = {2, 0};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{0.5f, 0}, {0, 1}}, {{1.5f, 0.5f}, {0.5f, 2}}};
    // act
    const Matrix<2, 2, std::complex<float>> as = a / s;
    // assert
    ASSERT_TRUE(as.equals(expected, 0.001f));
}

TEST(MatrixOperators, scalar_division_diff_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr float c = 2;
    constexpr std::complex<float> d = {2, 3};
    constexpr Matrix<2, 2, std::complex<float>> expectedAd = {{{0.15385f, -0.23077f}, {0.30769f, -0.46154f}}, {{0.46154f, -0.69231f}, {0.61538f, -0.92308f}}};
    constexpr Matrix<2, 2, std::complex<float>> expectedBc = {{{0.5f, 1}, {1.5f, 2}}, {{2.5f, 3}, {3.5f, 4}}};
    // act
    const Matrix<2, 2, std::complex<float>> ad = a / d;
    const Matrix<2, 2, std::complex<float>> bc = b / c;
    // assert
    ASSERT_TRUE(ad.equals(expectedAd, 0.001f));
    ASSERT_TRUE(bc.equals(expectedBc, 0.001f));
}

TEST(MatrixOperators, vector_multiplication_same_type_real) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Vector<2> b = {1, 2};
    constexpr Vector<2> expected = {5, 11};
    // act
    const Vector<2> v = a * b;
    // assert
    ASSERT_TRUE(v.equals(expected, 0.001f));
}

TEST(MatrixOperators, vector_multiplication_same_type_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{{1, 0}, {0, 2}}, {{3, 1}, {1, 4}}};
    constexpr Vector<2, std::complex<float>> b = {{1, 0}, {2, 0}};
    constexpr Vector<2, std::complex<float>> expected = {{1, 4}, {5, 9}};
    // act
    const Vector<2, std::complex<float>> v = a * b;
    // assert
    ASSERT_TRUE(v.equals(expected, 0.001f));
}

TEST(MatrixOperators, vector_multiplication_diff_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr Vector<2> c = {1, 2};
    constexpr Vector<2, std::complex<float>> d = {{1,2}, {3, 4}};
    constexpr Vector<2, std::complex<float>> expectedAd = {{7, 10}, {15, 22}};
    constexpr Vector<2, std::complex<float>> expectedBc = {{7, 10}, {19, 22}};
    // act
    const Vector<2, std::complex<float>> ad = a * d;
    const Vector<2, std::complex<float>> bc = b * c;
    // assert
    ASSERT_TRUE(ad.equals(expectedAd, 0.001f));
    ASSERT_TRUE(bc.equals(expectedBc, 0.001f));
}

TEST(MatrixOperators, addition_equals_same_type_real) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 4}, {6, 8}};
    constexpr Matrix<2, 2> expected = {{3, 6}, {9, 12}};
    // act
    a += b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, addition_equals_same_type_complex) {
    // arrange
    Matrix<2, 2, std::complex<float>> a = {{{1, 0}, {0, 2}}, {{3, 1}, {1, 4}}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{0, 1}, {2, 2}}, {{6, 7}, {0, 0}}};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{1, 1}, {2, 4}}, {{9, 8}, {1, 4}}};
    // act
    a += b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, addition_equals_diff_type) {
    // arrange
    Matrix<2, 2, std::complex<float>> a = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr Matrix<2, 2> b = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{2, 2}, {5, 4}}, {{8, 6}, {11, 8}}};
    // act
    a += b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, subtraction_equals_same_type_real) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 4}, {6, 8}};
    constexpr Matrix<2, 2> expected = {{-1, -2}, {-3, -4}};
    // act
    a -= b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, subtraction_equals_same_type_complex) {
    // arrange
    Matrix<2, 2, std::complex<float>> a = {{{1, 0}, {0, 2}}, {{3, 1}, {1, 4}}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{0, 1}, {2, 2}}, {{6, 7}, {0, 0}}};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{1, -1}, {-2, 0}}, {{-3, -6}, {1, 4}}};
    // act
    a -= b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, subtraction_equals_diff_type) {
    // arrange
    Matrix<2, 2, std::complex<float>> a = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr Matrix<2, 2> b = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{0, 2}, {1, 4}}, {{2, 6}, {3, 8}}};
    // act
    a -= b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, scalar_multiplication_equals_same_type_real) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr float s = 2.0f;
    constexpr Matrix<2, 2> expected = {{2, 4}, {6, 8}};
    // act
    a *= s;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, scalar_multiplication_equals_same_type_complex) {
    // arrange
    Matrix<2, 2, std::complex<float>> a = {{{1, 0}, {0, 2}}, {{3, 1}, {1, 4}}};
    constexpr std::complex<float> s = {2, 1};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{2, 1}, {-2, 4}}, {{5, 5}, {-2, 9}}};
    // act
    a *= s;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, scalar_multiplication_equals_diff_type) {
    // arrange
    Matrix<2, 2, std::complex<float>> a = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr float s = 2.0f;
    constexpr Matrix<2, 2, std::complex<float>> expected ={{{2, 4}, {6, 8}}, {{10, 12}, {14, 16}}};
    // act
    a *= s;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, scalar_division_equals_same_type_real) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr float s = 2.0f;
    constexpr Matrix<2, 2> expected = {{0.5f, 1.0f}, {1.5f, 2.0f}};
    // act
    a /= s;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, scalar_division_equals_same_type_complex) {
    // arrange
    Matrix<2, 2, std::complex<float>> a = {{{1, 0}, {0, 2}}, {{3, 1}, {1, 4}}};
    constexpr std::complex<float> s = {2, 0};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{0.5f, 0}, {0, 1}}, {{1.5f, 0.5f}, {0.5f, 2}}};
    // act
    a /= s;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, scalar_division_equals_diff_type) {
    // arrange
    Matrix<2, 2, std::complex<float>> a = {{{2, 4}, {6, 8}}, {{10, 12}, {14, 16}}};
    constexpr float scalar = 2.0f;
    constexpr Matrix<2, 2, std::complex<float>> expected ={{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    // act
    a /= scalar;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(MatrixOperators, const_indexing_operator_real) {
    // arrange
    constexpr Matrix<2, 2> m = {{1, 2}, {3, 4}};
    // act / assert
    ASSERT_TRUE(compare(m[0][0], 1));
    ASSERT_TRUE(compare(m[1][0], 2));
    ASSERT_TRUE(compare(m[0][1], 3));
    ASSERT_TRUE(compare(m[1][1], 4));
}

TEST(MatrixOperators, indexing_operator_real) {
    // arrange
    Matrix<2, 2> m = {{1, 2}, {3, 4}};
    // act / assert
    ASSERT_TRUE(compare(m[0][0], 1));
    ASSERT_TRUE(compare(m[1][0], 2));
    ASSERT_TRUE(compare(m[0][1], 3));
    ASSERT_TRUE(compare(m[1][1], 4));
}

TEST(MatrixOperators, const_indexing_operator_complex) {
    // arrange
    const Matrix<2, 2, std::complex<float>> m = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    // act / assert
    ASSERT_TRUE(compare(m[0][0], std::complex<float>(1, 2)));
    ASSERT_TRUE(compare(m[1][0], std::complex<float>(3, 4)));
    ASSERT_TRUE(compare(m[0][1], std::complex<float>(5, 6)));
    ASSERT_TRUE(compare(m[1][1], std::complex<float>(7, 8)));
}

TEST(MatrixOperators, indexing_operator_complex) {
    // arrange
    Matrix<2, 2, std::complex<float>> m = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    // act / assert
    ASSERT_TRUE(compare(m[0][0], std::complex<float>(1, 2)));
    ASSERT_TRUE(compare(m[1][0], std::complex<float>(3, 4)));
    ASSERT_TRUE(compare(m[0][1], std::complex<float>(5, 6)));
    ASSERT_TRUE(compare(m[1][1], std::complex<float>(7, 8)));
}

TEST(MatrixOperators, unary_minus_real) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> expected = {{-1, -2}, {-3, -4}};
    // act
    const Matrix<2, 2> b = -a;
    // assert
    ASSERT_TRUE(b.equals(expected, 0.001f));
}

TEST(MatrixOperators, unary_minus_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{-1, -2}, {-3, -4}}, {{-5, -6}, {-7, -8}}};
    // act
    const Matrix<2, 2, std::complex<float>> b = -a;
    // assert
    ASSERT_TRUE(b.equals(expected, 0.001f));
}

TEST(MatrixOperators, const_to_pointer_real) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    // act
    const float* data = static_cast<const float*>(a);
    // assert
    ASSERT_TRUE(compare(data[0], 1, 0.001f));
    ASSERT_TRUE(compare(data[1], 3, 0.001f));
    ASSERT_TRUE(compare(data[2], 2, 0.001f));
    ASSERT_TRUE(compare(data[3], 4, 0.001f));
}

TEST(MatrixOperators, to_pointer_real) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    // act
    float* data = static_cast<float*>(a);
    // assert
    ASSERT_TRUE(compare(data[0], 1, 0.001f));
    ASSERT_TRUE(compare(data[1], 3, 0.001f));
    ASSERT_TRUE(compare(data[2], 2, 0.001f));
    ASSERT_TRUE(compare(data[3], 4, 0.001f));
}

TEST(MatrixOperators, const_to_pointer_complex) {
    // arrange
    const Matrix<2, 2, std::complex<float>> a = {{{1, 1}, {2, 2}}, {{3, 3}, {4, 4}}};
    // act
    const std::complex<float>* data = static_cast<const std::complex<float>*>(a);
    // assert
    ASSERT_TRUE(compare(data[0], std::complex<float>(1, 1), 0.001f));
    ASSERT_TRUE(compare(data[1], std::complex<float>(3, 3), 0.001f));
    ASSERT_TRUE(compare(data[2], std::complex<float>(2, 2), 0.001f));
    ASSERT_TRUE(compare(data[3], std::complex<float>(4, 4), 0.001f));
}

TEST(MatrixOperators, to_pointer_complex) {
    // arrange
    Matrix<2, 2, std::complex<float>> a = {{{1, 1}, {2, 2}}, {{3, 3}, {4, 4}}};
    // act
    std::complex<float>* data = static_cast<std::complex<float>*>(a);
    // assert
    ASSERT_TRUE(compare(data[0], std::complex<float>(1, 1), 0.001f));
    ASSERT_TRUE(compare(data[1], std::complex<float>(3, 3), 0.001f));
    ASSERT_TRUE(compare(data[2], std::complex<float>(2, 2), 0.001f));
    ASSERT_TRUE(compare(data[3], std::complex<float>(4, 4), 0.001f));
}