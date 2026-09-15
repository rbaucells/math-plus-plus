#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <cstddef>

#include "like.h"

#include "../../main.h"

namespace py = pybind11;

py::class_<MatrixLikeBase> matrix_common_like_bindings(py::module_& m) {
    py::class_<MatrixLikeBase> matrix_like_base_py(m, "MatrixLike", "Base class for any 2D matrix that implements the MatrixLike functions");

    matrix_like_base_py
        .def(py::init<>())
        .def("dtype", [](MatrixLikeBase&) -> py::dtype {
            PyErr_SetString(PyExc_NotImplementedError, "dtype function not implemented");
            throw py::error_already_set();
        }, "Returns the dtype that represents the matrix's elements")
        .def("is_complex", [](MatrixLikeBase&) -> bool {
            PyErr_SetString(PyExc_NotImplementedError, "is_complex function not implemented");
            throw py::error_already_set();
        }, "Returns whether the matrix's elements are complex or real")
        .def("rows", [](MatrixLikeBase&) -> std::size_t {
            PyErr_SetString(PyExc_NotImplementedError, "rows function not implemented");
            throw py::error_already_set();
        }, "Returns the number of rows in the matrix")
        .def("columns", [](MatrixLikeBase&) -> std::size_t {
            PyErr_SetString(PyExc_NotImplementedError, "columns function not implemented");
            throw py::error_already_set();
        }, "Returns the number of columns in the matrix")
        .def("get", [](MatrixLikeBase&, std::size_t, std::size_t) -> AnyNumber {
            PyErr_SetString(PyExc_NotImplementedError, "get function not implemented");
            throw py::error_already_set();
        }, py::arg("r"), py::arg("c"), "Returns the element at row 'r' and column 'c'. Checks 'r' and 'c' are within bounds")
        .def("set", [](MatrixLikeBase&, std::size_t, std::size_t, const AnyNumber) -> void {
            PyErr_SetString(PyExc_NotImplementedError, "set function not implemented");
            throw py::error_already_set();
        }, py::arg("r"), py::arg("c"), py::arg("v"), "Sets the matrix's element at row 'r' and columns 'c' to 'v'. Checks 'r' and c' are within bounds");

    return matrix_like_base_py;
}
