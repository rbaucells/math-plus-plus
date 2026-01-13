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

TEST(VectorGeneral, normalized_real) {
    // arrange
    constexpr Vector<3> a = {2, 2, 2};
    constexpr Vector<3> expected = {0.57735f, 0.57735f, 0.57735f};
    // act
    const Vector<3> normalized = a.normalized();
    // assert
    ASSERT_TRUE(normalized.equals(expected, 0.001f));
}

TEST(VectorGeneral, normalized_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3, std::complex<float>> expected = {{0.10483f, 0.20966f}, {0.31449f, 0.41931f}, {0.52414f, 0.62897f}};
    // act
    const Vector<3, std::complex<float>> normalized = a.normalized();
    // assert
    ASSERT_TRUE(normalized.equals(expected, 0.001f));
}

TEST(VectorGeneral, euclidian_angle_degrees_real) {
    // arrange
    constexpr Vector<3> a = {1, 0, 0};
    constexpr Vector<3> b = {0, 1, 0};
    constexpr float expected = 90;
    // act
    const float angleAb = a.euclidianAngle(b, RotationType::degrees);
    const float angleBa = b.euclidianAngle(a, RotationType::degrees);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, euclidian_angle_radians_real) {
    // arrange
    constexpr Vector<3> a = {1, 0, 0};
    constexpr Vector<3> b = {0, 1, 0};
    constexpr float expected = M_PI_2;
    // act
    const float angleAb = a.euclidianAngle(b, RotationType::radians);
    const float angleBa = b.euclidianAngle(a, RotationType::radians);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, euclidian_angle_radians_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr float expected = 0.74758f;
    // act
    const float angleAb = a.euclidianAngle(b, RotationType::radians);
    const float angleBa = b.euclidianAngle(a, RotationType::radians);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, euclidian_angle_angle_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr float expected = 42.83343f;
    // act
    const float angleAb = a.euclidianAngle(b, RotationType::degrees);
    const float angleBa = b.euclidianAngle(a, RotationType::degrees);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, complex_angle_degrees_real) {
    // arrange
    constexpr Vector<3> a = {1, 0, 0};
    constexpr Vector<3> b = {0, 1, 0};
    constexpr float expected = 90;
    // act
    const float angleAb = a.complexAngle(b, Vector<3>::neither, RotationType::degrees);
    const float angleBa = b.complexAngle(a, Vector<3>::neither, RotationType::degrees);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, complex_angle_radians_real) {
    // arrange
    constexpr Vector<3> a = {1, 0, 0};
    constexpr Vector<3> b = {0, 1, 0};
    constexpr float expected = M_PI_2;
    // act
    const float angleAb = a.complexAngle(b, Vector<3>::neither, RotationType::radians);
    const float angleBa = b.complexAngle(a, Vector<3>::neither, RotationType::radians);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, complex_angle_radians_complex_first) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr std::complex<float> expectedAb = {0.76677f, 0.19101f};
    constexpr std::complex<float> expectedBa = {0.76677f, -0.19101f};
    // act
    const std::complex<float> angleAb = a.complexAngle(b, Vector<3, std::complex<float>>::first_argument, RotationType::radians);
    const std::complex<float> angleBa = b.complexAngle(a, Vector<3, std::complex<float>>::first_argument, RotationType::radians);
    // assert
    ASSERT_TRUE(compare(angleAb, expectedAb, 0.001f));
    ASSERT_TRUE(compare(angleBa, expectedBa, 0.001f));
}

TEST(VectorGeneral, complex_angle_degrees_complex_first) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr std::complex<float> expectedAb = {43.93268f, 10.94407f};
    constexpr std::complex<float> expectedBa = {43.93268f, -10.94407f};
    // act
    const std::complex<float> angleAb = a.complexAngle(b, Vector<3, std::complex<float>>::first_argument, RotationType::degrees);
    const std::complex<float> angleBa = b.complexAngle(a, Vector<3, std::complex<float>>::first_argument, RotationType::degrees);
    // assert
    ASSERT_TRUE(compare(angleAb, expectedAb, 0.001f));
    ASSERT_TRUE(compare(angleBa, expectedBa, 0.001f));
}

