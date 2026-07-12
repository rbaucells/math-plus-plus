#include "gtest/gtest.h"
#include "../../../telemetry.tests.h"

#include "mathpp/implementation/matrix/dense/matrix.h"
#include "mathpp/implementation/matrix/dense/operators/add_assign.h"
#include "mathpp/implementation/matrix/dense/operators/compare.h"

TEST(dense_matrix_add_equals_operator, given_dense_matrix_should_give_dense_matrix_reference) {
    static_assert(std::is_same_v<decltype(std::declval<DenseMatrix<float>&>() += std::declval<DenseMatrix<float>>()), DenseMatrix<float>&>);
}


TEST(dense_matrix_add_assign, given_dense_matrix_should_give_dense_matrix_reference) {
    static_assert(std::is_same_v<decltype(add_assign(std::declval<DenseMatrix<float>&>(), std::declval<DenseMatrix<float>>())), DenseMatrix<float>&>);
}

TEST(dense_matrix_add_assign, given_2_dense_matrices_should_modify_dense_matrix) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<double> b = {{9, -8, -7}, {7, -6, 5}, {-5, 4, -3}};
    const DenseMatrix<double> expected = {{10, -6, -4}, {11, -1, 11}, {2, 12, 6}};
    // act
    TelemetryTests::start();
    add_assign(a, b);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), a, expected));
    TelemetryTests::asserts({.dimensions_checks = 1});
}

TEST(dense_matrix_add_assign, given_2_dense_matrices_of_diff_size_should_throw) {
    // arrange
    DenseMatrix<float> a = {{1, 2}, {3, 4}};
    const DenseMatrix<int> b = {{3, 5, 8}, {3, -1, 5}, {4, -6, 8}};
    // act / assert
    ASSERT_THROW(add_assign(a, b), InvalidSizeException);
}

TEST(dense_matrix_add_equals_operator, given_dense_matrix_should_modify_dense_matrix) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<double> b = {{9, -8, -7}, {7, -6, 5}, {-5, 4, -3}};
    const DenseMatrix<double> expected = {{10, -6, -4}, {11, -1, 11}, {2, 12, 6}};
    // act
    TelemetryTests::start();
    a += b;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), a, expected));
    TelemetryTests::asserts({});
}
