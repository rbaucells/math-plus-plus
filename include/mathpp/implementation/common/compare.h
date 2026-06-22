#pragma once
#include <algorithm>
#include <type_traits>

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
