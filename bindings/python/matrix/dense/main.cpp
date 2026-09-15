#include <pybind11/pybind11.h>
#include "main.h"

#include "../common/like.h"
#include "like.h"
#include "operators/main.h"

namespace py = pybind11;

void matrix_dense_matrix_bindings(py::module_& m);
void matrix_dense_view_bindings(py::module_& m);
py::class_<DenseMatrixLikeBase, MatrixLikeBase> matrix_dense_like_bindings(py::module_& m);

void matrix_dense_bindings(py::module_& m) {
    py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py = matrix_dense_like_bindings(m);
    matrix_dense_matrix_bindings(m);
    matrix_dense_view_bindings(m);
    matrix_dense_operators_bindings(m, dense_matrix_like_base_py);
}
