#ifndef MATHPY_MATRIX_DENSE_LIKE_H
#define MATHPY_MATRIX_DENSE_LIKE_H

#include <pybind11/pybind11.h>
#include <cstddef>

#include "../common/like.h"

namespace py = pybind11;

struct DenseMatrixLikeBase : MatrixLikeBase {
    virtual ~DenseMatrixLikeBase() = default;
};

template<scalar T>
struct DenseMatrixLikeElementPyWrapper {
    py::handle handle;
    const std::size_t r;
    const std::size_t c;

    DenseMatrixLikeElementPyWrapper& operator=(const T& v) {
        handle.attr("__setitem__")(std::pair(r, c), v);
        return *this;
    }

    operator T() const {
        return py::cast<T>(handle.attr("__getitem__")(std::pair(r, c)));
    }
};

template<scalar T>
struct DenseMatrixLikePyWrapper : MatrixLikePyWrapper<T> {
    using MatrixLikePyWrapper<T>::MatrixLikePyWrapper;

    [[nodiscard]] T operator[](const std::size_t r, const std::size_t c) const {
        return py::cast<T>(this->object.attr("__getitem__")(std::pair(r, c)));
    }

    [[nodiscard]] DenseMatrixLikeElementPyWrapper<T> operator[](const std::size_t r, const std::size_t c) {
        return DenseMatrixLikeElementPyWrapper<T>(this->object, r, c);
    }
};

#endif // MATHPY_MATRIX_DENSE_LIKE_H
