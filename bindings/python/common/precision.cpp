#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <variant>

#include "../main.h"
#include "precision.h"

#include "mathpp/implementation/common/precision.h"

namespace py = pybind11;

void common_precision_bindings(py::module_& m) {
    py::class_<Py_Precision>(m, "Precision")
            .def(py::init([](const py::handle value) {
                const py::dtype dt = get_dtype(value);

                return dispatch_dt_no_complex(dt, [&]<typename T>() -> Py_Precision {
                    return Py_Precision(std::in_place_type<Precision<T>>, py::cast<T>(value));
                });
            }), py::arg("value"))
            .def(py::init([](const py::handle value, const py::dtype dt) {
                return dispatch_dt_no_complex(dt, [&]<typename T>() {
                    return Py_Precision(std::in_place_type<Precision<T>>, py::cast<T>(value));
                });
            }), py::arg("value"), py::arg("dt"))
            .def_property("value", [](Py_Precision& self) -> py::object {
                              return std::visit([]<typename T>(const Precision<T>& p) -> py::object {
                                  return py::cast(p.value);
                              }, self);
                          }, [](Py_Precision& self, const py::handle value) {
                              std::visit([&]<typename T>(Precision<T>& p) {
                                  p.value = py::cast<T>(value);
                              }, self);
                          })
            .def_property_readonly("dtype", [](Py_Precision& self) -> py::dtype {
                return std::visit([]<typename T>(const Precision<T>& p) {
                    return py::dtype::of<T>();
                }, self);
            })
            .def("astype", [](Py_Precision& self, const py::dtype dt) {
                return std::visit([&]<typename T>(const Precision<T>& p) {
                    return dispatch_dt_no_complex(dt, [&]<typename U>() {
                        return Py_Precision(std::in_place_type<Precision<U>>, static_cast<U>(p.value));
                    });
                }, self);
            }, py::arg("dt"));
}