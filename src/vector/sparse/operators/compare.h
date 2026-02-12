#pragma once
#include "../vector.h"
#include "../../../helper.h"

template<sparse_vector_base T, sparse_vector_base... OTHERS>
[[nodiscard]] bool compare(const T& a, const OTHERS&... others, const underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>> precision = epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>>>()) {
    assert_same_size(a, others...);

    // early exit if not same number of non zero elements.
    if (((a.nnz() != others.nnz()) && ...)) {
        return false;
    }

    const int n = a.n;

    for (int i = 0; i < n; i++) {
        if (!compare<typename T::ValueType, typename OTHERS::ValueType...>(a[i], others[i]..., precision)) {
            return false;
        }
    }

    return true;
}