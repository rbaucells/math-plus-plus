#include "gtest/gtest.h"
#include "mathpp/math.h"

TEST(dense_matrix_mixed_operators, given_f_dense_matrices_should_return_a_plus_b_minus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<float> c = {{-5, 1, 7}, {-22, 56, 2}, {9, 4, 7}};
    const DenseMatrix<float> expected = {{8, 6, 4}, {27, -44, 35}, {6, 6, 9}};
    // act
    const DenseMatrix<float> result = a + b - c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed_operators, given_f_dense_matrices_should_return_a_minus_b_plus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<float> c = {{-5, 1, 7}, {-22, 56, 2}, {9, 4, 7}};
    const DenseMatrix<float> expected = {{-6, -2, 2}, {-19, 54, -23}, {8, 10, 9}};
    // act
    const DenseMatrix<float> result = a - b + c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed_operators, given_f_dense_matrices_should_return_a_plus_b_times_c_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 5, 1}, {5,7, 1}, {9, -1, 37}};
    const DenseMatrix<float> b = {{8, 1,3}, {8, 1, 4}, {3, -3, 5}};
    const DenseMatrix<float> c = {{1, 0, 3}, {8, 19, 5}, {9, 17, 5}};
    const DenseMatrix<float> expected = {{44, 75, 45}, {57, 94, 50}, {33, 27, 56}};
    // act
    const DenseMatrix<float> result = a + b * c;
    // a + b * c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed_operators, given_f_dense_matrices_should_return_a_plus_b_times_c_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 5, 1}, {5,7, 1}, {9, -1, 37}};
    const DenseMatrix<float> b = {{8, 1,3}, {8, 1, 4}, {3, -3, 5}};
    const DenseMatrix<float> c = {{1, 0, 3}, {8, 19, 5}, {9, 17, 5}};
    const DenseMatrix<float> expected = {{93, 182, 77}, {122, 237, 104}, {358, 638, 226}};
    // act
    const DenseMatrix<float> result = (a + b) * c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed_operators, given_f_dense_matrices_should_return_a_minus_b_times_c) {
    // arrange
    const DenseMatrix<float> a = {{50, 80, 60}, {60, 90, 70}, {40, 30, 80}};
    const DenseMatrix<float> b = {{2, 1, 3}, {4, 1, 4}, {3, 0, 1}};
    const DenseMatrix<float> c = {{1, 0, 3}, {8, 19, 5}, {9, 17, 5}};
    const DenseMatrix<float> expected = {{13, 10, 34}, {12, 3, 33}, {28, 13, 66}};
    // act
    const DenseMatrix<float> result = a - b * c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed_operators, given_f_dense_matrices_should_return_parenthesized_a_minus_b_times_c) {
    // arrange
    const DenseMatrix<float> a = {{9, 2, 6}, {13, 2, 8}, {6, 0, 10}};
    const DenseMatrix<float> b = {{8, 1, 3}, {8, 1, 4}, {3, 3, 5}};
    const DenseMatrix<float> c = {{1, 0, 3}, {8, 19, 5}, {9, 17, 5}};
    const DenseMatrix<float> expected = {{36, 70, 23}, {49, 87, 40}, {24, 28, 19}};
    // act
    const DenseMatrix<float> result = (a - b) * c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed_operators, given_f_dense_matrices_should_return_a_times_b_minus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 1}, {0, 1, 0}, {2, 0, 1}};
    const DenseMatrix<float> b = {{5, 2, 1}, {1, 3, 0}, {4, 0, 2}};
    const DenseMatrix<float> c = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    // a * b = {{11, 8, 3}, {1, 3, 0}, {14, 4, 4}}
    const DenseMatrix<float> expected = {{10, 7, 2}, {0, 2, -1}, {13, 3, 3}};
    // act
    const DenseMatrix<float> result = a * b - c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed_operators, given_f_dense_matrices_should_return_a_times_parenthesized_b_minus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 0, 2}, {0, 1, 0}, {3, 1, 1}};
    const DenseMatrix<float> b = {{10, 5, 8}, {6, 4, 2}, {8, 2, 6}};
    const DenseMatrix<float> c = {{8, 4, 5}, {5, 3, 1}, {7, 5, 1}};
    const DenseMatrix<float> expected = {{4, -5, 13}, {1, 1, 1}, {8, 1, 15}};
    // act
    const DenseMatrix<float> result = a * (b - c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed_operators, given_f_dense_matrices_should_return_a_times_b_plus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; // Identity
    const DenseMatrix<float> c = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
    const DenseMatrix<float> expected = {{3, 4, 5}, {6, 7, 8}, {9, 10, 11}};
    // act
    const DenseMatrix<float> result = a * b + c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed_operators, given_f_dense_matrices_should_return_a_times_parenthesized_b_plus_c) {
    // arrange
    const DenseMatrix<float> a = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    const DenseMatrix<float> expected = {{4, 6, 8}, {10, 12, 14}, {16, 18, 20}};
    // act
    const DenseMatrix<float> result = a * (b + c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed, given_f_dense_matrices_should_return_a_plus_b_minus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<float> c = {{-5, 1, 7}, {-22, 56, 2}, {9, 4, 7}};
    const DenseMatrix<float> expected = {{8, 6, 4}, {27, -44, 35}, {6, 6, 9}};
    // act
    const DenseMatrix<float> result = subtract(add(a, b), c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed, given_f_dense_matrices_should_return_a_minus_b_plus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{2, 5, 8}, {1, 7, 31}, {8, 2, 7}};
    const DenseMatrix<float> c = {{-5, 1, 7}, {-22, 56, 2}, {9, 4, 7}};
    const DenseMatrix<float> expected = {{-6, -2, 2}, {-19, 54, -23}, {8, 10, 9}};
    // act
    const DenseMatrix<float> result = add(subtract(a, b), c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed, given_f_dense_matrices_should_return_a_plus_b_times_c_1) {
    // arrange
    const DenseMatrix<float> a = {{1, 5, 1}, {5,7, 1}, {9, -1, 37}};
    const DenseMatrix<float> b = {{8, 1,3}, {8, 1, 4}, {3, -3, 5}};
    const DenseMatrix<float> c = {{1, 0, 3}, {8, 19, 5}, {9, 17, 5}};
    const DenseMatrix<float> expected = {{44, 75, 45}, {57, 94, 50}, {33, 27, 56}};
    // act
    const DenseMatrix<float> result = add(a, multiply(b, c));
    // a + b * c;
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed, given_f_dense_matrices_should_return_a_plus_b_times_c_2) {
    // arrange
    const DenseMatrix<float> a = {{1, 5, 1}, {5,7, 1}, {9, -1, 37}};
    const DenseMatrix<float> b = {{8, 1,3}, {8, 1, 4}, {3, -3, 5}};
    const DenseMatrix<float> c = {{1, 0, 3}, {8, 19, 5}, {9, 17, 5}};
    const DenseMatrix<float> expected = {{93, 182, 77}, {122, 237, 104}, {358, 638, 226}};
    // act
    const DenseMatrix<float> result = multiply(add(a, b), c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed, given_f_dense_matrices_should_return_a_minus_b_times_c) {
    // arrange
    const DenseMatrix<float> a = {{50, 80, 60}, {60, 90, 70}, {40, 30, 80}};
    const DenseMatrix<float> b = {{2, 1, 3}, {4, 1, 4}, {3, 0, 1}};
    const DenseMatrix<float> c = {{1, 0, 3}, {8, 19, 5}, {9, 17, 5}};
    const DenseMatrix<float> expected = {{13, 10, 34}, {12, 3, 33}, {28, 13, 66}};
    // act
    const DenseMatrix<float> result = subtract(a, multiply(b, c));
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed, given_f_dense_matrices_should_return_parenthesized_a_minus_b_times_c) {
    // arrange
    const DenseMatrix<float> a = {{9, 2, 6}, {13, 2, 8}, {6, 0, 10}};
    const DenseMatrix<float> b = {{8, 1, 3}, {8, 1, 4}, {3, 3, 5}};
    const DenseMatrix<float> c = {{1, 0, 3}, {8, 19, 5}, {9, 17, 5}};
    const DenseMatrix<float> expected = {{36, 70, 23}, {49, 87, 40}, {24, 28, 19}};
    // act
    const DenseMatrix<float> result = multiply(subtract(a, b), c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed, given_f_dense_matrices_should_return_a_times_b_minus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 1}, {0, 1, 0}, {2, 0, 1}};
    const DenseMatrix<float> b = {{5, 2, 1}, {1, 3, 0}, {4, 0, 2}};
    const DenseMatrix<float> c = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    // a * b = {{11, 8, 3}, {1, 3, 0}, {14, 4, 4}}
    const DenseMatrix<float> expected = {{10, 7, 2}, {0, 2, -1}, {13, 3, 3}};
    // act
    const DenseMatrix<float> result = subtract(multiply(a, b), c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed, given_f_dense_matrices_should_return_a_times_parenthesized_b_minus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 0, 2}, {0, 1, 0}, {3, 1, 1}};
    const DenseMatrix<float> b = {{10, 5, 8}, {6, 4, 2}, {8, 2, 6}};
    const DenseMatrix<float> c = {{8, 4, 5}, {5, 3, 1}, {7, 5, 1}};
    const DenseMatrix<float> expected = {{4, -5, 13}, {1, 1, 1}, {8, 1, 15}};
    // act
    const DenseMatrix<float> result = multiply(a, subtract(b, c));
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed, given_f_dense_matrices_should_return_a_times_b_plus_c) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; // Identity
    const DenseMatrix<float> c = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
    const DenseMatrix<float> expected = {{3, 4, 5}, {6, 7, 8}, {9, 10, 11}};
    // act
    const DenseMatrix<float> result = add(multiply(a, b), c);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}

TEST(dense_matrix_mixed, given_f_dense_matrices_should_return_a_times_parenthesized_b_plus_c) {
    // arrange
    const DenseMatrix<float> a = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    const DenseMatrix<float> expected = {{4, 6, 8}, {10, 12, 14}, {16, 18, 20}};
    // act
    const DenseMatrix<float> result = multiply(a, add(b, c));
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), result, expected));
}
