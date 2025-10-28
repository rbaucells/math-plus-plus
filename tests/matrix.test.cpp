#include <gtest/gtest.h>
#include "math++/math.h"

TEST(Matrix, should_default_construct_matrix_f) {
    // act
    Matrix<2, 2> m;

    // assert
    ASSERT_FLOAT_EQ(m.data[0][0], 0.0f);
    ASSERT_FLOAT_EQ(m.data[1][0], 0.0f);
    ASSERT_FLOAT_EQ(m.data[0][1], 0.0f);
    ASSERT_FLOAT_EQ(m.data[1][1], 0.0f);
}

TEST(Matrix, should_default_construct_matrix_d) {
    // act
    Matrix<2, 2, double> m;

    // assert
    ASSERT_DOUBLE_EQ(m.data[0][0], 0.0);
    ASSERT_DOUBLE_EQ(m.data[1][0], 0.0);
    ASSERT_DOUBLE_EQ(m.data[0][1], 0.0);
    ASSERT_DOUBLE_EQ(m.data[1][1], 0.0);
}

TEST(Matrix, should_subscript_f) {
    // assemble
    Matrix<2, 2> m;

    // assert
    ASSERT_FLOAT_EQ(m[0][0], m.data[0][0]);
    ASSERT_FLOAT_EQ(m[1][0], m.data[1][0]);
    ASSERT_FLOAT_EQ(m[0][1], m.data[0][1]);
    ASSERT_FLOAT_EQ(m[1][1], m.data[1][1]);
}

TEST(Matrix, should_subscript_d) {
    // assemble
    Matrix<2, 2, double> m;

    // assert
    ASSERT_DOUBLE_EQ(m[0][0], m.data[0][0]);
    ASSERT_DOUBLE_EQ(m[1][0], m.data[1][0]);
    ASSERT_DOUBLE_EQ(m[0][1], m.data[0][1]);
    ASSERT_DOUBLE_EQ(m[1][1], m.data[1][1]);
}

TEST(Matrix, should_const_subscript_f) {
    // assemble
    const Matrix<2, 2> m;

    // assert
    ASSERT_FLOAT_EQ(m[0][0], m.data[0][0]);
    ASSERT_FLOAT_EQ(m[1][0], m.data[1][0]);
    ASSERT_FLOAT_EQ(m[0][1], m.data[0][1]);
    ASSERT_FLOAT_EQ(m[1][1], m.data[1][1]);
}

TEST(Matrix, should_const_subscript_d) {
    // assemble
    const Matrix<2, 2, double> m;

    // assert
    ASSERT_DOUBLE_EQ(m[0][0], m.data[0][0]);
    ASSERT_DOUBLE_EQ(m[1][0], m.data[1][0]);
    ASSERT_DOUBLE_EQ(m[0][1], m.data[0][1]);
    ASSERT_DOUBLE_EQ(m[1][1], m.data[1][1]);
}

TEST(Matrix, should_initialize_from_brackets) {
    // act
    Matrix<2, 2> a = {{1, 2}, {3, 4}};

    // assert
    ASSERT_FLOAT_EQ(a[0][0], 1.0f);
    ASSERT_FLOAT_EQ(a[1][0], 2.0f);
    ASSERT_FLOAT_EQ(a[0][1], 3.0f);
    ASSERT_FLOAT_EQ(a[1][1], 4.0f);
}

TEST(Matrix, should_copy_construct_matrix_f_from_another_matrix_f) {
    // arrange
    Matrix<2, 2> a = {{1, 0}, {0, 1}};
    // act
    Matrix<2, 2> b = a;
    // assert
    ASSERT_FLOAT_EQ(b[0][0], 1.0f);
    ASSERT_FLOAT_EQ(b[0][1], 0.0f);
    ASSERT_FLOAT_EQ(b[1][0], 0.0f);
    ASSERT_FLOAT_EQ(b[1][1], 1.0f);
}

TEST(Matrix, should_copy_construct_matrix_d_from_another_matrix_d) {
    // arrange
    Matrix<2, 2, double> a = {{1, 0}, {0, 1}};
    // act
    Matrix<2, 2, double> b = a;
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], 1.0);
    ASSERT_DOUBLE_EQ(b[0][1], 0.0);
    ASSERT_DOUBLE_EQ(b[1][0], 0.0);
    ASSERT_DOUBLE_EQ(b[1][1], 1.0);
}

TEST(Matrix, should_copy_construct_matrix_d_from_another_matrix_f) {
    // arrange
    Matrix<2, 2> a = {{1, 0}, {0, 1}};
    // act
    Matrix<2, 2, double> b = a;
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], 1.0);
    ASSERT_DOUBLE_EQ(b[0][1], 0.0);
    ASSERT_DOUBLE_EQ(b[1][0], 0.0);
    ASSERT_DOUBLE_EQ(b[1][1], 1.0);
}

TEST(Matrix, should_copy_construct_matrix_f_from_another_matrix_d) {
    // arrange
    Matrix<2, 2, double> a = {{1, 0}, {0, 1}};
    // act
    Matrix<2, 2> b = a;
    // assert
    ASSERT_FLOAT_EQ(b[0][0], 1.0f);
    ASSERT_FLOAT_EQ(b[0][1], 0.0f);
    ASSERT_FLOAT_EQ(b[1][0], 0.0f);
    ASSERT_FLOAT_EQ(b[1][1], 1.0f);
}

