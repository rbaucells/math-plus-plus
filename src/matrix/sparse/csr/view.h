#pragma once
#include "../../../helper.h"
#include <cstddef>
#include "../../../exceptions.h"
#include "matrix.h"

template<scalar T = float>
struct CSRSparseMatrixView {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    CSRSparseMatrixView() = delete;

    CSRSparseMatrixView(CSRSparseMatrixView<T>&& other) noexcept = delete;

    CSRSparseMatrixView<T>& operator=(const CSRSparseMatrixView<T>& other) = delete;

    CSRSparseMatrixView<T>& operator=(CSRSparseMatrixView<T>&& other) noexcept = delete;

    /**
     * @brief Constructs a SparseMatrixView into an existing SparseMatrix.
     *
     * Creates a view of size `rows x columns` into the `owner` matrix, starting at the 'colOffset' and 'rowOffset'.
     * Does not allocate new memory.
     * The view holds a reference to the 'owner'.
     *
     * @param owner SparseMatrix to create a view from.
     * @param rows Number of rows in the view.
     * @param columns Number of columns in the view.
     * @param colOffset Starting column offset in the 'owner' matrix.
     * @param rowOffset Starting row offset in the 'owner' matrix.
     */
    CSRSparseMatrixView(const CSRSparseMatrix<T>& owner, const std::size_t rows, const std::size_t columns, const std::size_t colOffset, const std::size_t rowOffset) : rows_(rows), columns_(columns), colOffset_(colOffset), rowOffset_(rowOffset), owner_(owner) {
    }

    /**
     * @brief Copy constructor for SparseMatrixView.
     *
     * Constructs a view with the same 'owner' as 'other'.
     * Does not allocate new memory.
     *
     * @param other SparseMatrixView to copy from.
     */
    CSRSparseMatrixView(const CSRSparseMatrixView<T>& other) : rows_(other.rows_), columns_(other.columns_), colOffset_(other.colOffset_), rowOffset_(other.rowOffset_), owner_(other.owner_) {
    }

    /**
    * @brief Trying to modify a SparseMatrix through a view is invalid.
    * @throws InvalidOperationException You cannot modify owner through a view.
    */
    void set(const std::size_t c, const std::size_t r, const T) {
        if (c > columns_ - 1 || r > rows_ - 1) {
            throw InvalidIndexException("Cannot set on view with invalid index");
        }
        throw InvalidOperationException("Cannot modify owner through view");
    }

    [[nodiscard]] T get(const std::size_t c, const std::size_t r) const {
        if ( c > columns_ - 1 || r > rows_ - 1) {
            throw InvalidIndexException("Cannot get on view with invalid index");
        }

        return owner_.get(c + colOffset_, r + rowOffset_);
    }

    [[nodiscard]] std::size_t nnz() const {
        std::size_t nnz = 0;

        for (std::size_t c = colOffset_; c < colOffset_ + columns_; c++) {
            const std::size_t start = owner().colOffsets()[c];
            const std::size_t end = owner().colOffsets()[c + 1];

            for (std::size_t r = start; r < end; ++r) {
                const std::size_t curIndex = owner().rowIndices()[r];

                if (curIndex >= rowOffset_ && curIndex < rowOffset_ + rows_) {
                    nnz++;
                }
            }
        }

        return nnz;
    }

    /**
    * @brief Gets the column offset relative to the 'owner'.
    * @return The column offset.
    */
    [[nodiscard]] std::size_t colOffset() const {
        return colOffset_;
    }

    /**
     * @brief Gets the row offset relative to the 'owner'.
     * @return The row offset.
     */
    [[nodiscard]] std::size_t rowOffset() const {
        return rowOffset_;
    }

    /**
     * @brief Gets the const reference to the DenseMatrix owner.
     * @return Const reference to denseMatrix owner.
     */
    [[nodiscard]] const CSRSparseMatrix<T>& owner() const {
        return owner_;
    }

    [[nodiscard]] std::size_t rows() const {
        return rows_;
    }

    [[nodiscard]] std::size_t columns() const {
        return columns_;
    }

    ~CSRSparseMatrixView() = default;

private:
    const std::size_t colOffset_;
    const std::size_t rowOffset_;
    std::size_t rows_;
    std::size_t columns_;

    const CSRSparseMatrix<T>& owner_;
};
