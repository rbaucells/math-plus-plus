#ifndef MATHPP_IMPLEMENTATION_COMMON_ROTATIONS
#define MATHPP_IMPLEMENTATION_COMMON_ROTATIONS

#include <numbers>
#include "traits.h"

enum class RotationType : std::uint8_t {
    degrees,
    radians
};

/**
 * @brief Converts 'radians' from radians to degrees.
 * @tparam T Scalar type of 'radians'.
 * @param radians Radians to convert to degrees.
 * @return 'radians' converted to degrees.
 */
template<scalar T>
[[nodiscard]] T radians_to_degrees(const T radians) {
    return radians * (static_cast<T>(180) / static_cast<T>(std::numbers::pi));
}

/**
 * @brief Converts 'degrees' from degrees to radians.
 * @tparam T Scalar type of 'degrees'.
 * @param degrees Degrees to convert to radians.
 * @return 'degrees' converted to radians.
 */
template<scalar T>
[[nodiscard]] T degrees_to_radians(const T degrees) {
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
template<scalar T>
[[nodiscard]] T convert(const RotationType from, const RotationType to, const T value) {
    switch (from) {
        case RotationType::degrees:
            switch (to) {
            case RotationType::degrees:
                    return value;
            case RotationType::radians:
                    return degrees_to_radians(value);
            }
            break;
        case RotationType::radians:
            switch (to) {
            case RotationType::radians:
                    return value;
            case RotationType::degrees:
                    return radians_to_degrees(value);
            }
            break;
    }

    return value;
}
#endif // MATHPP_IMPLEMENTATION_COMMON_ROTATIONS
