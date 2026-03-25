#pragma once
#include "../matrix.h"
#include "../../../expression.h"
#include "../../../helper.h"

template<dense_matrix_base T, dense_matrix_base U, dense_matrix_base... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>> add(const T& a, const U& b, const ARGS&... args) {
    assert_same_dimensions(a, b, args...);

    const int columns = a.columns;
    const int rows = a.rows;

    DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>> result(rows, columns, false);

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            result[c, r] = ((a[c, r] + b[c, r]) + ... + args[c, r]);
        }
    }

    return std::move(result);
}

template<dense_matrix_base... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseMatrixAddExpr : Expression<DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> , ARGS...> {
    using Expression<DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> , ARGS...>::Expression;

    [[nodiscard]] DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> evaluate() const override {
        return std::apply([this](const auto&... args) {
            return add(args...);
        }, this->args);
    }

    template<dense_matrix_base OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    DenseMatrixAddExpr<ARGS..., OTHER> operator+(const OTHER& other) const {
        return std::apply([&](const auto&... args) {
            return DenseMatrixAddExpr<ARGS..., OTHER>(args..., other);
        }, this->args);
    }
};

template<dense_matrix_base T, dense_matrix_base U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseMatrixAddExpr<T, U> operator+(const T& a, const U& b) {
    return DenseMatrixAddExpr<T, U>(a, b);
}