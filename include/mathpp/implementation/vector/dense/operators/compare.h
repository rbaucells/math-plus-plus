#ifndef MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_COMPARE_H
#define MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_COMPARE_H

#include <cstddef>
#include <tuple>
#include <type_traits>

#include "mathpp/implementation/common/precision.h"
#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/common/compare.h"

#include "../traits.h"

/**
 * @brief Compares elements of dense vector like objects up to the specified precision.
 *
 * Implemented using scalar compare function with provided precision.
 * Time complexity is O(n * k) where k is the number of vector args. (except for 2 matrices where its O(n))
 *
 * @tparam T Dense vector like object type of 'a'.
 * @tparam U Dense vector like object type of 'b'.
 * @tparam ARGS Dense vector like object types of 'args'.
 * @param precision How precise the comparison should be. (inclusive).
 * @param a First dense vector like argument.
 * @param b Second dense vector like argument.
 * @param args Remaining dense vector like arguments.
 *
 * @return Whether all elements of all arguments are equal up to the specified precision.
 * @note Inclusive comparison, meaning a vector elements of 1, 0.9, and 1.1 are not all equal up to a precision of 0.1
 * @note Vectors of different size will always return false.
 */
template<dense_vector_like T, dense_vector_like U, dense_vector_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType,typename U::ValueType, typename ARGS::ValueType...>>> precision, const T& a, const U& b, const ARGS&... args) {
    if (!(a.n() == b.n() && ((b.n() == args.n()) && ...))) {
        return false;
    }

    const std::size_t n = a.n();

    for (std::size_t i = 0; i < n; i++) {
        if (!compare(precision, a[i], b[i], args[i]...)) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Compares elements of dense vector like objects up to machine epsilon precision.
 *
 * @details Implemented by calling dense vector like compare function with machine epsilon precision .
 * Time complexity is O(n * k) where k is the number of vector args. (except for 2 matrices where its O(n))
 *
 * @tparam T Dense vector like object type of 'a'.
 * @tparam U Dense vector like object type of 'b'.
 * @tparam ARGS Dense vector like object types of 'args'.
 * @param a First dense vector like argument.
 * @param b Second dense vector like argument.
 * @param args Remaining dense vector like arguments.
 *
 * @see compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename ARGS::ValueType...>>> precision, const T& a, const U& b, const ARGS&... args)
 *
 * @return Whether all elements of all arguments are equal up to the machine epsilon precision.
 * @note Vectors of different size will always return false.
 */
template<dense_vector_like T, dense_vector_like U, dense_vector_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const T& a, const U& b, const ARGS&... args) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>>>()), a, b, args...);
}

/**
 * @brief Expression object that lazily computes the comparison of a variadic number of dense vector like objects.
 * @tparam ARGS Types of dense vector like objects to compare together.
 */
template<dense_vector_like... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseVectorCompareExpr {
    std::tuple<const ARGS&...> args;

    Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision = Precision(epsilon<std::common_type_t<typename ARGS::ValueType...>>());

    explicit DenseVectorCompareExpr(const ARGS&... args) : args(args...) {}

    [[nodiscard]] bool evaluate() const {
        return std::apply([&](const auto&... m) {
            return compare(precision, m...);
        }, args);
    }

    operator bool() const {
        return evaluate();
    }

    template<dense_vector_like OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    DenseVectorCompareExpr<ARGS..., OTHER> operator==(const OTHER& other) const {
        return std::apply([&](const auto&... m) {
            return DenseVectorCompareExpr<ARGS..., OTHER>(m..., other);
        }, args);
    }

    DenseVectorCompareExpr<ARGS...>& operator+(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>>& newPrecision) {
        precision.value = newPrecision.value;
        return *this;
    }
};

/**
 * @brief Compares 2 dense vector like objects up to machine epsilon precision.
 *
 * Implemented using scalar compare function with provided precision.
 * Time complexity is O(n * k) where k is the number of vector args. (except for 2 matrices where its O(n))
 *
 * @tparam T Dense vector like type of first param.
 * @tparam U Dense vector like type of second param.
 * @param a First dense vector like object param.
 * @param b First dense vector like object param.
 * @return Expression object that lazily computes comparison of a variadic number of vectors.
 * @note Vectors of different size will always return false.
 */
template<dense_vector_like T, dense_vector_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseVectorCompareExpr<T, U> operator==(const T& a, const U& b) {
    return DenseVectorCompareExpr<T, U>(a, b);
}

#endif // MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_COMPARE_H
