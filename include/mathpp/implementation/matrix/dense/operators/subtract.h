#pragma once
#include <tuple>
#include <type_traits>
#include <cstddef>

#include "mathpp/implementation/common/expressions.h"
#include "../traits.h"
#include "../../common/asserts.h"

template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS>
struct DenseMatrixSubtractExpr {
    using ValueType = std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>;

    static constexpr bool isComplex = T::isComplex || U::isComplex || (ARGS::isComplex || ...);
    static constexpr bool isExpr = true;

    const std::tuple<ExprStorage<T>, ExprStorage<U>, ExprStorage<ARGS>...> tuple;

    DenseMatrixSubtractExpr(ExprStorage<T> a, ExprStorage<U> b, ExprStorage<ARGS>... args) : tuple(a, b, args...) {}

    [[nodiscard]] std::size_t rows() const {
        return std::get<0>(tuple).rows();
    }

    [[nodiscard]] std::size_t columns() const {
        return std::get<0>(tuple).columns();
    }

    [[nodiscard]] ValueType operator[](const std::size_t r, const std::size_t c) const {
        return std::apply([r, c](const auto&... args) {
            return (... - args[r, c]);
        }, tuple);
    }

    [[nodiscard]] ValueType at(const std::size_t r, const std::size_t c) const {
        return std::apply([r, c](const auto&... args) {
            return (... - args.at(r, c));
        }, tuple);
    }

    [[nodiscard]] ValueType data(const std::size_t i) const {
        return std::apply([i](const auto&... args) {
            return (... - args.data(i));
        }, tuple);
    }
};


template<dense_matrix_like T, dense_matrix_like U>
DenseMatrixSubtractExpr<T, U> operator-(const T& a, const U& b) {
    return DenseMatrixSubtractExpr<T, U>(a, b);
}

template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS>
DenseMatrixSubtractExpr<T, U, ARGS...> subtract(const T& a, const U& b, const ARGS&... args) {
    assert_same_dimensions(a, b, args...);
    return DenseMatrixSubtractExpr<T, U, ARGS...>(a, b, args...);
}