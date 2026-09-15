#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <cstddef>

#include "like.h"

#include "../../main.h"

namespace py = pybind11;

py::class_<VectorLikeBase> vector_common_vector_like_bindings(py::module_& m) {
    py::class_<VectorLikeBase> vector_like_base_py(m, "VectorLike", "Base class for any 1D vector that implements the VectorLike functions");

    vector_like_base_py
        .def(py::init<>())
        .def("dtype", [](VectorLikeBase&) -> py::dtype {
            PyErr_SetString(PyExc_NotImplementedError, "dtype function not implemented");
            throw py::error_already_set();
        }, "Returns the dtype that represents the vector's elements")
        .def("is_complex", [](VectorLikeBase&) -> bool {
            PyErr_SetString(PyExc_NotImplementedError, "is_complex function not implemented");
            throw py::error_already_set();
        }, "Returns whether the vector's elements are complex or real")
        .def("n", [](VectorLikeBase&) -> std::size_t {
            PyErr_SetString(PyExc_NotImplementedError, "n function not implemented");
            throw py::error_already_set();
        }, "Returns the number of elements in the vector")
        .def("get", [](VectorLikeBase&, std::size_t) -> AnyNumber {
            PyErr_SetString(PyExc_NotImplementedError, "get function not implemented");
            throw py::error_already_set();
        }, py::arg("i"), "Returns the element at index 'i'. Checks 'i' is within bounds")
        .def("set", [](VectorLikeBase&, std::size_t, const AnyNumber) -> void {
            PyErr_SetString(PyExc_NotImplementedError, "set function not implemented");
            throw py::error_already_set();
        }, py::arg("i"), py::arg("v"), "Sets the vector's element at index 'i' to 'v'. Checks 'i' is within bounds");

    return vector_like_base_py;
}