TEST(VectorGeneral, complex_angle_radians_complex_neither) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr std::complex<float> expected = {1.37685f, -0.26854f};
    // act
    const std::complex<float> angleAb = a.complexAngle(b, Vector<3, std::complex<float>>::neither, RotationType::radians);
    const std::complex<float> angleBa = b.complexAngle(a, Vector<3, std::complex<float>>::neither, RotationType::radians);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, complex_angle_degrees_complex_neither) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr std::complex<float> expected = {78.87213f, -15.38605f};
    // act
    const std::complex<float> angleAb = a.complexAngle(b, Vector<3, std::complex<float>>::neither, RotationType::degrees);
    const std::complex<float> angleBa = b.complexAngle(a, Vector<3, std::complex<float>>::neither, RotationType::degrees);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, complex_angle_radians_complex_second) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr std::complex<float> expectedAb = {0.76677f, -0.19101f};
    constexpr std::complex<float> expectedBa = {0.76677f, 0.19101f};
    // act
    const std::complex<float> angleAb = a.complexAngle(b, Vector<3, std::complex<float>>::second_argument, RotationType::radians);
    const std::complex<float> angleBa = b.complexAngle(a, Vector<3, std::complex<float>>::second_argument, RotationType::radians);
    // assert
    ASSERT_TRUE(compare(angleAb, expectedAb, 0.001f));
    ASSERT_TRUE(compare(angleBa, expectedBa, 0.001f));
}

TEST(VectorGeneral, complex_angle_degrees_complex_second) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr std::complex<float> expectedAb = {43.93268f, -10.94407f};
    constexpr std::complex<float> expectedBa = {43.93268f, 10.94407f};
    // act
    const std::complex<float> angleAb = a.complexAngle(b, Vector<3, std::complex<float>>::second_argument, RotationType::degrees);
    const std::complex<float> angleBa = b.complexAngle(a, Vector<3, std::complex<float>>::second_argument, RotationType::degrees);
    // assert
    ASSERT_TRUE(compare(angleAb, expectedAb, 0.001f));
    ASSERT_TRUE(compare(angleBa, expectedBa, 0.001f));
}

TEST(VectorGeneral, hermitian_angle_degrees_real) {
    // arrange
    constexpr Vector<3> a = {1, 0, 0};
    constexpr Vector<3> b = {0, 1, 0};
    constexpr float expected = 90;
    // act
    const float angleAb = a.hermitianAngle(b, Vector<3>::neither, RotationType::degrees);
    const float angleBa = b.hermitianAngle(a, Vector<3>::neither, RotationType::degrees);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, hermitian_angle_radians_real) {
    // arrange
    constexpr Vector<3> a = {1, 0, 0};
    constexpr Vector<3> b = {0, 1, 0};
    constexpr float expected = M_PI_2;
    // act
    const float angleAb = a.hermitianAngle(b, Vector<3>::neither, RotationType::radians);
    const float angleBa = b.hermitianAngle(a, Vector<3>::neither, RotationType::radians);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, hermitian_angle_radians_complex_first) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr float expected = 0.72973f;
    // act
    const float angleAb = a.hermitianAngle(b, Vector<3, std::complex<float>>::first_argument, RotationType::radians);
    const float angleBa = b.hermitianAngle(a, Vector<3, std::complex<float>>::first_argument, RotationType::radians);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, hermitian_angle_degrees_complex_first) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr float expected = 41.81031f;
    // act
    const float angleAb = a.hermitianAngle(b, Vector<3, std::complex<float>>::first_argument, RotationType::degrees);
    const float angleBa = b.hermitianAngle(a, Vector<3, std::complex<float>>::first_argument, RotationType::degrees);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, hermitian_angle_radians_complex_neither) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr float expected = 1.23096f;
    // act
    const float angleAb = a.hermitianAngle(b, Vector<3, std::complex<float>>::neither, RotationType::radians);
    const float angleBa = b.hermitianAngle(a, Vector<3, std::complex<float>>::neither, RotationType::radians);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, hermitian_angle_degrees_complex_neither) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr float expected = 70.52878f;
    // act
    const float angleAb = a.hermitianAngle(b, Vector<3, std::complex<float>>::neither, RotationType::degrees);
    const float angleBa = b.hermitianAngle(a, Vector<3, std::complex<float>>::neither, RotationType::degrees);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, hermitian_angle_radians_complex_second) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr float expected = 0.72973f;
    // act
    const float angleAb = a.hermitianAngle(b, Vector<3, std::complex<float>>::second_argument, RotationType::radians);
    const float angleBa = b.hermitianAngle(a, Vector<3, std::complex<float>>::second_argument, RotationType::radians);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, hermitian_angle_degrees_complex_second) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr float expected = 41.81031f;
    // act
    const float angleAb = a.hermitianAngle(b, Vector<3, std::complex<float>>::second_argument, RotationType::degrees);
    const float angleBa = b.hermitianAngle(a, Vector<3, std::complex<float>>::second_argument, RotationType::degrees);
    // assert
    ASSERT_TRUE(compare(angleAb, expected, 0.001f));
    ASSERT_TRUE(compare(angleBa, expected, 0.001f));
}

