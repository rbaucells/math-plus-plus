#ifndef MATHPP_IMPLEMENTATION_MATRIX_COMMON_TRAITS_H
#define MATHPP_IMPLEMENTATION_MATRIX_COMMON_TRAITS_H

#include <concepts>
#include <cstddef>
#include "mathpp/implementation/common/traits.h"

template<typename T>
concept matrix_like = requires(T m, const T constM, std::size_t r, std::size_t c, std::size_t i, typename T::ValueType v) {
    // compile time
    typename T::ValueType;
    T::isComplex;

    // dimensions
    { constM.rows() } -> std::same_as<std::size_t>;
    { constM.columns() } -> std::same_as<std::size_t>;

    // accessing
    requires std::same_as<std::remove_cvref_t<decltype(constM.get(r, c))>, typename T::ValueType>;
    { m.set(r, c, v) } -> std::same_as<void>;
};

template<typename T>
inline constexpr bool is_matrix_like_v = matrix_like<T>;

template<typename>
struct is_matrix_like : std::false_type {};

template<matrix_like T>
struct is_matrix_like<T> : std::true_type {};

template<matrix_like T>
struct underlying_type<T> {
    using ValueType = T::ValueType;
};

#endif // MATHPP_IMPLEMENTATION_MATRIX_COMMON_TRAITS_H
