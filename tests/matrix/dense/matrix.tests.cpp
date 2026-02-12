#include "gtest/gtest.h"

#include "mathpp/math.h"

#pragma region dense_matrix
#pragma region indexing_operator
TEST(dense_matrix_indexing_operator, given_index_should_return_reference_f) {
    // arrange
    DenseMatrix<float> v(3, 3, false);
    // act
    float& v00 = v[0, 0];
    v00 = 1;
    float& v10 = v[1, 0];
    v10 = 2;
    float& v20 = v[2, 0];
    v20 = 3;
    float& v01 = v[0, 1];
    v01 = 4;
    float& v11 = v[1, 1];
    v11 = 5;
    float& v21 = v[2, 1];
    v21 = 6;
    float& v02 = v[0, 2];
    v02 = 7;
    float& v12 = v[1, 2];
    v12 = 8;
    float& v22 = v[2, 2];
    v22 = 9;
    // assert
    ASSERT_TRUE((compare<float, float>(v00, 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v10, 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v20, 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v01, 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v11, 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v21, 6, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v02, 7, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v12, 8, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v22, 9, 0.001f)));
}

TEST(dense_matrix_indexing_operator, given_index_should_return_reference_cf) {
    // arrange
    DenseMatrix<std::complex<float>> v(3, 3, false);
    // act
    std::complex<float>& v00 = v[0, 0];
    v00 = {1, 2};
    std::complex<float>& v10 = v[1, 0];
    v10 = {3, 4};
    std::complex<float>& v20 = v[2, 0];
    v20 = {5, 6};
    std::complex<float>& v01 = v[0, 1];
    v01 = {7, 8};
    std::complex<float>& v11 = v[1, 1];
    v11 = {9, 10};
    std::complex<float>& v21 = v[2, 1];
    v21 = {11, 12};
    std::complex<float>& v02 = v[0, 2];
    v02 = {13, 14};
    std::complex<float>& v12 = v[1, 2];
    v12 = {15, 16};
    std::complex<float>& v22 = v[2, 2];
    v22 = {17, 18};
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v00, {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v10, {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v20, {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v01, {7, 8}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v11, {9, 10}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v21, {11, 12}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v02, {13, 14}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v12, {15, 16}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v22, {17, 18}, 0.001f)));
}

TEST(dense_matrix_indexing_operator, given_negative_index_should_throw_1) {
    // arrange
    DenseMatrix<float> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act / assert
    ASSERT_THROW((std::ignore = v[-1, 0]), InvalidIndexException);
}

TEST(dense_matrix_indexing_operator, given_negative_index_should_throw_2) {
    // arrange
    DenseMatrix<float> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act / assert
    ASSERT_THROW((std::ignore = v[0, -1]), InvalidIndexException);
}

TEST(dense_matrix_indexing_operator, given_big_index_should_throw_1) {
    // arrange
    DenseMatrix<float> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act / assert
    ASSERT_THROW((std::ignore = v[4, 0]), InvalidIndexException);
}

TEST(dense_matrix_indexing_operator, given_big_index_should_throw_2) {
    // arrange
    DenseMatrix<float> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 4]), InvalidIndexException);
}
#pragma endregion
#pragma region const_indexing_operator
TEST(dense_matrix_const_indexing_operator, given_index_should_return_const_reference_f) {
    // arrange
    const DenseMatrix<float> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act / assert
    ASSERT_TRUE((compare<float, float>(v[0, 0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[1, 0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[2, 0], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[0, 1], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[1, 1], 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[2, 1], 6, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[0, 2], 7, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[1, 2], 8, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[2, 2], 9, 0.001f)));
}

TEST(dense_matrix_const_indexing_operator, given_index_should_return_const_reference_cf) {
    // arrange
    const DenseMatrix<std::complex<float>> v = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act / assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[0, 0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[1, 0], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[2, 0], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[0, 1], {7, 8}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[1, 1], {9, 10}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[2, 1], {11, 12}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[0, 2], {13, 14}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[1, 2], {15, 16}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[2, 2], {17, 18}, 0.001f)));
}

TEST(dense_matrix_const_indexing_operator, given_negative_index_should_throw_1) {
    // arrange
    const DenseMatrix<float> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act / assert
    ASSERT_THROW((std::ignore = v[-1, 0]), InvalidIndexException);
}

