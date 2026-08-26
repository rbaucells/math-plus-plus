#ifndef MATHPY_COMMON_LIKE_H
#define MATHPY_COMMON_LIKE_H
#include "mathpp/implementation/common/traits.h"

struct MatrixLikeBase {
    virtual ~MatrixLikeBase() = default;
};

template<scalar T>
struct MatrixLikePyWrapper {
    using ValueType = T;
    static constexpr bool isComplex = is_complex_v<T>;

    py::object object;

    MatrixLikePyWrapper(py::object obj) : object(std::move(obj)) {}

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
};

#endif // MATHPY_COMMON_LIKE_H
