#include <pybind11/pybind11.h>
#include <cstddef>

#include "mathpp/implementation/common/telemetry.h"

namespace py = pybind11;

void common_telemetry_bindings(pybind11::module_& m) {
    py::class_<TelemetryStats>(m, "TelemetryStats")
        .def(py::init<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t, std::size_t, std::size_t>(), py::arg("copy_constructs") = 0, py::arg("move_constructs") = 0, py::arg("copy_assigns") = 0, py::arg("move_assigns") = 0, py::arg("allocations") = 0, py::arg("deallocations") = 0, py::arg("dimensions_checks") = 0)
        .def_readwrite("copy_constructs", &TelemetryStats::copy_constructs)
        .def_readwrite("move_constructs", &TelemetryStats::move_constructs)
        .def_readwrite("copy_assigns", &TelemetryStats::copy_assigns)
        .def_readwrite("move_assigns", &TelemetryStats::move_assigns)
        .def_readwrite("allocations", &TelemetryStats::allocations)
        .def_readwrite("deallocations", &TelemetryStats::deallocations)
        .def_readwrite("dimensions_checks", &TelemetryStats::dimensions_checks);

    py::module_ telemetry_module = m.def_submodule("Telemetry");

    telemetry_module.def("emit_copy_construct", &Telemetry::emit_copy_construct);
    telemetry_module.def("emit_move_construct", &Telemetry::emit_move_construct);
    telemetry_module.def("emit_copy_assign", &Telemetry::emit_copy_assign);
    telemetry_module.def("emit_move_assign", &Telemetry::emit_move_assign);
    telemetry_module.def("emit_allocation", &Telemetry::emit_allocation);
    telemetry_module.def("emit_deallocation", &Telemetry::emit_deallocation);
    telemetry_module.def("emit_dimension_check", &Telemetry::emit_dimension_check);
    telemetry_module.def("reset", &Telemetry::reset);
    telemetry_module.def("snapshot", &Telemetry::snapshot);
}