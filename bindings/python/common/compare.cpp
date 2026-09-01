#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <complex>
#include "../main.h"
#include "mathpp/implementation/common/compare.h"
#include "precision.h"

#include <ranges>

#include "../matrix/dense/operators/compare.h"

template<typename T>
static bool common_compare(const std::size_t size, const Precision<underlying_type_t<T>> precision, const py::sequence& sequence) {
    auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
        return py::cast<T>(sequence[i]);
    });

    return compare(precision, wrapper);
}

template<typename T>
static bool common_compare(const std::size_t size, const Precision<underlying_type_t<T>> precision, const py::array& array) {
    const py::detail::unchecked_reference<T, 1> unchecked = array.unchecked<T, 1>();

    auto wrapper = std::views::iota(0u, size) | std::views::transform([&](const std::size_t i) -> T {
        return unchecked(i);
    });

    return compare(precision, wrapper);
}

void common_compare_bindings(pybind11::module_& m) {
    m.def("compare", [](const Py_Precision& precision, const py::sequence& sequence) -> bool {
        const auto [dt, et, size] = get_sequence_info(sequence);

        return dispatch_dt(dt, [&]<typename T>() -> bool {
            return std::visit([&](const auto& p) -> bool {
                using U = std::decay_t<decltype(p)>::ValueType;

                if constexpr (lossless_convertible<U, underlying_type_t<T>>) {
                    const Precision<underlying_type_t<T>> casted_precision = Precision<underlying_type_t<T>>(p.value);

                    if (et == EType::scalar) {
                        return common_compare<T>(size, casted_precision, sequence);
                    }
                    else if (et == EType::dense_matrix_like) {
                        return matrix_dense_operators_compare<T>(size, casted_precision, sequence);
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
                        return common_compare<T>(size, casted_precision, array);
                    }
                    else if (et == EType::dense_matrix_like) {
                        return matrix_dense_operators_compare<T>(size, casted_precision, array);
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
                return common_compare<T>(size, precision, sequence);
            }
            else if (et == EType::dense_matrix_like) {
                return matrix_dense_operators_compare<T>(size, precision, sequence);
            }

            throw py::type_error("Unknown et");
        });
    });

    m.def("compare", [](const py::array& array) -> bool {
        const auto [dt, et, size] = get_array_info(array);

        return dispatch_dt(dt, [&]<typename T>() -> bool {
            const Precision<underlying_type_t<T>> precision = Precision<underlying_type_t<T>>(epsilon<T>());

            if (et == EType::scalar) {
                return common_compare<T>(size, precision, array);
            }
            else if (et == EType::dense_matrix_like) {
                return matrix_dense_operators_compare<T>(size, precision, array);
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
                        return common_compare<T>(size, casted_precision, py::sequence(args));
                    }
                    else if (et == EType::dense_matrix_like) {
                        return matrix_dense_operators_compare<T>(size, casted_precision, py::sequence(args));
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
                return common_compare<T>(size, precision, py::sequence(args));
            }
            else if (et == EType::dense_matrix_like) {
                return matrix_dense_operators_compare<T>(size, precision, py::sequence(args));
            }

            throw py::type_error("Unknown et");
        });
    });
}
