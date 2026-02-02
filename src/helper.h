#pragma once
#include <complex>
#include <type_traits>

// is_complex and is_complex_v and complex and real and scalar
template<typename T>
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
concept HasCommonType = requires { typename std::common_type_t<T...>; };

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
T radiansToDegrees(const T radians) {
    return radians * (static_cast<T>(180) / static_cast<T>(M_PI));
}

/**
 * @brief Converts 'degrees' from degrees to radians.
 * @tparam T Scalar type of 'degrees'.
 * @param degrees Degrees to convert to radians.
 * @return 'degrees' converted to radians.
 */
template<scalar T = float>
T degreesToRadians(const T degrees) {
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
T convert(const RotationType from, const RotationType to, const T value) {
    switch (from) {
        case RotationType::degrees:
            switch (to) {
                case RotationType::degrees:
                    return value;
                case RotationType::radians:
                    return degreesToRadians(value);
            }
            break;
        case RotationType::radians:
            switch (to) {
                case RotationType::radians:
                    return value;
                case RotationType::degrees:
                    return radiansToDegrees(value);
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
 * @note This is always 1 for integer types.
 */
template<std::integral T>
constexpr T epsilon() {
    return 1;
}

/**
 * @brief Returns at compile time the machine precision of type 'T'.
 * @tparam T Floating point type.
 * @return The epsilon of type 'T'.
 */
template<std::floating_point T>
constexpr T epsilon() {
    return std::numeric_limits<T>::epsilon();
}

/**
 * @brief Returns at compile time the machine precision of type 'T'.
 * @tparam T Complex number type.
 * @return The epsilon of type 'T'.
 */
template<complex T>
constexpr underlying_type_t<T> epsilon() {
    return epsilon<underlying_type_t<T>>();
}

/**
 * @brief Checks if 'a' and 'b' are equal up to 'precision'.
 * @tparam T Scalar type of 'a'.
 * @tparam U Scalar type of 'b'.
 * @param a Scalar to compare to 'b'.
 * @param b Scalar to compare to 'a'.
 * @param precision The precision to use when comparing 'a' and 'b'. Defaults to machine precision for 'common_type_t<underlying_type_t<T>, underlying_type_t<U>>'.
 * @return Whether 'a' and 'b' are equal up to 'precision'.
 * @note The underlying types of 'T' and 'U' must have a common type.
 */
template<scalar T, scalar U> requires HasCommonType<underlying_type_t<T>, underlying_type_t<U>>
bool compare(const T a, const U b, const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>> precision = epsilon<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>()) {
    return std::abs(static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>(std::real(a)) - static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>(std::real(b))) < precision && std::abs(static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>(std::imag(a)) - static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>(std::imag(b))) < precision;
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
template<real T, real U> requires HasCommonType<T, U>
bool lesser(const T a, const U b) {
    return static_cast<std::common_type_t<T, U>>(a) < static_cast<std::common_type_t<T, U>>(b);
}

/**
 * @brief Checks if the real part of 'a' is less than 'b' and 'a' is real (no imag part).
 * @tparam T Complex type of 'a'.
 * @tparam U Real type of 'b'.
 * @param a Complex scalar to compare to 'b'.
 * @param b Real scalar to compare to 'a'.
 * @return Whether the real part of 'a' is less than 'b' and 'a' is real (no imag part).
 * @note Underlying type of 'T' and 'U' must have a common type.
 */
template<complex T, real U>  requires HasCommonType<underlying_type_t<T>, U>
bool lesser(const T a, const U b) {
    return lesser(std::real(a), b) && compare(std::imag(a), 0);
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
template<real T, real U> requires HasCommonType<T, U>
bool greater(const T a, const U b) {
    return static_cast<std::common_type_t<T, U>>(a) > static_cast<std::common_type_t<T, U>>(b);
}

/**
 * @brief Checks if the real part of 'a' is greater than 'b' and 'a' is real (no imag part).
 * @tparam T Complex type of 'a'.
 * @tparam U Real type of 'b'.
 * @param a Complex scalar to compare to 'b'.
 * @param b Real scalar to compare to 'a'.
 * @return Whether the real part of 'a' is greater than 'b' and 'a' is real (no imag part).
 * @note Underlying type of 'T' and 'U' must have a common type.
 */
template<complex T, real U> requires HasCommonType<underlying_type_t<T>, U>
bool greater(const T a, const U b) {
    return greater(std::real(a), b) && compare(std::imag(a), 0);
}

enum class DotProductConjugationBehavior {
    first_argument,
    second_argument,
    neither
};
