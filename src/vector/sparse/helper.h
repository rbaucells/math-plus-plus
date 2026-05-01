#pragma once
#include "../../helper.h"
#include <cstddef>
#include <concepts>
#include <type_traits>
#include "../../exceptions.h"

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

/**
 * @brief Asserts that 'a', 'b', and 'args' have the same size.
 * @tparam T Dense vector type of 'a'.
 * @tparam U Dense vector type of 'b'.
 * @tparam ARGS Dense vector types of 'args'.
 * @param a First sparse vector to compare dimensions.
 * @param b Second sparse vector to compare dimensions.
 * @param args Rest of sparse vectors to compare dimensions.
 * @throws InvalidDimensionException If 'a', 'b', and 'args' are not all of same size.
 */
template<sparse_vector_like T, sparse_vector_like U, sparse_vector_like... ARGS>
inline void assert_same_size(const T& a, const U& b, const ARGS&... args) {
    if (!(a.n() == b.n() && ((a.n() == args.n()) && ...))) {
        throw InvalidDimensionException("Sparse vectors must all be of same size");
    }
}
