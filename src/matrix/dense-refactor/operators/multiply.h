#pragma once
#include "../matrix.h"
#include "../../../expression.h"
#include "../../../helper.h"

template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>> multiply(const T& a, const U& b, const ARGS&... args) {
    assert_can_multiply(a, b, args...);

    if constexpr (sizeof...(args) == 0) {
        const int aRows = a.rows();
        const int aColumns = a.columns();
        const int bColumns = b.columns();

        std::cout << "running multiplicaiton loop" << std::endl;

        DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType>> result(aRows, bColumns, false);

        for (int c = 0; c < bColumns; c++) {
            for (int r = 0; r < aRows; r++) {
                result[c, r] = 0;

                for (int x = 0; x < aColumns; x++) {
                    result[c, r] += a[x, r] * b[c, x];
                }
            }
        }

        return std::move(result);
    }

    DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>> result = multiply(a, b);

    ((result = multiply(result, args)), ...);

    return std::move(result);
}

template<dense_matrix_like... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseMatrixMultiplyExpr {
    using ValueType = std::common_type_t<typename ARGS::ValueType...>;
    using UnderlyingType = underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>;

    static constexpr bool isComplex = is_complex_v<std::common_type_t<typename ARGS::ValueType...>>;

    std::tuple<const ARGS&...> args;

    mutable DenseMatrix<std::common_type_t<typename ARGS::ValueType...>>* result = nullptr;

    explicit DenseMatrixMultiplyExpr(const ARGS&... args) : args(args...) {
        assert_can_multiply(args...);
    }

    [[nodiscard]] std::size_t rows() const {
        return std::get<0>(args).rows();
    }

    [[nodiscard]] std::size_t columns() const {
        constexpr std::size_t args_size = std::tuple_size_v<std::tuple<const ARGS&...>>;
        return std::get<args_size - 1>(args).columns();
    }

    void remakeResultIfNeeded() const {
        if (result == nullptr) {
            std::apply([this](const auto&... m) {
                result = new DenseMatrix<std::common_type_t<typename ARGS::ValueType...>>(multiply(m...));
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

    ~DenseMatrixMultiplyExpr() {
        delete result;
    }
};

template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseMatrixMultiplyExpr<T, U> operator*(const T& a, const U& b) {
    return DenseMatrixMultiplyExpr<T, U>(a, b);
}
