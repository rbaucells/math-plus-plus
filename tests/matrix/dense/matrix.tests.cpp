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
    const float* data = v.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), data[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), data[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), data[2], 7)));

    ASSERT_TRUE((compare(Precision(0.001f), data[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), data[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), data[5], 8)));

    ASSERT_TRUE((compare(Precision(0.001f), data[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), data[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), data[8], 9)));
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
    std::complex<float>* data = v.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), data[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), data[1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), data[2], std::complex<float>(13, 14))));

    ASSERT_TRUE((compare(Precision(0.001f), data[3], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), data[4], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), data[5], std::complex<float>(15, 16))));

    ASSERT_TRUE((compare(Precision(0.001f), data[6], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), data[7], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), data[8], std::complex<float>(17, 18))));
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
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 2], 9)));
}

TEST(dense_matrix_const_indexing_operator, given_index_should_return_const_reference_cf) {
    // arrange
    const DenseMatrix<std::complex<float>> v = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act / assert
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], std::complex<float>(13, 14))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], std::complex<float>(15, 16))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 2], std::complex<float>(17, 18))));
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
    const float* vData = v.data();
    // assert
    ASSERT_TRUE((compare(v.rows(), 3)));
    ASSERT_TRUE((compare(v.columns(), 3)));
    for (int i = 0; i < 8; i++) {
        ASSERT_TRUE((compare(Precision(0.001f), vData[i], 0)));
    }
}

TEST(dense_matrix_default_constructor, given_size_and_fill_should_construct_cf) {
    // arrange / act
    const DenseMatrix<std::complex<float>> v(3, 3, true);
    const std::complex<float>* vData = v.data();
    // assert
    ASSERT_TRUE((compare(v.rows(), 3)));
    ASSERT_TRUE((compare(v.columns(), 3)));
    for (int i = 0; i < 8; i++) {
        ASSERT_TRUE((compare(Precision(0.001f), vData[i], std::complex<float>(0, 0))));
    }
}
#pragma endregion
#pragma region initializer_list_constructor
TEST(dense_matrix_initializer_list_constructor, given_initializer_list_should_construct_f) {
    // arrange / act
    const DenseMatrix<float> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const float* vData = v.data();
    // assert
    ASSERT_TRUE((compare(v.rows(), 3)));
    ASSERT_TRUE((compare(v.columns(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[8], 9)));
}

TEST(dense_matrix_initializer_list_constructor, given_initializer_list_should_construct_cf) {
    // arrange / act
    const DenseMatrix<std::complex<float>> v = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    const std::complex<float>* vData = v.data();
    // assert
    ASSERT_TRUE((compare(v.rows(), 3)));
    ASSERT_TRUE((compare(v.columns(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[2], std::complex<float>(13, 14))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[3], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[4], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[5], std::complex<float>(15, 16))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[6], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[7], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[8], std::complex<float>(17, 18))));
}

TEST(dense_matrix_initializer_list_constructor, given_initializer_list_with_different_sized_rows_should_throw) {
    // arrange / act / assert
    ASSERT_THROW(((std::ignore = DenseMatrix<float>{{1, 2, 3}, {4, 5}, {6, 7, 8}})), InvalidDimensionException);
}
#pragma endregion
#pragma region copy_constructor_from_same_type_dense_matrix
TEST(dense_matrix_copy_constructor_from_same_type_dense_matrix, given_f_dense_matrix_should_copy_construct) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<float> b = a;
    const float* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.rows(), 3)));
    ASSERT_TRUE((compare(b.columns(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], 9)));
}

TEST(dense_matrix_copy_constructor_from_same_type_dense_matrix, given_cf_dense_matrix_should_copy_construct) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const DenseMatrix<std::complex<float>> b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.rows(), 3)));
    ASSERT_TRUE((compare(b.columns(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(13, 14))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], std::complex<float>(15, 16))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], std::complex<float>(17, 18))));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_dense_matrix