TEST(Matrix, should_make_identity_matrix_f) {
    // act
    Matrix<2, 2> a = Matrix<2, 2>::identity();
    // assert
    ASSERT_FLOAT_EQ(a[0][0], 1.0f);
    ASSERT_FLOAT_EQ(a[0][1], 0.0f);
    ASSERT_FLOAT_EQ(a[1][0], 0.0f);
    ASSERT_FLOAT_EQ(a[1][1], 1.0f);
}

TEST(Matrix, should_make_identity_matrix_d) {
    // act
    Matrix<2, 2, double> a = Matrix<2, 2, double>::identity();
    // assert
    ASSERT_DOUBLE_EQ(a[0][0], 1.0);
    ASSERT_DOUBLE_EQ(a[0][1], 0.0);
    ASSERT_DOUBLE_EQ(a[1][0], 0.0);
    ASSERT_DOUBLE_EQ(a[1][1], 1.0);
}

TEST(Matrix, should_copy_assign_to_f_from_f) {
    // arrange
    Matrix<2, 2> a = Matrix<2, 2>::identity();
    Matrix<2, 2> b;
    // act
    b = a;
    // assert
    ASSERT_FLOAT_EQ(b[0][0], 1.0f);
    ASSERT_FLOAT_EQ(b[0][1], 0.0f);
    ASSERT_FLOAT_EQ(b[1][0], 0.0f);
    ASSERT_FLOAT_EQ(b[1][1], 1.0f);
}

TEST(Matrix, should_copy_assign_to_d_from_d) {
    // arrange
    Matrix<2, 2, double> a = Matrix<2, 2, double>::identity();
    Matrix<2, 2, double> b;
    // act
    b = a;
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], 1.0);
    ASSERT_DOUBLE_EQ(b[0][1], 0.0);
    ASSERT_DOUBLE_EQ(b[1][0], 0.0);
    ASSERT_DOUBLE_EQ(b[1][1], 1.0);
}

TEST(Matrix, should_copy_assign_to_f_from_d) {
    // arrange
    Matrix<2, 2, double> a = Matrix<2, 2, double>::identity();
    Matrix<2, 2> b;
    // act
    b = a;
    // assert
    ASSERT_FLOAT_EQ(b[0][0], 1.0f);
    ASSERT_FLOAT_EQ(b[0][1], 0.0f);
    ASSERT_FLOAT_EQ(b[1][0], 0.0f);
    ASSERT_FLOAT_EQ(b[1][1], 1.0f);
}

TEST(Matrix, should_copy_assign_to_d_from_f) {
    // arrange
    Matrix<2, 2> a = Matrix<2, 2>::identity();
    Matrix<2, 2, double> b;
    // act
    b = a;
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], 1.0);
    ASSERT_DOUBLE_EQ(b[0][1], 0.0);
    ASSERT_DOUBLE_EQ(b[1][0], 0.0);
    ASSERT_DOUBLE_EQ(b[1][1], 1.0);
}

TEST(Matrix, should_add_f_to_f) {
    // arrange
    Matrix<2, 2> a = {
        {1, 2},
        {3, 4}
    };
    Matrix<2, 2> b = {
        {5, 6},
        {7, 8}
    };
    // act
    Matrix<2, 2> c = a + b;
    // assert
    ASSERT_FLOAT_EQ(c[0][0], 6.0f);
    ASSERT_FLOAT_EQ(c[1][0], 8.0f);
    ASSERT_FLOAT_EQ(c[0][1], 10.0f);
    ASSERT_FLOAT_EQ(c[1][1], 12.0f);
}

TEST(Matrix, should_add_d_to_d) {
    // arrange
    Matrix<2, 2, double> a = {
        {1, 2},
        {3, 4}
    };
    Matrix<2, 2, double> b = {
        {5, 6},
        {7, 8}
    };
    // act
    Matrix<2, 2, double> c = a + b;
    // assert
    ASSERT_DOUBLE_EQ(c[0][0], 6.0);
    ASSERT_DOUBLE_EQ(c[1][0], 8.0);
    ASSERT_DOUBLE_EQ(c[0][1], 10.0);
    ASSERT_DOUBLE_EQ(c[1][1], 12.0);
}

TEST(Matrix, should_add_d_to_f) {
    // arrange
    Matrix<2, 2, double> a = {
        {1, 2},
        {3, 4}
    };
    Matrix<2, 2> b = {
        {5, 6},
        {7, 8}
    };
    // act
    Matrix<2, 2> c = a + b;
    // assert
    ASSERT_FLOAT_EQ(c[0][0], 6.0f);
    ASSERT_FLOAT_EQ(c[1][0], 8.0f);
    ASSERT_FLOAT_EQ(c[0][1], 10.0f);
    ASSERT_FLOAT_EQ(c[1][1], 12.0f);
}

TEST(Matrix, should_add_f_to_d) {
    // arrange
    Matrix<2, 2> a = {
        {1, 2},
        {3, 4}
    };
    Matrix<2, 2, double> b = {
        {5, 6},
        {7, 8}
    };
    // act
    Matrix<2, 2, double> c = a + b;
    // assert
    ASSERT_DOUBLE_EQ(c[0][0], 6.0);
    ASSERT_DOUBLE_EQ(c[1][0], 8.0);
    ASSERT_DOUBLE_EQ(c[0][1], 10.0);
    ASSERT_DOUBLE_EQ(c[1][1], 12.0);
}

