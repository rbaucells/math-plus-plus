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

// is_csc_matrix, is_csc_matrix_v, csc_matrix
template<typename>
struct is_csc_matrix : std::false_type {};

template<typename U>
struct is_csc_matrix<CSCSparseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_csc_matrix_v = is_csc_matrix<T>::value;

template<typename T>
concept csc_matrix = is_csc_matrix_v<T>;

// is_csc_matrix_view, is_csc_matrix_view_v, csc_matrix_view
template<typename>
struct is_csc_matrix_view : std::false_type {};

template<typename U>
struct is_csc_matrix_view<CSCSparseMatrixView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_csc_matrix_view_v = is_csc_matrix_view<T>::value;

template<typename T>
concept csc_matrix_view = is_csc_matrix_view_v<T>;

// is_csc_custom_matrix, is_csc_custom_matrix_v, csc_custom_matrix
template<typename>
struct is_csc_custom_matrix : std::false_type {};

template<typename U>
struct is_csc_custom_matrix<CSCCustomSparseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_csc_custom_matrix_v = is_csc_custom_matrix<T>::value;

template<typename T>
concept custom_csc_matrix = is_csc_custom_matrix_v<T>;
