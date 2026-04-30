#pragma once
#include <complex>
#include <type_traits>
#include <algorithm>
#include <concepts>
#include <limits>
#include <numbers>

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
 * @brief Compares arguments up to the specified precision.
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
 * @note Inclusive comparison, meaning 1, 0.9, and 1.1 are all equal up to a precision of 0.1
 */
template<scalar T, scalar U, scalar... ARGS> requires has_common_type<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>
[[nodiscard]] bool compare(const Precision<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>> precision, const T a, const U b, const ARGS... args) {
    if constexpr (real<T> && real<U> && (real<ARGS> && ...)) { // get min and max, then compare withing precision
        const std::common_type_t<T, U, ARGS...> min = std::min({static_cast<std::common_type_t<T, U, ARGS...>>(a), static_cast<std::common_type_t<T, U, ARGS...>>(b), (static_cast<std::common_type_t<T, U, ARGS...>>(args))...});
        const std::common_type_t<T, U, ARGS...> max = std::max({static_cast<std::common_type_t<T, U, ARGS...>>(a), static_cast<std::common_type_t<T, U, ARGS...>>(b), (static_cast<std::common_type_t<T, U, ARGS...>>(args))...});

        return max - min <= precision.value;
    }
    else { // get min and max of real and imag parts separately, then compare withing precision
        const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> realMin = std::min({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(b)), (static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(args)))...});
        const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> realMax = std::max({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(b)), (static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::real(args)))...});

        if (realMax - realMin > precision.value) {
            return false;
        }

        const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> imagMin = std::min({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(b)), (static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(args)))...});
        const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...> imagMax = std::max({static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(a)), static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(b)), (static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>, underlying_type_t<ARGS>...>>(std::imag(args)))...});

        if (imagMax - imagMin > precision.value) {
            return false;
        }

        return true;
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

enum class DotProductConjugationBehavior {
    first_argument,
    second_argument,
    neither
};

constexpr DotProductConjugationBehavior DEFAULT_CONJUGATION_BEHAVIOR = DotProductConjugationBehavior::second_argument;
