#include "gtest/gtest.h"

#include "mathpp/math.h"

#pragma region dense_vector
#pragma region indexing_operator
TEST(dense_vector_indexing_operator, given_index_should_return_reference_f) {
    // arrange
    DenseVector<float> v(3, false);
    // act
    float& v0 = v[0];
    v0 = 1;
    float& v1 = v[1];
    v1 = 2;
    float& v2 = v[2];
    v2 = 3;
    const float* data = v.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), data[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), data[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), data[2], 3)));
}

TEST(dense_vector_indexing_operator, given_index_should_return_reference_cf) {
    // arrange
    DenseVector<std::complex<float>> v(3, false);
    // act
    std::complex<float>& v0 = v[0];
    v0 = {1, 2};
    std::complex<float>& v1 = v[1];
    v1 = {3, 4};
    std::complex<float>& v2 = v[2];
    v2 = {5, 6};
    const std::complex<float>* data = v.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), data[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), data[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), data[2], std::complex<float>(5, 6))));
}

TEST(dense_vector_indexing_operator, given_negative_index_should_throw) {
    // arrange
    DenseVector<float> v = {1, 2, 3};
    // act / assert
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
}

TEST(dense_vector_indexing_operator, given_big_index_should_throw) {
    // arrange
    DenseVector<float> v = {1, 2, 3};
    // act / assert
    ASSERT_THROW(std::ignore = v[4], InvalidIndexException);
}
#pragma endregion
#pragma region const_indexing_operator
TEST(dense_vector_const_indexing_operator, given_index_should_return_const_reference_f) {
    // arrange
    const DenseVector<float> v = {1, 2, 3};
    const float* vData = v.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), vData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[2], 3)));
}

TEST(dense_vector_const_indexing_operator, given_index_should_return_const_reference_cf) {
    // arrange
    const DenseVector<std::complex<float>> v = {{1, 2}, {3, 4}, {5, 6}};
    const std::complex<float>* vData = v.data();
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), vData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[2], std::complex<float>(5, 6))));
}

TEST(dense_vector_const_indexing_operator, given_negative_index_should_throw) {
    // arrange
    const DenseVector<float> v = {1, 2, 3};
    // act / assert
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
}

TEST(dense_vector_const_indexing_operator, given_big_index_should_throw) {
    // arrange
    const DenseVector<float> v = {1, 2, 3};
    // act / assert
    ASSERT_THROW(std::ignore = v[4], InvalidIndexException);
}
#pragma endregion
#pragma region default_constructor
TEST(dense_vector_default_constructor, given_size_and_fill_should_construct_f) {
    // arrange / act
    const DenseVector<float> v(3, true);
    const float* vData = v.data();
    // assert
    ASSERT_TRUE((compare(v.n(), 3)));
    for (int i = 0; i < 3; i++) {
        ASSERT_TRUE((compare(Precision(0.001f), vData[i], 0)));
    }
}

TEST(dense_vector_default_constructor, given_size_and_fill_should_construct_cf) {
    // arrange / act
    const DenseVector<std::complex<float>> v(3, true);
    const std::complex<float>* vData = v.data();
    // assert
    ASSERT_TRUE((compare(v.n(), 3)));
    for (int i = 0; i < 3; i++) {
        ASSERT_TRUE((compare(Precision(0.001f), vData[i], std::complex<float>(0, 0))));
    }
}
#pragma endregion
#pragma region initializer_list_constructor
TEST(dense_vector_initializer_list_constructor, given_initializer_list_should_construct_f) {
    // arrange / act
    const DenseVector<float> v = {1, 2, 3};
    const float* vData = v.data();
    // assert
    ASSERT_TRUE((compare(v.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[2], 3)));
}

