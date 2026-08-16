#include "common/main.h"
#include "dense/main.h"
#include "sparse/main.h"
#include "main.h"

void vector_bindings(py::module_& m) {
    vector_common_bindings(m);
    vector_dense_bindings(m);
    vector_sparse_bindings(m);
}
