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

TEST(Vector, should_initialize_list) {
    // arrange/act
    Vector<3> v = {1, 2, 3};
    // assert
    ASSERT_FLOAT_EQ(v[0], 1.0f);
    ASSERT_FLOAT_EQ(v[1], 2.0f);
    ASSERT_FLOAT_EQ(v[2], 3.0f);
}

TEST(Vector, should_not_initialize_list) {
    ASSERT_ANY_THROW((Vector<3>({1, 2})));
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

TEST(Vector, should_copy_assign_to_f_from_f) {
    // arrange
    Vector<3> a = {1, 2, 3};
    Vector<3> b;

    // act
    b = a;

    // assert
    ASSERT_FLOAT_EQ(b[0], 1);
    ASSERT_FLOAT_EQ(b[1], 2);
    ASSERT_FLOAT_EQ(b[2], 3);
}

TEST(Vector, should_copy_assign_to_d_from_d) {
    // arrange
    Vector<3, double> a = {1, 2, 3};
    Vector<3, double> b;

    // act
    b = a;

    // assert
    ASSERT_DOUBLE_EQ(b[0], 1);
    ASSERT_DOUBLE_EQ(b[1], 2);
    ASSERT_DOUBLE_EQ(b[2], 3);
}

TEST(Vector, should_copy_assign_to_f_from_d) {
    // arrange
    Vector<3, double> a = {1, 2, 3};
    Vector<3> b;

    // act
    b = a;

    // assert
    ASSERT_FLOAT_EQ(b[0], 1);
    ASSERT_FLOAT_EQ(b[1], 2);
    ASSERT_FLOAT_EQ(b[2], 3);
}

TEST(Vector, should_copy_assign_to_d_from_f) {
    // arrange
    Vector<3> a = {1, 2, 3};
    Vector<3, double> b;

    // act
    b = a;

    // assert
    ASSERT_DOUBLE_EQ(b[0], 1);
    ASSERT_DOUBLE_EQ(b[1], 2);
    ASSERT_DOUBLE_EQ(b[2], 3);
}

TEST(Vector, should_equal_f_to_f) {
    // arrange
    Vector<3> a = {1, 2, 3};
    Vector<3> b = {1, 2, 3};
    // act / assert
    ASSERT_TRUE(a == b);
}

TEST(Vector, should_equal_d_to_d) {
    // arrange
    Vector<3, double> a = {1, 2, 3};
    Vector<3, double> b = {1, 2, 3};
    // act / assert
    ASSERT_TRUE(a == b);
}

TEST(Vector, should_equal_f_to_d) {
    // arrange
    Vector<3> a = {1, 2, 3};
    Vector<3, double> b = {1, 2, 3};
    // act / assert
    ASSERT_TRUE(a == b);
}

TEST(Vector, should_equal_d_to_f) {
    // arrange
    Vector<3, double> a = {1, 2, 3};
    Vector<3> b = {1, 2, 3};
    // act / assert
    ASSERT_TRUE(a == b);
}

TEST(Vector, should_not_equal_f_to_f) {
    // arrange
    Vector<3> a = {1, 2, 3};
    Vector<3> b = {4, 5, 6};
    // act / assert
    ASSERT_TRUE(a != b);
}

TEST(Vector, should_not_equal_d_to_d) {
    // arrange
    Vector<3, double> a = {1, 2, 3};
    Vector<3, double> b = {4, 5, 6};
    // act / assert
    ASSERT_TRUE(a != b);
}

TEST(Vector, should_not_equal_f_to_d) {
    // arrange
    Vector<3> a = {1, 2, 3};
    Vector<3, double> b = {4, 5, 6};
    // act / assert
    ASSERT_TRUE(a != b);
}

TEST(Vector, should_not_equal_d_to_f) {
    // arrange
    Vector<3, double> a = {1, 2, 3};
    Vector<3> b = {4, 5, 6};
    // act / assert
    ASSERT_TRUE(a != b);
}

TEST(Vector, should_add_f_plus_f) {
    // arrange
    Vector<2> a = {1, 2};
    Vector<2> b = {3, 4};
    // act
    Vector<2> c = a + b;
    // assert
    ASSERT_FLOAT_EQ(c[0], 4);
    ASSERT_FLOAT_EQ(c[1], 6);
}

TEST(Vector, should_add_d_plus_d) {
    // arrange
    Vector<2, double> a = {1, 2};
    Vector<2, double> b = {3, 4};
    // act
    Vector<2, double> c = a + b;
    // assert
    ASSERT_DOUBLE_EQ(c[0], 4);
    ASSERT_DOUBLE_EQ(c[1], 6);
}

TEST(Vector, should_add_d_plus_f) {
    // arrange
    Vector<2, double> a = {1, 2};
    Vector<2> b = {3, 4};
    // act
    Vector<2, double> c = a + b;
    // assert
    ASSERT_DOUBLE_EQ(c[0], 4);
    ASSERT_DOUBLE_EQ(c[1], 6);
}

TEST(Vector, should_add_f_plus_d) {
    // arrange
    Vector<2> a = {1, 2};
    Vector<2, double> b = {3, 4};
    // act
    Vector<2> c = a + b;
    // assert
    ASSERT_FLOAT_EQ(c[0], 4);
    ASSERT_FLOAT_EQ(c[1], 6);
}

TEST(Vector, should_sub_f_minus_f) {
    // arrange
    Vector<2> a = {1, 3};
    Vector<2> b = {5, 5};
    // act
    Vector<2> c = a - b;
    // assert
    ASSERT_FLOAT_EQ(c[0], -4);
    ASSERT_FLOAT_EQ(c[1], -2);
}

TEST(Vector, should_sub_d_minus_d) {
    // arrange
    Vector<2, double> a = {1, 3};
    Vector<2, double> b = {5, 5};
    // act
    Vector<2, double> c = a - b;
    // assert
    ASSERT_DOUBLE_EQ(c[0], -4);
    ASSERT_DOUBLE_EQ(c[1], -2);
}

TEST(Vector, should_sub_d_minus_f) {
    // arrange
    Vector<2, double> a = {1, 3};
    Vector<2> b = {5, 5};
    // act
    Vector<2, double> c = a - b;
    // assert
    ASSERT_DOUBLE_EQ(c[0], -4);
    ASSERT_DOUBLE_EQ(c[1], -2);
}

TEST(Vector, should_sub_f_minus_d) {
    // arrange
    Vector<2> a = {1, 3};
    Vector<2, double> b = {5, 5};
    // act
    Vector<2> c = a - b;
    // assert
    ASSERT_FLOAT_EQ(c[0], -4);
    ASSERT_FLOAT_EQ(c[1], -2);
}

TEST(Vector, should_add_equals_f_plus_f) {
    // arrange
    Vector<2> a = {1, 2};
    Vector<2> b = {3, 4};
    // act
    a += b;
    // assert
    ASSERT_FLOAT_EQ(a[0], 4);
    ASSERT_FLOAT_EQ(a[1], 6);
}

TEST(Vector, should_add_equals_d_plus_d) {
    // arrange
    Vector<2, double> a = {1, 2};
    Vector<2, double> b = {3, 4};
    // act
    a += b;
    // assert
    ASSERT_DOUBLE_EQ(a[0], 4);
    ASSERT_DOUBLE_EQ(a[1], 6);
}

TEST(Vector, should_add_equals_d_plus_f) {
    // arrange
    Vector<2, double> a = {1, 2};
    Vector<2> b = {3, 4};
    // act
    a += b;
    // assert
    ASSERT_DOUBLE_EQ(a[0], 4);
    ASSERT_DOUBLE_EQ(a[1], 6);
}

TEST(Vector, should_add_equals_f_plus_d) {
    // arrange
    Vector<2> a = {1, 2};
    Vector<2, double> b = {3, 4};
    // act
    a += b;
    // assert
    ASSERT_FLOAT_EQ(a[0], 4);
    ASSERT_FLOAT_EQ(a[1], 6);
}

TEST(Vector, should_sub_equals_f_minus_f) {
    // arrange
    Vector<2> a = {1, 3};
    Vector<2> b = {5, 5};
    // act
    a -= b;
    // assert
    ASSERT_FLOAT_EQ(a[0], -4);
    ASSERT_FLOAT_EQ(a[1], -2);
}

TEST(Vector, should_sub_equals_d_minus_d) {
    // arrange
    Vector<2, double> a = {1, 3};
    Vector<2, double> b = {5, 5};
    // act
    a -= b;
    // assert
    ASSERT_DOUBLE_EQ(a[0], -4);
    ASSERT_DOUBLE_EQ(a[1], -2);
}

TEST(Vector, should_sub_equals_d_minus_f) {
    // arrange
    Vector<2, double> a = {1, 3};
    Vector<2> b = {5, 5};
    // act
    a -= b;
    // assert
    ASSERT_DOUBLE_EQ(a[0], -4);
    ASSERT_DOUBLE_EQ(a[1], -2);
}

TEST(Vector, should_sub_equals_f_minus_d) {
    // arrange
    Vector<2> a = {1, 3};
    Vector<2, double> b = {5, 5};
    // act
    a -= b;
    // assert
    ASSERT_FLOAT_EQ(a[0], -4);
    ASSERT_FLOAT_EQ(a[1], -2);
}

TEST(Vector, should_angle_same_type) {
    // arrange
    Vector<2> a = {0, 1};
    Vector<2> b = {1, 0};
    // act
    float angle = a.angle(b);
    // assert
    ASSERT_FLOAT_EQ(angle, 90);
}

TEST(Vector, should_angle_different_type) {
    // arrange
    Vector<2, double> a = {0, 1};
    Vector<2> b = {1, 0};
    // act
    double angle = a.angle(b);
    // assert
    ASSERT_DOUBLE_EQ(angle, 90);
}

TEST(Vector, should_magnitude) {
    // arrange
    Vector<2> a = {1, 1};
    // act
    float magnitude = a.magnitude();
    // assert
    ASSERT_FLOAT_EQ(magnitude, M_SQRT2);
}

TEST(Vector, should_component_dot_same_type) {
    // arrange
    Vector<2> a = {1, 1};
    Vector<2> b = {0, 2};
    // act
    float compDot = a.componentDot(b);
    // assert
    ASSERT_FLOAT_EQ(compDot, 2);
}

TEST(Vector, should_component_dot_different_type) {
    // arrange
    Vector<2, double> a = {1, 1};
    Vector<2> b = {0, 2};
    // act
    double compDot = a.componentDot(b);
    // assert
    ASSERT_DOUBLE_EQ(compDot, 2);
}

TEST(Vector, should_geometric_dot_same_type) {
    // arrange
    Vector<2> a = {1, 1};
    Vector<2> b = {1, 2};
    // act
    float geoDot = a.geometricDot(b);
    // assert
    ASSERT_FLOAT_EQ(geoDot, 3);
}

TEST(Vector, should_geometric_dot_different_type) {
    // arrange
    Vector<2, double> a = {1, 1};
    Vector<2> b = {1, 2};
    // act
    double geoDot = a.geometricDot(b);
    // assert
    ASSERT_DOUBLE_EQ(geoDot, 3);
}

TEST(Vector, should_cast_f) {
    // arrange
    Vector<2> a = {1, 2};
    // act
    float* ptr = static_cast<float*>(a);
    // assert
    ASSERT_FLOAT_EQ(ptr[0], 1);
    ASSERT_FLOAT_EQ(ptr[1], 2);
}

TEST(Vector, should_cast_d) {
    // arrange
    Vector<2, double> a = {1, 2};
    // act
    double* ptr = static_cast<double*>(a);
    // assert
    ASSERT_DOUBLE_EQ(ptr[0], 1);
    ASSERT_DOUBLE_EQ(ptr[1], 2);
}

TEST(Vector, should_const_cast_f) {
    // arrange
    const Vector<2> a = {1, 2};
    // act
    const float* ptr = static_cast<const float*>(a);
    // assert
    ASSERT_FLOAT_EQ(ptr[0], 1);
    ASSERT_FLOAT_EQ(ptr[1], 2);
}

TEST(Vector, should_const_cast_d) {
    // arrange
    const Vector<2, double> a = {1, 2};
    // act
    const double* ptr = static_cast<const double*>(a);
    // assert
    ASSERT_DOUBLE_EQ(ptr[0], 1);
    ASSERT_DOUBLE_EQ(ptr[1], 2);
}

TEST(Vector, multiply_with_matrix) {
    // assemble
    Vector<2> a = {2, 5};
    Matrix<2, 2> b = {{1, 0}, {0, 1}};
    // act
    auto c = b * a;
}