#ifndef MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_COMPARE_H
#define MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_COMPARE_H

#include <cstddef>
#include <tuple>
#include <type_traits>

#include "mathpp/implementation/common/precision.h"
#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/common/compare.h"

#include "../traits.h"
#include "mathpp/implementation/common/expressions.h"

/**
 * @brief Compares elements of dense vector like objects up to the specified precision.
 *
 * Implemented using scalar compare function with provided precision.
 * Time complexity is O(n * k) where k is the number of vector args. (except for 2 vectors where its O(n))
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
 * @brief Compares a range of dense vector like objects up to specified precision.
 * @details Calls compare(precision, args) with specified precision.
 *
 * Time complexity is O(2m * n^2) where 'm' is the number of vectors in the range.
 *
 * @tparam R Range of dense vector like objects.
 * @tparam T Dense vector like object type of elements of 'args'.
 * @param precision How precise the comparison should be. (inclusive).
 * @param args Range of dense vector like arguments.
 *
 * @return Whether all vectors in 'args' are equal up to specified precision.
 * @note Inclusive comparison, meaning a vectors elements of 1, 0.9, and 1.1 are not all equal up to a precision of 0.1.
 * @note Vectors of different size will always return false.
 * @see bool compare(const Precision<underlying_type_t<typename T::ValueType>> precision, const R& args)
 */
template<std::ranges::random_access_range R, dense_vector_like T = std::ranges::range_value_t<R>> requires dense_vector_like<std::ranges::range_value_t<R>>
[[nodiscard]] bool compare(const Precision<underlying_type_t<typename T::ValueType>> precision, const R& args) {
    if (args.size() < 2) {
        throw InvalidSizeException("Cannot compare with less than 2 dense vector arguments");
    }

    const std::size_t n = (*args.begin()).n();

    for (const T& v : args) {
        if (v.n() != n) {
            return false;
        }
    }

    for (std::size_t i = 0; i < n; i++) {
        auto accessor = std::views::iota(0u, args.size()) | std::views::transform([&](const std::size_t ii) -> T::ValueType {
            return args[ii][i];
        });

        if (!compare(precision, accessor)) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Compares elements of dense vector like objects up to machine epsilon precision.
 *
 * @details Implemented by calling dense vector like compare function with machine epsilon precision .
 * Time complexity is O(n * k) where k is the number of vector args. (except for 2 vectors where its O(n))
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
 * @brief Compares a range of dense vector like objects up to machine epsilon precision.
 * @details Calls compare(precision, args) with machine epsilon precision.
 *
 * Time complexity is O(2m * n^2) where 'm' is the number of vectors in the range.
 *
 * @tparam R Range of dense vector like objects.
 * @tparam T Dense vector like object type of elements of 'args'.
 * @param args Range of dense vector like arguments.
 *
 * @return Whether all vectors in 'args' are equal up to machine epsilon precision.
 * @note Vectors of different size will always return false.
 * @see bool compare(const Precision<underlying_type_t<typename T::ValueType>> precision, const R& args)
 */
template<std::ranges::random_access_range R, dense_vector_like T = std::ranges::range_value_t<R>> requires dense_vector_like<std::ranges::range_value_t<R>>
[[nodiscard]] bool compare(const R& args) {
    if (args.size() < 2) {
        throw InvalidSizeException("Cannot compare with less than 2 dense vector arguments");
    }

    return compare(Precision<underlying_type_t<typename T::ValueType>>(epsilon<typename T::ValueType>()), args);
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

template<dense_vector_like T>
struct DynamicDenseVectorCompareExpr {
    std::vector<VectorExprStorage<T>> vector;

    Precision<underlying_type_t<typename T::ValueType>> precision = Precision(epsilon<underlying_type_t<typename T::ValueType>>());

    explicit DynamicDenseVectorCompareExpr(std::vector<VectorExprStorage<T>> v) : vector(std::move(v)) {}

    template<typename... Args> requires (std::same_as<std::remove_cvref_t<Args>, VectorExprStorage<T>> && ...)
    explicit DynamicDenseVectorCompareExpr(Args&&... args) : vector{std::forward<Args>(args)...} {}

    [[nodiscard]] bool evaluate() const {
        return compare(precision, vector);
    }

    operator bool() const {
        return evaluate();
    }

    DynamicDenseVectorCompareExpr<T>& add(VectorExprStorage<T> other) {
        vector.push_back(other);
        return *this;
    }

    DynamicDenseVectorCompareExpr<T>& add(const Precision<underlying_type_t<typename T::ValueType>>& newPrecision) {
        precision.value = newPrecision.value;
        return *this;
    }
};

/**
 * @brief Compares 2 dense vector like objects up to machine epsilon precision.
 *
 * Implemented using scalar compare function with provided precision.
 * Time complexity is O(n * k) where k is the number of vector args. (except for 2 vectors where its O(n))
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
