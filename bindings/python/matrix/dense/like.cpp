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
        .def("at", [](const DenseMatrixLikeBase& self, const std::size_t r, const std::size_t c) -> py::object {
            PyErr_SetString(PyExc_NotImplementedError, "at function not implemented");
            throw py::error_already_set();
        }, py::arg("r"), py::arg("c"))
        .def("__getitem__", [](const DenseMatrixLikeBase& self, const std::size_t r, const std::size_t c) -> py::object {
            PyErr_SetString(PyExc_NotImplementedError, "__getitem__ function not implemented");
            throw py::error_already_set();
        }, py::arg("r"), py::arg("c"))
        .def("__setitem__", [](const DenseMatrixLikeBase& self, const std::size_t r, const std::size_t c, const py::object v) -> void {
            PyErr_SetString(PyExc_NotImplementedError, "__setitem__ function not implemented");
            throw py::error_already_set();
        }, py::arg("r"), py::arg("c"), py::arg("v"))
        .def("data", [](const DenseMatrixLikeBase& self, const std::size_t i) -> py::object {
            PyErr_SetString(PyExc_NotImplementedError, "data function not implemented");
            throw py::error_already_set();
        }, py::arg("i"));
}