TEST(dense_vector_initializer_list_constructor, given_initializer_list_should_construct_cf) {
    // arrange / act
    const DenseVector<std::complex<float>> v = {{1, 2}, {3, 4}, {5, 6}};
    const std::complex<float>* vData = v.data();
    // assert
    ASSERT_TRUE((compare(v.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), vData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), vData[2], std::complex<float>(5, 6))));
}
#pragma endregion
#pragma region copy_constructor_from_same_type_dense_vector
TEST(dense_vector_copy_constructor_from_same_type_dense_vector, given_f_dense_vector_should_copy_construct) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    // act
    const DenseVector<float> b = a;
    const float* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}

TEST(dense_vector_copy_constructor_from_same_type_dense_vector, given_cf_dense_vector_should_copy_construct) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const DenseVector<std::complex<float>> b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(5, 6))));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_dense_vector
TEST(dense_vector_copy_constructor_from_different_type_dense_vector, given_f_dense_vector_should_copy_construct) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    // act
    const DenseVector<std::complex<float>> b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}
#pragma endregion
#pragma region copy_constructor_from_same_type_dense_vector_base
TEST(dense_vector_copy_constructor_from_same_type_dense_vector_base, given_f_dense_vector_base_should_copy_construct) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    // act
    const DenseVector<float> b = static_cast<const DenseVectorBase<float>&>(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}

TEST(dense_vector_copy_constructor_from_same_type_dense_vector_base, given_cf_dense_vector_base_should_copy_construct) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const DenseVector<std::complex<float>> b = static_cast<const DenseVectorBase<std::complex<float>>&>(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(5, 6))));
}
#pragma endregion
#pragma region copy_constructor_from_different_type_dense_vector_base
TEST(dense_vector_copy_constructor_from_different_type_dense_vector_base, given_f_dense_vector_base_should_copy_construct) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    // act
    const DenseVector<std::complex<float>> b = static_cast<const DenseVectorBase<float>&>(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}
#pragma endregion
#pragma region move_constructor
TEST(dense_vector_move_constructor, given_f_dense_vector_should_construct_and_leave_other_empty) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    // act
    const DenseVector<float> b = std::move(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}

TEST(dense_vector_move_constructor, given_cf_dense_vector_should_construct_and_leave_other_empty) {
    // arrange
    DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    // act
    const DenseVector<std::complex<float>> b = std::move(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(5, 6))));
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_dense_vector
TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_f_dense_vector_of_same_size_should_copy_assign) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    DenseVector<float> b(3, true);
    // act
    b = a;
    const float* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_cf_dense_vector_of_same_size_should_copy_assign) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    DenseVector<std::complex<float>> b(3, true);
    // act
    b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(5, 6))));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_f_dense_vector_of_diff_size_should_copy_assign) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    DenseVector<float> b(2, true);
    // act
    b = a;
    const float* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector, given_f_self_should_do_nothing) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    // act
    a = a;
    const float* aData = a.data();
    // assert
    ASSERT_TRUE((compare(a.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[2], 3)));
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_dense_vector
TEST(dense_vector_copy_assignment_operator_from_different_type_dense_vector, given_f_dense_vector_of_same_size_should_copy_assign) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    DenseVector<std::complex<float>> b(3, true);
    // act
    b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}

TEST(dense_vector_copy_assignment_operator_from_different_type_dense_vector, given_f_dense_vector_of_diff_size_should_copy_assign) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    DenseVector<std::complex<float>> b(2, true);
    // act
    b = a;
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(2, 0))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(3, 0))));
}
#pragma endregion
#pragma region copy_assignment_operator_from_same_type_dense_vector_base
TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector_base, given_f_dense_vector_base_of_same_size_should_copy_assign) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    DenseVector<float> b(3, true);
    // act
    b = static_cast<const DenseVectorBase<float>&>(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector_base, given_cf_dense_vector_base_of_same_size_should_copy_assign) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    DenseVector<std::complex<float>> b(3, true);
    // act
    b = static_cast<const DenseVectorBase<std::complex<float>>&>(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(5, 6))));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector_base, given_f_dense_vector_base_of_diff_size_should_copy_assign) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    DenseVector<float> b(2, true);
    // act
    b = static_cast<const DenseVectorBase<float>&>(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}

