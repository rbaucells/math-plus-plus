#pragma once
#include "../vector.h"
#include "../../../helper.h"

template<dense_vector_base T, dense_vector_base U, dense_vector_base... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const T& a, const U& b, const ARGS&... args) {
    return compare(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>>>()), a, b, args...);
}

template<dense_vector_base T, dense_vector_base U, dense_vector_base... ARGS> requires has_common_type<typename T::ValueType, typename U::ValueType, typename ARGS::ValueType...>
[[nodiscard]] bool compare(const Precision<underlying_type_t<std::common_type_t<typename T::ValueType, typename ARGS::ValueType...>>> precision, const T& a, const U& b, const ARGS&... args) {
    assert_same_size(a, b, args...);

    const int columns = a.n();

    for (int i = 0; i < columns; i++) {
        if (!compare(precision, a[i], b[i], args[i]...)) {
            return false;
        }
    }

    return true;
}

template<dense_vector_base... ARGS> requires has_common_type<typename ARGS::ValueType...>
struct DenseVectorCompareExpr : Expression<bool, ARGS...> {
    Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision;

    DenseVectorCompareExpr(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>> precision, const ARGS&... args) : Expression<bool, ARGS...>(args...), precision(precision) {}


    [[nodiscard]] bool evaluate() const override {
        return std::apply([this](const auto&... args) {
            return compare(precision, args...);
        }, this->args);
    }

    template<dense_vector_base OTHER> requires has_common_type<typename ARGS::ValueType..., typename OTHER::ValueType>
    DenseVectorCompareExpr<ARGS..., OTHER> operator==(const OTHER& other) const {
        return std::apply([&](const auto&... args) {
            return DenseVectorCompareExpr<ARGS..., OTHER>(precision, args..., other);
        }, this->args);
    }

    DenseVectorCompareExpr<ARGS...>& operator+(const Precision<underlying_type_t<std::common_type_t<typename ARGS::ValueType...>>>& newPrecision) {
        precision.value = newPrecision.value;
        return *this;
    }
};

template<dense_vector_base T, dense_vector_base U>
DenseVectorCompareExpr<T, U> operator==(const T& a, const U& b) {
    return DenseVectorCompareExpr<T, U>(Precision(epsilon<underlying_type_t<std::common_type_t<typename T::ValueType, typename U::ValueType>>>()), a, b);
}
