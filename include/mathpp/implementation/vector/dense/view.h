#ifndef MATHPP_IMPLEMENTATION_VECTOR_DENSE_VIEW_H
#define MATHPP_IMPLEMENTATION_VECTOR_DENSE_VIEW_H

#include <cstddef>

#include "vector.h"
#include "mathpp/implementation/common/exceptions.h"
#include "mathpp/implementation/common/traits.h"

/**
 * @brief Non-owning view on a DenseVector<T>.
 * @note Owner DenseVector must outlive view.
 * @tparam T Scalar type of vector elements.
 */
template<scalar T>
struct DenseVectorView {
    using ValueType = T;

    static constexpr bool isComplex = is_complex_v<T>;

    DenseVectorView() = delete;
    DenseVectorView(const DenseVectorView<T>& other) = delete;
    DenseVectorView(DenseVectorView<T>&& other) noexcept = delete;
    DenseVectorView<T>& operator=(const DenseVectorView<T>& other) = delete;
    DenseVectorView<T>& operator=(DenseVectorView<T>&& other) noexcept = delete;

    /**
     * @brief Owner constructor.
     *
     * Creates a view of the owner vector of size 'n'.
     * View starts at offset.
     * Does not allocate memory on heap.
     *
     * @param owner DenseVector owner containing real data.
     * @param n Number of elements in constructed view.
     * @param offset Zero-based index at which the view starts relative to owner.
     *
     * @note DenseVector owner must outlive view.
     */
    DenseVectorView(const DenseVector<T>& owner, const std::size_t n, const std::size_t offset) : n_(n), offset_(offset), owner_(owner) {}

    /**
     * @brief Accesses the element at a provided index.
     *
     * Retrieves a const reference to the element at (i) relative to where the view starts.
     * Implemented by accessing owner at i + offset.
     * Does not check bounds of provided index.
     * Does not allocate memory on the heap.
     *
     * @param i Zero-based index of element.
     *
     * @see DenseVectorView::at(const std::size_t i).
     *
     * @return Const-reference to element at (i).
     * @note Undefined behavior if i (plus offset) is out of bounds of the owner vector.
     */
    const T& operator[](const std::size_t i) const {
        return owner_[i + offset_];
    }

    /**
    * @warning InvalidOperationException Modifying owner through view is illegal.
    */
    T& operator[](const std::size_t) {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "Cannot modify owner through view");
    }

    /**
     * @brief Accesses the element at a provided index.
     *
     * Retrieves a const reference to the element at (i) relative to where the view starts.
     * Implemented by accessing owner at i + offset.
     * Checks bounds of provided index relative to view AND to owner.
     * Does not allocate memory on the heap.
     *
     * @param i Zero-based index of element.
     *
     * @see DenseVectorView::operator[](const std::size_t i).
     *
     * @throws InvalidIndexException If index is not withing view OR i + offset is not within owner vector.
     * @note Index must be within size of view AND i + offset must be within size of owner vector.
     * @return Const-reference to element at (r, c).
     */
    const T& at(const std::size_t i) const {
        if (i >= n_) {
            throw InvalidIndexException("Cannot access view at invalid index");
        }

        return owner_.at(i + offset_);
    }

    /**
     * @throws InvalidOperationException Modifying owner through view is illegal.
     */
    T& at(const std::size_t) {
        throw InvalidOperationException("Cannot modify owner through view");
    }

    /**
     * @return Number of elements to offset view by relative to owner vector.
     */
    [[nodiscard]] std::size_t offset() const {
        return offset_;
    }

    /**
    * @return Number of elements in DenseVector.
    */
    [[nodiscard]] std::size_t n() const {
        return n_;
    }

    [[nodiscard]] const DenseVector<T>& owner() const {
        return owner_;
    }

    ~DenseVectorView() = default;


private:
    // number of elements
    const std::size_t n_;
    // offset relative to owner
    const std::size_t offset_;

    // owner dense vector
    const DenseVector<T>& owner_;
};

#endif // MATHPP_IMPLEMENTATION_VECTOR_DENSE_VIEW_H
