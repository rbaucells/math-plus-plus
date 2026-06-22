#pragma once
#include <concepts>
#include <type_traits>
#include "mathpp/implementation/common/traits.h"

template<typename T>
concept sparse_matrix_like = requires(const T constM, T m, std::size_t c, std::size_t r, const typename T::ValueType value) {
    typename T::ValueType;
    T::isComplex;
    { constM.nnz() } -> std::same_as<std::size_t>;
    { constM.rows() } -> std::same_as<std::size_t>;
    { constM.columns() } -> std::same_as<std::size_t>;
    { constM.get(c, r) } -> std::same_as<typename T::ValueType>;
    { m.set(c, r, value) };
};

template<typename T>
inline constexpr bool is_sparse_matrix_like_v = sparse_matrix_like<T>;

template<typename>
struct is_sparse_matrix_like : std::false_type {};

template<sparse_matrix_like T>
struct is_sparse_matrix_like<T> : std::true_type {};

template<sparse_matrix_like T>
struct underlying_type<T> {
    using value_type = T::ValueType;
};
