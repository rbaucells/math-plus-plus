#pragma once
#include "../../helper.h"
#include <cstddef>
#include "../../exceptions.h"

template<scalar T = float>
struct CustomDenseMatrix {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    CustomDenseMatrix() = delete;

    CustomDenseMatrix(const CustomDenseMatrix<T>& other) = delete;

    CustomDenseMatrix(CustomDenseMatrix<T>&& other) noexcept = delete;

    CustomDenseMatrix<T>& operator=(const CustomDenseMatrix<T>& other) = delete;

    CustomDenseMatrix<T>& operator=(CustomDenseMatrix<T>&& other) noexcept = delete;

    /**
     * @brief Constructs a CustomDenseMatrix of size 'rows x columns'.
     *
     * Does not allocate any memory on the heap.
     * CustomDenseMatrix instance does not own 'data' pointer.
     * Think of it as a view on an arbitrary 'data' pointer.
     *
     * @param data Flat 1d array containing all matrix elements in column major ordering.
     * @param rows Number of rows in matrix.
     * @param columns Number of columns in matrix.
     * @param stride How many elements to skip when accessing elements.
     *
     * @note Length of 'data' array must be greater than '(columns - 1) x stride + (rows - 1)'.
     * @note 'data' array must be in column major ordering.
     */
    CustomDenseMatrix(T* data, const std::size_t rows, const std::size_t columns, const std::size_t stride) : rows_(rows), columns_(columns), stride_(stride), data_(data) {
    }

    [[nodiscard]] T& at(const std::size_t r, const std::size_t c) {
        return data_[c * stride_ + r];
    }

    [[nodiscard]] const T& at(const std::size_t r, const std::size_t c) const {
        return data_[c * stride_ + r];
    }

    [[nodiscard]] T& operator[](const std::size_t r, const std::size_t c) {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return at(r, c);
    }

    [[nodiscard]] const T& operator[](const std::size_t r, const std::size_t c) const {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return at(r, c);
    }

    /**
     * @brief Gets the stride or how far to jump between elements.
     * @return The stride.
     */
    [[nodiscard]] std::size_t stride() const {
        return stride_;
    }

    [[nodiscard]] std::size_t rows() const {
        return rows_;
    }

    [[nodiscard]] std::size_t columns() const {
        return columns_;
    }

    /**
     * @brief Gets the data pointer storing the matrices elements.
     * @return Pointer to array of elements.
     */
    [[nodiscard]] T* data() {
        return data_;
    }

    /**
     * @brief Gets the const data pointer storing the matrices elements.
     * @return Const pointer to array of elements.
     */
    [[nodiscard]] const T* data() const {
        return data_;
    }

    ~CustomDenseMatrix() = default;

private:
    std::size_t rows_;
    std::size_t columns_;
    const std::size_t stride_;

    T* const data_;
};