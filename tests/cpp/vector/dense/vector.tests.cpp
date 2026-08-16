#include "../../telemetry.tests.h"
#include "gtest/gtest.h"

#include "mathpp/implementation/common/compare.h"
#include "mathpp/implementation/vector/dense/vector.h"
#include "mathpp/implementation/vector/dense/view.h"
#include "mathpp/implementation/vector/dense/operators/compare.h"

#pragma region default_constructor
TEST(dense_vector_default_constructor, given_dense_vector_should_default_construct) {
    // act
    TelemetryTests::start();
    const DenseVector<float> a;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(a.rawData() == nullptr);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region sized_constructor
TEST(dense_vector_sized_constructor, given_n_and_fill_should_construct) {
    // arrange
    const DenseVector<float> expected = {0, 0, 0};
    // act
    TelemetryTests::start();
    const DenseVector<float> a(3, true);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1});
}

TEST(dense_vector_sized_constructor, given_n_and_no_fill_should_construct) {
    // act
    TelemetryTests::start();
    const DenseVector<int> a(3, false);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 3));
    ASSERT_TRUE(a.rawData() != nullptr);
    TelemetryTests::asserts({.allocations = 1});
}
#pragma endregion
#pragma region initializer_list_constructor
TEST(dense_vector_initializer_list_constructor, given_initializer_list_should_construct) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3, 4};
    // act
    TelemetryTests::start();
    const DenseVector<float> a = {1, 2, 3, 4};
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 4));
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1});
}
#pragma endregion
#pragma region copy_constructor_from_same_type
TEST(dense_vector_copy_constructor_from_same_type, given_dense_vector_should_copy) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    // act
    TelemetryTests::start();
    const DenseVector<float> b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region copy_constructor_from_diff_type
TEST(dense_vector_copy_constructor_from_diff_type, given_dense_vector_should_copy) {
    // arrange
    const DenseVector<int> expected = {1, 2, 3};
    // act
    TelemetryTests::start();
    const DenseVector<std::complex<float>> b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region copy_constructor_from_like
TEST(dense_vector_copy_constructor_from_like, given_view_should_copy) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVectorView<float> expected(a, 3, 1);
    // act
    TelemetryTests::start();
    const DenseVector<float> b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region move_constructor
TEST(dense_vector_move_constructor, given_dense_vector_should_move) {
    // arrange
    DenseVector<long double> a = {1, 2, 3};
    const DenseVector<long double> expected = {1, 2, 3};
    // act
    TelemetryTests::start();
    const DenseVector<long double> b = std::move(a);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(a.rawData() == nullptr);
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE(compare(Precision(0.001l), b, expected));
    TelemetryTests::asserts({.move_constructs = 1});
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type
TEST(dense_vector_copy_assignment_operator_from_same_type, given_dense_vector_of_same_size_should_copy_assign) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<float> b(3);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1});
}

TEST(dense_vector_copy_assignment_operator_from_same_type, given_dense_vector_of_diff_size_should_copy_assign) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<float> b(1);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}

TEST(dense_vector_copy_assignment_operator_from_same_type, given_self_should_do_nothing) {
    // arrange
    DenseVector<float> b = {1, 2, 3};
    // act
    const float* before = b.rawData();
    TelemetryTests::start();
    b = b;
    TelemetryTests::end();
    const float* after = b.rawData();
    // assert
    ASSERT_TRUE(before == after);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region copy_assignment_operator_from_diff_type
TEST(dense_vector_copy_assignment_operator_from_diff_type, given_dense_vector_of_same_size_should_copy_assign) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<std::complex<float>> b(3);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1});
}

TEST(dense_vector_copy_assignment_operator_from_diff_type, given_dense_vector_of_diff_size_should_copy_assign) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<std::complex<float>> b(1);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}
#pragma endregion
#pragma region copy_assignment_operator_from_like
TEST(dense_vector_copy_assignment_operator_from_like, given_view_of_same_size_should_copy_assign) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4};
    const DenseVectorView<float> expected(a, 2, 1);
    DenseVector<float> b(2);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1});
}

