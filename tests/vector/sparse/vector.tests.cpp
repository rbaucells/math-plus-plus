#include "gtest/gtest.h"

#include "mathpp/math.h"

#pragma region sparse_vector
#pragma region set
TEST(sparse_vector_set, given_index_to_zero_value_and_non_zero_value_should_set) {
    // arrange
    SparseVector<float> v(3);
    float* expectedValues = new float[1];
    expectedValues[0] = 2;
    int* expectedIndices = new int[1];
    expectedIndices[0] = 1;
    constexpr int expectedNnz = 1;
    // act
    v.set(1, 2);
    // assert
    const int vNnz = v.nnz();
    const float* vValues = v.values();
    const int* vIndices = v.indexes();
    ASSERT_TRUE((compare<int, int>(expectedNnz, vNnz)));
    ASSERT_TRUE((compare<float, float>(vValues[0], expectedValues[0], 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndices[0], expectedIndices[0])));
}

TEST(sparse_vector_set, given_index_to_non_zero_value_and_non_zero_value_should_set) {
    // arrange
    SparseVector<float> v(3);
    float* expectedValues = new float[1];
    expectedValues[0] = 2;
    int* expectedIndices = new int[1];
    expectedIndices[0] = 1;
    constexpr int expectedNnz = 1;
    // act
    v.set(1, 4);
    v.set(1, 2);
    // assert
    const int vNnz = v.nnz();
    const float* vValues = v.values();
    const int* vIndices = v.indexes();
    ASSERT_TRUE((compare<int, int>(expectedNnz, vNnz)));
    ASSERT_TRUE((compare<float, float>(vValues[0], expectedValues[0], 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndices[0], expectedIndices[0])));
}

TEST(sparse_vector_set, given_index_to_non_zero_value_and_zero_value_should_set) {
    // arrange
    SparseVector<float> v(3);
    constexpr int expectedNnz = 0;
    // act
    v.set(1, 4);
    v.set(1, 0);
    // assert
    const int vNnz = v.nnz();
    ASSERT_TRUE((compare<int, int>(expectedNnz, vNnz)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_do_nothing) {
    // arrange
    SparseVector<float> v(3);
    constexpr int expectedNnz = 0;
    // act
    v.set(1, 0);
    // assert
    const int vNnz = v.nnz();
    ASSERT_TRUE((compare<int, int>(expectedNnz, vNnz)));
}
#pragma endregion
#pragma endregion