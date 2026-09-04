#include <pybind11/pybind11.h>

namespace py = pybind11;

void common_operators_compare_bindings(py::module_& m);

void common_operators_bindings(py::module_& m) {
    common_operators_compare_bindings(m);
}