#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <cstddef>

#include "like.h"

namespace py = pybind11;

py::class_<VectorLikeBase> vector_common_vector_like_bindings(py::module_& m) {
    py::class_<VectorLikeBase> vector_like_base_py(m, "VectorLike");

    vector_like_base_py
        .def(py::init<>())
        .def("dtype", [](VectorLikeBase&) -> py::dtype {
            PyErr_SetString(PyExc_NotImplementedError, "dtype function not implemented");
            throw py::error_already_set();
        })
        .def("is_complex", [](VectorLikeBase&) -> bool {
            PyErr_SetString(PyExc_NotImplementedError, "is_complex function not implemented");
            throw py::error_already_set();
        })
        .def("n", [](VectorLikeBase&) -> std::size_t {
            PyErr_SetString(PyExc_NotImplementedError, "n function not implemented");
            throw py::error_already_set();
        })
        .def("get", [](VectorLikeBase&, std::size_t) -> py::object {
            PyErr_SetString(PyExc_NotImplementedError, "get function not implemented");
            throw py::error_already_set();
        }, py::arg("i"))
        .def("set", [](VectorLikeBase&, std::size_t, const py::handle) -> void {
            PyErr_SetString(PyExc_NotImplementedError, "set function not implemented");
            throw py::error_already_set();
        }, py::arg("i"), py::arg("v"));

    return vector_like_base_py;
}
