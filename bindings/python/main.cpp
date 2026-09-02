#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cstdint>
#include <cstddef>
#include <tuple>

#include "main.h"
#include "common/main.h"
#include "matrix/main.h"
#include "vector/main.h"

#include "matrix/common/like.h"
#include "matrix/dense/like.h"

namespace py = pybind11;

PYBIND11_MODULE(mathpy, m) {
    // for debug only stuff
    py::enum_<EType>(m, "EType", py::arithmetic())
        .value("none", EType::none)
        .value("scalar", EType::scalar)
        .value("csc_sparse_matrix_like", EType::csc_sparse_matrix_like)
        .value("csr_sparse_matrix_like", EType::csr_sparse_matrix_like)
        .value("coo_sparse_vector_like", EType::coo_sparse_vector_like)
        .value("dok_sparse_vector_like", EType::dok_sparse_vector_like)
        .value("dense_matrix_like", EType::dense_matrix_like)
        .value("dense_vector_like", EType::dense_vector_like)
        .value("sparse_vector_like", EType::sparse_vector_like)
        .value("sparse_matrix_like", EType::sparse_matrix_like)
        .value("matrix_like", EType::matrix_like)
        .value("vector_like", EType::vector_like)
        .value("invalid", EType::invalid);

    m.def("get_py_int_dtype", &get_py_int_dtype, py::arg("pyInt"), "Given a py builtin int type calculates the numpy dtype that can fit the int");
    m.def("get_dtype", &get_dtype, py::arg("obj"));
    m.def("get_etype", &get_dtype, py::arg("obj"));
    m.def("get_sequence_info", &get_sequence_info, py::arg("sequence"));
    m.def("get_sequence_info_2d", &get_sequence_info_2d, py::arg("sequence"));
    m.def("get_array_info", &get_array_info, py::arg("array"));
    m.def("get_array_info_2d", &get_array_info_2d, py::arg("array"));

    common_bindings(m);
    matrix_bindings(m);
    vector_bindings(m);
}

EType& operator|=(EType& lhs, const EType rhs) {
    if (lhs == EType::invalid || rhs == EType::invalid) {
        lhs = EType::invalid;
        return lhs;
    }

    const std::uint32_t combined = static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs);

    const bool has_matrix = (combined & static_cast<std::uint32_t>(EType::matrix_like)) != 0;
    const bool has_vector = (combined & static_cast<std::uint32_t>(EType::vector_like)) != 0;
    const bool has_scalar = (combined & static_cast<std::uint32_t>(EType::scalar)) != 0;

    if ((has_matrix + has_vector + has_scalar) > 1) {
        lhs = EType::invalid;
        return lhs;
    }

    lhs = static_cast<EType>(combined);
    return lhs;
}

bool is_actually_sequence(const py::handle sequence) {
    return py::isinstance<py::sequence>(sequence) && !py::isinstance<MatrixLikeBase>(sequence);
}

py::dtype get_py_int_dtype(const py::int_ pyInt) {
    const bool negative = pyInt < py::int_(0);

    if (negative) { // signed
        if (pyInt >= py::int_(std::numeric_limits<std::int8_t>::min())) {
            return py::dtype::of<std::int8_t>();
        }

        if (pyInt >= py::int_(std::numeric_limits<std::int16_t>::min())) {
            return py::dtype::of<std::int16_t>();
        }

        if (pyInt >= py::int_(std::numeric_limits<std::int32_t>::min())) {
            return py::dtype::of<std::int32_t>();
        }

        if (pyInt >= py::int_(std::numeric_limits<std::int64_t>::min())) {
            return py::dtype::of<std::int64_t>();
        }
    }
    else { // unsigned
        if (pyInt <= py::int_(std::numeric_limits<std::uint8_t>::max())) {
            return py::dtype::of<std::uint8_t>();
        }

        if (pyInt <= py::int_(std::numeric_limits<std::uint16_t>::max())) {
            return py::dtype::of<std::uint16_t>();
        }

        if (pyInt <= py::int_(std::numeric_limits<std::uint32_t>::max())) {
            return py::dtype::of<std::uint32_t>();
        }

        if (pyInt <= py::int_(std::numeric_limits<std::uint64_t>::max())) {
            return py::dtype::of<std::uint64_t>();
        }
    }

    return py::dtype::of<std::int64_t>();
}

