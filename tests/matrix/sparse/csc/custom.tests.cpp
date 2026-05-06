#include "gtest/gtest.h"

#include "mathpp/matrix/sparse/common/operators.h"

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
    const CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    const CSCCustomSparseMatrix<std::complex<float>> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<std::complex<float>> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<std::complex<float>> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<std::complex<float>> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    const CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    const CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
    CSCCustomSparseMatrix<float> m(5, 5, colOffsets, rowIndices, values, nnz);
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
