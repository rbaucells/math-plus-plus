#pragma once
#include <iostream>
#include <ostream>
#include <type_traits>

#include "../../../expression.h"
#include "../matrix.h"

namespace Mathpp {
    /**
     * @brief Adds together all the matrices supplied
     * @tparam T Scalar type of DenseMatrix<T>
     * @tparam OTHERS The types of the other matrices being added (must derive fromm DenseMatrixBase)
     * @param a The first matrix param
     * @param others All the other matrices to be added to a
     * @return A DenseMatrix<T> made from adding each element of each matrix together
     */
    template<typename T, typename... OTHERS>
    DenseMatrix<std::common_type_t<T, typename OTHERS::ValueType...>> add(const DenseMatrixBase<T>& a, const OTHERS&... others) {
        static_assert((std::is_base_of_v<DenseMatrixBase<typename OTHERS::ValueType>, OTHERS> && ...), "All arguments must derive from DenseMatrixBase");
        (assert_same_size(a, others, "add"), ...);

        const int columns = a.columns;
        const int rows = a.rows;

        DenseMatrix<std::common_type_t<T, typename OTHERS::ValueType...>> result(a.columns, a.rows);

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