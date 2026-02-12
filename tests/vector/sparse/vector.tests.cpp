#include "gtest/gtest.h"

#include "mathpp/math.h"

#pragma region sparse_vector
#pragma region set
TEST(sparse_vector_set, given_index_to_zero_value_and_non_zero_value_should_set_f) {
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

TEST(sparse_vector_set, given_index_to_non_zero_value_and_non_zero_value_should_set_f) {
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

TEST(sparse_vector_set, given_index_to_non_zero_value_and_zero_value_should_set_f) {
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

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_do_nothing_f) {
    // arrange
    SparseVector<float> v(3);
    constexpr int expectedNnz = 0;
    // act
    v.set(1, 0);
    // assert
    const int vNnz = v.nnz();
    ASSERT_TRUE((compare<int, int>(expectedNnz, vNnz)));
}

TEST(sparse_vector_set, given_index_to_zero_value_and_non_zero_value_should_set_cf) {
    // arrange
    SparseVector<std::complex<float>> v(3);
    std::complex<float>* expectedValues = new std::complex<float>[1];
    expectedValues[0] = {2, 3};
    int* expectedIndices = new int[1];
    expectedIndices[0] = 1;
    constexpr int expectedNnz = 1;
    // act
    v.set(1, {2, 3});
    // assert
    const int vNnz = v.nnz();
    const std::complex<float>* vValues = v.values();
    const int* vIndices = v.indexes();
    ASSERT_TRUE((compare<int, int>(expectedNnz, vNnz)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], expectedValues[0], 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndices[0], expectedIndices[0])));
}

TEST(sparse_vector_set, given_index_to_non_zero_value_and_non_zero_value_should_set_cf) {
    // arrange
    SparseVector<std::complex<float>> v(3);
    std::complex<float>* expectedValues = new std::complex<float>[1];
    expectedValues[0] = {2, 3};
    int* expectedIndices = new int[1];
    expectedIndices[0] = 1;
    constexpr int expectedNnz = 1;
    // act
    v.set(1, {4, 5});
    v.set(1, {2, 3});
    // assert
    const int vNnz = v.nnz();
    const std::complex<float>* vValues = v.values();
    const int* vIndices = v.indexes();
    ASSERT_TRUE((compare<int, int>(expectedNnz, vNnz)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(vValues[0], expectedValues[0], 0.001f)));
    ASSERT_TRUE((compare<int, int>(vIndices[0], expectedIndices[0])));
}

TEST(sparse_vector_set, given_index_to_non_zero_value_and_zero_value_should_set_cf) {
    // arrange
    SparseVector<std::complex<float>> v(3);
    constexpr int expectedNnz = 0;
    // act
    v.set(1, {4, 5});
    v.set(1, {0, 0});
    // assert
    const int vNnz = v.nnz();
    ASSERT_TRUE((compare<int, int>(expectedNnz, vNnz)));
}

TEST(sparse_vector_set, given_index_to_zero_element_and_zero_value_should_do_nothing_cf) {
    // arrange
    SparseVector<std::complex<float>> v(3);
    constexpr int expectedNnz = 0;
    // act
    v.set(1, {0, 0});
    // assert
    const int vNnz = v.nnz();
    ASSERT_TRUE((compare<int, int>(expectedNnz, vNnz)));
}
#pragma endregion
#pragma region get
TEST(sparse_vector_get, given_index_to_non_zero_value_should_return_value_f) {
    // arrange
    SparseVector<float> v(3);
    constexpr float expectedValue = 2;
    v.set(1, 2);
    // act
    const float value = v.get(1);
    // assert
    ASSERT_TRUE((compare<float, float>(value, expectedValue, 0.001f)));
}

TEST(sparse_vector_get, given_index_to_zero_value_should_return_zero_f) {
    // arrange
    SparseVector<float> v(3);
    constexpr float expectedValue = 0;
    v.set(1, 2);
    // act
    const float value = v.get(2);
    // assert
    ASSERT_TRUE((compare<float, float>(value, expectedValue, 0.001f)));
}

TEST(sparse_vector_get, given_index_to_non_zero_value_should_return_value_cf) {
    // arrange
    SparseVector<std::complex<float>> v(3);
    constexpr std::complex<float> expectedValue = {3, 4};
    v.set(1, {3, 4});
    // act
    const std::complex<float> value = v.get(1);
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(value, expectedValue, 0.001f)));
}

TEST(sparse_vector_get, given_index_to_zero_value_should_return_zero_cf) {
    // arrange
    SparseVector<std::complex<float>> v(3);
    constexpr std::complex<float> expectedValue = {0, 0};
    v.set(1, {1, 2});
    // act
    const std::complex<float> value = v.get(2);
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(value, expectedValue, 0.001f)));
}
#pragma endregion
#pragma region constructor
TEST(sparse_vector_constructor, given_size_should_construct_f) {
    // arrange
    constexpr int expectedNnz = 0;
    constexpr int expectedN = 3;
    // act
    const SparseVector<float> v(3);
    // assert
    const int vNnz = v.nnz();
    const int vN = v.n;
    ASSERT_TRUE((compare<int, int>(vNnz, expectedNnz)));
    ASSERT_TRUE((compare<int, int>(vN, expectedN)));
}

