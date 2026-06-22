#pragma once
#include <tuple>
#include <type_traits>

#include "mathpp/implementation/common/exceptions.h"

#include "../../common/asserts.h"
#include "../traits.h"

#include "mathpp/implementation/common/traits.h"

template<dense_vector_like... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseVectorSubtractExpr {
    using ValueType = std::common_type_t<typename ARGS::ValueType...>;
    using UnderlyingType = underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>;

    static constexpr bool isComplex = is_complex_v<std::common_type_t<typename ARGS::ValueType...>>;

    std::tuple<const ARGS&...> args;

    explicit DenseVectorSubtractExpr(const ARGS&... args) : args(args...) {
    }

    [[nodiscard]] std::size_t n() const {
        // all args should be of same n, so get first
        return std::get<0>(args).n();
    }

    std::common_type_t<typename ARGS::ValueType...> at(const std::size_t i) const {
        return std::apply([i](const auto&... args) {
            return (... - args.at(i));
        }, args);
    }

    std::common_type_t<typename ARGS::ValueType...> operator[](const std::size_t i) const {
        if (i >= n()) {
            throw InvalidIndexException("Cannot access DenseVectorSubtractExpr at invalid index");
        }

        return at(i);
    }

    template<dense_vector_like OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    DenseVectorSubtractExpr<ARGS..., OTHER> operator-(const OTHER& other) const {
        if (other.n() != n()) {
            throw InvalidDimensionException("Cannot subtract vectors to DenseVectorSubtractExpr of different sizes");
        }

        return std::apply([&](const auto&... args) {
            return DenseVectorSubtractExpr<ARGS..., OTHER>(args..., other);
        }, args);
    }
};

template<dense_vector_like T, dense_vector_like U, dense_vector_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
DenseVectorSubtractExpr<T, U, ARGS...> subtract(const T& a, const U& b, const ARGS&... args) {
    assert_same_size(a, b, args...);
    return DenseVectorSubtractExpr<T, U, ARGS...>(a, b, args...);
}

template<dense_vector_like T, dense_vector_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseVectorSubtractExpr<T, U> operator-(const T& a, const U& b) {
    assert_same_size(a, b);
    return DenseVectorSubtractExpr<T, U>(a, b);
}
