#pragma once
#include "../../../helper.h"
#include <cstddef>
#include "../../../exceptions.h"
#include <initializer_list>
#include <tuple>
#include <cstring>
#include "helper.h"

template<scalar T = float>
struct DokSparseVector {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    DokSparseVector() = delete;

    /**
     * @brief Constructs a SparseVector of size 'n'.
     *
     * Does not allocate memory yet.
     *
     * @param n Size of vector.
     */
    explicit DokSparseVector(const std::size_t n) : nnz_(0), n_(n), values_(new T[0]), indices_(new std::size_t[0]) {
    }

    /**
     * @brief Constructs a SparseVector of size 'n' with elements 'initializerList'.
     * Allocates 'initializerList.size() x sizeof(T) + initializerList.size() x sizeof(std::size_t)' bytes of memory on the heap.
     * @param n Size of vector.
     * @param initializerList Initializer list of T, std::size_t tuples. Representing value and index.
     *
     * @note 'initializerList' must be sorted in increasing indices.
     */
    DokSparseVector(const std::size_t n, std::initializer_list<std::tuple<T, int>> initializerList) : nnz_(initializerList.size()), n_(n), values_(new T[nnz_]), indices_(new std::size_t[nnz_]) {
        if (n < 0) {
            throw InvalidIndexException("Cannot construct SparseVector of negative size");
        }

        std::size_t i = 0;
        for (const auto& nonZeroElement: initializerList) {
            values_[i] = std::get<0>(nonZeroElement);
            indices_[i] = std::get<1>(nonZeroElement);
            ++i;
        }
    }

    /**
     * @brief Copy constructor for SparseVector from same type SparseVector.
     *
     * Constructs a vector of size 'n' and performs a deep copy of 'other'.
     * Allocated 'nnz * sizeof(T) + nnz * sizeof(std::size_t)' bytes of memory on the heap.
     *
     * @param other SparseVector to copy from.
     */
    DokSparseVector(const DokSparseVector<T>& other) : n_(other.n_), nnz_(other.nnz_), values_(other.values_), indices_(other.indices_) {
        std::memcpy(values_, other.values_, nnz_ * sizeof(T));
        std::memcpy(indices_, other.indices_, nnz_ * sizeof(std::size_t));
    }

    /**
    * @brief Copy constructor for SparseVector from different type SparseVector.
    *
    * Constructs a vector of size 'n' and performs a deep copy of 'other'.
    * Allocates 'nnz * sizeof(T) + nnz * sizeof(std::size_t)' bytes on the heap.
    *
    * @param other SparseVector to copy from.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    * @tparam OTHER_T Scalar type of the 'other' SparseVector.
    */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    DokSparseVector(const DokSparseVector<OTHER_T>& other) : n_(other.n()), nnz_(other.nnz()), values_(new T[nnz_]), indices_(new std::size_t[nnz_]) {
        const OTHER_T* otherValues = other.values();

        for (std::size_t i = 0; i < nnz_; i++) {
            values_[i] = otherValues[i];
        }

        std::memcpy(indices_, other.indices(), nnz_ * sizeof(std::size_t));
    }

    template<sparse_vector_like U>
    DokSparseVector(const U& other) : nnz_(0), n_(other.n()), values_(new T[nnz_]), indices_(new std::size_t[nnz_]) {
        for (std::size_t i = 0; i < this->n_; i++) {
            DokSparseVector<T>::set(i, other.get(i));
        }
    }

    /**
     * @brief Move constructor for SparseVector.
     *
     * Constructs a vector of size 'other.n' and performs a move from 'other'.
     * Does not allocate any memory on the heap.
     *
     * @param other SparseVector to move from.
     */
    DokSparseVector(DokSparseVector<T>&& other) noexcept : nnz_(other.nnz_), n_(other.n_), values_(other.values_), indices_(other.indices_) {
        other.values_ = nullptr;
        other.indices_ = nullptr;
        other.n_ = 0;
        other.nnz_ = 0;
    }

    /**
     * @brief Copy assignment operator for SparseVector from same type SparseVector.
     * Replaces all elements with elements of 'other'.
     * May allocate 'other.nnz * sizeof(T) + other.nnz * sizeof(std::size_t)' bytes of memory on the heap if number of non-zero elements here doesn't match number of non-zero elements in 'other'.
     * @param other SparseVector to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same size as this.
     * @note 'other' must be of same size as this.
     */
    DokSparseVector<T>& operator=(const DokSparseVector<T>& other) {
        if (this != &other) {
            if (nnz_ != other.nnz_) {
                nnz_ = other.nnz_;

                delete[] values_;
                values_ = new T[nnz_];

                delete[] indices_;
                indices_ = new std::size_t[nnz_];
            }

            this->n_ = other.n_;

            std::memcpy(values_, other.values_, nnz_ * sizeof(T));
            std::memcpy(indices_, other.indices_, nnz_ * sizeof(std::size_t));
        }

        return *this;
    }

