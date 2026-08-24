#ifndef MATHPY_MATRIX_DENSE_LIKE_H
#define MATHPY_MATRIX_DENSE_LIKE_H
#include <utility>

#include "../common/like.h"
#include "mathpp/implementation/common/traits.h"

struct DenseMatrixLikeBase : MatrixLikeBase {
    virtual ~DenseMatrixLikeBase() = default;
};

template<scalar T>
struct DenseMatrixLikeElementPyWrapper {
    const py::object& object;
    std::size_t r;
    std::size_t c;

    DenseMatrixLikeElementPyWrapper& operator=(const T& v) {
        object.attr("__setitem__")(r, c, v);
        return *this;
    }

    operator T() const {
        return py::cast<T>(object.attr("__getitem__")(r, c));
    }
};

template<scalar T>
struct DenseMatrixLikePyWrapper {
    using ValueType = T;
    static constexpr bool isComplex = is_complex_v<T>;

    py::object object;

    DenseMatrixLikePyWrapper(py::object obj) : object(std::move(obj)) {}

    [[nodiscard]] std::size_t rows() const {
        return py::cast<std::size_t>(object.attr("rows")());
    }

    [[nodiscard]] std::size_t columns() const {
        return py::cast<std::size_t>(object.attr("columns")());
    }

    [[nodiscard]] T get(const std::size_t r, const std::size_t c) const {
        return py::cast<T>(object.attr("get")(r, c));
    }

    void set(const std::size_t r, const std::size_t c, const T v) const {
        object.attr("set")(r, c, v);
    }

    [[nodiscard]] T operator[](const std::size_t c, const std::size_t r) const {
        return py::cast<T>(object.attr("__getitem__")(r, c));
    }

    [[nodiscard]] DenseMatrixLikeElementPyWrapper<T> operator[](const std::size_t c, const std::size_t r) {
        return DenseMatrixLikeElementPyWrapper<T>(object, r, c);
    }
};

#endif // MATHPY_MATRIX_DENSE_LIKE_H
