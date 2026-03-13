#include "gtest/gtest.h"

#include "mathpp/math.h"

TEST(equality_operator, given_f_dense_vectors_should_return_true) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> b = {1, 2, 3};
    const DenseVector<float> c = {1, 2, 3};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_dense_vectors_should_return_false) {
    // arrange
    const DenseVector<float> a = {1, 2, 3.1f};
    const DenseVector<float> b = {1, 2, 3};
    const DenseVector<float> c = {1, 2, 3};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_cf_dense_vectors_should_return_true) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    const DenseVector<std::complex<float>> b = {{1, 2}, {3, 4}, {5, 6}};
    const DenseVector<std::complex<float>> c = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_cf_dense_vectors_should_return_false) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    const DenseVector<std::complex<float>> b = {{1, 2}, {3, 4}, {5, 6}};
    const DenseVector<std::complex<float>> c = {{1, 2}, {3, 4}, {6, 6}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_f_and_cf_dense_vectors_should_return_true) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<std::complex<float>> b = {{1, 0}, {2, 0}, {3, 0}};
    const DenseVector<float> c = {1, 2, 3};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_and_cf_dense_vectors_should_return_false) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<std::complex<float>> b = {{1, 0}, {2, 0}, {3, 1}};
    const DenseVector<float> c = {1, 2, 3};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_f_dense_vectors_and_precision_should_return_true) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> b = {1, 2.1f, 3};
    const DenseVector<float> c = {1, 2, 3};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_dense_vectors_and_precision_should_return_false) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> b = {1, 2.1f, 3};
    const DenseVector<float> c = {1, 1.9f, 3};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_cf_dense_vectors_and_precision_should_return_true) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    const DenseVector<std::complex<float>> b = {{1, 2}, {3.1f, 4}, {5, 6}};
    const DenseVector<std::complex<float>> c = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_cf_dense_vectors_and_precision_should_return_false) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    const DenseVector<std::complex<float>> b = {{1.1f, 2}, {3, 4}, {5, 6}};
    const DenseVector<std::complex<float>> c = {{0.9f, 2}, {3, 4}, {5, 6}};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_f_and_cf_dense_vectors_and_precision_should_return_true) {
    // arrange
    const DenseVector<float> a = {1, 2, 3.1f};
    const DenseVector<std::complex<float>> b = {{1, 0}, {2, 0.1f}, {3, 0}};
    const DenseVector<float> c = {1, 2, 3};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_and_cf_dense_vectors_and_precision_should_return_false) {
    // arrange
    const DenseVector<float> a = {{1, 2, 3.1f}};
    const DenseVector<std::complex<float>> b = {{1, 0}, {2, 0.1f}, {3, 0}};
    const DenseVector<float> c = {1, 2, 2.9f};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}