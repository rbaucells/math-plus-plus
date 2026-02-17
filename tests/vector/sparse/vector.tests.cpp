#include "gtest/gtest.h"

#include "mathpp/math.h"

#pragma region sparse_vector
#pragma region set
TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    SparseVector<float> v(5);
    // act
    v.set(3, 1);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE((compare<float, float>(vValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    // act
    v.set(3, 2);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE((compare<float, float>(vValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(vValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_3) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    v.set(4, 2);
    // act
    v.set(3, 3);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 3)));
    ASSERT_TRUE((compare<float, float>(vValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(vValues[1], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(vValues[2], 2, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 3)));
    ASSERT_TRUE((compare<int, int>(vIndexes[2], 4)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_4) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    // act
    v.set(1, 2);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE((compare<float, float>(vValues[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(vValues[1], 1, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_1) {
    // arrange
    SparseVector<float> v(5);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 0)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_2) {
    // arrange
    SparseVector<float> v(5);
    v.set(0,1);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<float, float>(vValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 0)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_3) {
    // arrange
    SparseVector<float> v(5);
    v.set(0,1);
    v.set(2,2);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(1, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<float, float>(vValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(vValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_4) {
    // arrange
    SparseVector<float> v(5);
    v.set(3,1);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<float, float>(vValues[0], 1, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<float, float>(vValues[0], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 2)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    SparseVector<float> v(5);
    v.set(1, 2);
    v.set(2, 1);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<float, float>(vValues[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(vValues[1], 3, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_3) {
    // arrange
    SparseVector<float> v(5);
    v.set(1, 2);
    v.set(2, 1);
    v.set(3, 4);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 3)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<float, float>(vValues[0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(vValues[1], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(vValues[2], 4, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(vIndexes[2], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_4) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    v.set(3, 2);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<float, float>(vValues[0], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(vValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_1) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 0)));
    ASSERT_TRUE(vValues != nullptr);
    ASSERT_TRUE(vIndexes != nullptr);
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_2) {
    // arrange
    SparseVector<float> v(5);
    v.set(1, 2);
    v.set(2, 1);
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE((compare<float, float>(vValues[0], 2, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 1)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_3) {
    // arrange
    SparseVector<float> v(5);
    v.set(1, 3);
    v.set(2, 1);
    v.set(3, 2);
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE((compare<float, float>(vValues[0], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(vValues[1], 2, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_4) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    v.set(3, 2);
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE((compare<float, float>(vValues[0], 2, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    // act
    v.set(3, {1, 2});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, {1, 2});
    // act
    v.set(3, {3, 4});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_3) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, {1, 2});
    v.set(4, {3, 4});
    // act
    v.set(3, {5, 6});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 3)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[1], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[2], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 3)));
    ASSERT_TRUE((compare<int, int>(vIndexes[2], 4)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_4) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, {1, 2});
    // act
    v.set(1, {3, 4});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[1], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_1) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, {0, 0});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 0)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_2) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(0, {1, 2});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, {0, 0});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 0)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_3) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(0, {1, 2});
    v.set(2, {3, 4});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(1, {0, 0});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 0)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_4) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(3, {1, 2});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, {0, 0});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, {1, 2});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, {3, 4});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 2)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(1, {1, 2});
    v.set(2, {3, 4});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, {5, 6});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[1], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_3) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(1, {1, 2});
    v.set(2, {3, 4});
    v.set(3, {5, 6});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, {7, 8});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 3)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[1], {7, 8}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[2], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 2)));
    ASSERT_TRUE((compare<int, int>(vIndexes[2], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_4) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, {1, 2});
    v.set(3, {3, 4});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indexes();
    // act
    v.set(2, {5, 6});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 2)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_1) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, {1, 2});
    // act
    v.set(2, {0, 0});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 0)));
    ASSERT_TRUE(vValues != nullptr);
    ASSERT_TRUE(vIndexes != nullptr);
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_2) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(1, {1, 2});
    v.set(2, {3, 4});
    // act
    v.set(2, {0, 0});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 1)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_3) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(1, {1, 2});
    v.set(2, {3, 4});
    v.set(3, {5, 6});
    // act
    v.set(2, {0, 0});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 2)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[1], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 1)));
    ASSERT_TRUE((compare<int, int>(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_4) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, {1, 2});
    v.set(3, {3, 4});
    // act
    v.set(2, {0, 0});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indexes();
    // assert
    ASSERT_TRUE((compare<int, int>(v.nnz(), 1)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_negative_index_should_throw) {
    // arrange
    SparseVector<float> v(5);
    // act / assert
    ASSERT_THROW(v.set(-1, 0), InvalidIndexException);
}

TEST(sparse_vector_set, given_big_index_should_throw) {
    // arrange
    SparseVector<float> v(5);
    // act / assert
    ASSERT_THROW(v.set(5, 0), InvalidIndexException);
}
#pragma endregion
#pragma region get
TEST(sparse_vector_get, given_index_should_return_value_f) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    // act
    const float value = v.get(2);
    // assert
    ASSERT_TRUE((compare<float, float>(value, 1, 0.001f)));
}

TEST(sparse_vector_get, given_index_should_return_zero_f) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    // act
    const float value = v.get(1);
    // assert
    ASSERT_TRUE((compare<float, float>(value, 0, 0.001f)));
}

TEST(sparse_vector_get, given_index_should_return_value_cf) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, {1, 2});
    // act
    const std::complex<float> value = v.get(2);
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(value, {1, 2}, 0.001f)));
}

TEST(sparse_vector_get, given_index_should_return_zero_cf) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, {1, 2});
    // act
    const std::complex<float> value = v.get(1);
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(value, {0, 0}, 0.001f)));
}

TEST(sparse_vector_get, given_negative_index_should_throw) {
    // arrange
    const SparseVector<float> v(5);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(-1),InvalidIndexException);
}

TEST(sparse_vector_get, given_big_index_should_throw) {
    // arrange
    const SparseVector<float> v(5);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(5),InvalidIndexException);
}
#pragma endregion
#pragma region default_constructor
TEST(sparse_vector_default_constructor, given_size_should_construct_f) {
    // act
    SparseVector<float> a(5);
    // assert
    ASSERT_TRUE((compare<int, int>(a.n, 5)));
    ASSERT_TRUE((compare<int, int>(a.nnz(), 0)));
    ASSERT_TRUE(a.values() != nullptr);
    ASSERT_TRUE(a.indexes() != nullptr);
}

TEST(sparse_vector_default_constructor, given_size_should_construct_cf) {
    // act
    SparseVector<std::complex<float>> a(5);
    // assert
    ASSERT_TRUE((compare<int, int>(a.n, 5)));
    ASSERT_TRUE((compare<int, int>(a.nnz(), 0)));
    ASSERT_TRUE(a.values() != nullptr);
    ASSERT_TRUE(a.indexes() != nullptr);
}

TEST(sparse_vector_default_constructor, given_negative_size_should_throw) {
    // act / assert
    ASSERT_THROW(std::ignore = SparseVector<std::complex<float>>(-1), InvalidIndexException);
}
#pragma endregion
#pragma endregion