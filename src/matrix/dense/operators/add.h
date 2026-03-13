#pragma once
#include <type_traits>

#include "../helper.h"

#include "../../../expression.h"
#include "../matrix.h"

/**
 * @brief Adds together all the dense matrices supplied.
 * @tparam T Dense matrix type of 'a'.
 * @tparam U Dense matrix type of 'b'.
 * @tparam ARGS Dense matrix types of 'args'.
 * @param a The first dense matrix to be added.
 * @param b The second dense matrix to be added.
 * @param args Optional rest of dense matrices to add.
 * @return A dense matrix made from adding each element of each matrix together.
 */
template<dense_matrix_base T, dense_matrix_base U, dense_matrix_base... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
DenseMatrix<std::common_type_t<typename T::ValueType, typename ARGS::ValueType...>> add(const T& a, const U& b, const ARGS&... args) {
    assert_same_dimensions(a, b, args...);

    const int columns = a.columns;
    const int rows = a.rows;

    DenseMatrix<std::common_type_t<typename T::ValueType, typename ARGS::ValueType...>> result(columns, rows);

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            result[c, r] = a[c, r] + b[c, r] + (args[c, r] + ...);
        }
    }

    return result;
}

template<typename... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseMatrixSumExpr : Expression<DenseMatrix<std::common_type_t<typename ARGS::ValueType...>>, ARGS...> {
    using Expression<DenseMatrix<std::common_type_t<typename ARGS::ValueType...>>, ARGS...>::Expression;

    DenseMatrix<std::common_type_t<typename ARGS::ValueType...>> evaluate() const override {
        return std::apply([](const auto&... args) {
            return add(args...);
        }, this->args);
    }

    template<typename OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    DenseMatrixSumExpr<ARGS..., OTHER> operator+(const OTHER& other) const {
        return std::apply([&](const auto&... args) {
            return DenseMatrixSumExpr<ARGS..., OTHER>(args..., other);
        }, this->args);
    }
};

template<dense_matrix_base T, dense_matrix_base U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseMatrixSumExpr<T, U> operator+(const T& a, const U& b) {
    return DenseMatrixSumExpr<T, U>(a, b);
}
