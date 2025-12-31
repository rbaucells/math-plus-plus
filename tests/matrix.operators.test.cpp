#include <gtest/gtest.h>
#include "math++/math.h"

TEST(MatrixOperators, subscript) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    const Matrix<2, 2> b = {{1, 2}, {3, 4}};
    // act / assert
    ASSERT_FLOAT_EQ(a[0][0], 1.0f);
    ASSERT_FLOAT_EQ(a[1][0], 2.0f); 
    ASSERT_FLOAT_EQ(a[0][1], 3.0f);
    ASSERT_FLOAT_EQ(a[1][1], 4.0f);

    ASSERT_FLOAT_EQ(b[0][0], 1.0f);
    ASSERT_FLOAT_EQ(b[1][0], 2.0f);
    ASSERT_FLOAT_EQ(b[0][1], 3.0f);
    ASSERT_FLOAT_EQ(b[1][1], 4.0f);
}

TEST(MatrixOperators, equality_same_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 4}, {6, 8}};
    // act/assert
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a == a);
    ASSERT_TRUE(b == b);

    ASSERT_TRUE(a != b);
    ASSERT_FALSE(a != a);
    ASSERT_FALSE(b != b);
}

TEST(MatrixOperators, copy_assignment_same_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    Matrix<2, 2> b;
    // act
    b = a;
    // assert
    ASSERT_TRUE(a == b);
}

TEST(MatrixOperators, addition_same_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 4}, {6, 8}};
    constexpr Matrix<2, 2> expected = {{3, 6}, {9, 12}};
    // act
    const Matrix<2, 2> c = a + b;
    const Matrix<2, 2> d = b + a;
    // assert
    ASSERT_TRUE(c == expected);
    ASSERT_TRUE(d == expected);
}

TEST(MatrixOperators, subtraction_same_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 4}, {6, 8}};
    constexpr Matrix<2, 2> expectedAb = {{-1, -2}, {-3, -4}};
    constexpr Matrix<2, 2> expectedBa = {{1, 2}, {3, 4}};
    // act
    const Matrix<2, 2> c = a - b;
    const Matrix<2, 2> d = b - a;
    // assert
    ASSERT_TRUE(c == expectedAb);
    ASSERT_TRUE(d == expectedBa);
}

TEST(MatrixOperators, multiplication_same_type_same_size) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 3}, {4, 5}};
    constexpr Matrix<2, 2> expectedAb = {{10, 13}, {22, 29}};
    constexpr Matrix<2, 2> expectedBa = {{11, 16}, {19, 28}};
    // act
    const Matrix<2, 2> c = a * b;
    const Matrix<2, 2> d = b * a;
    // assert
    ASSERT_TRUE(c == expectedAb);
    ASSERT_TRUE(d == expectedBa);
}

TEST(MatrixOperators, multiplication_same_type_different_size) {
    // arrange
    constexpr Matrix<2, 3> a = {{1, 2, 3}, {3, 4, 5}};
    constexpr Matrix<3, 2> b = {{2, 3}, {4, 5}, {6, 7}};
    constexpr Matrix<2, 2> expectedAb = {{28, 34}, {52, 64}};
    constexpr Matrix<3, 3> expectedBa = {{11, 16, 21}, {19, 28, 37}, {27, 40, 53}};
    // act
    const Matrix<2, 2> c = a * b;
    const Matrix<3, 3> d = b * a;
    // assert
    ASSERT_TRUE(c == expectedAb);
    ASSERT_TRUE(d == expectedBa);
}

TEST(MatrixOperators, multiplication_same_type_vector) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Vector<2> b = {2, 2};
    constexpr Vector<2> expectedAb = {6, 14};
    constexpr Vector<2> expectedBa = {8, 12};
    // act
    const Vector<2> c = a * b;
    const Vector<2> d = b * a;
    // assert
    ASSERT_TRUE(c == expectedAb);
    ASSERT_TRUE(d == expectedBa);
}

TEST(MatrixOperators, multiplication_same_type_scalar) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr int b = 2;
    constexpr Matrix<2, 2> expected = {{2, 4}, {6, 8}};
    // act
    const Matrix<2, 2> c = a * b;
    const Matrix<2, 2> d = b * a;
    // assert
    ASSERT_TRUE(c == expected);
    ASSERT_TRUE(d == expected);
}

TEST(MatrixOperators, division_same_type_scalar) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr int b = 2;
    constexpr Matrix<2, 2> expected = {{0.5, 1}, {1.5, 2}};
    // act
    const Matrix<2, 2> c = a / b;
    // assert
    ASSERT_TRUE(c == expected);
}

TEST(MatrixOperators, equality_diff_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2, std::complex<float>> b = {{2, 4}, {6, 8}};
    // act/assert
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a == a);
    ASSERT_TRUE(b == b);

    ASSERT_TRUE(a != b);
    ASSERT_FALSE(a != a);
    ASSERT_FALSE(b != b);
}

TEST(MatrixOperators, copy_assignment_diff_type) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    Matrix<2, 2, std::complex<float>> b;
    // act
    b = a;
    // assert
    ASSERT_TRUE(a == b);
}