TEST(dense_matrix_copy_constructor_from_different_type_dense_matrix, given_f_dense_matrix_should_copy_construct) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<std::complex<float>> b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.rows(), 3)));
    ASSERT_TRUE((compare(b.columns(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], 9)));
}
#pragma endregion
#pragma region copy_constructor_from_same_type_dense_matrix_base
TEST(dense_matrix_copy_constructor_from_same_type_dense_matrix_base, given_f_dense_matrix_base_should_copy_construct) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<float> b = static_cast<const DenseMatrixBase<float>&>(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.rows(), 3)));
    ASSERT_TRUE((compare(b.columns(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], 9)));
}

TEST(dense_matrix_copy_constructor_from_same_type_dense_matrix_base, given_cf_dense_matrix_base_should_copy_construct) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const DenseMatrix<std::complex<float>> b = static_cast<const DenseMatrixBase<std::complex<float>>&>(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.rows(), 3)));
    ASSERT_TRUE((compare(b.columns(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(13, 14))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], std::complex<float>(15, 16))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], std::complex<float>(17, 18))));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_dense_matrix_base
TEST(dense_matrix_copy_constructor_from_different_type_dense_matrix_base, given_f_dense_matrix_base_should_copy_construct) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<std::complex<float>> b = static_cast<const DenseMatrixBase<float>&>(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.rows(), 3)));
    ASSERT_TRUE((compare(b.columns(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], 9)));
}
#pragma endregion
#pragma region move_constructor
TEST(dense_matrix_move_constructor, given_f_dense_matrix_should_move_construct_and_invalidate_other_data) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<float> b = std::move(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare(b.rows(), 3)));
    ASSERT_TRUE((compare(b.columns(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], 9)));
}

TEST(dense_matrix_move_constructor, given_cf_dense_matrix_should_move_construct_and_invalidate_other_data) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const DenseMatrix<std::complex<float>> b = std::move(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare(b.rows(), 3)));
    ASSERT_TRUE((compare(b.columns(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(13, 14))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], std::complex<float>(15, 16))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], std::complex<float>(17, 18))));
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_dense_matrix
TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_f_dense_matrix_should_copy_assign) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(3, 3, true);
    // act
    b = a;
    const float* bData = b.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], 9)));
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_cf_dense_matrix_should_copy_assign) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    DenseMatrix<std::complex<float>> b(3, 3, true);
    // act
    b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(13, 14))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], std::complex<float>(15, 16))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], std::complex<float>(17, 18))));
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_dense_matrix_of_different_size_should_throw_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(2, 3, true);
    // act / assert
    ASSERT_THROW(b = a, InvalidDimensionException);
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_dense_matrix_of_different_size_should_throw_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(3, 2, true);
    // act / assert
    ASSERT_THROW(b = a, InvalidDimensionException);
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_dense_matrix
TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix, given_f_dense_matrix_should_copy_assign) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> b(3, 3, true);
    // act
    b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], 9)));
}

TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix, given_f_dense_matrix_of_different_size_should_throw_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> b(2, 3, true);
    // act / assert
    ASSERT_THROW(b = a, InvalidDimensionException);
}

TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix, given_f_dense_matrix_of_different_size_should_throw_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> b(3, 2, true);
    // act / assert
    ASSERT_THROW(b = a, InvalidDimensionException);
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_dense_matrix_base
TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix_base, given_f_dense_matrix_base_should_copy_assign) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(3, 3, true);
    // act
    b = static_cast<const DenseMatrixBase<float>&>(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], 9)));
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix_base, given_cf_dense_matrix_base_should_copy_assign) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    DenseMatrix<std::complex<float>> b(3, 3, true);
    // act
    b = static_cast<const DenseMatrixBase<std::complex<float>>&>(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(13, 14))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], std::complex<float>(15, 16))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], std::complex<float>(17, 18))));
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix_base, given_dense_vector_base_of_different_size_should_throw_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(2, 3, true);
    // act / assert
    ASSERT_THROW(b = static_cast<const DenseMatrixBase<float>&>(a), InvalidDimensionException);
}

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix_base, given_dense_vector_base_of_different_size_should_throw_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(3, 2, true);
    // act / assert
    ASSERT_THROW(b = static_cast<const DenseMatrixBase<float>&>(a), InvalidDimensionException);
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_base
TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix_base, given_f_dense_matrix_base_should_copy_assign) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> b(3, 3, true);
    // act
    b = static_cast<const DenseMatrixBase<float>&>(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], 9)));
}

TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix_base, given_dense_vector_base_of_different_size_should_throw_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> b(2, 3, true);
    // act / assert
    ASSERT_THROW(b = static_cast<const DenseMatrixBase<float>&>(a), InvalidDimensionException);
}

TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix_base, given_dense_vector_base_of_different_size_should_throw_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> b(3, 2, true);
    // act / assert
    ASSERT_THROW(b = static_cast<const DenseMatrixBase<float>&>(a), InvalidDimensionException);
}
#pragma endregion
#pragma region move_assignment_operator
TEST(dense_matrix_move_assignment_operator, given_f_dense_matrix_should_move_assign) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(3, 3, true);
    // act
    b = std::move(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], 9)));
}

TEST(dense_matrix_move_assignment_operator, given_cf_dense_matrix_should_move_assign) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    DenseMatrix<std::complex<float>> b(3, 3, true);
    // act
    b = std::move(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(13, 14))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[3], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[4], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[5], std::complex<float>(15, 16))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[6], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[7], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[8], std::complex<float>(17, 18))));
}

TEST(dense_matrix_move_assignment_operator, given_dense_matrix_of_different_size_should_throw_1) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(2, 3, true);
    // act / assert
    ASSERT_THROW(b = std::move(a), InvalidDimensionException);
}

TEST(dense_matrix_move_assignment_operator, given_dense_matrix_of_different_size_should_throw_2) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(3, 2, true);
    // act / assert
    ASSERT_THROW(b = std::move(a), InvalidDimensionException);
}
#pragma endregion
#pragma region identity
TEST(dense_matrix_identity, given_3_should_make_identity_matrix_f) {
    // arrange
    const DenseMatrix<float> expected = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    // act
    const DenseMatrix<float> m = DenseMatrix<float>::identity(3);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), m, expected));
}

TEST(dense_matrix_identity, given_3_should_make_identity_matrix_cf) {
    // arrange
    const DenseMatrix<std::complex<float>> expected = {{{1, 0}, {0, 0}, {0, 0}}, {{0, 0}, {1, 0}, {0, 0}}, {{0, 0}, {0, 0}, {1, 0}}};
    // act
    const DenseMatrix<std::complex<float>> m = DenseMatrix<std::complex<float>>::identity(3);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), m, expected));
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
    ASSERT_TRUE((compare(view.rows(), 3)));
    ASSERT_TRUE((compare(view.columns(), 3)));
    ASSERT_TRUE((compare(view.rowOffset(), 1)));
    ASSERT_TRUE((compare(view.colOffset(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), view, expected)));
}

TEST(dense_matrix_view_constructor, given_cf_dense_matrix_should_construct) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}}, {{11, 12}, {13, 14}, {15, 16}, {17, 18}, {19, 20}}, {{21, 22}, {23, 24}, {25, 26}, {27, 28}, {29, 30}}, {{31, 32}, {33, 34}, {35, 36}, {37, 38}, {39, 40}}, {{41, 42}, {43, 44}, {45, 46}, {47, 48}, {49, 50}}};
    const DenseMatrix<std::complex<float>> expected = {{{13, 14}, {15, 16}, {17, 18}}, {{23, 24}, {25, 26}, {27, 28}}, {{33, 34}, {35, 36}, {37, 38}}};
    // act
    const DenseMatrixView<std::complex<float>> view = DenseMatrixView<std::complex<float>>(a, 3, 3, 1, 1);
    // assert
    ASSERT_TRUE((compare(view.rows(), 3)));
    ASSERT_TRUE((compare(view.columns(), 3)));
    ASSERT_TRUE((compare(view.rowOffset(), 1)));
    ASSERT_TRUE((compare(view.colOffset(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), view, expected)));
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
    ASSERT_TRUE((compare(newView.rows(), 3)));
    ASSERT_TRUE((compare(newView.columns(), 3)));
    ASSERT_TRUE((compare(newView.rowOffset(), 2)));
    ASSERT_TRUE((compare(newView.colOffset(), 2)));
    ASSERT_TRUE(&view.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), view, newView)));
}

