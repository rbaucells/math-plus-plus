#include <pybind11/pybind11.h>
#include "main.h"

#include "../common/like.h"
#include "like.h"
#include "operators/main.h"

namespace py = pybind11;

void dense_matrix_bindings(py::module_& m);
py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_bindings(py::module_& m);

void matrix_dense_bindings(py::module_& m) {
    py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py = dense_matrix_like_bindings(m);
    dense_matrix_bindings(m);
    matrix_dense_operators_bindings(m, dense_matrix_like_base_py);
}
