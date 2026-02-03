#pragma once

#include "../../exceptions.h"
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

    [[nodiscard]] virtual int nnz() const = 0;

    virtual ~SparseVectorBase() = default;
};

template<scalar T = float>
struct SparseVector : SparseVectorBase<T> {
    /**
     * @brief Constructs a SparseVector of size 'n'.
     *
     * Does not allocate memory yet.
     *
     * @param n Size of vector.
     */
    explicit SparseVector(const int n) : SparseVectorBase<T>(n) {
        nnz_ = 0;
        values_ = new T[nnz_];
        indexes_ = new T[nnz_];
    }

    /**
     * @brief Copy constructor for SparseVector.
     *
     * Constructs a vector of size 'n' and performs a deep copy of 'other'.
     * Allocated 'nnz * sizeof(T) * 2' bytes of memory on the heap.
     *
     * @param other SparseVector to copy from.
     */
    SparseVector(const SparseVector<T>& other) : SparseVectorBase<T>(other.n), nnz_(other.nnz_) {
        values_ = new T[nnz_];
        memcpy(values_, other.values_, nnz_ * sizeof(T));

        indexes_ = new T[nnz_];
        memcpy(indexes_, other.values_, nnz_ * sizeof(T));
    }

    SparseVector(const SparseVectorBase<T>& other) : SparseVectorBase<T>(other.n) {
        for (int i = 0; i < this->n; i++) {
            SparseVector<T>::set(i, other.get(i));
        }
    }

    SparseVector(SparseVector<T>&& other) noexcept : SparseVectorBase<T>(other.n), values_(other.values_), indexes_(other.indexes_), nnz_(other.nnz_) {
        other.indexes_ = nullptr;
        other.values_ = nullptr;
    }

