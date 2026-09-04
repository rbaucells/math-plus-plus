#ifndef MATHPY_MATRIX_DENSE_OPERATORS_MAIN_H
#define MATHPY_MATRIX_DENSE_OPERATORS_MAIN_H

#include <pybind11/pybind11.h>

#include "../like.h"
#include "../../common/like.h"

namespace py = pybind11;

void matrix_dense_operators_bindings(py::module_& m, py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py);

#endif // MATHPY_MATRIX_DENSE_OPERATORS_MAIN_H
