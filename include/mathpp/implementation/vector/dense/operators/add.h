#ifndef MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_ADD_H
#define MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_ADD_H

#include <tuple>
#include <type_traits>
#include <cstddef>

#include "mathpp/implementation/common/expressions.h"
#include "../traits.h"
#include "../../common/asserts.h"

template<dense_vector_like T, dense_vector_like U, dense_vector_like... ARGS>
struct DenseVectorAddExpr {
    using ValueType = std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>;

    static constexpr bool isComplex = T::isComplex || U::isComplex || (ARGS::isComplex || ...);
    static constexpr bool isExpr = true;

    const std::tuple<ExprStorage<T>, ExprStorage<U>, ExprStorage<ARGS>...> tuple;

    DenseVectorAddExpr(ExprStorage<T> a, ExprStorage<U> b, ExprStorage<ARGS>... args) : tuple(a, b, args...) {}

    [[nodiscard]] std::size_t n() const {
        return std::get<0>(tuple).n();
    }

    [[nodiscard]] ValueType operator[](const std::size_t i) const {
        return std::apply([i](const auto&... args) {
            return (... + args[i]);
        }, tuple);
    }

    [[nodiscard]] ValueType at(const std::size_t i) const {
        return std::apply([i](const auto&... args) {
            return (... + args.at(i));
        }, tuple);
    }
};

template<dense_vector_like T, dense_vector_like U>
DenseVectorAddExpr<T, U> operator+(const T& a, const U& b) {
    return DenseVectorAddExpr<T, U>(a, b);
}

template<dense_vector_like T, dense_vector_like U, dense_vector_like... ARGS>
DenseVectorAddExpr<T, U, ARGS...> add(const T& a, const U& b, const ARGS&... args) {
    assert_same_size(a, b, args...);
    return DenseVectorAddExpr<T, U, ARGS...>(a, b, args...);
}

#endif // MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_ADD_H
