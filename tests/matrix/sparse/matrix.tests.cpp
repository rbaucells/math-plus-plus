#include "gtest/gtest.h"

#include "mathpp/matrix.h"

#pragma region sparse_matrix
#pragma region set
TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    SparseMatrix<float> m(5, 5);
    // act
    m.set(2, 2, 3);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 3.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 1.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 1, 4);
    // act
    m.set(2, 2, 3);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], 3.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 2.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_3) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 4);
    m.set(2, 1, 5);
    // act
    m.set(2, 2, 3);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[2], 3.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[1], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[2], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 3.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 3.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_4) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 4);
    // act
    m.set(2, 2, 3);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], 3.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 2.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_f_1) {
    // arrange
    SparseMatrix<float> m(5, 5);
    const float* oldMValues = m.values();
    const std::size_t* oldMRowIndexes = m.rowIndices();
    const std::size_t* oldMColOffsets = m.colOffsets();
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 0)));
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
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 1.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_f_3) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 5);
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 1.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_f_4) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 1, 4);
    m.set(1, 2, 5);
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[1], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 2.0f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 4);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 1.0f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 1, 4);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 5);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 2.0f)));
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
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[2], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[1], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[2], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 3.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 3.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_4) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 4);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 5);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 2.0f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_f_1) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 0)));
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
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 1.0f)));
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
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[1], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 2.0f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_f_4) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(1, 2, 4);
    m.set(2, 2, 3);
    // act
    m.set(2, 2, 0);
    const float* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), mColOffsets[5], 1.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    // act
    m.set(2, 2, {1, 2});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 1.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 1, {1, 2});
    // act
    m.set(2, 2, {3, 4});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(mRowIndexes[0], 1.0f)));
    ASSERT_TRUE((compare(mRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 2.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_3) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    m.set(2, 1, {3, 4});
    // act
    m.set(2, 2, {5, 6});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(mRowIndexes[1], 1.0f)));
    ASSERT_TRUE((compare(mRowIndexes[2], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 3.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 3.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_4) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    // act
    m.set(2, 2, {3, 4});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(mRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 2.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_cf_1) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    const std::complex<float>* oldMValues = m.values();
    const std::size_t* oldMRowIndexes = m.rowIndices();
    const std::size_t* oldMColOffsets = m.colOffsets();
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 0)));
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
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(mRowIndexes[0], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 1.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_cf_3) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 1.0f)));
}

TEST(sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_set_cf_4) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 1, {1, 2});
    m.set(1, 2, {3, 4});
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(mRowIndexes[1], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 2.0f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 2, {1, 2});
    // act
    m.set(2, 2, {3, 4});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 1.0f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 1, {1, 2});
    m.set(2, 2, {3, 4});
    // act
    m.set(2, 2, {5, 6});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(mRowIndexes[0], 1.0f)));
    ASSERT_TRUE((compare(mRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 2.0f)));
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
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[2], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(mRowIndexes[1], 1.0f)));
    ASSERT_TRUE((compare(mRowIndexes[2], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 3.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 3.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_4) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    m.set(2, 2, {3, 4});
    // act
    m.set(2, 2, {5, 6});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(mRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 2.0f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_1) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 2, {1, 2});
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 0)));
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
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(mRowIndexes[0], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 1.0f)));
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
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[1], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(mRowIndexes[1], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 2.0f)));
}

TEST(sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_4) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(1, 2, {1, 2});
    m.set(2, 2, {3, 4});
    // act
    m.set(2, 2, {0, 0});
    const std::complex<float>* mValues = m.values();
    const std::size_t* mRowIndexes = m.rowIndices();
    const std::size_t* mColOffsets = m.colOffsets();
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), mValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(mRowIndexes[0], 2.0f)));
    ASSERT_TRUE((compare(mColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(mColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(mColOffsets[5], 1.0f)));
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
    ASSERT_TRUE((compare(Precision(0.001f), value, 1)));
}

TEST(sparse_matrix_get, given_index_should_return_zero_f) {
    // arrange
    SparseMatrix<float> m(5, 5);
    m.set(2, 3, 1);
    // act
    const float value = m.get(1, 2);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 0)));
}

TEST(sparse_matrix_get, given_index_should_return_value_cf) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 3, {1, 2});
    // act
    const std::complex<float> value = m.get(2, 3);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(1, 2))));
}

TEST(sparse_matrix_get, given_index_should_return_zero_cf) {
    // arrange
    SparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 3, {1, 2});
    // act
    const std::complex<float> value = m.get(1, 2);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(0, 0))));
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
    ASSERT_TRUE((compare(a.rows(), 5)));
    ASSERT_TRUE((compare(a.columns(), 5)));
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE(a.values() != nullptr);
    ASSERT_TRUE(a.rowIndices() != nullptr);
    ASSERT_TRUE(a.colOffsets() != nullptr);
}

