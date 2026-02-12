#pragma once

#include "../../exceptions.h"
#include "../../helper.h"

#include "helper.h"

template<scalar T = float>
struct SparseVectorBase {
    const int n;

    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

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

    /**
    * @brief Gets the number of non-zero elements in the sparse vector.
    * @return Number of non-zero elements.
    */
    [[nodiscard]] virtual int nnz() const = 0;

    virtual ~SparseVectorBase() = default;
};

template<scalar T = float>
struct SparseVector : SparseVectorBase<T> {
    SparseVector() = delete;

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
        indexes_ = new int[nnz_];
    }

    /**
     * @brief Copy constructor for SparseVector from same type SparseVector.
     *
     * Constructs a vector of size 'n' and performs a deep copy of 'other'.
     * Allocated 'nnz * sizeof(T) + nnz * sizeof(int)' bytes of memory on the heap.
     *
     * @param other SparseVector to copy from.
     */
    SparseVector(const SparseVector<T>& other) : SparseVectorBase<T>(other.n), nnz_(other.nnz_) {
        values_ = new T[nnz_];
        memcpy(values_, other.values_, nnz_ * sizeof(T));

        indexes_ = new int[nnz_];
        memcpy(indexes_, other.indexes_, nnz_ * sizeof(int));
    }

    /**
    * @brief Copy constructor for SparseVector from different type SparseVector.
    *
    * Constructs a vector of size 'n' and performs a deep copy of 'other'.
    * Allocates 'nnz * sizeof(T) + nnz * sizeof(int)' bytes on the heap.
    *
    * @param other SparseVector to copy from.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    * @tparam OTHER_T Scalar type of the 'other' SparseVector.
    */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    SparseVector(const SparseVector<OTHER_T>& other) : SparseVectorBase<T>(other.n), nnz_(other.nnz()) {
        values_ = new T[nnz_];

        const OTHER_T* otherValues = other.values();

        for (int i = 0; i < nnz_; i++) {
            values_[i] = otherValues[i];
        }

        indexes_ = new int[nnz_];

        const int* otherIndexes = other.indexes();

        memcpy(indexes_, otherIndexes, nnz_ * sizeof(int));
    }

    /**
    * @brief Copy constructor for SparseVector from same type SparseVectorBase.
    *
    * Constructs a vector of size 'n' and performs a deep copy of 'other'.
    * Allocates 'nnz * sizeof(T) + nnz * sizeof(int)' bytes on the heap.
    *
    * @param other SparseVectorBase to copy from.
    */
    SparseVector(const SparseVectorBase<T>& other) : SparseVectorBase<T>(other.n) {
        nnz_ = 0;
        values_ = new T[nnz_];
        indexes_ = new int[nnz_];
        for (int i = 0; i < this->n; i++) {
            SparseVector<T>::set(i, other.get(i));
        }
    }

    /**
    * @brief Copy constructor for SparseVector from different type SparseVectorBase.
    *
    * Constructs a vector of size 'n' and performs a deep copy of 'other'.
    * Allocates 'nnz * sizeof(T) + nnz * sizeof(int)' bytes on the heap.
    *
    * @param other SparseVectorBase to copy from.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    * @tparam OTHER_T Scalar type of the 'other' SparseVectorBase.
    */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    SparseVector(const SparseVectorBase<OTHER_T>& other) : SparseVectorBase<T>(other.n) {
        nnz_ = 0;
        values_ = new T[nnz_];
        indexes_ = new int[nnz_];
        for (int i = 0; i < this->n; i++) {
            SparseVector<T>::set(i, other.get(i));
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
    SparseVector(SparseVector<T>&& other) noexcept : SparseVectorBase<T>(other.n), nnz_(other.nnz_) {
        values_ = other.values_;
        other.values_ = nullptr;

        indexes_ = other.indexes_;
        other.indexes_ = nullptr;
    }

    /**
     * @brief Copy assignment operator for SparseVector from same type SparseVector.
     * Replaces all elements with elements of 'other'.
     * May allocate 'other.nnz * sizeof(T) + other.nnz * sizeof(int)' bytes of memory on the heap if number of non-zero elements here doesn't match number of non-zero elements in 'other'.
     * @param other SparseVector to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same size as this.
     * @note 'other' must be of same size as this.
     */
    SparseVector<T>& operator=(const SparseVector<T>& other) {
        if (values_ != other.values_ && indexes_ != other.indexes_) {
            assert_same_size(*this, other);

            if (nnz_ != other.nnz_) {
                nnz_ = other.nnz_;

                delete[] values_;
                values_ = new T[nnz_];

                delete[] indexes_;
                indexes_ = new int[nnz_];
            }

            memcpy(values_, other.values_, nnz_ * sizeof(T));
            memcpy(indexes_, other.indexes_, nnz_ * sizeof(int));
        }

        return *this;
    }

    /**
     * @brief Copy assignment operator for SparseVector from different type SparseVector.
     * Replaces all elements with elements of 'other'.
     * May allocate 'other.nnz * sizeof(T) + other.nnz * sizeof(int)' bytes of memory on the heap if number of non-zero elements here doesn't match number of non-zero elements in 'other'.
     * @param other SparseVector to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same size as this.
     * @note 'other' must be of same size as this.
     * @note 'OTHER_T' must be able to implicitly convert to 'T'.
     * @tparam OTHER_T Scalar type of the 'other' DenseVector.
     */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    SparseVector<T>& operator=(const SparseVector<OTHER_T>& other) {
        assert_same_size(*this, other);

        const int otherNnz = other.nnz();

        if (nnz_ != otherNnz) {
            nnz_ = otherNnz;

            delete[] values_;
            values_ = new T[nnz_];

            delete[] indexes_;
            indexes_ = new int[nnz_];
        }

        const OTHER_T* otherValues = other.values();

        for (int i = 0; i < nnz_; i++) {
            values_[i] = otherValues[i];
        }

        memcpy(indexes(), other.indexes(), nnz_ * sizeof(int));

        return *this;
    }

    /**
    * @brief Copy assignment operator for SparseVector from same type SparseVectorBase.
    * Replaces all elements with elements of 'other'.
    * Allocates 'other.nnz * sizeof(T) + other.nnz * sizeof(T)' bytes of memory on the heap.
    * @param other SparseVectorBase to copy from.
    * @return Reference to this.
    * @throws InvalidDimensionException If 'other' does not have same size as this.
    * @note 'other' must be of same size as this.
    */
    SparseVector<T>& operator=(const SparseVectorBase<T>& other) {
        assert_same_size(*this, other, "copy assign");
        for (int i = 0; i < this->n; i++) {
            SparseVector<T>::set(i, other.get(i));
        }

        return *this;
    }

    /**
    * @brief Copy assignment operator for SparseVector from different type SparseVectorBase.
    * Replaces all elements with elements of 'other'.
    * Allocates 'other.nnz * sizeof(T) + other.nnz * sizeof(T)' bytes of memory on the heap.
    * @param other SparseVectorBase to copy from.
    * @return Reference to this.
    * @throws InvalidDimensionException If 'other' does not have same size as this.
    * @note 'other' must be of same size as this.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    * @tparam OTHER_T Scalar type of the 'other' DenseVector.
    */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    SparseVector<T>& operator=(const SparseVectorBase<OTHER_T>& other) {
        assert_same_size(*this, other, "copy assign");
        for (int i = 0; i < this->n; i++) {
            SparseVector<T>::set(i, other.get(i));
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
    SparseVector<T>& operator=(SparseVector<T>&& other) noexcept {
        if (values_ != other.values_ && indexes_ != other.indexes_) {
            assert_same_size(*this, other);

            delete[] values_;
            values_ = other.values_;
            other.values_ = nullptr;

            delete[] indexes_;
            indexes_ = other.indexes_;
            other.indexes_ = nullptr;

            nnz_ = other.nnz_;
        }

        return *this;
    }

    void set(const int i, const T value) override {
        int j;

        for (j = 0; j < nnz_; j++) {
            const int curIndex = indexes_[j];

            if (curIndex == i) {
                // there is currently a non-zero element there, and we are placing a zero so we remove a non-zero element;
                if (compare<T, int>(value, 0)) {
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

                    memcpy(newIndices, indexes_, j * sizeof(int));

                    memcpy(&newIndices[j], &indexes_[j + 1], (nnz_ - j - 1) * sizeof(int));

                    delete[] indexes_;

                    indexes_ = newIndices;

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
        if (compare<T, int>(value, 0)) {
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

        memcpy(newIndices, indexes_, j * sizeof(int));

        newIndices[j] = i;

        memcpy(&newIndices[j + 1], &indexes_[j], (nnz_ - j) * sizeof(int));

        delete[] indexes_;

        indexes_ = newIndices;

        nnz_++;
    }

    [[nodiscard]] T get(const int i) const override {
        for (int j = 0; j < nnz_; j++) {
            if (indexes_[j] == i)
                return values_[j];
        }

        return 0;
    }

    [[nodiscard]] int nnz() const override {
        return nnz_;
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
     * @brief Gets the indexes pointer storing the indexes for the vectors non-zero elements.
     * @return Pointer to array of indexes of non-zero elements.
     */
    [[nodiscard]] int* indexes() {
        return indexes_;
    }

    /**
     * @brief Gets the const indexes pointer storing the indexes for the vectors non-zero elements.
     * @return Const pointer to array of indexes of non-zero elements.
     */
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
    SparseVectorView<T>& operator=(const SparseVectorView<T>& other) = delete;
    SparseVectorView<T>& operator=(SparseVectorView<T>&& other) noexcept = delete;

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
    SparseVectorView(const SparseVector<T>& owner, const int n, const int offset) : SparseVectorBase<T>(n), offset_(offset), owner_(owner) {}


    /**
     * @brief Copy constructor for SparseVectorView.
     *
     * Constructs a view with the same 'owner' as 'other'.
     * Does not allocate new memory.
     *
     * @param other SparseVectorView to copy from.
     */
    SparseVectorView(const SparseVectorView<T>& other) : SparseVectorBase<T>(other.n), offset_(other.offset_), owner_(other.owner_) {}

    /**
     * @brief Trying to modify a SparseVector through a view is invalid.
     * @throws InvalidOperationException You cannot modify owner through a view.
     */
    void set(const int, const T) override {
        throw InvalidOperationException("Cannot modify owner through view");
    }

    [[nodiscard]] T get(const int i) const override {
        return owner_.get(i + offset_);
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

    /**
     * @brief Gets the offset relative to the 'owner'.
     * @return The offset.
     */
    [[nodiscard]] int offset() const {
        return offset_;
    }

    /**
    * @brief Gets the const reference to the SparseVector owner.
    * @return Const reference to SparseVector owner.
    */
    [[nodiscard]] const SparseVector<T>& owner() const {
        return owner_;
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
    CustomSparseVector<T>& operator=(const CustomSparseVector<T>& other) = delete;
    CustomSparseVector<T>& operator=(CustomSparseVector<T>&& other) noexcept = delete;

    /**
     * @brief Constructs a CustomSparseMatrix of size 'n'.
     * Does not allocate any memory on the heap.
     * CustomSparseVector instance does not own 'values' or 'indexes' pointer.
     * Think of it as a view on an arbitrary 'values' and 'indexes' pointer.
     * @param n Number of vector elements.
     * @param values Reference to array containing non-zero elements of vector.
     * @param indexes Reference to array containing indexes of non-zero elements of vector.
     * @param nnz Reference to number of non-zero elements.
     * @note Length of 'data' array must be greater than 'nnz - 1'.
     * @note The array 'values' and 'indexes' are pointing to may change.
     * @note Value of 'nnz' may change.
     */
    CustomSparseVector(const int n, T*& values, int*& indexes, int& nnz) : SparseVectorBase<T>(n), values_(values), indexes_(indexes), nnz_(nnz) {}

    void set(const int i, const T value) override {
        int j;

        for (j = 0; j < nnz_; j++) {
            const int curIndex = indexes_[j];

            if (curIndex == i) {
                // there is currently a non-zero element there, and we are placing a zero so we remove a non-zero element;
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

                    memcpy(newIndices, indexes_, j * sizeof(int));

                    memcpy(&newIndices[j], &indexes_[j + 1], (nnz_ - j - 1) * sizeof(int));

                    delete[] indexes_;

                    indexes_ = newIndices;

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
        memcpy(newValues, values_, j * sizeof(T));

        // set the new value
        newValues[j] = value;

        // copy everything after j
        memcpy(&newValues[j + 1], &values_[j], (nnz_ - j) * sizeof(T));

        delete[] values_;

        values_ = newValues;

        int* newIndices = new int[nnz_ + 1];

        memcpy(newIndices, indexes_, j * sizeof(int));

        memcpy(&newIndices[j + 1], &values_[j], (nnz_ - j) * sizeof(int));

        delete[] indexes_;

        indexes_ = newIndices;

        nnz_++;
    }

    [[nodiscard]] T get(const int i) const override {
        for (int j = 0; j < nnz_; j++) {
            if (indexes_[j] == i)
                return values_[j];
        }

        return 0;
    }

    [[nodiscard]] int nnz() const override {
        return nnz_;
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
    * @brief Gets the reference to the pointer storing the indexes of the vectors non-zero elements.
    * @return Reference to pointer containing the indexes of the non-zero elements.
    */
    [[nodiscard]] int*& indexes() {
        return indexes_;
    }

    /**
    * @brief Gets the const reference to the const pointer storing the indexes of the vectors non-zero elements.
    * @return Const reference to const pointer containing the indexes of the non-zero elements.
    */
    [[nodiscard]] const int* const& indexes() const {
        return indexes_;
    }

    ~CustomSparseVector() override = default;

private:
    T*& values_;
    int*& indexes_;
    int& nnz_;
};
