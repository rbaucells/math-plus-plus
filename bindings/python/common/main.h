#ifndef MATHPY_COMMON_MAIN_H
#define MATHPY_COMMON_MAIN_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

void common_bindings(py::module_& m);

#endif // MATHPY_COMMON_MAIN_H
