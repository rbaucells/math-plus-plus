#pragma once
#include "../helper.h"
#include <type_traits>
#include "../../../helper.h"
#include <tuple>
#include <cstddef>
#include "../../../exceptions.h"

template<dense_matrix_like... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseMatrixAddExpr {
    using ValueType = std::common_type_t<typename ARGS::ValueType...>;
    using UnderlyingType = underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>;

    static constexpr bool isComplex = is_complex_v<std::common_type_t<typename ARGS::ValueType...>>;

    std::tuple<const ARGS&...> args;

    explicit DenseMatrixAddExpr(const ARGS&... args) : args(args...) {
    }

    [[nodiscard]] std::size_t rows() const {
        // all args should be of same rows, so get first
        return std::get<0>(args).rows();
    }

    [[nodiscard]] std::size_t columns() const {
        // all args should be of same columns, so get first
        return std::get<0>(args).columns();
    }

    std::common_type_t<typename ARGS::ValueType...> at(const std::size_t r, const std::size_t c) const {
        return std::apply([r, c](const auto&... args) {
            return (... + args.at(r, c));
        }, args);
    }

    std::common_type_t<typename ARGS::ValueType...> operator[](const std::size_t r, const std::size_t c) const {
        if (r >= rows() || c >= columns()) {
            throw InvalidIndexException("Cannot access DenseMatrixAddExpr at invalid index");
        }

        return at(r, c);
    }

    template<dense_matrix_like OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    DenseMatrixAddExpr<ARGS..., OTHER> operator+(const OTHER& other) const {
        if (other.rows() != rows() || other.columns() != columns()) {
            throw InvalidDimensionException("Cannot add matrices to DenseMatrixAddExpr of different sizes");
        }

        return std::apply([&](const auto&... args) {
            return DenseMatrixAddExpr<ARGS..., OTHER>(args..., other);
        }, args);
    }
};

template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseMatrixAddExpr<T, U> operator+(const T& a, const U& b) {
    assert_same_dimensions(a, b);
    return DenseMatrixAddExpr<T, U>(a, b);
}

template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
DenseMatrixAddExpr<T, U, ARGS...> add(const T& a, const U& b, const ARGS&... args) {
    assert_same_dimensions(a, b, args...);
    return DenseMatrixAddExpr<T, U, ARGS...>(a, b, args...);
}