TEST(dense_matrix_const_indexing_operator, given_negative_index_should_throw_2) {
    // arrange
    const DenseMatrix<float> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act / assert
    ASSERT_THROW((std::ignore = v[0, -1]), InvalidIndexException);
}

TEST(dense_matrix_const_indexing_operator, given_big_index_should_throw_1) {
    // arrange
    const DenseMatrix<float> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act / assert
    ASSERT_THROW((std::ignore = v[4, 0]), InvalidIndexException);
}

TEST(dense_matrix_const_indexing_operator, given_big_index_should_throw_2) {
    // arrange
    const DenseMatrix<float> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 4]), InvalidIndexException);
}
#pragma endregion
#pragma region default_constructor
TEST(dense_matrix_default_constructor, given_size_and_fill_should_construct_f) {
    // arrange / act
    const DenseMatrix<float> v(3, 3, true);
    const DenseMatrix<float> expected = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    // assert
    ASSERT_TRUE((compare<DenseMatrix<float>, DenseMatrix<float>>(v, expected, 0.001f)));
}

TEST(dense_matrix_default_constructor, given_size_and_fill_should_construct_cf) {
    // arrange / act
    const DenseMatrix<std::complex<float>> v(3, 3, true);
    const DenseMatrix<std::complex<float>> expected = {{{0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}}};
    // assert
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region initializer_list_constructor
TEST(dense_matrix_initializer_list_constructor, given_initializer_list_should_construct_f) {
    // arrange / act
    const DenseMatrix<float> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> expected(3, 3, false);
    expected[0, 0] = 1;
    expected[1, 0] = 2;
    expected[2, 0] = 3;
    expected[0, 1] = 4;
    expected[1, 1] = 5;
    expected[2, 1] = 6;
    expected[0, 2] = 7;
    expected[1, 2] = 8;
    expected[2, 2] = 9;
    // assert
    ASSERT_TRUE((compare<DenseMatrix<float>, DenseMatrix<float>>(v, expected, 0.001f)));
}

TEST(dense_matrix_initializer_list_constructor, given_initializer_list_should_construct_cf) {
    // arrange / act
    const DenseMatrix<std::complex<float>> v = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    DenseMatrix<std::complex<float>> expected(3, 3, false);
    expected[0, 0] = {1, 2};
    expected[1, 0] = {3, 4};
    expected[2, 0] = {5, 6};
    expected[0, 1] = {7, 8};
    expected[1, 1] = {9, 10};
    expected[2, 1] = {11, 12};
    expected[0, 2] = {13, 14};
    expected[1, 2] = {15, 16};
    expected[2, 2] = {17, 18};
    // assert
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<std::complex<float>>>(v, expected, 0.001f)));
}

TEST(dense_matrix_initializer_list_constructor, given_initializer_list_with_different_sized_rows_should_throw) {
    // arrange / act / assert
    ASSERT_THROW(((std::ignore = DenseMatrix<float>{{1, 2, 3}, {4, 5}, {6, 7, 8}})), InvalidDimensionException);
}
#pragma endregion
#pragma region copy_constructor_from_same_type_dense_matrix
TEST(dense_matrix_copy_constructor_from_same_type_dense_matrix, given_f_dense_matrix_should_copy_construct) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<float> v = expected;
    // assert
    ASSERT_TRUE((compare<DenseMatrix<float>, DenseMatrix<float>>(v, expected, 0.001f)));
}

TEST(dense_matrix_copy_constructor_from_same_type_dense_matrix, given_cf_dense_matrix_should_copy_construct) {
    // arrange
    const DenseMatrix<std::complex<float>> expected = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const DenseMatrix<std::complex<float>> v = expected;
    // assert
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_dense_matrix
TEST(dense_matrix_copy_constructor_from_different_type_dense_matrix, given_f_dense_matrix_should_copy_construct) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<std::complex<float>> v = expected;
    // assert
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<float>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_constructor_from_same_type_dense_matrix_base
TEST(dense_matrix_copy_constructor_from_same_type_dense_matrix_base, given_f_dense_matrix_base_should_copy_construct) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<float> v = static_cast<const DenseMatrixBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseMatrix<float>, DenseMatrix<float>>(v, expected, 0.001f)));
}

