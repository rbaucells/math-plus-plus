#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <complex>
#include "../main.h"
#include "mathpp/implementation/common/precision.h"
#include "precision.h"

void common_precision_bindings(pybind11::module_& m) {
    py::class_<Py_Precision>(m, "Precision")
            .def(py::init([](const py::object& value) {
                const py::dtype dt = get_dtype(value);

                return dispatch_dt_no_complex(dt, [&]<typename T>() {
                    return Py_Precision(std::in_place_type<Precision<T>>, py::cast<T>(value));
                });
            }), py::arg("value"))
            .def(py::init([](const py::object& value, const py::dtype& dt) {
                return dispatch_dt_no_complex(dt, [&]<typename T>() {
                    return Py_Precision(std::in_place_type<Precision<T>>, py::cast<T>(value));
                });
            }), py::arg("value"), py::arg("dt"))
            .def_property("value", [](Py_Precision& self) {
                              return std::visit([](const auto& p) {
                                  return py::cast(p.value);
                              }, self);
                          }, [](Py_Precision& self, const py::object& value) {
                              std::visit([&](auto& p) {
                                  using T = std::decay_t<decltype(p)>::ValueType;
                                  p.value = py::cast<T>(value);
                              }, self);
                          })
            .def_property_readonly("dtype", [](Py_Precision& self) -> py::dtype {
                return std::visit([](const auto& p) {
                    using T = std::decay_t<decltype(p)>::ValueType;
                    return py::dtype::of<T>();
                }, self);
            })
            .def("astype", [](Py_Precision& self, py::dtype dt) {
                return std::visit([&](const auto& p) {
                    return dispatch_dt_no_complex(dt, [&]<typename T>() {
                        return Py_Precision(std::in_place_type<Precision<T>>, static_cast<T>(p.value));
                    });
                }, self);
            }, py::arg("dt"));
}