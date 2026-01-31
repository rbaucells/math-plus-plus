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

template<typename T = float>
T radiansToDegrees(const T radians) {
    return radians * (static_cast<T>(180) / static_cast<T>(M_PI));
}

template<typename T = float>
T degreesToRadians(const T degrees) {
    return degrees * (static_cast<T>(M_PI) / static_cast<T>(180));
}

template<typename T = float>
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
template<std::integral T>
constexpr T epsilon() {
    return 1;
}

template<std::floating_point T>
constexpr T epsilon() {
    return std::numeric_limits<T>::epsilon();
}

template<complex T>
constexpr underlying_type_t<T> epsilon() {
    return epsilon<underlying_type_t<T>>();
}

// anything with anything
template<scalar T, scalar U> requires HasCommonType<underlying_type_t<T>, underlying_type_t<U>>
bool compare(const T a, const U b, const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>> precision = epsilon<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>()) {
    return std::abs(static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>(std::real(a)) - static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>(std::real(b))) < precision && std::abs(static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>(std::imag(a)) - static_cast<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>(std::imag(b))) < precision;
}

template<real T, real U> requires HasCommonType<T, U>
bool lesser(const T a, const U b) {
    return static_cast<std::common_type_t<T, U>>(a) < static_cast<std::common_type_t<T, U>>(b);
}

template<complex T, real U>  requires HasCommonType<underlying_type_t<T>, U>
bool lesser(const T a, const U b) {
    return lesser(std::real(a), b) && compare(std::imag(a), 0);
}

template<real T, real U> requires HasCommonType<T, U>
bool greater(const T a, const U b) {
    return static_cast<std::common_type_t<T, U>>(a) > static_cast<std::common_type_t<T, U>>(b);
}

template<complex T, real U> requires HasCommonType<underlying_type_t<T>, U>
bool greater(const T a, const U b) {
    return greater(std::real(a), b) && compare(std::imag(a), 0);
}

enum class DotProductConjugationBehavior {
    first_argument,
    second_argument,
    neither
};
