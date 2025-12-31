#pragma once
#include <type_traits>
#include <complex>

// is_complex - is_complex_v - IsComplex
template<typename T>
struct is_complex : std::false_type {};

template<typename U>
struct is_complex<std::complex<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_complex_v = is_complex<T>::value;

template<typename T>
concept complex = is_complex_v<T>;

// IsScalar
template<typename T>
concept scalar = std::is_arithmetic_v<T> || complex<T>;

// is_matrix - is_matrix_v - IsMatrix
template< int ROWS, int COLUMNS, scalar T>
struct Matrix;

template<typename T>
struct is_matrix : std::false_type {};

template< int ROWS, int COLUMNS, scalar T>
struct is_matrix<Matrix<ROWS, COLUMNS, T>> : std::true_type {};

template<typename T>
inline constexpr bool is_matrix_v = is_matrix<T>::value;

template<typename T>
concept matrix = is_matrix_v<T>;

// is_vector - is_vector_v - IsVector
template<int N, scalar T>
struct Vector;

template<typename T>
struct is_vector : std::false_type {};

template<int N, scalar T>
struct is_vector<Vector<N, T>> : std::true_type {};

template<typename T>
inline constexpr bool is_vector_v = is_vector<T>::value;

template<typename T>
concept vector = is_vector_v<T>;

// underlying_type - underlying_type_t
template<typename T>
struct underlying_type {
    using value_type = T;
};

template<complex T>
struct underlying_type<T> {
    using value_type = T::value_type;
};

template<matrix T>
struct underlying_type<T> {
    using value_type = T::value_type;
};

template<vector T>
struct underlying_type<T> {
    using value_type = T::value_type;
};

template<typename T>
using underlying_type_t = underlying_type<T>::value_type;

// HasCommonType
template<typename... T>
concept HasCommonType =
    requires { typename std::common_type_t<T...>; };

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

template<std::integral T>
bool compare(const T a, const T b, const T precision = epsilon<T>()) {
    return std::abs(a - b) < precision;
}

template<std::floating_point T>
bool compare(const T a, const T b, const T precision = epsilon<T>()) {
    return std::abs(a - b) < precision;
}

template<complex T>
bool compare(const T a, const T b, const underlying_type_t<T> precision = epsilon<underlying_type_t<T>>()) {
    return std::abs(a - b) < precision;
}

template<scalar T, scalar U> requires HasCommonType<T, U>
bool compare(const T a, const U b, const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>> precision = epsilon<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>()) {
    return compare(static_cast<std::common_type_t<T, U>>(a), static_cast<std::common_type_t<T, U>>(b), precision);
}