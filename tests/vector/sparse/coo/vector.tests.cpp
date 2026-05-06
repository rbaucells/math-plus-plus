#include "gtest/gtest.h"

#include "mathpp/vector/sparse/common/operators.h"

#pragma region set
TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    CooSparseVector<float> v(5);
    // act
    v.set(3, 1);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 1)));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(2, 1);
    // act
    v.set(3, 2);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], 2)));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_3) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(2, 1);
    v.set(4, 2);
    // act
    v.set(3, 3);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[2], 2)));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
    ASSERT_TRUE((compare(vIndexes[2], 4)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_4) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(2, 1);
    // act
    v.set(1, 2);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], 1)));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_1) {
    // arrange
    CooSparseVector<float> v(5);
    const float* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 0)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_2) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(0, 1);
    const float* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 1)));
    ASSERT_TRUE((compare(vIndexes[0], 0)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_3) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(0, 1);
    v.set(2, 2);
    const float* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(1, 0);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], 2)));
    ASSERT_TRUE((compare(vIndexes[0], 0)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_4) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(3, 1);
    const float* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 1)));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(2, 1);
    const float* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 3)));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(1, 2);
    v.set(2, 1);
    const float* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], 3)));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_3) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(1, 2);
    v.set(2, 1);
    v.set(3, 4);
    const float* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 3)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[2], 4)));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
    ASSERT_TRUE((compare(vIndexes[2], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_4) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(2, 1);
    v.set(3, 2);
    const float* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], 2)));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_1) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(2, 1);
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 0)));
    ASSERT_TRUE(vValues != nullptr);
    ASSERT_TRUE(vIndexes != nullptr);
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_2) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(1, 2);
    v.set(2, 1);
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 2)));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_3) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(1, 3);
    v.set(2, 1);
    v.set(3, 2);
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], 2)));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_4) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(2, 1);
    v.set(3, 2);
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 2)));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    // act
    v.set(3, std::complex<float>(1, 2));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    // act
    v.set(3, std::complex<float>(3, 4));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_3) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    v.set(4, std::complex<float>(3, 4));
    // act
    v.set(3, std::complex<float>(5, 6));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[2], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
    ASSERT_TRUE((compare(vIndexes[2], 4)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_4) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    // act
    v.set(1, std::complex<float>(3, 4));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_1) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 0)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_2) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(0, std::complex<float>(1, 2));
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(vIndexes[0], 0)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_3) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(0, std::complex<float>(1, 2));
    v.set(2, std::complex<float>(3, 4));
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(1, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(vIndexes[0], 0)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_4) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(3, std::complex<float>(1, 2));
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(3, 4));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(1, std::complex<float>(1, 2));
    v.set(2, std::complex<float>(3, 4));
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(5, 6));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_3) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(1, std::complex<float>(1, 2));
    v.set(2, std::complex<float>(3, 4));
    v.set(3, std::complex<float>(5, 6));
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(7, 8));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 3)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
    ASSERT_TRUE((compare(vIndexes[2], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_4) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    v.set(3, std::complex<float>(3, 4));
    const std::complex<float>* oldVValues = v.values();
    const std::size_t* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(5, 6));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_1) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 0)));
    ASSERT_TRUE(vValues != nullptr);
    ASSERT_TRUE(vIndexes != nullptr);
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_2) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(1, std::complex<float>(1, 2));
    v.set(2, {3, 4});
    // act
    v.set(2, {0, 0});
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_3) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(1, std::complex<float>(1, 2));
    v.set(2, std::complex<float>(3, 4));
    v.set(3, {5, 6});
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_4) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    v.set(3, std::complex<float>(3, 4));
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_big_index_should_throw) {
    // arrange
    CooSparseVector<float> v(5);
    // act / assert
    ASSERT_THROW(v.set(5, 0), InvalidIndexException);
}
#pragma endregion
#pragma region get
TEST(sparse_vector_get, given_index_should_return_value_f) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(2, 1);
    // act
    const float value = v.get(2);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 1)));
}

TEST(sparse_vector_get, given_index_should_return_zero_f) {
    // arrange
    CooSparseVector<float> v(5);
    v.set(2, 1);
    // act
    const float value = v.get(1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 0)));
}

TEST(sparse_vector_get, given_index_should_return_value_cf) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    // act
    const std::complex<float> value = v.get(2);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(1, 2))));
}

TEST(sparse_vector_get, given_index_should_return_zero_cf) {
    // arrange
    CooSparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    // act
    const std::complex<float> value = v.get(1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(0, 0))));
}

