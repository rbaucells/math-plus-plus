#include "gtest/gtest.h"

#include "mathpp/vector.h"

TEST(dot_operator, given_f_dense_vectors_should_return_dot) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> b = {2, 4, 6};
    constexpr float expected = 28;
    // act
    const float dot = a * b;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), expected, dot));
}

TEST(dot_operator, given_cf_dense_vectors_should_return_dot) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 1}, {2, 0}, {0, 3}};
    const DenseVector<std::complex<float>> b = {{3, 1}, {2, 0}, {0, 1}};
    constexpr std::complex<float> expected = {11, 2};
    // act
    const std::complex<float> dot = a * b;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), expected, dot));
}

TEST(dot_operator, given_f_and_cf_dense_vectors_should_return_dot) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<std::complex<float>> b = {{1, 2}, {3, 4}, {5, 6}};
    constexpr std::complex<float> expected = {22, -28};
    // act
    const std::complex<float> dot = a * b;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), expected, dot));
}
