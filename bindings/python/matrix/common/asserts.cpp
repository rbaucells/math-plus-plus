#include <pybind11/numpy.h>
#include <pybind11/typing.h>
#include <pybind11/pybind11.h>

#include "like.h"
#include <ranges>
#include <format>
#include <cstddef>
#include <cstdint>
#include <string>

#include "mathpp/implementation/matrix/common/asserts.h"

#include "../../main.h"

namespace py = pybind11;

void matrix_common_asserts_bindings(py::module_& m) {
    m.def("assert_same_dimensions", [](const py::sequence sequence) -> void {
        const auto [dt, et, size] = get_sequence_info(sequence);

        if ((static_cast<uint32_t>(et) & static_cast<uint32_t>(EType::matrix_like)) == 0) {
            throw py::type_error(std::format("Cannot assert same dimensions. Sequence has '{}' elements, expected sequence of MatrixLike", to_string(et)));
        }

        dispatch_dt(dt, [&]<typename T>() -> void {
            auto wrapper = std::views::iota(0ul, size) | std::views::transform([&](const std::size_t i) -> MatrixLikePyWrapper<T> {
                return MatrixLikePyWrapper<T>(sequence[i]);
            });

            assert_same_dimensions(wrapper);
        });
    }, py::arg("sequence"), "Asserts all MatrixLike elements of 'sequence' have same dimensions. Throws type_error if not");

    m.def("assert_same_dimensions", [](const py::array array) -> void {
        const auto [dt, et, size] = get_array_info(array);

        if ((static_cast<uint32_t>(et) & static_cast<uint32_t>(EType::matrix_like)) == 0) {
            throw py::type_error(std::format("Cannot assert same dimensions. Array has '{}' elements, expected array of MatrixLike", to_string(et)));
        }

        dispatch_dt(dt, [&]<typename T>() -> void {
            auto wrapper = std::views::iota(0ul, size) | std::views::transform([&](const std::size_t i) -> MatrixLikePyWrapper<T> {
                return MatrixLikePyWrapper<T>(array[py::cast(i)]);
            });

            assert_same_dimensions(wrapper);
        });
    }, py::arg("array"), "Asserts all MatrixLike elements of 'array' have same dimensions. Throws type_error if not");

    m.def("assert_same_dimensions", [](const py::args args) -> void {
        const auto [dt, et, size] = get_sequence_info(args);

        if ((static_cast<uint32_t>(et) & static_cast<uint32_t>(EType::matrix_like)) == 0) {
            throw py::type_error(std::format("Cannot assert same dimensions. args has '{}' elements, expected args of MatrixLike", to_string(et)));
        }

        dispatch_dt(dt, [&]<typename T>() -> void {
            auto wrapper = std::views::iota(0ul, size) | std::views::transform([&](const std::size_t i) -> MatrixLikePyWrapper<T> {
                return MatrixLikePyWrapper<T>(args[i]);
            });

            assert_same_dimensions(wrapper);
        });
    }, "Asserts all MatrixLike elements of 'args' have same dimensions. Throws type_error if not");

    m.def("assert_square", [](const PyMatrixLike mat) {
        if (!py::isinstance<MatrixLikeBase>(mat)) {
            throw py::type_error(std::format("Cannot assert square. '{}' is not a MatrixLike", py::cast<std::string>(py::str(mat))));
        }

        const py::dtype dt = get_dtype(mat);

        dispatch_dt(dt, [&]<typename T>() {
            assert_square(MatrixLikePyWrapper<T>(mat));
        });
    }, py::arg("matrix"), "Asserts 'matrix' is square. Throws type_error if not");

    m.def("assert_wide", [](const PyMatrixLike mat) {
        if (!py::isinstance<MatrixLikeBase>(mat)) {
            throw py::type_error(std::format("Cannot assert wide. '{}' is not a MatrixLike", py::cast<std::string>(py::str(mat))));
        }

        const py::dtype dt = get_dtype(mat);

        dispatch_dt(dt, [&]<typename T>() {
            assert_wide(MatrixLikePyWrapper<T>(mat));
        });
    }, py::arg("matrix"), "Asserts 'matrix' is wide. Throws type_error if not");

    m.def("assert_tall", [](const PyMatrixLike mat) {
        if (!py::isinstance<MatrixLikeBase>(mat)) {
            throw py::type_error(std::format("Cannot assert tall. '{}' is not a MatrixLike", py::cast<std::string>(py::str(mat))));
        }

        const py::dtype dt = get_dtype(mat);

        dispatch_dt(dt, [&]<typename T>() {
            assert_tall(MatrixLikePyWrapper<T>(mat));
        });
    }, py::arg("matrix"), "Asserts 'matrix' is tall. Throws type_error if not");

    m.def("assert_can_multiply", [](const PyMatrixLike mat, const PyMatrixLike otherMat) {
        if (!py::isinstance<MatrixLikeBase>(mat)) {
            throw py::type_error(std::format("Cannot assert can multiple. '{}' is not a MatrixLike", py::cast<std::string>(py::str(mat))));
        }

        if (!py::isinstance<MatrixLikeBase>(otherMat)) {
            throw py::type_error(std::format("Cannot assert can multiple. '{}' is not a MatrixLike", py::cast<std::string>(py::str(otherMat))));
        }

        const py::dtype dt = get_dtype(mat);

        dispatch_dt(dt, [&]<typename T>() {
            assert_can_multiply(MatrixLikePyWrapper<T>(mat), MatrixLikePyWrapper<T>(otherMat));
        });
    }, py::arg("matrix_a"), py::arg("matrix_b"), "Asserts 'matrix_a' and 'matrix_b' can multiply based on their dimensions. Throws type_error if not");
}
