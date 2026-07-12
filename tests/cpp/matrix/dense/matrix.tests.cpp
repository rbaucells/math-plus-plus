#include "../../telemetry.tests.h"
#include "gtest/gtest.h"

#include "mathpp/implementation/common/compare.h"
#include "mathpp/implementation/matrix/dense/matrix.h"
#include "mathpp/implementation/matrix/dense/view.h"
#include "mathpp/implementation/matrix/dense/operators/compare.h"

#pragma region default_constructor
TEST(dense_matrix_default_constructor, given_dense_matrix_should_default_construct) {
    // act
    TelemetryTests::start();
    const DenseMatrix<float> a;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.rows(), 0));
    ASSERT_TRUE(compare(a.columns(), 0));
    ASSERT_TRUE(a.rawData() == nullptr);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region sized_constructor
TEST(dense_matrix_sized_constructor, given_rows_and_columns_and_fill_should_construct) {
    // arrange
    const DenseMatrix<float> expected = {{0, 0, 0}, {0, 0, 0}};
    // act
    TelemetryTests::start();
    const DenseMatrix<float> a(2, 3, true);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.rows(), 2));
    ASSERT_TRUE(compare(a.columns(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1});
}

TEST(dense_matrix_sized_constructor, given_rows_and_columns_and_no_fill_should_construct) {
    // act
    TelemetryTests::start();
    const DenseMatrix<int> a(2, 3, false);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.rows(), 2));
    ASSERT_TRUE(compare(a.columns(), 3));
    ASSERT_TRUE(a.rawData() != nullptr);
    TelemetryTests::asserts({.allocations = 1});
}
#pragma endregion
#pragma region initializer_list_constructor
TEST(dense_matrix_initializer_list_constructor, given_nested_initializer_list_should_construct) {
    // arrange
    DenseMatrix<float> expected(2, 2);
    expected[0, 0] = 1;
    expected[0, 1] = 2;
    expected[1, 0] = 3;
    expected[1, 1] = 4;
    // act
    TelemetryTests::start();
    const DenseMatrix<float> a = {{1, 2}, {3, 4}};
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(expected.rows(), 2));
    ASSERT_TRUE(compare(expected.columns(), 2));
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1});
}

TEST(dense_matrix_initializer_list_constructor, given_differently_sized_nested_initializer_list_should_throw) {
    // act / assert
    ASSERT_THROW(DenseMatrix<float>({{1, 2}, {3, 4, 5}}), InvalidSizeException);
}
#pragma endregion
#pragma region copy_constructor_from_same_type
TEST(dense_matrix_copy_constructor_from_same_type, given_dense_matrix_should_copy) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    TelemetryTests::start();
    const DenseMatrix<float> b = expected; // NOLINT(*-unnecessary-copy-initialization)
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region copy_constructor_from_diff_type
TEST(dense_matrix_copy_constructor_from_diff_type, given_i_dense_matrix_should_copy) {
    // arrange
    const DenseMatrix<int> expected = {{1, 2}, {3, 4}};
    // act
    TelemetryTests::start();
    const DenseMatrix<std::complex<float>> b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.rows(), 2));
    ASSERT_TRUE(compare(b.columns(), 2));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region copy_constructors_from_like
TEST(dense_matrix_copy_constructors_from_like, given_view_should_copy) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrixView<float> expected(a, 2, 2, 0, 0);
    // act
    TelemetryTests::start();
    const DenseMatrix<float> b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.rows(), 2));
    ASSERT_TRUE(compare(b.columns(), 2));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_constructs = 1, .allocations = 1});
}
#pragma endregion
#pragma region move_constructor
TEST(dense_matrix_move_constructor, given_dense_matrix_should_move) {
    // arrange
    DenseMatrix<long double> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<long double> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    TelemetryTests::start();
    const DenseMatrix<long double> b = std::move(a);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.rows(), 0));
    ASSERT_TRUE(compare(a.columns(), 0));
    ASSERT_TRUE(a.rawData() == nullptr);
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
    ASSERT_TRUE(compare(Precision(0.001l), b, expected));
    TelemetryTests::asserts({.move_constructs = 1});
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type
TEST(dense_matrix_copy_assignment_operator_from_same_type, given_dense_matrix_of_same_size_should_copy_assign) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(3, 3);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1});
}