    void set(const int i, const T value) override {
        int j;

        for (j = 0; j < nnz_; j++) {
            const int curIndex = indexes_[j];

            if (curIndex == i) {
                // there is currently a non-zero element there and we are placing a zero so we remove a non-zero element;
                if (compare(value, 0)) {
                    T* newValues = new T[nnz_ - 1];

                    // copy everything before us
                    memcpy(newValues, values_, j * sizeof(T));

                    // copy everything after us but 1 back
                    memcpy(&newValues[j], &values_[j + 1], (nnz_ - j - 1) * sizeof(T));

                    // delete old array
                    delete[] values_;

                    // and set the new array
                    values_ = newValues;

                    int* newIndices = new int[nnz_ - 1];

                    memcpy(newIndices, indexes_, j * sizeof(T));

                    memcpy(&newIndices[j], &values_[j + 1], (nnz_ - j - 1) * sizeof(T));

                    delete[] indexes_;

                    indexes_ = newIndices;

                    nnz_--;

                    return;
                }

                // there is a non-zero element and we are setting another non-zero element, indices do not need to change
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
        memcpy(newValues, values_, j * sizeof(T));

        // set the new value
        newValues[j] = value;

        // copy everything after j
        memcpy(&newValues[j + 1], &values_[j], (nnz_ - j) * sizeof(T));

        delete[] values_;

        values_ = newValues;

        int* newIndices = new int[nnz_ + 1];

        memcpy(newIndices, indexes_, j * sizeof(T));

        memcpy(&newIndices[j + 1], &values_[j], (nnz_ - j) * sizeof(T));

        delete[] indexes_;

        indexes_ = newIndices;

        nnz_++;
    }

    [[nodiscard]] T get(const int i) const override {
        for (int j = 0; j < nnz_; j++) {
            const int curIndex = indexes_[j];

            if (curIndex == i)
                return values_[j];
        }

        return 0;
    }

    [[nodiscard]] int nnz() const override {
        return nnz_;
    }

    [[nodiscard]] T* values() {
        return values_;
    }

    [[nodiscard]] const T* values() const {
        return values_;
    }

    [[nodiscard]] int* indexes() {
        return indexes_;
    }

    [[nodiscard]] const int* indexes() const {
        return indexes_;
    }

    ~SparseVector() override = default;

private:
    T* values_;
    int* indexes_;
    int nnz_;
};

template<scalar T = float>
struct SparseVectorView : SparseVectorBase<T> {
    SparseVectorView() = delete;

    SparseVectorView(SparseVectorView<T>&& other) noexcept = delete;

    /**
     * @brief Copy constructor for SparseVectorView.
     *
     * Constructs a view with the same 'owner' as 'other'.
     * Does not allocate new memory.
     *
     * @param other SparseVectorView to copy from.
     */
    SparseVectorView(const SparseVectorView<T>& other) : SparseVectorBase<T>(other.n), owner_(other.owner_), offset_(other.offset_) {}

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
    SparseVectorView(SparseVector<T>& owner, const int n, const int offset) : SparseVectorBase<T>(n), owner_(owner), offset_(offset) {}

    /**
     * @throws InvalidOperation You cannot modify owner through a view.
     */
    void set(const int, const T) override {
        throw InvalidOperation("Cannot modify owner through view");
    }

    [[nodiscard]] T get(const int i) const override {
        return owner_.get(i + offset_);
    }

    [[nodiscard]] const SparseVector<T>& owner() const {
        return owner_;
    }

    [[nodiscard]] int nnz() const override {
        int nnz = 0;

        for (int i = 0; i < owner_.nnz(); i++) {
            const int curIndex = owner_.indexes()[i];

            if (curIndex >= offset_ && curIndex < offset_ + this->n) {
                nnz++;
            }
        }

        return nnz;
    }

    [[nodiscard]] int offset() const {
        return offset_;
    }

    ~SparseVectorView() override = default;

private:
    const int offset_;

    const SparseVector<T>& owner_;
};

template<scalar T = float>
struct CustomSparseVector : SparseVectorBase<T> {
    CustomSparseVector() = delete;
    CustomSparseVector(const CustomSparseVector<T>& other) = delete;
    CustomSparseVector(CustomSparseVector<T>&& other) noexcept = delete;

    CustomSparseVector(const int n, T* values, int* indexes, const int nnz) : SparseVectorBase<T>(n), values_(values), indexes_(indexes), nnz_(nnz) {}

    void set(int i, T value) override {
        int j;

        for (j = 0; j < nnz_; j++) {
            const int curIndex = indexes_[j];

            if (curIndex == i) {
                // there is currently a non-zero element there and we are placing a zero so we remove a non-zero element;
                if (compare(value, 0)) {
                    T* newValues = new T[nnz_ - 1];

                    // copy everything before us
                    memcpy(newValues, values_, j * sizeof(T));

                    // copy everything after us but 1 back
                    memcpy(&newValues[j], &values_[j + 1], (nnz_ - j - 1) * sizeof(T));

                    // delete old array
                    delete[] values_;

                    // and set the new array
                    values_ = newValues;

                    int* newIndices = new int[nnz_ - 1];

                    memcpy(newIndices, indexes_, j * sizeof(T));

                    memcpy(&newIndices[j], &values_[j + 1], (nnz_ - j - 1) * sizeof(T));

                    delete[] indexes_;

                    indexes_ = newIndices;

                    nnz_--;

                    return;
                }

                // there is a non-zero element and we are setting another non-zero element, indices do not need to change
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
        memcpy(newValues, values_, j * sizeof(T));

        // set the new value
        newValues[j] = value;

        // copy everything after j
        memcpy(&newValues[j + 1], &values_[j], (nnz_ - j) * sizeof(T));

        delete[] values_;

        values_ = newValues;

        int* newIndices = new int[nnz_ + 1];

        memcpy(newIndices, indexes_, j * sizeof(T));

        memcpy(&newIndices[j + 1], &values_[j], (nnz_ - j) * sizeof(T));

        delete[] indexes_;

        indexes_ = newIndices;

        nnz_++;
    }

    [[nodiscard]] T get(int i) const override {
        for (int j = 0; j < nnz_; j++) {
            const int curIndex = indexes_[j];

            if (curIndex == i)
                return values_[j];
        }

        return 0;
    }

    [[nodiscard]] int nnz() const override {
        return nnz_;
    }

    [[nodiscard]] T* values() {
        return values_;
    }

    [[nodiscard]] const T* values() const {
        return values_;
    }

    [[nodiscard]] int* indexes() {
        return indexes_;
    }

    [[nodiscard]] const int* indexes() const {
        return indexes_;
    }

private:
    T* values_;
    int* indexes_;
    int nnz_;
};
