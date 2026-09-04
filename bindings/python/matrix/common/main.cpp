#include <pybind11/pybind11.h>
#include "main.h"

#include "like.h"

namespace py = pybind11;

py::class_<MatrixLikeBase> matrix_common_matrix_like_bindings(py::module_& m);

void matrix_common_bindings(py::module_& m) {
    py::class_<MatrixLikeBase> matrix_like_base_py = matrix_common_matrix_like_bindings(m);
}
