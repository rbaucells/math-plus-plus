#include "math++/math.h"
#include <gtest/gtest.h>

TEST(VectorChecks, is_orthogonal_real) {
    // arrange
    constexpr Vector<3> a = {1, 0, 0};
    constexpr Vector<3> b = {0, 2, 0};
    constexpr Vector<3> c = {0, 0, 3};
    // act / assert
    ASSERT_TRUE(Vector<3>::isOrthogonal({a, b, c}));
}

TEST(VectorChecks, is_orthonormal_real) {
    // arrange
    constexpr Vector<3> a = {1, 0, 0};
    constexpr Vector<3> b = {0, 1, 0};
    constexpr Vector<3> c = {0, 0, 1};
    // act / assert
    ASSERT_TRUE(Vector<3>::isOrthonormal({a, b, c}));
}

TEST(VectorChecks, not_is_orthogonal_real) {
    // arrange
    constexpr Vector<3> a = {1, 1, 0};
    constexpr Vector<3> b = {0, 2, 0};
    constexpr Vector<3> c = {0, 0, 3};
    // act / assert
    ASSERT_FALSE(Vector<3>::isOrthogonal({a, b, c}));
}

TEST(VectorChecks, not_is_orthonormal_real_not_orthogonal) {
    // arrange
    constexpr Vector<3> a = {0, 0, 0};
    constexpr Vector<3> b = {1, 1, 0};
    constexpr Vector<3> c = {0, 0, 1};
    // act / assert
    ASSERT_FALSE(Vector<3>::isOrthonormal({a, b, c}));
}

TEST(VectorChecks, not_is_orthonormal_real_not_normalized) {
    // arrange
    constexpr Vector<3> a = {1, 0, 0};
    constexpr Vector<3> b = {0, 2, 0};
    constexpr Vector<3> c = {0, 0, 3};
    // act / assert
    ASSERT_FALSE(Vector<3>::isOrthonormal({a, b, c}));
}

TEST(VectorChecks, is_orthogonal_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {0, 0}, {0, 0}};
    constexpr Vector<3, std::complex<float>> b = {{0, 0}, {2, -1}, {0, 0}};
    constexpr Vector<3, std::complex<float>> c = {{0, 0}, {0, 0}, {3, 2}};
    // act
    const bool isOrthogonal = Vector<3, std::complex<float>>::isOrthogonal({a, b, c});
    // assert
    ASSERT_TRUE(isOrthogonal);
}

TEST(VectorChecks, is_orthonormal_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 0}, {0, 0}, {0, 0}};
    constexpr Vector<3, std::complex<float>> b = {{0, 0}, {0, 1}, {0, 0}};
    constexpr Vector<3, std::complex<float>> c = {{0, 0}, {0, 0}, {1, 0}};
    // act
    const bool isOrthonormal = Vector<3, std::complex<float>>::isOrthonormal({a, b, c});
    // assert
    ASSERT_TRUE(isOrthonormal);
}

TEST(VectorChecks, not_is_orthogonal_complex) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{1, 1}, {1, -1}, {0, 0}};
    constexpr Vector<3, std::complex<float>> b = {{0, 0}, {2, 0}, {0, 0}};
    constexpr Vector<3, std::complex<float>> c = {{0, 0}, {0, 0}, {3, 1}};
    // act
    const bool isOrthogonal = Vector<3, std::complex<float>>::isOrthogonal({a, b, c});
    // assert
    ASSERT_FALSE(isOrthogonal);
}

TEST(VectorChecks, not_is_orthonormal_complex_not_orthogonal) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{0, 0}, {0, 0}, {0, 0}};
    constexpr Vector<3, std::complex<float>> b = {{1, 1}, {1, 0}, {0, 0}};
    constexpr Vector<3, std::complex<float>> c = {{0, 0}, {0, 0}, {0, 1}};
    // act
    const bool isOrthonormal = Vector<3, std::complex<float>>::isOrthonormal({a, b, c});
    // assert
    ASSERT_FALSE(isOrthonormal);
}

TEST(VectorChecks, not_is_orthonormal_complex_not_normalized) {
    // arrange
    constexpr Vector<3, std::complex<float>> a = {{2, 0}, {0, 0}, {0, 0}};
    constexpr Vector<3, std::complex<float>> b = {{0, 0}, {0, 2}, {0, 0}};
    constexpr Vector<3, std::complex<float>> c = {{0, 0}, {0, 0}, {1, -1}};
    // act
    const bool isOrthonormal = Vector<3, std::complex<float>>::isOrthonormal({a, b, c});
    // assert
    ASSERT_FALSE(isOrthonormal);
}