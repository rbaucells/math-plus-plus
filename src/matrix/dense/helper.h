#pragma once
#include <string>

#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T>
struct DenseMatrixBase;

template<scalar T>
struct DenseMatrix;

template<scalar T>
struct DenseMatrixView;

template<scalar T>
struct CustomDenseMatrix;

// is_dense_matrix_base, is_dense_matrix_base_v, dense_matrix_base
template<typename T>
struct is_dense_matrix_base {
private:
    template<typename U>
    static std::true_type test(const DenseMatrixBase<U>*) {
        return {};
    }

    static std::false_type test(...) {
        return {};
    }

public:
    static constexpr bool value = decltype(test(std::declval<std::remove_cvref_t<T>*>()))::value;
};

template<typename T>
inline constexpr bool is_dense_matrix_base_v = is_dense_matrix_base<T>::value;

template<typename T>
concept dense_matrix_base = is_dense_matrix_base_v<T>;

// is_dense_matrix, is_dense_matrix_v, dense_matrix
template<typename T>
struct is_dense_matrix : std::false_type {};

template<typename U>
struct is_dense_matrix<DenseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_matrix_v = is_dense_matrix<T>::value;

template<typename T>
concept dense_matrix = is_dense_matrix_v<T>;


// is_dense_matrix_view, is_dense_matrix_view_v, dense_matrix_view
template<typename T>
struct is_dense_matrix_view : std::false_type {};

template<typename U>
struct is_dense_matrix_view<DenseMatrixView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_matrix_view_v = is_dense_matrix_view<T>::value;

template<typename T>
concept dense_matrix_view = is_dense_matrix_view_v<T>;

// is_custom_dense_matrix, is_custom_dense_matrix_v, custom_dense_matrix
template<typename T>
struct is_custom_dense_matrix : std::false_type {};

template<typename U>
struct is_custom_dense_matrix<CustomDenseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_custom_dense_matrix_v = is_custom_dense_matrix<T>::value;

template<typename T>
concept custom_dense_matrix = is_custom_dense_matrix_v<T>;


template<dense_matrix_base T>
struct underlying_type<T> {
    using value_type = T::ValueType;
};


template<dense_matrix_base T, dense_matrix_base U> requires HasCommonType<underlying_type_t<T>, underlying_type_t<U>>
bool compare(const T a, const U b, const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>> precision = epsilon<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>()) {
    return a.equals(b, precision);
}

/**
 * @brief Asserts that 'a' and 'b' have the same dimensions.
 * @tparam T Matrix type of 'a'.
 * @tparam U Matrix type of 'b'.
 * @param a Dense matrix to compare with 'b'.
 * @param b Dense matrix to compare with 'a'.
 * @param operation The name of the operation being done (e.g. "add", "multiply").
 * @throws InvalidDimensionException if the 'a' and 'b' matrices don't have the same dimensions.
 */
template<dense_matrix_base T, dense_matrix_base U>
inline void assert_same_dimensions(const T& a, const U& b, const std::string& operation) {
    if (a.columns != b.columns || a.rows != b.rows) {
        throw InvalidDimensionException(std::string("Cannot ") + operation + " with matrices of different dimensions");
    }
}

/**
 * @brief Asserts that the 'm' matrix is square.
 * @tparam T Matrix type of 'm'.
 * @param m Dense matrix to test squareness of.
 * @param operation The name of the operation being done (e.g. "add", "multiply").
 * @throws InvalidDimensionException if the 'm' matrix is not square.
 */
template<dense_matrix_base T>
inline void assert_square(const T& m, const std::string& operation) {
    if (m.columns != m.rows) {
        throw InvalidDimensionException(std::string("Cannot") + operation + " with non square matrix");
    }
}