#ifndef MATHPY_COMMON_LIKE_H
#define MATHPY_COMMON_LIKE_H

#include "pybind11/pybind11.h"
#include "mathpp/implementation/common/traits.h"

namespace py = pybind11;

struct MatrixLikeBase {
    virtual ~MatrixLikeBase() = default;
};

template<scalar T>
struct MatrixLikePyWrapper {
    using ValueType = T;
    static constexpr bool isComplex = is_complex_v<T>;

    py::handle handle;

    MatrixLikePyWrapper(const py::handle obj) : handle(obj) {}

    [[nodiscard]] std::size_t rows() const {
        return py::cast<std::size_t>(handle.attr("rows")());
    }

    [[nodiscard]] std::size_t columns() const {
        return py::cast<std::size_t>(handle.attr("columns")());
    }

    [[nodiscard]] T get(const std::size_t r, const std::size_t c) const {
        return py::cast<T>(handle.attr("get")(r, c));
    }

    void set(const std::size_t r, const std::size_t c, const T v) const {
        handle.attr("set")(r, c, v);
    }
};

#endif // MATHPY_COMMON_LIKE_H
