#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <complex>
#include "../main.h"
#include "mathpp/implementation/common/compare.h"

using Py_Precision = PyWrapper<std::variant<Precision<int8_t>, Precision<uint8_t>, Precision<int16_t>, Precision<uint16_t>, Precision<int32_t>, Precision<uint32_t>, Precision<int64_t>, Precision<uint64_t>, Precision<float>, Precision<double>>>;

void compare_bindings(pybind11::module_& m) {
    py::class_<Py_Precision>(m, "Precision")
            .def(py::init([](const py::object& value) {
                const py::dtype dt = get_dtype(value);

                return dispatch_dt_no_complex(dt, [&]<typename T>() {
                    return Py_Precision(Precision<T>(py::cast<T>(value)));
                });
            }), py::arg("value"))
            .def(py::init([](const py::object& value, const py::dtype& dt) {
                return dispatch_dt_no_complex(dt, [&]<typename T>() {
                    return Py_Precision(Precision<T>(py::cast<T>(value)));
                });
            }), py::arg("value"), py::arg("dt"))
            .def_property("value", [](Py_Precision& self) {
                              return std::visit([](const auto& p) {
                                  return py::cast(p.value);
                              }, self.storage);
                          }, [](Py_Precision& self, const py::object& value) {
                              std::visit([&](auto& p) {
                                  using T = std::decay_t<decltype(p)>::ValueType;
                                  p.value = py::cast<T>(value);
                              }, self.storage);
                          })
            .def_property_readonly("dtype", [](Py_Precision& self) -> py::dtype {
                return std::visit([](const auto& p) {
                    using T = std::decay_t<decltype(p)>::ValueType;

                    return py::dtype::of<T>();
                }, self.storage);
            })
            .def("astype", [](Py_Precision& self, py::dtype dt) {
                return std::visit([&](const auto& p) {
                    return dispatch_dt_no_complex(dt, [&]<typename T>() {
                        return Py_Precision(Precision<T>(static_cast<T>(p.value)));
                    });
                }, self.storage);
            }, py::arg("dt"));

    m.def("compare", [](const Py_Precision& precision, const py::args& args) {
        const py::dtype dt = get_common_dtype(args);

        return dispatch_dt(dt, [&]<typename T>() {
            std::vector<T> vec(args.size());

            for (std::size_t i = 0; i < args.size(); i++) {
                vec[i] = py::cast<T>(args[i]);
            }

            return std::visit([&](const auto& p) -> bool {
                using U = std::decay_t<decltype(p)>::ValueType;

                if constexpr (is_lossless_convertible<U, T>) {
                    using UnderlyingT = underlying_type_t<T>;
                    const Precision<UnderlyingT> casted(p.value);

                    return compare(casted, std::span<const T>(vec));
                }
                else {
                    throw py::type_error("Precision type does not match args type");
                }
            }, precision.storage);
        });
    });

    m.def("compare", [](const py::args& args) {
        const py::dtype dt = get_common_dtype(args);

        return dispatch_dt(dt, [&]<typename T>() {
            std::vector<T> vec(args.size());

            for (std::size_t i = 0; i < args.size(); i++) {
                vec[i] = py::cast<T>(args[i]);
            }

            return compare<T>(Precision<underlying_type_t<T>>(epsilon<T>()), std::span<const T>(vec));
        });
    });

    m.def("compare", [](const Py_Precision& precision, const py::iterable& iterable) {
        const py::dtype dt = get_common_dtype(iterable);

        return dispatch_dt(dt, [&]<typename T>() {
            std::vector<T> vec(py::len(iterable));

            std::size_t i = 0;
            for (py::handle val : iterable) {
                vec[i] = py::cast<T>(val);
                ++i;
            }

            return std::visit([&](const auto& p) -> bool {
                using U = std::decay_t<decltype(p)>::ValueType;

                if constexpr (is_lossless_convertible<U, T>) {
                    using UnderlyingT = underlying_type_t<T>;
                    const Precision<UnderlyingT> casted(p.value);

                    return compare(casted, std::span<const T>(vec));
                }
                else {
                    throw py::type_error("Precision type does not match args type");
                }
            }, precision.storage);
        });
    });

    m.def("compare", [](const py::iterable& iterable) {
        const py::dtype dt = get_common_dtype(iterable);

        return dispatch_dt(dt, [&]<typename T>() {
            std::vector<T> vec(py::len(iterable));

            std::size_t i = 0;
            for (const py::handle val : iterable) {
                vec[i] = py::cast<T>(val);
                ++i;
            }

            return compare<T>(Precision<underlying_type_t<T>>(epsilon<T>()), std::span<const T>(vec));
        });
    });
}
