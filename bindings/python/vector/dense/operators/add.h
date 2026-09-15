#ifndef MATHPY_VECTOR_DENSE_OPERATORS_ADD_H
#define MATHPY_VECTOR_DENSE_OPERATORS_ADD_H

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cstddef>
#include <ranges>
#include <variant>
#include <string>
#include <type_traits>

#include "../../common/like.h"
#include "../like.h"

#include "mathpp/implementation/common/precision.h"
#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/vector/dense/operators/add.h"

namespace py = pybind11;

template<typename T>
bool vector_dense_operators_add(const std::size_t size, const py::sequence sequence) {
    auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> DenseVectorLikePyWrapper<T> {
        return DenseVectorLikePyWrapper<T>(sequence[i]);
    });

    return add(wrapper);
}

template<typename T>
bool vector_dense_operators_add(const std::size_t size, const py::array array) {
    auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> DenseVectorLikePyWrapper<T> {
        return DenseVectorLikePyWrapper<T>(array[py::cast(i)]);
    });

    return add(wrapper);
}

#endif //MATHPY_VECTOR_DENSE_OPERATORS_ADD_H
