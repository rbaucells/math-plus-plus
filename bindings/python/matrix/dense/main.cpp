#include "main.h"

void dense_matrix_bindings(py::module_& m);
void dense_matrix_like_bindings(py::module_& m);

void matrix_dense_bindings(py::module_& m) {
    dense_matrix_like_bindings(m);
    dense_matrix_bindings(m);
}
