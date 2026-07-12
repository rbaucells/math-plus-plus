#include "gtest/gtest.h"
#include "../../../telemetry.tests.h"

#include "mathpp/implementation/vector/dense/vector.h"
#include "mathpp/implementation/vector/dense/operators/add_assign.h"
#include "mathpp/implementation/vector/dense/operators/compare.h"

TEST(dense_vector_add_equals_operator, given_dense_vector_should_give_dense_vector_reference) {
    static_assert(std::is_same_v<decltype(std::declval<DenseVector<float>&>() += std::declval<DenseVector<float>>()), DenseVector<float>&>);
}


TEST(dense_vector_add_assign, given_dense_vector_should_give_dense_vector_reference) {
    static_assert(std::is_same_v<decltype(add_assign(std::declval<DenseVector<float>&>(), std::declval<DenseVector<float>>())), DenseVector<float>&>);
}

TEST(dense_vector_add_assign, given_2_dense_matrices_should_modify_dense_vector) {
    // arrange
    DenseVector<float> a = {1.1f, 2.2f, 3.3f};
    const DenseVector<double> b = {-4, 6, 3};
    const DenseVector<double> expected = {-2.9f, 8.2f, 6.3f};
    // act
    TelemetryTests::start();
    add_assign(a, b);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), a, expected));
    TelemetryTests::asserts({.dimensions_checks = 1});
}

TEST(dense_vector_add_assign, given_2_dense_matrices_of_diff_size_should_throw) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    const DenseVector<int> b = {1, 2, 3, 4};
    // act / assert
    ASSERT_THROW(add_assign(a, b), InvalidSizeException);
}

TEST(dense_vector_add_equals_operator, given_dense_vector_should_modify_dense_vector) {
    // arrange
    DenseVector<float> a = {1.1f, 2.2f, 3.3f};
    const DenseVector<double> b = {-4, 6, 3};
    const DenseVector<double> expected = {-2.9f, 8.2f, 6.3f};
    // act
    TelemetryTests::start();
    a += b;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001), a, expected));
    TelemetryTests::asserts({});
}
