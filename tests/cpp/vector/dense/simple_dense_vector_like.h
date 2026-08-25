#ifndef MATHPP_TESTS_SIMPLE_DENSE_VECTOR_LIKE_H
#define MATHPP_TESTS_SIMPLE_DENSE_VECTOR_LIKE_H

#include <cstddef>
#include <initializer_list>
#include "mathpp/implementation/common/traits.h"

template<typename T>
struct SimpleDenseVectorLike {
    using ValueType = T;
    static constexpr bool isComplex = is_complex_v<T>;

    std::size_t n_;
    T* data_;

    SimpleDenseVectorLike(std::initializer_list<T> data) : n_(data.size()), data_(new T[n_]) {


        std::size_t i = 0;
        for (T element : data) {
            data_[i] = element;
            ++i;
        }
    }

    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    [[nodiscard]] T get(const std::size_t i) const {
        return data_[i];
    }

    void set(const std::size_t i, T v) {
        data_[i] = v;
    }

    [[nodiscard]] const T& operator[](const std::size_t i) const {
        return data_[i];
    }

    [[nodiscard]] T& operator[](const std::size_t i) {
        return data_[i];
    }
};

#endif // MATHPP_TESTS_SIMPLE_DENSE_VECTOR_LIKE_H
