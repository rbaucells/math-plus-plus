#include <ranges>
#include <flat_map>
#include <map>
#include <unordered_map>

#include "gtest/gtest.h"

#include "mathpp/implementation/vector/sparse/dok/traits.h"
#include "mathpp/implementation/vector/sparse/dok/view.h"

template<typename TValueType, bool TisComplex, typename GetterReturnType>
struct should_be_dok_sparse_vector_like {
    using ValueType = TValueType;
    static constexpr bool isComplex = TisComplex;

    [[nodiscard]] std::size_t n() const;
    [[nodiscard]] std::size_t nnz() const;

     [[nodiscard]] const std::flat_map<std::size_t, TValueType>& map() const;
     [[nodiscard]] std::map<std::size_t, TValueType>& map();

    [[nodiscard]] GetterReturnType get(std::size_t) const;
    void set(std::size_t, TValueType);
};

template<typename T>
struct ElementProxy {
    T element;

    operator T&() const {
        return element;
    }

    ElementProxy& operator=(const T& v) {
        element = v;
        return *this;
    }
};

template<typename T>
struct DokMapProxy {
    bool contains(std::size_t) const;
    T at(std::size_t) const;

    ElementProxy<T> operator[](std::size_t);
    T& at(std::size_t);

    std::size_t size() const;

    std::vector<std::pair<std::size_t, T>>::iterator begin();
    std::vector<std::pair<std::size_t, T>>::iterator end();
    std::vector<std::pair<std::size_t, T>>::const_iterator cbegin() const;
    std::vector<std::pair<std::size_t, T>>::const_iterator cend() const;
};

template<typename TValueType, bool TisComplex>
struct should_be_dok_sparse_vector_like_with_proxy {
    using ValueType = TValueType;
    static constexpr bool isComplex = TisComplex;

    [[nodiscard]] std::size_t n() const;
    [[nodiscard]] std::size_t nnz() const;

    [[nodiscard]] const DokMapProxy<TValueType> map() const;
    [[nodiscard]] DokMapProxy<TValueType> map();

    [[nodiscard]] ValueType get(std::size_t) const;
    void set(std::size_t, TValueType);
};

TEST(dok_sparse_vector_like, given_should_be_dok_sparse_vector_like_should_return_true_1) {
    static_assert(dok_sparse_vector_like<should_be_dok_sparse_vector_like<float, false, float>>);
}

TEST(dok_sparse_vector_like, given_should_be_dok_sparse_vector_like_should_return_true_2) {
    static_assert(dok_sparse_vector_like<should_be_dok_sparse_vector_like<float, true, const float&>>);
}

TEST(dok_sparse_vector_like, given_should_be_dok_sparse_vector_like_should_return_true_3) {
    static_assert(dok_sparse_vector_like<should_be_dok_sparse_vector_like<float, false, float&>>);
}

TEST(dok_sparse_vector_like, given_should_not_be_dok_sparse_vector_like_should_return_false_1) {
    static_assert(!dok_sparse_vector_like<should_be_dok_sparse_vector_like<float, true, double>>);
}

TEST(dok_sparse_vector_like, given_should_be_dok_sparse_vector_like_with_proxy_should_return_true) {
    static_assert(dok_sparse_vector_like<should_be_dok_sparse_vector_like_with_proxy<float, false>>);
}

TEST(dok_sparse_vector_like, given_should_be_dok_sparse_vector_like_with_proxy_complex_should_return_true) {
    static_assert(dok_sparse_vector_like<should_be_dok_sparse_vector_like_with_proxy<std::complex<float>, true>>);
}

TEST(is_dok_sparse_vector_like_v, given_should_be_dok_sparse_vector_like_should_return_true) {
    static_assert(is_dok_sparse_vector_like_v<should_be_dok_sparse_vector_like<float, true, const float&>>);
}

TEST(is_dok_sparse_vector_like_v, given_should_not_be_dok_sparse_vector_like_should_return_false) {
    static_assert(!is_dok_sparse_vector_like_v<should_be_dok_sparse_vector_like<float, true, double>>);
}

