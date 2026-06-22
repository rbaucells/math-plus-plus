#pragma once
#include <cstddef>
#include <tuple>
#include <type_traits>

#include "mathpp/implementation/common/precision.h"
#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/common/compare.h"

#include "../traits.h"

/**
 * @brief Compares elements of dense matrix like objects up to the specified precision.
 *
 * Implemented using scalar compare function with provided precision.
 * Time complexity is O(n^2 * k) where k is the number of matrix args. (except for 2 matrices where its O(n^2))
 *
 * @tparam T Dense matrix like object type of 'a'.
 * @tparam U Dense matrix like object type of 'b'.
 * @tparam ARGS Dense matrix like object types of 'args'.
 * @param precision How precise the comparison should be. (inclusive).
 * @param a First dense matrix like argument.
 * @param b Second dense matrix like argument.
 * @param args Remaining dense matrix like arguments.
 *
 * @return Whether all elements of all arguments are equal up to the specified precision.
 * @note Inclusive comparison, meaning a matrices elements of 1, 0.9, and 1.1 are not all equal up to a precision of 0.1
 * @note Matrices of different size will always return false.
 */
template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType,typename U::ValueType, typename ARGS::ValueType...>>> precision, const T& a, const U& b, const ARGS&... args) {
    if (!(a.columns() == b.columns() && a.rows() == b.rows() && ((a.columns() == args.columns() && a.rows() == args.rows()) && ...))) {
        return false;
    }

    const std::size_t columns = a.columns();
    const std::size_t rows = a.rows();

    for (std::size_t c = 0; c < columns; c++) {
        for (std::size_t r = 0; r < rows; r++) {
            if (!compare(precision, a[r, c], b[r, c], args[r, c]...)) {
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief Compares elements of dense matrix like objects up to machine epsilon precision.
 *
 * @details Implemented by calling dense matrix like compare function with machine epsilon precision .
 * Time complexity is O(n^2 * k) where k is the number of matrix args. (except for 2 matrices where its O(n^2))
 *
 * @tparam T Dense matrix like object type of 'a'.
 * @tparam U Dense matrix like object type of 'b'.
 * @tparam ARGS Dense matrix like object types of 'args'.
 * @param a First dense matrix like argument.
 * @param b Second dense matrix like argument.
 * @param args Remaining dense matrix like arguments.
 *
 * @see compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename ARGS::ValueType...>>> precision, const T& a, const U& b, const ARGS&... args)
 *
 * @return Whether all elements of all arguments are equal up to the machine epsilon precision.
 * @note Matrices of different size will always return false.
 */
template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const T& a, const U& b, const ARGS&... args) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>>>()), a, b, args...);
}

/**
 * @brief Expression object that lazily computes the comparison of a variadic number of dense matrix like objects.
 * @tparam ARGS Types of dense matrix like objects to compare together.
 */
template<dense_matrix_like... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseMatrixCompareExpr {
    std::tuple<const ARGS&...> args;

    Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision = Precision(epsilon<std::common_type_t<typename ARGS::ValueType...>>());

    explicit DenseMatrixCompareExpr(const ARGS&... args) : args(args...) {}

    [[nodiscard]] bool evaluate() const {
        return std::apply([&](const auto&... m) {
            return compare(precision, m...);
        }, args);
    }

    operator bool() const {
        return evaluate();
    }

    template<dense_matrix_like OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    DenseMatrixCompareExpr<ARGS..., OTHER> operator==(const OTHER& other) const {
        return std::apply([&](const auto&... m) {
            return DenseMatrixCompareExpr<ARGS..., OTHER>(m..., other);
        }, args);
    }

    DenseMatrixCompareExpr<ARGS...>& operator+(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>>& newPrecision) {
        precision.value = newPrecision.value;
        return *this;
    }
};

/**
 * @brief Compares 2 dense matrix like objects up to machine epsilon precision.
 *
 * Implemented using scalar compare function with provided precision.
 * Time complexity is O(n^2 * k) where k is the number of matrix args. (except for 2 matrices where its O(n^2))
 *
 * @tparam T Dense matrix like type of first param.
 * @tparam U Dense matrix like type of second param.
 * @param a First dense matrix like object param.
 * @param b First dense matrix like object param.
 * @return Expression object that lazily computes comparison of a variadic number of matrices
 * @note Matrices of different size will always return false.
 */
template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseMatrixCompareExpr<T, U> operator==(const T& a, const U& b) {
    return DenseMatrixCompareExpr<T, U>(a, b);
}
