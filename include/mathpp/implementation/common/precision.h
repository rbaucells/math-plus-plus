#ifndef MATHPP_IMPLEMENTATION_COMMON_PRECISION
#define MATHPP_IMPLEMENTATION_COMMON_PRECISION

#include <concepts>
#include <limits>
#include "traits.h"
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
    using ValueType = T;
    T value;
};

#endif // MATHPP_IMPLEMENTATION_COMMON_PRECISION
