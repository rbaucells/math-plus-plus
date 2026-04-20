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
    DenseVector(const std::size_t n, const bool fill) : DenseVectorBase<T>(n), data_(new T[n]) {
        if (fill) {
            for (std::size_t i = 0; i < n; i++) {
                data_[i] = 0;
            }
        }
    }

    /**
    * @brief Constructs a DenseVector from an initializer list of size 'initializerList.size()'.
    *
    * Allocates 'n * sizeof(T)' bytes on the heap.
    *
    * @param initializerList Initializer_list representing vector elements.
    */
    DenseVector(const std::initializer_list<T>& initializerList) : DenseVectorBase<T>(initializerList.size()), data_(new T[initializerList.size()]) {
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
    DenseVector(const DenseVector<T>& other) : DenseVectorBase<T>(other.n_), data_(new T[other.n_]) {
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
    DenseVector(const DenseVector<OTHER_T>& other) : DenseVectorBase<T>(other.n()), data_(new T[other.n()]) {
        const OTHER_T* otherData = other.data();

        for (std::size_t i = 0; i < this->n_; i++) {
            data_[i] = otherData[i];
        }
    }

    /**
     * @brief Copy constructor for DenseVector from same type DenseVectorBase.
     *
     * Constructs a vector of size 'other.n' and performs a deep copy of 'other'.
     * Allocates 'other.n * sizeof(T)' bytes on the heap.
     *
     * @param other DenseVectorBase to copy from.
     */
    DenseVector(const DenseVectorBase<T>& other) : DenseVectorBase<T>(other.n()), data_(new T[other.n()]) {
        for (std::size_t i = 0; i < this->n_; i++) {
            data_[i] = other[i];
        }
    }

    /**
    * @brief Copy constructor for DenseVector from different type DenseVectorBase.
    *
    * Constructs a vector of size 'other.n' and performs a deep copy of 'other'.
    * Allocates 'other.n * sizeof(T)' bytes on the heap.
    *
    * @param other DenseVectorBase to copy from.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    * @tparam OTHER_T Scalar type of the 'other' DenseMatrix.
    */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    DenseVector(const DenseVectorBase<OTHER_T>& other) : DenseVectorBase<T>(other.n()), data_(new T[other.n()]) {
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
    DenseVector(DenseVector<T>&& other) noexcept : DenseVectorBase<T>(other.n_), data_(other.data_) {
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

    /**
     * @brief Copy assignment operator for DenseVector from same type DenseVectorBase.
     * Replaces all elements with elements of 'other'.
     * Does not allocate memory on the heap.
     * @param other DenseVectorBase to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same size as this.
     * @note 'other' must be of same size as this.
     */
    DenseVector<T>& operator=(const DenseVectorBase<T>& other) {
        if (static_cast<const DenseVectorBase<T>*>(this) != &other) {
            if (this->n_ != other.n()) {
                this->n_ = other.n();
                delete[] data_;
                data_ = new T[this->n_];
            }

            for (std::size_t i = 0; i < this->n_; i++) {
                data_[i] = other[i];
            }
        }

        return *this;
    }

    /**
    * @brief Copy assignment operator for DenseVector from different type DenseVectorBase.
    * Replaces all elements with elements of 'other'.
    * Does not allocate memory on the heap.
    * @param other DenseVectorBase to copy from.
    * @return Reference to this.
    * @throws InvalidDimensionException If 'other' does not have same size as this.
    * @note 'other' must be of same size as this.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    * @tparam OTHER_T Scalar type of the 'other' DenseVectorBase.
    */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    DenseVector<T>& operator=(const DenseVectorBase<OTHER_T>& other) {
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

    ~DenseVector() override {
        delete[] data_;
    }

private:
    std::size_t n_;

    T* data_;
};

template<scalar T = float>
struct DenseVectorView : DenseVectorBase<T> {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    DenseVectorView() = delete;

    DenseVectorView(DenseVectorView<T>&& other) noexcept = delete;

    DenseVectorView<T>& operator=(const DenseVectorView<T>& other) = delete;

    DenseVectorView<T>& operator=(DenseVectorView<T>&& other) noexcept = delete;

    /**
     * @brief Constructs a DenseVectorView into an existing DenseVector.
     *
     * Creates a view of size 'n' into the 'owner' vector, starting at offset.
     * Does not allocate new memory.
     * The view holds a reference to the owner.
     *
     * @param owner DenseVector to create the view from.
     * @param n Number of elements in the view.
     * @param offset Starting index offset in the owner vector.
     */
    DenseVectorView(const DenseVector<T>& owner, const std::size_t n, const std::size_t offset) : DenseVectorBase<T>(n), offset_(offset), owner_(owner) {
    }

    /**
    * @brief Copy constructor for DenseVectorView.
    *
    * Constructs a view with the same 'owner' as 'other'.
    * Does not allocate new memory.
    *
    * @param other DenseVectorView to copy from.
    */
    DenseVectorView(const DenseVectorView<T>& other) : DenseVectorBase<T>(other.n_), offset_(other.offset_), owner_(other.owner_) {
    }

    /**
     * @brief Trying to modify a DenseVector through a view is invalid.
     * @throws InvalidOperationException You cannot modify owner through a view.
     */
    [[nodiscard]] T& at(const std::size_t) {
        throw InvalidOperationException("Cannot modify owner through view");
    }

    [[nodiscard]] const T& at(const std::size_t i) const {
        return owner_.at(i + offset_);
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
     * @brief Gets the offset relative to the 'owner'.
     * @return The offset.
     */
    [[nodiscard]] std::size_t offset() const {
        return offset_;
    }

    /**
    * @brief Gets the const reference to the DenseMatrix owner.
    * @return Const reference to DenseMatrix owner.
    */
    [[nodiscard]] const DenseVector<T>& owner() const {
        return owner_;
    }

    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    ~DenseVectorView() override = default;

private:
    const std::size_t offset_;
    std::size_t n_;

    const DenseVector<T>& owner_;
};

template<scalar T = float>
struct CustomDenseVector : DenseVectorBase<T> {
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
    CustomDenseVector(T* data, const std::size_t n, const std::size_t stride) : DenseVectorBase<T>(n), stride_(stride), data_(data) {
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

    ~CustomDenseVector() override = default;

private:
    const std::size_t stride_;
    std::size_t n_;

    T* const data_;
};