TEST(sparse_vector_get, given_big_index_should_throw) {
    // arrange
    const CooSparseVector<float> v(5);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(5), InvalidIndexException);
}
#pragma endregion
#pragma region default_constructor
TEST(sparse_vector_default_constructor, given_size_should_construct_f) {
    // act
    CooSparseVector<float> a(5);
    // assert
    ASSERT_TRUE((compare(a.n(), 5)));
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE(a.values() != nullptr);
    ASSERT_TRUE(a.indices() != nullptr);
}

TEST(sparse_vector_default_constructor, given_size_should_construct_cf) {
    // act
    CooSparseVector<std::complex<float>> a(5);
    // assert
    ASSERT_TRUE((compare(a.n(), 5)));
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE(a.values() != nullptr);
    ASSERT_TRUE(a.indices() != nullptr);
}
#pragma endregion
#pragma region initializer_list_constructor
TEST(sparse_vector_initializer_list_constructor, given_n_and_value_index_pairs_should_construct_f) {
    // arrange / act
    const CooSparseVector<float> v(5, {{1, 0}, {3, 2}, {5, 4}});
    const float* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.n(), 5)));
    ASSERT_TRUE((compare(v.nnz(), 3)));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[0], 1));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[1], 3));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[2], 5));
    ASSERT_TRUE((compare(vIndexes[0], 0)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
    ASSERT_TRUE((compare(vIndexes[2], 4)));
}

TEST(sparse_vector_initializer_list_constructor, given_n_and_value_index_pairs_should_construct_cf) {
    // arrange / act
    const CooSparseVector<std::complex<float>> v(5, {{{1, 2}, 0}, {{5, 6}, 2}, {{9, 10}, 4}});
    const std::complex<float>* vValues = v.values();
    const std::size_t* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.n(), 5)));
    ASSERT_TRUE((compare(v.nnz(), 3)));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2)));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[1], std::complex<float>(5, 6)));
    ASSERT_TRUE(compare(Precision(0.001f), vValues[2], std::complex<float>(9, 10)));
    ASSERT_TRUE((compare(vIndexes[0], 0)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
    ASSERT_TRUE((compare(vIndexes[2], 4)));
}
#pragma endregion
#pragma region copy_constructor_from_same_type_sparse_vector
TEST(sparse_vector_copy_constructor_from_same_type_sparse_vector, given_f_sparse_vector_should_copy_construct) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
    const CooSparseVector<float> b = a;
    const float* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3)));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_copy_constructor_from_same_type_sparse_vector, given_cf_sparse_vector_should_copy_construct) {
    // arrange
    CooSparseVector<std::complex<float>> a(5);
    a.set(0, std::complex<float>(1, 2));
    a.set(2, std::complex<float>(3, 4));
    a.set(4, std::complex<float>(5, 6));
    // act
    const CooSparseVector<std::complex<float>> b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_sparse_vector
TEST(sparse_vector_copy_constructor_from_different_type_sparse_vector, given_f_sparse_vector_should_copy_construct) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
    const CooSparseVector<std::complex<float>> b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(2, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(3, 0))));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}
#pragma endregion
#pragma region move_constructor
TEST(sparse_vector_move_constructor, given_f_sparse_vector_should_move_construct_and_leave_other_empty) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
    const CooSparseVector<float> b = std::move(a);
    const float* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.indices() == nullptr);
    ASSERT_TRUE((compare(a.n(), 0)));
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3)));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_move_constructor, given_cf_sparse_vector_should_move_construct_and_leave_other_empty) {
    // arrange
    CooSparseVector<std::complex<float>> a(5);
    a.set(0, {1, 2});
    a.set(2, {3, 4});
    a.set(4, {5, 6});
    // act
    const CooSparseVector<std::complex<float>> b = std::move(a);
    const std::complex<float>* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.indices() == nullptr);
    ASSERT_TRUE((compare(a.n(), 0)));
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_sparse_vector
TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector, given_f_sparse_vector_of_same_size_diff_nnz_should_copy_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<float> b(5);
    // act
    b = a;
    const float* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3)));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector, given_f_sparse_vector_of_same_size_same_nnz_should_copy_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<float> b(5);
    b.set(1, 3);
    b.set(2, 2);
    b.set(3, 1);
    // act
    b = a;
    const float* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3)));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector, given_cf_sparse_vector_of_same_size_diff_nnz_should_copy_assign) {
    // arrange
    CooSparseVector<std::complex<float>> a(5);
    a.set(0, {1, 2});
    a.set(2, {3, 4});
    a.set(4, {5, 6});
    CooSparseVector<std::complex<float>> b(5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector, given_f_sparse_vector_of_diff_size_diff_nnz_should_copy_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<float> b(3);
    // act
    b = a;
    const float* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3)));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector, given_f_sparse_vector_of_diff_size_same_nnz_should_copy_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<float> b(3);
    b.set(0, 1);
    b.set(1, 3);
    b.set(2, 2);
    // act
    b = a;
    const float* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3)));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector, given_f_self_should_do_nothing) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-assign-overloaded"
    // ReSharper disable once CppIdenticalOperandsInBinaryExpression
    a = a;