TEST(MatrixOperators, addition_diff_type) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 4}, {6, 8}};
    constexpr Matrix<2, 2, std::complex<float>> expected = {{3, 6}, {9, 12}};
    // act
    const Matrix<2, 2, std::complex<float>> c = a + b;
    const Matrix<2, 2, std::complex<float>> d = b + a;
    // assert
    ASSERT_TRUE(c == expected);
    ASSERT_TRUE(d == expected);
}

TEST(MatrixOperators, subtraction_diff_type) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 4}, {6, 8}};
    constexpr Matrix<2, 2, std::complex<float>> expectedAb = {{-1, -2}, {-3, -4}};
    constexpr Matrix<2, 2, std::complex<float>> expectedBa = {{1, 2}, {3, 4}};
    // act
    const Matrix<2, 2, std::complex<float>> c = a - b;
    const Matrix<2, 2, std::complex<float>> d = b - a;
    // assert
    ASSERT_TRUE(c == expectedAb);
    ASSERT_TRUE(d == expectedBa);
}

TEST(MatrixOperators, multiplication_diff_type_same_size) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> b = {{2, 3}, {4, 5}};
    constexpr Matrix<2, 2, std::complex<float>> expectedAb = {{10, 13}, {22, 29}};
    constexpr Matrix<2, 2, std::complex<float>> expectedBa = {{11, 16}, {19, 28}};
    // act
    const Matrix<2, 2, std::complex<float>> c = a * b;
    const Matrix<2, 2, std::complex<float>> d = b * a;
    // assert
    ASSERT_TRUE(c == expectedAb);
    ASSERT_TRUE(d == expectedBa);
}

TEST(MatrixOperators, multiplication_diff_type_different_size) {
    // arrange
    constexpr Matrix<2, 3, std::complex<float>> a = {{1, 2, 3}, {3, 4, 5}};
    constexpr Matrix<3, 2> b = {{2, 3}, {4, 5}, {6, 7}};
    constexpr Matrix<2, 2, std::complex<float>> expectedAb = {{28, 34}, {52, 64}};
    constexpr Matrix<3, 3, std::complex<float>> expectedBa = {{11, 16, 21}, {19, 28, 37}, {27, 40, 53}};
    // act
    const Matrix<2, 2, std::complex<float>> c = a * b;
    const Matrix<3, 3, std::complex<float>> d = b * a;
    // assert
    ASSERT_TRUE(c == expectedAb);
    ASSERT_TRUE(d == expectedBa);
}

TEST(MatrixOperators, multiplication_diff_type_vector) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{1, 2}, {3, 4}};
    constexpr Vector<2> b = {2, 2};
    constexpr Vector<2, std::complex<float>> expectedAb = {6, 14};
    constexpr Vector<2, std::complex<float>> expectedBa = {8, 12};
    // act
    const Vector<2, std::complex<float>> c = a * b;
    const Vector<2, std::complex<float>> d = b * a;
    // assert
    ASSERT_TRUE(c == expectedAb);
    ASSERT_TRUE(d == expectedBa);
}

TEST(MatrixOperators, multiplication_diff_type_scalar) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{1, 2}, {3, 4}};
    constexpr float b = 2;
    constexpr Matrix<2, 2, std::complex<float>> expected = {{2, 4}, {6, 8}};
    // act
    const Matrix<2, 2, std::complex<float>> c = a * b;
    const Matrix<2, 2, std::complex<float>> d = b * a;
    // assert
    ASSERT_TRUE(c == expected);
    ASSERT_TRUE(d == expected);
}

TEST(MatrixOperators, division_diff_type_scalar) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> a = {{1, 2}, {3, 4}};
    constexpr float b = 2;
    constexpr Matrix<2, 2, std::complex<float>> expected = {{0.5, 1}, {1.5, 2}};
    // act
    const Matrix<2, 2, std::complex<float>> c = a / b;
    // assert
    ASSERT_TRUE(c == expected);
}

TEST(MatrixOperators, unary_minus) {
    // arrange
    constexpr Matrix<2, 2> a = {{1, 2}, {3, 4}};
    constexpr Matrix<2, 2> expected = {{-1, -2}, {-3, -4}};
    // act
    const Matrix<2, 2> b = -a;
    // assert
    ASSERT_TRUE(b == expected);
}

TEST(MatrixOperators, to_pointer) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    const Matrix<2, 2> b = {{1, 2}, {3, 4}};
    // act
    auto* c = static_cast<float*>(a);
    const auto* d = static_cast<const float*>(b);
    // assert
    ASSERT_FLOAT_EQ(c[0], 1.0f);
    ASSERT_FLOAT_EQ(c[1], 3.0f);
    ASSERT_FLOAT_EQ(c[2], 2.0f);
    ASSERT_FLOAT_EQ(c[3], 4.0f);

    ASSERT_FLOAT_EQ(d[0], 1.0f);
    ASSERT_FLOAT_EQ(d[1], 3.0f);
    ASSERT_FLOAT_EQ(d[2], 2.0f);
    ASSERT_FLOAT_EQ(d[3], 4.0f);
}
