#ifndef MATHPP_IMPLEMENTATION_MATRIX_DENSE_TRAITS_H
#define MATHPP_IMPLEMENTATION_MATRIX_DENSE_TRAITS_H

#include <concepts>
#include <type_traits>

#include "../common/traits.h"
#include "mathpp/implementation/common/traits.h"

// forward declare
template<scalar T>
struct DenseMatrix;

template<scalar T>
struct DenseMatrixView;

// dense_matrix_like
template<typename T>
concept dense_matrix_like = requires(T m, const T constM, std::size_t r, std::size_t c, std::size_t i) {
    requires matrix_like<T>;

    // accessing
    requires std::same_as<std::remove_cvref_t<decltype(constM.at(r, c))>, typename T::ValueType>;
    requires std::same_as<std::remove_cvref_t<decltype(constM[r, c])>, typename T::ValueType>;

    // arrays
    requires std::same_as<std::remove_cvref_t<decltype(constM.data(i))>, typename T::ValueType>;
};

template<typename T>
inline constexpr bool is_dense_matrix_like_v = dense_matrix_like<T>;

template<typename>
struct is_dense_matrix_like : std::false_type {};

template<dense_matrix_like T>
struct is_dense_matrix_like<T> : std::true_type {};

// dense_matrix
template<typename>
struct is_dense_matrix : std::false_type {};

template<typename U>
struct is_dense_matrix<DenseMatrix<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_matrix_v = is_dense_matrix<T>::value;

template<typename T>
concept dense_matrix = is_dense_matrix_v<T>;

// dense_matrix_view
template<typename>
struct is_dense_matrix_view : std::false_type {};

template<typename U>
struct is_dense_matrix_view<DenseMatrixView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_matrix_view_v = is_dense_matrix_view<T>::value;

template<typename T>
concept dense_matrix_view = is_dense_matrix_view_v<T>;

#endif // MATHPP_IMPLEMENTATION_MATRIX_DENSE_TRAITS_H
