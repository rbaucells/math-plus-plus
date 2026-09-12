#include <pybind11/pybind11.h>

#include "main.h"

#include "../like.h"
#include "../../common/like.h"

namespace py = pybind11;

void vector_dense_operators_compare_bindings(py::module_& m, py::class_<DenseVectorLikeBase, VectorLikeBase> dense_vector_like_base_py);
void vector_dense_operators_add_bindings(py::module_& m, py::class_<DenseVectorLikeBase, VectorLikeBase> dense_vector_like_base_py);

void vector_dense_operators_bindings(py::module_& m, py::class_<DenseVectorLikeBase, VectorLikeBase> dense_vector_like_base_py) {
    vector_dense_operators_compare_bindings(m, dense_vector_like_base_py);
    vector_dense_operators_add_bindings(m, dense_vector_like_base_py);
}