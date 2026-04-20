#pragma once
#include "../../../helper.h"
#include "../matrix.h"

template<dense_matrix_like... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseMatrixMultiplyExpr {
    using ValueType = std::common_type_t<typename ARGS::ValueType...>;
    using UnderlyingType = underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>;

    static constexpr bool isComplex = is_complex_v<std::common_type_t<typename ARGS::ValueType...>>;

    std::tuple<const ARGS&...> args;

    mutable std::optional<DenseMatrix<std::common_type_t<typename ARGS::ValueType...>>> result;

    explicit DenseMatrixMultiplyExpr(const ARGS&... args) : args(args...) {
    }

    [[nodiscard]] std::size_t rows() const {
        return std::get<0>(args).rows();
    }

    [[nodiscard]] std::size_t columns() const {
        constexpr std::size_t args_size = std::tuple_size_v<std::tuple<const ARGS&...>>;
        return std::get<args_size - 1>(args).columns();
    }

    void remakeResultIfNeeded() const {
        if (!result.has_value()) {
            std::apply([this](const auto&... m) {
                result.emplace(DenseMatrixMultiplyExpr<ARGS...>::multiply(m...));
            }, args);
        }
    }

    std::common_type_t<typename ARGS::ValueType...> at(const std::size_t r, const std::size_t c) const {
        remakeResultIfNeeded();
        return result->at(r, c);
    }

    std::common_type_t<typename ARGS::ValueType...> operator[](const std::size_t r, const std::size_t c) const {
        remakeResultIfNeeded();
        return result->operator[](r, c);
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
        const std::size_t a_rows = a.rows();
        const std::size_t a_columns = a.columns();
        const std::size_t b_columns = b.columns();

        DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> result(a_rows, b_columns, false);

        for (std::size_t c = 0; c < b_columns; c++) {
            for (std::size_t r = 0; r < a_rows; r++) {
                result.at(r, c) = 0;

                for (std::size_t x = 0; x < a_columns; x++) {
                    result.at(r, c) += a.at(r, x) * b.at(x, c);
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
