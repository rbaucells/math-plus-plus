#include "gtest/gtest.h"

#include "mathpp/matrix/sparse/common/operators.h"

#pragma region constructor
TEST(sparse_matrix_view_constructor, given_f_sparse_matrix_should_construct) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    a.set(2, 2, 1);
    a.set(3, 2, 2);
    a.set(0, 0, 3);
    CSCSparseMatrix<float> expected(3, 3);
    expected.set(1, 1, 1);
    expected.set(2, 1, 2);
    // act
    const CSCSparseMatrixView<float> v(a, 3, 3, 1, 1);
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(v.columns(), 3)));
    ASSERT_TRUE((compare(v.rows(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), v, expected)));
}

TEST(sparse_matrix_view_constructor, given_cf_sparse_matrix_should_construct) {
    // arrange
    CSCSparseMatrix<std::complex<float>> a(5, 5);
    a.set(2, 2, {1, 2});
    a.set(3, 2, {3, 4});
    a.set(0, 0, {5, 6});
    CSCSparseMatrix<std::complex<float>> expected(3, 3);
    expected.set(1, 1, {1, 2});
    expected.set(2, 1, {3, 4});
    // act
    const CSCSparseMatrixView<std::complex<float>> v(a, 3, 3, 1, 1);
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(v.columns(), 3)));
    ASSERT_TRUE((compare(v.rows(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f),v, expected)));
}
#pragma endregion
#pragma region copy_constructor
TEST(sparse_matrix_view_copy_constructor, given_f_sparse_matrix_view_should_copy_construct) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    a.set(2, 2, 1);
    a.set(3, 2, 2);
    a.set(0, 0, 3);
    const CSCSparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act
    const CSCSparseMatrixView<float> newView = v;
    // assert
    ASSERT_TRUE((compare(newView.rows(), 3)));
    ASSERT_TRUE((compare(newView.columns(), 3)));
    ASSERT_TRUE((compare(newView.rowOffset(), 1)));
    ASSERT_TRUE((compare(newView.colOffset(), 1)));
    ASSERT_TRUE(&v.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), v, newView)));
}

TEST(sparse_matrix_view_copy_constructor, given_cf_sparse_matrix_view_should_copy_construct) {
    // arrange
    CSCSparseMatrix<std::complex<float>> a(5, 5);
    a.set(2, 2, {1, 2});
    a.set(3, 2, {3, 4});
    a.set(0, 0, {5, 6});
    const CSCSparseMatrixView<std::complex<float>> v(a, 3, 3, 1, 1);
    // act
    const CSCSparseMatrixView<std::complex<float>> newView = v;
    // assert
    ASSERT_TRUE((compare(newView.rows(), 3)));
    ASSERT_TRUE((compare(newView.columns(), 3)));
    ASSERT_TRUE((compare(newView.rowOffset(), 1)));
    ASSERT_TRUE((compare(newView.colOffset(), 1)));
    ASSERT_TRUE(&v.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), v, newView)));
}
#pragma endregion
#pragma region set
TEST(sparse_matrix_view_set, given_index_should_throw) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    CSCSparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW(v.set(0, 0, 1), InvalidOperationException);
}

TEST(sparse_matrix_view_set, given_big_column_index_should_throw_1) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    CSCSparseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW(v.set(3, 0, 1), InvalidIndexException);
}

TEST(sparse_matrix_view_set, given_big_row_index_should_throw_1) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    CSCSparseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW(v.set(0, 3, 1), InvalidIndexException);
}

TEST(sparse_matrix_view_set, given_big_column_index_should_throw_2) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    CSCSparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW(v.set(3, 0, 1), InvalidIndexException);
}

TEST(sparse_matrix_view_set, given_big_row_index_should_throw_2) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    CSCSparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW(v.set(0, 3, 1), InvalidIndexException);
}
#pragma endregion
#pragma region get
TEST(sparse_matrix_view_get, given_index_should_return_value_f) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    a.set(2, 2, 1);
    const CSCSparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act
    const float value = v.get(1, 1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 1)));
}

TEST(sparse_matrix_view_get, given_index_should_return_value_cf) {
    // arrange
    CSCSparseMatrix<std::complex<float>> a(5, 5);
    a.set(2, 2, {1, 2});
    const CSCSparseMatrixView<std::complex<float>> v(a, 3, 3, 1, 1);
    // act
    const std::complex<float> value = v.get(1, 1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(1, 2))));
}

TEST(sparse_matrix_view_get, given_big_column_index_should_throw_1) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    CSCSparseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(3, 0), InvalidIndexException);
}

TEST(sparse_matrix_view_get, given_big_row_index_should_throw_1) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    CSCSparseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(0, 3), InvalidIndexException);
}

TEST(sparse_matrix_view_get, given_big_column_index_should_throw_2) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    CSCSparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(3, 0), InvalidIndexException);
}

TEST(sparse_matrix_view_get, given_big_row_index_should_throw_2) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    CSCSparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(0, 3), InvalidIndexException);
}
#pragma endregion
#pragma region col_offset
TEST(sparse_matrix_view_col_offset, should_return_col_offset) {
    // arrange
    const CSCSparseMatrix<float> a(5, 5);
    const CSCSparseMatrixView<float> v(a, 3, 3, 1, 2);
    constexpr std::size_t expected = 1;
    // act
    const std::size_t colOffset = v.colOffset();
    // assert
    ASSERT_TRUE((compare(colOffset, expected)));
}
#pragma endregion
#pragma region row_offset
TEST(sparse_matrix_view_row_offset, should_return_row_offset) {
    // arrange
    const CSCSparseMatrix<float> a(5, 5);
    const CSCSparseMatrixView<float> v(a, 3, 3, 1, 2);
    constexpr std::size_t expected = 2;
    // act
    const std::size_t rowOffset = v.rowOffset();
    // assert
    ASSERT_TRUE((compare(rowOffset, expected)));
}
#pragma endregion
#pragma region owner
TEST(sparse_matrix_view_owner, should_return_owner) {
    // arrange
    const CSCSparseMatrix<float> a(5, 5);
    const CSCSparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act
    const CSCSparseMatrix<float>& owner = v.owner();
    // assert
    ASSERT_TRUE(&owner == &a);
}
#pragma endregion
