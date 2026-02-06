#include "gtest/gtest.h"

#include "mathpp/math.h"

#pragma region dense_matrix_base
TEST(dense_matrix_base, given_dense_matrix_should_return_true) {
    static_assert(dense_matrix_base<DenseMatrix<float>>, "dense_matrix_base is wrong, 'DenseMatrix<float>' should be dense_matrix_base");
}

TEST(dense_matrix_base, given_dense_matrix_view_should_return_true) {
    static_assert(dense_matrix_base<DenseMatrixView<float>>, "dense_matrix_base is wrong, 'DenseMatrixView<float>' should be dense_matrix_base");
}

TEST(dense_matrix_base, given_custom_dense_matrix_should_return_true) {
    static_assert(dense_matrix_base<CustomDenseMatrix<float>>, "dense_matrix_base is wrong, 'CustomDenseMatrix<float>' should be dense_matrix_base");
}

TEST(dense_matrix_base, given_float_should_return_false) {
    static_assert(!dense_matrix_base<float>, "dense_matrix_base is wrong, 'float' should not be dense_matrix_base");
}

TEST(dense_matrix_base, given_sparse_matrix_should_return_false) {
    static_assert(!dense_matrix_base<SparseMatrix<float>>, "dense_matrix_base is wrong, 'SparseMatrix<float>' should not be dense_matrix_base");
}
#pragma endregion
#pragma region dense_matrix
TEST(dense_matrix, given_dense_matrix_should_return_true) {
    static_assert(dense_matrix<DenseMatrix<float>>, "dense_matrix is wrong, 'DenseMatrix<float>' should be dense_matrix");
}

TEST(dense_matrix, given_dense_matrix_view_should_return_false) {
    static_assert(!dense_matrix<DenseMatrixView<float>>, "dense_matrix is wrong, 'DenseMatrixView<float>' should not be dense_matrix");
}

TEST(dense_matrix, given_custom_dense_matrix_should_return_false) {
    static_assert(!dense_matrix<CustomDenseMatrix<float>>, "dense_matrix is wrong, 'CustomDenseMatrix<float>' should not be dense_matrix");
}

TEST(dense_matrix, given_dense_matrix_base_should_return_false) {
    static_assert(!dense_matrix<DenseMatrixBase<float>>, "dense_matrix is wrong, 'DenseMatrixBase<float>' should not be dense_matrix");
}
#pragma endregion
#pragma region dense_matrix_view
TEST(dense_matrix_view, given_dense_matrix_view_should_return_true) {
    static_assert(dense_matrix_view<DenseMatrixView<float>>, "dense_matrix_view is wrong, 'DenseMatrixView<float>' should be dense_matrix_view");
}

TEST(dense_matrix_view, given_dense_matrix_should_return_false) {
    static_assert(!dense_matrix_view<DenseMatrix<float>>, "dense_matrix_view is wrong, 'DenseMatrix<float>' should not be dense_matrix_view");
}

TEST(dense_matrix_view, given_custom_dense_matrix_should_return_false) {
    static_assert(!dense_matrix_view<CustomDenseMatrix<float>>, "dense_matrix_view is wrong, 'CustomDenseMatrix<float>' should not be dense_matrix_view");
}

TEST(dense_matrix_view, given_dense_matrix_base_should_return_false) {
    static_assert(!dense_matrix_view<DenseMatrixBase<float>>, "dense_matrix_view is wrong, 'DenseMatrixBase<float>' should not be dense_matrix_view");
}
#pragma endregion
#pragma region custom_dense_matrix
TEST(custom_dense_matrix, given_custom_dense_matrix_should_return_true) {
    static_assert(custom_dense_matrix<CustomDenseMatrix<float>>, "custom_dense_matrix is wrong, 'CustomDenseMatrix<float>' should be custom_dense_matrix");
}

TEST(custom_dense_matrix, given_dense_matrix_should_return_false) {
    static_assert(!custom_dense_matrix<DenseMatrix<float>>, "custom_dense_matrix is wrong, 'DenseMatrix<float>' should not be custom_dense_matrix");
}

