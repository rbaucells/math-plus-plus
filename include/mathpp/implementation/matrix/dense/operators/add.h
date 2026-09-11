#ifndef MATHPP_IMPLEMENTATION_MATRIX_DENSE_OPERATORS_ADD_H
#define MATHPP_IMPLEMENTATION_MATRIX_DENSE_OPERATORS_ADD_H

#include <tuple>
#include <type_traits>
#include <cstddef>
#include <vector>

#include "mathpp/implementation/common/expressions.h"
#include "../traits.h"
#include "../matrix.h"
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

template<dense_matrix_like T>
struct DynamicDenseMatrixAddExpr {
    using ValueType = typename T::ValueType;
    static constexpr bool isComplex = T::isComplex;
    static constexpr bool isExpr = true;

    std::vector<VectorExprStorage<T>> vector;

    explicit DynamicDenseMatrixAddExpr(std::vector<VectorExprStorage<T>> v) : vector(std::move(v)) {}

    template<std::ranges::sized_range R>
    explicit DynamicDenseMatrixAddExpr(const R& range) : vector(range.size()) {
        std::size_t i = 0;
        for (const auto& m : range) {
            vector[i] = m;
        }
    }

    template<typename... Args> requires (std::same_as<std::remove_cvref_t<Args>, VectorExprStorage<T>> && ...)
    explicit DynamicDenseMatrixAddExpr(Args&&... args) : vector{std::forward<Args>(args)...} {}

    [[nodiscard]] std::size_t rows() const {
        return vector[0].rows();
    }

    [[nodiscard]] std::size_t columns() const {
        return vector[0].columns();
    }

    [[nodiscard]] ValueType operator[](const std::size_t r, const std::size_t c) const {
        ValueType sum = {};

        for (const auto& m : vector) {
            sum += m[r, c];
        }

        return sum;
    }

    [[nodiscard]] ValueType& operator[](const std::size_t, const std::size_t) {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "Cannot get ref on DynamicDenseMatrixAddExpr");
    }

    [[nodiscard]] ValueType get(const std::size_t r, const std::size_t c) const {
        ValueType sum = {};

        for (const auto& m : vector) {
            sum += m.get(r, c);
        }

        return sum;
    }

    void set(const std::size_t, const std::size_t, const ValueType) {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "Cannot set on DynamicDenseMatrixAddExpr");
    }

    DynamicDenseMatrixAddExpr<T>& add(VectorExprStorage<T> other) {
        vector.push_back(std::move(other));
        return *this;
    }
};

template<std::ranges::random_access_range R, dense_matrix_like T = std::ranges::range_value_t<R>> requires dense_matrix_like<std::ranges::range_value_t<R>>
DynamicDenseMatrixAddExpr<T> add(const R& args) {
    assert_same_dimensions(args);
    return DynamicDenseMatrixAddExpr<T>(args);
}

#endif // MATHPP_IMPLEMENTATION_MATRIX_DENSE_OPERATORS_ADD_H
