#pragma once
#include <concepts>
#include <type_traits>

#include "../common/traits.h"
#include "mathpp/implementation/common/traits.h"

// forward declare
template<scalar T>
struct DenseVector;

template<scalar T>
struct DenseVectorView;

// dense_vector_like
template<typename T>
concept dense_vector_like = requires(const T constV, std::size_t n) {
    requires vector_like<T>;
    requires std::same_as<std::remove_cvref_t<decltype(constV.at(n))>, typename T::ValueType>;
    requires std::same_as<std::remove_cvref_t<decltype(constV[n])>, typename T::ValueType>;
};

template<typename T>
inline constexpr bool is_dense_vector_like_v = dense_vector_like<T>;

template<typename>
struct is_dense_vector_like : std::false_type {};

template<dense_vector_like T>
struct is_dense_vector_like<T> : std::true_type {};

// dense_vector
template<typename>
struct is_dense_vector : std::false_type {};

template<typename U>
struct is_dense_vector<DenseVector<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_vector_v = is_dense_vector<T>::value;

template<typename T>
concept dense_vector = is_dense_vector_v<T>;

// dense_vector_view
template<typename>
struct is_dense_vector_view : std::false_type {};

template<typename U>
struct is_dense_vector_view<DenseVectorView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_vector_view_v = is_dense_vector_view<T>::value;

template<typename T>
concept dense_vector_view = is_dense_vector_view_v<T>;
