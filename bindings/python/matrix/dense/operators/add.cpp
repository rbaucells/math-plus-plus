#include "add.h"
#include "mathpp/implementation/matrix/dense/operators/add.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <complex>
#include <variant>
#include <memory>
#include <utility>

#include "mathpp/implementation/matrix/dense/traits.h"
#include "mathpp/implementation/matrix/dense/operators/add.h"

#include "../like.h"
#include "../matrix.h"
#include "../../../main.h"

namespace py = pybind11;

using Py_DenseMatrixAddExpr = std::variant<DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<uint8_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<uint16_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<uint32_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<uint64_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<int8_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<int16_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<int32_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<int64_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<float>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<double>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<std::complex<float>>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<std::complex<double>>>>;

void matrix_dense_operators_add_bindings(py::module_& m, py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py) {
    py::class_<Py_DenseMatrixAddExpr>(m, "DenseMatrixAddExpr")
        .def("evaluate", [](Py_DenseMatrixAddExpr& self) -> Py_DenseMatrix {
            return std::visit([]<typename T>(const DynamicDenseMatrixAddExpr<T>& expr) -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<typename T::ValueType>>, expr);
            }, self);
        })
        .def("__or__", [](Py_DenseMatrixAddExpr& self, const py::handle type) -> Py_DenseMatrix {
            if (!type.is(py::type::of<Py_DenseMatrix>())) {
                throw py::type_error("DenseMatrixAddExpr must evaluate to DenseMatrix");
            }

            return std::visit([]<typename T>(const DynamicDenseMatrixAddExpr<T>& expr) -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<typename T::ValueType>>, expr);
            }, self);
        })
        .def("__add__", [](Py_DenseMatrixAddExpr& self, const py::object other) -> Py_DenseMatrixAddExpr& {
            if (!py::isinstance<DenseMatrixLikeBase>(other)) {
                throw py::type_error("DenseMatrixAddExpr can only add dense matrix likes");
            }

            std::visit([&]<typename T>(DynamicDenseMatrixAddExpr<T>& expr) -> void {
                const py::dtype otherDt = get_dtype(other);
                dispatch_dt(otherDt, [&]<typename U>() -> void {
                    if constexpr (lossless_convertible<U, typename T::ValueType>) {
                        expr.add(DenseMatrixLikePyWrapper<typename T::ValueType>(other));
                    }
                    else {
                        throw py::type_error("Cannot add incompatible types to DenseMatrixAddExpr");
                    }
                });
            }, self);

            return self;
        });

    dense_matrix_like_base_py.def("__add__", [](const py::object self, const py::object other) -> Py_DenseMatrixAddExpr {
        if (!py::isinstance<DenseMatrixLikeBase>(other)) {
            throw py::type_error();
        }

        const py::dtype selfDt = get_dtype(self);
        const py::dtype otherDt = get_dtype(other);

        return dispatch_dt(selfDt, [&]<typename T>() -> Py_DenseMatrixAddExpr {
            return dispatch_dt(otherDt, [&]<typename U>() -> Py_DenseMatrixAddExpr {
                if constexpr (has_common_type<T, U>) {
                    return Py_DenseMatrixAddExpr(std::in_place_type<DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<std::common_type_t<T, U>>>>, DenseMatrixLikePyWrapper<std::common_type_t<T, U>>(self), DenseMatrixLikePyWrapper<std::common_type_t<T, U>>(other));
                }
                else {
                    throw py::type_error();
                }
            });
        });
    });
}