TEST(Matrix, should_sub_f_minus_f) {
    // arrange
    Matrix<2, 2> a = {
        {10, 8},
        {12, 6}
    };
    Matrix<2, 2> b = {
        {5, 2},
        {4, 3}
    };
    // act
    Matrix<2, 2> c = a - b;
    // assert
    ASSERT_FLOAT_EQ(c[0][0], 5.0f);
    ASSERT_FLOAT_EQ(c[1][0], 6.0f);
    ASSERT_FLOAT_EQ(c[0][1], 8.0f);
    ASSERT_FLOAT_EQ(c[1][1], 3.0f);
}

TEST(Matrix, should_sub_d_minus_d) {
    // arrange
    Matrix<2, 2, double> a = {
        {10, 8},
        {12, 6}
    };
    Matrix<2, 2, double> b = {
        {5, 2},
        {4, 3}
    };
    // act
    Matrix<2, 2, double> c = a - b;
    // assert
    ASSERT_DOUBLE_EQ(c[0][0], 5.0);
    ASSERT_DOUBLE_EQ(c[1][0], 6.0);
    ASSERT_DOUBLE_EQ(c[0][1], 8.0);
    ASSERT_DOUBLE_EQ(c[1][1], 3.0);
}

TEST(Matrix, should_sub_d_minus_f) {
    // arrange
    Matrix<2, 2, double> a = {
        {10, 8},
        {12, 6}
    };
    Matrix<2, 2> b = {
        {5, 2},
        {4, 3}
    };
    // act
    Matrix<2, 2, double> c = a - b;
    // assert
    ASSERT_DOUBLE_EQ(c[0][0], 5.0);
    ASSERT_DOUBLE_EQ(c[1][0], 6.0);
    ASSERT_DOUBLE_EQ(c[0][1], 8.0);
    ASSERT_DOUBLE_EQ(c[1][1], 3.0);
}

TEST(Matrix, should_sub_f_minus_d) {
    // arrange
    Matrix<2, 2> a = {
        {10, 8},
        {12, 6}
    };
    Matrix<2, 2, double> b = {
        {5, 2},
        {4, 3}
    };
    // act
    Matrix<2, 2> c = a - b;
    // assert
    ASSERT_FLOAT_EQ(c[0][0], 5.0f);
    ASSERT_FLOAT_EQ(c[1][0], 6.0f);
    ASSERT_FLOAT_EQ(c[0][1], 8.0f);
    ASSERT_FLOAT_EQ(c[1][1], 3.0f);
}

TEST(Matrix, should_multiply_f_by_f_same_size) {
    // arrange
    Matrix<2, 2> a = {
        {10, 8},
        {12, 6}
    };
    Matrix<2, 2> b = {
        {5, 2},
        {4, 3}
    };
    // act
    Matrix<2, 2> c = a * b;
    // assert
    ASSERT_FLOAT_EQ(c[0][0], 82.0f);
    ASSERT_FLOAT_EQ(c[1][0], 44.0f);
    ASSERT_FLOAT_EQ(c[0][1], 84.0f);
    ASSERT_FLOAT_EQ(c[1][1], 42.0f);
}

TEST(Matrix, should_multiply_d_by_d_same_size) {
    // arrange
    Matrix<2, 2, double> a = {
        {10, 8},
        {12, 6}
    };
    Matrix<2, 2, double> b = {
        {5, 2},
        {4, 3}
    };
    // act
    Matrix<2, 2, double> c = a * b;
    // assert
    ASSERT_DOUBLE_EQ(c[0][0], 82.0);
    ASSERT_DOUBLE_EQ(c[1][0], 44.0);
    ASSERT_DOUBLE_EQ(c[0][1], 84.0);
    ASSERT_DOUBLE_EQ(c[1][1], 42.0);
}

TEST(Matrix, should_multiply_f_by_d_same_size) {
    // arrange
    Matrix<2, 2> a = {
        {10, 8},
        {12, 6}
    };
    Matrix<2, 2, double> b = {
        {5, 2},
        {4, 3}
    };
    // act
    Matrix<2, 2> c = a * b;
    // assert
    ASSERT_FLOAT_EQ(c[0][0], 82.0f);
    ASSERT_FLOAT_EQ(c[1][0], 44.0f);
    ASSERT_FLOAT_EQ(c[0][1], 84.0f);
    ASSERT_FLOAT_EQ(c[1][1], 42.0f);
}

TEST(Matrix, should_multiply_d_by_f_same_size) {
    // arrange
    Matrix<2, 2, double> a = {
        {10, 8},
        {12, 6}
    };
    Matrix<2, 2> b = {
        {5, 2},
        {4, 3}
    };
    // act
    Matrix<2, 2, double> c = a * b;
    // assert
    ASSERT_DOUBLE_EQ(c[0][0], 82.0);
    ASSERT_DOUBLE_EQ(c[1][0], 44.0);
    ASSERT_DOUBLE_EQ(c[0][1], 84.0);
    ASSERT_DOUBLE_EQ(c[1][1], 42.0);
}

TEST(Matrix, should_multiply_f_by_f_different_size) {
    // arrange
    Matrix<3, 2> a = {{1, 2, 3}, {4, 5, 6}};
    Matrix<2, 3> b = {{7, 8}, {9, 10}, {11, 12}};
    // act
    Matrix<2, 2> c = a * b;
    // assert
    ASSERT_FLOAT_EQ(c[0][0], 58.0f);
    ASSERT_FLOAT_EQ(c[1][0], 64.0f);
    ASSERT_FLOAT_EQ(c[0][1], 139.0f);
    ASSERT_FLOAT_EQ(c[1][1], 154.0f);
}

