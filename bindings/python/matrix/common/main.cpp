#include <pybind11/pybind11.h>
#include "main.h"

namespace py = pybind11;

void matrix_common_matrix_like_bindings(py::module_& m);

void matrix_common_bindings(py::module_& m) {
    matrix_common_matrix_like_bindings(m);
}
