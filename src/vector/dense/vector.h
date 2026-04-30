#pragma once
#include <initializer_list>

#include "helper.h"

#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T = float>
struct DenseVector {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    DenseVector() = delete;

    /**
     * @brief Constructs a DenseVector of size 'n'.
     * Allocates 'n * sizeof(T)' bytes of memory on the heap.
     * Optionally fills all elements with zero.
     * @param n Number of elements.
     * @param fill If true, initializes all elements to zero; otherwise leaves elements uninitialized.
     */
    DenseVector(const std::size_t n, const bool fill = true) : n_(n), data_(fill ? new T[n_]() : new T[n_]) {

    }

    /**
    * @brief Constructs a DenseVector from an initializer list of size 'initializerList.size()'.
    *
    * Allocates 'n * sizeof(T)' bytes on the heap.
    *
    * @param initializerList Initializer_list representing vector elements.
    */
    DenseVector(const std::initializer_list<T>& initializerList) : n_(initializerList.size()), data_(new T[n_]) {
        std::size_t i = 0;
        for (const T element: initializerList) {
            data_[i] = element;
            i++;
        }
    }

    /**
     * @brief Copy constructor for DenseVector from same type DenseVector.
     *
     * Constructs a vector of size 'n' and performs a deep copy of 'other'.
     * Allocates 'n * sizeof(T)' bytes on the heap.
     *
     * @param other DenseVector to copy from.
     */
    DenseVector(const DenseVector<T>& other) : n_(other.n_), data_(new T[n_]) {
        memcpy(data_, other.data_, this->n_ * sizeof(T));
    }

    /**
    * @brief Copy constructor for DenseVector from different type DenseVector.
    *
    * Constructs a vector of size 'n' and performs a deep copy of 'other'.
    * Allocates 'n * sizeof(T)' bytes on the heap.
    *
    * @param other DenseVector to copy from.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    * @tparam OTHER_T Scalar type of the 'other' DenseMatrix.
    */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    DenseVector(const DenseVector<OTHER_T>& other) : n_(other.n()), data_(new T[n_]) {
        const OTHER_T* otherData = other.data();

        for (std::size_t i = 0; i < this->n_; i++) {
            data_[i] = otherData[i];
        }
    }


    template<dense_vector_like U>
    DenseVector(const U& other) : n_(other.n()), data_(new T[n_]) {
        for (std::size_t i = 0; i < this->n_; i++) {
            data_[i] = other[i];
        }
    }

    /**
     * @brief Move constructor for DenseVector.
     *
     * Constructs a vector of size 'other.n' and performs a move from 'other'.
     * Does not allocate any memory on the heap.
     *
     * @param other DenseVector to move from.
     */
    DenseVector(DenseVector<T>&& other) noexcept : n_(other.n_), data_(other.data_) {
        other.data_ = nullptr;
        other.n_ = 0;
    }

    /**
     * @brief Copy assignment operator for DenseVector from same type DenseVector.
     * Replaces all elements with elements of 'other'.
     * Does not allocate memory on the heap.
     * @param other DenseVector to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same size as this.
     * @note 'other' must be of same size as this.
     */
    DenseVector<T>& operator=(const DenseVector<T>& other) {
        if (this != &other) {
            if (this->n_ != other.n_) {
                this->n_ = other.n_;
                delete[] data_;
                data_ = new T[this->n_];
            }

            memcpy(data_, other.data_, this->n_ * sizeof(T));
        }

        return *this;
    }

    /**
    * @brief Copy assignment operator for DenseVector from different type DenseVector.
    * Replaces all elements with elements of 'other'.
    * Does not allocate memory on the heap.
    * @param other DenseVector to copy from.
    * @return Reference to this.
    * @throws InvalidDimensionException If 'other' does not have same size as this.
    * @note 'other' must be of same size as this.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    * @tparam OTHER_T Scalar type of the 'other' DenseVector.
    */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    DenseVector<T>& operator=(const DenseVector<OTHER_T>& other) {
        if (this->n_ != other.n()) {
            this->n_ = other.n();
            delete[] data_;
            data_ = new T[this->n_];
        }

        const OTHER_T* otherData = other.data();

        for (std::size_t i = 0; i < this->n_; i++) {
            data_[i] = otherData[i];
        }

        return *this;
    }

    template<dense_vector_like U>
    DenseVector<T>& operator=(const U& other) {
        if (this->n_ != other.n()) {
            this->n_ = other.n();
            delete[] data_;
            data_ = new T[this->n_];
        }

        for (std::size_t i = 0; i < this->n_; i++) {
            data_[i] = other[i];
        }

        return *this;
    }

    /**
     * @brief Move assignment operator for DenseVector from same type DenseVector.
     * Takes ownership of 'other' data.
     * Does not allocate memory on the heap.
     * @param other DenseVector to move from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same size as this.
     * @note 'other' must be of same size as this.
     */
    DenseVector<T>& operator=(DenseVector<T>&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            other.data_ = nullptr;

            this->n_ = other.n_;
            other.n_ = 0;
        }

        return *this;
    }

    [[nodiscard]] T& at(std::size_t i) {
        return data_[i];
    }

    [[nodiscard]] const T& at(std::size_t i) const {
        return data_[i];
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

    ~DenseVector() {
        delete[] data_;
    }

private:
    std::size_t n_;

    T* data_;
};