TEST(Matrix, should_multiply_d_by_d_different_size) {
    // arrange
    Matrix<3, 2, double> a = {{1, 2, 3}, {4, 5, 6}};
    Matrix<2, 3, double> b = {{7, 8}, {9, 10}, {11, 12}};
    // act
    Matrix<2, 2, double> c = a * b;
    // assert
    ASSERT_DOUBLE_EQ(c[0][0], 58.0);
    ASSERT_DOUBLE_EQ(c[1][0], 64.0);
    ASSERT_DOUBLE_EQ(c[0][1], 139.0);
    ASSERT_DOUBLE_EQ(c[1][1], 154.0);
}

TEST(Matrix, should_multiply_f_by_d_different_size) {
    // arrange
    Matrix<3, 2> a = {{1, 2, 3}, {4, 5, 6}};
    Matrix<2, 3, double> b = {{7, 8}, {9, 10}, {11, 12}};
    // act
    Matrix<2, 2> c = a * b;
    // assert
    ASSERT_FLOAT_EQ(c[0][0], 58.0f);
    ASSERT_FLOAT_EQ(c[1][0], 64.0f);
    ASSERT_FLOAT_EQ(c[0][1], 139.0f);
    ASSERT_FLOAT_EQ(c[1][1], 154.0f);
}

TEST(Matrix, should_multiply_d_by_f_different_size) {
    // arrange
    Matrix<3, 2, double> a = {{1, 2, 3}, {4, 5, 6}};
    Matrix<2, 3> b = {{7, 8}, {9, 10}, {11, 12}};
    // act
    Matrix<2, 2, double> c = a * b;
    // assert
    ASSERT_DOUBLE_EQ(c[0][0], 58.0);
    ASSERT_DOUBLE_EQ(c[1][0], 64.0);
    ASSERT_DOUBLE_EQ(c[0][1], 139.0);
    ASSERT_DOUBLE_EQ(c[1][1], 154.0);
}

TEST(Matrix, should_equal_f_with_f) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    Matrix<2, 2> b = {{1, 2}, {3, 4}};
    // act/assert
    ASSERT_TRUE(a == b);
}

TEST(Matrix, should_not_equal_f_with_f) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    Matrix<2, 2> b = {{5, 6}, {7, 8}};
    // act/assert
    ASSERT_TRUE(a != b);
}

TEST(Matrix, should_equal_d_with_d) {
    // arrange
    Matrix<2, 2, double> a = {{1, 2}, {3, 4}};
    Matrix<2, 2, double> b = {{1, 2}, {3, 4}};
    // act/assert
    ASSERT_TRUE(a == b);
}

TEST(Matrix, should_not_equal_d_with_d) {
    // arrange
    Matrix<2, 2, double> a = {{1, 2}, {3, 4}};
    Matrix<2, 2, double> b = {{5, 6}, {7, 8}};
    // act/assert
    ASSERT_TRUE(a != b);
}

TEST(Matrix, should_equal_f_with_d) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    Matrix<2, 2, double> b = {{1, 2}, {3, 4}};
    // act/assert
    ASSERT_TRUE(a == b);
}

TEST(Matrix, should_equal_d_with_f) {
    // arrange
    Matrix<2, 2, double> a = {{1, 2}, {3, 4}};
    Matrix<2, 2> b = {{1, 2}, {3, 4}};
    // act/assert
    ASSERT_TRUE(a == b);
}

TEST(Matrix, should_not_equal_f_with_d) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    Matrix<2, 2, double> b = {{5, 6}, {7, 8}};
    // act/assert
    ASSERT_TRUE(a != b);
}

TEST(Matrix, should_not_equal_d_with_f) {
    // arrange
    Matrix<2, 2, double> a = {{1, 2}, {3, 4}};
    Matrix<2, 2> b = {{5, 6}, {7, 8}};
    // act/assert
    ASSERT_TRUE(a != b);
}

TEST(Matrix, should_transpose_square) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    // act
    Matrix<2, 2> b = a.transpose();
    // assert
    ASSERT_FLOAT_EQ(b[0][0], a[0][0]);
    ASSERT_FLOAT_EQ(b[0][1], a[1][0]);
    ASSERT_FLOAT_EQ(b[1][0], a[0][1]);
    ASSERT_FLOAT_EQ(b[1][1], a[1][1]);
}

TEST(Matrix, should_transpose_non_square) {
    // arrange
    Matrix<3, 2> a = {{1, 2, 3}, {4, 5, 6}};
    // act
    Matrix<2, 3> b = a.transpose();
    // assert
    ASSERT_FLOAT_EQ(b[0][0], a[0][0]);
    ASSERT_FLOAT_EQ(b[1][0], a[0][1]);
    ASSERT_FLOAT_EQ(b[0][1], a[1][0]);
    ASSERT_FLOAT_EQ(b[1][1], a[1][1]);
    ASSERT_FLOAT_EQ(b[0][2], a[2][0]);
    ASSERT_FLOAT_EQ(b[1][2], a[2][1]);
}

