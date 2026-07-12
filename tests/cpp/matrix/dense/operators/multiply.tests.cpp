#include "gtest/gtest.h"
#include "../../../telemetry.tests.h"

#include "mathpp/implementation/matrix/dense/matrix.h"
#include "mathpp/implementation/matrix/dense/operators/multiply.h"
#include "mathpp/implementation/matrix/dense/operators/compare.h"

TEST(dense_matrix_multiply, given_dense_matrices_should_return_product) {
    // arrange
    const DenseMatrix<int> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<double> b = {{1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 10}};
    const DenseMatrix<double> expected = {{30, 36, 42, 48}, {66, 81, 96, 111}, {102, 126, 150, 174}};
    // act
    TelemetryTests::start();
    const DenseMatrix<double> product = multiply(a, b);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), product, expected));
    TelemetryTests::asserts({.allocations = 1, .dimensions_checks = 1});
}

TEST(dense_matrix_multiply, given_2_dense_matrices_of_non_multipliable_size_should_throw) {
    // arrange
    const DenseMatrix<float> a = {{1, 2}, {3, 4}};
    const DenseMatrix<int> b = {{3, 5, 8}, {3, -1, 5}, {4, -6, 8}};
    // act / assert
    ASSERT_THROW(multiply(a, b), InvalidSizeException);
}

TEST(dense_matrix_multiplication_operator, given_dense_matrix_should_return_product) {
    // arrange
    const DenseMatrix<int> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<double> b = {{1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 10}};
    const DenseMatrix<double> expected = {{30, 36, 42, 48}, {66, 81, 96, 111}, {102, 126, 150, 174}};
    // act
    TelemetryTests::start();
    const DenseMatrix<double> product = a * b;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), product, expected));
    TelemetryTests::asserts({.allocations = 1});
}
