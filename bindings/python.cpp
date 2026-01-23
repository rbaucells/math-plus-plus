#include <pybind11/pybind11.h>
#include <pybind11/native_enum.h>
#include "math++/math.h"

namespace py = pybind11;

PYBIND11_MODULE(mathpy, m) {
    // 1. Define the enum
    py::native_enum<RotationType>(m, "RotationType", "enum.Enum")
        .value("radians", RotationType::radians)
        .value("degrees", RotationType::degrees)
        .export_values()
        .finalize();

    m.def("convert", [](const RotationType from, const RotationType to, const float rotation) -> float {
        return convert<float>(from, to, rotation);
    }, py::arg("from"), py::arg("to"), py::arg("rotation"));

    m.def("convert", [](const RotationType from, const RotationType to, const double rotation) -> double {
        return convert<double>(from, to, rotation);
    }, py::arg("from"), py::arg("to"), py::arg("rotation"));
}