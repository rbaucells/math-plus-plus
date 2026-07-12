#ifndef MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_DOT
#define MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_DOT

#include <complex>
#include <type_traits>
#include <cstddef>

#include "mathpp/implementation/common/dot_behavior.h"

#include "../../common/asserts.h"

#include "../traits.h"

/**
 * @brief Dots 2 dense vector like objects together.
 *
 * Allocates no memory on the heap.
 * Operation is O(n) time complexity.
 * Uses default conjugation behavior (DEFAULT_CONJUGATION_BEHAVIOR).
 *
 * @tparam T Dense vector like type of first param.
 * @tparam U Dense vector like type of second param.
 * @param a First dense vector like param.
 * @param b Second dense vector like param.
 * @return The vector-vector dot of 'a' and 'b'.
 * @note Does not do size checking. Instead, assumes 'a' and 'b' vectors have same size.
 */
template<dense_vector_like T, dense_vector_like U>
std::common_type_t<typename T::ValueType, typename U::ValueType> operator*(const T& a, const U& b) {
    const std::size_t n = a.n();

    std::common_type_t<typename T::ValueType, typename U::ValueType> result = 0;

    for (std::size_t i = 0; i < n; i++) {
        if constexpr (T::isComplex || U::isComplex) {
            if constexpr (DEFAULT_CONJUGATION_BEHAVIOR == DotProductConjugationBehavior::first_argument) {
                result += std::conj(a.at(i)) * b.at(i);
            }
            else if constexpr (DEFAULT_CONJUGATION_BEHAVIOR == DotProductConjugationBehavior::neither) {
                result += a.at(i) * b.at(i);
            }
            else if constexpr (DEFAULT_CONJUGATION_BEHAVIOR == DotProductConjugationBehavior::second_argument) {
                result += a.at(i) * std::conj(b.at(i));
            }
        }
        else {
            result += a.at(i) * b.at(i);
        }
    }

    return result;
}

/**
 * @brief Dots 2 dense vector like objects together.
 *
 * Allocates no memory on the heap.
 * Operation is O(n) time complexity.
 *
 * @tparam T Dense vector like type of first param.
 * @tparam U Dense vector like type of second param.
 * @param a First dense vector like param.
 * @param b Second dense vector like param.
 * @return The vector-vector dot of 'a' and 'b'.
 * @throws InvalidSizeException If the size of 'a' and 'b' are not same.
 * @note 'a' and 'b' must have same size.
 */
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
#endif // MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_DOT
