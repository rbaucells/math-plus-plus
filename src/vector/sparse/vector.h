#pragma once

#include "../../exceptions.h"
#include "../../helper.h"

#include "helper.h"

template<scalar T = float>
struct SparseVectorBase {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    [[nodiscard]] int n() const {
        return n_;
    }

protected:
    /**
     * @brief Initializes the size of the vector.
     *
     * Internal constructor that initializes the 'n' field.
     * Does not allocate memory for matrix elements.
     *
     * @param n Number of elements.
     */
    explicit SparseVectorBase(const int n) : n_(n) {}

    int n_;

public:
    /**
     * @brief Sets the value of the element at index 'i'
     * @param i Index of element
     * @param value The value to set at index 'i'
     * @throws InvalidIndexException If 'i' is negative or greater than 'n - 1'
     */
    virtual void set(int i, T value) = 0;

    /**
     * @brief Gets the value of the element at index 'i'
     * @param i Index of element
     * @return The value at index 'i'
     * @throws InvalidIndexException If 'i' is negative or greater than 'n - 1'
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
        if (n < 0) {
            throw InvalidIndexException("Cannot construct SparseVector of negative size");
        }

        nnz_ = 0;
        values_ = new T[nnz_];
        indices_ = new int[nnz_];
    }

    /**
     * @brief Constructs a SparseVector of size 'n' with elements 'initializerList'.
     * Allocates 'initializerList.size() x sizeof(T) + initializerList.size() x sizeof(int)' bytes of memory on the heap.
     * @param n Size of vector.
     * @param initializerList Initializer list of T, int tuples. Representing value and index.
     *
     * @note 'initializerList' must be sorted in increasing indices.
     */
    SparseVector(const int n, std::initializer_list<std::tuple<T, int>> initializerList) : SparseVector<T>(n) {
        if (n < 0) {
            throw InvalidIndexException("Cannot construct SparseVector of negative size");
        }

        nnz_ = initializerList.size();
        values_ = new T[nnz_];
        indices_ = new int[nnz_];

        int i = 0;
        for (const auto& nonZeroElement : initializerList) {
            values_[i] = std::get<0>(nonZeroElement);
            indices_[i] = std::get<1>(nonZeroElement);

            ++i;
        }
    }

