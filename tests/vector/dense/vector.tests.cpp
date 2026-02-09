#include "gtest/gtest.h"

#include "mathpp/math.h"

#pragma region dense_vector_indexing_operator
TEST(dense_vector_indexing_operator, given_index_should_return_reference_f) {
    // arrange
    DenseVector<float> v = {1, 2, 3};
    // act
    float& val0 = v[0];
    float& val1 = v[1];
    float& val2 = v[2];
    // assert
    ASSERT_TRUE((compare<float, float>(val0, 1, 0.001f)));
    val0 = 4;
    ASSERT_TRUE((compare<float, float>(val0, 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(val1, 2, 0.001f)));
    val1 = 5;
    ASSERT_TRUE((compare<float, float>(val1, 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(val2, 3, 0.001f)));
    val2 = 6;
    ASSERT_TRUE((compare<float, float>(val2, 6, 0.001f)));
}

TEST(dense_vector_indexing_operator, given_index_should_return_reference_cf) {
    // arrange
    DenseVector<std::complex<float>> v = {{1, 2}, {3, 4}, {5, 6}};
    // act
    std::complex<float>& val0 = v[0];
    std::complex<float>& val1 = v[1];
    std::complex<float>& val2 = v[2];
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(val0, {1, 2}, 0.001f)));
    val0 = {7, 8};
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(val0, {7, 8}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(val1, {3, 4}, 0.001f)));
    val1 = {9, 10};
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(val1, {9, 10}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(val2, {5, 6}, 0.001f)));
    val2 = {11, 12};
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(val2, {11, 12}, 0.001f)));
}

TEST(dense_vector_indexing_operator, given_negative_index_should_throw) {
    // arrange
    DenseVector<float> v = {1, 2, 3};
    // act / assert
    ASSERT_THROW({std::ignore = v[-1];}, InvalidIndexException);
}

