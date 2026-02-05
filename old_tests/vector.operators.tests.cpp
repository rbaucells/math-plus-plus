#include "math++/math.h"
#include <gtest/gtest.h>

TEST(VectorOperators, copy_assignment_same_type_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    // act
    Vector<3> b;
    b = a;
    // assert
    ASSERT_TRUE(b.equals(a, 0.001f));
}

TEST(VectorOperators, copy_assignment_same_type_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    // act
    Vector<3, std::complex<float>> b;
    b = a;
    // assert
    ASSERT_TRUE(b.equals(a, 0.001f));
}

TEST(VectorOperators, copy_assignment_diff_type) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    // act
    Vector<3, std::complex<float>> b;
    b = a;
    // assert
    ASSERT_TRUE(b.equals(a, 0.001f));
}

TEST(VectorOperators, equal_same_type_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3> b = {1, 2, 3};
    // act / assert
    ASSERT_TRUE(a == b);
    ASSERT_TRUE(b == a);
    ASSERT_FALSE(a != b);
    ASSERT_FALSE(b != a);
}

TEST(VectorOperators, not_equal_same_type_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3> b = {2, 4, 6};
    // act / assert
    ASSERT_FALSE(a == b);
    ASSERT_FALSE(b == a);
    ASSERT_TRUE(a != b);
    ASSERT_TRUE(b != a);
}

TEST(VectorOperators, equal_same_type_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3, std::complex<float>> b = {{1, 2}, {3, 4}, {5, 6}};
    // act / assert
    ASSERT_TRUE(a == b);
    ASSERT_TRUE(b == a);
    ASSERT_FALSE(a != b);
    ASSERT_FALSE(b != a);
}

TEST(VectorOperators, not_equal_same_type_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3, std::complex<float>> b = {{2, 4}, {6, 8}, {10, 12}};
    // act / assert
    ASSERT_FALSE(a == b);
    ASSERT_FALSE(b == a);
    ASSERT_TRUE(a != b);
    ASSERT_TRUE(b != a);
}

TEST(VectorOperators, equal_diff_type) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3, std::complex<float>> b = {{1, 0}, {2, 0}, {3, 0}};
    // act / assert
    ASSERT_TRUE(a == b);
    ASSERT_TRUE(b == a);
    ASSERT_FALSE(a != b);
    ASSERT_FALSE(b != a);
}

TEST(VectorOperators, not_equal_diff_type) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3, std::complex<float>> b = {{1, 2}, {3, 4}, {5, 6}};
    // act / assert
    ASSERT_FALSE(a == b);
    ASSERT_FALSE(b == a);
    ASSERT_TRUE(a != b);
    ASSERT_TRUE(b != a);
}

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
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3, std::complex<float>> b = {{2, 4}, {6, 8}, {10, 12}};
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
    constexpr Vector<3, std::complex<float>> b = {{1, 2}, {3, 4}, {5, 6}};
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

TEST(VectorOperators, unary_minus_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    constexpr Vector<3> expected = {-1, -2, -3};
    // act
    const Vector<3> v = -a;
    // assert
    ASSERT_TRUE(v.equals(expected, 0.001f));
}

TEST(VectorOperators, unary_minus_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3, std::complex<float>> expected = {{-1, -2}, {-3, -4}, {-5, -6}};
    // act
    const Vector<3, std::complex<float>> v = -a;
    // assert
    ASSERT_TRUE(v.equals(expected, 0.001f));
}

TEST(VectorOperators, matrix_multiplication_same_type_real) {
    // arrange
    constexpr Vector<2> a = {1, 2};
    constexpr Matrix<2, 2> b = {{1, 2}, {3, 4}};
    constexpr Vector<2> expected = {7, 10};
    // act
    const Vector<2> v = a * b;
    // assert
    ASSERT_TRUE(v.equals(expected, 0.001f));
}

TEST(VectorOperators, matrix_multiplication_same_type_complex) {
    // arrange
    constexpr Vector<2, std::complex<float>> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr Vector<2, std::complex<float>> expected = {{-12, 42}, {-16, 62}};
    // act
    const Vector<2, std::complex<float>> v = a * b;
    // assert
    ASSERT_TRUE(v.equals(expected, 0.001f));
}

TEST(VectorOperators, matrix_multiplicaiton_diff_type) {
    // arrange
    constexpr Vector<2> a = {1, 2};
    constexpr Vector<2, std::complex<float>> b = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> c = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> d = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    constexpr Vector<2, std::complex<float>> expectedAd = {{11, 14}, {17, 20}};
    constexpr Vector<2, std::complex<float>> expectedBc = {{10, 14}, {14, 20}};
    // act
    const Vector<2, std::complex<float>> ad = a * d;
    const Vector<2, std::complex<float>> bc = b * c;
    // assert
    ASSERT_TRUE(ad.equals(expectedAd, 0.001f));
    ASSERT_TRUE(bc.equals(expectedBc, 0.001f));
}

