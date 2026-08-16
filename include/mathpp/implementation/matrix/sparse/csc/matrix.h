#ifndef MATHPP_IMPLEMENTATION_MATRIX_SPARSE_CSC_MATRIX_H
#define MATHPP_IMPLEMENTATION_MATRIX_SPARSE_CSC_MATRIX_H

#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <tuple>
#include <type_traits>

#include "mathpp/implementation/common/exceptions.h"
#include "mathpp/implementation/common/traits.h"

#include "../common/traits.h"

template<scalar T = float>
struct CSCSparseMatrix {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    CSCSparseMatrix() = delete;

    /**
     * @brief Constructs a SparseMatrix of size 'rows x columns'.
     * Allocates '(columns + 1) * sizeof(std::size_t)' bytes of memory on the heap.
     * @param rows Number of rows.
     * @param columns Number of columns.
     */
    CSCSparseMatrix(const std::size_t rows, const std::size_t columns) : rows_(rows), columns_(columns) {
        colOffsets_ = new std::size_t[columns + 1];

        for (std::size_t i = 0; i < columns + 1; i++) {
            colOffsets_[i] = 0;
        }

        nnz_ = 0;

        rowIndices_ = new std::size_t[nnz_];
        values_ = new T[nnz_];
    }

    /**
     * @brief Constructs a SparseMatrix of size 'rows x columns'.
     * Allocates '(columns + 1) x sizeof(std::size_t) + initializerList.size() x sizeof(std::size_t) + initializerList.size() x sizeof(T)'.
     * @param rows Number of rows.
     * @param columns Number of columns.
     * @param initializerList Initializer list of T, int, std::size_t tuples representing value, column index, row index.
     *
     * @note 'initializerList' must be sorted within each row, and between rows
     */
    CSCSparseMatrix(const std::size_t rows, const std::size_t columns, std::initializer_list<std::tuple<T, int, int> > initializerList) : rows_(rows), columns_(columns) {
        if (rows < 0 || columns < 0) {
            throw InvalidIndexException("Cannot create SparseMatrix with negative size");
        }

        colOffsets_ = new std::size_t[columns + 1];

        for (std::size_t i = 0; i < columns + 1; i++) {
            colOffsets_[i] = 0;
        }

        nnz_ = initializerList.size();

        rowIndices_ = new std::size_t[nnz_];
        values_ = new T[nnz_];

        std::size_t i = 0;
        for (const auto nonZeroElement: initializerList) {
            rowIndices_[i] = std::get<2>(nonZeroElement);
            values_[i] = std::get<0>(nonZeroElement);

            for (std::size_t j = std::get<1>(nonZeroElement) + 1; j < columns + 1; ++j) {
                ++colOffsets_[j];
            }

            ++i;
        }
    }

    /**
     * @brief Copy constructor for SparseMatrix from same type SparseMatrix.
     *
     * Constructs a 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
     * Allocates '(other.columns + 1) * sizeof(std::size_t) + other.nnz * sizeof(std::size_t) + other.nnz * sizeof(T)' bytes on the heap.
     *
     * @param other SparseMatrix to copy from.
     */
    CSCSparseMatrix(const CSCSparseMatrix<T>& other) : rows_(other.rows_), columns_(other.columns_) {
        colOffsets_ = new std::size_t[columns_ + 1];
        std::memcpy(colOffsets_, other.colOffsets_, (columns_ + 1) * sizeof(std::size_t));

        nnz_ = other.nnz_;

        rowIndices_ = new std::size_t[nnz_];
        std::memcpy(rowIndices_, other.rowIndices_, nnz_ * sizeof(std::size_t));

        values_ = new T[nnz_];
        std::memcpy(values_, other.values_, nnz_ * sizeof(T));
    }

