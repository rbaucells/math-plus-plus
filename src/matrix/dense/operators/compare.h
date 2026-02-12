#pragma once
#include "../matrix.h"
#include "../../../helper.h"

template<dense_matrix_base T, dense_matrix_base... OTHERS>
[[nodiscard]] bool compare(const T& a, const OTHERS&... others, const underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>> precision = epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>>>()) {
    assert_same_dimensions(a, others...);

    const int columns = a.columns;
    const int rows = a.rows;

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            if (!compare<typename T::ValueType, typename OTHERS::ValueType...>(a[c, r], others[c, r]..., precision)) {
                return false;
            }
        }
    }

    return true;
}