TEST(is_dok_sparse_vector_like, given_should_be_dok_sparse_vector_like_should_return_true) {
    static_assert(is_dok_sparse_vector_like<should_be_dok_sparse_vector_like<float, true, const float&>>::value);
}

TEST(is_dok_sparse_vector_like, given_should_not_be_dok_sparse_vector_like_should_return_false) {
    static_assert(!is_dok_sparse_vector_like<should_be_dok_sparse_vector_like<float, true, double>>::value);
}

TEST(is_sparse_vector, given_sparse_vector_should_return_true) {
    static_assert(is_dok_sparse_vector<DokSparseVector<float>>::value);
}

TEST(is_sparse_vector, given_sparse_vector_view_should_return_false) {
    static_assert(!is_dok_sparse_vector<DokSparseVectorView<float>>::value);
}

TEST(is_sparse_vector, given_dok_sparse_vector_like_should_return_false) {
    static_assert(!is_dok_sparse_vector<should_be_dok_sparse_vector_like<float, false, float&>>::value);
}

TEST(is_sparse_vector_v, given_sparse_vector_should_return_true) {
    static_assert(is_dok_sparse_vector_v<DokSparseVector<float>>);
}

TEST(is_sparse_vector_v, given_sparse_vector_view_should_return_false) {
    static_assert(!is_dok_sparse_vector_v<DokSparseVectorView<float>>);
}

TEST(is_sparse_vector_v, given_dok_sparse_vector_like_should_return_false) {
    static_assert(!is_dok_sparse_vector_v<should_be_dok_sparse_vector_like<float, false, float&>>);
}

TEST(sparse_vector, given_sparse_vector_should_return_true) {
    static_assert(dok_sparse_vector<DokSparseVector<float>>);
}

TEST(sparse_vector, given_sparse_vector_view_should_return_false) {
    static_assert(!dok_sparse_vector<DokSparseVectorView<float>>);
}

TEST(sparse_vector, given_dok_sparse_vector_like_should_return_false) {
    static_assert(!dok_sparse_vector<should_be_dok_sparse_vector_like<float, false, float&>>);
}

TEST(is_dok_sparse_vector_view, given_sparse_vector_view_should_return_true) {
    static_assert(is_dok_sparse_vector_view<DokSparseVectorView<float>>::value);
}

TEST(is_dok_sparse_vector_view, given_sparse_vector_should_return_false) {
    static_assert(!is_dok_sparse_vector_view<DokSparseVector<float>>::value);
}

TEST(is_dok_sparse_vector_view, given_dok_sparse_vector_like_should_return_false) {
    static_assert(!is_dok_sparse_vector_view<should_be_dok_sparse_vector_like<float, false, float&>>::value);
}

TEST(is_dok_sparse_vector_view_v, given_sparse_vector_view_should_return_true) {
    static_assert(is_dok_sparse_vector_view_v<DokSparseVectorView<float>>);
}

TEST(is_dok_sparse_vector_view_v, given_sparse_vector_should_return_false) {
    static_assert(!is_dok_sparse_vector_view_v<DokSparseVector<float>>);
}

TEST(is_dok_sparse_vector_view_v, given_dok_sparse_vector_like_should_return_false) {
    static_assert(!is_dok_sparse_vector_view_v<should_be_dok_sparse_vector_like<float, false, float&>>);
}

TEST(dok_sparse_vector_view, given_dok_sparse_vector_view_should_return_true) {
    static_assert(dok_sparse_vector_view<DokSparseVectorView<float>>);
}

TEST(dok_sparse_vector_view, given_dok_sparse_vector_should_return_false) {
    static_assert(!dok_sparse_vector_view<DokSparseVector<float>>);
}

TEST(dok_sparse_vector_view, given_dok_sparse_vector_like_should_return_false) {
    static_assert(!dok_sparse_vector_view<should_be_dok_sparse_vector_like<float, false, float&>>);
}
