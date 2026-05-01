#include "gtest/gtest.h"

#include "mathpp/vector.h"

TEST(equality_operator, given_f_sparse_vectors_should_return_true) {
    // arrange
    const CooSparseVector<float> a(5, {{1, 0}, {2, 2}, {3, 4}});
    const CooSparseVector<float> b(5, {{1, 0}, {2, 2}, {3, 4}});
    const CooSparseVector<float> c(5, {{1, 0}, {2, 2}, {3, 4}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_sparse_vectors_should_return_false) {
    // arrange
    const CooSparseVector<float> a(5, {{1, 0}, {2, 2}, {3.1f, 4}});
    const CooSparseVector<float> b(5, {{1, 0}, {2, 2}, {3, 4}});
    const CooSparseVector<float> c(5, {{1, 0}, {2, 2}, {3, 4}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_cf_sparse_vectors_should_return_true) {
    // arrange
    const CooSparseVector<std::complex<float>> a(5, {{{1, 2}, 0}, {{3, 4}, 2}, {{5, 6}, 4}});
    const CooSparseVector<std::complex<float>> b(5, {{{1, 2}, 0}, {{3, 4}, 2}, {{5, 6}, 4}});
    const CooSparseVector<std::complex<float>> c(5, {{{1, 2}, 0}, {{3, 4}, 2}, {{5, 6}, 4}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_cf_sparse_vectors_should_return_false) {
    // arrange
    const CooSparseVector<std::complex<float>> a(5, {{{1, 2}, 0}, {{3, 4}, 2}, {{5, 6}, 4}});
    const CooSparseVector<std::complex<float>> b(5, {{{1, 2}, 0}, {{3, 4}, 2}, {{5, 6}, 4}});
    const CooSparseVector<std::complex<float>> c(5, {{{1, 2}, 0}, {{3, 4}, 2}, {{6, 6}, 4}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_f_and_cf_sparse_vectors_should_return_true) {
    // arrange
    const CooSparseVector<float> a(5, {{1, 0}, {2, 2}, {3, 4}});
    const CooSparseVector<std::complex<float>> b(5, {{{1, 0}, 0}, {{2, 0}, 2}, {{3, 0}, 4}});
    const CooSparseVector<float> c(5, {{1, 0}, {2, 2}, {3, 4}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_and_cf_sparse_vectors_should_return_false) {
    // arrange
    const CooSparseVector<float> a(5, {{1, 0}, {2, 2}, {3, 4}});
    const CooSparseVector<std::complex<float>> b(5, {{{1, 0}, 0}, {{2, 0}, 2}, {{3, 1}, 4}});
    const CooSparseVector<float> c(5, {{1, 0}, {2, 2}, {3, 4}});
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_f_sparse_vectors_and_precision_should_return_true) {
    // arrange
    const CooSparseVector<float> a(5, {{1, 0}, {2, 2}, {3, 4}});
    const CooSparseVector<float> b(5, {{1, 0}, {2.1f, 2}, {3, 4}});
    const CooSparseVector<float> c(5, {{1, 0}, {2, 2}, {3, 4}});
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_sparse_vectors_and_precision_should_return_false) {
    // arrange
    const CooSparseVector<float> a(5, {{1, 0}, {2, 2}, {3, 4}});
    const CooSparseVector<float> b(5, {{1, 0}, {2.1f, 2}, {3, 4}});
    const CooSparseVector<float> c(5, {{1, 0}, {1.9f, 2}, {3, 4}});
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_cf_sparse_vectors_and_precision_should_return_true) {
    // arrange
    const CooSparseVector<std::complex<float>> a(5, {{{1, 2}, 0}, {{3, 4}, 2}, {{5, 6}, 4}});
    const CooSparseVector<std::complex<float>> b(5, {{{1, 2}, 0}, {{3.1f, 4}, 2}, {{5, 6}, 4}});
    const CooSparseVector<std::complex<float>> c(5, {{{1, 2}, 0}, {{3, 4}, 2}, {{5, 6}, 4}});
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_cf_sparse_vectors_and_precision_should_return_false) {
    // arrange
    const CooSparseVector<std::complex<float>> a(5, {{{1, 2}, 0}, {{3, 4}, 2}, {{5, 6}, 4}});
    const CooSparseVector<std::complex<float>> b(5, {{{1.1f, 2}, 0}, {{3, 4}, 2}, {{5, 6}, 4}});
    const CooSparseVector<std::complex<float>> c(5, {{{0.9f, 2}, 0}, {{3, 4}, 2}, {{5, 6}, 4}});
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}

TEST(equality_operator, given_f_and_cf_sparse_vectors_and_precision_should_return_true) {
    // arrange
    const CooSparseVector<float> a(5, {{1, 0}, {2, 2}, {3.1f, 4}});
    const CooSparseVector<std::complex<float>> b(5, {{{1, 0}, 0}, {{2, 0.1f}, 2}, {{3, 0}, 4}});
    const CooSparseVector<float> c(5, {{1, 0}, {2, 2}, {3, 4}});
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(equality_operator, given_f_and_cf_sparse_vectors_and_precision_should_return_false) {
    // arrange
    const CooSparseVector<float> a(5, {{1, 0}, {2, 2}, {3.1f, 4}});
    const CooSparseVector<std::complex<float>> b(5, {{{1, 0}, 0}, {{2, 0.1f}, 2}, {{3, 0}, 4}});
    const CooSparseVector<float> c(5, {{1, 0}, {2, 2}, {2.9f, 4}});
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_FALSE(result);
}
