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
            .def(py::init([](const py::handle value) -> Py_Precision {
                const py::dtype dt = get_dtype(value);

                return dispatch_dt_no_complex(dt, [&]<typename T>() -> Py_Precision {
                    return Py_Precision(std::in_place_type<Precision<T>>, py::cast<T>(value));
                });
            }), py::arg("value"))
            .def(py::init([](const py::dtype dt, const py::handle value) -> Py_Precision {
                const py::dtype valueDt = get_dtype(value);

                return dispatch_dt_no_complex(dt, [&]<typename T>() -> Py_Precision {
                    return dispatch_dt_no_complex(valueDt, [&]<typename U>() -> Py_Precision {
                        if constexpr (lossless_convertible<U, T>) {
                            return Py_Precision(std::in_place_type<Precision<T>>, py::cast<T>(value));
                        }
                        else {
                            throw py::type_error("Cannot convert value to dt while constructing precision");
                        }
                    });
                });
            }), py::arg("value"), py::arg("dt"))
            .def_property("value",
                [](Py_Precision& self) -> py::object {
                      return std::visit([]<typename T>(const Precision<T>& p) -> py::object {
                          return py::cast(p.value);
                      }, self);
                    },
                [](Py_Precision& self, const py::handle value) {
                        const py::dtype dt = get_dtype(value);

                        std::visit([&]<typename T>(Precision<T>& p) {
                            dispatch_dt_no_complex(dt, [&]<typename U>() {
                                if constexpr (lossless_convertible<U, T>) {
                                    p.value = py::cast<T>(value);
                                }
                                else {
                                    throw py::type_error("Cannot convert value to dt of precision while setting value");
                                }
                            });
                        }, self);
                    })
            .def_property_readonly("dtype", [](Py_Precision& self) -> py::dtype {
                return std::visit([]<typename T>(const Precision<T>& p) {
                    return py::dtype::of<T>();
                }, self);
            })
            .def("astype", [](Py_Precision& self, const py::dtype dt) -> Py_Precision  {
                return std::visit([&]<typename T>(const Precision<T>& p) {
                    return dispatch_dt_no_complex(dt, [&]<typename U>() {
                        return Py_Precision(std::in_place_type<Precision<U>>, static_cast<U>(p.value));
                    });
                }, self);
            }, py::arg("dt"));
}
