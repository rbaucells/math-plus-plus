#include "gtest/gtest.h"

#include "mathpp/vector/sparse/coo/core.h"
#include "mathpp/vector/dense/core.h"

#pragma region coo_sparse_vector
TEST(coo_sparse_vector, given_coo_sparse_vector_should_return_true) {
    static_assert(coo_sparse_vector<CooSparseVector<float>>, "coo_sparse_vector is wrong, 'CooSparseVector<float>' should be coo_sparse_vector");
}

TEST(coo_sparse_vector, given_coo_sparse_vector_view_should_return_false) {
    static_assert(!coo_sparse_vector<CooSparseVectorView<float>>, "coo_sparse_vector is wrong, 'CooSparseVectorView<float>' should not be coo_sparse_vector");
}
#pragma endregion
#pragma region coo_sparse_vector_view
TEST(coo_sparse_vector_view, given_coo_sparse_vector_view_should_return_true) {
    static_assert(coo_sparse_vector_view<CooSparseVectorView<float>>, "coo_sparse_vector_view is wrong, 'CooSparseVectorView<float>' should be coo_sparse_vector_view");
}

TEST(coo_sparse_vector_view, given_coo_sparse_vector_should_return_false) {
    static_assert(!coo_sparse_vector_view<CooSparseVector<float>>, "coo_sparse_vector_view is wrong, 'CooSparseVector<float>' should not be coo_sparse_vector_view");
}
#pragma endregion
