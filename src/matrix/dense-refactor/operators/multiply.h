#pragma once
#include "../matrix.h"
#include "../../../expression.h"
#include "../../../helper.h"

template<dense_matrix_like... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseMatrixMultiplyExpr {
    using ValueType = std::common_type_t<typename ARGS::ValueType...>;
    using UnderlyingType = underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>;

    static constexpr bool isComplex = is_complex_v<std::common_type_t<typename ARGS::ValueType...>>;

    std::tuple<const ARGS&...> args;

    mutable std::optional<DenseMatrix<std::common_type_t<typename ARGS::ValueType...>>> result;

    explicit DenseMatrixMultiplyExpr(const ARGS&... args) : args(args...) {}

    [[nodiscard]] std::size_t rows() const {
        return std::get<0>(args).rows();
    }

    [[nodiscard]] std::size_t columns() const {
        constexpr std::size_t args_size = std::tuple_size_v<std::tuple<const ARGS&...>>;
        return std::get<args_size - 1>(args).columns();
    }

    void remakeResultIfNeeded() const {
        if (!result.has_value()) {
            std::cout << "Recalculating Multiplication Result" << std::endl;

            std::apply([this](const auto&... m) {
                result.emplace(DenseMatrixMultiplyExpr<ARGS...>::multiply(m...));
            }, args);
        }
    }

    std::common_type_t<typename ARGS::ValueType...> at(const std::size_t c, const std::size_t r) const {
        remakeResultIfNeeded();
        return result->at(c, r);
    }

    std::common_type_t<typename ARGS::ValueType...> operator[](const std::size_t c, const std::size_t r) const {
        remakeResultIfNeeded();
        return result->operator[](c, r);
    }

    template<dense_matrix_like OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    DenseMatrixMultiplyExpr<ARGS..., OTHER> operator*(const OTHER& other) const {
        if (other.rows() != columns()) {
            throw InvalidDimensionException("Cannot multiply matrices to DenseMatrixMultiplyExpr whose inner dimensions dont match");
        }

        return std::apply([&](const auto&... m) {
            return DenseMatrixMultiplyExpr<ARGS..., OTHER>(m..., other);
        }, args);
    }

private:
    template<dense_matrix_like T, dense_matrix_like U>
    static DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> multiply(const T& a, const U& b) {
        const int aRows = a.rows();
        const int aColumns = a.columns();
        const int bColumns = b.columns();

        DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> result(aRows, bColumns, false);

        for (int c = 0; c < bColumns; c++) {
            for (int r = 0; r < aRows; r++) {
                result[c, r] = 0;

                for (int x = 0; x < aColumns; x++) {
                    result[c, r] += a[x, r] * b[c, x];
                }
            }
        }

        return result;
    }

    template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS1>
    static DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> multiply(const T& a, const U& b, const ARGS1&... args) {
        DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> temp = DenseMatrixMultiplyExpr<ARGS...>::multiply(a, b);
        return DenseMatrixMultiplyExpr<ARGS...>::multiply(temp, args...);
    }
};

template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
DenseMatrixMultiplyExpr<T, U, ARGS...> multiply(const T& a, const U& b, const ARGS&... args) {
    assert_can_multiply(a, b, args...);
    return DenseMatrixMultiplyExpr<T, U, ARGS...>(a, b, args...);
}

template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseMatrixMultiplyExpr<T, U> operator*(const T& a, const U& b) {
    assert_can_multiply(a, b);
    return DenseMatrixMultiplyExpr<T, U>(a, b);
}
