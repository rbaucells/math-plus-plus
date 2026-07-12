#include "../../../telemetry.tests.h"
#include "gtest/gtest.h"

#include "mathpp/implementation/matrix/dense/matrix.h"
#include "mathpp/implementation/matrix/dense/operators/add.h"
#include "mathpp/implementation/matrix/dense/operators/compare.h"

TEST(dense_matrix_addition_operator, given_3_dense_matrices_should_give_dense_matrix_add_expr) {
    static_assert(std::is_same_v<decltype(std::declval<DenseMatrix<float>>() + std::declval<DenseMatrix<float>>() + std::declval<DenseMatrix<float>>()), DenseMatrixAddExpr<DenseMatrixAddExpr<DenseMatrix<float>, DenseMatrix<float>>, DenseMatrix<float>>>);
}

TEST(dense_matrix_add, given_3_dense_matrices_should_give_dense_matrix_add_expr) {
    static_assert(std::is_same_v<decltype(add(std::declval<DenseMatrix<float>>(), std::declval<DenseMatrix<float>>(), std::declval<DenseMatrix<float>>())), DenseMatrixAddExpr<DenseMatrix<float>, DenseMatrix<float>, DenseMatrix<float>>>);
}

TEST(dense_matrix_add_expr, given_3_dense_matrices_should_return_sum_dense_matrix) {
    // arrange
    const DenseMatrix<float> a = {{1.1f, 2.2f, 3.3f}, {4.4f, 5.5f, 6.6f}, {7.7f, 8.8f, 9.9f}};
    const DenseMatrix<int> b = {{4, 7, 1}, {3, 5, 1}, {4, 8, 6}};
    const DenseMatrix<double> c = {{1, 4, 8}, {5, 21, 4}, {4, 7, 1}};
    const DenseMatrix<double> expected = {{6.1, 13.2, 12.3}, {12.4, 31.5, 11.6}, {15.7, 23.8, 16.9}};
    // act
    TelemetryTests::start();
    const DenseMatrixAddExpr<DenseMatrix<float>, DenseMatrix<int>, DenseMatrix<double>> expr(a, b, c);
    const DenseMatrix<double> sum = expr;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), sum, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}

namespace {
    DenseMatrixAddExpr<DenseMatrixAddExpr<DenseMatrix<float>, DenseMatrix<float>>, DenseMatrix<float>> make_expression(const DenseMatrix<float>& a, const DenseMatrix<float>& b, const DenseMatrix<float>& c) {
        return DenseMatrixAddExpr<DenseMatrixAddExpr<DenseMatrix<float>, DenseMatrix<float>>, DenseMatrix<float>>(DenseMatrixAddExpr<DenseMatrix<float>, DenseMatrix<float>>(a, b), c);
    }
}

TEST(dense_matrix_add_expr, given_3_dense_matrices_and_returned_should_work_and_return_dense_matrix) {
    // arrange
    const DenseMatrix<float> a = {{1.1f, 2.2f, 3.3f}, {4.4f, 5.5f, 6.6f}, {7.7f, 8.8f, 9.9f}};
    const DenseMatrix<float> b = {{4, 7, 1}, {3, 5, 1}, {4, 8, 6}};
    const DenseMatrix<float> c = {{1, 4, 8}, {5, 21, 4}, {4, 7, 1}};
    const DenseMatrix<float> expected = {{6.1, 13.2, 12.3}, {12.4, 31.5, 11.6}, {15.7, 23.8, 16.9}};
    // act
    TelemetryTests::start();
    const DenseMatrixAddExpr<DenseMatrixAddExpr<DenseMatrix<float>, DenseMatrix<float>>, DenseMatrix<float>> expr = make_expression(a, b, c);
    const DenseMatrix<float> sum = expr;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), sum, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}

TEST(dense_matrix_add, given_2_dense_matrices_should_return_dense_matrix) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<int> b = {{3, 5, 8}, {3, -1, 5}, {4, -6, 8}};
    const DenseMatrix<float> expected = {{4, 7, 11}, {7, 4, 11}, {11, 2, 17}};
    // act
    TelemetryTests::start();
    const DenseMatrix<float> sum = add(a, b);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), sum, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1, .dimensions_checks = 1});
}

TEST(dense_matrix_add, given_2_dense_matrices_of_diff_size_should_throw) {
    // arrange
    const DenseMatrix<float> a = {{1, 2}, {3, 4}};
    const DenseMatrix<int> b = {{3, 5, 8}, {3, -1, 5}, {4, -6, 8}};
    // act / assert
    ASSERT_THROW(add(a, b), InvalidSizeException);
}

TEST(dense_matrix_addition_operator, given_2_dense_matrices_should_return_dense_matrix) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<int> b = {{3, 5, 8}, {3, -1, 5}, {4, -6, 8}};
    const DenseMatrix<float> expected = {{4, 7, 11}, {7, 4, 11}, {11, 2, 17}};
    // act
    TelemetryTests::start();
    const DenseMatrix<float> sum = a + b;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), sum, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
