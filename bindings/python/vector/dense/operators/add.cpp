#include "add.h"
#include "mathpp/implementation/vector/dense/operators/add.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <complex>
#include <variant>
#include <memory>
#include <utility>

#include "mathpp/implementation/vector/dense/traits.h"
#include "mathpp/implementation/vector/dense/operators/add.h"

#include "../like.h"
#include "../vector.h"
#include "../../../main.h"

namespace py = pybind11;

using Py_DenseVectorAddExpr = std::variant<DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<uint8_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<uint16_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<uint32_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<uint64_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<int8_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<int16_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<int32_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<int64_t>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<float>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<double>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<std::complex<float>>>, DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<std::complex<double>>>>;

void vector_dense_operators_add_bindings(py::module_& m, py::class_<DenseVectorLikeBase, VectorLikeBase> dense_vector_like_base_py) {
    py::class_<Py_DenseVectorAddExpr>(m, "DenseVectorAddExpr")
        .def("evaluate", [](Py_DenseVectorAddExpr& self) -> Py_DenseVector {
            return std::visit([]<typename T>(const DynamicDenseVectorAddExpr<T>& expr) -> Py_DenseVector {
                return Py_DenseVector(std::in_place_type<DenseVector<typename T::ValueType>>, expr);
            }, self);
        })
        .def("__or__", [](Py_DenseVectorAddExpr& self, const py::handle type) -> Py_DenseVector {
            if (!type.is(py::type::of<Py_DenseVector>())) {
                throw py::type_error("DenseVectorAddExpr must evaluate to DenseVector");
            }

            return std::visit([]<typename T>(const DynamicDenseVectorAddExpr<T>& expr) -> Py_DenseVector {
                return Py_DenseVector(std::in_place_type<DenseVector<typename T::ValueType>>, expr);
            }, self);
        })
        .def("__add__", [](Py_DenseVectorAddExpr& self, const py::object other) -> Py_DenseVectorAddExpr& {
            if (!py::isinstance<DenseVectorLikeBase>(other)) {
                throw py::type_error("DenseVectorAddExpr can only add dense vector likes");
            }

            std::visit([&]<typename T>(DynamicDenseVectorAddExpr<T>& expr) -> void {
                const py::dtype otherDt = get_dtype(other);
                dispatch_dt(otherDt, [&]<typename U>() -> void {
                    if constexpr (lossless_convertible<U, typename T::ValueType>) {
                        expr.add(DenseVectorLikePyWrapper<typename T::ValueType>(other));
                    }
                    else {
                        throw py::type_error("Cannot add incompatible types to DenseVectorAddExpr");
                    }
                });
            }, self);

            return self;
        });

    dense_vector_like_base_py.def("__add__", [](const py::object self, const py::object other) -> Py_DenseVectorAddExpr {
        if (!py::isinstance<DenseVectorLikeBase>(other)) {
            throw py::type_error();
        }

        const py::dtype selfDt = get_dtype(self);
        const py::dtype otherDt = get_dtype(other);

        return dispatch_dt(selfDt, [&]<typename T>() -> Py_DenseVectorAddExpr {
            return dispatch_dt(otherDt, [&]<typename U>() -> Py_DenseVectorAddExpr {
                if constexpr (has_common_type<T, U>) {
                    return Py_DenseVectorAddExpr(std::in_place_type<DynamicDenseVectorAddExpr<DenseVectorLikePyWrapper<std::common_type_t<T, U>>>>, DenseVectorLikePyWrapper<std::common_type_t<T, U>>(self), DenseVectorLikePyWrapper<std::common_type_t<T, U>>(other));
                }
                else {
                    throw py::type_error();
                }
            });
        });
    });
}
