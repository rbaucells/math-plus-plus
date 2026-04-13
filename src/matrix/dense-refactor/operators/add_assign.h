#pragma once
#include "../matrix.h"
#include "../../../helper.h"

template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
T& add_assign(T& a, const U& b) {
    assert_same_dimensions(a, b);

    const int columns = a.columns();
    const int rows = a.rows();

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            a[c, r] += b[c, r];
        }
    }

    return a;
}

template<dense_matrix_like T, dense_matrix_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
T& operator+=(T& a, const U& b) {
    return add_assign(a, b);
}