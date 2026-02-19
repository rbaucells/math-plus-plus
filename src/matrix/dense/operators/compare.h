#pragma once
#include "../matrix.h"
#include "../../../helper.h"

template<dense_matrix_base T, dense_matrix_base... OTHERS>
[[nodiscard]] bool compare(const T& a, const OTHERS&... others, const underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>> precision = epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>>>()) {
    assert_same_dimensions(a, others...);

    const int columns = a.columns;
    const int rows = a.rows;

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            if (!compare<typename T::ValueType, typename OTHERS::ValueType...>(a[c, r], others[c, r]..., precision)) {
                return false;
            }
        }
    }

    return true;
}

template<typename... OTHERS>
struct DenseMatrixCompareExpr : Expression<bool, OTHERS...> {
    using Expression<bool, OTHERS...>::Expression;

    bool evaluate() const override {
        return std::apply([](const auto&... args) {
            return compare<OTHERS...>(args...);
        }, this->others);
    }

    template<typename OTHER>
    DenseMatrixCompareExpr<OTHER, OTHERS...> operator+(const OTHER& other) const {
        return std::apply([&](const auto&... args) {
            return DenseMatrixSumExpr<OTHER, OTHERS...>(other, args...);
        }, this->others);
    }
};

template<dense_matrix_base T, dense_matrix_base U>
DenseMatrixCompareExpr<T, U> operator==(const T& a, const U& b) {
    return DenseMatrixCompareExpr<T, U>(a, b);
}
