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
        object.attr("__setitem__")(std::pair(r, c), v);
        return *this;
    }

    operator T() const {
        return py::cast<T>(object.attr("__getitem__")(std::pair(r, c)));
    }
};

template<scalar T>
struct DenseMatrixLikePyWrapper : MatrixLikePyWrapper<T> {
    using MatrixLikePyWrapper<T>::MatrixLikePyWrapper;

    [[nodiscard]] T operator[](const std::size_t r, const std::size_t c) const {
        return py::cast<T>(this->object.attr("__getitem__")(std::pair(r, c)));
    }

    [[nodiscard]] DenseMatrixLikeElementPyWrapper<T> operator[](const std::size_t r, const std::size_t c) {
        return DenseMatrixLikeElementPyWrapper<T>(this->object, std::pair(r, c));
    }
};

#endif // MATHPY_MATRIX_DENSE_LIKE_H
