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
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 1)));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    // act
    v.set(3, 2);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], 2)));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_f_3) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    v.set(4, 2);
    // act
    v.set(3, 3);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
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
    SparseVector<float> v(5);
    v.set(2, 1);
    // act
    v.set(1, 2);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], 1)));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_1) {
    // arrange
    SparseVector<float> v(5);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 0)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_2) {
    // arrange
    SparseVector<float> v(5);
    v.set(0, 1);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 1)));
    ASSERT_TRUE((compare(vIndexes[0], 0)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_f_3) {
    // arrange
    SparseVector<float> v(5);
    v.set(0, 1);
    v.set(2, 2);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(1, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
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
    SparseVector<float> v(5);
    v.set(3, 1);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 1)));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_1) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 3)));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_f_2) {
    // arrange
    SparseVector<float> v(5);
    v.set(1, 2);
    v.set(2, 1);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
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
    SparseVector<float> v(5);
    v.set(1, 2);
    v.set(2, 1);
    v.set(3, 4);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
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
    SparseVector<float> v(5);
    v.set(2, 1);
    v.set(3, 2);
    const float* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, 3);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
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
    SparseVector<float> v(5);
    v.set(2, 1);
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 0)));
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
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 2)));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
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
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], 2)));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_f_4) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    v.set(3, 2);
    // act
    v.set(2, 0);
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], 2)));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    // act
    v.set(3, std::complex<float>(1, 2));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    // act
    v.set(3, std::complex<float>(3, 4));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_non_zero_value_should_set_cf_3) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    v.set(4, std::complex<float>(3, 4));
    // act
    v.set(3, std::complex<float>(5, 6));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
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
    SparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    // act
    v.set(1, std::complex<float>(3, 4));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 2)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_1) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 0)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_2) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(0, std::complex<float>(1, 2));
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(vIndexes[0], 0)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_set_cf_3) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(0, std::complex<float>(1, 2));
    v.set(2, std::complex<float>(3, 4));
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(1, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
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
    SparseVector<std::complex<float>> v(5);
    v.set(3, std::complex<float>(1, 2));
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_1) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(3, 4));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE(vValues == oldVValues);
    ASSERT_TRUE(vIndexes == oldVIndexes);
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(vIndexes[0], 2)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_non_zero_value_should_set_cf_2) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(1, std::complex<float>(1, 2));
    v.set(2, std::complex<float>(3, 4));
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(5, 6));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
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
    SparseVector<std::complex<float>> v(5);
    v.set(1, std::complex<float>(1, 2));
    v.set(2, std::complex<float>(3, 4));
    v.set(3, std::complex<float>(5, 6));
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(7, 8));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
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
    SparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    v.set(3, std::complex<float>(3, 4));
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = v.indices();
    // act
    v.set(2, std::complex<float>(5, 6));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
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
    SparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 0)));
    ASSERT_TRUE(vValues != nullptr);
    ASSERT_TRUE(vIndexes != nullptr);
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_2) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(1, std::complex<float>(1, 2));
    v.set(2, {3, 4});
    // act
    v.set(2, {0, 0});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_3) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(1, std::complex<float>(1, 2));
    v.set(2, std::complex<float>(3, 4));
    v.set(3, {5, 6});
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[1], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(vIndexes[0], 1)));
    ASSERT_TRUE((compare(vIndexes[1], 3)));
}

TEST(sparse_vector_set, given_index_to_non_zero_element_and_zero_value_should_set_cf_4) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    v.set(3, std::complex<float>(3, 4));
    // act
    v.set(2, std::complex<float>(0, 0));
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
    // assert
    ASSERT_TRUE((compare(v.nnz(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vValues[0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(vIndexes[0], 3)));
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
    ASSERT_TRUE((compare(Precision(0.001f), value, 1)));
}

TEST(sparse_vector_get, given_index_should_return_zero_f) {
    // arrange
    SparseVector<float> v(5);
    v.set(2, 1);
    // act
    const float value = v.get(1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 0)));
}

TEST(sparse_vector_get, given_index_should_return_value_cf) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    // act
    const std::complex<float> value = v.get(2);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(1, 2))));
}

TEST(sparse_vector_get, given_index_should_return_zero_cf) {
    // arrange
    SparseVector<std::complex<float>> v(5);
    v.set(2, std::complex<float>(1, 2));
    // act
    const std::complex<float> value = v.get(1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(0, 0))));
}