    /**
    * @brief Copy constructor for SparseMatrix from different type SparseMatrix.
    *
    * Constructs a 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
    * Allocates '(other.columns + 1) * sizeof(std::size_t) + other.nnz * sizeof(std::size_t) + other.nnz * sizeof(T)' bytes on the heap.
    *
    * @tparam OTHER_T Scalar type of the 'other' SparseMatrix.
    * @param other SparseMatrix to copy from.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    CSCSparseMatrix(const CSCSparseMatrix<OTHER_T>& other) : rows_(other.rows()), columns_(other.columns()) {
        colOffsets_ = new std::size_t[columns_ + 1];

        const std::size_t* otherColOffsets = other.colOffsets();

        std::memcpy(colOffsets_, otherColOffsets, (columns_ + 1) * sizeof(std::size_t));

        const std::size_t otherNnz = other.nnz();

        nnz_ = otherNnz;

        rowIndices_ = new std::size_t[nnz_];

        const std::size_t* otherRowIndices = other.rowIndices();

        std::memcpy(rowIndices_, otherRowIndices, nnz_ * sizeof(std::size_t));

        values_ = new T[nnz_];

        const OTHER_T* otherValues = other.values();

        for (std::size_t i = 0; i < nnz_; i++) {
            values_[i] = otherValues[i];
        }
    }

    template<sparse_matrix_like U>
    CSCSparseMatrix(const U& other) : rows_(other.rows()), columns_(other.columns()) {
        colOffsets_ = new std::size_t[columns_ + 1];

        for (std::size_t i = 0; i < columns_ + 1; i++) {
            colOffsets_[i] = 0;
        }

        nnz_ = 0;

        rowIndices_ = new std::size_t[nnz_];
        values_ = new T[nnz_];

        for (std::size_t c = 0; c < columns_; c++) {
            for (std::size_t r = 0; r < rows_; r++) {
                CSCSparseMatrix<T>::set(c, r, other.get(c, r));
            }
        }
    }

    /**
     * @brief Move constructor for SparseMatrix from same type SparseMatrix.
     *
     * Constructs a 'other.rows' x 'other.columns' matrix and uses the same arrays of 'other'.
     * Does not allocate memory.
     *
     * @param other SparseMatrix to move from.
     */
    CSCSparseMatrix(CSCSparseMatrix&& other) noexcept : rows_(other.rows_), columns_(other.columns_), nnz_(other.nnz_), values_(other.values_), colOffsets_(other.colOffsets_), rowIndices_(other.rowIndices_) {
        other.colOffsets_ = nullptr;
        other.rowIndices_ = nullptr;
        other.values_ = nullptr;
        other.rows_ = 0;
        other.columns_ = 0;
        other.nnz_ = 0;
    }

    /**
     * @brief Copy assignment operator for SparseMatrix from same type SparseMatrix.
     * Replaces all elements with elements of 'other'.
     * May allocate memory if nnz != other.nnz, if not then 'nnz * sizeof(T) + nnz * sizeof(std::size_t)' bytes of memory are allocated on the heap.
     * @param other SparseMatrix to copy from.
     * @return Reference to this.
     * @throws InvalidSizeException If 'other' does not have same dimensions as this.
     * @note 'other' must be of same dimensions as this.
     */
    CSCSparseMatrix<T>& operator=(const CSCSparseMatrix<T>& other) {
        if (this != &other) {
            if (rows_ != other.rows_ || columns_ != other.columns_) {
                delete[] colOffsets_;
                rows_ = other.rows_;
                columns_ = other.columns_;
                colOffsets_ = new std::size_t[columns_ + 1];
            }

            if (nnz_ != other.nnz_) {
                nnz_ = other.nnz_;
                delete[] values_;
                delete[] rowIndices_;
                values_ = new T[nnz_];
                rowIndices_ = new std::size_t[nnz_];
            }

            std::memcpy(values_, other.values_, nnz_ * sizeof(T));
            std::memcpy(rowIndices_, other.rowIndices_, nnz_ * sizeof(std::size_t));
            std::memcpy(colOffsets_, other.colOffsets_, (columns_ + 1) * sizeof(std::size_t));
        }

        return *this;
    }

    /**
     * @brief Copy assignment operator for SparseMatrix from different type SparseMatrix.
     * Replaces all elements with elements of 'other'.
     * May allocate memory if nnz != other.nnz, if not then 'nnz * sizeof(T) + nnz * sizeof(std::size_t)' bytes of memory are allocated on the heap.
     * @param other SparseMatrix to copy from.
     * @return Reference to this.
     * @throws InvalidSizeException If 'other' does not have same dimensions as this.
     * @note 'other' must be of same dimensions as this.
     * @note 'OTHER_T' must be able to implicitly convert to 'T'.
     * @tparam OTHER_T Scalar type of the 'other' SparseMatrix.
     */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    CSCSparseMatrix<T>& operator=(const CSCSparseMatrix<OTHER_T>& other) {
        if (columns_ != other.columns()) {
            delete[] colOffsets_;
            columns_ = other.columns();
            colOffsets_ = new std::size_t[columns_ + 1];
        }

        rows_ = other.rows();

        if (nnz_ != other.nnz()) {
            nnz_ = other.nnz();
            delete[] values_;
            delete[] rowIndices_;
            values_ = new T[nnz_];
            rowIndices_ = new std::size_t[nnz_];
        }

        const OTHER_T* otherValues = other.values();
        for (std::size_t i = 0; i < nnz_; i++) {
            values_[i] = otherValues[i];
        }

        std::memcpy(rowIndices_, other.rowIndices(), nnz_ * sizeof(std::size_t));
        std::memcpy(colOffsets_, other.colOffsets(), (columns_ + 1) * sizeof(std::size_t));

        return *this;
    }

