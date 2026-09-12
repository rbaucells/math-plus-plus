#include <pybind11/pybind11.h>
#include "main.h"

#include "like.h"

namespace py = pybind11;

py::class_<VectorLikeBase> vector_common_vector_like_bindings(py::module_& m);

void vector_common_bindings(py::module_& m) {
    py::class_<VectorLikeBase> vector_like_base_py = vector_common_vector_like_bindings(m);
}