TEST(dense_matrix_copy_assignment_operator_from_same_type, given_dense_matrix_of_diff_size_should_copy_assign) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(1, 2);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}

TEST(dense_matrix_copy_assignment_operator_from_same_type, given_self_should_do_nothing) {
    // arrange
    DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
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
TEST(dense_matrix_copy_assignment_operator_from_diff_type, given_f_dense_matrix_of_same_size_should_copy_assign) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> b(3, 3);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1});
}

TEST(dense_matrix_copy_assignment_operator_from_diff_type, given_f_dense_matrix_of_diff_size_should_copy_assign) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> b(1, 2);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}
#pragma endregion
#pragma region copy_assignment_operator_from_like
TEST(dense_matrix_copy_assignment_operator_from_like, given_view_of_same_size_should_copy_assign) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrixView<float> expected(a, 2, 2, 0, 0);
    DenseMatrix<float> b(2, 2);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1});
}

TEST(dense_matrix_copy_assignment_operator_from_like, given_view_of_diff_size_should_copy_assign) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrixView<float> expected(a, 2, 2, 0, 0);
    DenseMatrix<float> b(3, 3);
    // act
    TelemetryTests::start();
    b = expected;
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(b.rows(), 2));
    ASSERT_TRUE(compare(b.columns(), 2));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.copy_assigns = 1, .allocations = 1, .deallocations = 1});
}
#pragma endregion
#pragma region move_assignment_operator
TEST(dense_matrix_move_assignment_oerator, given_dense_matrix_of_should_move_assign) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(2, 1);
    // act
    TelemetryTests::start();
    b = std::move(a);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a.rows(), 0));
    ASSERT_TRUE(compare(a.columns(), 0));
    ASSERT_TRUE(a.rawData() == nullptr);
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
    ASSERT_TRUE(compare(Precision(0.001f), b, expected));
    TelemetryTests::asserts({.move_assigns = 1, .deallocations = 1});
}

TEST(dense_matrix_move_assignment_operator_from_same_type, given_self_should_do_nothing) {
    // arrange
    DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
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
TEST(dense_matrix_reshape, given_same_dimensions_should_do_nothing_1) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {67, 8, 9}};
    DenseMatrix<float> a = expected;
    // act
    TelemetryTests::start();
    a.reshape(3, 3, false);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({});
}

TEST(dense_matrix_reshape, given_same_dimensions_should_do_nothing_2) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {67, 8, 9}};
    DenseMatrix<float> a = expected;
    // act
    TelemetryTests::start();
    a.reshape(3, 3, true);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({});
}

TEST(dense_matrix_reshape, given_same_dimensions_should_do_nothing_3) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {67, 8, 9}};
    DenseMatrix<float> a = expected;
    // act
    TelemetryTests::start();
    a.reshape(3, 3, false, 1);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({});
}

TEST(dense_matrix_reshape, given_same_dimensions_should_do_nothing_4) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {67, 8, 9}};
    DenseMatrix<float> a = expected;
    // act
    TelemetryTests::start();
    a.reshape(3, 3, true, 1);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({});
}

TEST(dense_matrix_reshape, given_new_dimensions_and_no_preserve_should_reshape) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const float* before = a.rawData();
    TelemetryTests::start();
    a.reshape(2, 3, false);
    TelemetryTests::end();
    const float* after = a.rawData();
    // assert
    ASSERT_TRUE(compare(a.rows(), 2));
    ASSERT_TRUE(compare(a.columns(), 3));
    ASSERT_TRUE(before != after);
    TelemetryTests::asserts({.allocations = 1, .deallocations = 1});
}

