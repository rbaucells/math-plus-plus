#pragma once
#include "../matrix.h"
#include "../../../expression.h"
#include "../../../helper.h"

template<dense_matrix_base T, dense_matrix_base U, dense_matrix_base... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const T& a, const U& b, const ARGS&... args) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>>>()), a, b, args...);
}

template<dense_matrix_base T, dense_matrix_base U, dense_matrix_base... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename ARGS::ValueType...>>> precision, const T& a, const U& b, const ARGS&... args) {
    assert_same_dimensions(a, b, args...);

    const int columns = a.columns;
    const int rows = a.rows;

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            if (!compare(precision, a[c, r], b[c, r], args[c, r]...)) {
                return false;
            }
        }
    }

    return true;
}

template<dense_matrix_base... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseMatrixCompareExpr : Expression<bool, ARGS...> {
    Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision;

    DenseMatrixCompareExpr(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision, const ARGS&... args) : Expression<bool, ARGS...>(args...), precision(precision) {}


    [[nodiscard]] bool evaluate() const override {
        return std::apply([this](const auto&... args) {
            return compare(precision, args...);
        }, this->args);
    }

    template<dense_matrix_base OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    DenseMatrixCompareExpr<ARGS..., OTHER> operator==(const OTHER& other) const {
        return std::apply([&](const auto&... args) {
            return DenseMatrixCompareExpr<ARGS..., OTHER>(precision, args..., other);
        }, this->args);
    }

    DenseMatrixCompareExpr<ARGS...>& operator+(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>>& newPrecision) {
        precision.value = newPrecision.value;
        return *this;
    }
};

template<dense_matrix_base T, dense_matrix_base U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseMatrixCompareExpr<T, U> operator==(const T& a, const U& b) {
    return DenseMatrixCompareExpr<T, U>(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType>>>()), a, b);
}
