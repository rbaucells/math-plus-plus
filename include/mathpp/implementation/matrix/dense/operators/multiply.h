#pragma once
#include <type_traits>
#include <cstddef>

#include "mathpp/implementation/common/traits.h"

#include "../../common/asserts.h"

#include "../traits.h"
#include "../matrix.h"

/**
 * @brief Multiplies 2 dense matrix like objects together.
 *
 * Allocates 'a.rows() * b.columns() * sizeof(std::common_type_t<typename T::ValueType, typename U::ValueType>)' bytes of memory on the heap.
 * Operation is O(n^3) time complexity.
 *
 * @tparam T Dense matrix like type of first param.
 * @tparam U Dense matrix like type of second param.
 * @param a First dense matrix like param.
 * @param b Second dense matrix like param.
 * @return The matrix-matrix multiplication of 'a' and 'b'.
 * @note Does not do dimensions checking. Instead, assumes 'a' and 'b' matrices have multipliable dimensions.
 */
template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType>> operator*(const T& a, const U& b) {
    const std::size_t aRows = a.rows();
    const std::size_t aColumns = a.columns();
    const size_t bColumns = b.columns();

    DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType>> result(aRows, bColumns, false);

    for (std::size_t c = 0; c < bColumns; c++) {
        for (std::size_t r = 0; r < aRows; r++) {
            result[r, c] = 0;

            for (std::size_t x = 0; x < aColumns; x++) {
                result[r, c] += a[r, x] * b[x, c];
            }
        }
    }

    return result;
}

/**
 * @brief Multiplies 2 dense matrix like objects together.
 *
 * Allocates 'a.rows() * b.columns() * sizeof(std::common_type_t<typename T::ValueType, typename U::ValueType>)' bytes of memory on the heap.
 * Operation is O(n^3) time complexity.
 *
 * @tparam T Dense matrix like type of first param.
 * @tparam U Dense matrix like type of second param.
 * @param a First dense matrix like param.
 * @param b Second dense matrix like param.
 * @return The matrix-matrix multiplication of 'a' and 'b'.
 * @throws InvalidDimensionException If the dimensions of 'a' and 'b' are not multipliable (inner dimensions don't match)
 * @note 'a' and 'b' must be multipliable in terms of their matching inner dimensions.
 */
template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType>> multiply(const T& a, const U& b) {
    assert_can_multiply(a, b);
    return a * b;
}