TEST(dense_matrix_reshape, given_new_dimensions_and_preserve_should_reshape) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}};
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const float* before = a.rawData();
    TelemetryTests::start();
    a.reshape(2, 3, true);
    TelemetryTests::end();
    const float* after = a.rawData();
    // assert
    ASSERT_TRUE(compare(a.rows(), 2));
    ASSERT_TRUE(compare(a.columns(), 3));
    ASSERT_TRUE(before != after);
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1, .deallocations = 1});
}

TEST(dense_matrix_reshape, given_new_dimensions_and_no_preserve_and_value_should_reshape) {
    // arrange
    const DenseMatrix<float> expected = {{67, 67, 67}, {67, 67, 67}};
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const float* before = a.rawData();
    TelemetryTests::start();
    a.reshape(2, 3, false, 67);
    TelemetryTests::end();
    const float* after = a.rawData();
    // assert
    ASSERT_TRUE(compare(a.rows(), 2));
    ASSERT_TRUE(compare(a.columns(), 3));
    ASSERT_TRUE(before != after);
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1, .deallocations = 1});
}

TEST(dense_matrix_reshape, given_new_dimensions_and_preserve_and_value_should_reshape) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3, 67}, {4, 5, 6, 67}};
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const float* before = a.rawData();
    TelemetryTests::start();
    a.reshape(2, 4, true, 67);
    TelemetryTests::end();
    const float* after = a.rawData();
    // assert
    ASSERT_TRUE(compare(a.rows(), 2));
    ASSERT_TRUE(compare(a.columns(), 4));
    ASSERT_TRUE(before != after);
    ASSERT_TRUE(compare(Precision(0.001f), a, expected));
    TelemetryTests::asserts({.allocations = 1, .deallocations = 1});
}
#pragma endregion
#pragma region at
TEST(dense_matrix_at, given_valid_indices_should_return_ref) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    TelemetryTests::start();
    float& ref = a.at(2, 2);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), ref, 9));
    ref = 4;
    ASSERT_TRUE(compare(Precision(0.001f), ref, 4));
    ASSERT_TRUE(&ref == &a.rawData()[8]);
    TelemetryTests::asserts({});
}

TEST(dense_matrix_at, given_valid_indices_should_return_const_ref) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    TelemetryTests::start();
    const float& ref = a.at(2, 2);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), ref, 9));
    ASSERT_TRUE(&ref == &a.rawData()[8]);
    TelemetryTests::asserts({});
}

TEST(dense_matrix_at, given_invalid_indices_should_throw_1) {
    // arrange
    const DenseMatrix<float> a(3, 3);
    // act / assert
    ASSERT_THROW([[maybe_unused]] const float& ref = a.at(4, 0), InvalidIndexException);
}

TEST(dense_matrix_at, given_invalid_indices_should_throw_2) {
    // arrange
    DenseMatrix<float> a(3, 3);
    // act / assert
    ASSERT_THROW([[maybe_unused]] float& ref = a.at(4, 0), InvalidIndexException);
}

TEST(dense_matrix_at, given_invalid_indices_should_throw_3) {
    // arrange
    const DenseMatrix<float> a(3, 3);
    // act / assert
    ASSERT_THROW([[maybe_unused]] const float& ref = a.at(0, 4), InvalidIndexException);
}

TEST(dense_matrix_at, given_invalid_indices_should_throw_5) {
    // arrange
    DenseMatrix<float> a(3, 3);
    // act / assert
    ASSERT_THROW([[maybe_unused]] float& ref = a.at(0, 4), InvalidIndexException);
}
#pragma endregion
#pragma region indexing_operator
TEST(dense_matrix_indexing_operator, given_valid_indices_should_return_ref) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    TelemetryTests::start();
    float& ref = a[2, 2];
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), ref, 9));
    ref = 4;
    ASSERT_TRUE(compare(Precision(0.001f), ref, 4));
    ASSERT_TRUE(&ref == &a.rawData()[8]);
    TelemetryTests::asserts({});
}

