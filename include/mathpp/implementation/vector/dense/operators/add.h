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

    [[nodiscard]] ValueType& operator[](const std::size_t) {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "Cannot get ref on DenseVectorAddExpr");
    }

    [[nodiscard]] ValueType get(const std::size_t i) const {
        return std::apply([i](const auto&... args) {
            return (... + args.get(i));
        }, tuple);
    }

    void set(const std::size_t, const ValueType) {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "Cannot set on DenseVectorAddExpr");
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

template<dense_vector_like T>
struct DynamicDenseVectorAddExpr {
    using ValueType = typename T::ValueType;
    static constexpr bool isComplex = T::isComplex;
    static constexpr bool isExpr = true;

    std::vector<VectorExprStorage<T>> vector;

    explicit DynamicDenseVectorAddExpr(std::vector<VectorExprStorage<T>> v) : vector(std::move(v)) {}

    template<std::ranges::sized_range R>
    explicit DynamicDenseVectorAddExpr(const R& range) : vector(range.size()) {
        std::size_t i = 0;
        for (const auto& m : range) {
            vector[i] = m;
        }
    }

    template<typename... Args> requires (std::same_as<std::remove_cvref_t<Args>, VectorExprStorage<T>> && ...)
    explicit DynamicDenseVectorAddExpr(Args&&... args) : vector{std::forward<Args>(args)...} {}

    [[nodiscard]] std::size_t n() const {
        return vector[0].n();
    }

    [[nodiscard]] ValueType operator[](const std::size_t i) const {
        ValueType sum = {};

        for (const auto& m : vector) {
            sum += m[i];
        }

        return sum;
    }

    [[nodiscard]] ValueType& operator[](const std::size_t) {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "Cannot get ref on DynamicDenseVectorAddExpr");
    }

    [[nodiscard]] ValueType get(const std::size_t i) const {
        ValueType sum = {};

        for (const auto& m : vector) {
            sum += m.get(i);
        }

        return sum;
    }

    void set(const std::size_t, const ValueType) {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "Cannot set on DynamicDenseVectorAddExpr");
    }

    DynamicDenseVectorAddExpr<T>& add(VectorExprStorage<T> other) {
        vector.push_back(std::move(other));
        return *this;
    }
};

template<std::ranges::random_access_range R, dense_vector_like T = std::ranges::range_value_t<R>> requires dense_vector_like<std::ranges::range_value_t<R>>
DynamicDenseVectorAddExpr<T> add(const R& args) {
    assert_same_size(args);
    return DynamicDenseVectorAddExpr<T>(args);
}

#endif // MATHPP_IMPLEMENTATION_VECTOR_DENSE_OPERATORS_ADD_H
