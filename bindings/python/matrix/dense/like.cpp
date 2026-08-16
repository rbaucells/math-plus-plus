#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../../main.h"
#include "like.h"
#include "../common/like.h"
#include "mathpp/implementation/matrix/dense/traits.h"

void dense_matrix_like_bindings(py::module_& m) {
    py::class_<DenseMatrixLikeBase, MatrixLikeBase>(m, "DenseMatrixLike")
        .def("at", [](const std::size_t r, const std::size_t c) -> py::object {
            PyErr_SetString(PyExc_NotImplementedError, "at function not implemented");
            throw py::error_already_set();
        })
        .def("__getitem__", [](const std::size_t r, const std::size_t c) -> py::object {
            PyErr_SetString(PyExc_NotImplementedError, "__getitem__ function not implemented");
            throw py::error_already_set();
        })
        .def("__setitem__", [](const std::size_t r, const std::size_t c, const py::object v) -> py::object {
            PyErr_SetString(PyExc_NotImplementedError, "__setitem__ function not implemented");
            throw py::error_already_set();
        })
        .def("data", [](const std::size_t i) -> py::object {
            PyErr_SetString(PyExc_NotImplementedError, "data function not implemented");
            throw py::error_already_set();
        });
}
