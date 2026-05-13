#pragma once
#include "../../helper.h"
#include "helper.h"
#include <cstddef>
#include "../../exceptions.h"

template<scalar T = float>
struct DenseVectorView {
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
    DenseVectorView(const DenseVector<T>& owner, const std::size_t n, const std::size_t offset) : offset_(offset), n_(n), owner_(owner) {
    }

    /**
    * @brief Copy constructor for DenseVectorView.
    *
    * Constructs a view with the same 'owner' as 'other'.
    * Does not allocate new memory.
    *
    * @param other DenseVectorView to copy from.
    */
    DenseVectorView(const DenseVectorView<T>& other) : offset_(other.offset_), n_(other.n_), owner_(other.owner_) {
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

    ~DenseVectorView() = default;

private:
    const std::size_t offset_;
    std::size_t n_;

    const DenseVector<T>& owner_;
};
