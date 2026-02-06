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
template<typename T>
struct is_sparse_vector : std::false_type {};

template<typename U>
struct is_sparse_vector<SparseVector<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_sparse_vector_v = is_sparse_vector<T>::value;

template<typename T>
concept sparse_vector = is_sparse_vector_v<T>;

// is_sparse_vector_view, is_sparse_vector_view_v, sparse_vector_view
template<typename T>
struct is_sparse_vector_view : std::false_type {};

template<typename U>
struct is_sparse_vector_view<SparseVectorView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_sparse_vector_view_v = is_sparse_vector_view<T>::value;

template<typename T>
concept sparse_vector_view = is_sparse_vector_view_v<T>;

// is_custom_sparse_vector, is_custom_sparse_vector_v, custom_sparse_vector
template<typename T>
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
 * @brief Asserts that 'a' and 'others' have the same size.
 * @tparam T Sparse Vector type of 'a'.
 * @tparam OTHERS Sparse Vector types of 'others'.
 * @param a Sparse vector to compare size with 'others'.
 * @param others Sparse vectors to compare size with 'a'.
 * @param operation The name of the operation being done (e.g "add", "dot").
 * @throws InvalidDimensionException If 'a' and 'others' are not all of same size.
 */
template<sparse_vector_base T, sparse_vector_base... OTHERS>
inline void assert_same_size(const T& a, const OTHERS&... others, const std::string& operation) {
    if (!((a.n == others.n) && ...)) {
        throw InvalidDimensionException(std::string("Cannot ") + operation + " with vectors of different size");
    }
}