TEST(Matrix, should_sub_matrix) {
    // arrange
    Matrix<3, 3> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act
    Matrix<2, 2> b = a.getSubMatrix(0, 1);
    // assert
    ASSERT_FLOAT_EQ(b[0][0], a[0][1]);
    ASSERT_FLOAT_EQ(b[1][0], a[2][1]);
    ASSERT_FLOAT_EQ(b[0][1], a[0][2]);
    ASSERT_FLOAT_EQ(b[1][1], a[2][2]);
}

TEST(Matrix, should_swap_rows) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    // act
    Matrix<2, 2> b = a.swapRows(0, 1);
    // assert
    ASSERT_FLOAT_EQ(b[0][0], a[0][1]);
    ASSERT_FLOAT_EQ(b[1][0], a[1][1]);
}

TEST(Matrix, should_non_zero_determinant_1x1_f) {
    // arrange
    Matrix<1, 1> a = {{5}};
    // act
    float det = a.determinant();
    // assert
    ASSERT_FLOAT_EQ(det, 5.0f);
}

TEST(Matrix, should_zero_determinant_1x1_f) {
    // arrange
    Matrix<1, 1> a = {{0}};
    // act
    float det = a.determinant();
    // assert
    ASSERT_FLOAT_EQ(det, 0.0f);
}

TEST(Matrix, should_non_zero_determinant_1x1_d) {
    // arrange
    Matrix<1, 1, double> a = {{5}};
    // act
    double det = a.determinant();
    // assert
    ASSERT_DOUBLE_EQ(det, 5.0f);
}

TEST(Matrix, should_zero_determinant_1x1_d) {
    // arrange
    Matrix<1, 1, double> a = {{0}};
    // act
    double det = a.determinant();
    // assert
    ASSERT_DOUBLE_EQ(det, 0.0f);
}

TEST(Matrix, should_non_zero_determinant_2x2_f) {
    // arrange
    Matrix<2, 2> a = {{2, 3}, {1, 4}};
    // act
    float det = a.determinant();
    // assert
    ASSERT_FLOAT_EQ(det, 5.0f);
}

TEST(Matrix, should_zero_determinant_2x2_f) {
    // arrange
    Matrix<2, 2> a = {{2, 4}, {1, 2}};
    // act
    float det = a.determinant();
    // assert
    ASSERT_FLOAT_EQ(det, 0.0f);
}

TEST(Matrix, should_non_zero_determinant_2x2_d) {
    // arrange
    Matrix<2, 2, double> a = {{2, 3}, {1, 4}};
    // act
    double det = a.determinant();
    // assert
    ASSERT_DOUBLE_EQ(det, 5.0);
}

TEST(Matrix, should_zero_determinant_2x2_d) {
    // arrange
    Matrix<2, 2, double> a = {{2, 4}, {1, 2}};
    // act
    double det = a.determinant();
    // assert
    ASSERT_DOUBLE_EQ(det, 0.0);
}

TEST(Matrix, should_non_zero_determinant_3x3_f) {
    // arrange
    Matrix<3, 3> a = {{1, -2, 3}, {2, 0, 3}, {1, 5, 4}};
    // act
    float det = a.determinant();
    // assert
    ASSERT_FLOAT_EQ(det, 25.0f);
}

TEST(Matrix, should_zero_determinant_3x3_f) {
    // arrange
    Matrix<3, 3> a = {{1, 2, 3}, {1, 2, 3}, {4, 5, 6}};
    // act
    float det = a.determinant();
    // assert
    ASSERT_FLOAT_EQ(det, 0.0f);
}

TEST(Matrix, should_non_zero_determinant_3x3_d) {
    // arrange
    Matrix<3, 3, double> a = {{1, -2, 3}, {2, 0, 3}, {1, 5, 4}};
    // act
    double det = a.determinant();
    // assert
    ASSERT_DOUBLE_EQ(det, 25.0);
}

TEST(Matrix, should_zero_determinant_3x3_d) {
    // arrange
    Matrix<3, 3, double> a = {{1, 2, 3}, {1, 2, 3}, {4, 5, 6}};
    // act
    double det = a.determinant();
    // assert
    ASSERT_DOUBLE_EQ(det, 0.0);
}

TEST(Matrix, should_inverse_1x1_f) {
    // arrange
    Matrix<1, 1> a = {{5}};
    // act
    Matrix<1, 1> b = a.inverse();
    // assert
    ASSERT_FLOAT_EQ(b[0][0], 0.2f);
}

TEST(Matrix, should_throw_inverse_1x1_f) {
    // arrange
    Matrix<1, 1> a = {{0}};
    Matrix<1, 1> b;
    // act
    ASSERT_ANY_THROW(b = a.inverse());
}

TEST(Matrix, should_inverse_1x1_d) {
    // arrange
    Matrix<1, 1, double> a = {{5}};
    // act
    Matrix<1, 1, double> b = a.inverse();
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], 0.2);
}

TEST(Matrix, should_throw_inverse_1x1_d) {
    // arrange
    Matrix<1, 1, double> a = {{0}};
    Matrix<1, 1, double> b;
    // act
    ASSERT_ANY_THROW(b = a.inverse());
}

TEST(Matrix, should_inverse_2x2_f) {
    // arrange
    Matrix<2, 2> a = {{1, 2}, {3, 4}};
    // act
    Matrix<2, 2> b = a.inverse();
    // assert
    ASSERT_FLOAT_EQ(b[0][0], -2);
    ASSERT_FLOAT_EQ(b[1][0], 1);
    ASSERT_FLOAT_EQ(b[0][1], 1.5f);
    ASSERT_FLOAT_EQ(b[1][1], -0.5f);
}

