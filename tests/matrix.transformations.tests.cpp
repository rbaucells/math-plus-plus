#include <gtest/gtest.h>
#include "math++/math.h"

TEST(MatrixTransformations, apply_homogenous_transformations_same_type_real) {
    // arrange
    constexpr Matrix<3, 3> translation = {{1, 0, 2}, {0, 1, 3}, {0, 0, 1}};
    constexpr Vector<2> v = {0, 0};
    constexpr Vector<2> expected1 = {2, 3};
    constexpr Vector<2> expected0 = {0, 0};
    // act
    const Vector<2> translated1 = translation.applyHomogeneousTransformation(v, 1);
    const Vector<2> translated0 = translation.applyHomogeneousTransformation(v, 0);
    // assert
    ASSERT_TRUE(translated1.equals(expected1, 0.001f));
    ASSERT_TRUE(translated0.equals(expected0, 0.001f));
}

TEST(MatrixTransformations, apply_homogenous_transformations_same_type_complex) {
    // arrange
    constexpr Matrix<3, 3, std::complex<float>> translation = {{{1, 0}, {0, 0}, {2, 3}}, {{0, 0}, {1, 0}, {4, 5}}, {{0, 0}, {0,0}, {1, 0}}};
    constexpr Vector<2, std::complex<float>> v = {{0, 0}, {0, 0}};
    constexpr Vector<2, std::complex<float>> expected1 = {{2, 3}, {4, 5}};
    constexpr Vector<2, std::complex<float>> expected0 = {{0, 0}, {0, 0}};
    // act
    const Vector<2, std::complex<float>> translated1 = translation.applyHomogeneousTransformation(v, 1);
    const Vector<2, std::complex<float>> translated0 = translation.applyHomogeneousTransformation(v, 0);
    // assert
    ASSERT_TRUE(translated1.equals(expected1, 0.001f));
    ASSERT_TRUE(translated0.equals(expected0, 0.001f));
}

TEST(MatrixTransformations, apply_homogenous_transformations_diff_type) {
    // arrange
    constexpr Matrix<3, 3> realTransformation = {{1, 0, 2}, {0, 1, 3}, {0, 0, 1}};
    constexpr Matrix<3, 3, std::complex<float>> complexTranslation = {{{1, 0}, {0, 0}, {2, 3}}, {{0, 0}, {1, 0}, {4, 5}}, {{0, 0}, {0,0}, {1, 0}}};
    constexpr Vector<2> realV = {0, 0};
    constexpr Vector<2, std::complex<float>> complexV = {{0, 0}, {0, 0}};
    constexpr Vector<2, std::complex<float>> expectedRealComplex0 = {{0, 0},{0, 0}};
    constexpr Vector<2, std::complex<float>> expectedComplexReal1 = {{2, 3}, {4, 5}};
    constexpr Vector<2, std::complex<float>> expectedComplexReal0 = {{0, 0},{0, 0}};
    constexpr Vector<2, std::complex<float>> expectedRealComplex1 = {{2,0}, {3, 0}};
    // act
    const Vector<2, std::complex<float>> realComplex0 = realTransformation.applyHomogeneousTransformation(complexV, 0);
    const Vector<2, std::complex<float>> realComplex1 = realTransformation.applyHomogeneousTransformation(complexV, 1);
    const Vector<2, std::complex<float>> complexReal0 = complexTranslation.applyHomogeneousTransformation(realV, 0);
    const Vector<2, std::complex<float>> complexReal1 = complexTranslation.applyHomogeneousTransformation(realV, 1);
    // assert
    ASSERT_TRUE(realComplex0.equals(expectedRealComplex0, 0.001f));
    ASSERT_TRUE(realComplex1.equals(expectedRealComplex1, 0.001f));
    ASSERT_TRUE(complexReal0.equals(expectedComplexReal0, 0.001f));
    ASSERT_TRUE(complexReal1.equals(expectedComplexReal1, 0.001f));
}

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

TEST(MatrixTransformations, reflection_through_origin_real) {
    // arrange
    constexpr Vector<3> normal = {0, 1, 0};
    constexpr Matrix<3, 3> expected = {{1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
    // act
    const Matrix<3, 3> reflection = Matrix<3, 3>::reflectionMatrixAcrossPlaneThroughOrigin(normal);
    // assert
    ASSERT_TRUE(reflection.equals(expected, 0.001f));
}

TEST(MatrixTransformations, reflection_not_through_origin_real) {
    // arrange
    constexpr Vector<3> normal = {0, 1, 0};
    constexpr Vector<3> point = {0, 2, 0};
    constexpr Vector<3> v = {0, 0, 1};
    constexpr Vector<3> expected = {0, 4, 1};
    // act
    const Matrix<4, 4> reflection = Matrix<3, 3>::reflectionMatrixAcrossPlaneNotThroughOrigin(normal, point);
    const Vector<3> calculated = reflection.applyHomogeneousTransformation(v, 1);
    // assert
    ASSERT_TRUE(calculated.equals(expected, 0.001f));
}
