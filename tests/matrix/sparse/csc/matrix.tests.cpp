#include "gtest/gtest.h"

#include "mathpp/matrix/sparse/common/operators.h"

#pragma region set
TEST(sparse_matrix_set, given_index_to_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<std::complex<float>> m(5, 5);
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
    CSCSparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(m.set(5, 2, 1), InvalidIndexException);
}

TEST(sparse_matrix_set, given_big_column_index_should_throw) {
    // arrange
    CSCSparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(m.set(2, 5, 1), InvalidIndexException);
}
#pragma endregion
#pragma region get
TEST(sparse_matrix_get, given_index_should_return_value_f) {
    // arrange
    CSCSparseMatrix<float> m(5, 5);
    m.set(2, 3, 1);
    // act
    const float value = m.get(2, 3);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 1)));
}

TEST(sparse_matrix_get, given_index_should_return_zero_f) {
    // arrange
    CSCSparseMatrix<float> m(5, 5);
    m.set(2, 3, 1);
    // act
    const float value = m.get(1, 2);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 0)));
}

TEST(sparse_matrix_get, given_index_should_return_value_cf) {
    // arrange
    CSCSparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 3, {1, 2});
    // act
    const std::complex<float> value = m.get(2, 3);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(1, 2))));
}

TEST(sparse_matrix_get, given_index_should_return_zero_cf) {
    // arrange
    CSCSparseMatrix<std::complex<float>> m(5, 5);
    m.set(2, 3, {1, 2});
    // act
    const std::complex<float> value = m.get(1, 2);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(0, 0))));
}

TEST(sparse_matrix_get, given_big_row_index_should_throw) {
    // arrange
    const CSCSparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(std::ignore = m.get(5, 2), InvalidIndexException);
}

TEST(sparse_matrix_get, given_big_column_index_should_throw) {
    // arrange
    const CSCSparseMatrix<float> m(5, 5);
    // act / assert
    ASSERT_THROW(std::ignore = m.get(2, 5), InvalidIndexException);
}
#pragma endregion
#pragma region default_constructor
TEST(sparse_matrix_default_constructor, given_rows_and_cols_should_construct_f) {
    // act
    CSCSparseMatrix<float> a(5, 5);
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
    CSCSparseMatrix<std::complex<float>> a(5, 5);
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
    CSCSparseMatrix<float> v(3, 3, {{1, 0, 0}, {5, 1, 1}, {6, 2, 1}, {9, 2, 2}});
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
    CSCSparseMatrix<std::complex<float>> v(3, 3, {{{1, 2}, 0, 0}, {{5, 6}, 1, 1}, {{6, 7}, 2, 1}, {{9, 10}, 2, 2}});
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    // act
    const CSCSparseMatrix<float> b = a;
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
    CSCSparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    // act
    const CSCSparseMatrix<std::complex<float>> b = a;
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    // act
    const CSCSparseMatrix<std::complex<float>> b = a;
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
#pragma region move_constructor
TEST(sparse_matrix_move_constructor, given_f_sparse_matrix_should_move_construct_and_invalidate_other_data) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    // act
    const CSCSparseMatrix<float> b = std::move(a);
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
    CSCSparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    // act
    const CSCSparseMatrix<std::complex<float>> b = std::move(a);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(5, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(5, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(4, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(5, 4);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(4, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(5, 4);
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
    CSCSparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    CSCSparseMatrix<std::complex<float>> b(5, 5);
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
    CSCSparseMatrix<float> a(5, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<std::complex<float>> b(5, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<std::complex<float>> b(5, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<std::complex<float>> b(4, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<std::complex<float>> b(5, 4);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<std::complex<float>> b(4, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<std::complex<float>> b(5, 4);
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
#pragma region move_assignment_operator
TEST(sparse_matrix_move_assignment_operator, given_f_sparse_matrix_of_same_size_diff_nnz_should_move_assign) {
    // arrange
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(5, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(5, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(4, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(5, 4);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(4, 5);
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
    CSCSparseMatrix<float> a(5, 5);
    a.set(0, 0, 1);
    a.set(2, 2, 2);
    a.set(4, 4, 3);
    CSCSparseMatrix<float> b(5, 4);
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
    CSCSparseMatrix<std::complex<float>> a(5, 5);
    a.set(0, 0, {1, 2});
    a.set(2, 2, {3, 4});
    a.set(4, 4, {5, 6});
    CSCSparseMatrix<std::complex<float>> b(5, 5);
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
    CSCSparseMatrix<float> a(5, 5);
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
