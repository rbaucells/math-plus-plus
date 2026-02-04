#pragma once
#include <initializer_list>

#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T = float>
struct DenseVectorBase {
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
    explicit DenseVectorBase(const int n) : n(n) {}

public:
    /**
    * @brief Accesses the element at index 'i'.
    *
    * @param i Zero-based index.
    * @return Reference to the element at index 'i'.
    */
    [[nodiscard]] virtual T& at(int i) = 0;

    /**
    * @brief Accesses the element at index 'i' (const).
    *
    * @param i Zero-based index.
    * @return Const reference to the element at index 'i'.
    */
    [[nodiscard]] virtual const T& at(int i) const = 0;

    [[nodiscard]] T& operator[](const int i) {
        return at(i);
    }

    [[nodiscard]] const T& operator[](const int i) const {
        return at(i);
    }

    virtual ~DenseVectorBase() = default;
};

template<scalar T = float>
struct DenseVector : DenseVectorBase<T> {
    DenseVector() = delete;

    /**
     * @brief Constructs a DenseVector of size 'n'.
     * Allocates 'n * sizeof(T)' bytes of memory on the heap.
     * Optionally fills all elements with zero.
     * @param n Number of elements.
     * @param fill If true, initializes all elements to zero; otherwise leaves elements uninitialized.
     */
    DenseVector(const int n, const bool fill) : DenseVectorBase<T>(n) {
        data_ = new T[n];

        if (!fill)
            return;

        for (int i = 0; i < n; i++) {
            data_[i] = 0;
        }
    }

    /**
    * @brief Constructs a DenseVector from an initializer list.
    *
    * Allocates 'n * sizeof(T)' bytes on the heap.
    *
    * @param initializerList Nested initializer_list representing matrix elements.
    */
    DenseVector(const std::initializer_list<T>& initializerList) : DenseVectorBase<T>(initializerList.size()) {
        data_ = new T[initializerList.size()];

        int i = 0;
        for (const T element : initializerList) {
            data_[i] = element;
            i++;
        }
    }

    /**
     * @brief Copy constructor for DenseVector.
     *
     * Constructs a vector of size 'n' and performs a deep copy of 'other'.
     * Allocates 'n * sizeof(T)' bytes on the heap.
     *
     * @param other DenseVector to copy from.
     */
    DenseVector(const DenseVector<T>& other) : DenseVectorBase<T>(other.n) {
        data_ = new T[other.n];
        memcpy(data_, other.data_, this->n * sizeof(T));
    }

    /**
     * @brief Copy constructor for DenseVector from DenseVectorBase.
     *
     * Constructs a vector of size 'other.n' and performs a deep copy of 'other'.
     * Allocates 'other.n * sizeof(T)' bytes on the heap.
     *
     * @param other DenseVectorBase to copy from.
     */
    DenseVector(const DenseVectorBase<T>& other) : DenseVectorBase<T>(other.n) {
        data_ = new T[other.n];

        for (int i = 0; i < this->n; i++) {
            data_[i] = other.at(i);
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
    DenseVector(DenseVector<T>&& other) noexcept : DenseVectorBase<T>(other.n) {
        data_ = other.data_;
        other.data_ = nullptr;
    }

    DenseVector& operator=(const DenseVector<T>& other) = delete;
    DenseVector& operator=(DenseVector<T>&& other) noexcept = delete;

    [[nodiscard]] T& at(int i) override {
        return data_[i];
    }

    [[nodiscard]] const T& at(int i) const override {
        return data_[i];
    }

    [[nodiscard]] T* data() {
        return data_;
    }

    [[nodiscard]] const T* data() const {
        return data_;
    }

    ~DenseVector() override {
        delete[] data_;
    }

private:
    T* data_;
};

template<scalar T = float>
struct DenseVectorView : DenseVectorBase<T> {
    DenseVectorView() = delete;
    DenseVectorView(DenseVectorView<T>&& other) noexcept = delete;
    DenseVectorView& operator=(const DenseVectorView<T>& other) = delete;
    DenseVectorView& operator=(DenseVectorView<T>&& other) noexcept = delete;

    /**
    * @brief Copy constructor for DenseVectorView.
    *
    * Constructs a view with the same 'owner' as 'other'.
    * Does not allocate new memory.
    *
    * @param other DenseVectorView to copy from.
    */
    DenseVectorView(const DenseVectorView<T>& other) : DenseVectorBase<T>(other.n), offset_(other.offset_), owner_(other.owner_) {};

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
    DenseVectorView(const DenseVector<T>& owner, const int n, const int offset) : DenseVectorBase<T>(n), offset_(offset), owner_(owner) {}

    /**
     * @brief Trying to modify a DenseVector through a view is invalid.
     * @throws InvalidOperationException You cannot modify owner through a view.
     */
    [[nodiscard]] T& at(const int) override {
        throw InvalidOperationException("Cannot modify owner through view");
    }

    [[nodiscard]] const T& at(const int i) const override {
        return owner_.at(i + offset_);
    }

    [[nodiscard]] const DenseVector<T>& owner() const {
        return owner_;
    }

    [[nodiscard]] int offset() const {
        return offset_;
    }

    ~DenseVectorView() override = default;

private:
    const int offset_;
    const DenseVector<T>& owner_;
};

template<scalar T = float>
struct CustomDenseVector : DenseVectorBase<T> {
    CustomDenseVector() = delete;
    CustomDenseVector(const CustomDenseVector<T>& other) = delete;
    CustomDenseVector(CustomDenseVector<T>&& other) noexcept = delete;

    CustomDenseVector(T* const data, const int n, const int stride) : DenseVectorBase<T>(n), stride_(stride), data_(data) {}

    [[nodiscard]] T& at(const int i) override {
        return data_[i * stride_];
    }

    [[nodiscard]] const T& at(const int i) const override {
        return data_[i * stride_];
    }

    [[nodiscard]] int stride() const {
        return stride_;
    }

    [[nodiscard]] T* data() {
        return data_;
    }

    [[nodiscard]] const T* data() const {
        return data_;
    }

    ~CustomDenseVector() override = default;

private:
    const int stride_;
    T* const data_;
};
