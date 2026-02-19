#pragma once
#include <complex>
#include <type_traits>

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
    return radians * (static_cast<T>(180) / static_cast<T>(M_PI));
}

/**
 * @brief Converts 'degrees' from degrees to radians.
 * @tparam T Scalar type of 'degrees'.
 * @param degrees Degrees to convert to radians.
 * @return 'degrees' converted to radians.
 */
template<scalar T = float>
[[nodiscard]] T degreesToRadians(const T degrees) {
    return degrees * (static_cast<T>(M_PI) / static_cast<T>(180));
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
    const T value;
};


/**
 * @brief Checks if 'a' and 'others' are equal up to 'precision'.
 * @tparam T Scalar type of 'a'.
 * @tparam OTHERS Scalar types of 'others'.
 * @param precision The precision to use when comparing 'a' and 'others'
 * @param a Scalar to compare to 'others'.
 * @param others Scalars to compare to 'a'.
 * @return Whether 'a' and 'others' are all equal up to 'precision'.
 * @note The underlying types of 'T' and 'OTHERS' must have a common type.
 */
template<scalar T, scalar... OTHERS> requires has_common_type<underlying_type_t<T>, underlying_type_t<OTHERS>...>
[[nodiscard]] bool compare(const Precision<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHERS>...>> precision, const T a, const OTHERS... others) {
    return ((std::abs(static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHERS>...>>(std::real(a)) - static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHERS>...>>(std::real(others))) <= precision.value && std::abs(static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHERS>...>>(std::imag(a)) - static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHERS>...>>(std::imag(others))) <= precision.value) && ...);
}

/**
 * @brief Checks if 'a' and 'others' are equal up to machine precision.
 * @tparam T Scalar type of 'a'.
 * @tparam OTHERS Scalar types of 'others'.
 * @param a Scalar to compare to 'others'.
 * @param others Scalars to compare to 'a'.
 * @return Whether 'a' and 'others' are all equal up to machine precision.
 * @note The underlying types of 'T' and 'OTHERS' must have a common type.
 */
template<scalar T, scalar... OTHERS> requires has_common_type<underlying_type_t<T>, underlying_type_t<OTHERS>...>
[[nodiscard]] bool compare(const T a, const OTHERS... others) {
    return compare(epsilon<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHERS>...>>(), a, others...);
}

/**
 * @brief Checks if 'a' is less than 'b'.
 * @tparam T Real type of 'a'.
 * @tparam U Real type of 'b'.
 * @param a Real scalar to compare to 'b'.
 * @param b Real scalar to compare to 'a'.
 * @return Whether 'a' is less than 'b'.
 * @note Types 'T' and 'U' must have a common type.
 */
template<real T, real U> requires has_common_type<T, U>
[[nodiscard]] bool lesser(const T a, const U b) {
    return static_cast<std::common_type_t<T, U>>(a) < static_cast<std::common_type_t<T, U>>(b);
}

/**
 * @brief Checks if 'a' is greater than 'b'.
 * @tparam T Real type of 'a'.
 * @tparam U Real type of 'b'.
 * @param a Real scalar to compare to 'b'.
 * @param b Real scalar to compare to 'a'.
 * @return Whether 'a' is greater than 'b'.
 * @note Types 'T' and 'U' must have a common type.
 */
template<real T, real U> requires has_common_type<T, U>
[[nodiscard]] bool greater(const T a, const U b) {
    return static_cast<std::common_type_t<T, U>>(a) > static_cast<std::common_type_t<T, U>>(b);
}

enum class DotProductConjugationBehavior {
    first_argument,
    second_argument,
    neither
};