TEST(sparse_matrix_default_constructor, given_rows_and_cols_should_construct_cf) {
    // act
    SparseMatrix<std::complex<float>> a(5, 5);
    // assert
    ASSERT_TRUE((compare(a.rows(), 5)));
    ASSERT_TRUE((compare(a.columns(), 5)));
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE(a.values() != nullptr);
    ASSERT_TRUE(a.rowIndices() != nullptr);
    ASSERT_TRUE(a.colOffsets() != nullptr);
}
#pragma endregion
#pragma region intializer_list_constructor
TEST(sparse_matrix_initializer_list_constructor, given_rows_cols_and_value_col_index_row_index_tuples_should_construct_f) {
    // arrange / act
    SparseMatrix<float> v(3, 3, {{1, 0, 0}, {5, 1, 1}, {6, 2, 1}, {9, 2, 2}});
    const std::size_t* vColOffsets = v.colOffsets();
    const std::size_t* vRowIndices = v.rowIndices();
    const float* vValues = v.values();
    // assert
    ASSERT_TRUE(compare(v.rows(), 3));
    ASSERT_TRUE(compare(v.columns(), 3));
    ASSERT_TRUE(compare(v.nnz(), 4));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[0], 1));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[1],  5));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[2], 6));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[3], 9));
    ASSERT_TRUE(compare(vRowIndices[0], 0));
    ASSERT_TRUE(compare(vRowIndices[1], 1));
    ASSERT_TRUE(compare(vRowIndices[2], 1));
    ASSERT_TRUE(compare(vRowIndices[3], 2));
    ASSERT_TRUE(compare(vColOffsets[0], 0));
    ASSERT_TRUE(compare(vColOffsets[1], 1));
    ASSERT_TRUE(compare(vColOffsets[2], 2));
    ASSERT_TRUE(compare(vColOffsets[3], 4));
}

