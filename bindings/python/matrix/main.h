#ifndef MATHPY_MATRIX_MAIN_H
#define MATHPY_MATRIX_MAIN_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

void matrix_bindings(py::module_& m);

#endif // MATHPY_MATRIX_MAIN_H