TEST(Matrix, should_inverse_2x2_d) {
    // arrange
    Matrix<2, 2, double> a = {{1, 2}, {3, 4}};
    // act
    Matrix<2, 2, double> b = a.inverse();
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], -2);
    ASSERT_DOUBLE_EQ(b[1][0], 1);
    ASSERT_DOUBLE_EQ(b[0][1], 1.5);
    ASSERT_DOUBLE_EQ(b[1][1], -0.5);
}

TEST(Matrix, should_throw_inverse_2x2_f) {
    // arrange
    Matrix<2, 2> a = {{1, 0}, {1, 0}};
    Matrix<2, 2> b;
    // act
    ASSERT_ANY_THROW(b = a.inverse());
}

TEST(Matrix, should_throw_inverse_2x2_d) {
    // arrange
    Matrix<2, 2, double> a = {{1, 0}, {1, 0}};
    Matrix<2, 2, double> b;
    // act
    ASSERT_ANY_THROW(b = a.inverse());
}

TEST(Matrix, should_inverse_3x3_f) {
    // arrange
    Matrix<3, 3> a = {{1, 0, 5}, {2, 1, 6}, {3, 4, 0}};
    // act
    Matrix<3, 3> b = a.inverse();
    // assert
    ASSERT_FLOAT_EQ(b[0][0], -24);
    ASSERT_FLOAT_EQ(b[1][0], 20);
    ASSERT_FLOAT_EQ(b[2][0], -5);
    ASSERT_FLOAT_EQ(b[0][1], 18);
    ASSERT_FLOAT_EQ(b[1][1], -15);
    ASSERT_FLOAT_EQ(b[2][1], 4);
    ASSERT_FLOAT_EQ(b[0][2], 5);
    ASSERT_FLOAT_EQ(b[1][2], -4);
    ASSERT_FLOAT_EQ(b[2][2], 1);
}

TEST(Matrix, should_inverse_3x3_d) {
    // arrange
    Matrix<3, 3, double> a = {{1, 0, 5}, {2, 1, 6}, {3, 4, 0}};
    // act
    Matrix<3, 3, double> b = a.inverse();
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], -24);
    ASSERT_DOUBLE_EQ(b[1][0], 20);
    ASSERT_DOUBLE_EQ(b[2][0], -5);
    ASSERT_DOUBLE_EQ(b[0][1], 18);
    ASSERT_DOUBLE_EQ(b[1][1], -15);
    ASSERT_DOUBLE_EQ(b[2][1], 4);
    ASSERT_DOUBLE_EQ(b[0][2], 5);
    ASSERT_DOUBLE_EQ(b[1][2], -4);
    ASSERT_DOUBLE_EQ(b[2][2], 1);
}

TEST(Matrix, should_throw_inverse_3x3_f) {
    // arrange
    Matrix<3, 3> a = {{1, 2, 3}, {1, 2, 3}, {4, 5, 6}};
    // act
    Matrix<3, 3> b;
    // assert
    ASSERT_ANY_THROW(b = a.inverse());
}

TEST(Matrix, should_throw_inverse_3x3_d) {
    // arrange
    Matrix<3, 3, double> a = {{1, 2, 3}, {1, 2, 3}, {4, 5, 6}};
    // act
    Matrix<3, 3, double> b;
    // assert
    ASSERT_ANY_THROW(b = a.inverse());
}

TEST(Matrix, should_scale_f) {
    // arrange
    Matrix<4, 4> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // act
    Matrix<4, 4> b = m.scale(2);
    // assert
    ASSERT_FLOAT_EQ(b[0][0], 2);
    ASSERT_FLOAT_EQ(b[1][0], 4);
    ASSERT_FLOAT_EQ(b[2][0], 6);
    ASSERT_FLOAT_EQ(b[3][0], 4);
    ASSERT_FLOAT_EQ(b[0][1], 10);
    ASSERT_FLOAT_EQ(b[1][1], 12);
    ASSERT_FLOAT_EQ(b[2][1], 14);
    ASSERT_FLOAT_EQ(b[3][1], 8);
    ASSERT_FLOAT_EQ(b[0][2], 18);
    ASSERT_FLOAT_EQ(b[1][2], 20);
    ASSERT_FLOAT_EQ(b[2][2], 22);
    ASSERT_FLOAT_EQ(b[3][2], 12);
    ASSERT_FLOAT_EQ(b[0][3], 26);
    ASSERT_FLOAT_EQ(b[1][3], 28);
    ASSERT_FLOAT_EQ(b[2][3], 30);
    ASSERT_FLOAT_EQ(b[3][3], 16);
}

TEST(Matrix, should_scale_d) {
    // arrange
    Matrix<4, 4, double> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // act
    Matrix<4, 4, double> b = m.scale(2);
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], 2);
    ASSERT_DOUBLE_EQ(b[1][0], 4);
    ASSERT_DOUBLE_EQ(b[2][0], 6);
    ASSERT_DOUBLE_EQ(b[3][0], 4);
    ASSERT_DOUBLE_EQ(b[0][1], 10);
    ASSERT_DOUBLE_EQ(b[1][1], 12);
    ASSERT_DOUBLE_EQ(b[2][1], 14);
    ASSERT_DOUBLE_EQ(b[3][1], 8);
    ASSERT_DOUBLE_EQ(b[0][2], 18);
    ASSERT_DOUBLE_EQ(b[1][2], 20);
    ASSERT_DOUBLE_EQ(b[2][2], 22);
    ASSERT_DOUBLE_EQ(b[3][2], 12);
    ASSERT_DOUBLE_EQ(b[0][3], 26);
    ASSERT_DOUBLE_EQ(b[1][3], 28);
    ASSERT_DOUBLE_EQ(b[2][3], 30);
    ASSERT_DOUBLE_EQ(b[3][3], 16);
}