TEST(dense_matrix_view_copy_constructor, given_cf_dense_matrix_view_should_copy) {
    // arrange
    const DenseMatrix<std::complex<float>> v = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}}, {{11, 12}, {13, 14}, {15, 16}, {17, 18}, {19, 20}}, {{21, 22}, {23, 24}, {25, 26}, {27, 28}, {29, 30}}, {{31, 32}, {33, 34}, {35, 36}, {37, 38}, {39, 40}}, {{41, 42}, {43, 44}, {45, 46}, {47, 48}, {49, 50}}};
    const DenseMatrixView<std::complex<float>> view(v, 3, 3, 2, 2);
    // act
    const DenseMatrixView<std::complex<float>> newView = view;
    // assert
    ASSERT_TRUE((compare(newView.rows(), 3)));
    ASSERT_TRUE((compare(newView.columns(), 3)));
    ASSERT_TRUE((compare(newView.rowOffset(), 2)));
    ASSERT_TRUE((compare(newView.colOffset(), 2)));
    ASSERT_TRUE(&view.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), view, newView)));
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
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 0], 13)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], 14)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], 15)));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], 18)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], 19)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], 20)));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], 23)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], 24)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 2], 25)));
}

TEST(dense_matrix_view_const_indexing_operator, given_index_should_return_const_reference_cf) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}}, {{11, 12}, {13, 14}, {15, 16}, {17, 18}, {19, 20}}, {{21, 22}, {23, 24}, {25, 26}, {27, 28}, {29, 30}}, {{31, 32}, {33, 34}, {35, 36}, {37, 38}, {39, 40}}, {{41, 42}, {43, 44}, {45, 46}, {47, 48}, {49, 50}}};
    const DenseMatrixView<std::complex<float>> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 0], std::complex<float>(25, 26))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], std::complex<float>(27, 28))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], std::complex<float>(29, 30))));

    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], std::complex<float>(35, 36))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], std::complex<float>(37, 38))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], std::complex<float>(39, 40))));

    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], std::complex<float>(45, 46))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], std::complex<float>(47, 48))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 2], std::complex<float>(49, 50))));
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
    ASSERT_TRUE((compare(colOffset, expected)));
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
    ASSERT_TRUE((compare(rowOffset, expected)));
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
    // act
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // assert
    ASSERT_TRUE(data == v.data());
    ASSERT_TRUE((compare(v.rows(), 3)));
    ASSERT_TRUE((compare(v.columns(), 3)));
    ASSERT_TRUE((compare(v.stride(), 3)));
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
    // act
    const CustomDenseMatrix<float> v(data, 3, 3, 0);
    // assert
    ASSERT_TRUE(data == v.data());
    ASSERT_TRUE((compare(v.rows(), 3)));
    ASSERT_TRUE((compare(v.columns(), 3)));
    ASSERT_TRUE((compare(v.stride(), 0)));
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
    // act
    const CustomDenseMatrix<float> v(data, 2, 2, 2);
    // assert
    ASSERT_TRUE(data == v.data());
    ASSERT_TRUE((compare(v.rows(), 2)));
    ASSERT_TRUE((compare(v.columns(), 2)));
    ASSERT_TRUE((compare(v.stride(), 2)));
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
    // act
    const CustomDenseMatrix<std::complex<float>> v(data, 3, 3, 3);
    // assert
    ASSERT_TRUE(data == v.data());
    ASSERT_TRUE((compare(v.rows(), 3)));
    ASSERT_TRUE((compare(v.columns(), 3)));
    ASSERT_TRUE((compare(v.stride(), 3)));
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
    // act
    const CustomDenseMatrix<std::complex<float>> v(data, 3, 3, 0);
    // assert
    ASSERT_TRUE(data == v.data());
    ASSERT_TRUE((compare(v.rows(), 3)));
    ASSERT_TRUE((compare(v.columns(), 3)));
    ASSERT_TRUE((compare(v.stride(), 0)));
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
    // act
    const CustomDenseMatrix<std::complex<float>> v(data, 2, 2, 2);
    // assert
    ASSERT_TRUE(data == v.data());
    ASSERT_TRUE((compare(v.rows(), 2)));
    ASSERT_TRUE((compare(v.columns(), 2)));
    ASSERT_TRUE((compare(v.stride(), 2)));
    // cleanup
    delete[] data;
}

