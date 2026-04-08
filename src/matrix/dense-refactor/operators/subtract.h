#pragma once
#include "../matrix.h"
#include "../../../helper.h"

template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>> subtract(const T& a, const U& b, const ARGS&... args) {
    assert_same_dimensions(a, b, args...);

    const int columns = a.columns();
    const int rows = a.rows();

    DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>> result(rows, columns, false);

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            result[c, r] = ((a[c, r] - b[c, r]) - ... - args[c, r]);
        }
    }

    return result;
}

template<dense_matrix_like... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseMatrixSubtractExpr {
    using ValueType = std::common_type_t<typename ARGS::ValueType...>;
    using UnderlyingType = underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>;

    static constexpr bool isComplex = is_complex_v<std::common_type_t<typename ARGS::ValueType...>>;

    std::tuple<ARGS...> args;

    DenseMatrixSubtractExpr(ARGS... args) : args(args...) {}

    std::size_t rows() const {
        // all args should be of same rows, so get first
        return std::get<0>(args).rows();
    }

    std::size_t columns() const {
        // all args should be of same columns, so get first
        return std::get<0>(args).columns();
    }

    std::common_type_t<typename ARGS::ValueType...> at(const std::size_t c, const std::size_t r) const {
        return std::apply([c, r](const auto... args) {
            return (args[c, r] - ...);
        }, args);
    }

    std::common_type_t<typename ARGS::ValueType...> operator[](const std::size_t c, const std::size_t r) const {
        if (c > columns() - 1 || r > rows() - 1) {
            throw InvalidIndexException("Cannot access DenseMatrixSubtractExpr at invalid index");
        }

        return at(c, r);
    }

    template<dense_matrix_like OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    DenseMatrixSubtractExpr<ARGS..., OTHER> operator-(const OTHER& other) const {
        if (!other.rows() == rows() || !other.columns() == columns()) {
            throw InvalidDimensionException("Cannot subtract matrices to DenseMatrixSubtractExpr of different sizes");
        }

        return std::apply([&](const auto&... args) {
            return DenseMatrixSubtractExpr<ARGS..., OTHER>(args..., other);
        }, args);
    }
};

template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseMatrixSubtractExpr<T, U> operator-(const T& a, const U& b) {
    if (!a.rows() == b.rows() || !a.columns() == b.columns()) {
        throw InvalidDimensionException("Cannot create DenseMatrixSubtractExpr matrices of different sizes");
    }

    return DenseMatrixSubtractExpr<T, U>(a, b);
}