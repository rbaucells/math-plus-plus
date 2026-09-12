#ifndef MATHPY_VECTOR_DENSE_LIKE_H
#define MATHPY_VECTOR_DENSE_LIKE_H

#include <pybind11/pybind11.h>
#include <cstddef>

#include "../common/like.h"

namespace py = pybind11;

struct DenseVectorLikeBase : VectorLikeBase {
    virtual ~DenseVectorLikeBase() = default;
};

template<scalar T>
struct DenseVectorLikeElementPyWrapper {
    py::handle handle;
    const std::size_t i;

    DenseVectorLikeElementPyWrapper& operator=(const T& v) {
        handle.attr("__setitem__")(i, v);
        return *this;
    }

    operator T() const {
        return py::cast<T>(handle.attr("__getitem__")(i));
    }
};

template<scalar T>
struct DenseVectorLikePyWrapper : VectorLikePyWrapper<T> {
    using VectorLikePyWrapper<T>::VectorLikePyWrapper;

    [[nodiscard]] T operator[](const std::size_t i) const {
        return py::cast<T>(this->object.attr("__getitem__")(i));
    }

    [[nodiscard]] DenseVectorLikeElementPyWrapper<T> operator[](const std::size_t i) {
        return DenseVectorLikeElementPyWrapper<T>(this->object, i);
    }
};

#endif // MATHPY_VECTOR_DENSE_LIKE_H
