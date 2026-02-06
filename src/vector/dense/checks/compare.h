#pragma once
#include "../vector.h"
#include "../../../helper.h"

template<dense_vector_base T, dense_vector_base... OTHERS>
[[nodiscard]] bool compare(const T& a, const OTHERS&... others, const underlying_type_t<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHERS>...>> precision = epsilon<underlying_type_t<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHERS>...>>>()) {
    assert_same_size(a, others..., "compare");

    const int columns = a.columns;
    const int rows = a.rows;

    for (int c = 0; c < columns; c++) {
        for (int r = 0; r < rows; r++) {
            if (!compare(a[c, r], others[c, r]..., precision)) {
                return false;
            }
        }
    }

    return true;
}
