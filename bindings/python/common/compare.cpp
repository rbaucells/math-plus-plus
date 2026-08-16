#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <complex>
#include "../main.h"
#include "mathpp/implementation/common/compare.h"
#include "precision.h"

void common_compare_bindings(pybind11::module_& m) {
    m.def("compare", [](const Py_Precision& precision, const py::iterable& iterable) {
        const py::dtype dt = get_common_dtype(iterable);

        return dispatch_dt(dt, [&]<typename T>() {
            using UnderlyingT = underlying_type_t<T>;

            std::vector<T> vec(py::len(iterable));

            std::size_t i = 0;
            for (const py::handle val : iterable) {
                vec[i] = py::cast<T>(val);
                ++i;
            }

            return std::visit([&](const auto& p) -> bool {
                using U = std::decay_t<decltype(p)>::ValueType;

                if constexpr (lossless_convertible<UnderlyingT, U>) {
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

            return compare(Precision<underlying_type_t<T>>(epsilon<T>()), std::span<const T>(vec));
        });
    });

    m.def("compare", [](const Py_Precision& precision, const py::args& args) {
        const py::dtype dt = get_common_dtype(args);

        return dispatch_dt(dt, [&]<typename T>() {
            std::vector<T> vec(args.size());

            for (std::size_t i = 0; i < args.size(); i++) {
                vec[i] = py::cast<T>(args[i]);
            }

            return std::visit([&](const auto& p) -> bool {
                using U = std::decay_t<decltype(p)>::ValueType;

                if constexpr (lossless_convertible<U, T>) {
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

            return compare(Precision<underlying_type_t<T>>(epsilon<T>()), std::span<const T>(vec));
        });
    });
}
