#pragma once
#include <iostream>
#include <ostream>
#include <type_traits>

#include "../helper.h"

#include "../../../expression.h"
#include "../matrix.h"

namespace Mathpp {
    /**
     * @brief Adds together all the matrices supplied.
     * @tparam T Matrix type of 'a'.
     * @tparam OTHERS The types of the other matrices being added.
     * @param a The first matrix param.
     * @param others All the other matrices to be added to 'a'.
     * @return A DenseMatrix made from adding each element of each matrix together.
     */
    template<dense_matrix_base T, dense_matrix_base... OTHERS>
    DenseMatrix<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHERS>...>> add(const T& a, const OTHERS&... others) {
        assert_same_dimensions(a, others..., "add");

        const int columns = a.columns;
        const int rows = a.rows;

        DenseMatrix<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHERS>...>> result(a.columns, a.rows);

        std::cout << "looping" << std::endl;

        for (int c = 0; c < columns; c++) {
            for (int r = 0; r < rows; r++) {
                result[c, r] = (a[c, r] + ... + others[c, r]);
            }
        }

        return result;
    }
}

template<typename... OTHERS>
struct DenseMatrixSumExpr : Expression<DenseMatrix<std::common_type_t<typename OTHERS::ValueType...>>, OTHERS...> {
    using Expression<DenseMatrix<std::common_type_t<typename OTHERS::ValueType...>>, OTHERS...>::Expression;

    DenseMatrix<std::common_type_t<typename OTHERS::ValueType...>> evaluate() const override {
        return std::apply([](const auto&... args) {
            return Mathpp::add(args...);
        }, this->others);
    }

    template<typename OTHER>
    DenseMatrixSumExpr<OTHER, OTHERS...> operator+(const OTHER& other) const {
        return std::apply([&](const auto&... args) {
            return DenseMatrixSumExpr<OTHER, OTHERS...>(other, args...);
        }, this->others);
    }
};

template<typename T, typename OTHER_T>
DenseMatrixSumExpr<DenseMatrixBase<T>, DenseMatrixBase<OTHER_T>> operator+(const DenseMatrixBase<T>& a, const DenseMatrixBase<OTHER_T>& b) {
    return DenseMatrixSumExpr<DenseMatrixBase<T>, DenseMatrixBase<OTHER_T>>(a, b);
}