TEST(dense_vector_copy_assignment_operator_from_like, given_view_of_diff_size_should_copy_assign) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4};
    const DenseVectorView<float> expected(a, 2, 1);
    DenseVector<float> b(4);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.n(), 2));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}
#pragma endregion
#pragma region move_assignment_operator
TEST(dense_vector_move_assignment_operator, given_dense_vector_should_move_assign) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<float> b(1);
    // act
    TelemetryTests::start();
    b = std::move(a);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(a.rawData() == nullptr);
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.move_assigns = 1, .deallocations = 1});
}

TEST(dense_vector_move_assignment_operator, given_self_should_do_nothing) {
    // arrange
    DenseVector<float> b = {1, 2, 3};
    // act
    const float* before = b.rawData();
    TelemetryTests::start();
    b = std::move(b);
    TelemetryTests::end();
    const float* after = b.rawData();
    // assert
    ASSERT_TRUE(before == after);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region reshape
TEST(dense_vector_reshape, given_same_size_should_do_nothing_1) {
    DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> expected = {1, 2, 3};
    TelemetryTests::start();
    a.reshape(3, false);
    TelemetryTests::end();
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({});
}

TEST(dense_vector_reshape, given_same_size_should_do_nothing_2) {
    DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> expected = {1, 2, 3};
    TelemetryTests::start();
    a.reshape(3, true);
    TelemetryTests::end();
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({});
}

TEST(dense_vector_reshape, given_same_size_should_do_nothing_3) {
    DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> expected = {1, 2, 3};
    TelemetryTests::start();
    a.reshape(3, false, 67);
    TelemetryTests::end();
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({});
}

TEST(dense_vector_reshape, given_same_size_should_do_nothing_4) {
    DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> expected = {1, 2, 3};
    TelemetryTests::start();
    a.reshape(3, true, 67);
    TelemetryTests::end();
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({});
}

TEST(dense_vector_reshape, given_new_size_and_preserve_should_reshape) {
    // arrange
    const DenseVector<float> expected = {1, 2};
    DenseVector<float> a = {1, 2, 3};
    // act
    const float* before = a.rawData();
    TelemetryTests::start();
    a.reshape(2, true);
    TelemetryTests::end();
    const float* after = a.rawData();
    // assert
    ASSERT_TRUE(compare(a.n(), 2));
    ASSERT_TRUE(before != after);
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1, .deallocations = 1});
}

TEST(dense_vector_reshape, given_new_size_and_no_preserve_and_value_should_reshape) {
    // arrange
    const DenseVector<float> expected = {67, 67};
    DenseVector<float> a = {1, 2, 3};
    // act
    const float* before = a.rawData();
    TelemetryTests::start();
    a.reshape(2, false, 67);
    TelemetryTests::end();
    const float* after = a.rawData();
    // assert
    ASSERT_TRUE(compare(a.n(), 2));
    ASSERT_TRUE(before != after);
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1, .deallocations = 1});
}

TEST(dense_vector_reshape, given_new_size_and_preserve_and_value_should_reshape) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3, 67};
    DenseVector<float> a = {1, 2, 3};
    // act
    const float* before = a.rawData();
    TelemetryTests::start();
    a.reshape(4, true, 67);
    TelemetryTests::end();
    const float* after = a.rawData();
    // assert
    ASSERT_TRUE(compare(a.n(), 4));
    ASSERT_TRUE(before != after);
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1, .deallocations = 1});
}
#pragma endregion
#pragma region at
TEST(dense_vector_at, given_valid_index_should_return_ref) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    // act
    TelemetryTests::start();
    float& ref = a.at(2);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), ref, 3));
    ref = 67;
    ASSERT_TRUE(compare(Precision(0.001f), a[2], 67));
    ASSERT_TRUE(&ref == &a.rawData()[2]);
    TelemetryTests::asserts({});
}

