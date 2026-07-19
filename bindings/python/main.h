#ifndef MATHPP_PYTHON_BINDINGS_MAIN_H
#define MATHPP_PYTHON_BINDINGS_MAIN_H

#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

template<typename F>
decltype(auto) dispatch_dt(const py::dtype& dt, F func) {
    if (dt.is(py::dtype::of<std::int8_t>())) {
        return func.template operator()<std::int8_t>();
    }

    if (dt.is(py::dtype::of<std::uint8_t>())) {
        return func.template operator()<std::uint8_t>();
    }

    if (dt.is(py::dtype::of<std::int16_t>())) {
        return func.template operator()<std::int16_t>();
    }

    if (dt.is(py::dtype::of<std::uint16_t>())) {
        return func.template operator()<std::uint16_t>();
    }

    if (dt.is(py::dtype::of<std::int32_t>())) {
        return func.template operator()<std::int32_t>();
    }

    if (dt.is(py::dtype::of<std::uint32_t>())) {
        return func.template operator()<std::uint32_t>();
    }

    if (dt.is(py::dtype::of<std::int64_t>())) {
        return func.template operator()<std::int64_t>();
    }

    if (dt.is(py::dtype::of<std::uint64_t>())) {
        return func.template operator()<std::uint64_t>();
    }

    if (dt.is(py::dtype::of<float>())) {
        return func.template operator()<float>();
    }

    if (dt.is(py::dtype::of<double>())) {
        return func.template operator()<double>();
    }

    if (dt.is(py::dtype::of<std::complex<float>>())) {
        return func.template operator()<std::complex<float>>();
    }

    if (dt.is(py::dtype::of<std::complex<double>>())) {
        return func.template operator()<std::complex<double>>();
    }

    throw py::type_error("Invalid type");
}

template<typename F>
decltype(auto) dispatch_dt_no_complex(const py::dtype& dt, F func) {
    if (dt.is(py::dtype::of<std::int8_t>())) {
        return func.template operator()<std::int8_t>();
    }

    if (dt.is(py::dtype::of<std::uint8_t>())) {
        return func.template operator()<std::uint8_t>();
    }

    if (dt.is(py::dtype::of<std::int16_t>())) {
        return func.template operator()<std::int16_t>();
    }

    if (dt.is(py::dtype::of<std::uint16_t>())) {
        return func.template operator()<std::uint16_t>();
    }

    if (dt.is(py::dtype::of<std::int32_t>())) {
        return func.template operator()<std::int32_t>();
    }

    if (dt.is(py::dtype::of<std::uint32_t>())) {
        return func.template operator()<std::uint32_t>();
    }

    if (dt.is(py::dtype::of<std::int64_t>())) {
        return func.template operator()<std::int64_t>();
    }

    if (dt.is(py::dtype::of<std::uint64_t>())) {
        return func.template operator()<std::uint64_t>();
    }

    if (dt.is(py::dtype::of<float>())) {
        return func.template operator()<float>();
    }

    if (dt.is(py::dtype::of<double>())) {
        return func.template operator()<double>();
    }

    throw py::type_error("Invalid type");
}

template <typename From, typename To>
concept is_lossless_convertible = requires(From f) {
    { To{f} };
};

template<typename Variant>
struct PyWrapper {
    Variant storage;

    PyWrapper() = default;

    template<typename T>
    PyWrapper(T v) : storage(std::move(v)) {}
};

py::dtype get_py_int_dtype(const py::int_& pyInt);
py::dtype get_dtype(const py::handle& obj);
py::dtype get_common_dtype(const py::iterable& iterable);

void compare_bindings(pybind11::module_& m);

#endif //MATHPP_PYTHON_BINDINGS_MAIN_H