TEST(dense_vector_copy_assignment_operator_from_same_type_dense_vector_base, given_f_self_should_do_nothing) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    // act
    a = static_cast<const DenseVectorBase<float>&>(a);
    const float* aData = a.data();
    // assert
    ASSERT_TRUE((compare(a.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[2], 3)));
}
#pragma endregion
#pragma region copy_assignment_operator_from_different_type_dense_vector_base
TEST(dense_vector_copy_assignment_operator_from_different_type_dense_vector_base, given_f_dense_vector_base_of_same_size_should_copy_assign) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    DenseVector<std::complex<float>> b(3, true);
    // act
    b = static_cast<const DenseVectorBase<float>&>(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}

TEST(dense_vector_copy_assignment_operator_from_different_type_dense_vector_base, given_f_dense_vector_base_of_diff_size_should_copy_assign) {
    // arrange
    const DenseVector<float> a = {1, 2, 3};
    DenseVector<std::complex<float>> b(2, true);
    // act
    b = static_cast<const DenseVectorBase<float>&>(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE((compare(b.n(), 3)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}
#pragma endregion
#pragma region move_assignment_operator
TEST(dense_vector_move_assignment_operator, given_f_dense_vector_of_same_size_should_move_assign) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    DenseVector<float> b(3, true);
    // act
    b = std::move(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}

TEST(dense_vector_move_assignment_operator, given_cf_dense_vector_of_same_size_should_move_assign) {
    // arrange
    DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}};
    DenseVector<std::complex<float>> b(3, true);
    // act
    b = std::move(a);
    const std::complex<float>* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], std::complex<float>(1, 2))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], std::complex<float>(3, 4))));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], std::complex<float>(5, 6))));
}

TEST(dense_vector_move_assignment_operator, given_f_dense_vector_of_diff_size_should_move_assign) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    DenseVector<float> b(2, true);
    // act
    b = std::move(a);
    const float* bData = b.data();
    // assert
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_TRUE(compare(a.n(), 0));
    ASSERT_TRUE(compare(b.n(), 3));
    ASSERT_TRUE((compare(Precision(0.001f), bData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), bData[2], 3)));
}

TEST(dense_vector_move_assignment_operator, given_f_self_should_do_nothing) {
    // arrange
    DenseVector<float> a = {1, 2, 3};
    // act
    a = std::move(a);
    const float* aData = a.data();
    // assert
    ASSERT_TRUE(compare(a.n(), 3));
    ASSERT_TRUE((compare(Precision(0.001f), aData[0], 1)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[1], 2)));
    ASSERT_TRUE((compare(Precision(0.001f), aData[2], 3)));
}
#pragma endregion
#pragma endregion
#pragma region dense_vector_view
#pragma region constructor
TEST(dense_vector_view_constructor, given_f_dense_vector_should_construct) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVector<float> expected = {2, 3, 4};
    // act
    const DenseVectorView<float> view = DenseVectorView<float>(a, 3, 1);
    // assert
    ASSERT_TRUE((compare(view.n(), 3)));
    ASSERT_TRUE((compare(view.offset(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), view, expected)));
}

TEST(dense_vector_view_constructor, given_cf_dense_vector_should_construct) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    const DenseVector<std::complex<float>> expected = {{3, 4}, {5, 6}, {7, 8}};
    // act
    const DenseVectorView<std::complex<float>> view = DenseVectorView<std::complex<float>>(a, 3, 1);
    // assert
    ASSERT_TRUE((compare(view.n(), 3)));
    ASSERT_TRUE((compare(view.offset(), 1)));
    ASSERT_TRUE((compare(Precision(0.001f), view, expected)));
}
#pragma endregion
#pragma region copy_constructor
TEST(dense_vector_view_copy_constructor, given_f_dense_vector_view_should_copy) {
    // arrange
    const DenseVector<float> v = {1, 2, 3, 4, 5};
    const DenseVectorView<float> view(v, 3, 2);
    // act
    const DenseVectorView<float> newView = view;
    // assert
    ASSERT_TRUE((compare(newView.n(), 3)));
    ASSERT_TRUE((compare(newView.offset(), 2)));
    ASSERT_TRUE(&view.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), view, newView)));
}