TEST(dense_vector_at, given_valid_index_should_return_const_ref) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    // act
    TelemetryTests::start();
    const float& ref = a.at(2);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), ref, 3));
    ASSERT_TRUE(&ref == &a.rawData()[2]);
    TelemetryTests::asserts({});
}

TEST(dense_vector_at, given_invalid_index_should_throw_1) {
    const DenseVector<float> a(3);
    ASSERT_THROW([[maybe_unused]] const float& ref = a.at(3), InvalidIndexException);
}

TEST(dense_vector_at, given_invalid_index_should_throw_2) {
    DenseVector<float> a(3);
    ASSERT_THROW([[maybe_unused]] float& ref = a.at(3), InvalidIndexException);
}
#pragma endregion
#pragma region indexing_operator
TEST(dense_vector_indexing_operator, given_valid_index_should_return_ref) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    // act
    TelemetryTests::start();
    float& ref = a[2];
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), ref, 3));
    ref = 67;
    ASSERT_TRUE(compare(Precision(0.001f), a[2], 67));
    ASSERT_TRUE(&ref == &a.rawData()[2]);
    TelemetryTests::asserts({});
}

TEST(dense_vector_indexing_operator, given_valid_index_should_return_const_ref) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    // act
    TelemetryTests::start();
    const float& ref = a[2];
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), ref, 3));
    ASSERT_TRUE(&ref == &a.rawData()[2]);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region n
TEST(dense_vector_n, given_dense_vector_should_return_n) {
    // arrange
    const DenseVector<float> a(3);
    // act
    TelemetryTests::start();
    const std::size_t n = a.n();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(n, 3));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region raw_data
TEST(dense_vector_raw_data, given_dense_vector_should_return_const_data_pointer) {
    // arrange
    DenseVector<int> a = {1, 2, 3};
    // act
    TelemetryTests::start();
    const int* data = a.rawData();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(data != nullptr);
    ASSERT_TRUE(compare(data[0], 1));
    ASSERT_TRUE(compare(data[1], 2));
    ASSERT_TRUE(compare(data[2], 3));
    a[2] = 67;
    ASSERT_TRUE(compare(data[2], 67));
    TelemetryTests::asserts({});
}

TEST(dense_vector_raw_data, given_dense_vector_should_return_data_pointer) {
    // arrange
    DenseVector<int> a = {1, 2, 3};
    // act
    TelemetryTests::start();
    int* data = a.rawData();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(data != nullptr);
    ASSERT_TRUE(compare(data[0], 1));
    ASSERT_TRUE(compare(data[1], 2));
    ASSERT_TRUE(compare(data[2], 3));
    data[2] = 67;
    ASSERT_TRUE(compare(a[2], 67));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region as_type
TEST(dense_vector_as_type, given_float_should_convert_to_double) {
    // arrange
    const DenseVector<float> expected = {1.5f, 2.5f, 3.5f, 4.5f};
    // act
    TelemetryTests::start();
    const DenseVector<double> result = expected.as_type<double>();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(result.n(), 4));
    ASSERT_TRUE(compare(Precision(0.001), result, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}

TEST(dense_vector_as_type, given_int_should_truncate_to_short) {
    // arrange
    const DenseVector<int> a = {1, 2, 3, 4};
    const DenseVector<short> expected = {1, 2, 3, 4};
    // act
    TelemetryTests::start();
    const DenseVector<short> result = a.as_type<short>();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(result.n(), 4));
    ASSERT_TRUE(compare(result, expected));
    TelemetryTests::asserts({.allocations = 1});
}

TEST(dense_vector_as_type, given_complex_double_should_truncate_to_float) {
    // arrange
    const DenseVector<std::complex<double>> a = {1.5, 2.5, 3.5, 4.5};
    const DenseVector<float> expected = {1.5f, 2.5f, 3.5f, 4.5f};
    // act
    TelemetryTests::start();
    const DenseVector<float> result = a.as_type<float>();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(result.n(), 4));
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
    TelemetryTests::asserts({.allocations = 1});
}
#pragma endregion