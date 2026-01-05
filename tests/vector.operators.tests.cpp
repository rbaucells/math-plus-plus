#include "math++/math.h"
#include <gtest/gtest.h>

TEST(VectorOperators, addition_same_type_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3> b = {2, 4, 6};
    constexpr Vector<3> expected = {3, 6, 9};
    // act
    const Vector<3> ab = a + b;
    const Vector<3> ba = b + a;
    // assert
    ASSERT_TRUE(ab.equals(expected, 0.001f));
    ASSERT_TRUE(ba.equals(expected, 0.001f));
}

TEST(VectorOperators, addition_same_type_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3, std::complex<float>> b = {{2, 4}, {6, 8}, {10, 12}};
    constexpr Vector<3, std::complex<float>> expected = {{3, 6}, {9, 12}, {15, 18}};
    // act
    const Vector<3, std::complex<float>> ab = a + b;
    const Vector<3, std::complex<float>> ba = b + a;
    // assert
    ASSERT_TRUE(ab.equals(expected, 0.001f));
    ASSERT_TRUE(ba.equals(expected, 0.001f));
}

TEST(VectorOperators, addition_diff_type) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3, std::complex<float>> b = {{2, 4}, {6, 8}, {10, 12}};
    constexpr Vector<3, std::complex<float>> expected = {{3, 4}, {8, 8}, {13, 12}};
    // act
    const Vector<3, std::complex<float>> ab = a + b;
    const Vector<3, std::complex<float>> ba = b + a;
    // assert
    ASSERT_TRUE(ab.equals(expected, 0.001f));
    ASSERT_TRUE(ba.equals(expected, 0.001f));
}

TEST(VectorOperators, subtraction_same_type_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3> b = {2, 4, 6};
    constexpr Vector<3> expectedAb = {-1, -2, -3};
    constexpr Vector<3> expectedBa = {1, 2, 3};
    // act
    const Vector<3> ab = a - b;
    const Vector<3> ba = b - a;
    // assert
    ASSERT_TRUE(ab.equals(expectedAb, 0.001f));
    ASSERT_TRUE(ba.equals(expectedBa, 0.001f));
}

TEST(VectorOperators, subtraction_same_type_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a  = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3, std::complex<float>> b  = {{2, 4}, {6, 8}, {10, 12}};
    constexpr Vector<3, std::complex<float>> expectedAb = {{-1, -2}, {-3, -4}, {-5, -6}};
    constexpr Vector<3, std::complex<float>> expectedBa = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const Vector<3, std::complex<float>> ab = a - b;
    const Vector<3, std::complex<float>> ba = b - a;
    // assert
    ASSERT_TRUE(ab.equals(expectedAb, 0.001f));
    ASSERT_TRUE(ba.equals(expectedBa, 0.001f));
}

TEST(VectorOperators, subtraction_diff_type) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3, std::complex<float>> b  = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3, std::complex<float>> expectedAb = {{0, -2}, {-1, -4}, {-2, -6}};
    constexpr Vector<3, std::complex<float>> expectedBa = {{0, 2}, {1, 4}, {2, 6}};
    // act
    const Vector<3, std::complex<float>> ab = a - b;
    const Vector<3, std::complex<float>> ba = b - a;
    // assert
    ASSERT_TRUE(ab.equals(expectedAb, 0.001f));
    ASSERT_TRUE(ba.equals(expectedBa, 0.001f));
}

TEST(VectorOperators, multiplication_same_type_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr float b = 2.0f;
    constexpr Vector<3> expected = {2, 4, 6};
    // act
    const Vector<3> ab = a * b;
    const Vector<3> ba = b * a;
    // assert
    ASSERT_TRUE(ab.equals(expected, 0.001f));
    ASSERT_TRUE(ba.equals(expected, 0.001f));
}

TEST(VectorOperators, multiplication_same_type_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr std::complex<float> b = {2, 3};
    constexpr Vector<3, std::complex<float>> expected = {{-4, 7}, {-6, 17}, {-8, 27}};
    // act
    const Vector<3, std::complex<float>> ab = a * b;
    const Vector<3, std::complex<float>> ba = b * a;
    // assert
    ASSERT_TRUE(ab.equals(expected, 0.001f));
    ASSERT_TRUE(ba.equals(expected, 0.001f));
}

TEST(VectorOperators, multiplication_diff_type) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3, std::complex<float>> b = {{1, 2}, {3, 4}, {5, 6}};
    constexpr float c = 2.0f;
    constexpr std::complex<float> d = {2, 3};
    constexpr Vector<3, std::complex<float>> expectedAd = {{2, 3}, {4, 6}, {6, 9}};
    constexpr Vector<3, std::complex<float>> expectedBc = {{2, 4}, {6, 8}, {10, 12}};
    // act
    const Vector<3, std::complex<float>> ad = a * d;
    const Vector<3, std::complex<float>> da = d * a;
    const Vector<3, std::complex<float>> bc = b * c;
    const Vector<3, std::complex<float>> cb = c * b;
    // assert
    ASSERT_TRUE(ad.equals(expectedAd, 0.001f));
    ASSERT_TRUE(da.equals(expectedAd, 0.001f));
    ASSERT_TRUE(bc.equals(expectedBc, 0.001f));
    ASSERT_TRUE(cb.equals(expectedBc, 0.001f));
}

TEST(VectorOperators, division_same_type_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr float b = 2;
    constexpr Vector<3> expected = {0.5f, 1, 1.5f};
    // act
    const Vector<3> ab = a / b;
    // assert
    ASSERT_TRUE(ab.equals(expected, 0.001f));
}

TEST(VectorOperators, division_same_type_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr std::complex<float> b = {2, 3};
    constexpr Vector<3, std::complex<float>> expected = {{0.61538f, 0.07692f}, {1.38462f, -0.07692f}, {2.15385f, -0.23077f}};
    // act
    const Vector<3, std::complex<float>> ab = a / b;
    // assert
    ASSERT_TRUE(ab.equals(expected, 0.001f));
}

TEST(VectorOperators, division_diff_type) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3, std::complex<float>> b = {{1, 2}, {3, 4}, {5, 6}};
    constexpr float c = 2;
    constexpr std::complex<float> d = {2, 3};
    constexpr Vector<3, std::complex<float>> expectedAd = {{0.15385f, -0.23077f}, {0.30769f, -0.46154f}, {0.46154f, -0.69231f}};
    constexpr Vector<3, std::complex<float>> expectedBc = {{0.5f, 1}, {1.5f, 2}, {2.5f, 3}};
    // act
    const Vector<3, std::complex<float>> ad = a / d;
    const Vector<3, std::complex<float>> bc = b / c;
    // assert
    ASSERT_TRUE(ad.equals(expectedAd, 0.001f));
    ASSERT_TRUE(bc.equals(expectedBc, 0.001f));
}