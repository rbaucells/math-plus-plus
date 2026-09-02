#include <pybind11/pybind11.h>

#include "main.h"
#include "common/main.h"
#include "csc/main.h"
#include "csr/main.h"

namespace py = pybind11;

void matrix_sparse_bindings(py::module_& m) {
    matrix_sparse_common_bindings(m);
    matrix_sparse_csc_bindings(m);
    matrix_sparse_csr_bindings(m);
}