TEST(Matrix, should_scale_anisotropic_f) {
    // arrange
    Matrix<4, 4> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // act
    Matrix<4, 4> b = m.scaleAnisotropic(1, 2, 3);
    // assert
    ASSERT_FLOAT_EQ(b[0][0], 1);
    ASSERT_FLOAT_EQ(b[1][0], 4);
    ASSERT_FLOAT_EQ(b[2][0], 9);
    ASSERT_FLOAT_EQ(b[3][0], 4);
    ASSERT_FLOAT_EQ(b[0][1], 5);
    ASSERT_FLOAT_EQ(b[1][1], 12);
    ASSERT_FLOAT_EQ(b[2][1], 21);
    ASSERT_FLOAT_EQ(b[3][1], 8);
    ASSERT_FLOAT_EQ(b[0][2], 9);
    ASSERT_FLOAT_EQ(b[1][2], 20);
    ASSERT_FLOAT_EQ(b[2][2], 33);
    ASSERT_FLOAT_EQ(b[3][2], 12);
    ASSERT_FLOAT_EQ(b[0][3], 13);
    ASSERT_FLOAT_EQ(b[1][3], 28);
    ASSERT_FLOAT_EQ(b[2][3], 45);
    ASSERT_FLOAT_EQ(b[3][3], 16);
}

TEST(Matrix, should_scale_anisotropic_d) {
    // arrange
    Matrix<4, 4, double> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // act
    Matrix<4, 4, double> b = m.scaleAnisotropic(1, 2, 3);
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], 1);
    ASSERT_DOUBLE_EQ(b[1][0], 4);
    ASSERT_DOUBLE_EQ(b[2][0], 9);
    ASSERT_DOUBLE_EQ(b[3][0], 4);
    ASSERT_DOUBLE_EQ(b[0][1], 5);
    ASSERT_DOUBLE_EQ(b[1][1], 12);
    ASSERT_DOUBLE_EQ(b[2][1], 21);
    ASSERT_DOUBLE_EQ(b[3][1], 8);
    ASSERT_DOUBLE_EQ(b[0][2], 9);
    ASSERT_DOUBLE_EQ(b[1][2], 20);
    ASSERT_DOUBLE_EQ(b[2][2], 33);
    ASSERT_DOUBLE_EQ(b[3][2], 12);
    ASSERT_DOUBLE_EQ(b[0][3], 13);
    ASSERT_DOUBLE_EQ(b[1][3], 28);
    ASSERT_DOUBLE_EQ(b[2][3], 45);
    ASSERT_DOUBLE_EQ(b[3][3], 16);
}

TEST(Matrix, should_translate_f) {
    // arrange
    Matrix<4, 4> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // act
    Matrix<4, 4> b = m.translate(3, 2, 1);
    // assert
    ASSERT_FLOAT_EQ(b[0][0], 1);
    ASSERT_FLOAT_EQ(b[1][0], 2);
    ASSERT_FLOAT_EQ(b[2][0], 3);
    ASSERT_FLOAT_EQ(b[3][0], 14);
    ASSERT_FLOAT_EQ(b[0][1], 5);
    ASSERT_FLOAT_EQ(b[1][1], 6);
    ASSERT_FLOAT_EQ(b[2][1], 7);
    ASSERT_FLOAT_EQ(b[3][1], 42);
    ASSERT_FLOAT_EQ(b[0][2], 9);
    ASSERT_FLOAT_EQ(b[1][2], 10);
    ASSERT_FLOAT_EQ(b[2][2], 11);
    ASSERT_FLOAT_EQ(b[3][2], 70);
    ASSERT_FLOAT_EQ(b[0][3], 13);
    ASSERT_FLOAT_EQ(b[1][3], 14);
    ASSERT_FLOAT_EQ(b[2][3], 15);
    ASSERT_FLOAT_EQ(b[3][3], 98);
}

TEST(Matrix, should_translate_d) {
    // arrange
    Matrix<4, 4, double> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // act
    Matrix<4, 4, double> b = m.translate(3, 2, 1);
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], 1);
    ASSERT_DOUBLE_EQ(b[1][0], 2);
    ASSERT_DOUBLE_EQ(b[2][0], 3);
    ASSERT_DOUBLE_EQ(b[3][0], 14);
    ASSERT_DOUBLE_EQ(b[0][1], 5);
    ASSERT_DOUBLE_EQ(b[1][1], 6);
    ASSERT_DOUBLE_EQ(b[2][1], 7);
    ASSERT_DOUBLE_EQ(b[3][1], 42);
    ASSERT_DOUBLE_EQ(b[0][2], 9);
    ASSERT_DOUBLE_EQ(b[1][2], 10);
    ASSERT_DOUBLE_EQ(b[2][2], 11);
    ASSERT_DOUBLE_EQ(b[3][2], 70);
    ASSERT_DOUBLE_EQ(b[0][3], 13);
    ASSERT_DOUBLE_EQ(b[1][3], 14);
    ASSERT_DOUBLE_EQ(b[2][3], 15);
    ASSERT_DOUBLE_EQ(b[3][3], 98);
}

