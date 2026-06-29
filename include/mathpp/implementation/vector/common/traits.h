#ifndef MATHPP_IMPLEMENTATION_VECTOR_COMMON_TRAITS
#define MATHPP_IMPLEMENTATION_VECTOR_COMMON_TRAITS

#include <concepts>
#include <cstddef>
#include "mathpp/implementation/common/traits.h"

template<typename T>
concept vector_like = requires(T v,  const T constV, const std::size_t i) {
    // compile time
    typename T::ValueType;
    T::isComplex;

    // dimensions
    { constV.n() } -> std::same_as<std::size_t>;
};

template<typename T>
inline constexpr bool is_vector_like_v = vector_like<T>;

template<typename>
struct is_vector_like : std::false_type {};

template<vector_like T>
struct is_vector_like<T> : std::true_type {};

template<vector_like T>
struct underlying_type<T> {
    using ValueType = T::ValueType;
};

#endif // MATHPP_IMPLEMENTATION_VECTOR_COMMON_TRAITS
