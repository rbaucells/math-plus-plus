#pragma once
#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T>
struct DenseVectorBase;

template<scalar T>
struct DenseVector;

template<scalar T>
struct DenseVectorView;

template<scalar T>
struct CustomDenseVector;

// is_dense_vector_base, is_dense_vector_base_v, dense_vector_base
template<typename T>
struct is_dense_vector_base {
private:
    template<typename U>
    static std::true_type test(const DenseVectorBase<U>*) {
        return {};
    }

    static std::false_type test(...) {
        return {};
    }

public:
    static constexpr bool value = decltype(test(std::declval<std::remove_cvref_t<T>*>()))::value;
};

template<typename T>
inline constexpr bool is_dense_vector_base_v = is_dense_vector_base<T>::value;

template<typename T>
concept dense_vector_base = is_dense_vector_base_v<T>;

// is_dense_vector, is_dense_vector_v, dense_vector
template<typename T>
struct is_dense_vector : std::false_type {};

template<typename U>
struct is_dense_vector<DenseVector<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_vector_v = is_dense_vector<T>::value;

template<typename T>
concept dense_vector = is_dense_vector_v<T>;

// is_dense_vector_view, is_dense_vector_view_v, dense_vector_view
template<typename T>
struct is_dense_vector_view : std::false_type {};

template<typename U>
struct is_dense_vector_view<DenseVectorView<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_dense_vector_view_v = is_dense_vector_view<T>::value;

template<typename T>
concept dense_vector_view = is_dense_vector_view_v<T>;

// is_custom_dense_vector, is_custom_dense_vector_v, custom_dense_vector
template<typename T>
struct is_custom_dense_vector : std::false_type {};

template<typename U>
struct is_custom_dense_vector<CustomDenseVector<U>> : std::true_type {};

template<typename T>
inline constexpr bool is_custom_dense_vector_v = is_custom_dense_vector<T>::value;

template<typename T>
concept custom_dense_vector = is_custom_dense_vector_v<T>;


template<dense_vector_base T>
struct underlying_type<T> {
    using value_type = T::ValueType;
};

/**
 * @brief Asserts that 'a' and 'others' have the same size.
 * @tparam T Dense Vector type of 'a'.
 * @tparam OTHERS Dense Vector types of 'others'.
 * @param a Dense vector to compare size with 'others'.
 * @param others Dense vectors to compare size with 'a'.
 * @param operation The name of the operation being done (e.g "add", "dot").
 * @throws InvalidDimensionException If 'a' and 'others' are not all of same size.
 */
template<dense_vector_base T, dense_vector_base... OTHERS>
inline void assert_same_size(const T& a, const OTHERS&... others, const std::string& operation) {
    if (!((a.n == others.n) && ...)) {
        throw InvalidDimensionException(std::string("Cannot ") + operation + " with vectors of different size");
    }
}
