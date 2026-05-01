#pragma once
#include "../../../helper.h"
#include <cstddef>
#include "../../../exceptions.h"
#include <cstring>

template<scalar T = float>
struct CooCustomSparseVector {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    CooCustomSparseVector() = delete;

    CooCustomSparseVector(const CooCustomSparseVector<T>& other) = delete;

    CooCustomSparseVector(CooCustomSparseVector<T>&& other) noexcept = delete;

    CooCustomSparseVector<T>& operator=(const CooCustomSparseVector<T>& other) = delete;

    CooCustomSparseVector<T>& operator=(CooCustomSparseVector<T>&& other) noexcept = delete;

    /**
     * @brief Constructs a CustomSparseMatrix of size 'n'.
     * Does not allocate any memory on the heap.
     * CustomSparseVector instance does not own 'values' or 'indices' pointer.
     * Think of it as a view on an arbitrary 'values' and 'indices' pointer.
     * @param n Number of vector elements.
     * @param values Reference to array containing non-zero elements of vector.
     * @param indices Reference to array containing indices of non-zero elements of vector.
     * @param nnz Reference to number of non-zero elements.
     * @note The array 'values' and 'indices' are pointing to may change.
     * @note Value of 'nnz' may change.
     */
    CooCustomSparseVector(const std::size_t n, T*& values, std::size_t*& indices, std::size_t& nnz) : nnz_(nnz), n_(n), values_(values), indices_(indices) {
    }

    void set(const std::size_t i, const T value)  {
        if (i > this->n_ - 1) {
            throw InvalidIndexException("Cannot set on CustomSparseVector with invalid index");
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

    [[nodiscard]] T get(const std::size_t i) const  {
        if (i > this->n_ - 1) {
            throw InvalidIndexException("Cannot get from CustomSparseVector with invalid index");
        }

        for (std::size_t j = 0; j < nnz_; j++) {
            if (indices_[j] == i) {
                return values_[j];
            }
        }

        return 0;
    }

    [[nodiscard]] std::size_t nnz() const  {
        return nnz_;
    }

    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    /**
     * @brief Gets the reference to the pointer storing the vectors non-zero elements.
     * @return Reference to pointer containing non-zero elements.
     */
    [[nodiscard]] T*& values() {
        return values_;
    }

    /**
    * @brief Gets the const reference to the const pointer storing the vectors non-zero elements.
    * @return Const reference to const pointer containing non-zero elements.
    */
    [[nodiscard]] const T* const& values() const {
        return values_;
    }

    /**
    * @brief Gets the reference to the pointer storing the indices of the vectors non-zero elements.
    * @return Reference to pointer containing the indices of the non-zero elements.
    */
    [[nodiscard]] std::size_t*& indices() {
        return indices_;
    }

    /**
    * @brief Gets the const reference to the const pointer storing the indices of the vectors non-zero elements.
    * @return Const reference to const pointer containing the indices of the non-zero elements.
    */
    [[nodiscard]] const std::size_t* const& indices() const {
        return indices_;
    }

    ~CooCustomSparseVector()  = default;

private:
    std::size_t& nnz_;
    std::size_t n_;

    T*& values_;
    std::size_t*& indices_;
};