TEST(sparse_matrix_initializer_list_constructor, given_rows_cols_and_value_col_index_row_index_tuples_should_construct_cf) {
    // arrange / act
    SparseMatrix<std::complex<float>> v(3, 3, {{{1, 2}, 0, 0}, {{5, 6}, 1, 1}, {{6, 7}, 2, 1}, {{9, 10}, 2, 2}});
    const std::size_t* vColOffsets = v.colOffsets();
    const std::size_t* vRowIndices = v.rowIndices();
    const std::complex<float>* vValues = v.values();
    // assert
    ASSERT_TRUE(compare(v.rows(), 3));
    ASSERT_TRUE(compare(v.columns(), 3));
    ASSERT_TRUE(compare(v.nnz(), 4));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2)));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[1],  std::complex<float>(5, 6)));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[2], std::complex<float>(6, 7)));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[3], std::complex<float>(9, 10)));
    ASSERT_TRUE(compare(vRowIndices[0], 0));
    ASSERT_TRUE(compare(vRowIndices[1], 1));
    ASSERT_TRUE(compare(vRowIndices[2], 1));
    ASSERT_TRUE(compare(vRowIndices[3], 2));
    ASSERT_TRUE(compare(vColOffsets[0], 0));
    ASSERT_TRUE(compare(vColOffsets[1], 1));
    ASSERT_TRUE(compare(vColOffsets[2], 2));
    ASSERT_TRUE(compare(vColOffsets[3], 4));
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
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
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
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
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
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}
#pragma endregion
// #pragma region copy_constructor_from_same_type_sparse_matrix_base
// TEST(sparse_matrix_copy_constructor_from_same_type_sparse_matrix_base, given_f_sparse_matrix_base_should_copy_construct) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     // act
//     const SparseMatrix<float> b = static_cast<const SparseMatrixBase<float>&>(a);
//     const float* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_constructor_from_same_type_sparse_matrix_base, given_cf_sparse_matrix_base_should_copy_construct) {
//     // arrange
//     SparseMatrix<std::complex<float>> a(5, 5);
//     a.set(0, 0, {1, 2});
//     a.set(2, 2, {3, 4});
//     a.set(4, 4, {5, 6});
//     // act
//     const SparseMatrix<std::complex<float>> b = static_cast<const SparseMatrixBase<std::complex<float>>&>(a);
//     const std::complex<float>* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 2))));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(3, 4))));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(5, 6))));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
// #pragma endregion
// #pragma region copy_constructor_from_different_type_sparse_matrix_base
// TEST(sparse_matrix_copy_constructor_from_different_type_sparse_matrix_base, given_f_sparse_matrix_base_should_copy_construct) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     // act
//     const SparseMatrix<std::complex<float>> b = static_cast<const SparseMatrixBase<float>&>(a);
//     const std::complex<float>* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
// #pragma endregion
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
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare(a.rows(), 0)));
    ASSERT_TRUE((compare(a.columns(), 0)));
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
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
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare(a.rows(), 0)));
    ASSERT_TRUE((compare(a.columns(), 0)));
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_sparse_matrix
TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix, given_f_sparse_matrix_of_same_size_diff_nnz_should_copy_assign) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(5, 5);
    // act
    b = a;
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix, given_f_sparse_matrix_of_same_size_same_nnz_should_copy_assign) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(5, 5);
    b.set(0, 1, 1);
    b.set(2, 1, 2);
    b.set(4, 2, 4);
    // act
    b = a;
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix, given_f_sparse_matrix_of_diff_size_diff_nnz_should_copy_assign_1) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(4, 5);
    // act
    b = a;
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix, given_f_sparse_matrix_of_diff_size_diff_nnz_should_copy_assign_2) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(5, 4);
    // act
    b = a;
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix, given_f_sparse_matrix_of_diff_size_same_nnz_should_copy_assign_1) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(4, 5);
    b.set(0, 1, 1);
    b.set(2, 1, 2);
    b.set(4, 2, 4);
    // act
    b = a;
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix, given_f_sparse_matrix_of_diff_size_same_nnz_should_copy_assign_2) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(5, 4);
    b.set(0, 1, 1);
    b.set(2, 1, 2);
    b.set(3, 2, 4);
    // act
    b = a;
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix, given_cf_sparse_matrix_of_same_size_diff_nnz_should_copy_assign) {
    // arrange
    SparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    SparseMatrix<std::complex<float>> b(5, 5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix, given_f_self_should_do_nothing) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    // act
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-assign-overloaded"
    // ReSharper disable once CppIdenticalOperandsInBinaryExpression
    a = a;
#pragma GCC diagnostic pop
    const float* aValues = a.values();
    const std::size_t* aRowIndexes = a.rowIndices();
    const std::size_t* aColOffsets = a.colOffsets();
    // assert
    ASSERT_TRUE((compare(a.rows(), 5)));
    ASSERT_TRUE((compare(a.columns(), 5)));
    ASSERT_TRUE((compare(a.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), aValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), aValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), aValues[2], 3.0f)));
    ASSERT_TRUE((compare(aRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(aRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(aRowIndexes[2], 4)));
    ASSERT_TRUE((compare(aColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(aColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(aColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(aColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(aColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(aColOffsets[5], 3.0f)));
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_sparse_matrix
TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix, given_f_sparse_matrix_of_same_size_diff_nnz_should_copy_assign) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<std::complex<float>> b(5, 5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix, given_f_sparse_matrix_of_same_size_same_nnz_should_copy_assign) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<std::complex<float>> b(5, 5);
    b.set(1, 3, 12);
    b.set(3, 2, 23);
    b.set(4, 4, 5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix, given_f_sparse_matrix_of_diff_size_diff_nnz_should_copy_assign_1) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<std::complex<float>> b(4, 5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix, given_f_sparse_matrix_of_diff_size_diff_nnz_should_copy_assign_2) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<std::complex<float>> b(5, 4);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix, given_f_sparse_matrix_of_same_size_same_nnz_should_copy_assign_1) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<std::complex<float>> b(4, 5);
    b.set(1, 3, 12);
    b.set(3, 2, 23);
    b.set(4, 3, 5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix, given_f_sparse_matrix_of_same_size_same_nnz_should_copy_assign_2) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<std::complex<float>> b(5, 4);
    b.set(1, 3, 12);
    b.set(3, 2, 23);
    b.set(3, 4, 5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}
#pragma endregion
// #pragma region copy_assignment_operator_from_same_type_sparse_matrix_base
// TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix_base, given_f_sparse_matrix_base_of_same_size_diff_nnz_should_copy_assign) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<float> b(5, 5);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const float* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix_base, given_f_sparse_matrix_base_of_same_size_same_nnz_should_copy_assign) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<float> b(5, 5);
//     b.set(1, 3, 45);
//     b.set(3, 2, 67);
//     b.set(4, 4, 89);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const float* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix_base, given_f_sparse_matrix_base_of_same_size_diff_nnz_should_copy_assign_1) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<float> b(4, 5);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const float* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix_base, given_f_sparse_matrix_base_of_same_size_diff_nnz_should_copy_assign_2) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<float> b(5, 4);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const float* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix_base, given_f_sparse_matrix_base_of_same_size_same_nnz_should_copy_assign_1) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<float> b(4, 5);
//     b.set(1, 3, 45);
//     b.set(3, 2, 67);
//     b.set(4, 3, 89);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const float* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix_base, given_f_sparse_matrix_base_of_same_size_same_nnz_should_copy_assign_2) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<float> b(5, 4);
//     b.set(1, 3, 45);
//     b.set(3, 2, 67);
//     b.set(3, 4, 89);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const float* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix_base, given_cf_sparse_matrix_base_of_same_size_diff_nnz_should_copy_assign) {
//     // arrange
//     SparseMatrix<std::complex<float>> a(5, 5);
//     a.set(0, 0, {1, 2});
//     a.set(2, 2, {3, 4});
//     a.set(4, 4, {5, 6});
//     SparseMatrix<std::complex<float>> b(5, 5);
//     // act
//     b = static_cast<const SparseMatrixBase<std::complex<float>>&>(a);
//     const std::complex<float>* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 2))));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(3, 4))));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(5, 6))));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_same_type_sparse_matrix_base, given_f_self_should_do_nothing) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     // act
//     a = static_cast<const SparseMatrixBase<float>&>(a);
//     const float* aValues = a.values();
//     const std::size_t* aRowIndexes = a.rowIndices();
//     const std::size_t* aColOffsets = a.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(a.rows(), 5)));
//     ASSERT_TRUE((compare(a.columns(), 5)));
//     ASSERT_TRUE((compare(a.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), aValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), aValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), aValues[2], 3.0f)));
//     ASSERT_TRUE((compare(aRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(aRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(aRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(aColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(aColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(aColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(aColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(aColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(aColOffsets[5], 3.0f)));
// }
// #pragma endregion
// #pragma region copy_assignment_operator_from_different_type_sparse_matrix_base
// TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix_base, given_f_sparse_matrix_base_of_same_size_diff_nnz_should_copy_assign) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<std::complex<float>> b(5, 5);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const std::complex<float>* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix_base, given_f_sparse_matrix_base_of_same_size_same_nnz_should_copy_assign) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<std::complex<float>> b(5, 5);
//     b.set(1, 3, 45);
//     b.set(3, 2, 67);
//     b.set(4, 4, 89);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const std::complex<float>* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix_base, given_f_sparse_matrix_base_of_diff_size_diff_nnz_should_copy_assign_1) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<std::complex<float>> b(4, 5);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const std::complex<float>* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix_base, given_f_sparse_matrix_base_of_diff_size_diff_nnz_should_copy_assign_2) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<std::complex<float>> b(5, 4);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const std::complex<float>* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix_base, given_f_sparse_matrix_base_of_diff_size_same_nnz_should_copy_assign_1) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<std::complex<float>> b(4, 5);
//     b.set(1, 3, 45);
//     b.set(3, 2, 67);
//     b.set(4, 3, 89);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const std::complex<float>* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
//
// TEST(sparse_matrix_copy_assignment_operator_from_different_type_sparse_matrix_base, given_f_sparse_matrix_base_of_diff_size_same_nnz_should_copy_assign_2) {
//     // arrange
//     SparseMatrix<float> a(5, 5);
//     a.set(0, 0, 1);
//     a.set(2, 2, 2);
//     a.set(4, 4, 3);
//     SparseMatrix<std::complex<float>> b(5, 4);
//     b.set(1, 3, 45);
//     b.set(3, 2, 67);
//     b.set(3, 4, 89);
//     // act
//     b = static_cast<const SparseMatrixBase<float>&>(a);
//     const std::complex<float>* bValues = b.values();
//     const std::size_t* bRowIndexes = b.rowIndices();
//     const std::size_t* bColOffsets = b.colOffsets();
//     // assert
//     ASSERT_TRUE((compare(b.rows(), 5)));
//     ASSERT_TRUE((compare(b.columns(), 5)));
//     ASSERT_TRUE((compare(b.nnz(), 3)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
//     ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
//     ASSERT_TRUE((compare(bRowIndexes[2], 4)));
//     ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
//     ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
//     ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
//     ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
// }
// #pragma endregion
#pragma region move_assignment_operator
TEST(sparse_matrix_move_assignment_operator, given_f_sparse_matrix_of_same_size_diff_nnz_should_move_assign) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(5, 5);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_move_assignment_operator, given_f_sparse_matrix_of_same_size_same_nnz_should_move_assign) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(5, 5);
    b.set(1, 3, 45);
    b.set(3, 2, 67);
    b.set(4, 4, 89);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_move_assignment_operator, given_f_sparse_matrix_of_diff_size_diff_nnz_should_move_assign_1) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(4, 5);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_move_assignment_operator, given_f_sparse_matrix_of_diff_size_diff_nnz_should_move_assign_2) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(5, 4);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_move_assignment_operator, given_f_sparse_matrix_of_diff_size_same_nnz_should_move_assign_1) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(4, 5);
    b.set(1, 3, 45);
    b.set(3, 2, 67);
    b.set(4, 3, 89);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_move_assignment_operator, given_f_sparse_matrix_of_diff_size_same_nnz_should_move_assign_2) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    SparseMatrix<float> b(5, 4);
    b.set(1, 3, 45);
    b.set(3, 2, 67);
    b.set(3, 4, 89);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_move_assignment_operator, given_cf_sparse_matrix_of_same_size_diff_nnz_should_move_assign) {
    // arrange
    SparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    SparseMatrix<std::complex<float>> b(5, 5);
    // act
    b = std::move(a);
    const std::complex<float>* bValues = b.values();
    const std::size_t* bRowIndexes = b.rowIndices();
    const std::size_t* bColOffsets = b.colOffsets();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.rowIndices() == nullptr);
    ASSERT_TRUE(a.colOffsets() == nullptr);
    ASSERT_TRUE((compare(b.rows(), 5)));
    ASSERT_TRUE((compare(b.columns(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}

TEST(sparse_matrix_move_assignment_operator, given_f_self_should_do_nothing) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    // act
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-move"
    a = std::move(a);
#pragma GCC diagnostic pop
    const float* bValues = a.values();
    const std::size_t* bRowIndexes = a.rowIndices();
    const std::size_t* bColOffsets = a.colOffsets();
    // assert
    ASSERT_TRUE((compare(a.rows(), 5)));
    ASSERT_TRUE((compare(a.columns(), 5)));
    ASSERT_TRUE((compare(a.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2.0f)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3.0f)));
    ASSERT_TRUE((compare(bRowIndexes[0], 0.0f)));
    ASSERT_TRUE((compare(bRowIndexes[1], 2.0f)));
    ASSERT_TRUE((compare(bRowIndexes[2], 4)));
    ASSERT_TRUE((compare(bColOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(bColOffsets[1], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(bColOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(bColOffsets[5], 3.0f)));
}
#pragma endregion
#pragma endregion
#pragma region sparse_matrix_view
#pragma region constructor
TEST(sparse_matrix_view_constructor, given_f_sparse_matrix_should_construct) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(2, 2, 1);
    a.set(3, 2, 2);
    a.set(0, 0, 3);
    SparseMatrix<float> expected(3, 3);
    expected.set(1, 1, 1);
    expected.set(2, 1, 2);
    // act
    const SparseMatrixView<float> v(a, 3, 3, 1, 1);
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(v.columns(), 3)));
    ASSERT_TRUE((compare(v.rows(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), v, expected)));
}

TEST(sparse_matrix_view_constructor, given_cf_sparse_matrix_should_construct) {
    // arrange
    SparseMatrix<std::complex<float>> a(5, 5);
    a.set(2, 2, {1, 2});
    a.set(3, 2, {3, 4});
    a.set(0, 0, {5, 6});
    SparseMatrix<std::complex<float>> expected(3, 3);
    expected.set(1, 1, {1, 2});
    expected.set(2, 1, {3, 4});
    // act
    const SparseMatrixView<std::complex<float>> v(a, 3, 3, 1, 1);
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
    SparseMatrix<float> a(5, 5);
    a.set(2, 2, 1);
    a.set(3, 2, 2);
    a.set(0, 0, 3);
    const SparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act
    const SparseMatrixView<float> newView = v;
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
    SparseMatrix<std::complex<float>> a(5, 5);
    a.set(2, 2, {1, 2});
    a.set(3, 2, {3, 4});
    a.set(0, 0, {5, 6});
    const SparseMatrixView<std::complex<float>> v(a, 3, 3, 1, 1);
    // act
    const SparseMatrixView<std::complex<float>> newView = v;
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
    SparseMatrix<float> a(5, 5);
    SparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW(v.set(0, 0, 1), InvalidOperationException);
}

TEST(sparse_matrix_view_set, given_big_column_index_should_throw_1) {
    // arrange
    SparseMatrix<float> a(5, 5);
    SparseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW(v.set(3, 0, 1), InvalidIndexException);
}

TEST(sparse_matrix_view_set, given_big_row_index_should_throw_1) {
    // arrange
    SparseMatrix<float> a(5, 5);
    SparseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW(v.set(0, 3, 1), InvalidIndexException);
}

TEST(sparse_matrix_view_set, given_big_column_index_should_throw_2) {
    // arrange
    SparseMatrix<float> a(5, 5);
    SparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW(v.set(3, 0, 1), InvalidIndexException);
}

TEST(sparse_matrix_view_set, given_big_row_index_should_throw_2) {
    // arrange
    SparseMatrix<float> a(5, 5);
    SparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW(v.set(0, 3, 1), InvalidIndexException);
}
#pragma endregion
#pragma region get
TEST(sparse_matrix_view_get, given_index_should_return_value_f) {
    // arrange
    SparseMatrix<float> a(5, 5);
    a.set(2, 2, 1);
    const SparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act
    const float value = v.get(1, 1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 1)));
}

