#include <pybind11/pybind11.h>

#include "main.h"

namespace py = pybind11;

void common_precision_bindings(py::module_& m);
void common_compare_bindings(py::module_& m);
void common_rotation_bindings(py::module_& m);
void common_telemetry_bindings(py::module_& m);

void common_bindings(py::module_& m) {
    common_precision_bindings(m);
    common_compare_bindings(m);
    common_rotation_bindings(m);
    common_telemetry_bindings(m);
}