TEST(dense_matrix_copy_constructor_from_same_type_dense_matrix_base, given_cf_dense_matrix_base_should_copy_construct) {
    // arrange
    const DenseMatrix<std::complex<float>> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<std::complex<float>> v = static_cast<const DenseMatrixBase<std::complex<float>>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_dense_matrix_base
TEST(dense_matrix_copy_constructor_from_different_type_dense_matrix_base, given_f_dense_matrix_base_should_copy_construct) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<std::complex<float>> v = static_cast<const DenseMatrixBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<float>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region move_constructor
TEST(dense_matrix_move_constructor, given_f_dense_matrix_should_move_construct_and_invalidate_other_data) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<float> v = std::move(a);
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare<DenseMatrix<float>, DenseMatrix<float>>(v, expected, 0.001f)));
}

TEST(dense_matrix_move_constructor, given_cf_dense_matrix_should_move_construct_and_invalidate_other_data) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> expected = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const DenseMatrix<std::complex<float>> v = std::move(a);
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<std::complex<float>>>(v, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_dense_matrix
TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_f_dense_matrix_should_copy_assign) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> v(3, 3, true);
    // act
    v = expected;
    // assert
    ASSERT_TRUE((compare<DenseMatrix<float>, DenseMatrix<float>>(v, expected, 0.001f)));
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_cf_dense_matrix_should_copy_assign) {
    // arrange
    const DenseMatrix<std::complex<float>> expected = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    DenseMatrix<std::complex<float>> v(3, 3, true);
    // act
    v = expected;
    // assert
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<std::complex<float>>>(v, expected, 0.001f)));
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_dense_matrix_of_different_size_should_throw_1) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> v(2, 3, true);
    // act / assert
    ASSERT_THROW(v = expected, InvalidDimensionException);
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_dense_matrix_of_different_size_should_throw_2) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> v(3, 2, true);
    // act / assert
    ASSERT_THROW(v = expected, InvalidDimensionException);
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_dense_matrix
TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix, given_f_dense_matrix_should_copy_assign) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> v(3, 3, true);
    // act
    v = expected;
    // assert
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<float>>(v, expected, 0.001f)));
}

TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix, given_f_dense_matrix_of_different_size_should_throw_1) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> v(2, 3, true);
    // act / assert
    ASSERT_THROW(v = expected, InvalidDimensionException);
}

TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix, given_f_dense_matrix_of_different_size_should_throw_2) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> v(3, 2, true);
    // act / assert
    ASSERT_THROW(v = expected, InvalidDimensionException);
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_dense_matrix_base
TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix_base, given_f_dense_matrix_base_should_copy_assign) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> v(3, 3, true);
    // act
    v = static_cast<const DenseMatrixBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseMatrix<float>, DenseMatrix<float>>(v, expected, 0.001f)));
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix_base, given_cf_dense_matrix_base_should_copy_assign) {
    // arrange
    const DenseMatrix<std::complex<float>> expected = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    DenseMatrix<std::complex<float>> v(3, 3, true);
    // act
    v = static_cast<const DenseMatrixBase<std::complex<float>>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<std::complex<float>>>(v, expected, 0.001f)));
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix_base, given_dense_vector_base_of_different_size_should_throw_1) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> v(2, 3, true);
    // act / assert
    ASSERT_THROW(v = static_cast<const DenseMatrixBase<float>&>(expected), InvalidDimensionException);
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix_base, given_dense_vector_base_of_different_size_should_throw_2) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> v(3, 2, true);
    // act / assert
    ASSERT_THROW(v = static_cast<const DenseMatrixBase<float>&>(expected), InvalidDimensionException);
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_base
TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix_base, given_f_dense_matrix_base_should_copy_assign) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> v(3, 3, true);
    // act
    v = static_cast<const DenseMatrixBase<float>&>(expected);
    // assert
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<float>>(v, expected, 0.001f)));
}

TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix_base, given_dense_vector_base_of_different_size_should_throw_1) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> v(2, 3, true);
    // act / assert
    ASSERT_THROW(v = static_cast<const DenseMatrixBase<float>&>(expected), InvalidDimensionException);
}

TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix_base, given_dense_vector_base_of_different_size_should_throw_2) {
    // arrange
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> v(3, 2, true);
    // act / assert
    ASSERT_THROW(v = static_cast<const DenseMatrixBase<float>&>(expected), InvalidDimensionException);
}
#pragma endregion
#pragma region move_assignment_operator
TEST(dense_matrix_move_assignment_operator, given_f_dense_matrix_should_move_assign) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> v(3, 3, true);
    // act
    v = std::move(a);
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare<DenseMatrix<float>, DenseMatrix<float>>(v, expected, 0.001f)));
}

