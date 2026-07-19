#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/numpy.h>
#include "main.h"

#include <iostream>

#include "mathpp/implementation/vector/dense/operators/compare.h"

namespace py = pybind11;

PYBIND11_MODULE(mathpy, m) {
    m.def("get_py_int_dtype", &get_py_int_dtype, py::arg("obj"), "Given a py builtin int type calculates the numpy dtype that can fit the int");
    m.def("get_dtype", &get_dtype, py::arg("obj"), "Given a numpy number or builtin py type gives a numpy dtype");
    m.def("get_common_dtype", &get_common_dtype, py::arg("obj"), "Given a container of py builtin number types or numpy types computes a common dtype");
    compare_bindings(m);
}

py::dtype get_py_int_dtype(const py::int_& pyInt) {
    const bool negative = pyInt < py::int_(0);

    if (negative) { // signed
        if (pyInt > py::int_(std::numeric_limits<int8_t>::min())) {
            return py::dtype::of<int8_t>();
        }

        if (pyInt > py::int_(std::numeric_limits<int16_t>::min())) {
            return py::dtype::of<int16_t>();
        }

        if (pyInt > py::int_(std::numeric_limits<int32_t>::min())) {
            return py::dtype::of<int32_t>();
        }

        if (pyInt > py::int_(std::numeric_limits<int64_t>::min())) {
            return py::dtype::of<int64_t>();
        }
    }
    else { // unsigned
        if (pyInt < py::int_(std::numeric_limits<uint8_t>::max())) {
            return py::dtype::of<uint8_t>();
        }

        if (pyInt < py::int_(std::numeric_limits<uint16_t>::max())) {
            return py::dtype::of<uint16_t>();
        }

        if (pyInt < py::int_(std::numeric_limits<uint32_t>::max())) {
            return py::dtype::of<uint32_t>();
        }

        if (pyInt < py::int_(std::numeric_limits<uint64_t>::max())) {
            return py::dtype::of<uint64_t>();
        }
    }

    return py::dtype::of<int64_t>();
}

py::dtype get_dtype(const py::handle& obj) {
    // numpy scalar
    if (py::hasattr(obj, "dtype")) {
        return py::cast<py::dtype>(obj.attr("dtype"));;
    }

    // py int
    if (py::isinstance<py::int_>(obj)) {
        return get_py_int_dtype(py::reinterpret_borrow<py::int_>(obj));
    }

    // py float
    if (py::isinstance<py::float_>(obj)) {
        return py::dtype::of<double>();
    }

    // py complex
    if (py::isinstance(obj, py::module_::import("builtins").attr("complex"))) {
        return py::dtype::of<std::complex<double>>();
    }

    throw py::type_error("Unsupported object type");
}

py::dtype get_common_dtype(const py::iterable& iterable) {
    if (py::isinstance<py::array>(iterable)) {
        const auto arr = py::cast<py::array>(iterable);
        const auto dt = arr.dtype();

        if (!dt.is(py::dtype::of<py::object>())) {
            return dt;
        }
    }

    py::tuple dtypes(py::len(iterable));

    std::size_t i = 0;
    for (py::handle val: iterable) {
        dtypes[i] = get_dtype(val);
        ++i;
    }

    const py::module_ np = py::module_::import("numpy");
    return py::cast<py::dtype>(np.attr("result_type")(*dtypes));
}
