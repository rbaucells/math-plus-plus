#ifndef MATHPP_IMPLEMENTATION_COMMON_EXPRESSIONS_H
#define MATHPP_IMPLEMENTATION_COMMON_EXPRESSIONS_H

#include <type_traits>

template<typename T>
concept expr = T::isExpr;

template<typename T>
using ExprStorage = std::conditional_t<expr<T>, T, const T&>;

template<typename T>
using VectorExprStorage = std::conditional_t<expr<T>, T, std::reference_wrapper<const T>>;

#endif // MATHPP_IMPLEMENTATION_COMMON_EXPRESSIONS_H
