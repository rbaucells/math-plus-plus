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

template<sparse_vector_base T, sparse_vector_base U> requires HasCommonType<underlying_type_t<T>, underlying_type_t<U>>
bool compare(const T a, const U b, const std::common_type_t<underlying_type_t<T>, underlying_type_t<U>> precision = epsilon<std::common_type_t<underlying_type_t<T>, underlying_type_t<U>>>()) {
    return a.equals(b, precision);
}

/**
 * @brief Asserts that 'a' and 'b' have the same size.
 * @tparam T Vector type of 'a'.
 * @tparam U Vector type of 'b'.
 * @param a Sparse vector to compare with 'b'.
 * @param b Sparse vector to compare with 'a'.
 * @param operation The name of the operation being done (e.g "add", "dot").
 */
template<sparse_vector_base T, sparse_vector_base U>
inline void assert_same_size(const T& a, const U& b, const std::string& operation) {
    if (a.n != b.n) {
        throw InvalidDimensionException(std::string("Cannot ") + operation + " with vectors of different size");
    }
}