    template<sparse_matrix_like U>
    CSCSparseMatrix<T>& operator=(const U& other) {
        if (columns_ != other.columns()) {
            delete[] colOffsets_;
            columns_ = other.columns();
            colOffsets_ = new std::size_t[columns_ + 1];
        }

        rows_ = other.rows();

        for (std::size_t i = 0; i < columns_ + 1; i++) {
            colOffsets_[i] = 0;
        }

        nnz_ = 0;

        delete[] rowIndices_;
        rowIndices_ = new std::size_t[0];

        delete[] values_;
        values_ = new T[0];

        for (std::size_t c = 0; c < columns_; c++) {
            for (std::size_t r = 0; r < rows_; r++) {
                CSCSparseMatrix<T>::set(c, r, other.get(c, r));
            }
        }

        return *this;
    }

    /**
    * @brief Move assignment operator for SparseMatrix from same type SparseMatrix.
    * Takes ownership of 'other' values, rowIndices, and colOffsets.
    * Does not allocate memory on the heap.
    * @param other SparseMatrix to move from.
    * @return Reference to this.
    * @throws InvalidSizeException If 'other' does not have same dimensions as this.
    * @note 'other' must be of same dimensions as this.
    */
    CSCSparseMatrix<T>& operator=(CSCSparseMatrix<T>&& other) noexcept {
        if (this != &other) {
            delete[] values_;
            delete[] rowIndices_;
            delete[] colOffsets_;

            values_ = other.values_;
            other.values_ = nullptr;
            rowIndices_ = other.rowIndices_;
            other.rowIndices_ = nullptr;
            colOffsets_ = other.colOffsets_;
            other.colOffsets_ = nullptr;

            nnz_ = other.nnz_;
            other.nnz_ = 0;

            rows_ = other.rows_;
            other.rows_ = 0;

            columns_ = other.columns_;
            other.columns_ = 0;
        }
        return *this;
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

                    const std::size_t before_count = i;
                    if (before_count > 0) {
                        std::memcpy(newRowIndices, rowIndices_, before_count * sizeof(std::size_t));
                    }

                    const std::size_t after_count = nnz_ - i - 1;
                    if (after_count > 0) {
                        std::memcpy(newRowIndices + i, rowIndices_ + i + 1, after_count * sizeof(std::size_t));
                    }

                    delete[] rowIndices_;

                    rowIndices_ = newRowIndices;


                    T* newValues = new T[nnz_ - 1];

                    if (before_count > 0) {
                        std::memcpy(newValues, values_, before_count * sizeof(T));
                    }

                    if (after_count > 0) {
                        std::memcpy(newValues + i, values_ + i + 1, after_count * sizeof(T));
                    }

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

        const std::size_t before_count = i;
        if (before_count > 0) {
            std::memcpy(newRowIndices, rowIndices_, before_count * sizeof(std::size_t));
        }

        newRowIndices[i] = r;

        const std::size_t after_count = nnz_ - i;
        if (after_count > 0) {
            std::memcpy(newRowIndices + i + 1, rowIndices_ + i, after_count * sizeof(std::size_t));
        }

        delete[] rowIndices_;

        rowIndices_ = newRowIndices;


        T* newValues = new T[nnz_ + 1];

        if (before_count > 0) {
            std::memcpy(newValues, values_, before_count * sizeof(T));
        }

        newValues[i] = value;

        if (after_count > 0) {
            std::memcpy(newValues + i + 1, values_ + i, after_count * sizeof(T));
        }

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
     * @brief Gets the array containing the column offsets.
     * Always of size 'columns + 1'.
     * @return Pointer to array of column offsets.
     */
    [[nodiscard]] std::size_t* colOffsets() {
        return colOffsets_;
    }

    /**
    * @brief Gets the array containing the column offsets.
    * Always of size 'columns + 1'.
    * @return Const pointer to array of column offsets.
    */
    [[nodiscard]] const std::size_t* colOffsets() const {
        return colOffsets_;
    }

    /**
    * @brief Gets the array containing the row indices.
    * @return Pointer to array of row indices.
    */
    [[nodiscard]] std::size_t* rowIndices() {
        return rowIndices_;
    }

    /**
    * @brief Gets the array containing the row indices.
    * @return Const pointer to array of row indices.
    */
    [[nodiscard]] const std::size_t* rowIndices() const {
        return rowIndices_;
    }

    /**
    * @brief Gets the values pointer storing the matrices non-zero elements.
    * @return Pointer to array of non-zero elements.
    */
    [[nodiscard]] T* values() {
        return values_;
    }

    /**
    * @brief Gets the const values pointer storing the matrices non-zero elements.
    * @return Const pointer to array of non-zero elements.
    */
    [[nodiscard]] const T* values() const {
        return values_;
    }

    [[nodiscard]] std::size_t rows() const {
        return rows_;
    }

    [[nodiscard]] std::size_t columns() const {
        return columns_;
    }

    ~CSCSparseMatrix() {
        delete[] colOffsets_;
        delete[] rowIndices_;
        delete[] values_;
    }

private:
    std::size_t nnz_;
    T* values_;
    std::size_t* colOffsets_;
    std::size_t* rowIndices_;
    std::size_t rows_;
    std::size_t columns_;
};

#endif // MATHPP_IMPLEMENTATION_MATRIX_SPARSE_CSC_MATRIX_H