TEST(sparse_matrix_view_get, given_index_should_return_value_cf) {
    // arrange
    SparseMatrix<std::complex<float>> a(5, 5);
    a.set(2, 2, {1, 2});
    const SparseMatrixView<std::complex<float>> v(a, 3, 3, 1, 1);
    // act
    const std::complex<float> value = v.get(1, 1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(1, 2))));
}

TEST(sparse_matrix_view_get, given_big_column_index_should_throw_1) {
    // arrange
    SparseMatrix<float> a(5, 5);
    SparseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(3, 0), InvalidIndexException);
}

TEST(sparse_matrix_view_get, given_big_row_index_should_throw_1) {
    // arrange
    SparseMatrix<float> a(5, 5);
    SparseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(0, 3), InvalidIndexException);
}

TEST(sparse_matrix_view_get, given_big_column_index_should_throw_2) {
    // arrange
    SparseMatrix<float> a(5, 5);
    SparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(3, 0), InvalidIndexException);
}

TEST(sparse_matrix_view_get, given_big_row_index_should_throw_2) {
    // arrange
    SparseMatrix<float> a(5, 5);
    SparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(0, 3), InvalidIndexException);
}
#pragma endregion
#pragma region col_offset
TEST(sparse_matrix_view_col_offset, should_return_col_offset) {
    // arrange
    const SparseMatrix<float> a(5, 5);
    const SparseMatrixView<float> v(a, 3, 3, 1, 2);
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
    const SparseMatrix<float> a(5, 5);
    const SparseMatrixView<float> v(a, 3, 3, 1, 2);
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
    const SparseMatrix<float> a(5, 5);
    const SparseMatrixView<float> v(a, 3, 3, 1, 1);
    // act
    const SparseMatrix<float>& owner = v.owner();
    // assert
    ASSERT_TRUE(&owner == &a);
}
#pragma endregion
#pragma endregion
#pragma region custom_sparse_matrix
#pragma region constructor
TEST(custom_sparse_matrix_constructor, given_f_pointers_and_size_should_construct) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 1;
    colOffsets[4] = 1;
    colOffsets[5] = 1;
    std::size_t* rowIndices = new std::size_t[1];
    rowIndices[0] = 2;
    float* values = new float[1];
    values[0] = 3;
    std::size_t nnz = 1;
    // act
    const CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // assert
    ASSERT_TRUE((compare(m.rows(), 5)));
    ASSERT_TRUE((compare(m.columns(), 5)));
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE(colOffsets == m.colOffsets());
    ASSERT_TRUE(rowIndices == m.rowIndices());
    ASSERT_TRUE(values == m.values());
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_constructor, given_cf_pointers_and_size_should_construct) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 1;
    colOffsets[4] = 1;
    colOffsets[5] = 1;
    std::size_t* rowIndices = new std::size_t[1];
    rowIndices[0] = 2;
    std::complex<float>* values = new std::complex<float>[1];
    values[0] = {1, 2};
    std::size_t nnz = 1;
    // act
    const CustomSparseMatrix<std::complex<float>> m(5, 5, colOffsets, rowIndices, values, nnz);
    // assert
    ASSERT_TRUE((compare(m.rows(), 5)));
    ASSERT_TRUE((compare(m.columns(), 5)));
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE(colOffsets == m.colOffsets());
    ASSERT_TRUE(rowIndices == m.rowIndices());
    ASSERT_TRUE(values == m.values());
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}
#pragma endregion
#pragma region set
TEST(custom_sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 0;
    colOffsets[4] = 0;
    colOffsets[5] = 0;
    std::size_t* rowIndices = new std::size_t[0];
    float* values = new float[0];
    std::size_t nnz = 0;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    m.set(2, 2, 3);
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(m.rows(), 5)));
    ASSERT_TRUE((compare(m.columns(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 3.0f)));
    ASSERT_TRUE((compare(rowIndices[0], 2.0f)));
    ASSERT_TRUE((compare(colOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(colOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(colOffsets[5], 1.0f)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 1;
    colOffsets[4] = 1;
    colOffsets[5] = 1;
    std::size_t* rowIndices = new std::size_t[1];
    rowIndices[0] = 1;
    float* values = new float[1];
    values[0] = 4;
    std::size_t nnz = 1;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    m.set(2, 2, 3);
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(m.rows(), 5)));
    ASSERT_TRUE((compare(m.columns(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], 3.0f)));
    ASSERT_TRUE((compare(rowIndices[0], 1.0f)));
    ASSERT_TRUE((compare(rowIndices[1], 2.0f)));
    ASSERT_TRUE((compare(colOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(colOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(colOffsets[5], 2.0f)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_3) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 1;
    colOffsets[3] = 2;
    colOffsets[4] = 2;
    colOffsets[5] = 2;
    std::size_t* rowIndices = new std::size_t[2];
    rowIndices[0] = 2;
    rowIndices[1] = 1;
    float* values = new float[2];
    values[0] = 4;
    values[1] = 5;
    std::size_t nnz = 2;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    m.set(2, 2, 3);
    // assert
    ASSERT_TRUE((compare(m.nnz(), 3)));
    ASSERT_TRUE((compare(m.rows(), 5)));
    ASSERT_TRUE((compare(m.columns(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), values[2], 3.0f)));
    ASSERT_TRUE((compare(rowIndices[0], 2.0f)));
    ASSERT_TRUE((compare(rowIndices[1], 1.0f)));
    ASSERT_TRUE((compare(rowIndices[2], 2.0f)));
    ASSERT_TRUE((compare(colOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(colOffsets[3], 3.0f)));
    ASSERT_TRUE((compare(colOffsets[4], 3.0f)));
    ASSERT_TRUE((compare(colOffsets[5], 3.0f)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_4) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 1;
    colOffsets[3] = 2;
    colOffsets[4] = 2;
    colOffsets[5] = 2;
    std::size_t* rowIndices = new std::size_t[2];
    rowIndices[0] = 2;
    rowIndices[1] = 2;
    float* values = new float[2];
    values[0] = 4;
    values[1] = 3;
    std::size_t nnz = 2;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    m.set(2, 2, 5);
    // assert
    ASSERT_TRUE((compare(m.nnz(), 2)));
    ASSERT_TRUE((compare(m.rows(), 5)));
    ASSERT_TRUE((compare(m.columns(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], 5)));
    ASSERT_TRUE((compare(rowIndices[0], 2.0f)));
    ASSERT_TRUE((compare(rowIndices[1], 2.0f)));
    ASSERT_TRUE((compare(colOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[2], 1.0f)));
    ASSERT_TRUE((compare(colOffsets[3], 2.0f)));
    ASSERT_TRUE((compare(colOffsets[4], 2.0f)));
    ASSERT_TRUE((compare(colOffsets[5], 2.0f)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_not_add_f_1) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 0;
    colOffsets[4] = 0;
    colOffsets[5] = 0;
    std::size_t* rowIndices = new std::size_t[0];
    float* values = new float[0];
    std::size_t nnz = 0;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    m.set(2, 2, 0);
    // assert
    ASSERT_TRUE((compare(m.nnz(), 0)));
    ASSERT_TRUE((compare(m.rows(), 5)));
    ASSERT_TRUE((compare(m.columns(), 5)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_set, given_index_to_zero_element_and_zero_value_should_not_add_f_2) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 1;
    colOffsets[4] = 1;
    colOffsets[5] = 1;
    std::size_t* rowIndices = new std::size_t[1];
    rowIndices[0] = 1;
    float* values = new float[1];
    values[0] = 4;
    std::size_t nnz = 1;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    m.set(2, 2, 0);
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(m.rows(), 5)));
    ASSERT_TRUE((compare(m.columns(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 4)));
    ASSERT_TRUE((compare(rowIndices[0], 1.0f)));
    ASSERT_TRUE((compare(colOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(colOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(colOffsets[5], 1.0f)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_remove_f_1) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 1;
    colOffsets[4] = 1;
    colOffsets[5] = 1;
    std::size_t* rowIndices = new std::size_t[1];
    rowIndices[0] = 2;
    float* values = new float[1];
    values[0] = 3;
    std::size_t nnz = 1;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    m.set(2, 2, 0);
    // assert
    ASSERT_TRUE((compare(m.nnz(), 0)));
    ASSERT_TRUE((compare(m.rows(), 5)));
    ASSERT_TRUE((compare(m.columns(), 5)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_set, given_index_to_non_zero_element_and_zero_value_should_remove_f_2) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 2;
    colOffsets[4] = 2;
    colOffsets[5] = 2;
    std::size_t* rowIndices = new std::size_t[2];
    rowIndices[0] = 1;
    rowIndices[1] = 2;
    float* values = new float[2];
    values[0] = 4;
    values[1] = 3;
    std::size_t nnz = 2;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    m.set(2, 2, 0);
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(m.rows(), 5)));
    ASSERT_TRUE((compare(m.columns(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 4)));
    ASSERT_TRUE((compare(rowIndices[0], 1.0f)));
    ASSERT_TRUE((compare(colOffsets[0], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[1], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[2], 0.0f)));
    ASSERT_TRUE((compare(colOffsets[3], 1.0f)));
    ASSERT_TRUE((compare(colOffsets[4], 1.0f)));
    ASSERT_TRUE((compare(colOffsets[5], 1.0f)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 0;
    colOffsets[4] = 0;
    colOffsets[5] = 0;
    std::size_t* rowIndices = new std::size_t[0];
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t nnz = 0;
    CustomSparseMatrix<std::complex<float>> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    m.set(2, 2, {1, 2});
    // assert
    ASSERT_TRUE((compare(m.nnz(), 1)));
    ASSERT_TRUE((compare(m.rows(), 5)));
    ASSERT_TRUE((compare(m.columns(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(rowIndices[0], 2.0f)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_set, given_big_row_index_should_throw) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 0;
    colOffsets[4] = 0;
    colOffsets[5] = 0;
    std::size_t* rowIndices = new std::size_t[0];
    float* values = new float[0];
    std::size_t nnz = 0;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act / assert
    ASSERT_THROW(m.set(5, 2, 1), InvalidIndexException);
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_set, given_big_column_index_should_throw) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 0;
    colOffsets[4] = 0;
    colOffsets[5] = 0;
    std::size_t* rowIndices = new std::size_t[0];
    float* values = new float[0];
    std::size_t nnz = 0;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act / assert
    ASSERT_THROW(m.set(2, 5, 1), InvalidIndexException);
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}
#pragma endregion
#pragma region get
TEST(custom_sparse_matrix_get, given_index_should_return_value_f) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 1;
    colOffsets[4] = 1;
    colOffsets[5] = 1;
    std::size_t* rowIndices = new std::size_t[1];
    rowIndices[0] = 3;
    float* values = new float[1];
    values[0] = 1;
    std::size_t nnz = 1;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    const float value = m.get(2, 3);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 1)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_get, given_index_should_return_zero_f) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 1;
    colOffsets[4] = 1;
    colOffsets[5] = 1;
    std::size_t* rowIndices = new std::size_t[1];
    rowIndices[0] = 3;
    float* values = new float[1];
    values[0] = 1;
    std::size_t nnz = 1;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    const float value = m.get(1, 2);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 0)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_get, given_index_should_return_value_cf) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 1;
    colOffsets[4] = 1;
    colOffsets[5] = 1;
    std::size_t* rowIndices = new std::size_t[1];
    rowIndices[0] = 3;
    std::complex<float>* values = new std::complex<float>[1];
    values[0] = {1, 2};
    std::size_t nnz = 1;
    CustomSparseMatrix<std::complex<float>> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    const std::complex<float> value = m.get(2, 3);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(1, 2))));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_get, given_index_should_return_zero_cf) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 1;
    colOffsets[4] = 1;
    colOffsets[5] = 1;
    std::size_t* rowIndices = new std::size_t[1];
    rowIndices[0] = 3;
    std::complex<float>* values = new std::complex<float>[1];
    values[0] = {1, 2};
    std::size_t nnz = 1;
    CustomSparseMatrix<std::complex<float>> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    const std::complex<float> value = m.get(1, 2);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(0, 0))));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_get, given_big_row_index_should_throw) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 0;
    colOffsets[4] = 0;
    colOffsets[5] = 0;
    std::size_t* rowIndices = new std::size_t[0];
    float* values = new float[0];
    std::size_t nnz = 0;
    const CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act / assert
    ASSERT_THROW(std::ignore = m.get(5, 2), InvalidIndexException);
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_get, given_big_column_index_should_throw) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 0;
    colOffsets[4] = 0;
    colOffsets[5] = 0;
    std::size_t* rowIndices = new std::size_t[0];
    float* values = new float[0];
    std::size_t nnz = 0;
    const CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act / assert
    ASSERT_THROW(std::ignore = m.get(2, 5), InvalidIndexException);
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}
#pragma endregion
#pragma region nnz
TEST(custom_sparse_matrix_nnz, should_return_nnz) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 1;
    colOffsets[3] = 2;
    colOffsets[4] = 2;
    colOffsets[5] = 2;
    std::size_t* rowIndices = new std::size_t[2];
    rowIndices[0] = 1;
    rowIndices[1] = 3;
    float* values = new float[2];
    values[0] = 1;
    values[1] = 2;
    std::size_t nnz = 2;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    const std::size_t result = m.nnz();
    // assert
    ASSERT_TRUE((compare(result, 2)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}

TEST(custom_sparse_matrix_nnz, should_return_zero_when_empty) {
    // arrange
    std::size_t* colOffsets = new std::size_t[6];
    colOffsets[0] = 0;
    colOffsets[1] = 0;
    colOffsets[2] = 0;
    colOffsets[3] = 0;
    colOffsets[4] = 0;
    colOffsets[5] = 0;
    std::size_t* rowIndices = new std::size_t[0];
    float* values = new float[0];
    std::size_t nnz = 0;
    CustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
    // act
    const std::size_t result = m.nnz();
    // assert
    ASSERT_TRUE((compare(result, 0)));
    // cleanup
    delete[] colOffsets;
    delete[] rowIndices;
    delete[] values;
}
#pragma endregion
#pragma endregion
