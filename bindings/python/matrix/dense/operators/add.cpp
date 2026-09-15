#include "add.h"
#include "mathpp/implementation/matrix/dense/operators/add.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <complex>
#include <variant>
#include <format>
#include <memory>
#include <utility>
#include <type_traits>
#include <string>

#include "mathpp/implementation/matrix/dense/traits.h"
#include "mathpp/implementation/matrix/dense/operators/add.h"

#include "../like.h"
#include "../matrix.h"
#include "../../../main.h"

namespace py = pybind11;

// DynamicDenseMatrixAddExpr of any type of DenseMatrixLikePyWrapper
using Py_DenseMatrixAddExpr = std::variant<DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<uint8_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<uint16_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<uint32_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<uint64_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<int8_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<int16_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<int32_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<int64_t>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<float>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<double>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<std::complex<float>>>, DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<std::complex<double>>>>;

void matrix_dense_operators_add_bindings(py::module_& m, py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py) {
    py::class_<Py_DenseMatrixAddExpr>(m, "DenseMatrixAddExpr", "Lazily evaluated expression for sum of DenseMatrixLike objects")
        .def("evaluate", [](Py_DenseMatrixAddExpr& self) -> Py_DenseMatrix {
            return std::visit([]<typename T>(const DynamicDenseMatrixAddExpr<T>& expr) -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<typename T::ValueType>>, expr);
            }, self);
        }, "Constructs a DenseMatrix whose elements are made up of the sum of matrices in expression")
        .def("__or__", [](Py_DenseMatrixAddExpr& self, const py::type type) -> Py_DenseMatrix {
            if (!type.is(py::type::of<Py_DenseMatrix>())) {
                throw py::type_error(std::format("DenseMatrixAddExpr cannot evaluate as a '{}', must evaluate to DenseMatrix", py::cast<std::string>(py::str(type))));
            }

            return std::visit([]<typename T>(const DynamicDenseMatrixAddExpr<T>& expr) -> Py_DenseMatrix {
                return Py_DenseMatrix(std::in_place_type<DenseMatrix<typename T::ValueType>>, expr);
            }, self);
        }, py::arg("type"), "Evaluates the expression, constructs a DenseMatrix whose elements are made up of the sum of matrices in expression. 'type' must be 'DenseMatrix'")
        .def("__add__", [](Py_DenseMatrixAddExpr& self, const PyDenseMatrixLike other) -> Py_DenseMatrixAddExpr& {
            if (!py::isinstance<DenseMatrixLikeBase>(other)) {
                throw py::type_error(std::format("Cannot add to DenseMatrixAddExpr. Got '{}' expected DenseMatrixLike", py::cast<std::string>(py::str(other))));
            }

            std::visit([&]<typename T>(DynamicDenseMatrixAddExpr<T>& expr) -> void {
                const py::dtype otherDt = get_dtype(other);

                dispatch_dt(otherDt, [&]<typename U>() -> void {
                    if constexpr (lossless_convertible<U, typename T::ValueType>) {
                        expr.add(DenseMatrixLikePyWrapper<typename T::ValueType>(other));
                    }
                    else {
                        throw py::type_error(std::format("Cannot add to DenseMatrixAddExpr. 'other' DenseMatrixLike dtype '{}' cannot convert to expression dtype '{}'", py::cast<std::string>(py::str(otherDt)), py::cast<std::string>(py::str(py::dtype::of<typename T::ValueType>()))));
                    }
                });
            }, self);

            return self;
        }, py::arg("other"), "Adds DenseMatrixLike to expression");

    dense_matrix_like_base_py.def("__add__", [](const PyDenseMatrixLike self, const PyDenseMatrixLike other) -> Py_DenseMatrixAddExpr {
        if (!py::isinstance<DenseMatrixLikeBase>(other)) {
            throw py::type_error(std::format("Cannot add to DenseMatrixLike. Got '{}' expected DenseMatrixLike", py::cast<std::string>(py::str(other))));
        }

        const py::dtype selfDt = get_dtype(self);
        const py::dtype otherDt = get_dtype(other);

        return dispatch_dt(selfDt, [&]<typename T>() -> Py_DenseMatrixAddExpr {
            return dispatch_dt(otherDt, [&]<typename U>() -> Py_DenseMatrixAddExpr {
                if constexpr (has_common_type<T, U>) {
                    return Py_DenseMatrixAddExpr(std::in_place_type<DynamicDenseMatrixAddExpr<DenseMatrixLikePyWrapper<std::common_type_t<T, U>>>>, DenseMatrixLikePyWrapper<std::common_type_t<T, U>>(self), DenseMatrixLikePyWrapper<std::common_type_t<T, U>>(other));
                }
                else {
                    throw py::type_error(std::format("Cannot add to DenseMatrixLike. 'other' DenseMatrixLike dtype '{}' cannot convert to matrix dtype '{}'", py::cast<std::string>(py::str(otherDt)), py::cast<std::string>(py::str(selfDt))));
                }
            });
        });
    });
}
