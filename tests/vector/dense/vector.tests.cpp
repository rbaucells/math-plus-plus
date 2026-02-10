#include "gtest/gtest.h"

#include "mathpp/math.h"

#pragma region dense_vector
#pragma region indexing_operator
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
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
}

TEST(dense_vector_indexing_operator, given_big_index_should_throw) {
    // arrange
    DenseVector<float> v = {1, 2, 3};
    // act / assert
    ASSERT_THROW(std::ignore = v[4], InvalidIndexException);
}
#pragma endregion
#pragma region const_indexing_operator
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
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
}

TEST(dense_vector_const_indexing_operator, given_big_index_should_throw) {
    // arrange
    const DenseVector<float> v = {1, 2, 3};
    // act / assert
    ASSERT_THROW(std::ignore = v[4], InvalidIndexException);
}
#pragma endregion
#pragma region default_constructor
TEST(dense_vector_default_constructor, given_size_and_fill_should_construct_f) {
    // arrange / act
    const DenseVector<float> v(3, true);
    const DenseVector<float> expected = {0, 0, 0};
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_default_constructor, given_size_and_fill_should_construct_cf) {
    // arrange / act
    const DenseVector<std::complex<float>> v(3, true);
    const DenseVector<std::complex<float>> expected = {{0, 0}, {0, 0}, {0, 0}};
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region initializer_list_constructor
TEST(dense_vector_initializer_list_constructor, given_initializer_list_should_construct_f) {
    // arrange / act
    const DenseVector<float> v = {1, 2, 3};
    DenseVector<float> expected(3, false);
    expected[0] = 1;
    expected[1] = 2;
    expected[2] = 3;
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_initializer_list_constructor, given_initializer_list_should_construct_cf) {
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
#pragma region copy_constructor_from_same_type_dense_vector
TEST(dense_vector_copy_constructor_from_same_type_dense_vector, given_f_dense_vector_should_copy_construct) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    // act
    const DenseVector<float> v = expected;
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_constructor_from_same_type_dense_vector, given_cf_dense_vector_should_copy_construct) {
    // arrange
    const DenseVector<std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const DenseVector<std::complex<float>> v = expected;
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_dense_vector
TEST(dense_vector_copy_constructor_from_different_type_dense_vector, given_f_dense_vector_should_copy_construct) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    // act
    const DenseVector<std::complex<float>> v = expected;
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<float>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_constructor_from_same_type_dense_vector_base
TEST(dense_vector_copy_constructor_from_same_type_dense_vector_base, given_f_dense_vector_base_should_copy_construct) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    // act
    const DenseVector<float> v = static_cast<const DenseVectorBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_constructor_from_same_type_dense_vector_base, given_cf_dense_vector_base_should_copy_construct) {
    // arrange
    const DenseVector<std::complex<float>> expected = {1, 2, 3};
    // act
    const DenseVector<std::complex<float>> v = static_cast<const DenseVectorBase<std::complex<float>>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_dense_vector_base
TEST(dense_vector_copy_constructor_from_different_type_dense_vector_base, given_f_dense_vector_base_should_copy_construct) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    // act
    const DenseVector<std::complex<float>> v = static_cast<const DenseVectorBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<float>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region move_constructor
TEST(dense_vector_move_constructor, given_f_dense_vector_should_move_construct_and_invalidate_other_data) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    const DenseVector<float> expected = {1, 2, 3};
    // act
    const DenseVector<float> v = std::move(a);
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_move_constructor, given_cf_dense_vector_should_move_construct_and_invalidate_other_data) {
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
#pragma region copy_assignment_operator_from_same_type_dense_vector
TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_f_dense_vector_should_copy_assign) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<float> v(3, true);
    // act
    v = expected;
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_f_dense_vector_of_different_size_should_throw) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<float> v(2, true);
    // act / assert
    ASSERT_THROW(v = expected, InvalidDimensionException);
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_cf_dense_vector_should_copy_assign) {
    // arrange
    const DenseVector<std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    DenseVector<std::complex<float>> v(3, true);
    // act
    v = expected;
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_cf_dense_vector_of_different_size_should_throw) {
    // arrange
    const DenseVector<std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    DenseVector<std::complex<float>> v(2, true);
    // act / assert
    ASSERT_THROW(v = expected, InvalidDimensionException);
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_dense_vector
TEST(dense_vector_copy_assignment_operator_from_different_type_dense_vector, given_f_dense_vector_should_copy_assign) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<std::complex<float>> v(3, true);
    // act
    v = expected;
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_assignment_operator_from_different_type_dense_vector, given_f_dense_vector_of_different_size_should_throw) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<std::complex<float>> v(2, true);
    // act / assert
    ASSERT_THROW(v = expected, InvalidDimensionException);
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_dense_vector_base
TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector_base, given_f_dense_vector_base_should_copy_assign) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<float> v(3, true);
    // act
    v = static_cast<const DenseVectorBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector_base, given_cf_dense_vector_base_should_copy_assign) {
    // arrange
    const DenseVector<std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    DenseVector<std::complex<float>> v(3, true);
    // act
    v = static_cast<const DenseVectorBase<std::complex<float>>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_base
TEST(dense_vector_copy_assignment_operator_from_different_type_dense_vector_base, given_f_dense_vector_base_should_copy_assign) {
    // arrange
    const DenseVector<float> expected = {1, 2, 3};
    DenseVector<std::complex<float>> v(3, true);
    // act
    v = static_cast<const DenseVectorBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseVector<std::complex<float>>, DenseVector<float>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region move_assignment_operator
TEST(dense_vector_move_assignment_operator, given_f_dense_vector_should_move_assign) {
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

TEST(dense_vector_move_assignment_operator, given_cf_dense_vector_should_move_assign) {
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
#pragma region data
TEST(dense_vector_data, should_return_data_pointer_f) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    // act
    float* data = a.data();
    // assert
    ASSERT_TRUE((compare<float, float>(data[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[2], 3, 0.001f)));
}

TEST(dense_vector_data, should_return_data_pointer_cf) {
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
#pragma region const_data
TEST(dense_vector_const_data, should_return_const_data_pointer_f) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    // act
    const float* data = a.data();
    // assert
    ASSERT_TRUE((compare<float, float>(data[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[1], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[2], 3, 0.001f)));
}

TEST(dense_vector_const_data, should_return_const_data_pointer_cf) {
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
#pragma endregion
#pragma region dense_vector_view
#pragma region constructor
TEST(dense_vector_view_constructor, given_f_dense_vector_should_construct) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVector<float> expected = {2, 3, 4};
    // act
    const DenseVectorView<float> view = DenseVectorView<float>(a, 3, 1);
    // assert
    ASSERT_TRUE((compare<DenseVectorView<float>, DenseVector<float>>(view, expected, 0.001f)));
}

TEST(dense_vector_view_constructor, given_cf_dense_vector_should_construct) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    const DenseVector<std::complex<float>> expected = {{3, 4}, {5, 6}, {7, 8}};
    // act
    const DenseVectorView<std::complex<float>> view = DenseVectorView<std::complex<float>>(a, 3, 1);
    // assert
    ASSERT_TRUE(
        (compare<DenseVectorView<std::complex<float>>, DenseVector<std::complex<float>>>(view, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_constructor
TEST(dense_vector_view_copy_constructor, given_f_dense_vector_view_should_copy) {
    // arrange
    const DenseVector<float> v = {1, 2, 3, 4, 5};
    const DenseVectorView<float> view(v, 3, 2);
    // act
    const DenseVectorView<float> newView = view;
    // assert
    ASSERT_TRUE(&view.owner() == &newView.owner());
}

TEST(dense_vector_view_copy_constructor, given_cf_dense_vector_view_should_copy) {
    // arrange
    const DenseVector<std::complex<float>> v = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    const DenseVectorView<std::complex<float>> view(v, 3, 2);
    // act
    const DenseVectorView<std::complex<float>> newView = view;
    // assert
    ASSERT_TRUE(&view.owner() == &newView.owner());
}
#pragma endregion
#pragma region indexing_operator
TEST(dense_vector_view_indexing_operator, given_index_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[2], InvalidOperationException);
}

TEST(dense_vector_view_indexing_operator, given_negative_index_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
}

TEST(dense_vector_view_indexing_operator, given_big_index_should_throw_1) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}

TEST(dense_vector_view_indexing_operator, given_big_index_should_throw_2) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}
#pragma endregion
#pragma region const_indexing_operator
TEST(dense_vector_view_const_indexing_operator, given_index_should_return_const_reference_f) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVectorView<float> v(a, 3, 2);
    // act
    const float& v0 = v[0];
    const float& v1 = v[1];
    const float& v2 = v[2];
    // assert
    ASSERT_TRUE((compare<float, float>(v0, 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v1, 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v2, 5, 0.001f)));
}

TEST(dense_vector_view_const_indexing_operator, given_index_should_return_const_reference_cf) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    const DenseVectorView<std::complex<float>> v(a, 3, 2);
    // act
    const std::complex<float>& v0 = v[0];
    const std::complex<float>& v1 = v[1];
    const std::complex<float>& v2 = v[2];
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v0, {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v1, {7, 8}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v2, {9, 10}, 0.001f)));
}

TEST(dense_vector_view_const_indexing_operator, given_negative_index_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
}

TEST(dense_vector_view_const_indexing_operator, given_big_index_should_throw_1) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}