TEST(VectorGeneral, to_real) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<6> expected = {1, 2, 3, 4, 5, 6};
    // act
    const Vector<6> real = a.toReal();
    // assert
    ASSERT_TRUE(real.equals(expected, 0.001f));
}

TEST(VectorGeneral, cross_product_matrix_real) {
    // arrange
    constexpr Vector<3> v = {1, 2, 3};
    constexpr Matrix<3, 3> expected = {{0, -3, 2}, {3, 0, -1}, {-2, 1, 0}};
    // act
    const Matrix<3, 3> m = v.crossProductMatrix();
    // assert
    ASSERT_TRUE(m.equals(expected, 0.001f));
}

TEST(VectorGeneral, cross_product_matrix_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> v = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Matrix<3, 3, std::complex<float>> expected = {{{0, 0}, {-5, -6}, {3, 4}}, {{5, 6}, {0, 0}, {-1, -2}}, {{-3, -4}, {1, 2}, {0, 0,}}};
    // act
    const Matrix<3, 3, std::complex<float>> m = v.crossProductMatrix();
    // assert
    ASSERT_TRUE(m.equals(expected, 0.001f));
}

TEST(VectorGeneral, cross_product_same_type_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3> b = {4, 5, 6};
    constexpr Vector<3> expectedAb = {-3, 6, -3};
    constexpr Vector<3> expectedBa = {3, -6, 3};
    // act
    const Vector<3> ab = a.cross(b);
    const Vector<3> ba = b.cross(a);
    // assert
    ASSERT_TRUE(ab.equals(expectedAb, 0.001f));
    ASSERT_TRUE(ba.equals(expectedBa, 0.001f));
}

TEST(VectorGeneral, cross_product_same_type_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3, std::complex<float>> b = {{7, 8}, {9, 10}, {11, 12}};
    constexpr Vector<3, std::complex<float>> expectedAb = {{0, -24}, {0, 48}, {0, -24}};
    constexpr Vector<3, std::complex<float>> expectedBa = {{0, 24}, {0, -48}, {0, 24}};
    // act
    const Vector<3, std::complex<float>> ab = a.cross(b);
    const Vector<3, std::complex<float>> ba = b.cross(a);
    // assert
    ASSERT_TRUE(ab.equals(expectedAb, 0.001f));
    ASSERT_TRUE(ba.equals(expectedBa, 0.001f));
}

TEST(VectorGeneral, cross_product_diff_type) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3, std::complex<float>> b = {{7, 8}, {9, 10}, {11, 12}};
    constexpr Vector<3, std::complex<float>> expectedAb = {{-5, -6}, {10, 12}, {-5, -6}};
    constexpr Vector<3, std::complex<float>> expectedBa = {{5, 6}, {-10, -12}, {5, 6}};
    // act
    const Vector<3, std::complex<float>> ab = a.cross(b);
    const Vector<3, std::complex<float>> ba = b.cross(a);
    // assert
    ASSERT_TRUE(ab.equals(expectedAb, 0.001f));
    ASSERT_TRUE(ba.equals(expectedBa, 0.001f));
}

