#ifndef MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_ADD_ASSIGN
#define MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_ADD_ASSIGN

#include <cstddef>

#include "mathpp/implementation/common/traits.h"
#include "../../common/asserts.h"
#include "../traits.h"

/**
 * @brief Adds the elements of dense vector like object 'b' into dense vector like object 'a'.
 *
 * Does not allocate memory on the heap.
 * O(n) time complexity.
 *
 * @tparam T Dense vector like type of first param.
 * @tparam U Dense vector like type of second param.
 * @param a Reference to first dense vector like param where the result is stored.
 * @param b Second dense vector like param to add into 'a'.
 *
 * @return Reference to 'a' vector.
 * @note Does not do any bounds checking. Instead, assumes size of 'b' vector is same as of 'a' vector.
 */
template<dense_vector_like T, dense_vector_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
T& operator+=(T& a, const U& b) {
    const std::size_t n = a.n();

    for (std::size_t i = 0; i < n; i++) {
        a[i] += b[i];
    }

    return a;
}

/**
 * @brief Adds the elements of dense vector like object 'b' into dense vector like object 'a'.
 *
 * Does not allocate memory on the heap.
 * O(n) time complexity.
 *
 * @tparam T Dense vector like type of first param.
 * @tparam U Dense vector like type of second param.
 * @param a Reference to first dense vector like param where the result is stored.
 * @param b Second dense vector like param to add into 'a'.
 *
 *
 * @return Reference to 'a' vector.
 * @throws InvalidDimensionException If 'a', and 'b' are not of same size.
 * @note Both dense vector like object params must be of same size.
 */
template<dense_vector_like T, dense_vector_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
T& add_assign(T& a, const U& b) {
    assert_same_size(a, b);
    return a += b;
}

#endif // MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_ADD_ASSIGN
