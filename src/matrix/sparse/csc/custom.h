#pragma once
#include "../../../helper.h"
#include <cstddef>
#include "../../../exceptions.h"

template<scalar T = float>
struct CSCCustomSparseMatrix {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    CSCCustomSparseMatrix() = delete;

    CSCCustomSparseMatrix(const CSCCustomSparseMatrix<T>& other) = delete;

    CSCCustomSparseMatrix(CSCCustomSparseMatrix<T>&& other) noexcept = delete;

    CSCCustomSparseMatrix<T>& operator=(const CSCCustomSparseMatrix<T>& other) = delete;

    CSCCustomSparseMatrix<T>& operator=(CSCCustomSparseMatrix<T>&& other) noexcept = delete;

    /**
     * Constructs a CustomSparseMatrix from the provided arrays of size 'rows x columns'.
     *
     * CustomSparseMatrix instance does not own 'colOffsets', 'rowIndices', or 'values' arrays.
     * Does allocate memory sometimes when adding or removeing elements.
     * The 'colOffsets', 'rowIndices' and 'values' arrays will be reallocated and what they are pointing to will change.
     *
     * Think of it as a view on an arbitrary data pointer.
     *
    * @param rows Number of rows in matrix.
     * @param columns Number of columns in matrix.
     * @param colOffsets Array of column offsets.
     * @param rowIndices Array of row indices.
     * @param values Array of values.
     * @param nnz Number of non-zero elements (also the length of 'values' and 'rowIndices').
     *
     * @note Assumes csc storage.
     * @note Assumes 'rowIndices' are sorted by column and within each column.
     * @note Assumes 'colOffsets' is of size 'columns + 1'.
     * @note Assumes 'rowIndices' and 'values' is of size 'nnz'.
     */
    CSCCustomSparseMatrix(const std::size_t rows, const std::size_t columns, std::size_t*& colOffsets, std::size_t*& rowIndices, T*& values, std::size_t& nnz) : rows_(rows), columns_(columns), nnz_(nnz), values_(values), colOffsets_(colOffsets), rowIndices_(rowIndices) {
    }

    void set(const std::size_t c, const std::size_t r, const T value) {
        if (c > columns_ - 1 || r > rows_ - 1) {
            throw InvalidIndexException("Cannot set on SparseMatrix with invalid index");
        }
        const std::size_t start = colOffsets_[c];
        const std::size_t end = colOffsets_[c + 1];

        std::size_t i;
        for (i = start; i < end; i++) {
            const std::size_t curIndex = rowIndices_[i];

            if (curIndex == r) {
                if (compare(value, 0)) {
                    std::size_t* newRowIndices = new std::size_t[nnz_ - 1];

                    std::memcpy(newRowIndices, rowIndices_, i * sizeof(std::size_t));

                    std::memcpy(&newRowIndices[i], &rowIndices_[i + 1], (nnz_ - i - 1) * sizeof(std::size_t));

                    delete[] rowIndices_;

                    rowIndices_ = newRowIndices;


                    T* newValues = new T[nnz_ - 1];

                    std::memcpy(newValues, values_, i * sizeof(T));

                    std::memcpy(&newValues[i], &values_[i + 1], (nnz_ - i - 1) * sizeof(T));

                    delete[] values_;

                    values_ = newValues;

                    // fix column offsets
                    for (std::size_t j = c + 1; j < columns_ + 1; j++) {
                        colOffsets_[j]--;
                    }

                    nnz_--;

                    return;
                }

                values_[i] = value;

                return;
            }

            if (curIndex > r) {
                break;
            }
        }

        if (compare(value, 0)) {
            return;
        }

        std::size_t* newRowIndices = new std::size_t[nnz_ + 1];

        std::memcpy(newRowIndices, rowIndices_, i * sizeof(std::size_t));

        newRowIndices[i] = r;

        std::memcpy(&newRowIndices[i + 1], &rowIndices_[i], (nnz_ - i) * sizeof(std::size_t));

        delete[] rowIndices_;

        rowIndices_ = newRowIndices;


        T* newValues = new T[nnz_ + 1];

        std::memcpy(newValues, values_, i * sizeof(T));

        newValues[i] = value;

        std::memcpy(&newValues[i + 1], &values_[i], (nnz_ - i) * sizeof(T));

        delete[] values_;

        values_ = newValues;

        // fix column offsets
        for (std::size_t j = c + 1; j < columns_ + 1; j++) {
            colOffsets_[j]++;
        }

        nnz_++;
    }

    [[nodiscard]] T get(const std::size_t c, const std::size_t r) const {
        if (c > columns_ - 1 || r > rows_ - 1) {
            throw InvalidIndexException("Cannot set on SparseMatrix with invalid index");
        }

        const std::size_t start = colOffsets_[c];
        const std::size_t end = colOffsets_[c + 1];

        for (std::size_t i = start; i < end; i++) {
            if (rowIndices_[i] == r) {
                return values_[i];
            }
        }

        return 0;
    }

    [[nodiscard]] std::size_t nnz() const {
        return nnz_;
    }

    /**
    * @brief Gets the reference to the pointer storing the column offsets.
    * @return Reference to pointer containing the column offsets.
    */
    [[nodiscard]] std::size_t*& colOffsets() {
        return colOffsets_;
    }

    /**
    * @brief Gets the const reference to the const pointer storing the column offsets.
    * @return Const reference to const pointer containing the column offsets.
    */
    [[nodiscard]] const std::size_t* const& colOffsets() const {
        return colOffsets_;
    }

    /**
    * @brief Gets the reference to the pointer storing the row indices.
    * @return Reference to pointer containing the row indices.
    */
    [[nodiscard]] std::size_t*& rowIndices() {
        return rowIndices_;
    }

    /**
    * @brief Gets the const reference to the const pointer storing the row indices.
    * @return Const reference to const pointer containing the row indices.
    */
    [[nodiscard]] const std::size_t* const& rowIndices() const {
        return rowIndices_;
    }

    /**
     * @brief Gets the reference to the pointer storing the matrices non-zero elements.
     * @return Reference to pointer containing non-zero elements.
     */
    [[nodiscard]] T*& values() {
        return values_;
    }

    /**
    * @brief Gets the const reference to the const pointer storing the matrices non-zero elements.
    * @return Const reference to const pointer containing non-zero elements.
    */
    [[nodiscard]] const T* const& values() const {
        return values_;
    }

    [[nodiscard]] std::size_t rows() const {
        return rows_;
    }

    [[nodiscard]] std::size_t columns() const {
        return columns_;
    }

private:
    std::size_t& nnz_;
    T*& values_;
    std::size_t*& colOffsets_;
    std::size_t*& rowIndices_;
    std::size_t rows_;
    std::size_t columns_;
};
