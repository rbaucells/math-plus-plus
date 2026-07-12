#include "gtest/gtest.h"
#include "../../../telemetry.tests.h"

#include "mathpp/implementation/vector/dense/vector.h"
#include "mathpp/implementation/vector/dense/operators/compare.h"

TEST(dense_vector_equality_operator, given_dense_matrices_should_return_compare_expr) {
    static_assert(std::is_same_v<decltype(std::declval<DenseVector<float>>() == std::declval<DenseVector<float>>() == std::declval<DenseVector<float>>()), DenseVectorCompareExpr<DenseVector<float>, DenseVector<float>, DenseVector<float>>>);
}

TEST(dense_vector_compare, given_3_dense_matrices_should_return_true) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<double> b = {1, 2, 3};
    const DenseVector<int> c = {1, 2, 3};
    // act
    TelemetryTests::start();
    const bool result = compare(a, b, c);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(result);
    TelemetryTests::asserts({});
}

TEST(dense_vector_compare, given_3_dense_matrices_should_return_false) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<double> b = {1, 2.001, 3};
    const DenseVector<int> c = {1, 2, 3};
    // act
    TelemetryTests::start();
    const bool result = compare(a, b, c);
    TelemetryTests::end();
    // assert
    ASSERT_FALSE(result);
    TelemetryTests::asserts({});
}

TEST(dense_vector_compare, given_3_dense_matrices_and_precision_should_return_true) {
    // arrange
    const DenseVector<float> a = {1, 2.09, 3};
    const DenseVector<double> b = {1, 2.05, 3};
    const DenseVector<int> c = {1, 2, 3};
    // act
    TelemetryTests::start();
    const bool result = compare(Precision(0.1), a, b, c);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(result);
    TelemetryTests::asserts({});
}

TEST(dense_vector_compare, given_3_dense_matrices_and_precision_should_return_false) {
    // arrange
    const DenseVector<float> a = {1, 2.1, 3};
    const DenseVector<double> b = {1, 1.9, 3.001};
    const DenseVector<int> c = {1, 2, 3};
    // act
    TelemetryTests::start();
    const bool result = compare(Precision(0.1), a, b, c);
    TelemetryTests::end();
    // assert
    ASSERT_FALSE(result);
    TelemetryTests::asserts({});
}

TEST(dense_vector_compare, given_dense_matrices_of_diff_size_should_return_false) {
    // arrange
    const DenseVector<float> a = {1, 1, 1};
    const DenseVector<float> b = {1, 1};
    // act
    TelemetryTests::start();
    const bool result = compare(a, b);
    TelemetryTests::end();
    // assert
    ASSERT_FALSE(result);
    TelemetryTests::asserts({});
}

TEST(dense_vector_equality_operator, given_dense_matrices_should_return_true) {
    // arrange
    const DenseVector<float> a = {1, 2};
    const DenseVector<float> b = {1, 2};
    const DenseVector<float> c = {1, 2};
    // act
    TelemetryTests::start();
    const bool result = a == b == c;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(result);
    TelemetryTests::asserts({});
}

TEST(dense_vector_equality_operator, given_dense_matrices_should_return_false) {
    // arrange
    const DenseVector<float> a = {1, 2.0001};
    const DenseVector<float> b = {1, 2};
    const DenseVector<float> c = {1, 2.0001};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_vector_equality_operator, given_dense_matrices_and_precision_should_return_true) {
    // arrange
    const DenseVector<float> a = {1, 2.05};
    const DenseVector<float> b = {1, 2};
    const DenseVector<float> c = {1, 1.95};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_vector_equality_operator, given_dense_matrices_and_precision_should_return_false) {
    // arrange
    const DenseVector<float> a = {1, 2.05};
    const DenseVector<float> b = {1, 2};
    const DenseVector<float> c = {1, 1.96};
    // act
    const bool result = (a == b == c) + Precision(0.08f);
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_vector_equality_operator, given_dense_vector_of_diff_size_should_return_false) {
    // arrange
    const DenseVector<float> a = {1, 1, 1};
    const DenseVector<float> b = {1, 1};
    // act
    TelemetryTests::start();
    const bool result = a == b;
    TelemetryTests::end();
    // assert
    ASSERT_FALSE(result);
    TelemetryTests::asserts({});
}