TEST(custom_dense_matrix, given_dense_matrix_view_should_return_false) {
    static_assert(!custom_dense_matrix<DenseMatrixView<float>>, "custom_dense_matrix is wrong, 'DenseMatrixView<float>' should not be custom_dense_matrix");
}

TEST(custom_dense_matrix, given_dense_matrix_base_should_return_false) {
    static_assert(!custom_dense_matrix<DenseMatrixBase<float>>, "custom_dense_matrix is wrong, 'DenseMatrixBase<float>' should not be custom_dense_matrix");
}
#pragma endregion
#pragma region underlying_type
TEST(underlying_type, given_dense_matrix_base_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<DenseMatrixBase<float>>, float>, "underlying_type_t is wrong, 'DenseMatrixBase<float>' should be 'float'");
}

TEST(underlying_type, given_dense_matrix_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<DenseMatrix<float>>, float>, "underlying_type_t is wrong, 'DenseMatrix<float>' should be 'float'");
}

TEST(underlying_type, given_dense_matrix_view_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<DenseMatrixView<float>>, float>, "underlying_type_t is wrong, 'DenseMatrixView<float>' should be 'float'");
}

TEST(underlying_type, given_custom_dense_matrix_templated_on_float_should_return_float) {
    static_assert(std::is_same_v<underlying_type_t<CustomDenseMatrix<float>>, float>, "underlying_type_t is wrong, 'CustomDenseMatrix<float>' should be 'float'");
}
#pragma endregion
#pragma region assert_same_dimensions
TEST(assert_same_dimensions, given_dense_matrixes_templated_on_float_of_same_dimensions_should_not_throw) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> c = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // act / assert
    ASSERT_NO_THROW(assert_same_dimensions(a, b, c));
}

TEST(assert_same_dimensions, given_dense_matrixes_templated_on_float_int_and_complex_float_of_same_dimensions_should_not_throw) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<int> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act / assert
    ASSERT_NO_THROW(assert_same_dimensions(a, b, c));
}

TEST(assert_same_dimensions, given_dense_matrixes_templated_on_float_of_same_dimensions_should_throw) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<float> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    const DenseMatrix<float> c = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    // act / assert
    ASSERT_THROW(assert_same_dimensions(a, b, c), InvalidDimensionException);
}

TEST(assert_same_dimensions, given_dense_matrixes_templated_on_float_int_and_complex_float_of_different_dimensions_should_throw) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const DenseMatrix<int> b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    const DenseMatrix<std::complex<float>> c = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}}, {{9, 10}, {11, 12}, {13, 14}, {15, 16}}, {{17, 18}, {19, 20}, {21, 22}, {23, 24}}};
    // act / assert
    ASSERT_THROW(assert_same_dimensions(a, b, c), InvalidDimensionException);
}
#pragma endregion
#pragma region assert_square
TEST(assert_square, given_square_dense_matrix_templated_on_float_should_return_true) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5,6}, {7, 8, 9}};
    // act / assert
    ASSERT_NO_THROW(assert_square(a));
}

TEST(assert_square, given_square_dense_matrix_templated_on_complex_float_should_return_true) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}}, {{7, 8}, {9, 10}, {11, 12}}, {{13, 14}, {15, 16}, {17, 18}}};
    // act / assert
    ASSERT_NO_THROW(assert_square(a));
}

TEST(assert_square, given_non_square_dense_matrix_templated_on_float_should_return_false) {
    // arrange
    const DenseMatrix<float> a = {{1, 2, 3}, {4, 5,6}, {7, 8, 9}, {10, 11, 12}};
    // act / assert
    ASSERT_THROW(assert_square(a), InvalidDimensionException);
}

TEST(assert_square, given_non_square_dense_matrix_templated_on_complex_float_should_return_false) {
    // arrange
    const DenseMatrix<std::complex<float>> a = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}}, {{9, 10}, {11, 12}, {13, 14}, {15, 16}}, {{17, 18}, {19, 20}, {21, 22}, {23, 24}}};
    // act / assert
    ASSERT_THROW(assert_square(a), InvalidDimensionException);
}
#pragma endregion