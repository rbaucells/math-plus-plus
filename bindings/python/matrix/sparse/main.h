#ifndef MATHPY_SPARSE_MAIN_H
#define MATHPY_SPARSE_MAIN_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

void matrix_sparse_bindings(py::module_& m);

#endif // MATHPY_SPARSE_MAIN_H
