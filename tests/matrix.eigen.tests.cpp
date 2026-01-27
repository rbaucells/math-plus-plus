#include <gtest/gtest.h>
#include "math++/math.h"

TEST(MatrixGeneral, rayleigh_quotient_real) {
    // arrange
    constexpr Matrix<3, 3> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    constexpr Vector<3> v = {1, -2, 1};
    constexpr float expected = 0.0f;
    // act
    const float eigenValue = m.rayleighQuotient(v);
    // assert
    ASSERT_TRUE(compare(eigenValue, expected, 0.001f));
}

TEST(MatrixGeneral, rayleigh_quotient_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> m = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    constexpr Vector<3, std::complex<float>> v = {{0.26336f, 0.02104f}, {0.63168f, 0.01052f}, {1, 0}};
    constexpr std::complex<float> expected = {29.436f, 32.2252f};
    // act
    const std::complex<float> eigenValue = m.rayleighQuotient(v);
    // assert
    ASSERT_TRUE(compare(eigenValue, expected, 0.001f));
}
