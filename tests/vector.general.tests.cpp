#include "math++/math.h"
#include <gtest/gtest.h>

TEST(VectorGeneral, default_constructor_real) {
    // arrange
    constexpr Vector<3> expected = {0, 0, 0};
    // act
    constexpr Vector<3> a;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorGeneral, default_constructor_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> expected = {{0, 0}, {0, 0}, {0, 0}};
    // act
    constexpr Vector<3, std::complex<float>> a;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorGeneral, initializer_list_constructor_real) {
    // arrange
    Vector<3> expected;
    expected[0] = 0;
    expected[1] = 1;
    expected[2] = 2;
    // act
    constexpr Vector<3> v = {0, 1, 2};
    // assert
    ASSERT_TRUE(v.equals(expected, 0.001f));
}

TEST(VectorGeneral, initializer_list_constructor_complex) {
    // arrange
    Vector<3, std::complex<float>> expected;
    expected[0] = {0, 1};
    expected[1] = {2, 3};
    expected[2] = {4, 5};
    // act
    constexpr Vector<3, std::complex<float>> v = {{0, 1}, {2, 3}, {4, 5}};
    // assert
    ASSERT_TRUE(v.equals(expected, 0.001f));
}

TEST(VectorGeneral, copy_constructor_same_type_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    // act
    const Vector<3> b = a;
    // assert
    ASSERT_TRUE(b.equals(a, 0.001f));
}

TEST(VectorGeneral, copy_constructor_same_type_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const Vector<3, std::complex<float>> b = a;
    // assert
    ASSERT_TRUE(b.equals(a, 0.001f));
}

TEST(VectorGeneral, copy_constructor_diff_type) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    // act
    const Vector<3, std::complex<float>> b = a;
    // assert
    ASSERT_TRUE(b.equals(a, 0.001f));
}

TEST(VectorGeneral, random_real_float) {
    // arrange
    const Vector<2> a = Vector<2>::random(0, 4);
    // act / assert
    for (int i = 0; i < 2; i++) {
        ASSERT_GE(a[i], 0.0f);
        ASSERT_LE(a[i], 4.0f);
    }
}

TEST(VectorGeneral, random_real_int) {
    // arrange
    const Vector<2, int> a = Vector<2>::random(0, 4);
    // act / assert
    for (int i = 0; i < 2; i++) {
        ASSERT_GE(a[i], 0);
        ASSERT_LE(a[i], 4);
    }
}

TEST(VectorGeneral, random_complex_float) {
    // arrange
    const Vector<2, std::complex<float>> a = Vector<2, std::complex<float>>::random(0, 4);
    // act / assert
    for (int i = 0; i < 2; i++) {
        ASSERT_GE(a[i].real(), 0.0f);
        ASSERT_LE(a[i].real(), 4.0f);
        ASSERT_GE(a[i].imag(), 0.0f);
        ASSERT_LE(a[i].imag(), 4.0f);
    }
}

TEST(VectorGeneral, random_complex_int) {
    // arrange
    const Vector<2, std::complex<int>> a = Vector<2, std::complex<int>>::random(0, 4);
    // act / assert
    for (int i = 0; i < 2; i++) {
        ASSERT_GE(a[i].real(), 0);
        ASSERT_LE(a[i].real(), 4);
        ASSERT_GE(a[i].imag(), 0);
        ASSERT_LE(a[i].imag(), 4);
    }
}

TEST(VectorGeneral, conjugate_real) {
    // arrange
    constexpr Vector<3> expected = {1, 2, 3};
    // act
    const Vector<3> conj = expected.conjugate();
    // assert
    ASSERT_TRUE(conj.equals(expected, 0.001f));
}

TEST(VectorGeneral, conjugate_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3, std::complex<float>> expected = {{1, -2}, {3, -4}, {5, -6}};
    // act
    const Vector<3, std::complex<float>> conj = a.conjugate();
    // assert
    ASSERT_TRUE(conj.equals(expected, 0.001f));
}

TEST(VectorGeneral, taxicab_norm_real) {
    // arrange
    constexpr Vector<3> a = {-1, 2, -3};
    constexpr float expected = 6;
    // act
    const float norm = a.taxicabNorm();
    // assert
    ASSERT_TRUE(compare(norm, expected, 0.001f));
}

TEST(VectorGeneral, taxicab_norm_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{-1, 2}, {3, 4}, {5, -6}};
    constexpr float expected = 15.04632f;
    // act
    const float norm = a.taxicabNorm();
    // assert
    ASSERT_TRUE(compare(norm, expected, 0.001f));
}

TEST(VectorGeneral, euclidian_norm_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr float expected = 3.74166f;
    // act
    const float norm = a.euclidianNorm();
    // assert
    ASSERT_TRUE(compare(norm, expected, 0.001f));
}

TEST(VectorGeneral, euclidian_norm_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr float expected = 9.53939f;
    // act
    const float norm = a.euclidianNorm();
    // assert
    ASSERT_TRUE(compare(norm, expected, 0.001f));
}

TEST(VectorGeneral, euclidian_norm_squared_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr float expected = 14;
    // act
    const float norm = a.euclidianNormSquared();
    // assert
    ASSERT_TRUE(compare(norm, expected, 0.001f));
}

TEST(VectorGeneral, euclidian_norm_squared_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr float expected = 91;
    // act
    const float norm = a.euclidianNormSquared();
    // assert
    ASSERT_TRUE(compare(norm, expected, 0.001f));
}

TEST(VectorGeneral, max_norm_real) {
    // arrange
    constexpr Vector<3> a = {1, -3, 2};
    constexpr float expected = 3;
    // act
    const float norm = a.maxNorm();
    // assert
    ASSERT_TRUE(compare(norm, expected, 0.001f));
}

TEST(VectorGeneral, max_norm_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {-5, -6}, {3, 4}};
    constexpr float expected = 7.81025f;
    // act
    const float norm = a.maxNorm();
    // assert
    ASSERT_TRUE(compare(norm, expected, 0.001f));
}