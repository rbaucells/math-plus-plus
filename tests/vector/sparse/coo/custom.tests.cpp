#include "gtest/gtest.h"

#include "mathpp/vector/sparse/common/operators.h"

#pragma region constructor
TEST(custom_sparse_vector_constructor, given_f_pointer_and_i_pointer_and_size_should_construct) {
    // arrange
    float* values = new float[2];
    values[0] = 1;
    values[1] = 2;
    std::size_t* indices = new std::size_t[2];
    indices[0] = 2;
    indices[0] = 4;
    std::size_t nnz = 2;
    // act
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    // assert
    ASSERT_TRUE((compare(v.n(), 5)));
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE(v.values() == values);
    ASSERT_TRUE(v.indices() == indices);
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_constructor, given_cf_pointer_and_i_pointer_and_size_should_construct) {
    // arrange
    std::complex<float>* values = new std::complex<float>[2];
    values[0] = {1, 2};
    values[1] = {3, 4};
    std::size_t* indices = new std::size_t[2];
    indices[0] = 2;
    indices[0] = 4;
    std::size_t nnz = 2;
    // act
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    // assert
    ASSERT_TRUE((compare(v.n(), 5)));
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE(v.values() == values);
    ASSERT_TRUE(v.indices() == indices);
    // clean up
    delete[] values;
    delete[] indices;
}
#pragma endregion
#pragma region set
TEST(custom_sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    // act
    v.set(3, 1);
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 1)));
    ASSERT_TRUE((compare(indices[0], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(2, 1);
    // act
    v.set(3, 2);
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], 2)));
    ASSERT_TRUE((compare(indices[0], 2)));
    ASSERT_TRUE((compare(indices[1], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_3) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(2, 1);
    v.set(4, 2);
    // act
    v.set(3, 3);
    // assert
    ASSERT_TRUE((compare(nnz, 3)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), values[2], 2)));
    ASSERT_TRUE((compare(indices[0], 2)));
    ASSERT_TRUE((compare(indices[1], 3)));
    ASSERT_TRUE((compare(indices[2], 4)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_4) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(2, 1);
    // act
    v.set(1, 2);
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], 1)));
    ASSERT_TRUE((compare(indices[0], 1)));
    ASSERT_TRUE((compare(indices[1], 2)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_1) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    const float* oldVValues = values;
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, 0);
    // assert
    ASSERT_TRUE((compare(nnz, 0)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_2) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(0, 1);
    const float* oldVValues = values;
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, 0);
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 1)));
    ASSERT_TRUE((compare(indices[0], 0)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_3) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(0, 1);
    v.set(2, 2);
    const float* oldVValues = values;
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(1, 0);
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], 2)));
    ASSERT_TRUE((compare(indices[0], 0)));
    ASSERT_TRUE((compare(indices[1], 2)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_4) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(3, 1);
    const float* oldVValues = values;
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, 0);
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 1)));
    ASSERT_TRUE((compare(indices[0], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(2, 1);
    const float* oldVValues = values;
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, 3);
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 3)));
    ASSERT_TRUE((compare(indices[0], 2)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(1, 2);
    v.set(2, 1);
    const float* oldVValues = values;
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, 3);
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], 3)));
    ASSERT_TRUE((compare(indices[0], 1)));
    ASSERT_TRUE((compare(indices[1], 2)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_3) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(1, 2);
    v.set(2, 1);
    v.set(3, 4);
    const float* oldVValues = values;
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, 3);
    // assert
    ASSERT_TRUE((compare(nnz, 3)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), values[2], 4)));
    ASSERT_TRUE((compare(indices[0], 1)));
    ASSERT_TRUE((compare(indices[1], 2)));
    ASSERT_TRUE((compare(indices[2], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_4) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(2, 1);
    v.set(3, 2);
    const float* oldVValues = values;
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, 3);
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], 2)));
    ASSERT_TRUE((compare(indices[0], 2)));
    ASSERT_TRUE((compare(indices[1], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_1) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(2, 1);
    // act
    v.set(2, 0);
    // assert
    ASSERT_TRUE((compare(nnz, 0)));
    ASSERT_TRUE(values != nullptr);
    ASSERT_TRUE(indices != nullptr);
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_2) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(1, 2);
    v.set(2, 1);
    // act
    v.set(2, 0);
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 2)));
    ASSERT_TRUE((compare(indices[0], 1)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_3) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(1, 3);
    v.set(2, 1);
    v.set(3, 2);
    // act
    v.set(2, 0);
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], 2)));
    ASSERT_TRUE((compare(indices[0], 1)));
    ASSERT_TRUE((compare(indices[1], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_4) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(2, 1);
    v.set(3, 2);
    // act
    v.set(2, 0);
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], 2)));
    ASSERT_TRUE((compare(indices[0], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    // act
    v.set(3, {1, 2});
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(indices[0], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    // act
    v.set(3, {3, 4});
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(indices[0], 2)));
    ASSERT_TRUE((compare(indices[1], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_3) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    v.set(4, {3, 4});
    // act
    v.set(3, {5, 6});
    // assert
    ASSERT_TRUE((compare(nnz, 3)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), values[2], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(indices[0], 2)));
    ASSERT_TRUE((compare(indices[1], 3)));
    ASSERT_TRUE((compare(indices[2], 4)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_4) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    // act
    v.set(1, {3, 4});
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(indices[0], 1)));
    ASSERT_TRUE((compare(indices[1], 2)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_1) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, {0, 0});
    // assert
    ASSERT_TRUE((compare(nnz, 0)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_2) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(0, {1, 2});
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, {0, 0});
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(indices[0], 0)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_3) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(0, {1, 2});
    v.set(2, {3, 4});
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(1, {0, 0});
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(indices[0], 0)));
    ASSERT_TRUE((compare(indices[1], 2)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_4) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(3, {1, 2});
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, {0, 0});
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(indices[0], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, {3, 4});
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(indices[0], 2)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(1, {1, 2});
    v.set(2, {3, 4});
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, {5, 6});
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(indices[0], 1)));
    ASSERT_TRUE((compare(indices[1], 2)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_3) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(1, {1, 2});
    v.set(2, {3, 4});
    v.set(3, {5, 6});
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, {7, 8});
    // assert
    ASSERT_TRUE((compare(nnz, 3)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), values[2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(indices[0], 1)));
    ASSERT_TRUE((compare(indices[1], 2)));
    ASSERT_TRUE((compare(indices[2], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_4) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    v.set(3, {3, 4});
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = indices;
    // act
    v.set(2, {5, 6});
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE(values == oldVValues);
    ASSERT_TRUE(indices == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(indices[0], 2)));
    ASSERT_TRUE((compare(indices[1], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_1) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    // act
    v.set(2, {0, 0});
    // assert
    ASSERT_TRUE((compare(nnz, 0)));
    ASSERT_TRUE(values != nullptr);
    ASSERT_TRUE(indices != nullptr);
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_2) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(1, {1, 2});
    v.set(2, {3, 4});
    // act
    v.set(2, {0, 0});
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(indices[0], 1)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_3) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(1, {1, 2});
    v.set(2, {3, 4});
    v.set(3, {5, 6});
    // act
    v.set(2, {0, 0});
    // assert
    ASSERT_TRUE((compare(nnz, 2)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), values[1], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(indices[0], 1)));
    ASSERT_TRUE((compare(indices[1], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_4) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    v.set(3, {3, 4});
    // act
    v.set(2, {0, 0});
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
    ASSERT_TRUE((compare(Precision(0.001f), values[0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(indices[0], 3)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_big_index_should_throw) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    // act / assert
    ASSERT_THROW(v.set(5, 0), InvalidIndexException);
    // clean up
    delete[] values;
    delete[] indices;
}
#pragma endregion
#pragma region get
TEST(custom_sparse_vector_get, given_index_should_return_value_f) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(2, 1);
    // act
    const float value = v.get(2);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 1)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_get, given_index_should_return_zero_f) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    v.set(2, 1);
    // act
    const float value = v.get(1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 0)));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_get, given_index_should_return_value_cf) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    // act
    const std::complex<float> value = v.get(2);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(1, 2))));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_get, given_index_should_return_zero_cf) {
    // arrange
    std::complex<float>* values = new std::complex<float>[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    // act
    const std::complex<float> value = v.get(1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(0, 0))));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_get, given_big_index_should_throw) {
    // arrange
    float* values = new float[0];
    std::size_t* indices = new std::size_t[0];
    std::size_t nnz = 0;
    CooCustomSparseVector<float> v(5, values, indices, nnz);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(5), InvalidIndexException);
    // clean up
    delete[] values;
    delete[] indices;
}
#pragma endregion
