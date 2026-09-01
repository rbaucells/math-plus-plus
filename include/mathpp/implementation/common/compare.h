#ifndef MATHPP_IMPLEMENTATION_COMMON_COMPARE_H
#define MATHPP_IMPLEMENTATION_COMMON_COMPARE_H

#include <algorithm>
#include <type_traits>
#include <span>
#include <ranges>

#include "exceptions.h"
#include "precision.h"
#include "traits.h"

/**
 * @brief Compares arguments up to the specified precision.
 *
 * O(2m) time complexity where 'm' is number of arguments
 *
 * @tparam T Scalar type of 'a'.
 * @tparam U Scalar type of 'b'.
 * @tparam ARGS Scalar types of 'args'.
 * @param precision How precise the comparison should be. (inclusive).
 * @param a First scalar argument.
 * @param b Second scalar argument.
 * @param args Remaining scalar arguments.
 *
 * @return Whether all arguments are equal up to the specified precision.
 * @note Inclusive comparison, meaning 1, 0.9, and 1.1 are not all equal up to a precision of 0.1
 */
template<scalar T, scalar U, scalar... ARGS> requires has_common_type<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>
[[nodiscard]] bool compare(const Precision<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>> precision, const T a, const U b, const ARGS... args) {
    if constexpr (real<T> && real<U> && (real<ARGS> && ...)) {
        // get min and max, then compare withing precision
        std::common_type_t<T, U, ARGS...> min = std::min({static_cast<std::common_type_t<T, U, ARGS...>>(a), static_cast<std::common_type_t<T, U, ARGS...>>(b), static_cast<std::common_type_t<T, U, ARGS...>>(args)...});
        std::common_type_t<T, U, ARGS...> max = std::max({static_cast<std::common_type_t<T, U, ARGS...>>(a), static_cast<std::common_type_t<T, U, ARGS...>>(b), static_cast<std::common_type_t<T, U, ARGS...>>(args)...});

        return (max - min) <= precision.value;
    }
    else {
        // get min and max of real and imag parts separately, then compare withing precision
        std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> realMin = std::min({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(b)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(args))...});
        std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> realMax = std::max({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(b)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(args))...});

        if ((realMax - realMin) > precision.value) {
            return false;
        }

        std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> imagMin = std::min({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(b)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(args))...});
        std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> imagMax = std::max({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(b)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(args))...});

        return (imagMax - imagMin) <= precision.value;
    }
}

/**
 * @brief Compares dynamic number of arguments up to the specified precision.
 *
 * O(2m) time complexity where 'm' is number of arguments
 *
 * @tparam R Range of scalar objects.
 * @tparam T Scalar type of elements of 'args'.
 * @param precision How precise the comparison should be. (inclusive).
 * @param args Range of scalar arguments.
 *
 * @return Whether all elements of 'args' are equal up to the specified precision.
 * @note Inclusive comparison, meaning 1, 0.9, and 1.1 are not all equal up to a precision of 0.1
 */
template<std::ranges::sized_range R, scalar T = std::ranges::range_value_t<R>> requires scalar<std::ranges::range_value_t<R>>
[[nodiscard]] bool compare(const Precision<underlying_type_t<T>> precision, const R& args) {
    if (args.size() < 2) {
        throw InvalidSizeException("Cannot compare with less than 2 scalar arguments");
    }

    if constexpr (real<T>) {
        // get min and max, then compare withing precision
        auto [min, max] = std::ranges::minmax_element(args.begin(), args.end());

        return (*max - *min) <= precision.value;
    }
    else {
        // get min and max of real and imag parts separately, then compare withing precision
        auto realPart = args | std::views::transform([](const T& val) -> underlying_type_t<T> {
            return std::real(val);
        });

        auto [realMin, realMax] = std::ranges::minmax_element(realPart.begin(), realPart.end());

        if ((*realMax - *realMin) > precision.value) {
            return false;
        }

        auto imagPart = args | std::views::transform([](const T& val) -> underlying_type_t<T> {
            return std::imag(val);
        });

        auto [imagMin, imagMax] = std::ranges::minmax_element(imagPart.begin(), imagPart.end());

        return (*imagMax - *imagMin) <= precision.value;
    }
}


/**
 * @brief Compares arguments up to machine epsilon precision.
 * @details Calls compare(precision, a, b, args) with machine epsilon precision.
 *
 * @tparam T Scalar type of 'a'.
 * @tparam U Scalar type of 'b'.
 * @tparam ARGS Scalar types of 'args'.
 * @param a First scalar argument.
 * @param b Second scalar argument.
 * @param args Remaining scalar arguments.
 *
 * @return Whether all arguments are equal up to machine epsilon precision.
 * @see compare(const Precision<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>> precision, const T a, const U b, const ARGS... args)
 */
template<scalar T, scalar U, scalar... ARGS> requires has_common_type<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>
[[nodiscard]] bool compare(const T a, const U b, const ARGS... args) {
    return compare(Precision(epsilon<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>()), a, b, args...);
}

/**
 * @brief Compares dynamic number of arguments up to machine epsilon precision.
 * @details Calls compare(precision, args) with machine epsilon precision.
 *
 * O(2m) time complexity where 'm' is number of arguments
 *
 * @tparam T Scalar type of elements of 'args'.
 * @param args Span of scalar arguments.
 *
 * @return Whether all elements of 'args' are equal up to machine epsilon precision.
 * @see bool compare(const Precision<underlying_type_t<T>> precision, const std::span<T>& args)
 */
template<std::ranges::sized_range R, scalar T = std::ranges::range_value_t<R>> requires scalar<std::ranges::range_value_t<R>>
[[nodiscard]] bool compare(const R& args) {
    if (args.size() < 2) {
        throw InvalidSizeException("Cannot compare with less than 2 scalar arguments");
    }

    return compare(Precision<underlying_type_t<T>>(epsilon<T>()), args);
}

#endif // MATHPP_IMPLEMENTATION_COMMON_COMPARE_H
