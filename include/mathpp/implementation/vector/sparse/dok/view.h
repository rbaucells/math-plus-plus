#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_VIEW_H
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_VIEW_H

#include <cstddef>

#include "vector.h"
#include "mathpp/implementation/common/exceptions.h"
#include "mathpp/implementation/common/traits.h"

template<scalar T = float>
struct DokSparseVectorView {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    DokSparseVectorView() = delete;

    DokSparseVectorView(DokSparseVectorView<T>&& other) noexcept = delete;

    DokSparseVectorView<T>& operator=(const DokSparseVectorView<T>& other) = delete;

    DokSparseVectorView<T>& operator=(DokSparseVectorView<T>&& other) noexcept = delete;

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
    DokSparseVectorView(const DokSparseVector<T>& owner, const std::size_t n, const std::size_t offset) : offset_(offset), n_(n), owner_(owner) {
    }


    /**
     * @brief Copy constructor for SparseVectorView.
     *
     * Constructs a view with the same 'owner' as 'other'.
     * Does not allocate new memory.
     *
     * @param other SparseVectorView to copy from.
     */
    DokSparseVectorView(const DokSparseVectorView<T>& other) : offset_(other.offset_), n_(other.n_), owner_(other.owner_) {
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
    [[nodiscard]] const DokSparseVector<T>& owner() const {
        return owner_;
    }

    ~DokSparseVectorView()  = default;

private:
    const std::size_t offset_;
    std::size_t n_;

    const DokSparseVector<T>& owner_;
};
#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_DOK_VIEW_H
