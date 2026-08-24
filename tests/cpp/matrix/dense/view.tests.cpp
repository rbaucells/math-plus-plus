#include "../../telemetry.tests.h"
#include "gtest/gtest.h"

#include "mathpp/implementation/common/compare.h"
#include "mathpp/implementation/matrix/dense/view.h"
#include "mathpp/implementation/matrix/dense/operators/compare.h"

#pragma region owner_constructor
TEST(dense_matrix_view_owner_constructor, given_dense_matrix_and_rows_and_columns_and_offsets_should_construct) {
    // arrange
    const DenseMatrix<double> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<double> expected = {{4, 5}, {7, 8}};
    // act
    TelemetryTests::start();
    const DenseMatrixView<double> view(a, 2, 2, 1, 0);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(view.rows(), 2));
    ASSERT_TRUE(compare(view.columns(), 2));
    ASSERT_TRUE(compare(view.rowOffset(), 1));
    ASSERT_TRUE(compare(view.colOffset(), 0));
    ASSERT_TRUE(&view.owner() == &a);
    ASSERT_TRUE(compare(Precision(0.001), view, expected));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region indexing_operator
TEST(dense_matrix_view_indexing_operator, given_valid_indices_should_return_const_ref) {
    // arrange
    DenseMatrix<long> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrixView<long> view(a, 2, 2, 1, 0);
    // act
    TelemetryTests::start();
    const long& ref = view[1, 0];
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(ref, 7));
    a[2, 0] = 67;
    ASSERT_TRUE(compare(ref, 67));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region get
TEST(dense_matrix_view_get, given_valid_indices_should_return_value) {
    // arrange
    DenseMatrix<long> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrixView<long> view(a, 2, 2, 1, 0);
    // act
    TelemetryTests::start();
    const long val = view.get(1, 0);
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(val, 7));
    a[2, 0] = 67;
    ASSERT_TRUE(compare(view.get(1, 0), 67));
    TelemetryTests::asserts({});
}

TEST(dense_matrix_view_get, given_invalid_indices_should_throw_1) {
    // arrange
    DenseMatrix<long> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrixView<long> view(a, 2, 2, 1, 0);
    // act / assert
    ASSERT_THROW(view.get(4, 0), InvalidIndexException);
}

TEST(dense_matrix_view_get, given_invalid_indices_should_throw_2) {
    // arrange
    DenseMatrix<long> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrixView<long> view(a, 2, 2, 1, 0);
    // act / assert
    ASSERT_THROW(view.get(4, 0), InvalidIndexException);
}
#pragma endregion
#pragma region set
TEST(dense_matrix_view_set, given_valid_indices_should_throw) {
    // arrange
    DenseMatrix<long> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrixView<long> view(a, 2, 2, 1, 0);
    // act / assert
    ASSERT_THROW(view.set(0, 1, 5), InvalidOperationException);
}

TEST(dense_matrix_view_set, given_invalid_indices_should_throw) {
    // arrange
    DenseMatrix<long> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrixView<long> view(a, 2, 2, 1, 0);
    // act / assert
    ASSERT_THROW(view.set(3, 1, 5), InvalidOperationException);
}
#pragma endregion
#pragma region row_offset
TEST(dense_matrix_view_row_offset, given_dense_matrix_view_should_return_row_offset) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrixView<float> view(a, 2, 2, 1, 0);
    // act
    TelemetryTests::start();
    const std::size_t rowOffset = view.rowOffset();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(rowOffset, 1));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region col_offset
TEST(dense_matrix_view_col_offset, given_dense_matrix_view_should_return_col_offset) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrixView<float> view(a, 2, 2, 1, 0);
    // act
    TelemetryTests::start();
    const std::size_t colOffset = view.colOffset();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(colOffset, 0));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region rows
TEST(dense_matrix_view_rows, given_dense_matrix_view_should_return_rows) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrixView<float> view(a, 1, 2, 1, 0);
    // act
    TelemetryTests::start();
    const std::size_t rows = view.rows();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(rows, 1));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region columns
TEST(dense_matrix_view_columns, given_dense_matrix_view_should_return_columns) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrixView<float> view(a, 1, 2, 1, 0);
    // act
    TelemetryTests::start();
    const std::size_t columns = view.columns();
    TelemetryTests::end();
    // assert
    ASSERT_TRUE(compare(columns, 2));
    TelemetryTests::asserts({});
}
#pragma endregion
#pragma region owner
TEST(dense_matrix_view_owner, given_dense_matrix_should_return_owner) {
    // arrange
    const DenseMatrix<std::complex<int>> a = {{{1, 0}, {2, 3}, {4, 67}}, {{3, 6}, {3, 1}, {3, 7}}, {{0, 0}, {0, 1}, {1, 0}}};
    const DenseMatrixView<std::complex<int>> view(a, 2, 2, 1, 0);
    // act
    const DenseMatrix<std::complex<int>>& owner = view.owner();
    // assert
    ASSERT_TRUE(&owner == &a);
}
#pragma endregion
