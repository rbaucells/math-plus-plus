#include "gtest/gtest.h"

#include "mathpp/matrix/dense/operators.h"

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
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
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
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
}

TEST(custom_dense_matrix_index_operator, given_big_index_should_throw_4) {
    // arrange
    float* data = new float[25];
    CustomDenseMatrix<float> v(data, 3, 3, 3);
    // act / assert
    ASSERT_THROW((std::ignore = v[0, 3]), InvalidIndexException);
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
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], 3)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], 4)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], 5)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], 6)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], 7)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], 8)));
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
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], std::complex<float>(9, 10))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], std::complex<float>(11, 12))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], std::complex<float>(13, 14))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], std::complex<float>(15, 16))));
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
