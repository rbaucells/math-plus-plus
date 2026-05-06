#include "gtest/gtest.h"

#include "mathpp/vector/sparse/common/operators.h"

#pragma region constructor
TEST(sparse_vector_view_constructor, given_f_sparse_vector_should_construct) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(1, 1);
    a.set(2, 2);
    a.set(3, 3);
    CooSparseVector<float> expected(3);
    expected.set(0, 1);
    expected.set(1, 2);
    expected.set(2, 3);
    // act
    const CooSparseVectorView<float> v(a, 3, 1);
    // assert
    ASSERT_TRUE((compare(v.n(), 3)));
    ASSERT_TRUE((compare(v.offset(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), v, expected)));
}

TEST(sparse_vector_view_constructor, given_cf_sparse_vector_should_construct) {
    // arrange
    CooSparseVector<std::complex<float>> a(5);
    a.set(1, {1, 2});
    a.set(2, {3, 4});
    a.set(3, {5, 6});
    CooSparseVector<std::complex<float>> expected(3);
    expected.set(0, {1, 2});
    expected.set(1, {3, 4});
    expected.set(2, {5, 6});
    // act
    const CooSparseVectorView<std::complex<float>> v(a, 3, 1);
    // assert
    ASSERT_TRUE((compare(v.n(), 3)));
    ASSERT_TRUE((compare(v.offset(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), v, expected)));
}
#pragma endregion
#pragma region copy_constructor
TEST(sparse_vector_view_copy_constructor, given_f_sparse_vector_view_should_copy) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(1, 1);
    a.set(2, 2);
    a.set(3, 3);
    const CooSparseVectorView<float> v(a, 3, 1);
    // act
    const CooSparseVectorView<float> newView = v;
    // assert
    ASSERT_TRUE((compare(newView.n(), 3)));
    ASSERT_TRUE((compare(newView.offset(), 1)));
    ASSERT_TRUE(&v.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), v, newView)));
}

TEST(sparse_vector_view_copy_constructor, given_cf_sparse_vector_view_should_copy) {
    // arrange
    CooSparseVector<std::complex<float>> a(5);
    a.set(1, {1, 2});
    a.set(2, {3, 4});
    a.set(3, {5, 6});
    const CooSparseVectorView<std::complex<float>> v(a, 3, 1);
    // act
    const CooSparseVectorView<std::complex<float>> newView = v;
    // assert
    ASSERT_TRUE((compare(newView.n(), 3)));
    ASSERT_TRUE((compare(newView.offset(), 1)));
    ASSERT_TRUE(&v.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), v, newView)));
}
#pragma endregion
#pragma region set
TEST(sparse_vector_view_set, given_index_should_throw) {
    // arrange
    CooSparseVector<float> a(5);
    CooSparseVectorView<float> v(a, 3, 1);
    // act
    ASSERT_THROW(v.set(0, 1), InvalidOperationException);
}

TEST(sparse_vector_view_set, given_big_index_should_throw_1) {
    // arrange
    CooSparseVector<float> a(5);
    CooSparseVectorView<float> v(a, 3, 2);
    // act
    ASSERT_THROW(v.set(3, 1), InvalidIndexException);
}
#pragma endregion
#pragma region get
TEST(sparse_vector_view_get, given_index_should_return_value_f) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(2, 1);
    CooSparseVectorView<float> v(a, 3, 1);
    // act
    const float value = v.get(1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, 1)));
}

TEST(sparse_vector_view_get, given_index_should_return_value_cf) {
    // arrange
    CooSparseVector<std::complex<float>> a(5);
    a.set(2, {1, 2});
    CooSparseVectorView<std::complex<float>> v(a, 3, 1);
    // act
    const std::complex<float> value = v.get(1);
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), value, std::complex<float>(1, 2))));
}

TEST(sparse_vector_view_get, given_big_index_should_throw_f_1) {
    // arrange
    CooSparseVector<float> a(5);
    CooSparseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(3), InvalidIndexException);
}

TEST(sparse_vector_view_get, given_big_index_should_throw_f_2) {
    // arrange
    CooSparseVector<float> a(5);
    CooSparseVectorView<float> v(a, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v.get(3), InvalidIndexException);
}
#pragma endregion
#pragma region nnz
TEST(sparse_vector_nnz, should_return_nnz_1) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(1, 1);
    CooSparseVectorView<float> v(a, 3, 1);
    // act
    const std::size_t nnz = v.nnz();
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
}

TEST(sparse_vector_nnz, should_return_nnz_2) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(1, 1);
    a.set(0, 2);
    CooSparseVectorView<float> v(a, 3, 1);
    // act
    const std::size_t nnz = v.nnz();
    // assert
    ASSERT_TRUE((compare(nnz, 1)));
}

TEST(sparse_vector_nnz, should_return_zero_1) {
    // arrange
    CooSparseVector<float> a(5);
    CooSparseVectorView<float> v(a, 3, 1);
    // act
    const std::size_t nnz = v.nnz();
    // assert
    ASSERT_TRUE((compare(nnz, 0)));
}

TEST(sparse_vector_nnz, should_return_zero_2) {
    // arrange
    CooSparseVector<float> a(5);
    a.set(0, 2);
    CooSparseVectorView<float> v(a, 3, 1);
    // act
    const std::size_t nnz = v.nnz();
    // assert
    ASSERT_TRUE((compare(nnz, 0)));
}
#pragma endregion
#pragma region offset
TEST(sparse_vector_view_offset, should_return_offset) {
    // arrange
    const CooSparseVector<float> a(5);
    const CooSparseVectorView<float> v(a, 3, 1);
    constexpr std::size_t expected = 1;
    // act
    const std::size_t offset = v.offset();
    // assert
    ASSERT_TRUE((compare(offset, expected)));
}
#pragma endregion
#pragma region owner
TEST(sparse_vector_view_owner, should_return_owner) {
    // arrange
    const CooSparseVector<float> a(5);
    const CooSparseVectorView<float> v(a, 3, 1);
    // act
    const CooSparseVector<float>& owner = v.owner();
    // assert
    ASSERT_TRUE(&owner == &a);
}
#pragma endregion
