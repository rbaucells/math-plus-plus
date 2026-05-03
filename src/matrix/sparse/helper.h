#pragma once
#include "../../helper.h"
#include <cstddef>
#include <concepts>
#include <type_traits>
#include "../../exceptions.h"

template<scalar T>
struct SparseMatrix;

template<scalar T>
struct SparseMatrixView;

template<scalar T>
struct CustomSparseMatrix;

template<typename T>
concept sparse_matrix_like = requires(const T constM, T m, std::size_t c, std::size_t r, const typename T::ValueType value) {
    typename T::ValueType;
    T::isComplex;
    { constM.nnz() } -> std::same_as<std::size_t>;
    { constM.rows() } -> std::same_as<std::size_t>;
    { constM.columns() } -> std::same_as<std::size_t>;
    { constM.get(c, r) } -> std::same_as<typename T::ValueType>;
    { m.set(c, r, value) };
};

template<typename T>
inline constexpr bool is_sparse_matrix_like_v = sparse_matrix_like<T>;

template<typename>
struct is_sparse_matrix_like : std::false_type {};

template<sparse_matrix_like T>
struct is_sparse_matrix_like<T> : std::true_type {};

// is_sparse_matrix, is_sparse_matrix_v, sparse_matrix
template<typename>
struct is_sparse_matrix : std::false_type {};

template<typename U>
struct is_sparse_matrix<SparseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_sparse_matrix_v = is_sparse_matrix<T>::value;

template<typename T>
concept sparse_matrix = is_sparse_matrix_v<T>;

// is_sparse_matrix_view, is_sparse_matrix_view_v, sparse_matrix_view
template<typename>
struct is_sparse_matrix_view : std::false_type {};

template<typename U>
struct is_sparse_matrix_view<SparseMatrixView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_sparse_matrix_view_v = is_sparse_matrix_view<T>::value;

template<typename T>
concept sparse_matrix_view = is_sparse_matrix_view_v<T>;

// is_custom_sparse_matrix, is_custom_sparse_matrix_v, custom_sparse_matrix
template<typename>
struct is_custom_sparse_matrix : std::false_type {};

template<typename U>
struct is_custom_sparse_matrix<CustomSparseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_custom_sparse_matrix_v = is_custom_sparse_matrix<T>::value;

template<typename T>
concept custom_sparse_matrix = is_custom_sparse_matrix_v<T>;


template<sparse_matrix_like T>
struct underlying_type<T> {
    using value_type = T::ValueType;
};

/**
 * @brief Asserts that 'a', 'b', and 'args' have the same dimensions.
 * @tparam T Sparse matrix type of 'a'.
 * @tparam U Sparse matrix type of 'b'.
 * @tparam ARGS Sparse matrix types of 'args'.
 * @param a First sparse matrix to compare dimensions.
 * @param b Second sparse matrix to compare dimensions.
 * @param args Rest of sparse matrices to compare dimensions.
 * @throws InvalidDimensionException If 'a', 'b', and 'args' are not all of same dimensions.
 */
template<sparse_matrix_like T, sparse_matrix_like U, sparse_matrix_like... ARGS>
inline void assert_same_dimensions(const T& a, const U& b, const ARGS&... args) {
    if (!(a.columns() == b.columns() && a.rows() == b.rows() && ((a.columns() == args.columns() && a.rows() == args.rows()) && ...))) {
        throw InvalidDimensionException("Sparse matrices must all have same dimensions");
    }
}

/**
 * @brief Asserts that the 'm' matrix is square.
 * @tparam T Matrix type of 'm'.
 * @param m Sparse matrix to test squareness of.
 * @throws InvalidDimensionException if the 'm' matrix is not square.
 */
template<sparse_matrix_like T>
inline void assert_square(const T& m) {
    if (m.columns() != m.rows()) {
        throw InvalidDimensionException("Sparse matrix must be square");
    }
}
