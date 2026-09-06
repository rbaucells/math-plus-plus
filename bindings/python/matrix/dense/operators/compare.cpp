#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include <complex>
#include <variant>
#include <memory>
#include <utility>

#include "../../../main.h"
#include "../../common/like.h"
#include "../like.h"
#include "compare.h"

#include "mathpp/implementation/common/traits.h"
#include "mathpp/implementation/matrix/dense/operators/compare.h"

#include "../../../common/precision.h"

namespace py = pybind11;

template<dense_matrix_like T>
struct Wrapper {
    struct Base {
        [[nodiscard]] virtual bool evaluate() const = 0;
        virtual void append(const T& v) = 0;
        virtual void append(const Precision<underlying_type_t<typename T::ValueType>>& precision) = 0;
    };

    template<dense_matrix_like... ARGS>
    struct Expression : Base, DenseMatrixCompareExpr<ARGS...> {
        Expression(ARGS&&... args) : Base(), DenseMatrixCompareExpr<ARGS...>(std::forward<ARGS>(args)...) {}

        [[nodiscard]] bool evaluate() const override {
            return DenseMatrixCompareExpr<ARGS...>::operator bool();
        }

        void append(const T& v) override {
            DenseMatrixCompareExpr<ARGS...>::operator==(v);
        }

        void append(const Precision<underlying_type_t<typename T::ValueType>>& precision) override {
            DenseMatrixCompareExpr<ARGS...>::operator+(precision);
        }
    };

    template<typename... ARGS>
    requires (std::same_as<std::remove_cvref_t<ARGS>, T> && ...)
    Wrapper(ARGS&&... args) {
        base = std::make_unique<Expression<ARGS...>>(std::forward<ARGS>(args)...);
    }

    [[nodiscard]] bool evaluate() const {
        return base->evaluate();
    }

    void append(const T& v) {
        base->append(v);
    }

    void append(const Precision<underlying_type_t<typename T::ValueType>>& precision) {
        base->append(precision);
    }

    std::unique_ptr<Base> base;
};

using Py_Wrapper = std::variant<Wrapper<DenseMatrixLikePyWrapper<uint8_t>>, Wrapper<DenseMatrixLikePyWrapper<uint16_t>>, Wrapper<DenseMatrixLikePyWrapper<uint32_t>>, Wrapper<DenseMatrixLikePyWrapper<uint64_t>>, Wrapper<DenseMatrixLikePyWrapper<int8_t>>, Wrapper<DenseMatrixLikePyWrapper<int16_t>>, Wrapper<DenseMatrixLikePyWrapper<int32_t>>, Wrapper<DenseMatrixLikePyWrapper<int64_t>>, Wrapper<DenseMatrixLikePyWrapper<float>>, Wrapper<DenseMatrixLikePyWrapper<double>>, Wrapper<DenseMatrixLikePyWrapper<std::complex<float>>>, Wrapper<DenseMatrixLikePyWrapper<std::complex<double>>>>;

void matrix_dense_operators_compare_bindings(py::module_& m, py::class_<DenseMatrixLikeBase, MatrixLikeBase> dense_matrix_like_base_py) {
    py::class_<Py_Wrapper> wrapper(m, "Wrapper");

    wrapper.def("__eq__", [](Py_Wrapper& self, const py::object& other) {
        if (!py::isinstance<DenseMatrixLikeBase>(other)) {
            throw py::type_error();
        }

        py::print("wrapper ==");

        std::visit([&]<typename T>(Wrapper<T>& a) {
            using ValueType = T::ValueType;

            const py::dtype dt = get_dtype(other);

            dispatch_dt(dt, [&]<typename U>()  {
                if constexpr (lossless_convertible<U, ValueType>) {
                    const DenseMatrixLikePyWrapper<ValueType> like(other);

                    a.append(like);
                }
                else {
                    throw py::type_error();
                }
            });
        }, self);
    });

    wrapper.def("__eq__", [](Py_Wrapper& self, const Py_Precision& precision) {
        std::visit([&]<typename T>(Wrapper<T>& a) {
            using ValueType = T::ValueType;

            std::visit([&]<typename U>(const Precision<U>& p) {
                if constexpr (lossless_convertible<U, underlying_type_t<ValueType>>) {
                    const Precision<underlying_type_t<ValueType>> casted(p.value);
                    a.append(casted);
                }
                else {
                    throw py::type_error();
                }
            }, precision);
        }, self);
    });

    wrapper.def("__or__", [](Py_Wrapper& self, py::object type) -> bool {
        if (!type.is(py::handle((PyObject*)&PyBool_Type))) {
            throw py::type_error();
        }

        py::print("or bool");

        return std::visit([&]<typename T>(const Wrapper<T>& a) -> bool {
            return a.evaluate();
        }, self);
    });

    dense_matrix_like_base_py.def("__eq__", [](const py::object& self, const py::object& other) -> Py_Wrapper {
        if (!py::isinstance<DenseMatrixLikeBase>(other)) {
            throw py::type_error("Cannot compare with object that does not derive from DenseMatrixLike");
        }

        py::print("like ==");

        const py::dtype selfDt = self.attr("dtype")();
        const py::dtype otherDt = other.attr("dtype")();

        return dispatch_dt(selfDt, [&]<typename T>() -> Py_Wrapper {
            return dispatch_dt(otherDt, [&]<typename U>() -> Py_Wrapper {
                if constexpr (has_common_type<T, U>) {
                    return Py_Wrapper(std::in_place_type<Wrapper<DenseMatrixLikePyWrapper<T>>>, DenseMatrixLikePyWrapper<T>(self), DenseMatrixLikePyWrapper<T>(other));
                }
                else {
                    throw py::type_error();
                }
            });
        });
    });
}

