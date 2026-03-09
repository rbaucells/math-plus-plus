#pragma once
#include "../matrix.h"
#include "../../../helper.h"

template<dense_matrix_base T, dense_matrix_base... OTHERS>
[[nodiscard]] bool compare(const T& a, const OTHERS&... others) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>>>()), a, others...);
}

template<dense_matrix_base T, dense_matrix_base... OTHERS>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>>> precision, const T&a, const OTHERS&... others) {
    assert_same_dimensions(a, others...);

    const int columns = a.columns;
    const int rows = a.rows;

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            if (!compare(precision, a[c, r], others[c, r]...)) {
                return false;
            }
        }
    }

    return true;
}

template<typename... OTHERS>
struct DenseMatrixCompareExpr : Expression<bool, OTHERS...> {
    Precision<underlying_type_t<std::common_type_t<underlying_type_t<OTHERS>...>>> precision;

    DenseMatrixCompareExpr(const Precision<underlying_type_t<std::common_type_t<underlying_type_t<OTHERS>...>>> precision, const OTHERS&... args) : Expression<bool, OTHERS...>(args...), precision(precision) {}


    [[nodiscard]] bool evaluate() const override {
        return std::apply([this](const auto&... args) {
            return compare(precision, args...);
        }, this->others);
    }

    template<typename OTHER>
    DenseMatrixCompareExpr<OTHER, OTHERS...> operator==(const OTHER& other) const {
        return std::apply([&](const auto&... args) {
            return DenseMatrixCompareExpr<OTHER, OTHERS...>(precision, other, args...);
        }, this->others);
    }

    DenseMatrixCompareExpr<OTHERS...>& operator+(const Precision<underlying_type_t<std::common_type_t<underlying_type_t<OTHERS>...>>>& newPrecision) {
        precision.value = newPrecision.value;
        return *this;
    }
};

template<dense_matrix_base T, dense_matrix_base U>
DenseMatrixCompareExpr<T, U> operator==(const T& a, const U& b) {
    return DenseMatrixCompareExpr<T, U>(Precision(epsilon<underlying_type_t<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>>()), a, b);
}
