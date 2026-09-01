#include "../like.h"
#include <ranges>

#include "mathpp/implementation/matrix/dense/operators/compare.h"
#include "compare.h"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "../../../main.h"

namespace py = pybind11;

void matrix_dense_operators_compare_bindings(py::module_& m, py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py) {
    dense_matrix_like_base_py.def("__eq__", [](const py::object& self, const py::object& other) -> bool {
        if (!py::isinstance<DenseMatrixLikeBase>(other)) {
            throw py::type_error();
        }

        const py::dtype selfDt = self.attr("dtype")();
        const py::dtype otherDt = other.attr("dtype")();

        return dispatch_dt(selfDt, [&]<typename T>() -> bool {
            return dispatch_dt(otherDt, [&]<typename U>() -> bool {
                if constexpr (has_common_type<T, U>) {
                    return compare(DenseMatrixLikePyWrapper<T>(self), DenseMatrixLikePyWrapper<T>(other));
                }
                else {
                    throw py::type_error();
                }
            });
        });
    });
}

