#include "gtest/gtest.h"

#include "mathpp/math.h"

TEST(dense_lu_decomposition, given_non_singular_matrix_should_find_triangular_l_u) {
    // arrange
    const DenseMatrix<float> m = {{2, 1, 3}, {4, 4, 7}, {6, 7, 9}};
    const DenseMatrix<float> expectedL = {{1, 0, 0}, {2, 1, 0}, {3, 2, 1}};
    const DenseMatrix<float> expectedU = {{2, 1, 3}, {0, 2, 1}, {0, 0, -2}};
    // act
    auto [l, u] = lu_decomposition(m);
    // assert
    ASSERT_TRUE(compare(Precision(0.001f), l, expectedL));
    ASSERT_TRUE(compare(Precision(0.001f), u, expectedU));
}