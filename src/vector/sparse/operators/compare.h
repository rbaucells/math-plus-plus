#pragma once
#include "../../../helper.h"
#include "../vector.h"

template<sparse_vector_like T, sparse_vector_like U, sparse_vector_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const T& a, const U& b, const ARGS&... args) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>>>()), a, b, args...);
}

template<sparse_vector_like T, sparse_vector_like U, sparse_vector_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename ARGS::ValueType...>>> precision, const T& a, const U& b, const ARGS&... args) {
    assert_same_size(a, b, args...);

    if (!compare(a.nnz(), b.nnz(), args.nnz()...)) {
        return false;
    }

    const std::size_t n = a.n();

    for (std::size_t i = 0; i < n; i++) {
        if (!compare(precision, a.get(i), b.get(i), args.get(i)...)) {
            return false;
        }
    }

    return true;
}

template<sparse_vector_like... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct SparseVectorCompareExpr {
    std::tuple<const ARGS&...> args;

    Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision;

    explicit SparseVectorCompareExpr(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision, const ARGS&... args) : args(args...), precision(precision) {
    }

    [[nodiscard]] bool evaluate() const {
        return std::apply([this](const auto&... m) {
            return compare(precision, m...);
        }, this->args);
    }

    operator bool() const {
        return evaluate();
    }

    template<sparse_vector_like OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    SparseVectorCompareExpr<ARGS..., OTHER> operator==(const OTHER& other) const {
        return std::apply([&](const auto&... m) {
            return SparseVectorCompareExpr<ARGS..., OTHER>(precision, m..., other);
        }, this->args);
    }

    SparseVectorCompareExpr<ARGS...>& operator+(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>>& newPrecision) {
        precision.value = newPrecision.value;
        return *this;
    }
};

template<sparse_vector_like T, sparse_vector_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
SparseVectorCompareExpr<T, U> operator==(const T& a, const U& b) {
    return SparseVectorCompareExpr<T, U>(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType>>>()), a, b);
}
