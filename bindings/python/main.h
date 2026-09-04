#ifndef MATHPY_PYTHON_BINDINGS_MAIN_H
#define MATHPY_PYTHON_BINDINGS_MAIN_H

#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include <cstdint>
#include <cstddef>
#include <tuple>
#include <complex>

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

    throw py::type_error("Cannot dispatch_dt on invalid dt");
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

    throw py::type_error("Cannot dispatch_dt_no_complex on invalid dt");
}

enum class EType : uint32_t {
    none                   = 0,
    scalar                 = 1 << 0,
    csc_sparse_matrix_like = 1 << 1,
    csr_sparse_matrix_like = 1 << 2,
    coo_sparse_vector_like = 1 << 3,
    dok_sparse_vector_like = 1 << 4,
    dense_matrix_like      = 1 << 5,
    dense_vector_like      = 1 << 6,

    sparse_vector_like = coo_sparse_vector_like | dok_sparse_vector_like,
    sparse_matrix_like = csc_sparse_matrix_like | csr_sparse_matrix_like,
    matrix_like        = dense_matrix_like | sparse_matrix_like,
    vector_like        = dense_vector_like | sparse_vector_like,

    invalid            = 0xFFFFFFFF
};


EType& operator|=(EType& lhs, EType rhs);
std::string to_string(const EType& etype);

bool is_actually_sequence(py::handle sequence);

py::dtype get_py_int_dtype(py::int_ number);
py::dtype get_dtype(py::handle obj);
EType get_etype(py::handle obj);

std::tuple<py::dtype, EType, std::size_t> get_sequence_info(py::sequence sequence);
std::tuple<py::dtype, EType, std::size_t, std::size_t>  get_sequence_info_2d(py::sequence sequence);
std::tuple<py::dtype, EType, std::size_t> get_array_info(py::array array);
std::tuple<py::dtype, EType, std::size_t, std::size_t> get_array_info_2d(py::array array);

#endif //MATHPY_PYTHON_BINDINGS_MAIN_H
