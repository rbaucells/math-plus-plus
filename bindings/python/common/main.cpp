#include "main.h"

#include <pybind11/pybind11.h>

void common_compare_bindings(pybind11::module_& m);
void common_precision_bindings(pybind11::module_& m);
void common_rotation_bindings(pybind11::module_& m);

void common_bindings(py::module_& m) {
    common_compare_bindings(m);
    common_precision_bindings(m);
    common_rotation_bindings(m);
}