TEST(dense_matrix_move_assignment_operator, given_cf_dense_matrix_should_move_assign) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const DenseMatrix<std::complex<float>> expected = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    DenseMatrix<std::complex<float>> v(3, 3, true);
    // act
    v = std::move(a);
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare<DenseMatrix<std::complex<float>>, DenseMatrix<std::complex<float>>>(v, expected, 0.001f)));
}

TEST(dense_matrix_move_assignment_operator, given_dense_matrix_of_different_size_should_throw_1) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> v(2, 3, true);
    // act / assert
    ASSERT_THROW(v = std::move(a), InvalidDimensionException);
}

TEST(dense_matrix_move_assignment_operator, given_dense_matrix_of_different_size_should_throw_2) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> v(3, 2, true);
    // act / assert
    ASSERT_THROW(v = std::move(a), InvalidDimensionException);
}
#pragma endregion
#pragma region data
TEST(dense_matrix_data, should_return_data_pointer_f) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    float* data = a.data();
    // assert
    ASSERT_TRUE((compare<float, float>(data[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[1], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[2], 7, 0.001f)));

    ASSERT_TRUE((compare<float, float>(data[3], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[4], 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[5], 8, 0.001f)));

    ASSERT_TRUE((compare<float, float>(data[6], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[7], 6, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[8], 9, 0.001f)));
}

TEST(dense_matrix_data, should_return_data_pointer_cf) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    std::complex<float>* data = a.data();
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[1], {7, 8}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[2], {13, 14}, 0.001f)));

    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[3], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[4], {9, 10}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[5], {15, 16}, 0.001f)));

    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[6], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[7], {11, 12}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[8], {17, 18}, 0.001f)));
}
#pragma endregion
#pragma region const_data
TEST(dense_matrix_const_data, should_return_const_data_pointer_f) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const float* data = a.data();
    // assert
    ASSERT_TRUE((compare<float, float>(data[0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[1], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[2], 7, 0.001f)));

    ASSERT_TRUE((compare<float, float>(data[3], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[4], 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[5], 8, 0.001f)));

    ASSERT_TRUE((compare<float, float>(data[6], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[7], 6, 0.001f)));
    ASSERT_TRUE((compare<float, float>(data[8], 9, 0.001f)));
}

TEST(dense_matrix_const_data, should_return_const_data_pointer_cf) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const std::complex<float>* data = a.data();
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[1], {7, 8}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[2], {13, 14}, 0.001f)));

    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[3], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[4], {9, 10}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[5], {15, 16}, 0.001f)));

    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[6], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[7], {11, 12}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(data[8], {17, 18}, 0.001f)));
}
#pragma endregion
#pragma endregion
#pragma region dense_matrix_view
#pragma region constructor
TEST(dense_matrix_view_constructor, given_f_dense_matrix_should_construct) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrix<float> expected = {{7, 8, 9}, {12, 13, 14}, {17, 18, 19}};
    // act
    const DenseMatrixView<float> view = DenseMatrixView<float>(a, 3, 3, 1, 1);
    // assert
    ASSERT_TRUE((compare<DenseMatrixView<float>, DenseMatrix<float>>(view, expected, 0.001f)));
}

TEST(dense_matrix_view_constructor, given_cf_dense_matrix_should_construct) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}}, {{11, 12}, {13, 14}, {15, 16}, {17, 18}, {19, 20}}, {{21, 22}, {23, 24}, {25, 26}, {27, 28}, {29, 30}}, {{31, 32}, {33, 34}, {35, 36}, {37, 38}, {39, 40}}, {{41, 42}, {43, 44}, {45, 46}, {47, 48}, {49, 50}}};
    const DenseMatrix<std::complex<float>> expected = {{{13, 14}, {15, 16}, {17, 18}}, {{23, 24}, {25, 26}, {27, 28}}, {{33, 34}, {35, 36}, {37, 38}}};
    // act
    const DenseMatrixView<std::complex<float>> view = DenseMatrixView<std::complex<float>>(a, 3, 3, 1, 1);
    // assert
    ASSERT_TRUE((compare<DenseMatrixView<std::complex<float>>, DenseMatrix<std::complex<float>>>(view, expected, 0.001f)));
}
#pragma endregion
#pragma region copy_constructor
TEST(dense_matrix_view_copy_constructor, given_f_dense_matrix_view_should_copy) {
    // arrange
    const DenseMatrix<float> v = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrixView<float> view(v, 3, 3, 2, 2);
    // act
    const DenseMatrixView<float> newView = view;
    // assert
    ASSERT_TRUE(&view.owner() == &newView.owner());
    ASSERT_TRUE((compare<DenseMatrixView<float>, DenseMatrixView<float>>(view, newView, 0.001f)));
}