TEST(dense_vector_indexing_operator, given_big_index_should_throw) {
    // arrange
    DenseVector<float> v = {1, 2, 3};
    // act / assert
    ASSERT_THROW({std::ignore = v[4];}, InvalidIndexException);
}
#pragma endregion
#pragma region dense_vector_const_indexing_operator
TEST(dense_vector_const_indexing_operator, given_index_should_return_const_reference_f) {
    // arrange
    const DenseVector<float> v = {1, 2, 3};
    // act
    const float& val0 = v[0];
    const float& val1 = v[1];
    const float& val2 = v[2];
    // assert
    ASSERT_TRUE((compare<float, float>(val0, 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(val1, 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(val2, 3, 0.001f)));
}

TEST(dense_vector_const_indexing_operator, given_index_should_return_const_reference_cf) {
    // arrange
    const DenseVector<std::complex<float>> v = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const std::complex<float>& val0 = v[0];
    const std::complex<float>& val1 = v[1];
    const std::complex<float>& val2 = v[2];
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(val0, {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(val1, {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(val2, {5, 6}, 0.001f)));
}

TEST(dense_vector_const_indexing_operator, given_negative_index_should_throw) {
    // arrange
    const DenseVector<float> v = {1, 2, 3};
    // act / assert
    ASSERT_THROW({std::ignore = v[-1];}, InvalidIndexException);
}

TEST(dense_vector_const_indexing_operator, given_big_index_should_throw) {
    // arrange
    const DenseVector<float> v = {1, 2, 3};
    // act / assert
    ASSERT_THROW({std::ignore = v[4];}, InvalidIndexException);
}
#pragma endregion
#pragma region dense_vector_default_constructor
TEST(dense_vector_default_constructor, given_size_and_fill_should_initialize_data_and_size_f) {
    // arrange / act
    const DenseVector<float> v(3, true);
    const DenseVector<float> expected = {0, 0, 0};
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_default_constructor, given_size_and_fill_should_initialize_data_and_size_cf) {
    // arrange / act
    const DenseVector<std::complex<float>> v(3, true);
    const DenseVector<std::complex<float>> expected = {{0, 0}, {0, 0}, {0, 0}};
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region dense_vector_initializer_list_constructor
TEST(dense_vector_initializer_list_constructor, given_initializer_list_of_floats_should_initialize_size_and_elements_f) {
    // arrange / act
    const DenseVector<float> v = {1, 2, 3};
    DenseVector<float> expected(3, false);
    expected[0] = 1;
    expected[1] = 2;
    expected[2] = 3;
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_initializer_list_constructor, given_initializer_list_of_floats_should_initialize_size_and_elements_cf) {
    // arrange / act
    const DenseVector<std::complex<float>> v = {{1, 2}, {3, 4}, {5, 6}};
    DenseVector<std::complex<float>> expected(3, false);
    expected[0] = {1, 2};
    expected[1] = {3, 4};
    expected[2] = {5, 6};
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region dense_vector_copy_constructor_from_same_type_dense_vector
TEST(dense_vector_copy_constructor_from_same_type_dense_vector, given_dense_vector_templated_on_float_should_initialize_size_and_elements) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    // act
    const DenseVector<float> v = expected; // NOLINT(*-unnecessary-copy-initialization)
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_constructor_from_same_type_dense_vector, given_dense_vector_templated_on_complex_float_should_initialize_size_and_elements) {
    // arrange
    const DenseVector<std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const DenseVector<std::complex<float>> v = expected; // NOLINT(*-unnecessary-copy-initialization)
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region dense_vector_copy_constructor_from_different_type_dense_vector
TEST(dense_vector_copy_constructor_from_different_type_dense_vector, given_dense_vector_templated_on_float_should_initialize_size_and_elements) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    // act
    const DenseVector<std::complex<float>> v = expected;
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<float>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region dense_vector_copy_constructor_from_same_type_dense_vector_base
TEST(dense_vector_copy_constructor_from_same_type_dense_vector_base, given_dense_vector_base_templated_on_float_should_initialize_size_and_elements) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    // act
    const DenseVector<float> v = static_cast<const DenseVectorBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_constructor_from_same_type_dense_vector_base, given_dense_vector_base_templated_on_complex_float_should_initialize_size_and_elements) {
    // arrange
    const DenseVector<std::complex<float>> expected = {1, 2, 3};
    // act
    const DenseVector<std::complex<float>> v = static_cast<const DenseVectorBase<std::complex<float>>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region dense_vector_copy_constructor_from_different_type_dense_vector_base
TEST(dense_vector_copy_constructor_from_different_type_dense_vector_base, given_dense_vector_base_templated_on_float_should_initialize_size_and_elements) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    // act
    const DenseVector<std::complex<float>> v = static_cast<const DenseVectorBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<float>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region dense_vector_move_constructor
TEST(dense_vector_move_constructor, given_dense_vector_templated_on_float_should_initialize_size_and_elements_and_invalidate_other_data) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> expected = {1, 2, 3};
    // act
    const DenseVector<float> v = std::move(a);
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_move_constructor, given_dense_vector_templated_on_complex_float_should_initialize_size_and_elements_and_invalidate_other_data) {
    // arrange
    DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    const DenseVector<std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const DenseVector<std::complex<float>> v = std::move(a);
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region dense_vector_copy_assignment_operator_from_same_type_dense_vector
TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_dense_vector_templated_on_float_should_copy_elements) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<float> v(3, true);
    // act
    v = expected;
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_dense_vector_templated_on_float_of_different_size_should_throw) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<float> v(2, true);
    // act / assert
    ASSERT_THROW(v = expected, InvalidDimensionException);
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_dense_vector_templated_on_complex_float_should_copy_elements) {
    // arrange
    const DenseVector<std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    DenseVector<std::complex<float>> v(3, true);
    // act
    v = expected;
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_dense_vector_templated_on_complex_float_of_different_size_should_throw) {
    // arrange
    const DenseVector<std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    DenseVector<std::complex<float>> v(2, true);
    // act / assert
    ASSERT_THROW(v = expected, InvalidDimensionException);
}
#pragma endregion
#pragma region dense_vector_copy_assignment_operator_from_different_type_dense_vector
TEST(dense_vector_copy_assignment_operator_from_different_type_dense_vector, given_dense_vector_templated_on_float_should_copy_elements) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<std::complex<float>> v(3, true);
    // act
    v = expected;
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_assignment_operator_from_different_type_dense_vector, given_dense_vector_templated_on_float_of_different_size_should_throw) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<std::complex<float>> v(2, true);
    // act / assert
    ASSERT_THROW(v = expected, InvalidDimensionException);
}
#pragma endregion
#pragma region dense_vector_copy_assignment_operator_from_same_type_dense_vector_base
TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector_base, given_dense_vector_base_templated_on_float_should_copy_elements) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<float> v(3, true);
    // act
    v = static_cast<const DenseVectorBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector_base, given_dense_vector_base_templated_on_complex_float_should_copy_elements) {
    // arrange
    const DenseVector<std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    DenseVector<std::complex<float>> v(3, true);
    // act
    v = static_cast<const DenseVectorBase<std::complex<float>>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region dense_vector_copy_assignment_operator_from_different_type_dense_vector_base
TEST(dense_vector_copy_assignment_operator_from_different_type_dense_vector_base, given_dense_vector_base_templated_on_float_should_copy_elements) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<std::complex<float>> v(3, true);
    // act
    v = static_cast<const DenseVectorBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<float>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region dense_vector_move_assignment_operator
TEST(dense_vector_move_assignment_operator, given_dense_vector_templated_on_float_should_copy_data) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<float> v(3, true);
    // act
    v = std::move(a);
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_move_assignment_operator, given_dense_vector_templated_on_complex_float_should_copy_data) {
    // arrange
    DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    const DenseVector<std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    DenseVector<std::complex<float>> v(3, true);
    // act
    v = std::move(a);
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}

TEST(dense_vector_move_assignment_operator, given_dense_vector_of_different_size_should_throw) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    DenseVector<float> v(2, true);
    // act / assert
    ASSERT_THROW(v = std::move(a), InvalidDimensionException);
}
#pragma endregion
#pragma region dense_vector_data
TEST(dense_vector_data, given_dense_vector_templated_on_float_should_give_data_pointer) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    // act
    float* data = a.data();
    // assert
    ASSERT_TRUE((compare<float, float>(data[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[2], 3, 0.001f)));
}

TEST(dense_vector_data, given_dense_vector_templated_on_complex_float_should_give_data_pointer) {
    // arrange
    DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    // act
    std::complex<float>* data = a.data();
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[2], {5, 6}, 0.001f)));
}
#pragma endregion
#pragma region dense_vector_const_data
TEST(dense_vector_const_data, given_dense_vector_templated_on_float_should_give_const_data_pointer) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    // act
    const float* data = a.data();
    // assert
    ASSERT_TRUE((compare<float, float>(data[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[2], 3, 0.001f)));
}

TEST(dense_vector_const_data, given_dense_vector_templated_on_complex_float_should_give_const_data_pointer) {
    // arrange
    DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const std::complex<float>* data = a.data();
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[1], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[2], {5, 6}, 0.001f)));
}
#pragma endregion
