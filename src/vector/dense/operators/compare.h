#pragma once
#include "../vector.h"
#include "../../../helper.h"

template<dense_vector_base T, dense_vector_base... OTHERS>
[[nodiscard]] bool compare(const T& a, const OTHERS&... others) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>>>(), a, others...));
}

template<dense_vector_base T, dense_vector_base... OTHERS>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename OTHERS::ValueType...>>> precision,const T& a, const OTHERS&... others) {
    assert_same_size(a, others...);

    const int n = a.n;

    for (int i = 0; i < n; i++) {
        if (!compare(precision, a[i], others[i]...)) {
            return false;
        }
    }

    return true;
}