TEST(dense_matrix_view_copy_constructor, given_cf_dense_matrix_view_should_copy) {
    // arrange
    const DenseMatrix<std::complex<float>> v = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}}, {{11, 12}, {13, 14}, {15, 16}, {17, 18}, {19, 20}}, {{21, 22}, {23, 24}, {25, 26}, {27, 28}, {29, 30}}, {{31, 32}, {33, 34}, {35, 36}, {37, 38}, {39, 40}}, {{41, 42}, {43, 44}, {45, 46}, {47, 48}, {49, 50}}};
    const DenseMatrixView<std::complex<float>> view(v, 3, 3, 2, 2);
    // act
    const DenseMatrixView<std::complex<float>> newView = view;
    // assert
    ASSERT_TRUE(&view.owner() == &newView.owner());
    ASSERT_TRUE((compare<DenseMatrixView<std::complex<float>>, DenseMatrixView<std::complex<float>>>(view, newView, 0.001f)));
}
#pragma endregion
#pragma region indexing_operator
TEST(dense_matrix_view_indexing_operator, given_index_should_throw) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    DenseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 0]), InvalidOperationException);
}

TEST(dense_matrix_view_indexing_operator, given_negative_index_should_throw_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    DenseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW((std::ignore = v[-1, 0]), InvalidIndexException);
}

TEST(dense_matrix_view_indexing_operator, given_negative_index_should_throw_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    DenseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, -1]), InvalidIndexException);
}

TEST(dense_matrix_view_indexing_operator, given_big_index_should_throw_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    DenseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(dense_matrix_view_indexing_operator, given_big_index_should_throw_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    DenseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}

TEST(dense_matrix_view_indexing_operator, given_big_index_should_throw_3) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    DenseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(dense_matrix_view_indexing_operator, given_big_index_should_throw_4) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    DenseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}
#pragma endregion
#pragma region const_indexing_operator
TEST(dense_matrix_view_const_indexing_operator, given_index_should_return_const_reference_f) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_TRUE((compare<float, float>(v[0, 0], 13, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[1, 0], 14, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[2, 0], 15, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[0, 1], 18, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[1, 1], 19, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[2, 1], 20, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[0, 2], 23, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[1, 2], 24, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[2, 2], 25, 0.001f)));
}

TEST(dense_matrix_view_const_indexing_operator, given_index_should_return_const_reference_cf) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}}, {{11, 12}, {13, 14}, {15, 16}, {17, 18}, {19, 20}}, {{21, 22}, {23, 24}, {25, 26}, {27, 28}, {29, 30}}, {{31, 32}, {33, 34}, {35, 36}, {37, 38}, {39, 40}}, {{41, 42}, {43, 44}, {45, 46}, {47, 48}, {49, 50}}};
    const DenseMatrixView<std::complex<float>> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[0, 0], {25, 26}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[1, 0], {27, 28}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[2, 0], {29, 30}, 0.001f)));

    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[0, 1], {35, 36}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[1, 1], {37, 38}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[2, 1], {39, 40}, 0.001f)));

    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[0, 2], {45, 46}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[1, 2], {47, 48}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[2, 2], {49, 50}, 0.001f)));
}

TEST(dense_matrix_view_const_indexing_operator, given_negative_index_should_throw_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW((std::ignore = v[-1, 0]), InvalidIndexException);
}

TEST(dense_matrix_view_const_indexing_operator, given_negative_index_should_throw_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, -1]), InvalidIndexException);
}

