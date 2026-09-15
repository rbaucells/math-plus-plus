#include "compare.h"
#include "mathpp/implementation/vector/dense/operators/compare.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <complex>
#include <variant>
#include <memory>
#include <utility>
#include <type_traits>
#include <string>
#include <format>

#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/vector/dense/operators/compare.h"

#include "../like.h"
#include "../vector.h"
#include "../../../main.h"
#include "../../../common/precision.h"

namespace py = pybind11;

// DynamicDenseVectorCompareExpr of any type of DenseVectorLikePyWrapper
using Py_DenseVectorCompareExpr = std::variant<DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<uint8_t>>, DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<uint16_t>>, DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<uint32_t>>, DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<uint64_t>>, DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<int8_t>>, DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<int16_t>>, DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<int32_t>>, DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<int64_t>>, DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<float>>, DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<double>>, DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<std::complex<float>>>, DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<std::complex<double>>>>;

void vector_dense_operators_compare_bindings(py::module_& m, py::class_<DenseVectorLikeBase, VectorLikeBase> dense_vector_like_base_py) {
    py::class_<Py_DenseVectorCompareExpr>(m, "DenseVectorCompareExpr", "Lazily evaluated expression for comparison between DenseVectorLike objects")
        .def("evaluate", [](Py_DenseVectorCompareExpr& self) -> bool {
            return std::visit([]<typename T>(const DynamicDenseVectorCompareExpr<T>& expr) -> bool {
                return expr.evaluate();
            }, self);
        }, "Evaluates the compare expression to be true or false")
        .def("__or__", [](Py_DenseVectorCompareExpr& self, const py::handle type) -> bool {
            if (!type.is(py::module_::import("builtins").attr("bool"))) {
                throw py::type_error(std::format("DenseVectorCompareExpr cannot evaluate as a '{}', must evaluate to bool", py::cast<std::string>(py::str(type))));
            }

            return std::visit([]<typename T>(const DynamicDenseVectorCompareExpr<T>& expr) -> bool {
                return expr;
            }, self);
        }, py::arg("type"), "Evaluates the compare expression to be true or false. 'type' must be 'bool'")
        .def("__eq__", [](Py_DenseVectorCompareExpr& self, const PyDenseVectorLike other) -> Py_DenseVectorCompareExpr& {
            if (!py::isinstance<DenseVectorLikeBase>(other)) {
                throw py::type_error(std::format("Cannot compare with DenseVectorCompareExpr. Got '{}' expected DenseVectorLike", py::cast<std::string>(py::str(other))));
            }

            std::visit([&]<typename T>(DynamicDenseVectorCompareExpr<T>& expr) -> void {
                expr.add(DenseVectorLikePyWrapper<typename T::ValueType>(other));
            }, self);

            return self;
        }, py::arg("other"), "Compares DenseVectorLike 'other' with expression. (appends it to the expression)")
        .def("__add__", [](Py_DenseVectorCompareExpr& self, const Py_Precision precision) -> Py_DenseVectorCompareExpr& {
            std::visit([&]<typename T>(DynamicDenseVectorCompareExpr<T>& expr) -> void {
                std::visit([&]<typename U>(const Precision<U>& p) -> void {
                    if constexpr (lossless_convertible<U, underlying_type_t<typename T::ValueType>>) {
                        expr.add(p);
                    }
                    else {
                        throw py::type_error(std::format("Cannot set precision on DenseVectorCompareExpr. 'precision' dtype '{}' cannot convert to expression dtype '{}'", py::cast<std::string>(py::str(py::dtype::of<U>())), py::cast<std::string>(py::str(py::dtype::of<typename T::ValueType>()))));
                    }
                }, precision);
            }, self);

            return self;
        }, py::arg("precision"), "Sets the precision for the comparison to use when evaluated");

    dense_vector_like_base_py.def("__eq__", [](const py::object self, const PyDenseVectorLike other) -> Py_DenseVectorCompareExpr {
        if (!py::isinstance<DenseVectorLikeBase>(other)) {
            throw py::type_error(std::format("Cannot compare with DenseVectorLike. Got '{}' expected DenseVectorLike", py::cast<std::string>(py::str(other))));
        }

        const py::dtype selfDt = get_dtype(self);
        const py::dtype otherDt = get_dtype(other);

        return dispatch_dt(selfDt, [&]<typename T>() -> Py_DenseVectorCompareExpr {
            return dispatch_dt(otherDt, [&]<typename U>() -> Py_DenseVectorCompareExpr {
                if constexpr (has_common_type<T, U>) {
                    return Py_DenseVectorCompareExpr(std::in_place_type<DynamicDenseVectorCompareExpr<DenseVectorLikePyWrapper<std::common_type_t<T, U>>>>, DenseVectorLikePyWrapper<std::common_type_t<T, U>>(self), DenseVectorLikePyWrapper<std::common_type_t<T, U>>(other));
                }
                else {
                    throw py::type_error(std::format("Cannot compare with DenseVectorLike. 'other' DenseVectorLike dtype '{}' cannot convert to vector dtype '{}'", py::cast<std::string>(py::str(otherDt)), py::cast<std::string>(py::str(selfDt))));
                }
            });
        });
    });
}
