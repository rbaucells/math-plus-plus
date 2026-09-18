#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_TRAITS_H
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_TRAITS_H

#include <concepts>
#include <type_traits>
#include <cstddef>

#include "mathpp/implementation/common/traits.h"

// sparse_vector_like
template<typename T>
concept sparse_vector_like = requires(T v,const T constV, std::size_t n, typename T::ValueType value) {
    requires vector_like<T>;

    { constV.nnz() } -> std::same_as<std::size_t>;

    { constV.indices() } -> std::ranges::random_access_range;
    requires std::same_as<std::remove_cvref_t<std::ranges::range_value_t<decltype(constV.indices())>>, std::size_t>;
    requires std::assignable_from<std::ranges::range_value_t<decltype(v.indices())>, std::size_t>;

    { constV.values() } -> std::ranges::random_access_range;
    requires lossless_convertible<std::remove_cvref_t<std::ranges::range_value_t<decltype(constV.values())>>, typename T::ValueType>;
    requires std::assignable_from<std::ranges::range_value_t<decltype(v.values())>, typename T::ValueType>;
};

template<typename T>
inline constexpr bool is_sparse_vector_like_v = sparse_vector_like<T>;

template<typename>
struct is_sparse_vector_like : std::false_type {};

template<sparse_vector_like T>
struct is_sparse_vector_like<T> : std::true_type {};

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_TRAITS_H
