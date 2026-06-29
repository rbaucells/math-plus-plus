#ifndef MATHPP_IMPLEMENTATION_MATRIX_SPARSE_COMMON_OPERATORS_COMPARE
#define MATHPP_IMPLEMENTATION_MATRIX_SPARSE_COMMON_OPERATORS_COMPARE

#include <type_traits>
#include <cstddef>
#include <tuple>

#include "mathpp/implementation/common/precision.h"

#include "../../common/asserts.h"

#include "mathpp/implementation/common/traits.h"

#include "../traits.h"

template<sparse_matrix_like T, sparse_matrix_like U, sparse_matrix_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const T& a, const U& b, const ARGS&... args) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>>>()), a, b, args...);
}

template<sparse_matrix_like T, sparse_matrix_like U, sparse_matrix_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename ARGS::ValueType...>>> precision, const T& a, const U& b, const ARGS&... args) {
    assert_same_dimensions(a, b, args...);

    if (!compare(a.nnz(), b.nnz(), args.nnz()...)) {
        return false;
    }

    const std::size_t columns = a.columns();
    const std::size_t rows = a.rows();

    for (std::size_t c = 0; c < columns; c++) {
        for (std::size_t r = 0; r < rows; r++) {
            if (!compare(precision, a.get(r, c), b.get(r, c), args.get(r, c)...)) {
                return false;
            }
        }
    }

    return true;
}

template<sparse_matrix_like... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct SparseMatrixCompareExpr {
    std::tuple<const ARGS&...> args;

    Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision;

    explicit SparseMatrixCompareExpr(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision, const ARGS&... args) : args(args...), precision(precision) {
    }

    [[nodiscard]] bool evaluate() const {
        return std::apply([this](const auto&... m) {
            return compare(precision, m...);
        }, this->args);
    }

    operator bool() const {
        return evaluate();
    }

    template<sparse_matrix_like OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    SparseMatrixCompareExpr<ARGS..., OTHER> operator==(const OTHER& other) const {
        return std::apply([&](const auto&... m) {
            return SparseMatrixCompareExpr<ARGS..., OTHER>(precision, m..., other);
        }, this->args);
    }

    SparseMatrixCompareExpr<ARGS...>& operator+(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>>& newPrecision) {
        precision.value = newPrecision.value;
        return *this;
    }
};

template<sparse_matrix_like T, sparse_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
SparseMatrixCompareExpr<T, U> operator==(const T& a, const U& b) {
    return SparseMatrixCompareExpr<T, U>(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType>>>()), a, b);
}

#endif // MATHPP_IMPLEMENTATION_MATRIX_SPARSE_COMMON_OPERATORS_COMPARE
