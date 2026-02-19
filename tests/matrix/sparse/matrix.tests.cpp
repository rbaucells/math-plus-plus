#include "gtest/gtest.h"

#include "mathpp/math.h"

#pragma region sparse_matrix
#pragma region set
TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    SparseMatrix<float> m(5, 5);
    // act
    m.set(2, 2, 3);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 1, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 1, 4);
    // act
    m.set(2, 2, 3);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mValues[1], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 2, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_3) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 4);
    m.set(2, 1, 5);
    // act
    m.set(2, 2, 3);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 3)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mValues[1], 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mValues[2], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[1], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[2], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 3, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_4) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 4);
    // act
    m.set(2, 2, 3);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mValues[1], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 2, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_f_1) {
    // arrange
    SparseMatrix<float> m(5, 5);
    const float* oldMValues = m.values();
    const int* oldMRowIndexes = m.rowIndices();
    const int* oldMColOffsets = m.colOffsets();
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 0)));
    ASSERT_TRUE(mValues == oldMValues);
    ASSERT_TRUE(mRowIndexes == oldMRowIndexes);
    ASSERT_TRUE(mColOffsets == oldMColOffsets);
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_f_2) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 1, 4);
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 1, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_f_3) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 5);
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 1, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_f_4) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 1, 4);
    m.set(1, 2, 5);
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mValues[1], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[1], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 2, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 4);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 1, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 1, 4);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 5);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mValues[1], 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 2, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_3) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 4);
    m.set(2, 1, 5);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 6);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 3)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mValues[1], 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mValues[2], 6, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[1], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[2], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 3, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_4) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 4);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 5);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mValues[1], 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 2, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_f_1) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 0)));
    ASSERT_TRUE(mValues != nullptr);
    ASSERT_TRUE(mRowIndexes != nullptr);
    ASSERT_TRUE(mColOffsets != nullptr);
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_f_2) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 1, 4);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 1, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_f_3) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 4);
    m.set(2, 2, 3);
    m.set(2, 1, 5);
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mValues[1], 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[1], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 2, 0.001f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_f_4) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 4);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<float, float>(mValues[0], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mRowIndexes[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[0], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[1], 0, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[2], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[3], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[4], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(mColOffsets[5], 1, 0.001f)));
}
#pragma endregion
#pragma endregion