TEST(dense_matrix_view_const_indexing_operator, given_big_index_should_throw_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(dense_matrix_view_const_indexing_operator, given_big_index_should_throw_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrixView<float> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}

TEST(dense_matrix_view_const_indexing_operator, given_big_index_should_throw_3) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(dense_matrix_view_const_indexing_operator, given_big_index_should_throw_4) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrixView<float> v(a, 3, 3, 1, 1);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}
#pragma endregion
#pragma region col_offset
TEST(dense_matrix_view_col_offset, should_return_col_offset) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrixView<float> v(a, 3, 3, 1, 2);
    constexpr int expected = 1;
    // act
    const int colOffset = v.colOffset();
    // assert
    ASSERT_TRUE((compare<int, int>(colOffset, expected)));
}
#pragma endregion
#pragma region row_offset
TEST(dense_matrix_view_row_offset, should_return_row_offset) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrixView<float> v(a, 3, 3, 1, 2);
    constexpr int expected = 2;
    // act
    const int rowOffset = v.rowOffset();
    // assert
    ASSERT_TRUE((compare<int, int>(rowOffset, expected)));
}
#pragma endregion
#pragma region owner
TEST(dense_matrix_view_owner, should_return_owner) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    const DenseMatrixView<float> v(a, 3, 3, 1, 1);
    // act
    const DenseMatrix<float>& owner = v.owner();
    // assert
    ASSERT_TRUE(&owner == &a);
}
#pragma endregion
#pragma endregion
#pragma region custom_dense_matrix
#pragma region constructor
TEST(custom_dense_matrix_constructor, given_f_pointer_and_size_should_construct) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    const DenseMatrix<float> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // assert
    ASSERT_TRUE((compare<CustomDenseMatrix<float>, DenseMatrix<float>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_matrix_constructor, given_f_pointer_and_size_and_stride_should_construct_1) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    const DenseMatrix<float> expected = {{1, 1, 1}, {4, 4, 4}, {7, 7, 7}};
    // act
    const CustomDenseMatrix<float> v(data, 3, 3, 0);
    // assert
    ASSERT_TRUE((compare<CustomDenseMatrix<float>, DenseMatrix<float>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_matrix_constructor, given_f_pointer_and_size_and_stride_should_construct_2) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    const DenseMatrix<float> expected = {{1, 7}, {4, 2}};
    // act
    const CustomDenseMatrix<float> v(data, 2, 2, 2);
    // assert
    ASSERT_TRUE((compare<CustomDenseMatrix<float>, DenseMatrix<float>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_matrix_constructor, given_cf_pointer_and_size_should_construct) {
    // arrange
    std::complex<float>* data = new std::complex<float>[9];
    data[0] = {1, 2};
    data[1] = {7, 8};
    data[2] = {13, 14};
    data[3] = {3, 4};
    data[4] = {9, 10};
    data[5] = {15, 16};
    data[6] = {5, 6};
    data[7] = {11, 12};
    data[8] = {17, 18};
    const DenseMatrix<std::complex<float>> expected = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const CustomDenseMatrix<std::complex<float>> v(data, 3, 3, 3);
    // assert
    ASSERT_TRUE((compare<CustomDenseMatrix<std::complex<float>>, DenseMatrix<std::complex<float>>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_matrix_constructor, given_cf_pointer_and_size_and_stride_should_construct_1) {
    // arrange
    std::complex<float>* data = new std::complex<float>[9];
    data[0] = {1, 2};
    data[1] = {7, 8};
    data[2] = {13, 14};
    data[3] = {3, 4};
    data[4] = {9, 10};
    data[5] = {15, 16};
    data[6] = {5, 6};
    data[7] = {11, 12};
    data[8] = {17, 18};
    const DenseMatrix<std::complex<float>> expected = {{{1, 2}, {1, 2}, {1, 2}}, {{7, 8}, {7, 8}, {7, 8}}, {{13, 14}, {13, 14}, {13, 14}}};
    // act
    const CustomDenseMatrix<std::complex<float>> v(data, 3, 3, 0);
    // assert
    ASSERT_TRUE((compare<CustomDenseMatrix<std::complex<float>>, DenseMatrix<std::complex<float>>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_matrix_constructor, given_cf_pointer_and_size_and_stride_should_construct_2) {
    // arrange
    std::complex<float>* data = new std::complex<float>[9];
    data[0] = {1, 2};
    data[1] = {7, 8};
    data[2] = {13, 14};
    data[3] = {3, 4};
    data[4] = {9, 10};
    data[5] = {15, 16};
    data[6] = {5, 6};
    data[7] = {11, 12};
    data[8] = {17, 18};
    const DenseMatrix<std::complex<float>> expected = {{{1, 2}, {13, 14}}, {{7, 8}, {3, 4}}};
    // act
    const CustomDenseMatrix<std::complex<float>> v(data, 2, 2, 2);
    // assert
    ASSERT_TRUE((compare<CustomDenseMatrix<std::complex<float>>, DenseMatrix<std::complex<float>>>(v, expected, 0.001f)));
    // cleanup
    delete[] data;
}

#pragma endregion
#pragma region index_operator
TEST(custom_dense_matrix_index_operator, given_index_should_return_reference_f) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act
    float& v00 = v[0, 0];
    v00 = 1;
    float& v10 = v[1, 0];
    v10 = 2;
    float& v20 = v[2, 0];
    v20 = 3;
    float& v01 = v[0, 1];
    v01 = 4;
    float& v11 = v[1, 1];
    v11 = 5;
    float& v21 = v[2, 1];
    v21 = 6;
    float& v02 = v[0, 2];
    v02 = 7;
    float& v12 = v[1, 2];
    v12 = 8;
    float& v22 = v[2, 2];
    v22 = 9;
    // assert
    ASSERT_TRUE((compare<float, float>(v00, 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v10, 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v20, 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v01, 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v11, 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v21, 6, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v02, 7, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v12, 8, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v22, 9, 0.001f)));
}

TEST(custom_dense_matrix_index_operator, given_index_should_return_reference_cf) {
    // arrange
    std::complex<float>* data = new std::complex<float>[9];
    data[0] = {1, 2};
    data[1] = {7, 8};
    data[2] = {13, 14};
    data[3] = {3, 4};
    data[4] = {9, 10};
    data[5] = {15, 16};
    data[6] = {5, 6};
    data[7] = {11, 12};
    data[8] = {17, 18};
    CustomDenseMatrix<std::complex<float>> v(data, 3, 3, 3);
    // act
    std::complex<float>& v00 = v[0, 0];
    v00 = {1, 2};
    std::complex<float>& v10 = v[1, 0];
    v10 = {3, 4};
    std::complex<float>& v20 = v[2, 0];
    v20 = {5, 6};
    std::complex<float>& v01 = v[0, 1];
    v01 = {7, 8};
    std::complex<float>& v11 = v[1, 1];
    v11 = {9, 10};
    std::complex<float>& v21 = v[2, 1];
    v21 = {11, 12};
    std::complex<float>& v02 = v[0, 2];
    v02 = {13, 14};
    std::complex<float>& v12 = v[1, 2];
    v12 = {15, 16};
    std::complex<float>& v22 = v[2, 2];
    v22 = {17, 18};
    // assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v00, {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v10, {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v20, {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v01, {7, 8}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v11, {9, 10}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v21, {11, 12}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v02, {13, 14}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v12, {15, 16}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v22, {17, 18}, 0.001f)));
}

TEST(custom_dense_matrix_index_operator, given_big_index_should_throw_1) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_index_operator, given_big_index_should_throw_2) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}

TEST(custom_dense_matrix_index_operator, given_big_index_should_throw_3) {
    // arrange
    float* data = new float[25];
    data[0] = 1;
    data[1] = 6;
    data[2] = 11;
    data[3] = 16;
    data[4] = 21;
    data[5] = 2;
    data[6] = 7;
    data[7] = 12;
    data[8] = 17;
    data[9] = 22;
    data[10] = 3;
    data[11] = 8;
    data[12] = 13;
    data[13] = 18;
    data[14] = 23;
    data[15] = 4;
    data[16] = 9;
    data[17] = 14;
    data[18] = 19;
    data[19] = 24;
    data[20] = 5;
    data[21] = 10;
    data[22] = 15;
    data[23] = 20;
    data[24] = 25;
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_index_operator, given_big_index_should_throw_4) {
    // arrange
    float* data = new float[25];
    data[0] = 1;
    data[1] = 6;
    data[2] = 11;
    data[3] = 16;
    data[4] = 21;
    data[5] = 2;
    data[6] = 7;
    data[7] = 12;
    data[8] = 17;
    data[9] = 22;
    data[10] = 3;
    data[11] = 8;
    data[12] = 13;
    data[13] = 18;
    data[14] = 23;
    data[15] = 4;
    data[16] = 9;
    data[17] = 14;
    data[18] = 19;
    data[19] = 24;
    data[20] = 5;
    data[21] = 10;
    data[22] = 15;
    data[23] = 20;
    data[24] = 25;
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}

TEST(custom_dense_matrix_index_operator, given_negative_index_should_throw_1) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[-1, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_index_operator, given_negative_index_should_throw_2) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, -1]), InvalidIndexException);
}
#pragma endregion
#pragma region const_index_operator
TEST(custom_dense_matrix_const_index_operator, given_index_should_return_reference_f) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_TRUE((compare<float, float>(v[0, 0], 1, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[1, 0], 2, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[2, 0], 3, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[0, 1], 4, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[1, 1], 5, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[2, 1], 6, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[0, 2], 7, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[1, 2], 8, 0.001f)));
    ASSERT_TRUE((compare<float, float>(v[2, 2], 9, 0.001f)));

}

