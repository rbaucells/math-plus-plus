#pragma once
#include "../../../helper.h"
#include <cstddef>
#include <concepts>
#include <type_traits>
#include "../common/helper.h"

template<scalar T>
struct CSRSparseMatrix;

template<scalar T>
struct CSRSparseMatrixView;

template<scalar T>
struct CSRCustomSparseMatrix;

template<typename T>
concept csr_sparse_matrix_like = requires(const T constM, T m, std::size_t c, std::size_t r, const typename T::ValueType value) {
    sparse_matrix_like<T>;
    requires std::same_as<std::remove_cvref_t<decltype(constM.values())>, typename T::ValueType*>;
    requires std::same_as<std::remove_cvref_t<decltype(constM.rowOffsets())>, std::size_t*>;
    requires std::same_as<std::remove_cvref_t<decltype(constM.colIndices())>, std::size_t*>;
};

template<typename T>
inline constexpr bool is_csr_sparse_matrix_like_v = csr_sparse_matrix_like<T>;

template<typename>
struct is_csr_sparse_matrix_like : std::false_type {};

template<csr_sparse_matrix_like T>
struct is_csr_sparse_matrix_like<T> : std::true_type {};

// is_csr_sparse_matrix, is_csr_sparse_matrix_v, csr_sparse_matrix
template<typename>
struct is_csr_sparse_matrix : std::false_type {};

template<typename U>
struct is_csr_sparse_matrix<CSRSparseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_csr_sparse_matrix_v = is_csr_sparse_matrix<T>::value;

template<typename T>
concept csr_sparse_matrix = is_csr_sparse_matrix_v<T>;

// is_csr_sparse_matrix_view, is_csr_sparse_matrix_view_v, csr_sparse_matrix_view
template<typename>
struct is_csr_sparse_matrix_view : std::false_type {};

template<typename U>
struct is_csr_sparse_matrix_view<CSRSparseMatrixView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_csr_sparse_matrix_view_v = is_csr_sparse_matrix_view<T>::value;

template<typename T>
concept csr_sparse_matrix_view = is_csr_sparse_matrix_view_v<T>;

// is_csr_custom_sparse_matrix, is_csr_custom_sparse_matrix_v, csr_custom_sparse_matrix
template<typename>
struct is_csr_custom_sparse_matrix : std::false_type {};

template<typename U>
struct is_csr_custom_sparse_matrix<CSRCustomSparseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_csr_custom_sparse_matrix_v = is_csr_custom_sparse_matrix<T>::value;

template<typename T>
concept custom_sparse_csr_matrix = is_csr_custom_sparse_matrix_v<T>;