TEST(sparse_vector_get, given_negative_index_should_throw) {
    // arrange
    const SparseVector<float> v(5);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(-1), InvalidIndexException);
}

TEST(sparse_vector_get, given_big_index_should_throw) {
    // arrange
    const SparseVector<float> v(5);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(5), InvalidIndexException);
}
#pragma endregion
#pragma region default_constructor
TEST(sparse_vector_default_constructor, given_size_should_construct_f) {
    // act
    SparseVector<float> a(5);
    // assert
    ASSERT_TRUE((compare(a.n(), 5)));
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE(a.values() != nullptr);
    ASSERT_TRUE(a.indices() != nullptr);
}

TEST(sparse_vector_default_constructor, given_size_should_construct_cf) {
    // act
    SparseVector<std::complex<float>> a(5);
    // assert
    ASSERT_TRUE((compare(a.n(), 5)));
    ASSERT_TRUE((compare(a.nnz(), 0)));
    ASSERT_TRUE(a.values() != nullptr);
    ASSERT_TRUE(a.indices() != nullptr);
}

TEST(sparse_vector_default_constructor, given_negative_size_should_throw) {
    // act / assert
    ASSERT_THROW(std::ignore = SparseVector<std::complex<float>>(-1), InvalidIndexException);
}
#pragma endregion
#pragma region initializer_list_constructor
TEST(sparse_vector_initializer_list_constructor, given_n_and_value_index_pairs_should_construct_f) {
    // arrange / act
    const SparseVector<float> v(5, {{1, 0}, {3, 2}, {5, 4}});
    const float* vValues = v.values();
    const int* vIndexes = v.indices();
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
    const SparseVector<std::complex<float>> v(5, {{{1, 2}, 0}, {{5, 6}, 2}, {{9, 10}, 4}});
    const std::complex<float>* vValues = v.values();
    const int* vIndexes = v.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
    const SparseVector<float> b = a;
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<std::complex<float>> a(5);
    a.set(0, std::complex<float>(1, 2));
    a.set(2, std::complex<float>(3, 4));
    a.set(4, std::complex<float>(5, 6));
    // act
    const SparseVector<std::complex<float>> b = a;
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
    const SparseVector<std::complex<float>> b = a;
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
#pragma region copy_constructor_from_same_type_sparse_vector_base
TEST(sparse_vector_copy_constructor_from_same_type_sparse_vector_base, given_f_sparse_vector_base_should_copy_construct) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
    const SparseVector<float> b = static_cast<const SparseVectorBase<float>&>(a);
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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

TEST(sparse_vector_copy_constructor_from_same_type_sparse_vector_base, given_cf_sparse_vector_base_should_copy_construct) {
    // arrange
    SparseVector<std::complex<float>> a(5);
    a.set(0, {1, 2});
    a.set(2, std::complex<float>(3, 4));
    a.set(4, std::complex<float>(5, 6));
    // act
    const SparseVector<std::complex<float>> b = static_cast<const SparseVectorBase<std::complex<float>>&>(a);
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
#pragma region copy_constructor_from_different_type_sparse_vector_base
TEST(sparse_vector_copy_constructor_from_different_type_sparse_vector_base, given_f_sparse_vector_base_should_copy_construct) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
    const SparseVector<std::complex<float>> b = static_cast<const SparseVectorBase<float>&>(a);
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
    const SparseVector<float> b = std::move(a);
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<std::complex<float>> a(5);
    a.set(0, {1, 2});
    a.set(2, {3, 4});
    a.set(4, {5, 6});
    // act
    const SparseVector<std::complex<float>> b = std::move(a);
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(5);
    // act
    b = a;
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(5);
    b.set(1, 3);
    b.set(2, 2);
    b.set(3, 1);
    // act
    b = a;
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<std::complex<float>> a(5);
    a.set(0, {1, 2});
    a.set(2, {3, 4});
    a.set(4, {5, 6});
    SparseVector<std::complex<float>> b(5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(3);
    // act
    b = a;
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(3);
    b.set(0, 1);
    b.set(1, 3);
    b.set(2, 2);
    // act
    b = a;
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
    a = a;
    const float* aValues = a.values();
    const int* aIndexes = a.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<std::complex<float>> b(5);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<std::complex<float>> b(5);
    b.set(1, 2);
    b.set(2, 3);
    b.set(3, 4);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<std::complex<float>> b(3);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<std::complex<float>> b(3);
    b.set(0, 1);
    b.set(1, 3);
    b.set(2, 2);
    // act
    b = a;
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
#pragma region copy_assignment_operator_from_same_type_sparse_vector_base
TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector_base, given_f_sparse_vector_base_of_same_size_diff_nnz_should_copy_assign) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(5);
    // act
    b = static_cast<const SparseVectorBase<float>&>(a);
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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

TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector_base, given_f_sparse_vector_base_of_same_size_same_nnz_should_copy_assign) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(5);
    b.set(1, -1);
    b.set(2, 3);
    b.set(4, 4);
    // act
    b = static_cast<const SparseVectorBase<float>&>(a);
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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

TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector_base, given_cf_sparse_vector_base_of_same_size_diff_nnz_should_copy_assign) {
    // arrange
    SparseVector<std::complex<float>> a(5);
    a.set(0, std::complex<float>(1, 2));
    a.set(2, std::complex<float>(3, 4));
    a.set(4, std::complex<float>(5, 6));
    SparseVector<std::complex<float>> b(5);
    // act
    b = static_cast<const SparseVectorBase<std::complex<float>>&>(a);
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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

TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector_base, given_f_sparse_vector_base_of_diff_size_diff_nnz_should_copy_assign) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(3);
    // act
    b = static_cast<const SparseVectorBase<float>&>(a);
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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

TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector_base, given_f_sparse_vector_base_of_diff_size_same_nnz_should_copy_assign) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(3);
    b.set(0, 2);
    b.set(1, 1);
    b.set(2, 4);
    // act
    b = static_cast<const SparseVectorBase<float>&>(a);
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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

TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector_base, given_f_self_should_do_nothing) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
    a = static_cast<const SparseVectorBase<float>&>(a);
    const float* aValues = a.values();
    const int* aIndexes = a.indices();
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
#pragma region copy_assignment_operator_from_different_type_sparse_vector_base
TEST(sparse_vector_copy_assignment_operator_from_different_type_sparse_vector_base, given_f_sparse_vector_base_of_same_size_diff_nnz_should_copy_assign) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<std::complex<float>> b(5);
    // act
    b = static_cast<const SparseVectorBase<float>&>(a);
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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

TEST(sparse_vector_copy_assignment_operator_from_different_type_sparse_vector_base, given_f_sparse_vector_base_of_same_size_same_nnz_should_copy_assign) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<std::complex<float>> b(5);
    b.set(1, 3);
    b.set(2, 4);
    b.set(4, 35);
    // act
    b = static_cast<const SparseVectorBase<float>&>(a);
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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

TEST(sparse_vector_copy_assignment_operator_from_different_type_sparse_vector_base, given_f_sparse_vector_base_of_diff_size_diff_nnz_should_copy_assign) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<std::complex<float>> b(3);
    // act
    b = static_cast<const SparseVectorBase<float>&>(a);
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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

TEST(sparse_vector_copy_assignment_operator_from_different_type_sparse_vector_base, given_f_sparse_vector_base_of_diff_size_same_nnz_should_copy_assign) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<std::complex<float>> b(3);
    b.set(0, 14);
    b.set(1, 32);
    b.set(2, 33);
    // act
    b = static_cast<const SparseVectorBase<float>&>(a);
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(5);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(5);
    b.set(1, 11);
    b.set(2, 22);
    b.set(4, 33);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<std::complex<float>> a(5);
    a.set(0, {1, 2});
    a.set(2, {3, 4});
    a.set(4, {5, 6});
    SparseVector<std::complex<float>> b(5);
    // act
    b = std::move(a);
    const std::complex<float>* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(3);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    SparseVector<float> b(3);
    b.set(0, -0.2f);
    b.set(1, 20);
    b.set(2, 4);
    // act
    b = std::move(a);
    const float* bValues = b.values();
    const int* bIndexes = b.indices();
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
    SparseVector<float> a(5);
    a.set(0, 1);
    a.set(2, 2);
    a.set(4, 3);
    // act
    a = std::move(a);
    const float* aValues = a.values();
    const int* aIndexes = a.indices();
    // assert
    ASSERT_TRUE(a.values() != nullptr);
    ASSERT_TRUE(a.indices() != nullptr);
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
#pragma endregion
#pragma region sparse_vector_view
#pragma region constructor
TEST(sparse_vector_view_constructor, given_f_sparse_vector_should_construct) {
    // arrange
    SparseVector<float> a(5);
    a.set(1, 1);
    a.set(2, 2);
    a.set(3, 3);
    SparseVector<float> expected(3);
    expected.set(0, 1);
    expected.set(1, 2);
    expected.set(2, 3);
    // act
    const SparseVectorView<float> v(a, 3, 1);
    // assert
    ASSERT_TRUE((compare(v.n(), 3)));
    ASSERT_TRUE((compare(v.offset(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), v, expected)));
}