TEST(Matrix, should_rotate_x_degrees_f) {
    // arrange
    Matrix<4, 4> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // act
    Matrix<4, 4> b = m.rotateX(90, RotationType::degrees);
    // assert
    ASSERT_FLOAT_EQ(b[0][0], 1);
    ASSERT_FLOAT_EQ(b[1][0], 3);
    ASSERT_FLOAT_EQ(b[2][0], -2);
    ASSERT_FLOAT_EQ(b[3][0], 4);
    ASSERT_FLOAT_EQ(b[0][1], 5);
    ASSERT_FLOAT_EQ(b[1][1], 7);
    ASSERT_FLOAT_EQ(b[2][1], -6);
    ASSERT_FLOAT_EQ(b[3][1], 8);
    ASSERT_FLOAT_EQ(b[0][2], 9);
    ASSERT_FLOAT_EQ(b[1][2], 11);
    ASSERT_FLOAT_EQ(b[2][2], -10);
    ASSERT_FLOAT_EQ(b[3][2], 12);
    ASSERT_FLOAT_EQ(b[0][3], 13);
    ASSERT_FLOAT_EQ(b[1][3], 15);
    ASSERT_FLOAT_EQ(b[2][3], -14);
    ASSERT_FLOAT_EQ(b[3][3], 16);
}

TEST(Matrix, should_rotate_x_degrees_d) {
    // arrange
    Matrix<4, 4, double> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // act
    Matrix<4, 4, double> b = m.rotateX(90, RotationType::degrees);
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], 1);
    ASSERT_DOUBLE_EQ(b[1][0], 3);
    ASSERT_DOUBLE_EQ(b[2][0], -2);
    ASSERT_DOUBLE_EQ(b[3][0], 4);
    ASSERT_DOUBLE_EQ(b[0][1], 5);
    ASSERT_DOUBLE_EQ(b[1][1], 7);
    ASSERT_DOUBLE_EQ(b[2][1], -6);
    ASSERT_DOUBLE_EQ(b[3][1], 8);
    ASSERT_DOUBLE_EQ(b[0][2], 9);
    ASSERT_DOUBLE_EQ(b[1][2], 11);
    ASSERT_DOUBLE_EQ(b[2][2], -10);
    ASSERT_DOUBLE_EQ(b[3][2], 12);
    ASSERT_DOUBLE_EQ(b[0][3], 13);
    ASSERT_DOUBLE_EQ(b[1][3], 15);
    ASSERT_DOUBLE_EQ(b[2][3], -14);
    ASSERT_DOUBLE_EQ(b[3][3], 16);
}

TEST(Matrix, should_rotate_x_radians_f) {
    // arrange
    Matrix<4, 4> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // act
    Matrix<4, 4> b = m.rotateX(M_PI, RotationType::radians);
    // assert
    ASSERT_FLOAT_EQ(b[0][0], 1);
    ASSERT_FLOAT_EQ(b[1][0], -2);
    ASSERT_FLOAT_EQ(b[2][0], -3);
    ASSERT_FLOAT_EQ(b[3][0], 4);
    ASSERT_FLOAT_EQ(b[0][1], 5);
    ASSERT_FLOAT_EQ(b[1][1], -6);
    ASSERT_FLOAT_EQ(b[2][1], -7);
    ASSERT_FLOAT_EQ(b[3][1], 8);
    ASSERT_FLOAT_EQ(b[0][2], 9);
    ASSERT_FLOAT_EQ(b[1][2], -10);
    ASSERT_FLOAT_EQ(b[2][2], -11);
    ASSERT_FLOAT_EQ(b[3][2], 12);
    ASSERT_FLOAT_EQ(b[0][3], 13);
    ASSERT_FLOAT_EQ(b[1][3], -14);
    ASSERT_FLOAT_EQ(b[2][3], -15);
    ASSERT_FLOAT_EQ(b[3][3], 16);
}

TEST(Matrix, should_rotate_x_radians_d) {
    // arrange
    Matrix<4, 4, double> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // act
    Matrix<4, 4, double> b = m.rotateX(M_PI, RotationType::radians);
    // assert
    ASSERT_DOUBLE_EQ(b[0][0], 1);
    ASSERT_DOUBLE_EQ(b[1][0], -2);
    ASSERT_DOUBLE_EQ(b[2][0], -3);
    ASSERT_DOUBLE_EQ(b[3][0], 4);
    ASSERT_DOUBLE_EQ(b[0][1], 5);
    ASSERT_DOUBLE_EQ(b[1][1], -6);
    ASSERT_DOUBLE_EQ(b[2][1], -7);
    ASSERT_DOUBLE_EQ(b[3][1], 8);
    ASSERT_DOUBLE_EQ(b[0][2], 9);
    ASSERT_DOUBLE_EQ(b[1][2], -10);
    ASSERT_DOUBLE_EQ(b[2][2], -11);
    ASSERT_DOUBLE_EQ(b[3][2], 12);
    ASSERT_DOUBLE_EQ(b[0][3], 13);
    ASSERT_DOUBLE_EQ(b[1][3], -14);
    ASSERT_DOUBLE_EQ(b[2][3], -15);
    ASSERT_DOUBLE_EQ(b[3][3], 16);
}