TEST(dense_matrix_indexing_operator, given_valid_indices_should_return_const_ref) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    TelemetryTests::start();
    const float& ref = a[2, 2];
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), ref, 9));
    ASSERT_TRUE(&ref == &a.rawData()[8]);
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region rows
TEST(dense_matrix_rows, given_dense_matrix_should_return_rows) {
    // arrange
    const DenseMatrix<float> a(3, 4);
    // act
    TelemetryTests::start();
    const std::size_t rows = a.rows();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(rows, 3));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region columns
TEST(dense_matrix_columns, given_dense_matrix_should_return_columns) {
    // arrange
    const DenseMatrix<float> a(3, 4);
    // act
    TelemetryTests::start();
    const std::size_t columns = a.columns();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(columns, 4));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region data
TEST(dense_matrix_data, given_index_should_return_const_reference) {
    // arrange
    DenseMatrix<int> a = {{1, 2, 3}, {4, 5, 6}};
    // act
    TelemetryTests::start();
    const int& a00 = a.data(0);
    const int& a10 = a.data(1);
    const int& a01 = a.data(2);
    const int& a11 = a.data(3);
    const int& a02 = a.data(4);
    const int& a12 = a.data(5);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a00, 1));
    ASSERT_TRUE(compare(a10, 4));
    ASSERT_TRUE(compare(a01, 2));
    ASSERT_TRUE(compare(a11, 5));
    ASSERT_TRUE(compare(a02, 3));
    ASSERT_TRUE(compare(a12, 6));
    a[1, 2] = 67;
    ASSERT_TRUE(compare(a12, 67));
    TelemetryTests::asserts({});
}

TEST(dense_matrix_data, given_dense_matrix_should_return_data_pointer) {
    // arrange
    DenseMatrix<int> a = {{1, 2, 3}, {4, 5, 6}};
    // act
    TelemetryTests::start();
    int& a00 = a.data(0);
    int& a10 = a.data(1);
    int& a01 = a.data(2);
    int& a11 = a.data(3);
    int& a02 = a.data(4);
    int& a12 = a.data(5);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(a00, 1));
    ASSERT_TRUE(compare(a10, 4));
    ASSERT_TRUE(compare(a01, 2));
    ASSERT_TRUE(compare(a11, 5));
    ASSERT_TRUE(compare(a02, 3));
    ASSERT_TRUE(compare(a12, 6));
    a12 = 67;
    ASSERT_TRUE(compare(a[1, 2], 67));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region raw_data
TEST(dense_matrix_raw_data, given_dense_matrix_should_return_const_data_pointer) {
    // arrange
    DenseMatrix<int> a = {{1, 2, 3}, {4, 5, 6}};
    // act
    TelemetryTests::start();
    const int* data = a.rawData();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(data != nullptr);
    ASSERT_TRUE(compare(data[0], 1));
    ASSERT_TRUE(compare(data[1], 4));
    ASSERT_TRUE(compare(data[2], 2));
    ASSERT_TRUE(compare(data[3], 5));
    ASSERT_TRUE(compare(data[4], 3));
    ASSERT_TRUE(compare(data[5], 6));
    a[1, 2] = 10;
    ASSERT_TRUE(compare(data[5], 10));
    TelemetryTests::asserts({});
}

TEST(dense_matrix_raw_data, given_dense_matrix_should_return_data_pointer) {
    // arrange
    DenseMatrix<int> a = {{1, 2, 3}, {4, 5, 6}};
    // act
    TelemetryTests::start();
    int* data = a.rawData();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(data != nullptr);
    ASSERT_TRUE(compare(data[0], 1));
    ASSERT_TRUE(compare(data[1], 4));
    ASSERT_TRUE(compare(data[2], 2));
    ASSERT_TRUE(compare(data[3], 5));
    ASSERT_TRUE(compare(data[4], 3));
    ASSERT_TRUE(compare(data[5], 6));
    data[5] = 10;
    ASSERT_TRUE(compare(a[1, 2], 10));
    TelemetryTests::asserts({});
}
#pragma endregion
