#pragma once

#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T>
struct SparseVectorBase;

template<scalar T>
struct SparseVector;

template<scalar T>
struct SparseVectorView;

template<scalar T>
struct CustomSparseVector;

// is_sparse_vector_base, is_sparse_vector_base_v, sparse_vector_base
template<typename T>
struct is_sparse_vector_base {
private:
    template<typename U>
    static std::true_type test(const SparseVectorBase<U>*) {
        return {};
    }

    static std::false_type test(...) {
        return {};
    }

public:
    static constexpr bool value = decltype(test(std::declval<std::remove_cvref_t<T>*>()))::value;
};

template<typename T>
inline constexpr bool is_sparse_vector_base_v = is_sparse_vector_base<T>::value;

template<typename T>
concept sparse_vector_base = is_sparse_vector_base_v<T>;

// is_sparse_vector, is_sparse_vector_v, sparse_vector
template<typename>
struct is_sparse_vector : std::false_type {};

template<typename U>
struct is_sparse_vector<SparseVector<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_sparse_vector_v = is_sparse_vector<T>::value;

template<typename T>
concept sparse_vector = is_sparse_vector_v<T>;

// is_sparse_vector_view, is_sparse_vector_view_v, sparse_vector_view
template<typename>
struct is_sparse_vector_view : std::false_type {};

template<typename U>
struct is_sparse_vector_view<SparseVectorView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_sparse_vector_view_v = is_sparse_vector_view<T>::value;

template<typename T>
concept sparse_vector_view = is_sparse_vector_view_v<T>;

// is_custom_sparse_vector, is_custom_sparse_vector_v, custom_sparse_vector
template<typename>
struct is_custom_sparse_vector : std::false_type {};

template<typename U>
struct is_custom_sparse_vector<CustomSparseVector<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_custom_sparse_vector_v = is_custom_sparse_vector<T>::value;

template<typename T>
concept custom_sparse_vector = is_custom_sparse_vector_v<T>;


template<sparse_vector_base T>
struct underlying_type<T> {
    using value_type = T::ValueType;
};

/**
 * @brief Asserts that 'a', 'b', and 'args' have the same size.
 * @tparam T Dense vector type of 'a'.
 * @tparam U Dense vector type of 'b'.
 * @tparam ARGS Dense vector types of 'args'.
 * @param a First dense vector to compare dimensions.
 * @param b Second dense vector to compare dimensions.
 * @param args Rest of dense vectors to compare dimensions.
 * @throws InvalidDimensionException If 'a', 'b', and 'args' are not all of same size.
 */
template<sparse_vector_base T, sparse_vector_base U, sparse_vector_base... ARGS>
inline void assert_same_size(const T& a, const U& b, const ARGS&... args) {
    if (!(a.n() == b.n() && ((a.n() == args.n()) && ...))) {
        throw InvalidDimensionException("Sparse vectors must all be of same size");
    }
}
