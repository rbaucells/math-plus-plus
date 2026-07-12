#include "gtest/gtest.h"
#include "../../../telemetry.tests.h"

#include "mathpp/implementation/matrix/dense/matrix.h"
#include "mathpp/implementation/matrix/dense/operators/subtract.h"
#include "mathpp/implementation/matrix/dense/operators/compare.h"

TEST(dense_matrix_subtractition_operator, given_3_dense_matrices_should_give_dense_matrix_subtract_expr) {
    static_assert(std::is_same_v<decltype(std::declval<DenseMatrix<float>>() - std::declval<DenseMatrix<float>>() - std::declval<DenseMatrix<float>>()), DenseMatrixSubtractExpr<DenseMatrixSubtractExpr<DenseMatrix<float>, DenseMatrix<float>>, DenseMatrix<float>>>);
}

TEST(dense_matrix_subtract, given_3_dense_matrices_should_give_dense_matrix_subtract_expr) {
    static_assert(std::is_same_v<decltype(subtract(std::declval<DenseMatrix<float>>(), std::declval<DenseMatrix<float>>(), std::declval<DenseMatrix<float>>())), DenseMatrixSubtractExpr<DenseMatrix<float>, DenseMatrix<float>, DenseMatrix<float>>>);
}

TEST(dense_matrix_subtract_expr, given_3_dense_matrices_should_return_diff_dense_matrix) {
    // arrange
    const DenseMatrix<float> a = {{1.1f, 2.2f, 3.3f}, {4.4f, 5.5f, 6.6f}, {-7.7f, 8.8f, 9.9f}};
    const DenseMatrix<int> b = {{4, 7, 1}, {3, 5, 1}, {-4, 8, 6}};
    const DenseMatrix<double> c = {{1, 4, 8}, {5, -21, 4}, {4, 7, 1}};
    const DenseMatrix<double> expected = {{-3.9, -8.8, -5.7}, {-3.6, 21.5, 1.6}, {-7.7, -6.2, 2.9}};
    // act
    TelemetryTests::start();
    const DenseMatrixSubtractExpr<DenseMatrix<float>, DenseMatrix<int>, DenseMatrix<double>> expr(a, b, c);
    const DenseMatrix<double> diff = expr;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), diff, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}

namespace {
    DenseMatrixSubtractExpr<DenseMatrixSubtractExpr<DenseMatrix<float>, DenseMatrix<float>>, DenseMatrix<float>> make_expression(const DenseMatrix<float>& a, const DenseMatrix<float>& b, const DenseMatrix<float>& c) {
        return DenseMatrixSubtractExpr<DenseMatrixSubtractExpr<DenseMatrix<float>, DenseMatrix<float>>, DenseMatrix<float>>(DenseMatrixSubtractExpr<DenseMatrix<float>, DenseMatrix<float>>(a, b), c);
    }
}

TEST(dense_matrix_subtract_expr, given_3_dense_matrices_and_returned_should_work_and_return_dense_matrix) {
    // arrange
    const DenseMatrix<float> a = {{1.1f, 2.2f, 3.3f}, {4.4f, 5.5f, 6.6f}, {-7.7f, 8.8f, 9.9f}};
    const DenseMatrix<float> b = {{4, 7, 1}, {3, 5, 1}, {-4, 8, 6}};
    const DenseMatrix<float> c = {{1, 4, 8}, {5, -21, 4}, {4, 7, 1}};
    const DenseMatrix<float> expected = {{-3.9f, -8.8f, -5.7f}, {-3.6f, 21.5f, 1.6f}, {-7.7f, -6.2f, 2.9f}};
    // act
    TelemetryTests::start();
    const DenseMatrixSubtractExpr<DenseMatrixSubtractExpr<DenseMatrix<float>, DenseMatrix<float>>, DenseMatrix<float>> expr = make_expression(a, b, c);
    const DenseMatrix<float> diff = expr;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}

TEST(dense_matrix_subtract, given_2_dense_matrices_should_return_dense_matrix) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<int> b = {{3, 5, 8}, {3, -1, 5}, {4, -6, 8}};
    const DenseMatrix<float> expected = {{-2, -3, -5}, {1, 6, 1}, {3, 14, 1}};
    // act
    TelemetryTests::start();
    const DenseMatrix<float> diff = subtract(a, b);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1, .dimensions_checks = 1});
}

TEST(dense_matrix_subtract, given_2_dense_matrices_of_diff_size_should_throw) {
    // arrange
    const DenseMatrix<float> a = {{1, 2}, {3, 4}};
    const DenseMatrix<int> b = {{3, 5, 8}, {3, -1, 5}, {4, -6, 8}};
    // act / assert
    ASSERT_THROW(subtract(a, b), InvalidSizeException);
}

TEST(dense_matrix_subtractition_operator, given_2_dense_matrices_should_return_dense_matrix) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<int> b = {{3, 5, 8}, {3, -1, 5}, {4, -6, 8}};
    const DenseMatrix<float> expected = {{-2, -3, -5}, {1, 6, 1}, {3, 14, 1}};
    // act
    TelemetryTests::start();
    const DenseMatrix<float> diff = a - b;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), diff, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}