TEST(dense_vector_view_const_indexing_operator, given_big_index_should_throw_2) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}
#pragma endregion
#pragma region offset
TEST(dense_vector_view_offset, should_return_offset) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVectorView<float> v(a, 3, 1);
    constexpr int expected = 1;
    // act
    const int offset = v.offset();
    // assert
    ASSERT_TRUE((compare<int, int>(offset, expected)));
}
#pragma endregion
#pragma region owner
TEST(dense_vector_view_owner, should_return_owner) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVectorView<float> v(a, 3, 1);
    // act
    const DenseVector<float>& owner = v.owner();
    // assert
    ASSERT_TRUE(&owner == &a);
}
#pragma endregion
#pragma endregion
#pragma region custom_dense_vector
#pragma region constructor
TEST(custom_dense_vector_constructor, given_f_pointer_and_size_should_construct) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    const DenseVector<float> expected = {1, 2, 3};
    // act
    const CustomDenseVector<float> v(data, 3, 1);
    // assert
    ASSERT_TRUE((compare<CustomDenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_constructor, given_f_pointer_and_size_and_stride_should_construct_1) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    const DenseVector<float> expected = {1, 1, 1};
    // act
    const CustomDenseVector<float> v(data, 3, 0);
    // assert
    ASSERT_TRUE((compare<CustomDenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_constructor, given_f_pointer_and_size_and_stride_should_construct_2) {
    // arrange
    float* data = new float[6];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    data[5] = 6;
    const DenseVector<float> expected = {1, 3, 5};
    // act
    const CustomDenseVector<float> v(data, 3, 2);
    // assert
    ASSERT_TRUE((compare<CustomDenseVector<float>, DenseVector<float>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_constructor, given_cf_pointer_and_size_should_construct) {
    // arrange
    std::complex<float>* data = new std::complex<float>[3];
    data[0] = {1, 2};
    data[1] = {3, 4};
    data[2] = {5, 6};
    const DenseVector<std::complex<float>> expected = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const CustomDenseVector<std::complex<float>> v(data, 3, 1);
    // assert
    ASSERT_TRUE((compare<CustomDenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_constructor, given_cf_pointer_and_size_and_stride_should_construct_1) {
    // arrange
    std::complex<float>* data = new std::complex<float>[3];
    data[0] = {1, 2};
    data[1] = {3, 4};
    data[2] = {5, 6};
    const DenseVector<std::complex<float>> expected = {{1, 2}, {1, 2}, {1, 2}};
    // act
    const CustomDenseVector<std::complex<float>> v(data, 3, 0);
    // assert
    ASSERT_TRUE((compare<CustomDenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_constructor, given_cf_pointer_and_size_and_stride_should_construct_2) {
    // arrange
    std::complex<float>* data = new std::complex<float>[6];
    data[0] = {1, 2};
    data[1] = {3, 4};
    data[2] = {5, 6};
    data[3] = {7, 8};
    data[4] = {9, 10};
    data[5] = {11, 12};
    const DenseVector<std::complex<float>> expected = {{1, 2}, {5, 6}, {9, 10}};
    // act
    const CustomDenseVector<std::complex<float>> v(data, 3, 2);
    // assert
    ASSERT_TRUE((compare<CustomDenseVector<std::complex<float>>, DenseVector<std::complex<float>>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}
#pragma endregion
#pragma region index_operator
TEST(custom_dense_vector_index_operator, given_index_should_return_reference_f) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    CustomDenseVector<float> v(data, 3, 1);
    // act
    float& v0 = v[0];
    float& v1 = v[1];
    float& v2 = v[2];
    // assert
    ASSERT_TRUE((compare<float, float>(v0, 1, 0.001f)));
    v0 = 4;
    ASSERT_TRUE((compare<float, float>(v0, 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v1, 2, 0.001f)));
    v1 = 5;
    ASSERT_TRUE((compare<float, float>(v1, 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v2, 3, 0.001f)));
    v2 = 6;
    ASSERT_TRUE((compare<float, float>(v2, 6, 0.001f)));
}

TEST(custom_dense_vector_index_operator, given_index_should_return_reference_cf) {
    // arrange
    std::complex<float>* data = new std::complex<float>[3];
    data[0] = {1, 2};
    data[1] = {3, 4};
    data[2] = {5, 6};
    CustomDenseVector<std::complex<float>> v(data, 3, 1);
    // act
    std::complex<float>& v0 = v[0];
    std::complex<float>& v1 = v[1];
    std::complex<float>& v2 = v[2];
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v0, {1, 2}, 0.001f)));
    v0 = {7, 8};
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v0, {7, 8}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v1, {3, 4}, 0.001f)));
    v1 = {9, 10};
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v1, {9, 10}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v2, {5, 6}, 0.001f)));
    v2 = {11, 12};
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v2, {11, 12}, 0.001f)));
}

