#include <pybind11/pybind11.h>

#include "main.h"

#include "../like.h"
#include "../../common/like.h"

namespace py = pybind11;

void matrix_dense_operators_compare_bindings(py::module_& m, py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py);

void matrix_dense_operators_bindings(py::module_& m, py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py) {
    matrix_dense_operators_compare_bindings(m, dense_matrix_like_base_py);
}