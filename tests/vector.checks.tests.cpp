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