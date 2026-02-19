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

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    // act
    m.set(2, 2, {1, 2});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 1)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 1, {1, 2});
    // act
    m.set(2, 2, {3, 4});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 2)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_3) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    m.set(2, 1, {3, 4});
    // act
    m.set(2, 2, {5, 6});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[2], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[1], 1)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[2], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 3)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 3)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 3)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_4) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    // act
    m.set(2, 2, {3, 4});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 2)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_cf_1) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    const std::complex<float>* oldMValues = m.values();
    const int* oldMRowIndexes = m.rowIndices();
    const int* oldMColOffsets = m.colOffsets();
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 0)));
    ASSERT_TRUE(mValues == oldMValues);
    ASSERT_TRUE(mRowIndexes == oldMRowIndexes);
    ASSERT_TRUE(mColOffsets == oldMColOffsets);
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_cf_2) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 1, {1, 2});
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 1)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_cf_3) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 1)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_cf_4) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 1, {1, 2});
    m.set(1, 2, {3, 4});
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[1], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[1], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 2)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 2, {1, 2});
    // act
    m.set(2, 2, {3, 4});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 1)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 1, {1, 2});
    m.set(2, 2, {3, 4});
    // act
    m.set(2, 2, {5, 6});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[1], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 2)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_3) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    m.set(2, 1, {3, 4});
    m.set(2, 2, {5, 6});
    // act
    m.set(2, 2, {7, 8});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[2], {7, 8}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[1], 1)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[2], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 3)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 3)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 3)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_4) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    m.set(2, 2, {3, 4});
    // act
    m.set(2, 2, {5, 6});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[1], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 2)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_1) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 2, {1, 2});
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 0)));
    ASSERT_TRUE(mValues != nullptr);
    ASSERT_TRUE(mRowIndexes != nullptr);
    ASSERT_TRUE(mColOffsets != nullptr);
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_2) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 1, {1, 2});
    m.set(2, 2, {3, 4});
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 1)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_3) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    m.set(2, 2, {3, 4});
    m.set(2, 1, {5, 6});
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 2)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[1], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[1], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 2)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_4) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    m.set(2, 2, {3, 4});
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const int* mRowIndexes = m.rowIndices();
    const int* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(m.nnz(), 1)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(mValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(mRowIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[1], 0)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[3], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[4], 1)));
    ASSERT_TRUE((compare<int, int>(mColOffsets[5], 1)));
}

TEST(sparse_matrix_set, given_negative_row_index_should_throw) {
    // arrange
    SparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(m.set(-1, 2, 1), InvalidIndexException);
}

TEST(sparse_matrix_set, given_negative_column_index_should_throw) {
    // arrange
    SparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(m.set(2, -1, 1), InvalidIndexException);
}

TEST(sparse_matrix_set, given_big_row_index_should_throw) {
    // arrange
    SparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(m.set(5, 2, 1), InvalidIndexException);
}

TEST(sparse_matrix_set, given_big_column_index_should_throw) {
    // arrange
    SparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(m.set(2, 5, 1), InvalidIndexException);
}
#pragma endregion
#pragma region get
TEST(sparse_matrix_get, given_index_should_return_value_f) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 3, 1);
    // act
    const float value = m.get(2, 3);
    // assert
    ASSERT_TRUE((compare<float, float>(value, 1, 0.001f)));
}

TEST(sparse_matrix_get, given_index_should_return_zero_f) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 3, 1);
    // act
    const float value = m.get(1, 2);
    // assert
    ASSERT_TRUE((compare<float, float>(value, 0, 0.001f)));
}

TEST(sparse_matrix_get, given_index_should_return_value_cf) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 3, {1, 2});
    // act
    const std::complex<float> value = m.get(2, 3);
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(value, {1, 2}, 0.001f)));
}

TEST(sparse_matrix_get, given_index_should_return_zero_cf) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 3, {1, 2});
    // act
    const std::complex<float> value = m.get(1, 2);
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(value, {0, 0}, 0.001f)));
}

TEST(sparse_matrix_get, given_negative_row_index_should_throw) {
    // arrange
    const SparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(std::ignore = m.get(-1, 2), InvalidIndexException);
}