    /**
     * @brief Copy assignment operator for SparseVector from different type SparseVector.
     * Replaces all elements with elements of 'other'.
     * May allocate 'other.nnz * sizeof(T) + other.nnz * sizeof(std::size_t)' bytes of memory on the heap if number of non-zero elements here doesn't match number of non-zero elements in 'other'.
     * @param other SparseVector to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same size as this.
     * @note 'other' must be of same size as this.
     * @note 'OTHER_T' must be able to implicitly convert to 'T'.
     * @tparam OTHER_T Scalar type of the 'other' DenseVector.
     */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    DokSparseVector<T>& operator=(const DokSparseVector<OTHER_T>& other) {
        if (nnz_ != other.nnz()) {
            nnz_ = other.nnz();

            delete[] values_;
            values_ = new T[nnz_];

            delete[] indices_;
            indices_ = new std::size_t[nnz_];
        }

        this->n_ = other.n();

        const OTHER_T* otherValues = other.values();

        for (std::size_t i = 0; i < nnz_; i++) {
            values_[i] = otherValues[i];
        }

        std::memcpy(indices(), other.indices(), nnz_ * sizeof(std::size_t));

        return *this;
    }

    template<sparse_vector_like U>
    DokSparseVector<T>& operator=(const U& other) {
        this->nnz_ = 0;
        this->n_ = other.n();

        for (std::size_t i = 0; i < this->n_; i++) {
            DokSparseVector<T>::set(i, other.get(i));
        }

        return *this;
    }

    /**
    * @brief Move assignment operator for SparseVector from same type SparseVector.
    * Takes ownership of 'other' data.
    * Does not allocate memory on the heap.
    * @param other SparseVector to move from.
    * @return Reference to this.
    * @throws InvalidDimensionException If 'other' does not have same size as this.
    * @note 'other' must be of same size as this.
    */
    DokSparseVector<T>& operator=(DokSparseVector<T>&& other) noexcept {
        if (this != &other) {
            delete[] values_;
            values_ = other.values_;
            other.values_ = nullptr;

            delete[] indices_;
            indices_ = other.indices_;
            other.indices_ = nullptr;

            nnz_ = other.nnz_;
            other.nnz_ = 0;

            this->n_ = other.n_;
            other.n_ = 0;
        }

        return *this;
    }

    void set(const std::size_t i, const T value) {
        if (i > this->n_ - 1) {
            throw InvalidIndexException("Cannot set on SparseVector with invalid index");
        }
        std::size_t j;

        for (j = 0; j < nnz_; j++) {
            const std::size_t curIndex = indices_[j];

            if (curIndex == i) {
                // there is currently a non-zero element there, and we are placing a zero so we remove a non-zero element;
                if (compare(value, 0)) {
                    T* newValues = new T[nnz_ - 1];

                    // copy everything before us
                    std::memcpy(newValues, values_, j * sizeof(T));

                    // copy everything after us but 1 back
                    std::memcpy(&newValues[j], &values_[j + 1], (nnz_ - j - 1) * sizeof(T));

                    // delete old array
                    delete[] values_;

                    // and set the new array
                    values_ = newValues;

                    std::size_t* newIndices = new std::size_t[nnz_ - 1];

                    std::memcpy(newIndices, indices_, j * sizeof(std::size_t));

                    std::memcpy(&newIndices[j], &indices_[j + 1], (nnz_ - j - 1) * sizeof(std::size_t));

                    delete[] indices_;

                    indices_ = newIndices;

                    nnz_--;

                    return;
                }

                // there is a non-zero element, and we are setting another non-zero element, indices do not need to change
                values_[j] = value;

                return;
            }

            // arrays are sorted, no reason to keep iterating
            if (curIndex > i) {
                break;
            }
        }

        // there is currently a zero element, and we are setting another zero element
        if (compare(value, 0)) {
            return;
        }

        T* newValues = new T[nnz_ + 1];

        // copy everything up to j
        std::memcpy(newValues, values_, j * sizeof(T));

        // set the new value
        newValues[j] = value;

        // copy everything after j
        std::memcpy(&newValues[j + 1], &values_[j], (nnz_ - j) * sizeof(T));

        delete[] values_;

        values_ = newValues;

        std::size_t* newIndices = new std::size_t[nnz_ + 1];

        std::memcpy(newIndices, indices_, j * sizeof(std::size_t));

        newIndices[j] = i;

        std::memcpy(&newIndices[j + 1], &indices_[j], (nnz_ - j) * sizeof(std::size_t));

        delete[] indices_;

        indices_ = newIndices;

        nnz_++;
    }

    [[nodiscard]] T get(const std::size_t i) const {
        if (i > this->n_ - 1) {
            throw InvalidIndexException("Cannot get from SparseVector with invalid index");
        }

        for (std::size_t j = 0; j < nnz_; j++) {
            if (indices_[j] == i) {
                return values_[j];
            }
        }

        return 0;
    }

    [[nodiscard]] std::size_t nnz() const {
        return nnz_;
    }

    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    /**
     * @brief Gets the data pointer storing the vectors non-zero elements.
     * @return Pointer to array of non-zero elements.
     */
    [[nodiscard]] T* values() {
        return values_;
    }

    /**
     * @brief Gets the const data pointer storing the vectors non-zero elements.
     * @return Const pointer to array of non-zero elements.
     */
    [[nodiscard]] const T* values() const {
        return values_;
    }

    /**
     * @brief Gets the indices pointer storing the indices for the vectors non-zero elements.
     * @return Pointer to array of indices of non-zero elements.
     */
    [[nodiscard]] std::size_t* indices() {
        return indices_;
    }

    /**
     * @brief Gets the const indices pointer storing the indices for the vectors non-zero elements.
     * @return Const pointer to array of indices of non-zero elements.
     */
    [[nodiscard]] const std::size_t* indices() const {
        return indices_;
    }

    ~DokSparseVector() = default;

private:
    std::size_t nnz_;
    std::size_t n_;

    T* values_;
    std::size_t* indices_;
};
