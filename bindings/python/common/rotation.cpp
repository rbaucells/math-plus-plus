#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include "../main.h"
#include "mathpp/implementation/common/rotations.h"

void common_rotation_bindings(pybind11::module_& m) {
    py::enum_<RotationType>(m, "RotationType")
        .value("degrees", RotationType::degrees)
        .value("radians", RotationType::radians);

    m.def("radians_to_degrees", [](const py::object& rad) {
        const py::dtype dt = get_dtype(rad);

        return dispatch_dt(dt, [&]<typename T>() {
            return py::cast(radians_to_degrees(py::cast<T>(rad)));
        });
    }, py::arg("rad"));

    m.def("degrees_to_radians", [](const py::object& deg) {
        const py::dtype dt = get_dtype(deg);

        return dispatch_dt(dt, [&]<typename T>() {
            return py::cast(degrees_to_radians(py::cast<T>(deg)));
        });
    }, py::arg("deg"));

    m.def("convert", [](const RotationType from, const RotationType to, const py::object& value) {
        const py::dtype dt = get_dtype(value);

        return dispatch_dt(dt, [&]<typename T>() {
            return py::cast(convert(from, to, py::cast<T>(value)));
        });
    });
}
