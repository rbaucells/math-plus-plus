#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <cstddef>

#include "like.h"

namespace py = pybind11;

py::class_<MatrixLikeBase> matrix_common_matrix_like_bindings(py::module_& m) {
    py::class_<MatrixLikeBase> matrix_like_base_py(m, "MatrixLike");

    matrix_like_base_py
        .def(py::init<>())
        .def("dtype", [](MatrixLikeBase&) -> py::dtype {
            PyErr_SetString(PyExc_NotImplementedError, "dtype function not implemented");
            throw py::error_already_set();
        })
        .def("is_complex", [](MatrixLikeBase&) -> bool {
            PyErr_SetString(PyExc_NotImplementedError, "is_complex function not implemented");
            throw py::error_already_set();
        })
        .def("rows", [](MatrixLikeBase&) -> std::size_t {
            PyErr_SetString(PyExc_NotImplementedError, "rows function not implemented");
            throw py::error_already_set();
        })
        .def("columns", [](MatrixLikeBase&) -> std::size_t {
            PyErr_SetString(PyExc_NotImplementedError, "columns function not implemented");
            throw py::error_already_set();
        })
        .def("get", [](MatrixLikeBase&, std::size_t, std::size_t) -> py::object {
            PyErr_SetString(PyExc_NotImplementedError, "get function not implemented");
            throw py::error_already_set();
        }, py::arg("r"), py::arg("c"))
        .def("set", [](MatrixLikeBase&, std::size_t, std::size_t, const py::handle) -> void {
            PyErr_SetString(PyExc_NotImplementedError, "set function not implemented");
            throw py::error_already_set();
        }, py::arg("r"), py::arg("c"), py::arg("v"));

    return matrix_like_base_py;
}
