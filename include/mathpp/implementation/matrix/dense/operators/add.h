#ifndef MATHPP_IMPLEMENTATION_MATRIX_DENSE_OPERATORS_ADD_H
#define MATHPP_IMPLEMENTATION_MATRIX_DENSE_OPERATORS_ADD_H

#include <tuple>
#include <type_traits>
#include <cstddef>

#include "mathpp/implementation/common/expressions.h"
#include "../traits.h"
#include "../../common/asserts.h"

template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS>
struct DenseMatrixAddExpr {
    using ValueType = std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>;

    static constexpr bool isComplex = T::isComplex || U::isComplex || (ARGS::isComplex || ...);
    static constexpr bool isExpr = true;

    const std::tuple<ExprStorage<T>, ExprStorage<U>, ExprStorage<ARGS>...> tuple;

    DenseMatrixAddExpr(ExprStorage<T> a, ExprStorage<U> b, ExprStorage<ARGS>... args) : tuple(a, b, args...) {}

    [[nodiscard]] std::size_t rows() const {
        return std::get<0>(tuple).rows();
    }

    [[nodiscard]] std::size_t columns() const {
        return std::get<0>(tuple).columns();
    }

    [[nodiscard]] ValueType operator[](const std::size_t r, const std::size_t c) const {
        return std::apply([r, c](const auto&... args) {
            return (... + args[r, c]);
        }, tuple);
    }

    [[nodiscard]] ValueType& operator[](const std::size_t, const std::size_t) {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "Cannot get ref on DenseMatrixAddExpr");
    }

    [[nodiscard]] ValueType get(const std::size_t r, const std::size_t c) const {
        return std::apply([r, c](const auto&... args) {
            return (... + args.get(r, c));
        }, tuple);
    }

    void set(const std::size_t, const std::size_t, const ValueType) {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "Cannot set on DenseMatrixAddExpr");
    }
};

template<dense_matrix_like T, dense_matrix_like U>
DenseMatrixAddExpr<T, U> operator+(const T& a, const U& b) {
    return DenseMatrixAddExpr<T, U>(a, b);
}

template<dense_matrix_like T, dense_matrix_like U, dense_matrix_like... ARGS>
DenseMatrixAddExpr<T, U, ARGS...> add(const T& a, const U& b, const ARGS&... args) {
    assert_same_dimensions(a, b, args...);
    return DenseMatrixAddExpr<T, U, ARGS...>(a, b, args...);
}

#endif // MATHPP_IMPLEMENTATION_MATRIX_DENSE_OPERATORS_ADD_H
