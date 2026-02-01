#pragma once
#include <initializer_list>

#include "../../helper.h"

template<scalar T = float>
struct DenseVectorBase {
    const int n;

    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    DenseVectorBase() = delete;
    DenseVectorBase(const DenseVectorBase<T>& other) = delete;
    DenseVectorBase(DenseVectorBase<T>&& other) = delete;

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
    mutable T* data = nullptr;

    DenseVector() = delete;

    /**
     * @brief Constructs a DenseVector of size 'n'.
     * Allocates 'n * sizeof(T)' bytes of memory on the heap.
     * Optionally fills all elements with zero.
     * @param n Number of elements.
     * @param fill If true, initializes all elements to zero; otherwise leaves elements uninitialized.
     */
    DenseVector(const int n, const bool fill) : DenseVectorBase<T>(n) {
        data = new T[n];

        if (!fill)
            return;

        for (int i = 0; i < n; i++) {
            data[i] = 0;
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
        data = new T[initializerList.size()];

        int i = 0;
        for (const T element : initializerList) {
            data[i] = element;
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
        data = new T[other.n];
        memcpy(data, other.data, this->n * sizeof(T));
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
        data = new T[other.n];

        for (int i = 0; i < this->n; i++) {
            data[i] = other.at(i);
        }
    }

    /**
     * @brief Move constructor for DenseVector.
     *
     * Constructs a vector of size 'other.n' and performs a move from 'other'.
     * Does not allocate any memory on the heap
     *
     * @param other DenseVector to move from.
     */
    DenseVector(DenseVector<T>&& other) noexcept : DenseVectorBase<T>(other.n) {
        data = other.data;
        other.data = nullptr;
    }

    [[nodiscard]] T& at(int i) override {
        return data[i];
    }

    [[nodiscard]] const T& at(int i) const override {
        return data[i];
    }

    ~DenseVector() override {
        delete[] data;
    }
};

template<scalar T = float>
struct DenseVectorView : DenseVectorBase<T> {
    DenseVector<T>& owner;

    DenseVectorView() = delete;
    DenseVectorView(DenseVectorView<T>&& other) noexcept = delete;

    /**
    * @brief Copy constructor for DenseVectorView
    *
    * Constructs a view with the same 'owner' as 'other'.
    * Does not allocate new memory.
    *
    * @param other DenseVectorView to copy from
    */
    DenseVectorView(const DenseVectorView<T>& other) : DenseVectorBase<T>(other.n), owner(other.owner), offset_(other.offset_) {};

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
    DenseVectorView(const DenseVector<T>& owner, const int n, const int offset) : DenseVectorBase<T>(n), owner(owner), offset_(offset) {}

    [[nodiscard]] T& at(const int i) override {
        return owner.at(i + offset_);
    }

    [[nodiscard]] const T& at(const int i) const override {
        return owner.at(i + offset_);
    }

    ~DenseVectorView() override = default;

private:
    const int offset_;
};

template<scalar T = float>
struct CustomDenseVector : DenseVectorBase<T> {
    const int stride;

    T* const data;

    CustomDenseVector() = delete;
    CustomDenseVector(const CustomDenseVector<T>& other) = delete;
    CustomDenseVector(CustomDenseVector<T>&& other) noexcept = delete;

    CustomDenseVector(T* const data, const int n, const int stride) : DenseVectorBase<T>(n), stride(stride), data(data) {}

    [[nodiscard]] T& at(const int i) override {
        return data[i * stride];
    }

    [[nodiscard]] const T& at(const int i) const override {
        return data[i * stride];
    }

    ~CustomDenseVector() override = default;
};
