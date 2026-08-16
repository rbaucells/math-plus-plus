#ifndef MATHPP_IMPLEMENTATION_MATRIX_SPARSE_CSC_TRAITS_H
#define MATHPP_IMPLEMENTATION_MATRIX_SPARSE_CSC_TRAITS_H

#include <concepts>
#include <type_traits>
#include <cstddef>

#include "../common/traits.h"
#include "mathpp/implementation/common/traits.h"

// forward declare
template<scalar T>
struct CSCSparseMatrix;

template<scalar T>
struct CSCSparseMatrixView;

// csc_sparse_matrix_like
template<typename T>
concept csc_sparse_matrix_like = requires(const T constM, T m, std::size_t c, std::size_t r, const typename T::ValueType value) {
    requires sparse_matrix_like<T>;
    requires std::same_as<std::remove_cvref_t<decltype(constM.values())>, const typename T::ValueType*>;
    requires std::same_as<std::remove_cvref_t<decltype(constM.rowIndices())>, const std::size_t*>;
    requires std::same_as<std::remove_cvref_t<decltype(constM.colOffsets())>, const std::size_t*>;
    requires std::same_as<std::remove_cvref_t<decltype(m.values())>, typename T::ValueType*>;
    requires std::same_as<std::remove_cvref_t<decltype(m.rowIndices())>, std::size_t*>;
    requires std::same_as<std::remove_cvref_t<decltype(m.colOffsets())>, std::size_t*>;
};

template<typename T>
inline constexpr bool is_csc_sparse_matrix_like_v = csc_sparse_matrix_like<T>;

template<typename>
struct is_csc_sparse_matrix_like : std::false_type {};

template<csc_sparse_matrix_like T>
struct is_csc_sparse_matrix_like<T> : std::true_type {};

// csc_sparse_matrix
template<typename>
struct is_csc_sparse_matrix : std::false_type {};

template<typename U>
struct is_csc_sparse_matrix<CSCSparseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_csc_sparse_matrix_v = is_csc_sparse_matrix<T>::value;

template<typename T>
concept csc_sparse_matrix = is_csc_sparse_matrix_v<T>;

// csc_sparse_matrix_view
template<typename>
struct is_csc_sparse_matrix_view : std::false_type {};

template<typename U>
struct is_csc_sparse_matrix_view<CSCSparseMatrixView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_csc_sparse_matrix_view_v = is_csc_sparse_matrix_view<T>::value;

template<typename T>
concept csc_sparse_matrix_view = is_csc_sparse_matrix_view_v<T>;
#endif // MATHPP_IMPLEMENTATION_MATRIX_SPARSE_CSC_TRAITS_H
