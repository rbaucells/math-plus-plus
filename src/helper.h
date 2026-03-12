#pragma once
#include <complex>
#include <type_traits>
#include <numbers>

#include "helper.h"

// is_complex and is_complex_v and complex and real and scalar
template<typename>
struct is_complex : std::false_type {};

template<typename T>
struct is_complex<std::complex<T>> : std::true_type {};

template<typename T>
inline constexpr bool is_complex_v = is_complex<T>::value;

template<typename T>
concept complex = is_complex_v<T>;

template<typename T>
concept real = std::is_arithmetic_v<T>;

template<typename T>
concept scalar = real<T> || complex<T>;

// underlying_type and underlying_type_t
template<typename T>
struct underlying_type {
    using value_type = T;
};

template<complex T>
struct underlying_type<T> {
    using value_type = T::value_type;
};

template<typename T>
using underlying_type_t = underlying_type<T>::value_type;

// HasCommonType
template<typename... T>
concept has_common_type = requires { typename std::common_type_t<T...>; };

// rotations
enum class RotationType {
    degrees,
    radians
};

/**
 * @brief Converts 'radians' from radians to degrees.
 * @tparam T Scalar type of 'radians'.
 * @param radians Radians to convert to degrees.
 * @return 'radians' converted to degrees.
 */
template<scalar T = float>
[[nodiscard]] T radiansToDegrees(const T radians) {
    return radians * (static_cast<T>(180) / static_cast<T>(std::numbers::pi));
}

/**
 * @brief Converts 'degrees' from degrees to radians.
 * @tparam T Scalar type of 'degrees'.
 * @param degrees Degrees to convert to radians.
 * @return 'degrees' converted to radians.
 */
template<scalar T = float>
[[nodiscard]] T degreesToRadians(const T degrees) {
    return degrees * (static_cast<T>(std::numbers::pi) / static_cast<T>(180));
}

/**
 * @brief Converts the rotation 'value' from 'from' to 'to'.
 * @tparam T Scalar type of 'value'.
 * @param from RotationType (unit) of 'value'.
 * @param to RotationType (unit) to return.
 * @param value The rotation in 'from' RotationType.
 * @return 'value' converted to 'to' RotationType.
 */
template<scalar T = float>
[[nodiscard]] T convert(const RotationType from, const RotationType to, const T value) {
    switch (from) {
        case RotationType::degrees:
            switch (to) {
                case RotationType::degrees:
                    return value;
                case RotationType::radians:
                    return degreesToRadians<T>(value);
            }
            break;
        case RotationType::radians:
            switch (to) {
                case RotationType::radians:
                    return value;
                case RotationType::degrees:
                    return radiansToDegrees<T>(value);
            }
            break;
    }

    return value;
}


// epsilon and precisions
/**
 * @brief Returns at compile time the machine precision of type 'T'.
 * @tparam T Integer type.
 * @return The epsilon of type 'T'.
 * @note This is always 0 for integer types.
 */
template<std::integral T>
[[nodiscard]] constexpr T epsilon() {
    return 0;
}

/**
 * @brief Returns at compile time the machine precision of type 'T'.
 * @tparam T Floating point type.
 * @return The epsilon of type 'T'.
 */
template<std::floating_point T>
[[nodiscard]] constexpr T epsilon() {
    return std::numeric_limits<T>::epsilon();
}

/**
 * @brief Returns at compile time the machine precision of type 'T'.
 * @tparam T Complex number type.
 * @return The epsilon of type 'T'.
 */
template<complex T>
[[nodiscard]] constexpr underlying_type_t<T> epsilon() {
    return epsilon<underlying_type_t<T>>();
}

/**
 * @brief Struct representing real precisions.
 * @tparam T Real scalar type of precision.
 */
template<real T>
struct Precision {
    T value;
};


/**
 * @brief Checks if 'a, b, and args' are all equal within 'precision'.
 * @return Whether 'a, b, and args' are all equal within 'precision'.
 * @param precision Precision type on real scalar of precision to compare numbers within.
 * @param a First argument to compare.
 * @param b Second argument to compare.
 * @param args Optional rest of arguments to compare.
 * @tparam T Scalar types of 'a'.
 * @tparam U Scalar types of 'b'.
 * @tparam ARGS Scalar types of 'args'.
 * @note The underlying types of 'T, U, and ARGS' must have a common type.
 * @note compare(Precision(0.1f), 1.0f, 1.1f) will return true. (inclusive).
 */
template<scalar T, scalar U, scalar... ARGS> requires has_common_type<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>
[[nodiscard]] bool compare(const Precision<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>> precision, const T a, const U b, const ARGS... args) {
    // they are all real
    if constexpr (real<T> && real<U> && (real<ARGS> && ...)) {
        const std::common_type_t<T, U, ARGS...> min = std::min({static_cast<std::common_type_t<T, U, ARGS...>>(a), static_cast<std::common_type_t<T, U, ARGS...>>(b), (static_cast<std::common_type_t<T, U, ARGS...>>(args))...});
        const std::common_type_t<T, U, ARGS...> max = std::max({static_cast<std::common_type_t<T, U, ARGS...>>(a), static_cast<std::common_type_t<T, U, ARGS...>>(b), (static_cast<std::common_type_t<T, U, ARGS...>>(args))...});

        return std::abs(max - min) <= precision.value;
    }
    else {
        const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> realMin = std::min({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(b)), (static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(args)))...});
        const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> realMax = std::max({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(b)), (static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(args)))...});

        if (std::abs(realMax - realMin) > precision.value) {
            return false;
        }

        const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> imagMin = std::min({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(b)), (static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(args)))...});
        const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> imagMax = std::max({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(b)), (static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(args)))...});

        if (std::abs(imagMax - imagMin) > precision.value) {
            return false;
        }

        return true;
    }
}

/**
 * @brief Checks if 'a, b, and args' are all equal within machine precision.
 * @return Whether 'a, b, and args' are all equal within machine precision.
 * @param a First argument to compare.
 * @param b Second argument to compare.
 * @param args Optional rest of arguments to compare.
 * @tparam T Scalar types of 'a'.
 * @tparam U Scalar types of 'b'.
 * @tparam ARGS Scalar types of 'args'.
 * @note The underlying types of 'T, U, and ARGS' must have a common type.
 */
template<scalar T, scalar U, scalar... ARGS> requires has_common_type<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>
[[nodiscard]] bool compare(const T a, const U b, const ARGS... args) {
    return compare(Precision(epsilon<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>()), a, b, args...);
}

enum class DotProductConjugationBehavior {
    first_argument,
    second_argument,
    neither
};
