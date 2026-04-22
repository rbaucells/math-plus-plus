#pragma once
#include "../../../helper.h"
#include "../matrix.h"

template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>> multiply(const T& a, const U& b, const ARGS&... args) {
    if constexpr (sizeof...(args) == 0) {
        assert_can_multiply(a, b);

        const std::size_t aRows = a.rows();
        const std::size_t aColumns = a.columns();
        const size_t bColumns = b.columns();

        DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType>> result(aRows, bColumns, false);

        for (std::size_t c = 0; c < bColumns; c++) {
            for (std::size_t r = 0; r < aRows; r++) {
                result.at(r, c) = 0;

                for (std::size_t x = 0; x < aColumns; x++) {
                    result.at(r, c) += a.at(r, x) * b.at(x, c);
                }
            }
        }

        return result;
    }
    else {
        assert_can_multiply(a, b, args...);

        DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>> result = multiply(a, b);

        ((result = multiply(result, args)), ...);

        return result;
    }
}

template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
DenseMatrix<std::common_type_t<typename T::ValueType, typename U::ValueType>> operator*(const T& a, const U& b) {
    return multiply(a, b);
}
