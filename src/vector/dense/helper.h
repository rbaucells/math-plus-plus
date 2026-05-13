#pragma once
#include "../../helper.h"
#include <cstddef>
#include <concepts>
#include <type_traits>
#include "../../exceptions.h"

// dense_vector_like
template<typename T>
concept dense_vector_like = requires(const T constV, std::size_t n) {
    typename T::ValueType;
    T::isComplex;
    { constV.n() } -> std::same_as<std::size_t>;
    requires std::same_as<std::remove_cvref_t<decltype(constV.at(n))>, typename T::ValueType>;
    requires std::same_as<std::remove_cvref_t<decltype(constV[n])>, typename T::ValueType>;
};

template<typename T>
inline constexpr bool is_dense_vector_like_v = dense_vector_like<T>;

template<typename>
struct is_dense_vector_like : std::false_type {};

template<dense_vector_like T>
struct is_dense_vector_like<T> : std::true_type {};

template<scalar T>
struct DenseVector;

template<dense_vector_like T>
struct DenseVectorView;

// is_dense_vector, is_dense_vector_v, dense_vector
template<typename>
struct is_dense_vector : std::false_type {};

template<typename U>
struct is_dense_vector<DenseVector<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_vector_v = is_dense_vector<T>::value;

template<typename T>
concept dense_vector = is_dense_vector_v<T>;

// is_dense_vector_view, is_dense_vector_view_v, dense_vector_view
template<typename>
struct is_dense_vector_view : std::false_type {};

template<typename U>
struct is_dense_vector_view<DenseVectorView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_vector_view_v = is_dense_vector_view<T>::value;

template<typename T>
concept dense_vector_view = is_dense_vector_view_v<T>;


template<dense_vector_like T>
struct underlying_type<T> {
    using value_type = T::ValueType;
};

/**
 * @brief Asserts that 'a', 'b', and 'args' have the same size.
 * @tparam T Dense vector type of 'a'.
 * @tparam U Dense vector type of 'b'.
 * @tparam ARGS Dense vector types of 'args'.
 * @param a First dense vector to compare dimensions.
 * @param b Second dense vector to compare dimensions.
 * @param args Rest of dense vectors to compare dimensions.
 * @throws InvalidDimensionException If 'a', 'b', and 'args' are not all of same size.
 */
template<dense_vector_like T, dense_vector_like U, dense_vector_like... ARGS>
inline void assert_same_size(const T& a, const U& b, const ARGS&... args) {
    if (!(a.n() == b.n() && ((a.n() == args.n()) && ...))) {
        throw InvalidDimensionException("Dense vectors must all be of same size");
    }
}
