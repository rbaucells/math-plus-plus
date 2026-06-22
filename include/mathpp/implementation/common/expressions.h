#pragma once
#include <type_traits>

template<typename T>
concept expr = T::isExpr;

template<typename T>
using ExprStorage = std::conditional_t<expr<T>, T, const T&>;
