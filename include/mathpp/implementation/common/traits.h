#ifndef MATHPP_IMPLEMENTATION_COMMON_TRAITS_H
#define MATHPP_IMPLEMENTATION_COMMON_TRAITS_H

#include <complex>
#include <type_traits>

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

template<typename>
struct is_real : std::false_type {};

template<typename T> requires std::is_arithmetic_v<T>
struct is_real<T> : std::true_type {};

template<typename T>
inline constexpr bool is_real_v = is_real<T>::value;

template<typename T>
concept scalar = real<T> || complex<T>;

template<typename>
struct is_scalar : std::false_type {};

template<typename T> requires real<T> || complex<T>
struct is_scalar<T> : std::true_type {};

template<typename T>
inline constexpr bool is_scalar_v = is_scalar<T>::value;

template<typename T>
struct underlying_type {
    using ValueType = T;
};

template<complex T>
struct underlying_type<T> {
    using ValueType = T::value_type;
};

template<typename T>
using underlying_type_t = underlying_type<T>::ValueType;

template<typename... T>
concept has_common_type = requires { typename std::common_type_t<T...>; };

template <typename From, typename To>
struct is_lossless_convertible {
    static constexpr bool int_to_int_narrowing = std::is_integral_v<From> && std::is_integral_v<To> && std::numeric_limits<To>::digits < std::numeric_limits<From>::digits;
    static constexpr bool float_to_int_narrowing = std::is_floating_point_v<From> && std::is_integral_v<To>;
    static constexpr bool int_to_float_narrowing = std::is_integral_v<From> && std::is_floating_point_v<To> && std::numeric_limits<From>::digits < std::numeric_limits<To>::digits;
    static constexpr bool float_to_float_narrowing = std::is_floating_point_v<From> && std::is_floating_point_v<To> && (sizeof(To) < sizeof(From));

    static constexpr bool value = !(int_to_int_narrowing || float_to_int_narrowing || int_to_float_narrowing || float_to_float_narrowing);
};

template <typename From, typename To>
inline constexpr bool is_lossless_convertible_v = is_lossless_convertible<From, To>::value;

template <typename From, typename To>
concept lossless_convertible = is_lossless_convertible_v<From, To>;

#endif // MATHPP_IMPLEMENTATION_COMMON_TRAITS_H
