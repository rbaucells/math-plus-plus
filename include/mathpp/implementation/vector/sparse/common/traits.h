#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_TRAITS
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_TRAITS

#include <concepts>
#include <type_traits>
#include <cstddef>
#include "mathpp/implementation/common/traits.h"

// sparse_vector_like
template<typename T>
concept sparse_vector_like = requires(T v,const T constV, std::size_t n, typename T::ValueType value) {
    typename T::ValueType;
    T::isComplex;
    { constV.n() } -> std::same_as<std::size_t>;
    { constV.nnz() } -> std::same_as<std::size_t>;
    requires std::same_as<std::remove_cvref_t<decltype(constV.get(n))>, typename T::ValueType>;
    v.set(n, value);
};

template<typename T>
inline constexpr bool is_sparse_vector_like_v = sparse_vector_like<T>;

template<typename>
struct is_sparse_vector_like : std::false_type {};

template<sparse_vector_like T>
struct is_sparse_vector_like<T> : std::true_type {};

template<sparse_vector_like T>
struct underlying_type<T> {
    using value_type = T::ValueType;
};

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_TRAITS
