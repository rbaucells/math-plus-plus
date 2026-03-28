#pragma once
#include "../matrix.h"
#include "../../../helper.h"

template<sparse_matrix_base T, sparse_matrix_base U, sparse_matrix_base... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const T& a, const U& b, const ARGS&... args) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>>>()), a, b, args...);
}

template<sparse_matrix_base T, sparse_matrix_base U, sparse_matrix_base... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename ARGS::ValueType...>>> precision, const T& a, const U& b, const ARGS&... args) {
    assert_same_dimensions(a, b, args...);

    // if nnz are different, there is no way they are the same
    if (!compare(a.nnz(), b.nnz(), args.nnz()...)) {
        return false;
    }

    const int columns = a.columns();
    const int rows = a.rows();

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            if (!compare(precision, a.get(c, r), b.get(c, r), args.get(c, r)...)) {
                return false;
            }
        }
    }

    return true;
}

template<sparse_matrix_base... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct SparseMatrixCompareExpr : Expression<bool, ARGS...> {
    Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision;

    SparseMatrixCompareExpr(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision, const ARGS&... args) : Expression<bool, ARGS...>(args...), precision(precision) {}


    [[nodiscard]] bool evaluate() const override {
        return std::apply([this](const auto&... args) {
            return compare(precision, args...);
        }, this->args);
    }

    template<sparse_matrix_base OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    SparseMatrixCompareExpr<ARGS..., OTHER> operator==(const OTHER& other) const {
        return std::apply([&](const auto&... args) {
            return SparseMatrixCompareExpr<ARGS..., OTHER>(precision, args..., other);
        }, this->args);
    }

    SparseMatrixCompareExpr<ARGS...>& operator+(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>>& newPrecision) {
        precision.value = newPrecision.value;
        return *this;
    }
};

template<sparse_matrix_base T, sparse_matrix_base U>
SparseMatrixCompareExpr<T, U> operator==(const T& a, const U& b) {
    return SparseMatrixCompareExpr<T, U>(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType>>>()), a, b);
}