TEST(sparse_matrix_get, given_negative_column_index_should_throw) {
    // arrange
    const SparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(std::ignore = m.get(2, -1), InvalidIndexException);
}

TEST(sparse_matrix_get, given_big_row_index_should_throw) {
    // arrange
    const SparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(std::ignore = m.get(5, 2), InvalidIndexException);
}

TEST(sparse_matrix_get, given_big_column_index_should_throw) {
    // arrange
    const SparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(std::ignore = m.get(2, 5), InvalidIndexException);
}
#pragma endregion
#pragma region default_constructor
TEST(sparse_matrix_default_constructor, given_rows_and_cols_should_construct_f) {
    // act
    SparseMatrix<float> a(5, 5);
    // assert
    ASSERT_TRUE((compare<int, int>(a.rows, 5)));
    ASSERT_TRUE((compare<int, int>(a.columns, 5)));
    ASSERT_TRUE((compare<int, int>(a.nnz(), 0)));
    ASSERT_TRUE(a.values() != nullptr);
    ASSERT_TRUE(a.rowIndices() != nullptr);
    ASSERT_TRUE(a.colOffsets() != nullptr);
}

TEST(sparse_matrix_default_constructor, given_rows_and_cols_should_construct_cf) {
    // act
    SparseMatrix<std::complex<float>> a(5, 5);
    // assert
    ASSERT_TRUE((compare<int, int>(a.rows, 5)));
    ASSERT_TRUE((compare<int, int>(a.columns, 5)));
    ASSERT_TRUE((compare<int, int>(a.nnz(), 0)));
    ASSERT_TRUE(a.values() != nullptr);
    ASSERT_TRUE(a.rowIndices() != nullptr);
    ASSERT_TRUE(a.colOffsets() != nullptr);
}

TEST(sparse_matrix_default_constructor, given_negative_rows_should_throw) {
    // act / assert
    ASSERT_THROW(std::ignore = SparseMatrix<float>(-1, 5), InvalidIndexException);
}

TEST(sparse_matrix_default_constructor, given_negative_cols_should_throw) {
    // act / assert
    ASSERT_THROW(std::ignore = SparseMatrix<float>(5, -1), InvalidIndexException);
}
#pragma endregion
#pragma region copy_constructor_from_same_type_sparse_matrix
TEST(sparse_matrix_copy_constructor_from_same_type_sparse_matrix, given_f_sparse_matrix_should_copy_construct) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    // act
    const SparseMatrix<float> b = a;
    const float* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<float, float>(bValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[2], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}

TEST(sparse_matrix_copy_constructor_from_same_type_sparse_matrix, given_cf_sparse_matrix_should_copy_construct) {
    // arrange
    SparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    // act
    const SparseMatrix<std::complex<float>> b = a;
    const std::complex<float>* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[2], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_sparse_matrix
TEST(sparse_matrix_copy_constructor_from_different_type_sparse_matrix, given_f_sparse_matrix_should_copy_construct) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    // act
    const SparseMatrix<std::complex<float>> b = a;
    const std::complex<float>* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[2], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}
#pragma endregion
#pragma region copy_constructor_from_same_type_sparse_matrix_base
TEST(sparse_matrix_copy_constructor_from_same_type_sparse_matrix_base, given_f_sparse_matrix_base_should_copy_construct) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    // act
    const SparseMatrix<float> b = static_cast<const SparseMatrixBase<float>&>(a);
    const float* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<float, float>(bValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[2], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}

TEST(sparse_matrix_copy_constructor_from_same_type_sparse_matrix_base, given_cf_sparse_matrix_base_should_copy_construct) {
    // arrange
    SparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    // act
    const SparseMatrix<std::complex<float>> b = static_cast<const SparseMatrixBase<std::complex<float>>&>(a);
    const std::complex<float>* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[2], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_sparse_matrix_base
TEST(sparse_matrix_copy_constructor_from_different_type_sparse_matrix_base, given_f_sparse_matrix_base_should_copy_construct) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    // act
    const SparseMatrix<std::complex<float>> b = static_cast<const SparseMatrixBase<float>&>(a);
    const std::complex<float>* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[2], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}
