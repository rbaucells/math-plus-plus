#include "gtest/gtest.h"

#include "mathpp/matrix/dense/operators.h"

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
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], 14)));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], 15)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], 18)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], 19)));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], 20)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], 23)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], 24)));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 2], 25)));
}

TEST(dense_matrix_view_const_indexing_operator, given_index_should_return_const_reference_cf) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}}, {{11, 12}, {13, 14}, {15, 16}, {17, 18}, {19, 20}}, {{21, 22}, {23, 24}, {25, 26}, {27, 28}, {29, 30}}, {{31, 32}, {33, 34}, {35, 36}, {37, 38}, {39, 40}}, {{41, 42}, {43, 44}, {45, 46}, {47, 48}, {49, 50}}};
    const DenseMatrixView<std::complex<float>> v(a, 3, 3, 2, 2);
    // act / assert
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 0], std::complex<float>(25, 26))));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 1], std::complex<float>(27, 28))));
    ASSERT_TRUE((compare(Precision(0.001f), v[0, 2], std::complex<float>(29, 30))));

    ASSERT_TRUE((compare(Precision(0.001f), v[1, 0], std::complex<float>(35, 36))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 1], std::complex<float>(37, 38))));
    ASSERT_TRUE((compare(Precision(0.001f), v[1, 2], std::complex<float>(39, 40))));

    ASSERT_TRUE((compare(Precision(0.001f), v[2, 0], std::complex<float>(45, 46))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 1], std::complex<float>(47, 48))));
    ASSERT_TRUE((compare(Precision(0.001f), v[2, 2], std::complex<float>(49, 50))));
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
