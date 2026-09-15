#include "add.h"
#include "mathpp/implementation/vector/dense/operators/add.h"

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

#include "mathpp/implementation/vector/dense/traits.h"
#include "mathpp/implementation/vector/dense/operators/add.h"

#include "../like.h"
#include "../vector.h"
#include "../../../main.h"

namespace py = pybind11;

// DynamicDenseVectorAddExpr of any type of DenseVectorLikePyWrapper
using Py_DenseVectorAddExpr = std::variant<DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<uint8_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<uint16_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<uint32_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<uint64_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<int8_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<int16_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<int32_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<int64_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<float>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<double>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<std::complex<float>>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<std::complex<double>>>>;

void vector_dense_operators_add_bindings(py::module_& m, py::class_<DenseVectorLikeBase, VectorLikeBase> dense_vector_like_base_py) {
    py::class_<Py_DenseVectorAddExpr>(m, "DenseVectorAddExpr", "Lazily evaluated expression for sum of DenseVectorLike objects")
        .def("evaluate", [](Py_DenseVectorAddExpr& self) -> Py_DenseVector {
            return std::visit([]<typename T>(const DynamicDenseVectorAddExpr<T>& expr) -> Py_DenseVector {
                return Py_DenseVector(std::in_place_type<DenseVector<typename T::ValueType>>, expr);
            }, self);
        }, "Constructs a DenseVector whose elements are made up of the sum of vectors in expression")
        .def("__or__", [](Py_DenseVectorAddExpr& self, const py::handle type) -> Py_DenseVector {
            if (!type.is(py::type::of<Py_DenseVector>())) {
                throw py::type_error(std::format("DenseVectorAddExpr cannot evaluate as a '{}', must evaluate to DenseVector", py::cast<std::string>(py::str(type))));
            }

            return std::visit([]<typename T>(const DynamicDenseVectorAddExpr<T>& expr) -> Py_DenseVector {
                return Py_DenseVector(std::in_place_type<DenseVector<typename T::ValueType>>, expr);
            }, self);
        }, py::arg("type"), "Evaluates the expression, constructs a DenseVector whose elements are made up of the sum of vectors in expression. 'type' must be 'DenseVector'")
        .def("__add__", [](Py_DenseVectorAddExpr& self, const PyDenseVectorLike other) -> Py_DenseVectorAddExpr& {
            if (!py::isinstance<DenseVectorLikeBase>(other)) {
                throw py::type_error(std::format("Cannot add to DenseVectorAddExpr. Got '{}' expected DenseVectorLike", py::cast<std::string>(py::str(other))));
            }

            std::visit([&]<typename T>(DynamicDenseVectorAddExpr<T>& expr) -> void {
                const py::dtype otherDt = get_dtype(other);

                dispatch_dt(otherDt, [&]<typename U>() -> void {
                    if constexpr (lossless_convertible<U, typename T::ValueType>) {
                        expr.add(DenseVectorLikePyWrapper<typename T::ValueType>(other));
                    }
                    else {
                        throw py::type_error(std::format("Cannot add to DenseVectorAddExpr. 'other' DenseVectorLike dtype '{}' cannot convert to expression dtype '{}'", py::cast<std::string>(py::str(otherDt)), py::cast<std::string>(py::str(py::dtype::of<typename T::ValueType>()))));
                    }
                });
            }, self);

            return self;
        }, py::arg("other"), "Adds DenseVectorLike to expression");

    dense_vector_like_base_py.def("__add__", [](const PyDenseVectorLike self, const PyDenseVectorLike other) -> Py_DenseVectorAddExpr {
        if (!py::isinstance<DenseVectorLikeBase>(other)) {
            throw py::type_error(std::format("Cannot add to DenseVectorLike. Got '{}' expected DenseVectorLike", py::cast<std::string>(py::str(other))));
        }

        const py::dtype selfDt = get_dtype(self);
        const py::dtype otherDt = get_dtype(other);

        return dispatch_dt(selfDt, [&]<typename T>() -> Py_DenseVectorAddExpr {
            return dispatch_dt(otherDt, [&]<typename U>() -> Py_DenseVectorAddExpr {
                if constexpr (has_common_type<T, U>) {
                    return Py_DenseVectorAddExpr(std::in_place_type<DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<std::common_type_t<T, U>>>>, DenseVectorLikePyWrapper<std::common_type_t<T, U>>(self), DenseVectorLikePyWrapper<std::common_type_t<T, U>>(other));
                }
                else {
                    throw py::type_error(std::format("Cannot add to DenseVectorLike. 'other' DenseVectorLike dtype '{}' cannot convert to vector dtype '{}'", py::cast<std::string>(py::str(otherDt)), py::cast<std::string>(py::str(selfDt))));
                }
            });
        });
    });
}