TEST(sparse_vector_constructor, given_size_should_construct_cf) {
    // arrange
    constexpr int expectedNnz = 0;
    constexpr int expectedN = 3;
    // act
    const SparseVector<std::complex<float>> v(3);
    // assert
    const int vNnz = v.nnz();
    const int vN = v.n;
    ASSERT_TRUE((compare<int, int>(vNnz, expectedNnz)));
    ASSERT_TRUE((compare<int, int>(vN, expectedN)));
}
#pragma endregion
#pragma region copy_constructor_from_same_type_sparse_vector
TEST(sparse_vector_copy_constructor_from_same_type_sparse_vector, given_f_sparse_vector_should_copy_construct) {
    // arrange
    SparseVector<float> expected(3);
    expected.set(0, 1);
    expected.set(2, 2);
    // act
    const SparseVector<float> v = expected;
    // assert
    ASSERT_TRUE((compare<SparseVector<float>, SparseVector<float>>(v, expected, 0.001f)));
}

TEST(sparse_vector_copy_constructor_from_same_type_sparse_vector, given_cf_sparse_vector_should_copy_construct) {
    // arrange
    SparseVector<std::complex<float>> expected(3);
    expected.set(0, {1, 2});
    expected.set(2, {3, 4});
    // act
    const SparseVector<std::complex<float>> v = expected;
    // assert
    ASSERT_TRUE((compare<SparseVector<std::complex<float>>, SparseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_sparse_vector
TEST(sparse_vector_copy_constructor_from_different_type_sparse_vector, given_f_sparse_vector_should_copy_construct) {
    // arrange
    SparseVector<float> expected(3);
    expected.set(0, 1);
    expected.set(2, 2);
    // act
    const SparseVector<std::complex<float>> v = expected;
    // assert
    ASSERT_TRUE((compare<SparseVector<std::complex<float>>, SparseVector<float>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_constructor_from_same_type_sparse_vector_base
TEST(sparse_vector_copy_constructor_from_same_type_sparse_vector_base, given_f_sparse_vector_base_should_copy_construct) {
    // arrange
    SparseVector<float> expected(3);
    expected.set(0, 1);
    expected.set(2, 2);
    // act
    const SparseVector<float> v = static_cast<const SparseVectorBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<SparseVector<float>, SparseVector<float>>(v, expected, 0.001f)));
}

TEST(sparse_vector_copy_constructor_from_same_type_sparse_vector_base, given_cf_sparse_vector_base_should_copy_construct) {
    // arrange
    SparseVector<std::complex<float>> expected(3);
    expected.set(0, {1, 2});
    expected.set(2, {3, 4});
    // act
    const SparseVector<std::complex<float>> v = static_cast<const SparseVectorBase<std::complex<float>>&>(expected);
    // assert
    ASSERT_TRUE((compare<SparseVector<std::complex<float>>, SparseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_sparse_vector_base
TEST(sparse_vector_copy_constructor_from_different_type_sparse_vector_base, given_f_sparse_vector_base_should_copy_construct) {
    // arrange
    SparseVector<float> expected(3);
    expected.set(0, 1);
    expected.set(2, 2);
    // act
    const SparseVector<std::complex<float>> v = static_cast<const SparseVectorBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<SparseVector<std::complex<float>>, SparseVector<float>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region move_constructor
TEST(sparse_vector_move_constructor, given_f_sparse_vector_should_move_construct_and_invalidate_other) {
    // arrange
    SparseVector<float> a(3);
    a.set(0, 3);
    a.set(2, 1);
    SparseVector<float> expected(3);
    expected.set(0, 3);
    expected.set(2, 1);
    // act
    const SparseVector<float> v = std::move(a);
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.indexes() == nullptr);
    ASSERT_TRUE((compare<SparseVector<float>, SparseVector<float>>(v, expected, 0.001f)));
}

TEST(sparse_vector_move_constructor, given_cf_sparse_vector_should_move_construct_and_invalidate_other) {
    // arrange
    SparseVector<std::complex<float>> a(3);
    a.set(0, {3, 4});
    a.set(2, {1, 2});
    SparseVector<std::complex<float>> expected(3);
    expected.set(0, {3, 4});
    expected.set(2, {1, 2});
    // act
    const SparseVector<std::complex<float>> v = std::move(a);
    // assert
    ASSERT_TRUE(a.values() == nullptr);
    ASSERT_TRUE(a.indexes() == nullptr);
    ASSERT_TRUE((compare<SparseVector<std::complex<float>>, SparseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_sparse_vector
TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector, given_f_sparse_vector_should_copy_assign) {
    // arrange
    SparseVector<float> expected(3);
    expected.set(0, 3);
    expected.set(2, 1);
    SparseVector<float> v(3);
    // act
    v = expected;
    // assert
    ASSERT_TRUE((compare<SparseVector<float>, SparseVector<float>>(v, expected, 0.001f)));
}

TEST(sparse_vector_copy_assignment_operator_from_same_type_sparse_vector, given_cf_sparse_vector_should_copy_assign) {
    // arrange
    SparseVector<std::complex<float>> expected(3);
    expected.set(0, 3);
    expected.set(2, 1);
    SparseVector<std::complex<float>> v(3);
    // act
    v = expected;
    // assert
    ASSERT_TRUE((compare<SparseVector<std::complex<float>>, SparseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma endregion