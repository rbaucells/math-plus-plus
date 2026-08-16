#ifndef MATHPY_VECTOR_COMMON_MAIN_H
#define MATHPY_VECTOR_COMMON_MAIN_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

void vector_common_bindings(py::module_& m);

#endif // MATHPY_VECTOR_COMMON_MAIN_H
