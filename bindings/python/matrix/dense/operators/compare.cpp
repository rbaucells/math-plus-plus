#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <complex>
#include <variant>
#include <memory>
#include <utility>
#include <type_traits>
#include <string>

#include "../../../main.h"
#include "../../common/like.h"
#include "../like.h"
#include "compare.h"

#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/matrix/dense/operators/compare.h"

#include "../../../common/precision.h"

namespace py = pybind11;

// DynamicDenseMatrixCompareExpr of any type of DenseMatrixLikePyWrapper
using Py_DenseMatrixCompareExpr = std::variant<DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<uint8_t>>, DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<uint16_t>>, DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<uint32_t>>, DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<uint64_t>>, DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<int8_t>>, DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<int16_t>>, DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<int32_t>>, DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<int64_t>>, DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<float>>, DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<double>>, DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<std::complex<float>>>, DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<std::complex<double>>>>;

void matrix_dense_operators_compare_bindings(py::module_& m, py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py) {
    py::class_<Py_DenseMatrixCompareExpr>(m, "DenseMatrixCompareExpr", "Lazily evaluated expression for comparison between DenseMatrixLike objects")
        .def("evaluate", [](Py_DenseMatrixCompareExpr& self) -> bool {
            return std::visit([]<typename T>(const DynamicDenseMatrixCompareExpr<T>& expr) -> bool {
                return expr.evaluate();
            }, self);
        }, "Evaluates the compare expression to be true or false")
        .def("__or__", [](Py_DenseMatrixCompareExpr& self, const py::handle type) -> bool {
            if (!type.is(py::module_::import("builtins").attr("bool"))) {
                throw py::type_error(std::format("DenseMatrixCompareExpr cannot evaluate as a '{}', must evaluate to bool", py::cast<std::string>(py::str(type))));
            }

            return std::visit([]<typename T>(const DynamicDenseMatrixCompareExpr<T>& expr) -> bool {
                return expr;
            }, self);
        }, py::arg("type"), "Evaluates the compare expression to be true or false. 'type' must be 'bool'")
        .def("__eq__", [](Py_DenseMatrixCompareExpr& self, const PyDenseMatrixLike other) -> Py_DenseMatrixCompareExpr& {
            if (!py::isinstance<DenseMatrixLikeBase>(other)) {
                throw py::type_error(std::format("Cannot compare with DenseMatrixCompareExpr. Got '{}' expected DenseMatrixLike", py::cast<std::string>(py::str(other))));
            }

            std::visit([&]<typename T>(DynamicDenseMatrixCompareExpr<T>& expr) -> void {
                expr.add(DenseMatrixLikePyWrapper<typename T::ValueType>(other));
            }, self);

            return self;
        }, py::arg("other"), "Compares DenseMatrixLike 'other' with expression. (appends it to the expression)")
        .def("__add__", [](Py_DenseMatrixCompareExpr& self, const Py_Precision precision) -> Py_DenseMatrixCompareExpr& {
            std::visit([&]<typename T>(DynamicDenseMatrixCompareExpr<T>& expr) -> void {
                std::visit([&]<typename U>(const Precision<U>& p) -> void {
                    if constexpr (lossless_convertible<U, underlying_type_t<typename T::ValueType>>) {
                        expr.add(p);
                    }
                    else {
                        throw py::type_error(std::format("Cannot set precision on DenseMatrixCompareExpr. 'precision' dtype '{}' cannot convert to expression dtype '{}'", py::cast<std::string>(py::str(py::dtype::of<U>())), py::cast<std::string>(py::str(py::dtype::of<typename T::ValueType>()))));
                    }
                }, precision);
            }, self);

            return self;
        }, py::arg("precision"), "Sets the precision for the comparison to use when evaluated");

    dense_matrix_like_base_py.def("__eq__", [](const py::object self, const PyDenseMatrixLike other) -> Py_DenseMatrixCompareExpr {
        if (!py::isinstance<DenseMatrixLikeBase>(other)) {
            throw py::type_error(std::format("Cannot compare with DenseMatrixLike. Got '{}' expected DenseMatrixLike", py::cast<std::string>(py::str(other))));
        }

        const py::dtype selfDt = get_dtype(self);
        const py::dtype otherDt = get_dtype(other);

        return dispatch_dt(selfDt, [&]<typename T>() -> Py_DenseMatrixCompareExpr {
            return dispatch_dt(otherDt, [&]<typename U>() -> Py_DenseMatrixCompareExpr {
                if constexpr (has_common_type<T, U>) {
                    return Py_DenseMatrixCompareExpr(std::in_place_type<DynamicDenseMatrixCompareExpr<DenseMatrixLikePyWrapper<std::common_type_t<T, U>>>>, DenseMatrixLikePyWrapper<std::common_type_t<T, U>>(self), DenseMatrixLikePyWrapper<std::common_type_t<T, U>>(other));
                }
                else {
                    throw py::type_error(std::format("Cannot compare with DenseMatrixLike. 'other' DenseMatrixLike dtype '{}' cannot convert to matrix dtype '{}'", py::cast<std::string>(py::str(otherDt)), py::cast<std::string>(py::str(selfDt))));
                }
            });
        });
    });
}

