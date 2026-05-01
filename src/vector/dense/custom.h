#pragma once
#include "../../helper.h"
#include <cstddef>
#include "../../exceptions.h"

template<scalar T = float>
struct CustomDenseVector {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    CustomDenseVector() = delete;

    CustomDenseVector(const CustomDenseVector<T>& other) = delete;

    CustomDenseVector(CustomDenseVector<T>&& other) noexcept = delete;

    CustomDenseVector<T>& operator=(const CustomDenseVector<T>& other) = delete;

    CustomDenseVector<T>& operator=(CustomDenseVector<T>&& other) noexcept = delete;

    /**
     * @brief Constructs a CustomDenseVector of size 'n'.
     * Does not allocate any memory on the heap.
     * CustomDenseMatrix instance does not own 'data' pointer.
     * Think of it as a view on an arbitrary 'data' pointer.
     * @param data Flat 1d array containing all vector elements.
     * @param n Number of elements in vector.
     * @param stride How many elements to skip when accessing elements.
     * @note Length of 'data' array must be greater than '(n - 1) x stride'.
     */
    CustomDenseVector(T* data, const std::size_t n, const std::size_t stride) : stride_(stride), n_(n), data_(data) {
    }

    [[nodiscard]] T& at(const std::size_t i) {
        return data_[i * stride_];
    }

    [[nodiscard]] const T& at(const std::size_t i) const {
        return data_[i * stride_];
    }

    [[nodiscard]] T& operator[](const std::size_t i) {
        if (i >= n_) {
            throw InvalidIndexException("Cannot access vector at invalid index");
        }

        return at(i);
    }

    [[nodiscard]] const T& operator[](const std::size_t i) const {
        if (i >= n_) {
            throw InvalidIndexException("Cannot access vector at invalid index");
        }

        return at(i);
    }

    /**
     * @brief Gets the stride or how far to jump between elements.
     * @return The stride.
     */
    [[nodiscard]] std::size_t stride() const {
        return stride_;
    }

    /**
    * @brief Gets the data pointer storing the vectors elements.
    * @return Pointer to array of elements.
    */
    [[nodiscard]] T* data() {
        return data_;
    }

    /**
    * @brief Gets the const data pointer storing the vectors elements.
    * @return Const pointer to array of elements.
    */
    [[nodiscard]] const T* data() const {
        return data_;
    }

    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    ~CustomDenseVector() = default;

private:
    const std::size_t stride_;
    std::size_t n_;

    T* const data_;
};