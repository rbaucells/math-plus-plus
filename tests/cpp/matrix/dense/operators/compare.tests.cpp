#include "gtest/gtest.h"
#include "../../../telemetry.tests.h"

#include "mathpp/implementation/matrix/dense/matrix.h"
#include "mathpp/implementation/matrix/dense/operators/compare.h"

TEST(dense_matrix_equality_operator, given_dense_matrices_should_return_compare_expr) {
    static_assert(std::is_same_v<decltype(std::declval<DenseMatrix<float>>() == std::declval<DenseMatrix<float>>() == std::declval<DenseMatrix<float>>()), DenseMatrixCompareExpr<DenseMatrix<float>, DenseMatrix<float>, DenseMatrix<float>>>);
}

TEST(dense_matrix_compare, given_3_dense_matrices_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<double> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<int> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    TelemetryTests::start();
    const bool result = compare(a, b, c);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(result);
    TelemetryTests::asserts({});
}

TEST(dense_matrix_compare, given_3_dense_matrices_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<double> b = {{1, 2, 3}, {4, 5, 6}, {7, 8.001, 9}};
    const DenseMatrix<int> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    TelemetryTests::start();
    const bool result = compare(a, b, c);
    TelemetryTests::end();
    // assert
    ASSERT_FALSE(result);
    TelemetryTests::asserts({});
}

TEST(dense_matrix_compare, given_3_dense_matrices_and_precision_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5.09, 6}, {7, 8, 9}};
    const DenseMatrix<double> b = {{1, 2, 3}, {4, 5.05, 6}, {7, 8, 9}};
    const DenseMatrix<int> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    TelemetryTests::start();
    const bool result = compare(Precision(0.1), a, b, c);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(result);
    TelemetryTests::asserts({});
}

TEST(dense_matrix_compare, given_3_dense_matrices_and_precision_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5.1, 6}, {7, 8, 9}};
    const DenseMatrix<double> b = {{1, 2, 3}, {4, 4.9, 6}, {7, 8.001, 9}};
    const DenseMatrix<int> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    TelemetryTests::start();
    const bool result = compare(Precision(0.1), a, b, c);
    TelemetryTests::end();
    // assert
    ASSERT_FALSE(result);
    TelemetryTests::asserts({});
}

TEST(dense_matrix_compare, given_dense_matrices_of_diff_size_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    const DenseMatrix<float> b = {{1, 1}, {1, 1}};
    // act
    TelemetryTests::start();
    const bool result = compare(a, b);
    TelemetryTests::end();
    // assert
    ASSERT_FALSE(result);
    TelemetryTests::asserts({});
}

TEST(dense_matrix_equality_operator, given_dense_matrices_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2}, {3, 4}};
    const DenseMatrix<float> b = {{1, 2}, {3, 4}};
    const DenseMatrix<float> c = {{1, 2}, {3, 4}};
    // act
    TelemetryTests::start();
    const bool result = a == b == c;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(result);
    TelemetryTests::asserts({});
}

TEST(dense_matrix_equality_operator, given_dense_matrices_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2.0001}, {3, 4}};
    const DenseMatrix<float> b = {{1, 2}, {3, 4}};
    const DenseMatrix<float> c = {{1, 2.0001}, {3, 4}};
    // act
    const bool result = a == b == c;
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality_operator, given_dense_matrices_and_precision_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2.05}, {3, 4}};
    const DenseMatrix<float> b = {{1, 2}, {3, 4}};
    const DenseMatrix<float> c = {{1, 1.95}, {3, 4}};
    // act
    const bool result = (a == b == c) + Precision(0.1f);
    // assert
    ASSERT_TRUE(result);
}

TEST(dense_matrix_equality_operator, given_dense_matrices_and_precision_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2.05}, {3, 4}};
    const DenseMatrix<float> b = {{1, 2}, {3, 4}};
    const DenseMatrix<float> c = {{1, 1.96}, {3, 4}};
    // act
    const bool result = (a == b == c) + Precision(0.08f);
    // assert
    ASSERT_FALSE(result);
}

TEST(dense_matrix_equality_operator, given_dense_matrix_of_diff_size_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    const DenseMatrix<float> b = {{1, 1}, {1, 1}};
    // act
    TelemetryTests::start();
    const bool result = a == b;
    TelemetryTests::end();
    // assert
    ASSERT_FALSE(result);
    TelemetryTests::asserts({});
}
