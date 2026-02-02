#pragma once

#include "../../helper.h"

template<scalar T = float>
struct SparseVectorBase {
    const int n;

    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    SparseVectorBase() = delete;
    SparseVectorBase(const SparseVectorBase<T>& other) = delete;
    SparseVectorBase(SparseVectorBase<T>&& other) = delete;

protected:
    /**
     * @brief Initializes the size of the vector.
     *
     * Internal constructor that initializes the 'n' field.
     * Does not allocate memory for matrix elements.
     *
     * @param n Number of elements.
     */
    explicit SparseVectorBase(const int n) : n(n) {}

public:
    /**
     * @brief Sets the value of the element at index 'i'
     * @param i Index of element
     * @param value The value to set at index 'i'
     */
    virtual void set(int i, T value) = 0;

    /**
     * @brief Gets the value of the element at index 'i'
     * @param i Index of element
     * @return The value at index 'i'
     */
    [[nodiscard]] virtual T get(int i) const = 0;

    virtual ~SparseVectorBase() = default;
};

template<scalar T = float>
struct SparseVector : SparseVectorBase<T> {
    T* values = nullptr;
    int* indexes = nullptr;
    int nnz = 0;

    /**
     * @brief Constructs a SparseVector of size 'n'.
     *
     * Does not allocate memory yet.
     *
     * @param n Size of vector
     */
    explicit SparseVector(const int n) : SparseVectorBase<T>(n) {}

    /**
     * @brief Copy constructor for SparseVector
     *
     * Constructs a vector of size 'n' and performs a deep copy of 'other'.
     * Allocated 'nnz * sizeof(T) * 2' bytes of memory on the heap
     *
     * @param other SparseVector to copy from
     */
    SparseVector(const SparseVector<T>& other) : SparseVectorBase<T>(other.n), nnz(other.nnz) {
        values = new T[nnz];
        memcpy(values, other.values, nnz * sizeof(T));

        indexes = new T[nnz];
        memcpy(indexes, other.values, nnz * sizeof(T));
    }

    SparseVector(const SparseVectorBase<T>& other) : SparseVectorBase<T>(other.n) {
        for (int i = 0; i < this->n; i++) {
            SparseVector<T>::set(i, other.get(i));
        }
    }

    SparseVector(SparseVector<T>&& other) noexcept : SparseVectorBase<T>(other.n), values(other.values), indexes(other.indexes), nnz(other.nnz) {
        other.indexes = nullptr;
        other.values = nullptr;
    }

    void set(const int i, const T value) override {
        int j;

        for (j = 0; j < nnz; j++) {
            const int curIndex = indexes[j];

            if (curIndex == i) {
                // there is currently a non-zero element there and we are placing a zero so we remove a non-zero element;
                if (compare(value, 0)) {
                    T* newValues = new T[nnz - 1];

                    // copy everything before us
                    memcpy(newValues, values, j * sizeof(T));

                    // copy everything after us but 1 back
                    memcpy(&newValues[j], &values[j + 1], (nnz - j - 1) * sizeof(T));

                    // delete old array
                    delete[] values;

                    // and set the new array
                    values = newValues;

                    int* newIndices = new int[nnz - 1];

                    memcpy(newIndices, indexes, j * sizeof(T));

                    memcpy(&newIndices[j], &values[j + 1], (nnz - j - 1) * sizeof(T));

                    delete[] indexes;

                    indexes = newIndices;

                    nnz--;

                    return;
                }

                // there is a non-zero element and we are setting another non-zero element, indices do not need to change
                values[j] = value;

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

        T* newValues = new T[nnz + 1];

        // copy everything up to j
        memcpy(newValues, values, j * sizeof(T));

        // set the new value
        newValues[j] = value;

        // copy everything after j
        memcpy(&newValues[j + 1], &values[j], (nnz - j) * sizeof(T));

        delete[] values;

        values = newValues;

        int* newIndices = new int[nnz + 1];

        memcpy(newIndices, indexes, j * sizeof(T));

        memcpy(&newIndices[j + 1], &values[j], (nnz - j) * sizeof(T));

        delete[] indexes;

        indexes = newIndices;

        nnz++;
    }

    [[nodiscard]] T get(const int i) const override {
        for (int j = 0; j < nnz; j++) {
            const int curIndex = indexes[j];

            if (curIndex == i)
                return values[j];
        }

        return 0;
    }

    ~SparseVector() override = default;
};

template<scalar T = float>
struct SparseVectorView : SparseVectorBase<T> {
    SparseVector<T>& owner;

    SparseVectorView() = delete;

    SparseVectorView(SparseVectorView<T>&& other) noexcept = delete;

    /**
     * @brief Copy constructor for SparseVectorView
     *
     * Constructs a view with the same 'owner' as 'other'.
     * Does not allocate new memory.
     *
     * @param other SparseVectorView to copy from
     */
    SparseVectorView(const SparseVectorView<T>& other) : SparseVectorBase<T>(other.n), owner(other.owner), offset_(other.offset_) {}

    /**
     * @brief Constructs a SparseVectorView into an existing SparseVector.
     *
     * Creates a view of size `n` into the `owner` vector,
     * starting at 'offset'.
     * Does not allocate new memory.
     * The view holds a reference to the 'owner'.
     *
     * @param owner SparseVector to create a view from.
     * @param n Number of elements in the view.
     * @param offset Starting element offset into the 'owner' vector.
     */
    SparseVectorView(SparseVector<T>& owner, const int n, const int offset) : SparseVectorBase<T>(n), owner(owner),offset_(offset) {}

    void set(const int i, const T value) override {
        owner.set(i + offset_,value);
    }

    [[nodiscard]] T get(const int i) const override {
        return owner.get(i + offset_);
    }

    ~SparseVectorView() override = default;

private:
    const int offset_;
};

template<scalar T = float>
struct CustomSparseVector : SparseVectorBase<T> {

};