TEST(sparse_vector_view_constructor, given_cf_sparse_vector_should_construct) {
    // arrange
    SparseVector<std::complex<float>> a(5);
    a.set(1, {1, 2});
    a.set(2, {3, 4});
    a.set(3, {5, 6});
    SparseVector<std::complex<float>> expected(3);
    expected.set(0, {1, 2});
    expected.set(1, {3, 4});
    expected.set(2, {5, 6});
    // act
    const SparseVectorView<std::complex<float>> v(a, 3, 1);
    // assert
    ASSERT_TRUE((compare(v.n(), 3)));
    ASSERT_TRUE((compare(v.offset(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), v, expected)));
}
#pragma endregion
#pragma region copy_constructor
TEST(sparse_vector_view_copy_constructor, given_f_sparse_vector_view_should_copy) {
    // arrange
    SparseVector<float> a(5);
    a.set(1, 1);
    a.set(2, 2);
    a.set(3, 3);
    const SparseVectorView<float> v(a, 3, 1);
    // act
    const SparseVectorView<float> newView = v;
    // assert
    ASSERT_TRUE((compare(newView.n(), 3)));
    ASSERT_TRUE((compare(newView.offset(), 1)));
    ASSERT_TRUE(&v.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), v, newView)));
}

TEST(sparse_vector_view_copy_constructor, given_cf_sparse_vector_view_should_copy) {
    // arrange
    SparseVector<std::complex<float>> a(5);
    a.set(1, {1, 2});
    a.set(2, {3, 4});
    a.set(3, {5, 6});
    const SparseVectorView<std::complex<float>> v(a, 3, 1);
    // act
    const SparseVectorView<std::complex<float>> newView = v;
    // assert
    ASSERT_TRUE((compare(newView.n(), 3)));
    ASSERT_TRUE((compare(newView.offset(), 1)));
    ASSERT_TRUE(&v.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), v, newView)));
}
#pragma endregion
#pragma region set
TEST(sparse_vector_view_set, given_index_should_throw) {
    // arrange
    SparseVector<float> a(5);
    SparseVectorView<float> v(a, 3, 1);
    // act
    ASSERT_THROW(v.set(0, 1), InvalidOperationException);
}

TEST(sparse_vector_view_set, given_negative_index_should_throw) {
    // arrange
    SparseVector<float> a(5);
    SparseVectorView<float> v(a, 3, 1);
    // act
    ASSERT_THROW(v.set(-1, 1), InvalidIndexException);
}

TEST(sparse_vector_view_set, given_big_index_should_throw_1) {
    // arrange
    SparseVector<float> a(5);
    SparseVectorView<float> v(a, 3, 2);
    // act
    ASSERT_THROW(v.set(3, 1), InvalidIndexException);
}
#pragma endregion
#pragma region get
TEST(sparse_vector_view_get, given_index_should_return_value_f) {
    // arrange
    SparseVector<float> a(5);
    a.set(2, 1);
    SparseVectorView<float> v(a, 3, 1);
    // act
    const float value = v.get(1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 1)));
}

TEST(sparse_vector_view_get, given_index_should_return_value_cf) {
    // arrange
    SparseVector<std::complex<float>> a(5);
    a.set(2, {1, 2});
    SparseVectorView<std::complex<float>> v(a, 3, 1);
    // act
    const std::complex<float> value = v.get(1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(1, 2))));
}

TEST(sparse_vector_view_get, given_negative_index_should_throw_f) {
    // arrange
    SparseVector<float> a(5);
    SparseVectorView<float> v(a, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(-1), InvalidIndexException);
}

TEST(sparse_vector_view_get, given_big_index_should_throw_f_1) {
    // arrange
    SparseVector<float> a(5);
    SparseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(3), InvalidIndexException);
}

TEST(sparse_vector_view_get, given_big_index_should_throw_f_2) {
    // arrange
    SparseVector<float> a(5);
    SparseVectorView<float> v(a, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(3), InvalidIndexException);
}
#pragma endregion
#pragma region nnz
TEST(sparse_vector_nnz, should_return_nnz_1) {
    // arrange
    SparseVector<float> a(5);
    a.set(1, 1);
    SparseVectorView<float> v(a, 3, 1);
    // act
    const int nnz = v.nnz();
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
}

