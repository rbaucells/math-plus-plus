#ifndef MATHPY_VECTOR_COMMON_LIKE_H
#define MATHPY_VECTOR_COMMON_LIKE_H

#include <pybind11/pybind11.h>

#include <cstddef>

#include "mathpp/implementation/common/traits.h"

namespace py = pybind11;

struct VectorLikeBase {
    virtual ~VectorLikeBase() = default;
};

template<scalar T>
struct VectorLikePyWrapper {
    using ValueType = T;
    static constexpr bool isExpr = true;
    static constexpr bool isComplex = is_complex_v<T>;

    py::object object;

    VectorLikePyWrapper(py::object obj) : object(std::move(obj)) {}

    [[nodiscard]] std::size_t n() const {
        return py::cast<std::size_t>(object.attr("n")());
    }

    [[nodiscard]] T get(const std::size_t i) const {
        return py::cast<T>(object.attr("get")(i));
    }

    void set(const std::size_t i, const T v) const {
        object.attr("set")(i, v);
    }
};

#endif // MATHPY_VECTOR_COMMON_LIKE_H
