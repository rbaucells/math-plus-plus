#pragma once
#include "../helper.h"
#include "../../../helper.h"
#include <cstddef>

template<dense_vector_like T, dense_vector_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
T& add_assign(T& a, const U& b) {
    assert_same_size(a, b);

    const std::size_t n = a.n();

    for (std::size_t i = 0; i < n; i++) {
        a.at(i) += b.at(i);
    }

    return a;
}

template<dense_vector_like T, dense_vector_like U> requires has_common_type<typename T::ValueType, typename U::ValueType>
T& operator+=(T& a, const U& b) {
    return add_assign(a, b);
}