TEST(custom_dense_matrix_const_index_operator, given_index_should_return_reference_cf) {
    // arrange
    std::complex<float>* data = new std::complex<float>[9];
    data[0] = {1, 2};
    data[1] = {7, 8};
    data[2] = {13, 14};
    data[3] = {3, 4};
    data[4] = {9, 10};
    data[5] = {15, 16};
    data[6] = {5, 6};
    data[7] = {11, 12};
    data[8] = {17, 18};
    const CustomDenseMatrix<std::complex<float>> v(data, 3, 3, 3);
    // act / assert
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[0, 0], {1, 2}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[1, 0], {3, 4}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[2, 0], {5, 6}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[0, 1], {7, 8}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[1, 1], {9, 10}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[2, 1], {11, 12}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[0, 2], {13, 14}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[1, 2], {15, 16}, 0.001f)));
    ASSERT_TRUE((compare<std::complex<float>, std::complex<float>>(v[2, 2], {17, 18}, 0.001f)));
}

TEST(custom_dense_matrix_const_index_operator, given_big_index_should_throw_1) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_const_index_operator, given_big_index_should_throw_2) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}

TEST(custom_dense_matrix_const_index_operator, given_big_index_should_throw_3) {
    // arrange
    float* data = new float[25];
    data[0] = 1;
    data[1] = 6;
    data[2] = 11;
    data[3] = 16;
    data[4] = 21;
    data[5] = 2;
    data[6] = 7;
    data[7] = 12;
    data[8] = 17;
    data[9] = 22;
    data[10] = 3;
    data[11] = 8;
    data[12] = 13;
    data[13] = 18;
    data[14] = 23;
    data[15] = 4;
    data[16] = 9;
    data[17] = 14;
    data[18] = 19;
    data[19] = 24;
    data[20] = 5;
    data[21] = 10;
    data[22] = 15;
    data[23] = 20;
    data[24] = 25;
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_const_index_operator, given_big_index_should_throw_4) {
    // arrange
    float* data = new float[25];
    data[0] = 1;
    data[1] = 6;
    data[2] = 11;
    data[3] = 16;
    data[4] = 21;
    data[5] = 2;
    data[6] = 7;
    data[7] = 12;
    data[8] = 17;
    data[9] = 22;
    data[10] = 3;
    data[11] = 8;
    data[12] = 13;
    data[13] = 18;
    data[14] = 23;
    data[15] = 4;
    data[16] = 9;
    data[17] = 14;
    data[18] = 19;
    data[19] = 24;
    data[20] = 5;
    data[21] = 10;
    data[22] = 15;
    data[23] = 20;
    data[24] = 25;
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}

TEST(custom_dense_matrix_const_index_operator, given_negative_index_should_throw_1) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[-1, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_const_index_operator, given_negative_index_should_throw_2) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, -1]), InvalidIndexException);
}
#pragma endregion
#pragma region stride
TEST(custom_dense_matrix_stride, should_return_stride) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act
    const int stride = v.stride();
    // assert
    ASSERT_TRUE((compare<int, int>(stride, 3)));
}
#pragma endregion
#pragma region data
TEST(custom_dense_matrix_data, should_return_data) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act
    float* matrixData = v.data();
    // assert
    ASSERT_TRUE(data == matrixData);
}
#pragma endregion
#pragma region const_data
TEST(custom_dense_matrix_const_data, should_return_const_data) {
    // arrange
    float* data = new float[9];
    data[0] = 1;
    data[1] = 4;
    data[2] = 7;
    data[3] = 2;
    data[4] = 5;
    data[5] = 8;
    data[6] = 3;
    data[7] = 6;
    data[8] = 9;
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act
    const float* matrixData = v.data();
    // assert
    ASSERT_TRUE(data == matrixData);
}
#pragma endregion
#pragma endregion
