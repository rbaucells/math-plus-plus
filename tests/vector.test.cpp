#include <gtest/gtest.h>
#include "math++/math.h"

TEST(Vector, should_default_construct_f) {
    // arrange/act
    Vector<3> v;
    // assert
    ASSERT_FLOAT_EQ(v.data[0], 0.0f);
    ASSERT_FLOAT_EQ(v.data[1], 0.0f);
    ASSERT_FLOAT_EQ(v.data[2], 0.0f);
}

TEST(Vector, should_subscript_f) {
    // arrange/act
    Vector<3> v;
    // assert
    ASSERT_FLOAT_EQ(v[0], 0.0f);
    ASSERT_FLOAT_EQ(v[1], 0.0f);
    ASSERT_FLOAT_EQ(v[2], 0.0f);
}

TEST(Vector, should_const_subscript_f) {
    // arrange/act
    const Vector<3> v;
    // assert
    ASSERT_FLOAT_EQ(v[0], 0.0f);
    ASSERT_FLOAT_EQ(v[1], 0.0f);
    ASSERT_FLOAT_EQ(v[2], 0.0f);
}

TEST(Vector, should_default_construct_d) {
    // arrange/act
    Vector<3, double> v;
    // assert
    ASSERT_FLOAT_EQ(v.data[0], 0.0);
    ASSERT_FLOAT_EQ(v.data[1], 0.0);
    ASSERT_FLOAT_EQ(v.data[2], 0.0);
}

TEST(Vector, should_subscript_d) {
    // arrange/act
    Vector<3, double> v;
    // assert
    ASSERT_DOUBLE_EQ(v[0], 0.0);
    ASSERT_DOUBLE_EQ(v[1], 0.0);
    ASSERT_DOUBLE_EQ(v[2], 0.0);
}

TEST(Vector, should_const_subscript_d) {
    // arrange/act
    const Vector<3, double> v;
    // assert
    ASSERT_DOUBLE_EQ(v[0], 0.0);
    ASSERT_DOUBLE_EQ(v[1], 0.0);
    ASSERT_DOUBLE_EQ(v[2], 0.0);
}

TEST(Vector, should_initialize_list_f) {
    // arrange/act
    Vector<3> v = {1, 2, 3};
    // assert
    ASSERT_FLOAT_EQ(v[0], 1.0f);
    ASSERT_FLOAT_EQ(v[1], 2.0f);
    ASSERT_FLOAT_EQ(v[2], 3.0f);
}

TEST(Vector, should_initialize_list_d) {
    // arrange/act
    Vector<3, double> v = {1, 2, 3};
    // assert
    ASSERT_DOUBLE_EQ(v[0], 1.0);
    ASSERT_DOUBLE_EQ(v[1], 2.0);
    ASSERT_DOUBLE_EQ(v[2], 3.0);
}

TEST(Vector, should_copy_construct_f_from_f) {
    // arrange
    Vector<3> a = {1, 2, 3};
    // act
    Vector<3> b = a;
    // assert
    ASSERT_FLOAT_EQ(b[0], 1.0f);
    ASSERT_FLOAT_EQ(b[1], 2.0f);
    ASSERT_FLOAT_EQ(b[2], 3.0f);
}

TEST(Vector, should_copy_construct_d_from_d) {
    // arrange
    Vector<3, double> a = {1, 2, 3};
    // act
    Vector<3, double> b = a;
    // assert
    ASSERT_DOUBLE_EQ(b[0], 1.0);
    ASSERT_DOUBLE_EQ(b[1], 2.0);
    ASSERT_DOUBLE_EQ(b[2], 3.0);
}

TEST(Vector, should_copy_construct_f_from_d) {
    // arrange
    Vector<3, double> a = {1, 2, 3};
    // act
    Vector<3> b = a;
    // assert
    ASSERT_FLOAT_EQ(b[0], 1.0f);
    ASSERT_FLOAT_EQ(b[1], 2.0f);
    ASSERT_FLOAT_EQ(b[2], 3.0f);
}

TEST(Vector, should_copy_construct_d_from_f) {
    // arrange
    Vector<3> a = {1, 2, 3};
    // act
    Vector<3, double> b = a;
    // assert
    ASSERT_DOUBLE_EQ(b[0], 1.0);
    ASSERT_DOUBLE_EQ(b[1], 2.0);
    ASSERT_DOUBLE_EQ(b[2], 3.0);
}