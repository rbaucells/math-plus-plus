#pragma once
#include "../../../helper.h"
#include <cstddef>
#include <concepts>
#include <type_traits>
#include "../../../exceptions.h"

template<scalar T>
struct CSCSparseMatrix;

template<scalar T>
struct CSCSparseMatrixView;

template<scalar T>
struct CSCCustomSparseMatrix;

// is_csc_sparse_matrix, is_csc_sparse_matrix_v, csc_sparse_matrix
template<typename>
struct is_csc_sparse_matrix : std::false_type {};

template<typename U>
struct is_csc_sparse_matrix<CSCSparseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_csc_sparse_matrix_v = is_csc_sparse_matrix<T>::value;

template<typename T>
concept csc_sparse_matrix = is_csc_sparse_matrix_v<T>;

// is_csc_sparse_matrix_view, is_csc_sparse_matrix_view_v, csc_sparse_matrix_view
template<typename>
struct is_csc_sparse_matrix_view : std::false_type {};

template<typename U>
struct is_csc_sparse_matrix_view<CSCSparseMatrixView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_csc_sparse_matrix_view_v = is_csc_sparse_matrix_view<T>::value;

template<typename T>
concept csc_sparse_matrix_view = is_csc_sparse_matrix_view_v<T>;

// is_csc_custom_sparse_matrix, is_csc_custom_sparse_matrix_v, csc_custom_sparse_matrix
template<typename>
struct is_csc_custom_sparse_matrix : std::false_type {};

template<typename U>
struct is_csc_custom_sparse_matrix<CSCCustomSparseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_csc_custom_sparse_matrix_v = is_csc_custom_sparse_matrix<T>::value;

template<typename T>
concept custom_sparse_csc_matrix = is_csc_custom_sparse_matrix_v<T>;
