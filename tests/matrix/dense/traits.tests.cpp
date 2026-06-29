#include "gtest/gtest.h"

#include "mathpp/implementation/matrix/dense/traits.h"

template<typename TValueType, bool TisComplex, typename GetterReturnType>
struct should_be_dense_matrix_like {
    using ValueType = TValueType;
    static constexpr bool isComplex = TisComplex;

    [[nodiscard]] std::size_t rows() const;
    [[nodiscard]] std::size_t columns() const;

    [[nodiscard]] GetterReturnType at(std::size_t, std::size_t) const;
    [[nodiscard]] GetterReturnType operator[](std::size_t, std::size_t) const;

    [[nodiscard]] GetterReturnType data(std::size_t) const;
};

TEST(dense_matrix_like, given_should_be_dense_matrix_like_should_return_true_1) {
    static_assert(dense_matrix_like<should_be_dense_matrix_like<float, false, float>>);
}

TEST(dense_matrix_like, given_should_be_dense_matrix_like_should_return_true_2) {
    static_assert(dense_matrix_like<should_be_dense_matrix_like<float, true, const float&>>);
}

TEST(dense_matrix_like, given_should_be_dense_matrix_like_should_return_true_3) {
    static_assert(dense_matrix_like<should_be_dense_matrix_like<float, false, float&>>);
}

TEST(dense_matrix_like, given_should_not_be_dense_matrix_like_should_return_false_1) {
    static_assert(!dense_matrix_like<should_be_dense_matrix_like<float, true, double>>);
}

TEST(is_dense_matrix_like_v, given_should_be_dense_matrix_like_should_return_true) {
    static_assert(is_dense_matrix_like_v<should_be_dense_matrix_like<float, true, const float&>>);
}

TEST(is_dense_matrix_like_v, given_should_not_be_dense_matrix_like_should_return_false) {
    static_assert(!is_dense_matrix_like_v<should_be_dense_matrix_like<float, true, double>>);
}

TEST(is_dense_matrix_like, given_should_be_dense_matrix_like_should_return_true) {
    static_assert(is_dense_matrix_like<should_be_dense_matrix_like<float, true, const float&>>::value);
}

TEST(is_dense_matrix_like, given_should_not_be_dense_matrix_like_should_return_false) {
    static_assert(!is_dense_matrix_like<should_be_dense_matrix_like<float, true, double>>::value);
}

TEST(is_dense_matrix, given_dense_matrix_should_return_true) {
    static_assert(is_dense_matrix<DenseMatrix<float>>::value);
}

TEST(is_dense_matrix, given_dense_matrix_view_should_return_false) {
    static_assert(!is_dense_matrix<DenseMatrixView<float>>::value);
}

TEST(is_dense_matrix, given_dense_matrix_like_should_return_false) {
    static_assert(!is_dense_matrix<should_be_dense_matrix_like<float, false, float&>>::value);
}

TEST(is_dense_matrix_v, given_dense_matrix_should_return_true) {
    static_assert(is_dense_matrix_v<DenseMatrix<float>>);
}

TEST(is_dense_matrix_v, given_dense_matrix_view_should_return_false) {
    static_assert(!is_dense_matrix_v<DenseMatrixView<float>>);
}

TEST(is_dense_matrix_v, given_dense_matrix_like_should_return_false) {
    static_assert(!is_dense_matrix_v<should_be_dense_matrix_like<float, false, float&>>);
}

TEST(dense_matrix, given_dense_matrix_should_return_true) {
    static_assert(dense_matrix<DenseMatrix<float>>);
}

TEST(dense_matrix, given_dense_matrix_view_should_return_false) {
    static_assert(!dense_matrix<DenseMatrixView<float>>);
}

TEST(dense_matrix, given_dense_matrix_like_should_return_false) {
    static_assert(!dense_matrix<should_be_dense_matrix_like<float, false, float&>>);
}

TEST(is_dense_matrix_view, given_dense_matrix_view_should_return_true) {
    static_assert(is_dense_matrix_view<DenseMatrixView<float>>::value);
}

TEST(is_dense_matrix_view, given_dense_matrix_should_return_false) {
    static_assert(!is_dense_matrix_view<DenseMatrix<float>>::value);
}

TEST(is_dense_matrix_view, given_dense_matrix_like_should_return_false) {
    static_assert(!is_dense_matrix_view<should_be_dense_matrix_like<float, false, float&>>::value);
}

TEST(is_dense_matrix_view_v, given_dense_matrix_view_should_return_true) {
    static_assert(is_dense_matrix_view_v<DenseMatrixView<float>>);
}

TEST(is_dense_matrix_view_v, given_dense_matrix_should_return_false) {
    static_assert(!is_dense_matrix_view_v<DenseMatrix<float>>);
}

TEST(is_dense_matrix_view_v, given_dense_matrix_like_should_return_false) {
    static_assert(!is_dense_matrix_view_v<should_be_dense_matrix_like<float, false, float&>>);
}

TEST(dense_matrix_view, given_dense_matrix_view_should_return_true) {
    static_assert(dense_matrix_view<DenseMatrixView<float>>);
}

TEST(dense_matrix_view, given_dense_matrix_should_return_false) {
    static_assert(!dense_matrix_view<DenseMatrix<float>>);
}

TEST(dense_matrix_view, given_dense_matrix_like_should_return_false) {
    static_assert(!dense_matrix_view<should_be_dense_matrix_like<float, false, float&>>);
}
