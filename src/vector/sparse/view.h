#pragma once
#include "../../helper.h"
#include "vector.h"
#include <cstddef>
#include "../../exceptions.h"

template<scalar T = float>
struct SparseVectorView {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

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
    SparseVectorView(const SparseVector<T>& owner, const std::size_t n, const std::size_t offset) : offset_(offset), n_(n), owner_(owner) {
    }


    /**
     * @brief Copy constructor for SparseVectorView.
     *
     * Constructs a view with the same 'owner' as 'other'.
     * Does not allocate new memory.
     *
     * @param other SparseVectorView to copy from.
     */
    SparseVectorView(const SparseVectorView<T>& other) : offset_(other.offset_), n_(other.n_), owner_(other.owner_) {
    }

    /**
     * @brief Trying to modify a SparseVector through a view is invalid.
     * @throws InvalidOperationException You cannot modify owner through a view.
     * @throws InvalidIndexException If 'i' is negative or greater than 'n - 1'
     */
    void set(const std::size_t i, const T)  {
        if (i > this->n_ - 1) {
            throw InvalidIndexException("Cannot set on view with invalid index");
        }

        throw InvalidOperationException("Cannot modify owner through view");
    }

    [[nodiscard]] T get(const std::size_t i) const  {
        if (i > this->n_ - 1) {
            throw InvalidIndexException("Cannot get from SparseVectorView with invalid index");
        }

        return owner_.get(i + offset_);
    }

    [[nodiscard]] std::size_t nnz() const  {
        std::size_t nnz = 0;

        for (std::size_t i = 0; i < owner_.nnz(); i++) {
            const std::size_t curIndex = owner_.indices()[i];

            if (curIndex >= offset_ && curIndex < offset_ + this->n_) {
                nnz++;
            }
        }

        return nnz;
    }

    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    /**
     * @brief Gets the offset relative to the 'owner'.
     * @return The offset.
     */
    [[nodiscard]] std::size_t offset() const {
        return offset_;
    }

    /**
    * @brief Gets the const reference to the SparseVector owner.
    * @return Const reference to SparseVector owner.
    */
    [[nodiscard]] const SparseVector<T>& owner() const {
        return owner_;
    }

    ~SparseVectorView()  = default;

private:
    const std::size_t offset_;
    std::size_t n_;

    const SparseVector<T>& owner_;
};