py::dtype get_dtype(const py::handle obj) {
    // numpy scalar or could be one of my types
    if (py::hasattr(obj, "dtype")) {
        const auto attr = obj.attr("dtype");
        return py::cast<py::dtype>(py::isinstance<py::function>(attr) ? attr() : attr);
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

EType get_etype(const py::handle obj) {
    if (py::isinstance<DenseMatrixLikeBase>(obj)) {
        return EType::dense_matrix_like;
    }

    // if (py::isinstance<DenseVectorLikeBase>(obj)) {
    //     return EType::dense_vector_like;
    // }

    // if (py::isinstance<CSCSparseMatrixLikeBase>(obj)) {
    //     return EType::csc_sparse_matrix_like;
    // }

    // if (py::isinstance<CSRSparseMatrixLikeBase>(obj)) {
    //     return EType::csr_sparse_matrix_like;
    // }

    // if (py::isinstance<SparseMatrixLikeBase>(obj)) {
    //     return EType::sparse_matrix_like;
    // }

    if (py::isinstance<MatrixLikeBase>(obj)) {
        return EType::matrix_like;
    }

    // if (py::isinstance<CooSparseVectorLikeBase>(obj)) {
    //     return EType::coo_sparse_vector_like;
    // }

    // if (py::isinstance<DokSparseVectorLikeBase>(obj)) {
    //     return EType::dok_sparse_vector_like;
    // }

    // if (py::isinstance<SparseVectorLikeBase>(obj)) {
    //     return EType::sparse_vector_like;
    // }

    // if (py::isinstance<VectorLikeBase>(obj)) {
    //     return EType::vector_like;
    // }

    if (py::isinstance(obj, py::module_::import("numpy").attr("number")) || py::isinstance<py::int_>(obj) || py::isinstance<py::float_>(obj) || py::isinstance(obj, py::module_::import("builtins").attr("complex"))) {

        py::print("returning scalar yo, obj = ", obj, " and type yo is ", py::type::of(obj));
        return EType::scalar;
    }

    py::print("returning none yo, obj = ", obj, " and type yo is ", py::type::of(obj));

    return EType::none;
}

std::tuple<py::dtype, EType, std::size_t> get_sequence_info(const py::sequence sequence) {
    EType et = EType::none;
    const std::size_t size = sequence.size();

    py::tuple dtypes(size);

    std::size_t i = 0;
    for (auto element : sequence) {
        if (is_actually_sequence(element)) {
            throw py::type_error("Cannot get 1d sequence info on non-1d sequence");
        }

        dtypes[i] = get_dtype(element);
        et |= get_etype(element);

        ++i;
    }

    const py::module_ np = py::module_::import("numpy");
    const py::dtype dt = py::cast<py::dtype>(np.attr("result_type")(*dtypes));

    return {dt, et, size};
}

std::tuple<py::dtype, EType, std::size_t, std::size_t>  get_sequence_info_2d(const py::sequence sequence) {
    EType et = EType::none;
    const std::size_t size = sequence.size();
    std::optional<std::size_t> nestedSize;

    py::tuple dtypes(size);

    std::size_t i = 0;
    for (auto inner : sequence) {
        if (!is_actually_sequence(inner)) {
            throw py::type_error("Cannot get 2d sequence info on non-2d sequence");
        }

        py::sequence asSequence = inner;

        const auto [innerDt, innerEt, innerSize] = get_sequence_info(inner);

        if (!nestedSize) {
            nestedSize = innerSize;
        }
        else {
            if (nestedSize != innerSize) {
                throw py::type_error();
            }
        }

        dtypes[i] = innerDt;
        et |= innerEt;

        ++i;
    }

    const py::module_ np = py::module_::import("numpy");
    const py::dtype dt = py::cast<py::dtype>(np.attr("result_type")(*dtypes));

    return {dt, et, size, *nestedSize};
}

std::tuple<py::dtype, EType, std::size_t> get_array_info(const py::array array) {
    if (array.ndim() != 1) {
        throw py::type_error("Cannot get 1d array info on non-1d array");
    }

    EType et = EType::none;
    const std::size_t size = array.size();

    py::dtype dt;

    if (!array.dtype().is(py::dtype::of<py::object>())) {
        py::print("rout 1");

        dt = array.dtype();

        for (auto element : array) {
            et |= get_etype(element);
        }
    }
    else {
        py::print("rout 2");
        py::tuple dtypes(size);

        std::size_t i = 0;
        for (auto element : array) {
            dtypes[i] = get_dtype(element);
            et |= get_etype(element);

            ++i;
        }

        const py::module_ np = py::module_::import("numpy");
        dt = py::cast<py::dtype>(np.attr("result_type")(*dtypes));
    }

    return {dt, et, size};
}

std::tuple<py::dtype, EType, std::size_t, std::size_t> get_array_info_2d(const py::array array) {
    py::print("up up here");
    if (array.ndim() != 2) {
        throw py::type_error("Cannot get 2d array info on non-2d array");
    }

    py::print("up here");

    EType et = EType::none;
    const std::size_t size = array.shape(0);
    const std::size_t nestedSize = array.shape(1);

    py::print("size = ", size);
    py::print("nestedSize = ", nestedSize);

    py::dtype dt;

    if (!array.dtype().is(py::dtype::of<py::object>())) {
        py::print("getting through dt and stuff");
        dt = array.dtype();

        et |= EType::scalar;
    }
    else {
        py::tuple dtypes(size);

        std::size_t i = 0;
        for (auto inner : array) {
            py::array asArray = py::cast<py::array>(inner);

            py::print("getting through recurse into get_array_info", nestedSize);

            const auto [innerDt, innerEt, _] = get_array_info(asArray);

            dtypes[i] = innerDt;
            et |= innerEt;

            ++i;
        }

        const py::module_ np = py::module_::import("numpy");
        dt = py::cast<py::dtype>(np.attr("result_type")(*dtypes));
    }

    py::print("we out");
    return {dt, et, size, nestedSize};
}
