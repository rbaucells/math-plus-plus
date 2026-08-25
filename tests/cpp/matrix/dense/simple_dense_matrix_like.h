#ifndef MATHPP_TESTS_SIMPLE_DENSE_MATRIX_LIKE_H
#define MATHPP_TESTS_SIMPLE_DENSE_MATRIX_LIKE_H

#include <cstddef>
#include <initializer_list>
#include "mathpp/implementation/common/traits.h"

template<typename T>
struct SimpleDenseMatrixLike {
    using ValueType = T;
    static constexpr bool isComplex = is_complex_v<T>;

    std::size_t rows_;
    std::size_t columns_;
    T* data_;

    SimpleDenseMatrixLike(std::initializer_list<std::initializer_list<T>> data) : rows_(data.size()), columns_(data.begin()->size()), data_(new T[rows_ * columns_]) {
        std::size_t r = 0;
        for (auto row : data) {

            std::size_t c = 0;
            for (T element : row) {
                (*this)[r, c] = element;
                ++c;
            }
            ++r;
        }
    }

    [[nodiscard]] std::size_t rows() const {
        return rows_;
    }
    [[nodiscard]] std::size_t columns() const {
        return columns_;
    }

    [[nodiscard]] T get(const std::size_t r, const std::size_t c) const {
        return data_[c * rows_ + r];
    }

    void set(const std::size_t r, const std::size_t c, T v) {
        data_[c * rows_ + r] = v;
    }

    [[nodiscard]] const T& operator[](const std::size_t r, const std::size_t c) const {
        return data_[c * rows_ + r];
    }

    [[nodiscard]] T& operator[](const std::size_t r, const std::size_t c) {
        return data_[c * rows_ + r];
    }
};

#endif // MATHPP_TESTS_SIMPLE_DENSE_MATRIX_LIKE_H
