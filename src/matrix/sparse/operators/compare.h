#pragma once
#include "../helper.h"

template<sparse_matrix_base T, sparse_matrix_base... OTHERS>
[[nodiscard]] bool compare(const T& a, const OTHERS&... others) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>>>(), a, others...));
}

template<sparse_matrix_base T, sparse_matrix_base... OTHERS>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>>> precision,const T& a, const OTHERS&... others) {
    assert_same_dimensions(a, others...);

    const int columns = a.columns;
    const int rows = a.rows;

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            if (!compare(precision, a.get(c, r), others.get(c, r)...)) {
                return false;
            }
        }
    }

    return true;
}