TEST(custom_dense_vector_index_operator, given_big_index_should_throw_1) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}

TEST(custom_dense_vector_index_operator, given_big_index_should_throw_2) {
    // arrange
    float* data = new float[5];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}

TEST(custom_dense_vector_index_operator, given_negative_index_should_throw_2) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
}
#pragma endregion
#pragma region const_index_operator
TEST(custom_dense_vector_const_index_operator, given_index_should_return_const_reference_f) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    const CustomDenseVector<float> v(data, 3, 1);
    // act
    const float& v0 = v[0];
    const float& v1 = v[1];
    const float& v2 = v[2];
    // assert
    ASSERT_TRUE((compare<float, float>(v0, 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v1, 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v2, 3, 0.001f)));
}

TEST(custom_dense_vector_const_index_operator, given_index_should_return_const_reference_cf) {
    // arrange
    std::complex<float>* data = new std::complex<float>[3];
    data[0] = {1, 2};
    data[1] = {3, 4};
    data[2] = {5, 6};
    const CustomDenseVector<std::complex<float>> v(data, 3, 1);
    // act
    const std::complex<float>& v0 = v[0];
    const std::complex<float>& v1 = v[1];
    const std::complex<float>& v2 = v[2];
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v0, {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v1, {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v2, {5, 6}, 0.001f)));
}

TEST(custom_dense_vector_const_index_operator, given_big_index_should_throw_1) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    const CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}

TEST(custom_dense_vector_const_index_operator, given_big_index_should_throw_2) {
    // arrange
    float* data = new float[5];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    const CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}

TEST(custom_dense_vector_const_index_operator, given_negative_index_should_throw_2) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    const CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
}
#pragma endregion
#pragma region stride
TEST(custom_dense_vector_stride, should_return_stride) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    const CustomDenseVector<float> v(data, 3, 1);
    // act
    const int stride = v.stride();
    // assert
    ASSERT_TRUE((compare<int, int>(stride, 1)));
}
#pragma endregion
#pragma region data
TEST(custom_dense_vector_data, should_return_data) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    CustomDenseVector<float> v(data, 3, 1);
    // act
    float* vectorData = v.data();
    // assert
    ASSERT_TRUE(data == vectorData);
}
#pragma endregion
#pragma region const_data
TEST(custom_dense_vector_const_data, should_return_const_data) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    const CustomDenseVector<float> v(data, 3, 1);
    // act
    const float* vectorData = v.data();
    // assert
    ASSERT_TRUE(data == vectorData);
}
#pragma endregion
#pragma endregion
