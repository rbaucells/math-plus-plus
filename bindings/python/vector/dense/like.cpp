#include <pybind11/pybind11.h>
#include <cstddef>

#include "like.h"
#include "../common/like.h"

#include "../../main.h"

namespace py = pybind11;

py::class_<DenseVectorLikeBase, VectorLikeBase> dense_vector_like_bindings(py::module_& m) {
    py::class_<DenseVectorLikeBase, VectorLikeBase> dense_vector_like_base_py(m, "DenseVectorLike");

    dense_vector_like_base_py
        .def(py::init<>())
        .def("__getitem__", [](DenseVectorLikeBase&, std::size_t) -> AnyNumber {
            PyErr_SetString(PyExc_NotImplementedError, "__getitem__ function not implemented");
            throw py::error_already_set();
        }, py::arg("i"))
        .def("__setitem__", [](DenseVectorLikeBase&, std::size_t, const AnyNumber) -> void {
            PyErr_SetString(PyExc_NotImplementedError, "__setitem__ function not implemented");
            throw py::error_already_set();
        }, py::arg("i"), py::arg("v"));

    return dense_vector_like_base_py;
}
