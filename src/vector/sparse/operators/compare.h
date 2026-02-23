#pragma once
#include "../vector.h"
#include "../../../helper.h"

template<sparse_vector_base T, sparse_vector_base... OTHERS>
[[nodiscard]] bool compare(const T& a, const OTHERS&... others) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>>>(), a, others...));
}

template<sparse_vector_base T, sparse_vector_base... OTHERS>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>>> precision,const T& a, const OTHERS&... others) {
    assert_same_size(a, others...);

    // early exit if not same number of non zero elements.
    if (((a.nnz() != others.nnz()) && ...)) {
        return false;
    }

    const int n = a.n;

    for (int i = 0; i < n; i++) {
        if (!compare(precision, a.get(i), others.get(i)...)) {
            return false;
        }
    }

    return true;
}