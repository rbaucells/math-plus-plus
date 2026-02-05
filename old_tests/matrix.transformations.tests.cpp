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

TEST(MatrixTransformations, translation_real) {
    // arrange
    constexpr Matrix<3, 3> expected = {{1, 0, 2}, {0, 1, 3}, {0, 0, 1}};
    // act
    const Matrix<3, 3> translation = Matrix<2, 2>::translationMatrix({2, 3});
    // assert
    ASSERT_TRUE(translation.equals(expected, 0.001f));
}

TEST(MatrixTransformations, translation_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> expected = {{{1, 0}, {0, 0}, {1, 2}}, {{0, 0}, {1, 0}, {3, 4}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act
    const Matrix<3, 3, std::complex<float>> translation = Matrix<2, 2, std::complex<float>>::translationMatrix({{1, 2}, {3, 4}});
    // assert
    ASSERT_TRUE(translation.equals(expected, 0.001f));
}

TEST(MatrixTransformations, rotation_origin_degrees_real) {
    // arrange
    constexpr Matrix<2, 2> expected = {{0, -1}, {1, 0}};
    // act
    const Matrix<2, 2> rotation = Matrix<2, 2>::rotationMatrixAboutOrigin(90, RotationType::degrees);
    // assert
    ASSERT_TRUE(rotation.equals(expected, 0.001f));
}

TEST(MatrixTransformations, rotation_origin_radians_real) {
    // arrange
    constexpr Matrix<2, 2> expected = {{0, -1}, {1, 0}};
    // act
    const Matrix<2, 2> rotation = Matrix<2, 2>::rotationMatrixAboutOrigin(M_PI_2, RotationType::radians);
    // assert
    ASSERT_TRUE(rotation.equals(expected, 0.001f));
}

TEST(MatrixTransformations, rotation_point_degrees_real) {
    // arrange
    constexpr Vector<2> v = {2, 0};
    constexpr Vector<2> p = {1, 0};
    constexpr Vector<2> expected = {1, 1};
    // act
    const Matrix<3, 3> rotation = Matrix<2, 2>::rotationMatrixAboutPoint(p, 90, RotationType::degrees);
    const Vector<2> calculated = rotation.applyHomogeneousTransformation(v, 1);
    // assert
    ASSERT_TRUE(calculated.equals(expected, 0.001f));
}

TEST(MatrixTransformations, rotation_point_radians_real) {
    // arrange
    constexpr Vector<2> v = {2, 0};
    constexpr Vector<2> p = {1, 0};
    constexpr Vector<2> expected = {1, 1};
    // act
    const Matrix<3, 3> rotation = Matrix<2, 2>::rotationMatrixAboutPoint(p, M_PI_2, RotationType::radians);
    const Vector<2> calculated = rotation.applyHomogeneousTransformation(v, 1);
    // assert
    ASSERT_TRUE(calculated.equals(expected, 0.001f));
}

TEST(MatrixTransformations, rotation_axis_pass_through_origin_degrees_real) {
    // arrange
    constexpr Vector<3> axis = {0, 1, 0};
    constexpr Matrix<3, 3> expected = {{0, 0, 1}, {0, 1, 0}, {-1, 0, 0}};
    // act
    const Matrix<3, 3> rotation = Matrix<3, 3>::rotationMatrixAroundAxisThroughOrigin(axis, 90, RotationType::degrees);
    // assert
    ASSERT_TRUE(rotation.equals(expected, 0.001f));
}

TEST(MatrixTransformations, rotation_axis_pass_through_origin_radians_real) {
    // arrange
    constexpr Vector<3> axis = {0, 1, 0};
    constexpr Matrix<3, 3> expected = {{0, 0, 1}, {0, 1, 0}, {-1, 0, 0}};
    // act
    const Matrix<3, 3> rotation = Matrix<3, 3>::rotationMatrixAroundAxisThroughOrigin(axis, M_PI_2, RotationType::radians);
    // assert
    ASSERT_TRUE(rotation.equals(expected, 0.001f));
}

TEST(MatrixTransformations, rotation_axis_not_through_origin_degrees_real) {
    // arrange
    constexpr Vector<3> axis = {0, 1, 0};
    constexpr Vector<3> pointOnAxis = {1, 0, 0};
    constexpr Vector<3> p = {2, 0, 0};
    constexpr Vector<3> expected = {1, 0, -1};
    // act
    const Matrix<4, 4> rotation = Matrix<3, 3>::rotationMatrixAroundAxisNotThroughOrigin(axis, pointOnAxis, 90, RotationType::degrees);
    const Vector<3> calculated = rotation.applyHomogeneousTransformation(p, 1);
    // assert
    ASSERT_TRUE(calculated.equals(expected, 0.001f));
}

TEST(MatrixTransformations, rotation_axis_not_through_origin_radians_real) {
    // arrange
    constexpr Vector<3> axis = {0, 1, 0};
    constexpr Vector<3> pointOnAxis = {1, 0, 0};
    constexpr Vector<3> p = {2, 0, 0};
    constexpr Vector<3> expected = {1, 0, -1};
    // act
    const Matrix<4, 4> rotation = Matrix<3, 3>::rotationMatrixAroundAxisNotThroughOrigin(axis, pointOnAxis, M_PI_2, RotationType::radians);
    const Vector<3> calculated = rotation.applyHomogeneousTransformation(p, 1);
    // assert
    ASSERT_TRUE(calculated.equals(expected, 0.001f));
}
