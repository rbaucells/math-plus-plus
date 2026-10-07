#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_TRAITS_H
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_TRAITS_H

#include <type_traits>
#include <concepts>
#include <cstddef>
#include <ranges>

#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/vector/sparse/common/traits.h"

// forward declare
template<scalar T>
struct DokSparseVector;

template<scalar T>
struct DokSparseVectorView;

// dok_sparse_vector_like
template<typename T>
concept dok_sparse_vector_like = requires (const T constV, T v, std::size_t i, typename T::ValueType val) {
    requires sparse_vector_like<T>;

    // { constV.map().size() } -> std::same_as<std::size_t>;
    requires std::same_as<std::remove_cvref_t<decltype(constV.map().at(i))>, typename T::ValueType>;
    { constV.map().contains(i) } -> std::same_as<bool>;
    requires std::convertible_to<std::remove_cvref_t<decltype(v.map()[i])>, typename T::ValueType>;
    { v.map()[i] = val };
    { v.map().at(i) = val };

    requires requires(std::ranges::range_value_t<std::remove_cvref_t<decltype(constV.map())>> pair) {
        requires std::same_as<std::remove_cvref_t<decltype(pair.first)>, std::size_t>;
        requires lossless_convertible<std::remove_cvref_t<decltype(pair.second)>, typename T::ValueType>;
    };

    requires requires(std::ranges::range_value_t<std::remove_cvref_t<decltype(v.map())>> pair) {
        requires std::same_as<std::remove_cvref_t<decltype(pair.first)>, std::size_t>;
        requires lossless_convertible<std::remove_cvref_t<decltype(pair.second)>, typename T::ValueType>;
        { pair.second = typename T::ValueType{} };
    };
};

template<typename T>
inline constexpr bool is_dok_sparse_vector_like_v = dok_sparse_vector_like<T>;

template<typename>
struct is_dok_sparse_vector_like : std::false_type {};

template<dok_sparse_vector_like T>
struct is_dok_sparse_vector_like<T> : std::true_type {};

// dok_sparse_vector
template<typename>
struct is_dok_sparse_vector : std::false_type {};

template<typename U>
struct is_dok_sparse_vector<DokSparseVector<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dok_sparse_vector_v = is_dok_sparse_vector<T>::value;

template<typename T>
concept dok_sparse_vector = is_dok_sparse_vector_v<T>;

// dok_sparse_vector_view
template<typename>
struct is_dok_sparse_vector_view : std::false_type {};

template<typename U>
struct is_dok_sparse_vector_view<DokSparseVectorView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dok_sparse_vector_view_v = is_dok_sparse_vector_view<T>::value;

template<typename T>
concept dok_sparse_vector_view = is_dok_sparse_vector_view_v<T>;

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_TRAITS_H
