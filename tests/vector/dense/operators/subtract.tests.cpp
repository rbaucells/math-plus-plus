#include "gtest/gtest.h"
#include "../../../telemetry.tests.h"

#include "mathpp/implementation/vector/dense/vector.h"
#include "mathpp/implementation/vector/dense/operators/subtract.h"
#include "mathpp/implementation/vector/dense/operators/compare.h"

TEST(dense_vector_subtractition_operator, given_3_dense_matrices_should_give_dense_vector_subtract_expr) {
    static_assert(std::is_same_v<decltype(std::declval<DenseVector<float>>() - std::declval<DenseVector<float>>() - std::declval<DenseVector<float>>()), DenseVectorSubtractExpr<DenseVectorSubtractExpr<DenseVector<float>, DenseVector<float>>, DenseVector<float>>>);
}

TEST(dense_vector_subtract, given_3_dense_matrices_should_give_dense_vector_subtract_expr) {
    static_assert(std::is_same_v<decltype(subtract(std::declval<DenseVector<float>>(), std::declval<DenseVector<float>>(), std::declval<DenseVector<float>>())), DenseVectorSubtractExpr<DenseVector<float>, DenseVector<float>, DenseVector<float>>>);
}

TEST(dense_vector_subtract_expr, given_3_dense_matrices_should_return_diff_dense_vector) {
    // arrange
    const DenseVector<float> a = {1.1f, 2.2f, 3.3f};
    const DenseVector<int> b = {4, 7, 1};
    const DenseVector<double> c = {1, 4, 8};
    const DenseVector<double> expected = {-3.9, -8.8, -5.7};
    // act
    TelemetryTests::start();
    const DenseVectorSubtractExpr<DenseVector<float>, DenseVector<int>, DenseVector<double>> expr(a, b, c);
    const DenseVector<double> diff = expr;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), diff, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}

namespace {
    DenseVectorSubtractExpr<DenseVectorSubtractExpr<DenseVector<float>, DenseVector<float>>, DenseVector<float>> make_expression(const DenseVector<float>& a, const DenseVector<float>& b, const DenseVector<float>& c) {
        return DenseVectorSubtractExpr<DenseVectorSubtractExpr<DenseVector<float>, DenseVector<float>>, DenseVector<float>>(DenseVectorSubtractExpr<DenseVector<float>, DenseVector<float>>(a, b), c);
    }
}

TEST(dense_vector_subtract_expr, given_3_dense_matrices_and_returned_should_work_and_return_dense_vector) {
    // arrange
    const DenseVector<float> a = {1.1f, 2.2f, 3.3f};
    const DenseVector<float> b = {4, 7, 1};
    const DenseVector<float> c = {1, 4, 8};
    const DenseVector<float> expected = {-3.9f, -8.8f, -5.7f};
    // act
    TelemetryTests::start();
    const DenseVectorSubtractExpr<DenseVectorSubtractExpr<DenseVector<float>, DenseVector<float>>, DenseVector<float>> expr = make_expression(a, b, c);
    const DenseVector<float> diff = expr;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}

TEST(dense_vector_subtract, given_2_dense_matrices_should_return_dense_vector) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<int> b = {3, 5, 8};
    const DenseVector<float> expected = {-2, -3, -5};
    // act
    TelemetryTests::start();
    const DenseVector<float> diff = subtract(a, b);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1, .dimensions_checks = 1});
}

TEST(dense_vector_subtract, given_2_dense_matrices_of_diff_size_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2};
    const DenseVector<int> b = {3, 5, 8};
    // act / assert
    ASSERT_THROW(subtract(a, b), InvalidDimensionException);
}

TEST(dense_vector_subtractition_operator, given_2_dense_matrices_should_return_dense_vector) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    const DenseVector<int> b = {3, 5, 8};
    const DenseVector<float> expected = {-2, -3, -5};
    // act
    TelemetryTests::start();
    const DenseVector<float> diff = a - b;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
