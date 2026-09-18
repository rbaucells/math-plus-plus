#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_TRAITS_H
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_TRAITS_H

#include <type_traits>
#include "mathpp/implementation/common/traits.h"

// forward declare
template<scalar T>
struct CooSparseVector;

template<scalar T>
struct CooSparseVectorView;

template<typename T>
concept coo_sparse_vector_like = requires (const T constV, T v) {
    requires sparse_vector_like<T>;

    { constV.indices() } -> std::ranges::random_access_range;
    requires std::same_as<std::remove_cvref_t<std::ranges::range_value_t<decltype(constV.indices())>>, std::size_t>;
    requires std::assignable_from<std::add_lvalue_reference_t<std::ranges::range_value_t<decltype(v.indices())>>, std::size_t>;

    { constV.values() } -> std::ranges::random_access_range;
    requires lossless_convertible<std::remove_cvref_t<std::ranges::range_value_t<decltype(constV.values())>>, typename T::ValueType>;
    requires std::assignable_from<std::add_lvalue_reference_t<std::ranges::range_value_t<decltype(v.values())>>, typename T::ValueType>;
};

// coo_sparse_vector
template<typename>
struct is_coo_sparse_vector : std::false_type {};

template<typename U>
struct is_coo_sparse_vector<CooSparseVector<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_coo_sparse_vector_v = is_coo_sparse_vector<T>::value;

template<typename T>
concept coo_sparse_vector = is_coo_sparse_vector_v<T>;

// coo_sparse_vector_view
template<typename>
struct is_coo_sparse_vector_view : std::false_type {};

template<typename U>
struct is_coo_sparse_vector_view<CooSparseVectorView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_coo_sparse_vector_view_v = is_coo_sparse_vector_view<T>::value;

template<typename T>
concept coo_sparse_vector_view = is_coo_sparse_vector_view_v<T>;

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COO_TRAITS_H