    /**
     * @brief Copy constructor for SparseVector from same type SparseVector.
     *
     * Constructs a vector of size 'n' and performs a deep copy of 'other'.
     * Allocated 'nnz * sizeof(T) + nnz * sizeof(int)' bytes of memory on the heap.
     *
     * @param other SparseVector to copy from.
     */
    SparseVector(const SparseVector<T>& other) : SparseVectorBase<T>(other.n_), nnz_(other.nnz_) {
        values_ = new T[nnz_];
        memcpy(values_, other.values_, nnz_ * sizeof(T));

        indices_ = new int[nnz_];
        memcpy(indices_, other.indices_, nnz_ * sizeof(int));
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
    SparseVector(const SparseVector<OTHER_T>& other) : SparseVectorBase<T>(other.n()), nnz_(other.nnz()) {
        values_ = new T[nnz_];

        const OTHER_T* otherValues = other.values();

        for (int i = 0; i < nnz_; i++) {
            values_[i] = otherValues[i];
        }

        indices_ = new int[nnz_];

        const int* otherIndices = other.indices();

        memcpy(indices_, otherIndices, nnz_ * sizeof(int));
    }

    /**
    * @brief Copy constructor for SparseVector from same type SparseVectorBase.
    *
    * Constructs a vector of size 'n' and performs a deep copy of 'other'.
    * Allocates 'nnz * sizeof(T) + nnz * sizeof(int)' bytes on the heap.
    *
    * @param other SparseVectorBase to copy from.
    */
    SparseVector(const SparseVectorBase<T>& other) : SparseVectorBase<T>(other.n()) {
        nnz_ = 0;
        values_ = new T[nnz_];
        indices_ = new int[nnz_];
        for (int i = 0; i < this->n_; i++) {
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
    SparseVector(const SparseVectorBase<OTHER_T>& other) : SparseVectorBase<T>(other.n()) {
        nnz_ = 0;
        values_ = new T[nnz_];
        indices_ = new int[nnz_];
        for (int i = 0; i < this->n_; i++) {
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
    SparseVector(SparseVector<T>&& other) noexcept : SparseVectorBase<T>(other.n_), nnz_(other.nnz_) {
        values_ = other.values_;
        other.values_ = nullptr;

        indices_ = other.indices_;
        other.indices_ = nullptr;
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
        if (values_ != other.values_ && indices_ != other.indices_) {
            assert_same_size(*this, other);

            if (nnz_ != other.nnz_) {
                nnz_ = other.nnz_;

                delete[] values_;
                values_ = new T[nnz_];

                delete[] indices_;
                indices_ = new int[nnz_];
            }

            memcpy(values_, other.values_, nnz_ * sizeof(T));
            memcpy(indices_, other.indices_, nnz_ * sizeof(int));
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

            delete[] indices_;
            indices_ = new int[nnz_];
        }

        const OTHER_T* otherValues = other.values();

        for (int i = 0; i < nnz_; i++) {
            values_[i] = otherValues[i];
        }

        memcpy(indices(), other.indices(), nnz_ * sizeof(int));

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
        assert_same_size(*this, other);
        for (int i = 0; i < this->n_; i++) {
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
        assert_same_size(*this, other);
        for (int i = 0; i < this->n_; i++) {
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
    SparseVector<T>& operator=(SparseVector<T>&& other) {
        if (values_ != other.values_ && indices_ != other.indices_) {
            assert_same_size(*this, other);

            delete[] values_;
            values_ = other.values_;
            other.values_ = nullptr;

            delete[] indices_;
            indices_ = other.indices_;
            other.indices_ = nullptr;

            nnz_ = other.nnz_;
        }

        return *this;
    }

    void set(const int i, const T value) override {
        if (i < 0 || i > this->n_ - 1) {
            throw InvalidIndexException("Cannot set on SparseVector with invalid index");
        }
        int j;

        for (j = 0; j < nnz_; j++) {
            const int curIndex = indices_[j];

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

                    memcpy(newIndices, indices_, j * sizeof(int));

                    memcpy(&newIndices[j], &indices_[j + 1], (nnz_ - j - 1) * sizeof(int));

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
        memcpy(newValues, values_, j * sizeof(T));

        // set the new value
        newValues[j] = value;

        // copy everything after j
        memcpy(&newValues[j + 1], &values_[j], (nnz_ - j) * sizeof(T));

        delete[] values_;

        values_ = newValues;

        int* newIndices = new int[nnz_ + 1];

        memcpy(newIndices, indices_, j * sizeof(int));

        newIndices[j] = i;

        memcpy(&newIndices[j + 1], &indices_[j], (nnz_ - j) * sizeof(int));

        delete[] indices_;

        indices_ = newIndices;

        nnz_++;
    }

    [[nodiscard]] T get(const int i) const override {
        if (i < 0 || i > this->n_ - 1) {
            throw InvalidIndexException("Cannot get from SparseVector with invalid index");
        }

        for (int j = 0; j < nnz_; j++) {
            if (indices_[j] == i) {
                return values_[j];
            }
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
     * @brief Gets the indices pointer storing the indices for the vectors non-zero elements.
     * @return Pointer to array of indices of non-zero elements.
     */
    [[nodiscard]] int* indices() {
        return indices_;
    }

    /**
     * @brief Gets the const indices pointer storing the indices for the vectors non-zero elements.
     * @return Const pointer to array of indices of non-zero elements.
     */
    [[nodiscard]] const int* indices() const {
        return indices_;
    }

    ~SparseVector() override = default;

private:
    T* values_;
    int* indices_;
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
    SparseVectorView(const SparseVectorView<T>& other) : SparseVectorBase<T>(other.n_), offset_(other.offset_), owner_(other.owner_) {}

    /**
     * @brief Trying to modify a SparseVector through a view is invalid.
     * @throws InvalidOperationException You cannot modify owner through a view.
     * @throws InvalidIndexException If 'i' is negative or greater than 'n - 1'
     */
    void set(const int i, const T) override {
        if (i > this->n_ - 1|| i < 0) {
            throw InvalidIndexException("Cannot set on view with invalid index");
        }

        throw InvalidOperationException("Cannot modify owner through view");
    }

    [[nodiscard]] T get(const int i) const override {
        if (i < 0 || i > this->n_ - 1) {
            throw InvalidIndexException("Cannot get from SparseVectorView with invalid index");
        }

        return owner_.get(i + offset_);
    }

    [[nodiscard]] int nnz() const override {
        int nnz = 0;

        for (int i = 0; i < owner_.nnz(); i++) {
            const int curIndex = owner_.indices()[i];

            if (curIndex >= offset_ && curIndex < offset_ + this->n_) {
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
     * CustomSparseVector instance does not own 'values' or 'indices' pointer.
     * Think of it as a view on an arbitrary 'values' and 'indices' pointer.
     * @param n Number of vector elements.
     * @param values Reference to array containing non-zero elements of vector.
     * @param indices Reference to array containing indices of non-zero elements of vector.
     * @param nnz Reference to number of non-zero elements.
     * @note The array 'values' and 'indices' are pointing to may change.
     * @note Value of 'nnz' may change.
     */
    CustomSparseVector(const int n, T*& values, int*& indices, int& nnz) : SparseVectorBase<T>(n), values_(values), indices_(indices), nnz_(nnz) {}

    void set(const int i, const T value) override {
        if (i < 0 || i > this->n_ - 1) {
            throw InvalidIndexException("Cannot set on CustomSparseVector with invalid index");
        }
        int j;

        for (j = 0; j < nnz_; j++) {
            const int curIndex = indices_[j];

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

                    memcpy(newIndices, indices_, j * sizeof(int));

                    memcpy(&newIndices[j], &indices_[j + 1], (nnz_ - j - 1) * sizeof(int));

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
        memcpy(newValues, values_, j * sizeof(T));

        // set the new value
        newValues[j] = value;

        // copy everything after j
        memcpy(&newValues[j + 1], &values_[j], (nnz_ - j) * sizeof(T));

        delete[] values_;

        values_ = newValues;

        int* newIndices = new int[nnz_ + 1];

        memcpy(newIndices, indices_, j * sizeof(int));

        newIndices[j] = i;

        memcpy(&newIndices[j + 1], &indices_[j], (nnz_ - j) * sizeof(int));

        delete[] indices_;

        indices_ = newIndices;

        nnz_++;
    }

    [[nodiscard]] T get(const int i) const override {
        if (i < 0 || i > this->n_ - 1) {
            throw InvalidIndexException("Cannot get from CustomSparseVector with invalid index");
        }

        for (int j = 0; j < nnz_; j++) {
            if (indices_[j] == i) {
                return values_[j];
            }
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
    * @brief Gets the reference to the pointer storing the indices of the vectors non-zero elements.
    * @return Reference to pointer containing the indices of the non-zero elements.
    */
    [[nodiscard]] int*& indices() {
        return indices_;
    }

    /**
    * @brief Gets the const reference to the const pointer storing the indices of the vectors non-zero elements.
    * @return Const reference to const pointer containing the indices of the non-zero elements.
    */
    [[nodiscard]] const int* const& indices() const {
        return indices_;
    }

    ~CustomSparseVector() override = default;

private:
    T*& values_;
    int*& indices_;
    int& nnz_;
};