#pragma endregion
#pragma region move_constructor
TEST(sparse_matrix_move_constructor, given_f_sparse_matrix_should_move_construct_and_invalidate_other_data) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    // act
    const SparseMatrix<float> b = std::move(a);
    const float* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<float, float>(bValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[2], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}

TEST(sparse_matrix_move_constructor, given_cf_sparse_matrix_should_move_construct_and_invalidate_other_data) {
    // arrange
    SparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    // act
    const SparseMatrix<std::complex<float>> b = std::move(a);
    const std::complex<float>* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[2], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_sparse_matrix
TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix, given_f_sparse_matrix_should_copy_assign) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(5, 5);
    // act
    b = a;
    const float* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<float, float>(bValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[2], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}

TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix, given_cf_sparse_matrix_should_copy_assign) {
    // arrange
    SparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    SparseMatrix<std::complex<float>> b(5, 5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[2], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}

TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix, given_sparse_matrix_of_different_size_should_throw) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(3, 3);
    // act / assert
    ASSERT_THROW(b = a, InvalidDimensionException);
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_sparse_matrix
TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix, given_f_sparse_matrix_should_copy_assign) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<std::complex<float>> b(5, 5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[2], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}

TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix, given_f_sparse_matrix_of_different_size_should_throw) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<std::complex<float>> b(3, 3);
    // act / assert
    ASSERT_THROW(b = a, InvalidDimensionException);
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_sparse_matrix_base
TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix_base, given_f_sparse_matrix_base_should_copy_assign) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(5, 5);
    // act
    b = static_cast<const SparseMatrixBase<float>&>(a);
    const float* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<float, float>(bValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[2], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}

TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix_base, given_cf_sparse_matrix_base_should_copy_assign) {
    // arrange
    SparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    SparseMatrix<std::complex<float>> b(5, 5);
    // act
    b = static_cast<const SparseMatrixBase<std::complex<float>>&>(a);
    const std::complex<float>* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[2], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}

TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix_base, given_sparse_matrix_base_of_different_size_should_throw) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(3, 3);
    // act / assert
    ASSERT_THROW(b = static_cast<const SparseMatrixBase<float>&>(a), InvalidDimensionException);
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_sparse_matrix_base
TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix_base, given_f_sparse_matrix_base_should_copy_assign) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<std::complex<float>> b(5, 5);
    // act
    b = static_cast<const SparseMatrixBase<float>&>(a);
    const std::complex<float>* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, float>(bValues[2], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}

TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix_base, given_sparse_matrix_base_of_different_size_should_throw) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<std::complex<float>> b(3, 3);
    // act / assert
    ASSERT_THROW(b = static_cast<const SparseMatrixBase<float>&>(a), InvalidDimensionException);
}
#pragma endregion
#pragma region move_assignment_operator
TEST(sparse_matrix_move_assignment_operator, given_f_sparse_matrix_should_move_assign) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(5, 5);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<float, float>(bValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(bValues[2], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}

TEST(sparse_matrix_move_assignment_operator, given_cf_sparse_matrix_should_move_assign) {
    // arrange
    SparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    SparseMatrix<std::complex<float>> b(5, 5);
    // act
    b = std::move(a);
    const std::complex<float>* bValues = b.values();
    const int* bRowIndexes = b.rowIndices();
    const int* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare<int, int>(b.rows, 5)));
    ASSERT_TRUE((compare<int, int>(b.columns, 5)));
    ASSERT_TRUE((compare<int, int>(b.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(bValues[2], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[0], 0)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[1], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[2], 1)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[3], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[4], 2)));
    ASSERT_TRUE((compare<int, int>(bColOffsets[5], 3)));
}

TEST(sparse_matrix_move_assignment_operator, given_sparse_matrix_of_different_size_should_throw) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(3, 3);
    // act / assert
    ASSERT_THROW(b = std::move(a), InvalidDimensionException);
}
#pragma endregion
#pragma endregion