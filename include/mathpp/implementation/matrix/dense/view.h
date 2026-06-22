#pragma once
#include <cstddef>

#include "matrix.h"
#include "mathpp/implementation/common/exceptions.h"
#include "mathpp/implementation/common/traits.h"

/**
 * @brief Non-owning column major view on a DenseMatrix<T>.
 * @note Owner DenseMatrix must outlive view.
 * @tparam T Scalar type of matrix elements.
 */
template<scalar T>
struct DenseMatrixView {
    using ValueType = T;

    static constexpr bool isComplex = is_complex_v<T>;

    DenseMatrixView() = delete;
    DenseMatrixView(const DenseMatrixView<T>& other) = delete;
    DenseMatrixView(DenseMatrixView<T>&& other) noexcept = delete;
    DenseMatrixView<T>& operator=(const DenseMatrixView<T>& other) = delete;
    DenseMatrixView<T>& operator=(DenseMatrixView<T>&& other) noexcept = delete;

    /**
     * @brief Owner constructor.
     *
     * Creates a 'rows x columns' view of the owner matrix.
     * View starts at rowOffset and colOffset.
     * Does not allocate memory on heap.
     *
     * @param owner DenseMatrix owner containing real data.
     * @param rows Number of rows in constructed view.
     * @param columns Number of columns in constructed view.
     * @param rowOffset Zero-based row index at which the view starts relative to owner.
     * @param colOffset Zero-based column index at which the view starts relative to owner.
     *
     * @note DenseMatrix owner must outlive view.
     */
    DenseMatrixView(const DenseMatrix<T>& owner, const std::size_t rows, const std::size_t columns, const std::size_t rowOffset, const std::size_t colOffset) : rows_(rows), columns_(columns), rowOffset_(rowOffset), colOffset_(colOffset), owner_(owner) {}

    /**
     * @brief Accesses the element at a provided row and column.
     *
     * Retrieves a reference to the element at coordinates (r, c) relative to where the view starts.
     * Implemented by accessing owner at r + rowOffset, c + colOffset.
     * Does not check bounds of provided r and c indices.
     * Does not allocate memory on the heap.
     *
     * @param r Zero-based row index of element.
     * @param c Zero-based columns index of element.
     *
     * @see DenseMatrixView::at(const std::size_t r, const std::size_t c).
     *
     * @return Const-reference to element at (r, c).
     * @note Undefined behavior if r or c (plus their respective offsets) are out of bounds of the owner matrix.
     */
    const T& operator[](const std::size_t r, const std::size_t c) const {
        return owner_[r + rowOffset_, c + colOffset_];
    }

    /**
    * @warning InvalidOperationException Modifying owner through view is illegal.
    */
    T& operator[](const std::size_t, const std::size_t) {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "Cannot modify owner through view");
    }

    /**
     * @brief Accesses the element at a provided row and column.
     *
     * Retrieves a reference to the element at coordinates (r, c) relative to where the view starts.
     * Implemented by accessing owner at r + rowOffset, c + colOffset.
     * Checks bounds of provided r and c indices relative to view AND to owner.
     * Does not allocate memory on the heap.
     *
     * @param r Zero-based row index of element.
     * @param c Zero-based columns index of element.
     *
     * @see DenseMatrixView::operator[](const std::size_t r, const std::size_t c).
     *
     * @throws InvalidIndexException If r or c are not withing view OR r + rowOffset or c + colOffset are not within owner matrix.
     * @note Indices r and c must be within size of view AND r + rowOffset and c + colOffset must be within size of owner matrix.
     * @return Const-reference to element at (r, c).
     */
    const T& at(const std::size_t r, const std::size_t c) const {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access view at invalid index");
        }

        return owner_.at(r + rowOffset_, c + colOffset_);
    }

    /**
     * @throws InvalidOperationException Modifying owner through view is illegal.
     */
    T& at(const std::size_t, const std::size_t) {
        throw InvalidOperationException("Cannot modify owner through view");
    }

    /**
     * @return Number of rows to offset view by relative to owner matrix.
     */
    [[nodiscard]] std::size_t rowOffset() const {
        return rowOffset_;
    }

    /**
     * @return Number of columns to offset view by relative to owner matrix.
     */
    [[nodiscard]] std::size_t colOffset() const {
        return colOffset_;
    }

    /**
    * @return Number of rows in DenseMatrix.
    */
    [[nodiscard]] std::size_t rows() const {
        return rows_;
    }

    /**
    * @return Number of columns in DenseMatrix.
    */
    [[nodiscard]] std::size_t columns() const {
        return columns_;
    }

    /**
     * @brief Accesses the matrix at a provided linear index.
     *
     * Works as if the view has a contiguous linear data array.
     * Implemented by converting linear index to r and c indices and then accessing owner matrix at r + rowOffset, c + colOffset.
     * Does not check bounds of index i.
     * Does not allocate memory.
     *
     * @param i Zero-based linear index to index into simulated data array.
     * @return Const-reference to element at linear index i of what the view 'sees'.
     */
    [[nodiscard]] const T& data(const std::size_t i) const {
        const std::size_t r = i % rows_;
        const std::size_t c = i / rows_;

        return owner_[r + rowOffset_, c + colOffset_];
    }

    /**
     * @throws InvalidOperationException Modifying owner through view is illegal.
     */
    [[nodiscard]] T& data(const std::size_t) {
        throw InvalidOperationException("Cannot modify owner through view");
    }

    [[nodiscard]] const DenseMatrix<T>& owner() const {
        return owner_;
    }

private:
    // number of rows
    const std::size_t rows_;
    // number of columns
    const std::size_t columns_;
    // row offset relative to owner
    const std::size_t rowOffset_;
    // column offset relative to owner
    const std::size_t colOffset_;

    // owner dense matrix
    const DenseMatrix<T>& owner_;
};
