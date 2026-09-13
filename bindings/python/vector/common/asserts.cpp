#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "like.h"
#include <ranges>

#include "mathpp/implementation/vector/common/asserts.h"

#include "../../main.h"

namespace py = pybind11;

void vector_common_asserts(py::module_& m) {
    m.def("assert_same_size", [](const py::sequence sequence) -> void {
        const auto [dt, et, size] = get_sequence_info(sequence);

        if ((static_cast<uint32_t>(et) & static_cast<uint32_t>(EType::vector_like)) == 0) {
            throw py::type_error("Cannot assert same dimensions on sequence that isnt all vector like");
        }

        dispatch_dt(dt, [&]<typename T>() -> void {
            auto wrapper = std::views::iota(0ul, size) | std::views::transform([&](const std::size_t i) -> VectorLikePyWrapper<T> {
                return VectorLikePyWrapper<T>(sequence[i]);
            });

            assert_same_size(wrapper);
        });
    });

    m.def("assert_same_size", [](const py::array array) -> void {
        const auto [dt, et, size] = get_array_info(array);

        if ((static_cast<uint32_t>(et) & static_cast<uint32_t>(EType::vector_like)) == 0) {
            throw py::type_error("Cannot assert same dimensions on sequence that isnt all vector like");
        }

        dispatch_dt(dt, [&]<typename T>() -> void {
            auto wrapper = std::views::iota(0ul, size) | std::views::transform([&](const std::size_t i) -> VectorLikePyWrapper<T> {
                return VectorLikePyWrapper<T>(array[py::cast(i)]);
            });

            assert_same_size(wrapper);
        });
    });

    m.def("assert_same_size", [](const py::args args) -> void {
        const auto [dt, et, size] = get_sequence_info(args);

        if ((static_cast<uint32_t>(et) & static_cast<uint32_t>(EType::vector_like)) == 0) {
            throw py::type_error("Cannot assert same dimensions on sequence that isnt all vector like");
        }

        dispatch_dt(dt, [&]<typename T>() -> void {
            auto wrapper = std::views::iota(0ul, size) | std::views::transform([&](const std::size_t i) -> VectorLikePyWrapper<T> {
                return VectorLikePyWrapper<T>(args[i]);
            });

            assert_same_size(wrapper);
        });
    });
}
