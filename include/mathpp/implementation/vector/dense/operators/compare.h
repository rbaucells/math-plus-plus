#pragma once
#include <type_traits>
#include <cstddef>
#include <tuple>

#include "mathpp/implementation/common/precision.h"
#include "mathpp/implementation/common/traits.h"

#include "../traits.h"

#include "../../common/asserts.h"


template<dense_vector_like T, dense_vector_like U, dense_vector_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const T& a, const U& b, const ARGS&... args) {
    return compare(Precision(epsilon<std::underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>>>()), a, b, args...);
}

template<dense_vector_like T, dense_vector_like U, dense_vector_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename ARGS::ValueType...>>> precision, const T& a, const U& b, const ARGS&... args) {
    assert_same_size(a, b, args...);

    const std::size_t n = a.n();

    for (std::size_t i = 0; i < n; i++) {
        if (!compare(precision, a.at(i), b.at(i), args.at(i)...)) {
            return false;
        }
    }

    return true;
}

template<dense_vector_like... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseVectorCompareExpr {
    std::tuple<const ARGS&...> args;

    Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision;

    explicit DenseVectorCompareExpr(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision, const ARGS&... args) : args(args...), precision(precision) {
    }

    [[nodiscard]] bool evaluate() const {
        return std::apply([this](const auto&... m) {
            return compare(precision, m...);
        }, this->args);
    }

    operator bool() const {
        return evaluate();
    }

    template<dense_vector_like OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    DenseVectorCompareExpr<ARGS..., OTHER> operator==(const OTHER& other) const {
        return std::apply([&](const auto&... m) {
            return DenseVectorCompareExpr<ARGS..., OTHER>(precision, m..., other);
        }, this->args);
    }

    DenseVectorCompareExpr<ARGS...>& operator+(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>>& newPrecision) {
        precision.value = newPrecision.value;
        return *this;
    }
};

template<dense_vector_like T, dense_vector_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseVectorCompareExpr<T, U> operator==(const T& a, const U& b) {
    return DenseVectorCompareExpr<T, U>(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType>>>()), a, b);
}
