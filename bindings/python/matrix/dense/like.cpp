#include <pybind11/pybind11.h>
#include <cstddef>
#include <utility>

#include "like.h"
#include "../common/like.h"

#include "../../main.h"

namespace py = pybind11;

py::class_<DenseMatrixLikeBase, MatrixLikeBase> matrix_dense_like_bindings(py::module_& m) {
    py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py(m, "DenseMatrixLike", "Base class for any dense 2D matrix that implements the DenseMatrixLike functions + the MatrixLike functions");

    dense_matrix_like_base_py
        .def(py::init<>())
        .def("__getitem__", [](DenseMatrixLikeBase&, const std::pair<std::size_t, std::size_t>&) -> AnyNumber {
            PyErr_SetString(PyExc_NotImplementedError, "__getitem__ function not implemented");
            throw py::error_already_set();
        }, py::arg("indices"), "Returns the element in the matrix at 'indices' ([0] = row, [1] = col). Does not check bounds of 'indices'")
        .def("__setitem__", [](DenseMatrixLikeBase&, const std::pair<std::size_t, std::size_t>&, const AnyNumber) -> void {
            PyErr_SetString(PyExc_NotImplementedError, "__setitem__ function not implemented");
            throw py::error_already_set();
        }, py::arg("indices"), py::arg("v"), "Sets the element in the matrix at 'indices' ([0] = row, [1] = col) to 'v'. Does not check bounds of 'indices'");

    return dense_matrix_like_base_py;
}
