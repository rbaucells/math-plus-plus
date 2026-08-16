#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_TRAITS_H
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_TRAITS_H

#include <type_traits>
#include "mathpp/implementation/common/traits.h"

// forward declare
template<scalar T>
struct DokSparseVector;

template<scalar T>
struct DokSparseVectorView;

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
