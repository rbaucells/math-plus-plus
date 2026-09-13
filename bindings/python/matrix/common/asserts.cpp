#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "like.h"
#include <ranges>

#include "mathpp/implementation/matrix/common/asserts.h"

#include "../../main.h"

namespace py = pybind11;

void matrix_common_asserts(py::module_& m) {
    m.def("assert_same_dimensions", [](const py::sequence sequence) -> void {
        const auto [dt, et, size] = get_sequence_info(sequence);

        if ((static_cast<uint32_t>(et) & static_cast<uint32_t>(EType::matrix_like)) == 0) {
            throw py::type_error("Cannot assert same dimensions on sequence that isnt all matrix like");
        }

        dispatch_dt(dt, [&]<typename T>() -> void {
            auto wrapper = std::views::iota(0ul, size) | std::views::transform([&](const std::size_t i) -> MatrixLikePyWrapper<T> {
                return MatrixLikePyWrapper<T>(sequence[i]);
            });

            assert_same_dimensions(wrapper);
        });
    });

    m.def("assert_same_dimensions", [](const py::array array) -> void {
        const auto [dt, et, size] = get_array_info(array);

        if ((static_cast<uint32_t>(et) & static_cast<uint32_t>(EType::matrix_like)) == 0) {
            throw py::type_error("Cannot assert same dimensions on sequence that isnt all matrix like");
        }

        dispatch_dt(dt, [&]<typename T>() -> void {
            auto wrapper = std::views::iota(0ul, size) | std::views::transform([&](const std::size_t i) -> MatrixLikePyWrapper<T> {
                return MatrixLikePyWrapper<T>(array[py::cast(i)]);
            });

            assert_same_dimensions(wrapper);
        });
    });

    m.def("assert_same_dimensions", [](const py::args args) -> void {
        const auto [dt, et, size] = get_sequence_info(args);

        if ((static_cast<uint32_t>(et) & static_cast<uint32_t>(EType::matrix_like)) == 0) {
            throw py::type_error("Cannot assert same dimensions on sequence that isnt all matrix like");
        }

        dispatch_dt(dt, [&]<typename T>() -> void {
            auto wrapper = std::views::iota(0ul, size) | std::views::transform([&](const std::size_t i) -> MatrixLikePyWrapper<T> {
                return MatrixLikePyWrapper<T>(args[i]);
            });

            assert_same_dimensions(wrapper);
        });
    });

    m.def("assert_square", [](const py::object mat) {
        if (!py::isinstance<MatrixLikeBase>(mat)) {
            throw py::type_error();
        }

        const py::dtype dt = get_dtype(mat);

        dispatch_dt(dt, [&]<typename T>() {
            assert_square(MatrixLikePyWrapper<T>(mat));
        });
    });

    m.def("assert_wide", [](const py::object mat) {
        if (!py::isinstance<MatrixLikeBase>(mat)) {
            throw py::type_error();
        }

        const py::dtype dt = get_dtype(mat);

        dispatch_dt(dt, [&]<typename T>() {
            assert_wide(MatrixLikePyWrapper<T>(mat));
        });
    });

    m.def("assert_tall", [](const py::object mat) {
        if (!py::isinstance<MatrixLikeBase>(mat)) {
            throw py::type_error();
        }

        const py::dtype dt = get_dtype(mat);

        dispatch_dt(dt, [&]<typename T>() {
            assert_tall(MatrixLikePyWrapper<T>(mat));
        });
    });

    m.def("assert_can_multiply", [](const py::object mat, const py::object otherMat) {
        if (!py::isinstance<MatrixLikeBase>(mat) || !py::isinstance<MatrixLikeBase>(otherMat)) {
            throw py::type_error();
        }

        const py::dtype dt = get_dtype(mat);

        dispatch_dt(dt, [&]<typename T>() {
            assert_can_multiply(MatrixLikePyWrapper<T>(mat), MatrixLikePyWrapper<T>(otherMat));
        });
    });
}
