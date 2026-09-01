#ifndef MATHPY_MATRIX_DENSE_OPERATORS_COMPARE_H
#define MATHPY_MATRIX_DENSE_OPERATORS_COMPARE_H

#include "../like.h"
#include <ranges>

#include "mathpp/implementation/matrix/dense/operators/compare.h"

template<typename T>
bool py_dense_matrix_like_compare(const std::size_t size, const Precision<underlying_type_t<T>> precision, const py::sequence& sequence) {
    auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> DenseMatrixLikePyWrapper<T> {
        return DenseMatrixLikePyWrapper<T>(sequence[i]);
    });

    return compare(precision, wrapper);
}

template<typename T>
bool py_dense_matrix_like_compare(const std::size_t size, const Precision<underlying_type_t<T>> precision, const py::array& array) {
    auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> DenseMatrixLikePyWrapper<T> {
        return DenseMatrixLikePyWrapper<T>(array[py::cast(i)]);
    });

    return compare(precision, wrapper);
}

#endif // MATHPY_MATRIX_DENSE_OPERATORS_COMPARE_H