TEST(sparse_vector_nnz, should_return_nnz_2) {
    // arrange
    SparseVector<float> a(5);
    a.set(1, 1);
    a.set(0, 2);
    SparseVectorView<float> v(a, 3, 1);
    // act
    const int nnz = v.nnz();
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
}

TEST(sparse_vector_nnz, should_return_zero_1) {
    // arrange
    SparseVector<float> a(5);
    SparseVectorView<float> v(a, 3, 1);
    // act
    const int nnz = v.nnz();
    // assert
    ASSERT_TRUE((compare(nnz, 0)));
}

TEST(sparse_vector_nnz, should_return_zero_2) {
    // arrange
    SparseVector<float> a(5);
    a.set(0, 2);
    SparseVectorView<float> v(a, 3, 1);
    // act
    const int nnz = v.nnz();
    // assert
    ASSERT_TRUE((compare(nnz, 0)));
}
#pragma endregion
#pragma region offset
TEST(sparse_vector_view_offset, should_return_offset) {
    // arrange
    const SparseVector<float> a(5);
    const SparseVectorView<float> v(a, 3, 1);
    constexpr int expected = 1;
    // act
    const int offset = v.offset();
    // assert
    ASSERT_TRUE((compare(offset, expected)));
}
#pragma endregion
#pragma region owner
TEST(sparse_vector_view_owner, should_return_owner) {
    // arrange
    const SparseVector<float> a(5);
    const SparseVectorView<float> v(a, 3, 1);
    // act
    const SparseVector<float>& owner = v.owner();
    // assert
    ASSERT_TRUE(&owner == &a);
}
#pragma endregion
#pragma endregion
#pragma region custom_sparse_vector
#pragma region constructor
TEST(custom_sparse_vector_constructor, given_f_pointer_and_i_pointer_and_size_should_construct) {
    // arrange
    float* values = new float[2];
    values[0] = 1;
    values[1] = 2;
    int* indices = new int[2];
    indices[0] = 2;
    indices[0] = 4;
    int nnz = 2;
    // act
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[2];
    indices[0] = 2;
    indices[0] = 4;
    int nnz = 2;
    // act
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
    const float* oldVValues = values;
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
    v.set(0, 1);
    const float* oldVValues = values;
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
    v.set(0, 1);
    v.set(2, 2);
    const float* oldVValues = values;
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
    v.set(3, 1);
    const float* oldVValues = values;
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
    v.set(2, 1);
    const float* oldVValues = values;
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
    v.set(1, 2);
    v.set(2, 1);
    const float* oldVValues = values;
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
    v.set(1, 2);
    v.set(2, 1);
    v.set(3, 4);
    const float* oldVValues = values;
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
    v.set(2, 1);
    v.set(3, 2);
    const float* oldVValues = values;
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(0, {1, 2});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(0, {1, 2});
    v.set(2, {3, 4});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(3, {1, 2});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(1, {1, 2});
    v.set(2, {3, 4});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(1, {1, 2});
    v.set(2, {3, 4});
    v.set(3, {5, 6});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    v.set(3, {3, 4});
    const std::complex<float>* oldVValues = v.values();
    const int* oldVIndexes = indices;
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
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

TEST(custom_sparse_vector_set, given_negative_index_should_throw) {
    // arrange
    float* values = new float[0];
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
    // act / assert
    ASSERT_THROW(v.set(-1, 0), InvalidIndexException);
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_set, given_big_index_should_throw) {
    // arrange
    float* values = new float[0];
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
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
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<std::complex<float>> v(5, values, indices, nnz);
    v.set(2, {1, 2});
    // act
    const std::complex<float> value = v.get(1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(0, 0))));
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_get, given_negative_index_should_throw) {
    // arrange
    float* values = new float[0];
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(-1), InvalidIndexException);
    // clean up
    delete[] values;
    delete[] indices;
}

TEST(custom_sparse_vector_get, given_big_index_should_throw) {
    // arrange
    float* values = new float[0];
    int* indices = new int[0];
    int nnz = 0;
    CustomSparseVector<float> v(5, values, indices, nnz);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(5), InvalidIndexException);
    // clean up
    delete[] values;
    delete[] indices;
}
#pragma endregion
#pragma endregion