#pragma endregion
#pragma region index_operator
TEST(custom_dense_matrix_index_operator, given_index_should_return_reference_f) {
    // arrange
    float* data = new float[9];
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
    ASSERT_TRUE((compare(Precision(0.001f), data[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), data[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), data[2], 7)));

    ASSERT_TRUE((compare(Precision(0.001f), data[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), data[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), data[5], 8)));

    ASSERT_TRUE((compare(Precision(0.001f), data[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), data[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), data[8], 9)));
}

TEST(custom_dense_matrix_index_operator, given_index_should_return_reference_cf) {
    // arrange
    std::complex<float>* data = new std::complex<float>[9];
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
    ASSERT_TRUE((compare(Precision(0.001f), data[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), data[1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), data[2], std::complex<float>(13, 14))));

    ASSERT_TRUE((compare(Precision(0.001f), data[3], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), data[4], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), data[5], std::complex<float>(15, 16))));

    ASSERT_TRUE((compare(Precision(0.001f), data[6], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), data[7], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), data[8], std::complex<float>(17, 18))));
}

TEST(custom_dense_matrix_index_operator, given_big_index_should_throw_1) {
    // arrange
    float* data = new float[9];
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_index_operator, given_big_index_should_throw_2) {
    // arrange
    float* data = new float[9];
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}

TEST(custom_dense_matrix_index_operator, given_big_index_should_throw_3) {
    // arrange
    float* data = new float[25];
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_index_operator, given_big_index_should_throw_4) {
    // arrange
    float* data = new float[25];
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}

TEST(custom_dense_matrix_index_operator, given_negative_index_should_throw_1) {
    // arrange
    float* data = new float[9];
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[-1, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_index_operator, given_negative_index_should_throw_2) {
    // arrange
    float* data = new float[9];
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
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 2], 9)));
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
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], std::complex<float>(13, 14))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], std::complex<float>(15, 16))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 2], std::complex<float>(17, 18))));
}

TEST(custom_dense_matrix_const_index_operator, given_big_index_should_throw_1) {
    // arrange
    float* data = new float[9];
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_const_index_operator, given_big_index_should_throw_2) {
    // arrange
    float* data = new float[9];
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}

TEST(custom_dense_matrix_const_index_operator, given_big_index_should_throw_3) {
    // arrange
    float* data = new float[25];
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[3, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_const_index_operator, given_big_index_should_throw_4) {
    // arrange
    float* data = new float[25];
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}

TEST(custom_dense_matrix_const_index_operator, given_negative_index_should_throw_1) {
    // arrange
    float* data = new float[9];
    const CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[-1, 0]), InvalidIndexException);
}

TEST(custom_dense_matrix_const_index_operator, given_negative_index_should_throw_2) {
    // arrange
    float* data = new float[9];
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
    ASSERT_TRUE((compare(stride, 3)));
}
#pragma endregion
#pragma endregion