TEST(VectorOperators, addition_equals_same_type_real) {
    // arrange
    Vector<3> a = {1, 2, 3};
    constexpr Vector<3> b = {2, 4, 6};
    constexpr Vector<3> expected = {3, 6, 9};
    // act
    a += b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, addition_equals_same_type_complex) {
    // arrange
    Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3, std::complex<float>> b = {{2, 4}, {6, 8}, {10, 12}};
    constexpr Vector<3, std::complex<float>> expected = {{3, 6}, {9, 12}, {15, 18}};
    // act
    a += b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, addition_equals_diff_type) {
    // arrange
    Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr Vector<3> b = {2, 4, 6};
    constexpr Vector<3, std::complex<float>> expected = {{3, 2}, {7, 4}, {11, 6}};
    // act
    a += b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, subtraction_equals_same_type_real) {
    // arrange
    Vector<3> a = {3, 6, 9};
    constexpr Vector<3> b = {2, 4, 6};
    constexpr Vector<3> expected = {1, 2, 3};
    // act
    a -= b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, subtraction_equals_same_type_complex) {
    // arrange
    Vector<3, std::complex<float>> a = {{3, 6}, {9, 12}, {15, 18}};
    constexpr Vector<3, std::complex<float>> b = {{2, 4}, {6, 8}, {10, 12}};
    constexpr Vector<3, std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    // act
    a -= b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, subtraction_equals_diff_type) {
    // arrange
    Vector<3, std::complex<float>> a = {{3, 2}, {7, 4}, {11, 6}};
    constexpr Vector<3> b = {2, 4, 6};
    constexpr Vector<3, std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    // act
    a -= b;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, multiply_equals_same_type_real) {
    // arrange
    Vector<3> a = {1, 2, 3};
    constexpr float s = 2.0f;
    constexpr Vector<3> expected = {2, 4, 6};
    // act
    a *= s;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, multiply_equals_same_type_complex) {
    // arrange
    Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr std::complex<float> s = {2, 3};
    constexpr Vector<3, std::complex<float>> expected = {{ -4,  7},{ -6, 17},{ -8, 27}};
    // act
    a *= s;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, multiply_equals_diff_type) {
    // arrange
    Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    constexpr float s = 2.0f;
    constexpr Vector<3, std::complex<float>> expected = {{2, 4},{6, 8},{10, 12}};
    // act
    a *= s;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, divide_equals_same_type_real) {
    // arrange
    Vector<3> a = {2, 4, 6};
    constexpr float s = 2.0f;
    constexpr Vector<3> expected = {1, 2, 3};
    // act
    a /= s;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, divide_equals_same_type_complex) {
    // arrange
    Vector<3, std::complex<float>> a = {{2, 4}, {6, 8}, {10, 12}};
    constexpr std::complex<float> s = {2, 0};
    constexpr Vector<3, std::complex<float>> expected = {{1, 2},{3, 4},{5, 6}};
    // act
    a /= s;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, divide_equals_diff_type) {
    // arrange
    Vector<3, std::complex<float>> a = {{2, 4}, {6, 8}, {10, 12}};
    constexpr float s = 2.0f;
    constexpr Vector<3, std::complex<float>> expected = {{1, 2},{3, 4},{5, 6}};
    // act
    a /= s;
    // assert
    ASSERT_TRUE(a.equals(expected, 0.001f));
}

TEST(VectorOperators, const_to_pointer_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    // act
    const float* ptr = static_cast<const float*>(a);
    // assert
    ASSERT_TRUE(compare(ptr[0], 1));
    ASSERT_TRUE(compare(ptr[1], 2));
    ASSERT_TRUE(compare(ptr[2], 3));
}

TEST(VectorOperators, to_pointer_real) {
    // arrange
    Vector<3> a = {1, 2, 3};
    // act
    float* ptr = static_cast<float*>(a);
    // assert
    ASSERT_TRUE(compare(ptr[0], 1));
    ASSERT_TRUE(compare(ptr[1], 2));
    ASSERT_TRUE(compare(ptr[2], 3));
}

TEST(VectorOperators, const_to_pointer_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const std::complex<float>* ptr = static_cast<const std::complex<float>*>(a);
    // assert
    ASSERT_TRUE(compare(ptr[0], std::complex<float>(1, 2)));
    ASSERT_TRUE(compare(ptr[1], std::complex<float>(3, 4)));
    ASSERT_TRUE(compare(ptr[2], std::complex<float>(5, 6)));
}

TEST(VectorOperators, to_pointer_complex) {
    // arrange
    Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    // act
    std::complex<float>* ptr = static_cast<std::complex<float>*>(a);
    // assert
    ASSERT_TRUE(compare(ptr[0], std::complex<float>(1, 2)));
    ASSERT_TRUE(compare(ptr[1], std::complex<float>(3, 4)));
    ASSERT_TRUE(compare(ptr[2], std::complex<float>(5, 6)));
}

TEST(VectorOperators, const_indexing_real) {
    // arrange
    constexpr Vector<3> a = {1, 2, 3};
    // act / assert
    ASSERT_TRUE(compare(a[0], 1));
    ASSERT_TRUE(compare(a[1], 2));
    ASSERT_TRUE(compare(a[2], 3));
}

TEST(VectorOperators, indexing_real) {
    // arrange
    Vector<3> a = {1, 2, 3};
    // act / assert
    ASSERT_TRUE(compare(a[0], 1));
    ASSERT_TRUE(compare(a[1], 2));
    ASSERT_TRUE(compare(a[2], 3));
}

TEST(VectorOperators, const_indexing_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    // act / assert
    ASSERT_TRUE(compare(a[0], std::complex<float>(1, 2)));
    ASSERT_TRUE(compare(a[1], std::complex<float>(3, 4)));
    ASSERT_TRUE(compare(a[2], std::complex<float>(5, 6)));
}

TEST(VectorOperators, indexing_complex) {
    // arrange
    Vector<3, std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    // act / assert
    ASSERT_TRUE(compare(a[0], std::complex<float>(1, 2)));
    ASSERT_TRUE(compare(a[1], std::complex<float>(3, 4)));
    ASSERT_TRUE(compare(a[2], std::complex<float>(5, 6)));
}
