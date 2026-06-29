#include "../../../telemetry.tests.h"
#include "gtest/gtest.h"

#include "mathpp/implementation/vector/dense/vector.h"
#include "mathpp/implementation/vector/dense/operators/add.h"
#include "mathpp/implementation/vector/dense/operators/compare.h"

TEST(dense_vector_addition_operator, given_3_dense_matrices_should_give_dense_vector_add_expr) {
    static_assert(std::is_same_v<decltype(std::declval<DenseVector<float>>() + std::declval<DenseVector<float>>() + std::declval<DenseVector<float>>()), DenseVectorAddExpr<DenseVectorAddExpr<DenseVector<float>, DenseVector<float>>, DenseVector<float>>>);
}

TEST(dense_vector_add, given_3_dense_matrices_should_give_dense_vector_add_expr) {
    static_assert(std::is_same_v<decltype(add(std::declval<DenseVector<float>>(), std::declval<DenseVector<float>>(), std::declval<DenseVector<float>>())), DenseVectorAddExpr<DenseVector<float>, DenseVector<float>, DenseVector<float>>>);
}

TEST(dense_vector_add_expr, given_3_dense_matrices_should_return_sum_dense_vector) {
    // arrange
    const DenseVector<float> a = {1.1f, 2.2f, 3.3f};
    const DenseVector<int> b = {-4, 6, 3};
    const DenseVector<double> c = {0.8, 2.1, -1.5};
    const DenseVector<double> expected = {-2.1, 10.3, 4.8};
    // act
    TelemetryTests::start();
    const DenseVectorAddExpr<DenseVector<float>, DenseVector<int>, DenseVector<double>> expr(a, b, c);
    const DenseVector<double> sum = expr;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), sum, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}

namespace {
    DenseVectorAddExpr<DenseVectorAddExpr<DenseVector<float>, DenseVector<float>>, DenseVector<float>> make_expression(const DenseVector<float>& a, const DenseVector<float>& b, const DenseVector<float>& c) {
        return DenseVectorAddExpr<DenseVectorAddExpr<DenseVector<float>, DenseVector<float>>, DenseVector<float>>(DenseVectorAddExpr<DenseVector<float>, DenseVector<float>>(a, b), c);
    }
}

TEST(dense_vector_add_expr, given_3_dense_matrices_and_returned_should_work_and_return_dense_vector) {
    // arrange
    const DenseVector<float> a = {1.1f, 2.2f, 3.3f};
    const DenseVector<float> b = {-4, 6, 3};
    const DenseVector<float> c = {0.8f, 2.1f, -1.5f};
    const DenseVector<float> expected = {-2.1, 10.3, 4.8};
    // act
    TelemetryTests::start();
    const DenseVectorAddExpr<DenseVectorAddExpr<DenseVector<float>, DenseVector<float>>, DenseVector<float>> expr = make_expression(a, b, c);
    const DenseVector<float> sum = expr;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), sum, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}

TEST(dense_vector_add, given_2_dense_matrices_should_return_dense_vector) {
    // arrange
    const DenseVector<float> a = {1.1f, 2.2f, 3.3f};
    const DenseVector<int> b = {-4, 6, 3};
    const DenseVector<float> expected = {-2.9f, 8.2f, 6.3f};
    // act
    TelemetryTests::start();
    const DenseVector<float> sum = add(a, b);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), sum, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1, .dimensions_checks = 1});
}

TEST(dense_vector_add, given_2_dense_matrices_of_diff_size_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<int> b = {1, 2, 3, 4};
    // act / assert
    ASSERT_THROW(add(a, b), InvalidDimensionException);
}

TEST(dense_vector_addition_operator, given_2_dense_matrices_should_return_dense_vector) {
    // arrange
    const DenseVector<float> a = {1.1f, 2.2f, 3.3f};
    const DenseVector<int> b = {-4, 6, 3};
    const DenseVector<float> expected = {-2.9f, 8.2f, 6.3f};
    // act
    TelemetryTests::start();
    const DenseVector<float> sum = a + b;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), sum, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
