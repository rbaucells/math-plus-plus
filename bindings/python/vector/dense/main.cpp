#include <pybind11/pybind11.h>
#include "main.h"

#include "../common/like.h"
#include "like.h"
#include "operators/main.h"

namespace py = pybind11;

void dense_vector_bindings(py::module_& m);
void dense_vector_view_bindings(py::module_& m);
py::class_<DenseVectorLikeBase, VectorLikeBase> dense_vector_like_bindings(py::module_& m);

void vector_dense_bindings(py::module_& m) {
    py::class_<DenseVectorLikeBase, VectorLikeBase> dense_vector_like_base_py = dense_vector_like_bindings(m);
    dense_vector_bindings(m);
    dense_vector_view_bindings(m);
    vector_dense_operators_bindings(m, dense_vector_like_base_py);
}
