#include "gtest/gtest.h"
#include "../../../telemetry.tests.h"

#include "mathpp/implementation/vector/dense/vector.h"
#include "mathpp/implementation/vector/dense/operators/dot.h"
#include "mathpp/implementation/vector/dense/operators/compare.h"

TEST(dense_vector_dot, given_2_real_dense_vectors_should_return_dot_1) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> b = {3, 1, 7};
    constexpr float expected = 26;
    // act
    TelemetryTests::start();
    const float product = dot(a, b, DotProductConjugationBehavior::first_argument);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
    TelemetryTests::asserts({.dimensions_checks = 1});
}

TEST(dense_vector_dot, given_2_real_dense_vectors_should_return_dot_2) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> b = {3, 1, 7};
    constexpr float expected = 26;
    // act
    TelemetryTests::start();
    const float product = dot(a, b, DotProductConjugationBehavior::neither);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
    TelemetryTests::asserts({.dimensions_checks = 1});
}

TEST(dense_vector_dot, given_2_real_dense_vectors_should_return_dot_3) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> b = {3, 1, 7};
    constexpr float expected = 26;
    // act
    TelemetryTests::start();
    const float product = dot(a, b, DotProductConjugationBehavior::second_argument);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
    TelemetryTests::asserts({.dimensions_checks = 1});
}

TEST(dense_vector_dot, given_2_dense_vectors_should_return_dot_and_conjugate_first_argument) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 4}, {4, 1}, {3, 0}};
    const DenseVector<std::complex<float>> b = {{3, 6}, {0, 0}, {-3, 1}};
    constexpr std::complex<float> expected = {18, -3};
    // act
    TelemetryTests::start();
    const std::complex<float> product = dot(a, b, DotProductConjugationBehavior::first_argument);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
    TelemetryTests::asserts({.dimensions_checks = 1});
}

TEST(dense_vector_dot, given_2_dense_vectors_should_return_dot_and_not_conjugate) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 4}, {4, 1}, {3, 0}};
    const DenseVector<std::complex<float>> b = {{3, 6}, {0, 0}, {-3, 1}};
    constexpr std::complex<float> expected = {-30, 21};
    // act
    TelemetryTests::start();
    const std::complex<float> product = dot(a, b, DotProductConjugationBehavior::neither);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
    TelemetryTests::asserts({.dimensions_checks = 1});
}

TEST(dense_vector_dot, given_2_dense_vectors_should_return_dot_and_conjugate_second_argument) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 4}, {4, 1}, {3, 0}};
    const DenseVector<std::complex<float>> b = {{3, 6}, {0, 0}, {-3, 1}};
    constexpr std::complex<float> expected = {18, 3};
    // act
    TelemetryTests::start();
    const std::complex<float> product = dot(a, b, DotProductConjugationBehavior::second_argument);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
    TelemetryTests::asserts({.dimensions_checks = 1});
}

TEST(dense_vector_dot, given_2_dense_vectors_should_return_dot_and_conjugate_default) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 4}, {4, 1}, {3, 0}};
    const DenseVector<std::complex<float>> b = {{3, 6}, {0, 0}, {-3, 1}};
    constexpr std::complex<float> expected = {18, 3};
    // act
    TelemetryTests::start();
    const std::complex<float> product = dot(a, b);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
    TelemetryTests::asserts({.dimensions_checks = 1});
}

TEST(dense_vector_dot, given_2_dense_vectors_of_diff_size_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<int> b = {1, 2, 3, 4};
    // act / assert
    ASSERT_THROW(dot(a, b), InvalidSizeException);
}

TEST(dense_vector_multiplication_operator, given_2_dense_vectors_should_return_dot_and_conjugate_default) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 4}, {4, 1}, {3, 0}};
    const DenseVector<std::complex<float>> b = {{3, 6}, {0, 0}, {-3, 1}};
    constexpr std::complex<float> expected = {18, 3};
    // act
    TelemetryTests::start();
    const std::complex<float> product = a * b;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), product, expected));
    TelemetryTests::asserts({});
}