TEST(VectorGeneral, dot_product_same_type_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3> b = {4, 5, 6};
    constexpr float expected = 32.0f;
    // act
    const float ab = a.dot(b);
    const float ba = b.dot(a);
    // assert
    ASSERT_TRUE(compare(ab, expected, 0.001f));
    ASSERT_TRUE(compare(ba, expected, 0.001f));
}

TEST(VectorGeneral, dot_product_same_type_complex_first) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr std::complex<float> expectedAb = {11, -2};
    constexpr std::complex<float> expectedBa = {11, 2};
    // act
    const std::complex<float> ab = a.dot(b, Vector<3, std::complex<float>>::first_argument);
    const std::complex<float> ba = b.dot(a, Vector<3, std::complex<float>>::first_argument);
    // assert
    ASSERT_TRUE(compare(ab, expectedAb, 0.001f));
    ASSERT_TRUE(compare(ba, expectedBa, 0.001f));
}

TEST(VectorGeneral, dot_product_same_type_complex_neither) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr std::complex<float> expected = {3, 4};
    // act
    const std::complex<float> ab = a.dot(b, Vector<3, std::complex<float>>::neither);
    const std::complex<float> ba = b.dot(a, Vector<3, std::complex<float>>::neither);
    // assert
    ASSERT_TRUE(compare(ab, expected, 0.001f));
    ASSERT_TRUE(compare(ba, expected, 0.001f));
}

TEST(VectorGeneral, dot_product_same_type_complex_second) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    constexpr Vector<3, std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr std::complex<float> expectedAb = {11, 2};
    constexpr std::complex<float> expectedBa = {11, -2};
    // act
    const std::complex<float> ab = a.dot(b, Vector<3, std::complex<float>>::second_argument);
    const std::complex<float> ba = b.dot(a, Vector<3, std::complex<float>>::second_argument);
    // assert
    ASSERT_TRUE(compare(ab, expectedAb, 0.001f));
    ASSERT_TRUE(compare(ba, expectedBa, 0.001f));
}

TEST(VectorGeneral, dot_product_diff_type_first) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3, std::complex<float>> b = {{4, 1}, {5, 0}, {6, -1}};
    constexpr std::complex<float> expectedAb = {32, -2};
    constexpr std::complex<float> expectedBa = {32, 2};
    // act
    const std::complex<float> ab = a.dot(b, Vector<3>::first_argument);
    const std::complex<float> ba = b.dot(a, Vector<3, std::complex<float>>::first_argument);
    // assert
    ASSERT_TRUE(compare(ab, expectedAb, 0.001f));
    ASSERT_TRUE(compare(ba, expectedBa, 0.001f));
}

TEST(VectorGeneral, dot_product_diff_type_neither) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3, std::complex<float>> b = {{4, 1}, {5, 0}, {6, -1}};
    constexpr std::complex<float> expected = {32, -2};
    // act
    const std::complex<float> ab = a.dot(b, Vector<3>::neither);
    const std::complex<float> ba = b.dot(a, Vector<3, std::complex<float>>::neither);
    // assert
    ASSERT_TRUE(compare(ab, expected, 0.001f));
    ASSERT_TRUE(compare(ba, expected, 0.001f));
}

TEST(VectorGeneral, dot_product_diff_type_second) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3, std::complex<float>> b = {{4, 1}, {5, 0}, {6, -1}};
    constexpr std::complex<float> expectedAb = {32, 2};
    constexpr std::complex<float> expectedBa = {32, -2};
    // act
    const std::complex<float> ab = a.dot(b, Vector<3>::second_argument);
    const std::complex<float> ba = b.dot(a, Vector<3, std::complex<float>>::second_argument);
    // assert
    ASSERT_TRUE(compare(ab, expectedAb, 0.001f));
    ASSERT_TRUE(compare(ba, expectedBa, 0.001f));
}
