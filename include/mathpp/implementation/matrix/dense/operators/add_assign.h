#ifndef MATHPP_IMPLEMENTATION_MATRIX_DENSE_OPERATORS_ADD_ASSIGN
#define MATHPP_IMPLEMENTATION_MATRIX_DENSE_OPERATORS_ADD_ASSIGN

#include <cstddef>

#include "mathpp/implementation/common/traits.h"
#include "../../common/asserts.h"
#include "../traits.h"

/**
 * @brief Adds the elements of dense matrix like object 'b' into dense matrix like object 'a'.
 *
 * Does not allocate memory on the heap.
 * O(n^2) time complexity.
 *
 * @tparam T Dense matrix like type of first param.
 * @tparam U Dense matrix like type of second param.
 * @param a Reference to first dense matrix like param where the result is stored.
 * @param b Second dense matrix like param to add into 'a'.
 *
 * @return Reference to 'a' matrix.
 * @note Does not do any bounds checking. Instead, assumes dimensions of 'b' matrix are same as of 'a' matrix.
 */
template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
T& operator+=(T& a, const U& b) {
    const std::size_t columns = a.columns();
    const std::size_t rows = a.rows();

    for (std::size_t c = 0; c < columns; c++) {
        for (std::size_t r = 0; r < rows; r++) {
            a[r, c] += b[r, c];
        }
    }

    return a;
}

/**
 * @brief Adds the elements of dense matrix like object 'b' into dense matrix like object 'a'.
 *
 * Does not allocate memory on the heap.
 * O(n^2) time complexity.
 *
 * @tparam T Dense matrix like type of first param.
 * @tparam U Dense matrix like type of second param.
 * @param a Reference to first dense matrix like param where the result is stored.
 * @param b Second dense matrix like param to add into 'a'.
 *
 *
 * @return Reference to 'a' matrix.
 * @throws InvalidDimensionException If 'a', and 'b' are not of same dimensions.
 * @note Both dense matrix like object params must be of same dimensions.
 */
template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
T& add_assign(T& a, const U& b) {
    assert_same_dimensions(a, b);
    return a += b;
}
#endif // MATHPP_IMPLEMENTATION_MATRIX_DENSE_OPERATORS_ADD_ASSIGN