TEST(dense_vector_view_copy_constructor, given_cf_dense_vector_view_should_copy) {
    // arrange
    const DenseVector<std::complex<float>> v = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    const DenseVectorView<std::complex<float>> view(v, 3, 2);
    // act
    const DenseVectorView<std::complex<float>> newView = view;
    // assert
    ASSERT_TRUE((compare(newView.n(), 3)));
    ASSERT_TRUE((compare(newView.offset(), 2)));
    ASSERT_TRUE(&view.owner() == &newView.owner());
    ASSERT_TRUE((compare(Precision(0.001f), view, newView)));
}
#pragma endregion
#pragma region indexing_operator
TEST(dense_vector_view_indexing_operator, given_index_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[2], InvalidOperationException);
}

TEST(dense_vector_view_indexing_operator, given_negative_index_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
}

TEST(dense_vector_view_indexing_operator, given_big_index_should_throw_1) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}

TEST(dense_vector_view_indexing_operator, given_big_index_should_throw_2) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}
#pragma endregion
#pragma region const_indexing_operator
TEST(dense_vector_view_const_indexing_operator, given_index_should_return_const_reference_f) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVectorView<float> v(a, 3, 2);
    // act
    const float& v0 = v[0];
    const float& v1 = v[1];
    const float& v2 = v[2];
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), v0, 3)));
    ASSERT_TRUE((compare(Precision(0.001f), v1, 4)));
    ASSERT_TRUE((compare(Precision(0.001f), v2, 5)));
}

TEST(dense_vector_view_const_indexing_operator, given_index_should_return_const_reference_cf) {
    // arrange
    const DenseVector<std::complex<float>> a = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    const DenseVectorView<std::complex<float>> v(a, 3, 2);
    // act
    const std::complex<float>& v0 = v[0];
    const std::complex<float>& v1 = v[1];
    const std::complex<float>& v2 = v[2];
    // assert
    ASSERT_TRUE((compare(Precision(0.001f), v0, std::complex<float>(5, 6))));
    ASSERT_TRUE((compare(Precision(0.001f), v1, std::complex<float>(7, 8))));
    ASSERT_TRUE((compare(Precision(0.001f), v2, std::complex<float>(9, 10))));
}

TEST(dense_vector_view_const_indexing_operator, given_negative_index_should_throw) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
}

TEST(dense_vector_view_const_indexing_operator, given_big_index_should_throw_1) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 2);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}

TEST(dense_vector_view_const_indexing_operator, given_big_index_should_throw_2) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    DenseVectorView<float> v(a, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[3], InvalidIndexException);
}
#pragma endregion
#pragma region offset
TEST(dense_vector_view_offset, should_return_offset) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVectorView<float> v(a, 3, 1);
    constexpr int expected = 1;
    // act
    const int offset = v.offset();
    // assert
    ASSERT_TRUE((compare(offset, expected)));
}
#pragma endregion
#pragma region owner
TEST(dense_vector_view_owner, should_return_owner) {
    // arrange
    const DenseVector<float> a = {1, 2, 3, 4, 5};
    const DenseVectorView<float> v(a, 3, 1);
    // act
    const DenseVector<float>& owner = v.owner();
    // assert
    ASSERT_TRUE(&owner == &a);
}
#pragma endregion
#pragma endregion
#pragma region custom_dense_vector
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

TEST(custom_dense_vector_index_operator, given_negative_index_should_throw) {
    // arrange
    float* data = new float[3];
    CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
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

TEST(custom_dense_vector_const_index_operator, given_negative_index_should_throw) {
    // arrange
    float* data = new float[3];
    const CustomDenseVector<float> v(data, 3, 1);
    // act / assert
    ASSERT_THROW(std::ignore = v[-1], InvalidIndexException);
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
#pragma endregion
