#pragma once
#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T>
struct DenseMatrix;

template<scalar T>
struct DenseMatrixView;

template<scalar T>
struct CustomDenseMatrix;

// dense_matrix_like
template<typename T>
concept dense_matrix_like = requires(T m, const T constM, std::size_t c, std::size_t r) {
    typename T::ValueType;
    typename T::IsComplex;
    { constM.rows() } -> std::same_as<std::size_t>;
    { constM.columns() } -> std::same_as<std::size_t>;
    { m.at(c, r) } -> std::same_as<typename T::ValueType&>;
    { constM.at(c, r) } -> std::same_as<const typename T::ValueType&>;
    { m[c, r] } -> std::same_as<typename T::ValueType&>;
    { constM[c, r] } -> std::same_as<const typename T::ValueType&>;
};

template<typename T>
inline constexpr bool is_dense_matrix_like_v = dense_matrix_like<T>;

template<typename>
struct is_dense_matrix_like : std::false_type {};

template<dense_matrix_like T>
struct is_dense_matrix_like<T> : std::true_type {};

// is_dense_matrix, is_dense_matrix_v, dense_matrix
template<typename>
struct is_dense_matrix : std::false_type {};

template<typename U>
struct is_dense_matrix<DenseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_matrix_v = is_dense_matrix<T>::value;

template<typename T>
concept dense_matrix = is_dense_matrix_v<T>;


// is_dense_matrix_view, is_dense_matrix_view_v, dense_matrix_view
template<typename>
struct is_dense_matrix_view : std::false_type {};

template<typename U>
struct is_dense_matrix_view<DenseMatrixView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_matrix_view_v = is_dense_matrix_view<T>::value;

template<typename T>
concept dense_matrix_view = is_dense_matrix_view_v<T>;

// is_custom_dense_matrix, is_custom_dense_matrix_v, custom_dense_matrix
template<typename>
struct is_custom_dense_matrix : std::false_type {};

template<typename U>
struct is_custom_dense_matrix<CustomDenseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_custom_dense_matrix_v = is_custom_dense_matrix<T>::value;

template<typename T>
concept custom_dense_matrix = is_custom_dense_matrix_v<T>;


template<dense_matrix_like T>
struct underlying_type<T> {
    using value_type = T::ValueType;
};

/**
 * @brief Asserts that 'a', 'b', and 'args' have the same dimensions.
 * @tparam T Dense matrix type of 'a'.
 * @tparam U Dense matrix type of 'b'.
 * @tparam ARGS Dense matrix types of 'args'.
 * @param a First dense matrix to compare dimensions.
 * @param b Second dense matrix to compare dimensions.
 * @param args Rest of dense matrices to compare dimensions.
 * @throws InvalidDimensionException If 'a', 'b', and 'args' are not all of same dimensions.
 */
template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS>
inline void assert_same_dimensions(const T& a, const U& b, const ARGS&... args) {
    if (!(a.columns() == b.columns() && a.rows() == b.rows() && ((a.columns() == args.columns() && a.rows() == args.rows()) && ...))) {
        throw InvalidDimensionException("Dense matrices must all have same dimensions");
    }
}

/**
 * @brief Asserts that the 'm' matrix is square.
 * @tparam T Matrix type of 'm'.
 * @param m Dense matrix to test squareness of.
 * @throws InvalidDimensionException if the 'm' matrix is not square.
 */
template<dense_matrix_like T>
inline void assert_square(const T& m) {
    if (m.columns() != m.rows()) {
        throw InvalidDimensionException("Dense matrix must be square");
    }
}

template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS>
inline void assert_can_multiply(const T& a, const U& b, const ARGS&... args) {
    bool valid = a.columns() == b.rows();

    std::size_t current_cols = b.columns();

    if (!(valid && ((valid = (current_cols == args.rows()), current_cols = args.columns(), valid) && ...))) {
        throw InvalidDimensionException("Dense Matrices must have matching inner dimensions (a.columns() == b.rows())");
    }
}
