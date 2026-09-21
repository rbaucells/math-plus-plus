#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_TRAITS_H
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_TRAITS_H

#include <concepts>
#include <type_traits>
#include <cstddef>

#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/vector/common/traits.h"

// sparse_vector_like
template<typename T>
concept sparse_vector_like = requires(const T constV) {
    requires vector_like<T>;

    { constV.nnz() } -> std::same_as<std::size_t>;
};

template<typename T>
inline constexpr bool is_sparse_vector_like_v = sparse_vector_like<T>;

template<typename>
struct is_sparse_vector_like : std::false_type {};

template<sparse_vector_like T>
struct is_sparse_vector_like<T> : std::true_type {};

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_TRAITS_H
