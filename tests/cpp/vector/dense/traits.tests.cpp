#include "gtest/gtest.h"

#include "mathpp/implementation/vector/dense/traits.h"

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

template<typename TValueType, bool TisComplex, typename GetterReturnType>
struct should_be_dense_vector_like {
    using ValueType = TValueType;
    static constexpr bool isComplex = TisComplex;

    [[nodiscard]] std::size_t n() const;

    [[nodiscard]] GetterReturnType get(std::size_t) const;
    void set(std::size_t, TValueType);
    [[nodiscard]] GetterReturnType operator[](std::size_t) const;
    [[nodiscard]] ValueType& operator[](std::size_t);
};

template<typename TValueType, bool TisComplex>
struct should_be_dense_vector_like_with_proxy {
    using ValueType = TValueType;
    static constexpr bool isComplex = TisComplex;

    [[nodiscard]] std::size_t n() const;

    [[nodiscard]] ValueType get(std::size_t) const;
    void set(std::size_t, TValueType);
    [[nodiscard]] ValueType operator[](std::size_t) const;
    [[nodiscard]] ElementProxy<ValueType> operator[](std::size_t);
};

TEST(dense_vector_like, given_should_be_dense_vector_like_should_return_true_1) {
    static_assert(dense_vector_like<should_be_dense_vector_like<float, false, float>>);
}

TEST(dense_vector_like, given_should_be_dense_vector_like_should_return_true_2) {
    static_assert(dense_vector_like<should_be_dense_vector_like<float, true, const float&>>);
}

TEST(dense_vector_like, given_should_be_dense_vector_like_should_return_true_3) {
    static_assert(dense_vector_like<should_be_dense_vector_like<float, false, float&>>);
}

TEST(dense_vector_like, given_should_not_be_dense_vector_like_should_return_false_1) {
    static_assert(!dense_vector_like<should_be_dense_vector_like<float, true, double>>);
}

TEST(dense_vector_like, given_should_be_dense_vector_like_with_proxy_should_return_true) {
    static_assert(dense_vector_like<should_be_dense_vector_like_with_proxy<float, false>>);
}

TEST(dense_vector_like, given_should_be_dense_vector_like_with_proxy_complex_should_return_true) {
    static_assert(dense_vector_like<should_be_dense_vector_like_with_proxy<std::complex<float>, true>>);
}

TEST(is_dense_vector_like_v, given_should_be_dense_vector_like_should_return_true) {
    static_assert(is_dense_vector_like_v<should_be_dense_vector_like<float, true, const float&>>);
}

TEST(is_dense_vector_like_v, given_should_not_be_dense_vector_like_should_return_false) {
    static_assert(!is_dense_vector_like_v<should_be_dense_vector_like<float, true, double>>);
}

TEST(is_dense_vector_like, given_should_be_dense_vector_like_should_return_true) {
    static_assert(is_dense_vector_like<should_be_dense_vector_like<float, true, const float&>>::value);
}

TEST(is_dense_vector_like, given_should_not_be_dense_vector_like_should_return_false) {
    static_assert(!is_dense_vector_like<should_be_dense_vector_like<float, true, double>>::value);
}

TEST(is_dense_vector, given_dense_vector_should_return_true) {
    static_assert(is_dense_vector<DenseVector<float>>::value);
}

TEST(is_dense_vector, given_dense_vector_view_should_return_false) {
    static_assert(!is_dense_vector<DenseVectorView<float>>::value);
}

TEST(is_dense_vector, given_dense_vector_like_should_return_false) {
    static_assert(!is_dense_vector<should_be_dense_vector_like<float, false, float&>>::value);
}

TEST(is_dense_vector_v, given_dense_vector_should_return_true) {
    static_assert(is_dense_vector_v<DenseVector<float>>);
}

TEST(is_dense_vector_v, given_dense_vector_view_should_return_false) {
    static_assert(!is_dense_vector_v<DenseVectorView<float>>);
}

TEST(is_dense_vector_v, given_dense_vector_like_should_return_false) {
    static_assert(!is_dense_vector_v<should_be_dense_vector_like<float, false, float&>>);
}

TEST(dense_vector, given_dense_vector_should_return_true) {
    static_assert(dense_vector<DenseVector<float>>);
}

TEST(dense_vector, given_dense_vector_view_should_return_false) {
    static_assert(!dense_vector<DenseVectorView<float>>);
}

TEST(dense_vector, given_dense_vector_like_should_return_false) {
    static_assert(!dense_vector<should_be_dense_vector_like<float, false, float&>>);
}

TEST(is_dense_vector_view, given_dense_vector_view_should_return_true) {
    static_assert(is_dense_vector_view<DenseVectorView<float>>::value);
}

TEST(is_dense_vector_view, given_dense_vector_should_return_false) {
    static_assert(!is_dense_vector_view<DenseVector<float>>::value);
}

TEST(is_dense_vector_view, given_dense_vector_like_should_return_false) {
    static_assert(!is_dense_vector_view<should_be_dense_vector_like<float, false, float&>>::value);
}

TEST(is_dense_vector_view_v, given_dense_vector_view_should_return_true) {
    static_assert(is_dense_vector_view_v<DenseVectorView<float>>);
}

TEST(is_dense_vector_view_v, given_dense_vector_should_return_false) {
    static_assert(!is_dense_vector_view_v<DenseVector<float>>);
}

TEST(is_dense_vector_view_v, given_dense_vector_like_should_return_false) {
    static_assert(!is_dense_vector_view_v<should_be_dense_vector_like<float, false, float&>>);
}

TEST(dense_vector_view, given_dense_vector_view_should_return_true) {
    static_assert(dense_vector_view<DenseVectorView<float>>);
}

TEST(dense_vector_view, given_dense_vector_should_return_false) {
    static_assert(!dense_vector_view<DenseVector<float>>);
}

TEST(dense_vector_view, given_dense_vector_like_should_return_false) {
    static_assert(!dense_vector_view<should_be_dense_vector_like<float, false, float&>>);
}
