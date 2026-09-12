#ifndef MATHPY_VECTOR_DENSE_OPERATORS_MAIN_H
#define MATHPY_VECTOR_DENSE_OPERATORS_MAIN_H

#include <pybind11/pybind11.h>

#include "../like.h"
#include "../../common/like.h"

namespace py = pybind11;

void vector_dense_operators_bindings(py::module_& m, py::class_<DenseVectorLikeBase, VectorLikeBase> dense_vector_like_base_py);

#endif // MATHPY_VECTOR_DENSE_OPERATORS_MAIN_H
