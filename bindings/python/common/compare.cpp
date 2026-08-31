#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <complex>
#include "../main.h"
#include "mathpp/implementation/common/compare.h"
#include "precision.h"

#include <ranges>

void common_compare_bindings(pybind11::module_& m) {
    m.def("compare", [](const Py_Precision& precision, const py::sequence& sequence) -> bool {
        const auto [dt, et, size] = get_sequence_info(sequence);

        return dispatch_dt(dt, [&]<typename T>() -> bool {
            return std::visit([&](const auto& p) -> bool {
                using U = std::decay_t<decltype(p)>::ValueType;

                if constexpr (lossless_convertible<U, underlying_type_t<T>>) {
                    const Precision<underlying_type_t<T>> casted_precision = Precision<underlying_type_t<T>>(p.value);

                    if (et == EType::scalar) {
                        auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
                            return py::cast<T>(sequence[i]);
                        });

                        return compare(casted_precision, wrapper);
                    }

                    throw py::type_error("Unknown et");
                }
                else {
                    throw py::type_error("Cannot convert");
                }
            }, precision);
        });
    });

    m.def("compare", [](const Py_Precision& precision, const py::array& array) -> bool {
        const auto [dt, et, size] = get_array_info(array);

        return dispatch_dt(dt, [&]<typename T>() -> bool {
            return std::visit([&](const auto& p) -> bool {
                using U = std::decay_t<decltype(p)>::ValueType;

                if constexpr (lossless_convertible<U, underlying_type_t<T>>) {
                    const Precision<underlying_type_t<T>> casted_precision = Precision<underlying_type_t<T>>(p.value);

                    if (et == EType::scalar) {
                        const py::detail::unchecked_reference<T, 1> unchecked = array.unchecked<T, 1>();

                        auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
                            return unchecked(i);
                        });

                        return compare(casted_precision, wrapper);
                    }

                    throw py::type_error("Unknown et");
                }
                else {
                    throw py::type_error("Cannot convert");
                }
            }, precision);
        });
    });

    m.def("compare", [](const py::sequence& sequence) -> bool {
        const auto [dt, et, size] = get_sequence_info(sequence);

        return dispatch_dt(dt, [&]<typename T>() -> bool {
            const Precision<underlying_type_t<T>> precision = Precision<underlying_type_t<T>>(epsilon<T>());

            if (et == EType::scalar) {
                auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
                    return py::cast<T>(sequence[i]);
                });

                return compare(precision, wrapper);
            }

            throw py::type_error("Unknown et");
        });
    });

    m.def("compare", [](const py::array& array) -> bool {
        const auto [dt, et, size] = get_array_info(array);

        return dispatch_dt(dt, [&]<typename T>() -> bool {
            const Precision<underlying_type_t<T>> precision = Precision<underlying_type_t<T>>(epsilon<T>());

            if (et == EType::scalar) {
                const py::detail::unchecked_reference<T, 1> iterator = array.unchecked<T, 1>();

                auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
                    return iterator[i];
                });

                return compare(precision, wrapper);
            }

            throw py::type_error("Unknown et");
        });
    });

    m.def("compare", [](const Py_Precision& precision, const py::args& args) -> bool {
        const auto [dt, et, size] = get_sequence_info(args);

        return dispatch_dt(dt, [&]<typename T>() -> bool {
            return std::visit([&](const auto& p) -> bool {
                using U = std::decay_t<decltype(p)>::ValueType;

                if constexpr (lossless_convertible<U, underlying_type_t<T>>) {
                    const Precision<underlying_type_t<T>> casted_precision = Precision<underlying_type_t<T>>(p.value);

                    py::print("et = ", et);

                    if (et == EType::scalar) {
                        auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
                            return py::cast<T>(args[i]);
                        });

                        return compare(casted_precision, wrapper);
                    }

                    throw py::type_error("Unknown et");
                }
                else {
                    throw py::type_error("Cannot convert");
                }
            }, precision);
        });
    });

    m.def("compare", [](const py::args& args) -> bool {
        const auto [dt, et, size] = get_sequence_info(args);

        return dispatch_dt(dt, [&]<typename T>() -> bool {
            const Precision<underlying_type_t<T>> precision = Precision<underlying_type_t<T>>(epsilon<T>());

            if (et == EType::scalar) {
                auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
                    return py::cast<T>(args[i]);
                });

                return compare(precision, wrapper);
            }

            throw py::type_error("Unknown et");
        });
    });
}
