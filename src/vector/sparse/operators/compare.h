#pragma once
#include "../vector.h"
#include "../../../helper.h"

template<sparse_vector_base T, sparse_vector_base U, sparse_vector_base... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const T& a, const U& b, const ARGS&... args) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>>>()), a, b, args...);
}

template<sparse_vector_base T, sparse_vector_base U, sparse_vector_base... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename ARGS::ValueType...>>> precision, const T& a, const U& b, const ARGS&... args) {
    assert_same_size(a, b, args...);

    // if nnz are different, there is no way they are the same
    if (!compare(a.nnz(), b.nnz(), args.nnz()...)) {
        return false;
    }

    const int n = a.n;

    for (int i = 0; i < n; i++) {
        if (!compare(precision, a.get(i), b.get(i), args.get(i)...)) {
            return false;
        }
    }

    return true;
}

template<sparse_vector_base... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct SparseVectorCompareExpr : Expression<bool, ARGS...> {
    Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision;

    SparseVectorCompareExpr(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision, const ARGS&... args) : Expression<bool, ARGS...>(args...), precision(precision) {}


    [[nodiscard]] bool evaluate() const override {
        return std::apply([this](const auto&... args) {
            return compare(precision, args...);
        }, this->args);
    }

    template<sparse_vector_base OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    SparseVectorCompareExpr<ARGS..., OTHER> operator==(const OTHER& other) const {
        return std::apply([&](const auto&... args) {
            return SparseVectorCompareExpr<ARGS..., OTHER>(precision, args..., other);
        }, this->args);
    }

    SparseVectorCompareExpr<ARGS...>& operator+(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>>& newPrecision) {
        precision.value = newPrecision.value;
        return *this;
    }
};

template<sparse_vector_base T, sparse_vector_base U>
SparseVectorCompareExpr<T, U> operator==(const T& a, const U& b) {
    return SparseVectorCompareExpr<T, U>(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType>>>()), a, b);
}
