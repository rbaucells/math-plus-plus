#include "gtest/gtest.h"

#include "mathpp/vector/dense/core.h"

#pragma region constructor
TEST(custom_dense_vector_constructor, given_f_pointer_and_size_should_construct) {
    // arrange
    float* data = new float[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    // act
    const CustomDenseVector<float> v(data, 3, 1);
    // assert
    ASSERT_TRUE(data == v.data());
    ASSERT_TRUE((compare(v.n(), 3)));
    ASSERT_TRUE((compare(v.stride(), 1)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_constructor, given_cf_pointer_and_size_should_construct) {
    // arrange
    std::complex<float>* data = new std::complex<float>[3];
    data[0] = {1, 2};
    data[1] = {3, 4};
    data[2] = {5, 6};
    // act
    const CustomDenseVector<std::complex<float>> v(data, 3, 1);
    // assert
    ASSERT_TRUE(data == v.data());
    ASSERT_TRUE((compare(v.n(), 3)));
    ASSERT_TRUE((compare(v.stride(), 1)));
    // cleanup
    delete[] data;
}
#pragma endregion
#pragma region index_operator
TEST(custom_dense_vector_index_operator, given_index_should_return_reference_f) {
    // arrange
    float* data = new float[3];
    CustomDenseVector<float> v(data, 3, 1);
    // act
    float& v0 = v[0];
    v0 = 1;
    float& v1 = v[1];
    v1 = 2;
    float& v2 = v[2];
    v2 = 3;
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), data[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), data[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), data[2], 3)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_index_operator, given_index_should_return_reference_cf) {
    // arrange
    std::complex<float>* data = new std::complex<float>[3];
    CustomDenseVector<std::complex<float>> v(data, 3, 1);
    // act
    std::complex<float>& v0 = v[0];
    v0 = {1, 2};
    std::complex<float>& v1 = v[1];
    v1 = {3, 4};
    std::complex<float>& v2 = v[2];
    v2 = {5, 6};
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), data[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), data[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), data[2], std::complex<float>(5, 6))));
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_index_operator, given_big_index_should_throw_1) {
    // arrange
    float* data = new float[3];
    CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_index_operator, given_big_index_should_throw_2) {
    // arrange
    float* data = new float[5];
    CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
    // cleanup
    delete[] data;
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
    // act / assert
    ASSERT_TRUE((compare(Precision(0.001f), v[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2], 3)));
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_const_index_operator, given_index_should_return_const_reference_cf) {
    // arrange
    std::complex<float>* data = new std::complex<float>[3];
    data[0] = {1, 2};
    data[1] = {3, 4};
    data[2] = {5, 6};
    const CustomDenseVector<std::complex<float>> v(data, 3, 1);
    // act / assert
    ASSERT_TRUE((compare(Precision(0.001f), v[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2], std::complex<float>(5, 6))));
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_const_index_operator, given_big_index_should_throw_1) {
    // arrange
    float* data = new float[3];
    const CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
    // cleanup
    delete[] data;
}

TEST(custom_dense_vector_const_index_operator, given_big_index_should_throw_2) {
    // arrange
    float* data = new float[5];
    const CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
    // cleanup
    delete[] data;
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
    ASSERT_TRUE((compare(stride, 1)));
    // cleanup
    delete[] data;
}
#pragma endregion
