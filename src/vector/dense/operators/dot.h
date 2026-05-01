#pragma once
#include "../helper.h"
#include <type_traits>
#include "../../../helper.h"
#include <cstddef>

template<dense_vector_like T, dense_vector_like U>
std::common_type_t<typename T::ValueType, typename U::ValueType> dot(const T& a, const U& b, const DotProductConjugationBehavior behavior = DEFAULT_CONJUGATION_BEHAVIOR) {
    assert_same_size(a, b);

    const std::size_t n = a.n();

    std::common_type_t<typename T::ValueType, typename U::ValueType> result = 0;

    for (std::size_t i = 0; i < n; i++) {
        if constexpr (T::isComplex || U::isComplex) {
            switch (behavior) {
                case DotProductConjugationBehavior::first_argument:
                    result += std::conj(a.at(i)) * b.at(i);
                    break;
                case DotProductConjugationBehavior::neither:
                    result += a.at(i) * b.at(i);
                    break;
                case DotProductConjugationBehavior::second_argument:
                    result += a.at(i) * std::conj(b.at(i));
                    break;
            }
        }
        else {
            result += a.at(i) * b.at(i);
        }
    }

    return result;
}

template<dense_vector_like T, dense_vector_like U>
std::common_type_t<typename T::ValueType, typename U::ValueType> operator*(const T& a, const U& b) {
    return dot(a, b, DEFAULT_CONJUGATION_BEHAVIOR);
}

