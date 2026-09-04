#ifndef MATHPY_MATRIX_DENSE_OPERATORS_COMPARE_H
#define MATHPY_MATRIX_DENSE_OPERATORS_COMPARE_H

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cstddef>

#include "../../common/like.h"
#include "../like.h"

#include "mathpp/implementation/common/precision.h"
#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/matrix/dense/operators/compare.h"

namespace py = pybind11;

template<typename T>
bool matrix_dense_operators_compare(const std::size_t size, const Precision<underlying_type_t<T>> precision, const py::sequence sequence) {
    auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> DenseMatrixLikePyWrapper<T> {
        return DenseMatrixLikePyWrapper<T>(sequence[i]);
    });

    return compare(precision, wrapper);
}

template<typename T>
bool matrix_dense_operators_compare(const std::size_t size, const Precision<underlying_type_t<T>> precision, const py::array array) {
    auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> DenseMatrixLikePyWrapper<T> {
        return DenseMatrixLikePyWrapper<T>(array[py::cast(i)]);
    });

    return compare(precision, wrapper);
}

#endif // MATHPY_MATRIX_DENSE_OPERATORS_COMPARE_H
