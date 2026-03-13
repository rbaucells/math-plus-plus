#pragma once
#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T>
struct SparseMatrixBase;

template<scalar T>
struct SparseMatrix;

template<scalar T>
struct SparseMatrixView;

template<scalar T>
struct CustomSparseMatrix;

// is_sparse_matrix_base, is_sparse_matrix_base_v, sparse_matrix_base
template<typename T>
struct is_sparse_matrix_base {
private:
    template<typename U>
    static std::true_type test(const SparseMatrixBase<U>*) {
        return {};
    }

    static std::false_type test(...) {
        return {};
    }

public:
    static constexpr bool value = decltype(test(std::declval<std::remove_cvref_t<T>*>()))::value;
};

template<typename T>
inline constexpr bool is_sparse_matrix_base_v = is_sparse_matrix_base<T>::value;

template<typename T>
concept sparse_matrix_base = is_sparse_matrix_base_v<T>;

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


template<sparse_matrix_base T>
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
template<sparse_matrix_base T, sparse_matrix_base U, sparse_matrix_base... ARGS>
inline void assert_same_dimensions(const T& a, const U& b, const ARGS&... args) {
    if (!(a.columns == b.columns && a.rows == b.rows && ((a.columns == args.columns && a.rows == args.rows) && ...))) {
        throw InvalidDimensionException("Sparse matrices must all have same dimensions");
    }
}

/**
 * @brief Asserts that the 'm' matrix is square.
 * @tparam T Matrix type of 'm'.
 * @param m Sparse matrix to test squareness of.
 * @throws InvalidDimensionException if the 'm' matrix is not square.
 */
template<sparse_matrix_base T>
inline void assert_square(const T& m) {
    if (m.columns != m.rows) {
        throw InvalidDimensionException("Sparse matrix must be square");
    }
}
