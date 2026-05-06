#pragma once
#include "../../helper.h"
#include <cstddef>
#include "helper.h"
#include "../../exceptions.h"

template<dense_matrix_like T>
struct DenseMatrixView {
    using ValueType = T::ValueType;
    using UnderlyingType = underlying_type_t<typename T::ValueType>;

    static constexpr bool isComplex = is_complex_v<typename T::ValueType>;

    DenseMatrixView() = delete;

    DenseMatrixView(DenseMatrixView<T>&& other) noexcept = delete;

    DenseMatrixView<T>& operator=(const DenseMatrixView<T>& other) = delete;

    DenseMatrixView<T>& operator=(DenseMatrixView<T>&& other) noexcept = delete;

    /**
     * @brief Constructs a DenseMatrixView into an existing dense matrix like.
     *
     * Creates a view of size `rows x columns` into the `owner` matrix,
     * starting at the colOffset and rowOffset.
     * Does not allocate new memory.
     * The view holds a reference to the owner.
     *
     * @param owner DenseMatrix to create a view from.
     * @param rows Number of rows in the view.
     * @param columns Number of columns in the view.
     * @param colOffset Starting column offset in the owner matrix.
     * @param rowOffset Starting row offset in the owner matrix.
     */
    DenseMatrixView(const T& owner, const std::size_t rows, const std::size_t columns, const std::size_t colOffset, const std::size_t rowOffset) : rows_(rows), columns_(columns), colOffset_(colOffset), rowOffset_(rowOffset), owner_(owner) {
    }


    /**
     * @brief Copy constructor for DenseMatrixView.
     *
     * Constructs a view with the same 'owner' as 'other'.
     * Does not allocate new memory.
     *
     * @param other DenseMatrixView to copy from.
     */
    DenseMatrixView(const DenseMatrixView<T>& other) : rows_(other.rows_), columns_(other.columns_), colOffset_(other.colOffset_), rowOffset_(other.rowOffset_), owner_(other.owner_) {
    }

    /**
     * @brief Trying to modify a DenseMatrix through a view is invalid.
     * @throws InvalidOperationException You cannot modify owner through a view.
     */
    [[nodiscard]] T::ValueType& at(const std::size_t, const std::size_t) {
        throw InvalidOperationException("Cannot modify owner through view");
    }

    [[nodiscard]] const T::ValueType& at(const std::size_t r, const std::size_t c) const {
        return owner_.at(r + rowOffset_, c + colOffset_);
    }

    [[nodiscard]] T::ValueType& operator[](const std::size_t r, const std::size_t c) {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return at(r, c);
    }

    [[nodiscard]] const T::ValueType& operator[](const std::size_t r, const std::size_t c) const {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return at(r, c);
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

    [[nodiscard]] std::size_t rows() const {
        return rows_;
    }

    [[nodiscard]] std::size_t columns() const {
        return columns_;
    }

    /**
     * @brief Gets the const reference to the DenseMatrix owner.
     * @return Const reference to denseMatrix owner.
     */
    [[nodiscard]] const T& owner() const {
        return owner_;
    }

    ~DenseMatrixView() = default;

private:
    std::size_t rows_;
    std::size_t columns_;
    const std::size_t colOffset_;
    const std::size_t rowOffset_;

    const T& owner_;
};