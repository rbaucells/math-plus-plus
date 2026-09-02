#include <pybind11/pybind11.h>
#include <cstddef>

#include "like.h"
#include "../common/like.h"

namespace py = pybind11;

py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_bindings(py::module_& m) {
    py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py(m, "DenseMatrixLike");

    dense_matrix_like_base_py
        .def(py::init<>())
        .def("__getitem__", [](DenseMatrixLikeBase&, const std::pair<std::size_t, std::size_t>&) -> py::object {
            PyErr_SetString(PyExc_NotImplementedError, "__getitem__ function not implemented");
            throw py::error_already_set();
        }, py::arg("indices"))
        .def("__setitem__", [](DenseMatrixLikeBase&, const std::pair<std::size_t, std::size_t>&, const py::object) -> void {
            PyErr_SetString(PyExc_NotImplementedError, "__setitem__ function not implemented");
            throw py::error_already_set();
        }, py::arg("indices"), py::arg("v"));

    return dense_matrix_like_base_py;
}