#pragma GCC diagnostic pop
    const float* aValues = a.values();
    const std::size_t* aIndexes = a.indices();
    // assert
    ASSERT_TRUE((compare(a.nnz(), 3)));
    ASSERT_TRUE((compare(a.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), aValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), aValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), aValues[2], 3)));
    ASSERT_TRUE((compare(aIndexes[0], 0)));
    ASSERT_TRUE((compare(aIndexes[1], 2)));
    ASSERT_TRUE((compare(aIndexes[2], 4)));
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_sparse_vector
TEST(sparse_vector_copy_assignment_operator_from_different_type_sparse_vector, given_f_sparse_vector_of_same_size_diff_nnz_should_copy_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<std::complex<float>> b(5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(2, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(3, 0))));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_copy_assignment_operator_from_different_type_sparse_vector, given_f_sparse_vector_of_same_size_same_nnz_should_copy_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<std::complex<float>> b(5);
    b.set(1, 2);
    b.set(2, 3);
    b.set(3, 4);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(2, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(3, 0))));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_copy_assignment_operator_from_different_type_sparse_vector, given_f_sparse_vector_of_diff_size_diff_nnz_should_copy_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<std::complex<float>> b(3);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(2, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(3, 0))));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_copy_assignment_operator_from_different_type_sparse_vector, given_f_sparse_vector_of_diff_size_same_nnz_should_copy_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<std::complex<float>> b(3);
    b.set(0, 1);
    b.set(1, 3);
    b.set(2, 2);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(2, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(3, 0))));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}
#pragma endregion
#pragma region move_assignment_operator
TEST(sparse_vector_move_assignment_operator, given_f_sparse_vector_of_same_size_diff_nnz_should_move_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<float> b(5);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.indices() == nullptr);
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE((compare(a.n(), 0)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3)));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_move_assignment_operator, given_f_sparse_vector_of_same_size_same_nnz_should_move_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<float> b(5);
    b.set(1, 11);
    b.set(2, 22);
    b.set(4, 33);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.indices() == nullptr);
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE((compare(a.n(), 0)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3)));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_move_assignment_operator, given_cf_sparse_vector_of_same_size_diff_nnz_should_move_assign) {
    // arrange
    CooSparseVector<std::complex<float>> a(5);
    a.set(0, {1, 2});
    a.set(2, {3, 4});
    a.set(4, {5, 6});
    CooSparseVector<std::complex<float>> b(5);
    // act
    b = std::move(a);
    const std::complex<float>* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.indices() == nullptr);
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE((compare(a.n(), 0)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_move_assignment_operator, given_f_sparse_vector_of_diff_size_diff_nnz_should_move_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<float> b(3);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.indices() == nullptr);
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE((compare(a.n(), 0)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3)));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_move_assignment_operator, given_f_sparse_vector_of_diff_size_same_nnz_should_move_assign) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    CooSparseVector<float> b(3);
    b.set(0, -0.2f);
    b.set(1, 20);
    b.set(2, 4);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const std::size_t* bIndexes = b.indices();
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.indices() == nullptr);
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE((compare(a.n(), 0)));
    ASSERT_TRUE((compare(b.nnz(), 3)));
    ASSERT_TRUE((compare(b.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bValues[2], 3)));
    ASSERT_TRUE((compare(bIndexes[0], 0)));
    ASSERT_TRUE((compare(bIndexes[1], 2)));
    ASSERT_TRUE((compare(bIndexes[2], 4)));
}

TEST(sparse_vector_move_assignment_operator, given_f_self_should_do_nothing) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-move"
    a = std::move(a);
#pragma GCC diagnostic pop
    const float* aValues = a.values();
    const std::size_t* aIndexes = a.indices();
    // assert
    ASSERT_TRUE((compare(a.nnz(), 3)));
    ASSERT_TRUE((compare(a.n(), 5)));
    ASSERT_TRUE((compare(Precision(0.001f), aValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), aValues[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), aValues[2], 3)));
    ASSERT_TRUE((compare(aIndexes[0], 0)));
    ASSERT_TRUE((compare(aIndexes[1], 2)));
    ASSERT_TRUE((compare(aIndexes[2], 4)));
}
#pragma endregion
