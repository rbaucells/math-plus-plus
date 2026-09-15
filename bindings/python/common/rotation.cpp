#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>

#include "../main.h"

#include "mathpp/implementation/common/rotations.h"

namespace py = pybind11;

void common_rotation_bindings(py::module_& m) {
    py::enum_<RotationType>(m, "RotationType")
        .value("degrees", RotationType::degrees)
        .value("radians", RotationType::radians);

    m.def("radians_to_degrees", [](const AnyNumber rad) -> AnyNumber {
        const py::dtype dt = get_dtype(rad);

        return dispatch_dt(dt, [&]<typename T>() -> AnyNumber {
            return py::cast(radians_to_degrees(py::cast<T>(rad)));
        });
    }, py::arg("radians"), "Converts input radians to output degrees");

    m.def("degrees_to_radians", [](const AnyNumber deg) -> AnyNumber {
        const py::dtype dt = get_dtype(deg);

        return dispatch_dt(dt, [&]<typename T>() -> AnyNumber {
            return py::cast(degrees_to_radians(py::cast<T>(deg)));
        });
    }, py::arg("degrees"), "Converts input degrees to output radians");

    m.def("convert", [](const RotationType from, const RotationType to, const AnyNumber value) -> AnyNumber {
        const py::dtype dt = get_dtype(value);

        return dispatch_dt(dt, [&]<typename T>() {
            return py::cast(convert(from, to, py::cast<T>(value)));
        });
    }, py::arg("from_rotation_type"), py::arg("to_rotation_type"), py::arg("value"), "Converts input rotation (of type 'from_rotation_type') to output rotation (of type 'to_rotation_type')");
}
