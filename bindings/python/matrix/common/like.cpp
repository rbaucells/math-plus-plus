#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../../main.h"
#include "like.h"
#include "mathpp/implementation/matrix/common/traits.h"

void matrix_common_matrix_like_bindings(py::module_& m) {
    py::class_<MatrixLikeBase>(m, "MatrixLike")
        .def("dtype", []() -> py::dtype {
            PyErr_SetString(PyExc_NotImplementedError, "dtype function not implemented");
            throw py::error_already_set();
        })
        .def("is_complex", []() -> bool {
            PyErr_SetString(PyExc_NotImplementedError, "is_complex function not implemented");
            throw py::error_already_set();
        })
        .def("rows", []() -> std::size_t {
            PyErr_SetString(PyExc_NotImplementedError, "rows function not implemented");
            throw py::error_already_set();
        })
        .def("columns", []() -> std::size_t {
            PyErr_SetString(PyExc_NotImplementedError, "columns function not implemented");
            throw py::error_already_set();
        });
}
