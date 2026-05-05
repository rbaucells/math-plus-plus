#include "gtest/gtest.h"

#include "mathpp/matrix/dense/operators.h"

#pragma region indexing_operator

TEST(dense_matrix_indexing_operator, given_index_should_return_reference_f) {
    // arrange
    DenseMatrix<float> v(3, 3, false);
    // act
    float& v00 = v[0, 0];
    v00 = 1;
    float& v10 = v[0, 1];
    v10 = 2;
    float& v20 = v[0, 2];
    v20 = 3;
    float& v01 = v[1, 0];
    v01 = 4;
    float& v11 = v[1, 1];
    v11 = 5;
    float& v21 = v[1, 2];
    v21 = 6;
    float& v02 = v[2, 0];
    v02 = 7;
    float& v12 = v[2, 1];
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
    std::complex<float>& v10 = v[0, 1];
    v10 = {3, 4};
    std::complex<float>& v20 = v[0, 2];
    v20 = {5, 6};
    std::complex<float>& v01 = v[1, 0];
    v01 = {7, 8};
    std::complex<float>& v11 = v[1, 1];
    v11 = {9, 10};
    std::complex<float>& v21 = v[1, 2];
    v21 = {11, 12};
    std::complex<float>& v02 = v[2, 0];
    v02 = {13, 14};
    std::complex<float>& v12 = v[2, 1];
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
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 2], 9)));
}

TEST(dense_matrix_const_indexing_operator, given_index_should_return_const_reference_cf) {
    // arrange
    const DenseMatrix<std::complex<float>> v = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act / assert
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], std::complex<float>(13, 14))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], std::complex<float>(15, 16))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 2], std::complex<float>(17, 18))));
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
#pragma region move_constructor
TEST(dense_matrix_move_constructor, given_f_dense_matrix_should_move_construct_and_leave_other_empty) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    const DenseMatrix<float> b = std::move(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare(a.rows(), 0)));
    ASSERT_TRUE((compare(a.columns(), 0)));
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

TEST(dense_matrix_move_constructor, given_cf_dense_matrix_should_move_construct_and_leave_other_empty) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act
    const DenseMatrix<std::complex<float>> b = std::move(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE((compare(a.rows(), 0)));
    ASSERT_TRUE((compare(a.columns(), 0)));
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
TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_f_dense_matrix_of_same_size_should_copy_assign) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(3, 3, true);
    // act
    b = a;
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
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

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_cf_dense_matrix_of_same_size_should_copy_assign) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    DenseMatrix<std::complex<float>> b(3, 3, true);
    // act
    b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
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

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_f_dense_matrix_of_diff_size_should_copy_assign_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(2, 3, true);
    // act
    b = a;
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
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

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_f_dense_matrix_of_diff_size_should_copy_assign_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(3, 2, true);
    // act
    b = a;
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
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

TEST(dense_matrix_copy_assignment_operator_from_same_type_dense_matrix, given_f_self_should_do_nothing) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-assign-overloaded"
    // ReSharper disable once CppIdenticalOperandsInBinaryExpression
    a = a;
#pragma GCC diagnostic pop
    const float* aData = a.data();
    // assert
    ASSERT_TRUE(compare(a.rows(), 3));
    ASSERT_TRUE(compare(a.columns(), 3));
    ASSERT_TRUE((compare(Precision(0.001f), aData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[8], 9)));
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_dense_matrix
TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix, given_f_dense_matrix_of_same_size_should_copy_assign) {
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

TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix, given_f_dense_matrix_of_diff_size_should_copy_assign_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> b(2, 3, true);
    // act
    b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
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

TEST(dense_matrix_copy_assignment_operator_from_different_type_dense_matrix, given_f_dense_matrix_of_diff_size_should_copy_assign_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<std::complex<float>> b(3, 2, true);
    // act
    b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
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
#pragma region move_assignment_operator
TEST(dense_matrix_move_assignment_operator, given_f_dense_matrix_of_same_size_should_move_assign) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(3, 3, true);
    // act
    b = std::move(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE(compare(a.rows(), 0));
    ASSERT_TRUE(compare(a.columns(), 0));
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
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

TEST(dense_matrix_move_assignment_operator, given_cf_dense_matrix_of_same_size_should_move_assign) {
    // arrange
    DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    DenseMatrix<std::complex<float>> b(3, 3, true);
    // act
    b = std::move(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE(compare(a.rows(), 0));
    ASSERT_TRUE(compare(a.columns(), 0));
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
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

TEST(dense_matrix_move_assignment_operator, given_f_dense_matrix_of_diff_size_should_move_assign_1) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(2, 3, true);
    // act
    b = std::move(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE(compare(a.rows(), 0));
    ASSERT_TRUE(compare(a.columns(), 0));
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
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

TEST(dense_matrix_move_assignment_operator, given_f_dense_matrix_of_diff_size_should_move_assign_2) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    DenseMatrix<float> b(3, 2, true);
    // act
    b = std::move(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE(compare(a.rows(), 0));
    ASSERT_TRUE(compare(a.columns(), 0));
    ASSERT_TRUE(compare(b.rows(), 3));
    ASSERT_TRUE(compare(b.columns(), 3));
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

TEST(dense_matrix_move_assignment_operator, given_f_self_should_do_nothing) {
    // arrange
    DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-move"
    a = std::move(a);
#pragma GCC diagnostic pop
    const float* aData = a.data();
    // assert
    ASSERT_TRUE(compare(a.rows(), 3));
    ASSERT_TRUE(compare(a.columns(), 3));
    ASSERT_TRUE((compare(Precision(0.001f), aData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[1], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[2], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[3], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[4], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[5], 8)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[6], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[7], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[8], 9)));
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
