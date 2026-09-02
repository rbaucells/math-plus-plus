#include "main.h"
#include <pybind11/pybind11.h>

#include "common/main.h"
#include "coo/main.h"
#include "dok/main.h"

namespace py = pybind11;

void vector_sparse_bindings(py::module_& m) {
    vector_sparse_common_bindings(m);
    vector_sparse_coo_bindings(m);
    vector_sparse_dok_bindings(m);
}
