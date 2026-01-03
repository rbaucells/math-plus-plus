#include <gtest/gtest.h>
#include "math++/math.h"

TEST(MatrixTransformations, scaling_real) {
    // arrange
    constexpr Matrix<2, 2> expected = {{1, 0}, {0, 2}};
    // act
    const Matrix<2, 2> scaling = Matrix<2, 2>::scalingMatrix({1, 2});
    // assert
    ASSERT_TRUE(scaling.equals(expected, 0.001f));
}

TEST(MatrixTransformations, scaling_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{1, 2}, {0, 0}}, {{0, 0}, {3, 4}}};
    // act
    const Matrix<2, 2, std::complex<float>> scaling = Matrix<2, 2, std::complex<float>>::scalingMatrix({{1, 2}, {3, 4}});
    // assert
    ASSERT_TRUE(scaling.equals(expected, 0.001f));
}

TEST(MatrixTransformations, shear_real) {
    // arrange
    constexpr Matrix<2, 2> expected = {{1, 3}, {0, 1}};
    // act
    const Matrix<2, 2> shear = Matrix<2, 2>::shearMatrix(0, 1, 3);
    // assert
    ASSERT_TRUE(shear.equals(expected, 0.001f));
}

TEST(MatrixTransformations, shear_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{1, 0}, {3, 2}}, {{0, 0}, {1, 0}}};
    // act
    const Matrix<2, 2, std::complex<float>> shear = Matrix<2, 2, std::complex<float>>::shearMatrix(0, 1, {3, 2});
    // assert
    ASSERT_TRUE(shear.equals(expected, 0.001f));
}

TEST(MatrixTransformations, squeeze_real) {
    // arrange
    constexpr Matrix<2, 2> expected = {{3, 0}, {0, 1.0f / 3.0f}};
    // act
    const Matrix<2, 2> squeeze = Matrix<2, 2>::squeezeMatrix(0, 1, 3);
    // assert
    ASSERT_TRUE(squeeze.equals(expected, 0.001f));
}

TEST(MatrixTransformations, squeeze_complex) {
    // arrange
    constexpr Matrix<2, 2, std::complex<float>> expected = {{{3, 2}, {0, 0}}, {{0, 0}, {3.0f / 13.0f, -2.0f / 13.0f}}};
    // act
    const Matrix<2, 2, std::complex<float>> squeeze = Matrix<2, 2, std::complex<float>>::squeezeMatrix(0, 1, {3, 2});
    // assert
    ASSERT_TRUE(squeeze.equals(expected, 0.001f));
}

