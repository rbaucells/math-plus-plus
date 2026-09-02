#include <pybind11/pybind11.h>

#include "common/main.h"
#include "dense/main.h"
#include "sparse/main.h"

namespace py = pybind11;

void matrix_bindings(py::module_& m) {
    matrix_common_bindings(m);
    matrix_dense_bindings(m);
    matrix_sparse_bindings(m);
}
