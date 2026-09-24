#include <ranges>

#include "gtest/gtest.h"

#include "mathpp/implementation/vector/sparse/coo/traits.h"
#include "mathpp/implementation/vector/sparse/coo/view.h"

template<typename TValueType, bool TisComplex, typename GetterReturnType>
struct should_be_coo_sparse_vector_like {
    using ValueType = TValueType;
    static constexpr bool isComplex = TisComplex;

    [[nodiscard]] std::size_t n() const;
    [[nodiscard]] std::size_t nnz() const;


     [[nodiscard]] std::span<const std::size_t> indices() const;
     [[nodiscard]] std::span<std::size_t> indices();

    [[nodiscard]] std::span<const TValueType> values() const;
    [[nodiscard]] std::span<TValueType> values();

    [[nodiscard]] GetterReturnType get(std::size_t) const;
    void set(std::size_t, TValueType);
};

template<typename TValueType, bool TisComplex>
struct should_be_coo_sparse_vector_like_with_proxy {
    using ValueType = TValueType;
    static constexpr bool isComplex = TisComplex;

    [[nodiscard]] std::size_t n() const;
    [[nodiscard]] std::size_t nnz() const;

    [[nodiscard]] decltype(std::views::iota(0, 5) | std::views::transform([](std::size_t) -> std::size_t {})) indices() const;
    [[nodiscard]] decltype(std::views::iota(0, 5) | std::views::transform([](std::size_t) -> std::size_t& {})) indices();

    [[nodiscard]] decltype(std::views::iota(0, 5) | std::views::transform([](std::size_t) -> TValueType {})) values() const;
    [[nodiscard]] decltype(std::views::iota(0, 5) | std::views::transform([](std::size_t) -> TValueType& {})) values();

    [[nodiscard]] ValueType get(std::size_t) const;
    void set(std::size_t, TValueType);
};

TEST(coo_sparse_vector_like, given_should_be_coo_sparse_vector_like_should_return_true_1) {
    static_assert(coo_sparse_vector_like<should_be_coo_sparse_vector_like<float, false, float>>);
}

TEST(coo_sparse_vector_like, given_should_be_coo_sparse_vector_like_should_return_true_2) {
    static_assert(coo_sparse_vector_like<should_be_coo_sparse_vector_like<float, true, const float&>>);
}

TEST(coo_sparse_vector_like, given_should_be_coo_sparse_vector_like_should_return_true_3) {
    static_assert(coo_sparse_vector_like<should_be_coo_sparse_vector_like<float, false, float&>>);
}

TEST(coo_sparse_vector_like, given_should_not_be_coo_sparse_vector_like_should_return_false_1) {
    static_assert(!coo_sparse_vector_like<should_be_coo_sparse_vector_like<float, true, double>>);
}

TEST(coo_sparse_vector_like, given_should_be_coo_sparse_vector_like_with_proxy_should_return_true) {
    static_assert(coo_sparse_vector_like<should_be_coo_sparse_vector_like_with_proxy<float, false>>);
}

TEST(coo_sparse_vector_like, given_should_be_coo_sparse_vector_like_with_proxy_complex_should_return_true) {
    static_assert(coo_sparse_vector_like<should_be_coo_sparse_vector_like_with_proxy<std::complex<float>, true>>);
}

TEST(is_coo_sparse_vector_like_v, given_should_be_coo_sparse_vector_like_should_return_true) {
    static_assert(is_coo_sparse_vector_like_v<should_be_coo_sparse_vector_like<float, true, const float&>>);
}

TEST(is_coo_sparse_vector_like_v, given_should_not_be_coo_sparse_vector_like_should_return_false) {
    static_assert(!is_coo_sparse_vector_like_v<should_be_coo_sparse_vector_like<float, true, double>>);
}

TEST(is_coo_sparse_vector_like, given_should_be_coo_sparse_vector_like_should_return_true) {
    static_assert(is_coo_sparse_vector_like<should_be_coo_sparse_vector_like<float, true, const float&>>::value);
}

TEST(is_coo_sparse_vector_like, given_should_not_be_coo_sparse_vector_like_should_return_false) {
    static_assert(!is_coo_sparse_vector_like<should_be_coo_sparse_vector_like<float, true, double>>::value);
}

TEST(is_sparse_vector, given_sparse_vector_should_return_true) {
    static_assert(is_coo_sparse_vector<CooSparseVector<float>>::value);
}

TEST(is_sparse_vector, given_sparse_vector_view_should_return_false) {
    static_assert(!is_coo_sparse_vector<CooSparseVectorView<float>>::value);
}

TEST(is_sparse_vector, given_coo_sparse_vector_like_should_return_false) {
    static_assert(!is_coo_sparse_vector<should_be_coo_sparse_vector_like<float, false, float&>>::value);
}

TEST(is_sparse_vector_v, given_sparse_vector_should_return_true) {
    static_assert(is_coo_sparse_vector_v<CooSparseVector<float>>);
}

TEST(is_sparse_vector_v, given_sparse_vector_view_should_return_false) {
    static_assert(!is_coo_sparse_vector_v<CooSparseVectorView<float>>);
}

TEST(is_sparse_vector_v, given_coo_sparse_vector_like_should_return_false) {
    static_assert(!is_coo_sparse_vector_v<should_be_coo_sparse_vector_like<float, false, float&>>);
}

TEST(sparse_vector, given_sparse_vector_should_return_true) {
    static_assert(coo_sparse_vector<CooSparseVector<float>>);
}

TEST(sparse_vector, given_sparse_vector_view_should_return_false) {
    static_assert(!coo_sparse_vector<CooSparseVectorView<float>>);
}

TEST(sparse_vector, given_coo_sparse_vector_like_should_return_false) {
    static_assert(!coo_sparse_vector<should_be_coo_sparse_vector_like<float, false, float&>>);
}

TEST(is_coo_sparse_vector_view, given_sparse_vector_view_should_return_true) {
    static_assert(is_coo_sparse_vector_view<CooSparseVectorView<float>>::value);
}

TEST(is_coo_sparse_vector_view, given_sparse_vector_should_return_false) {
    static_assert(!is_coo_sparse_vector_view<CooSparseVector<float>>::value);
}

TEST(is_coo_sparse_vector_view, given_coo_sparse_vector_like_should_return_false) {
    static_assert(!is_coo_sparse_vector_view<should_be_coo_sparse_vector_like<float, false, float&>>::value);
}

TEST(is_coo_sparse_vector_view_v, given_sparse_vector_view_should_return_true) {
    static_assert(is_coo_sparse_vector_view_v<CooSparseVectorView<float>>);
}

TEST(is_coo_sparse_vector_view_v, given_sparse_vector_should_return_false) {
    static_assert(!is_coo_sparse_vector_view_v<CooSparseVector<float>>);
}

TEST(is_coo_sparse_vector_view_v, given_coo_sparse_vector_like_should_return_false) {
    static_assert(!is_coo_sparse_vector_view_v<should_be_coo_sparse_vector_like<float, false, float&>>);
}

TEST(sparse_vector_view, given_sparse_vector_view_should_return_true) {
    static_assert(coo_sparse_vector_view<CooSparseVectorView<float>>);
}

TEST(sparse_vector_view, given_sparse_vector_should_return_false) {
    static_assert(!coo_sparse_vector_view<CooSparseVector<float>>);
}

TEST(sparse_vector_view, given_coo_sparse_vector_like_should_return_false) {
    static_assert(!coo_sparse_vector_view<should_be_coo_sparse_vector_like<float, false, float&>>);
}
