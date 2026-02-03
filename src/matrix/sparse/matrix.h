#pragma once
#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T>
struct SparseMatrixBase {
    const int rows;
    const int columns;

    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    SparseMatrixBase() = delete;
    SparseMatrixBase(const SparseMatrixBase<T>& other) = delete;
    SparseMatrixBase(SparseMatrixBase&& other) noexcept = delete;

protected:
    /**
    * @brief Initializes the size of the matrix.
    *
    * Internal constructor that initializes the 'rows' and 'columns' fields.
    * Does not allocate memory for matrix elements.
    *
    * @param rows Number of rows.
    * @param columns Number of columns.
    */
    SparseMatrixBase(const int rows, const int columns) : rows(rows), columns(columns) {}

public:
    /**
     * @brief Sets the value of the element at column 'c' and row 'r'.
     *
     * @param c Column index.
     * @param r Row index.
     * @param value The value to set at 'c, r'.
     */
    virtual void set(int c, int r, T value) = 0;

    /**
     * @brief Gets the value of the element at column 'c' and row 'r'.
     * @param c Column index.
     * @param r Row index.
     * @return The value at 'c, r'.
     */
    [[nodiscard]] virtual T get(int c, int r) const = 0;

    [[nodiscard]] virtual int nnz() const = 0;

    virtual ~SparseMatrixBase() = default;
};

template<scalar T>
struct SparseMatrix : SparseMatrixBase<T> {
    SparseMatrix(const int rows, const int columns) : SparseMatrixBase<T>(rows, columns) {
        colOffsets_ = new int[columns + 1];

        for (int i = 0; i < columns + 1; i++) {
            colOffsets_[i] = 0;
        }

        nnz_ = 0;

        rowIndices_ = new int[nnz_];
        values_ = new T[nnz_];
    }

    SparseMatrix(const SparseMatrix<T>& other) : SparseMatrixBase<T>(other.rows, other.columns) {
        colOffsets_ = new int[other.colOffsetsSize];
        memcpy(colOffsets_, other.colOffsets_, (this->columns + 1) * sizeof(int));

        nnz_ = other.nnz_;

        rowIndices_ = new int[nnz_];
        memcpy(rowIndices_, other.rowIndices_, nnz_ * sizeof(int));

        values_ = new T[nnz_];
        memcpy(values_, other.values_, nnz_ * sizeof(T));
    }

    SparseMatrix(const SparseMatrixBase<T>& other) : SparseMatrixBase<T>(other.rows, other.columns) {
        colOffsets_ = new int[this->columns + 1];

        for (int i = 0; i < this->columns + 1; i++) {
            colOffsets_[i] = 0;
        }

        nnz_ = 0;

        rowIndices_ = new int[nnz_];
        values_ = new T[nnz_];

        for (int c = 0; c < this->columns; c++) {
            for (int r = 0; r < this->rows; r++) {
                SparseMatrix<T>::set(c, r, other.get(c, r));
            }
        }
    }

    SparseMatrix(SparseMatrix&& other) noexcept {
        colOffsets_ = other.colOffsets_;
        other.colOffsets_ = nullptr;

        rowIndices_ = other.rowIndices_;
        other.rowIndices_ = nullptr;

        values_ = other.values_;
        other.values_ = nullptr;

        nnz_ = other.nnz_;
    }

    void set(const int c, const int r, const T value) override {
        const int start = colOffsets_[c];
        const int end = colOffsets_[c + 1];

        int i;
        for (i = start; i < end; i++) {
            const int curIndex = rowIndices_[i];

            if (curIndex == r) {
                if (compare(value, 0)) {
                    int* newRowIndices = new int[nnz_ - 1];

                    memcpy(newRowIndices, rowIndices_, i * sizeof(T));

                    memcpy(&newRowIndices[i], &rowIndices_[i + 1], (nnz_ - i - 1) * sizeof(T));

                    delete[] rowIndices_;

                    rowIndices_ = newRowIndices;


                    T* newValues = new T[nnz_ - 1];

                    memcpy(newValues, values_, i * sizeof(T));

                    memcpy(&newValues[i], &values_[i + 1], (nnz_ - i - 1) * sizeof(T));

                    delete[] values_;

                    values_ = newValues;

                    // fix column offsets
                    for (int j = c; j < this->columns + 1; j++) {
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

        int* newRowIndices = new int[nnz_ + 1];

        memcpy(newRowIndices, rowIndices_, i * sizeof(T));

        newRowIndices[i] = r;

        memcpy(&newRowIndices[i + 1], &rowIndices_[i], (nnz_ - i) * sizeof(T));

        delete[] rowIndices_;

        rowIndices_ = newRowIndices;


        T* newValues = new T[nnz_ + 1];

        memcpy(newValues, values_, i * sizeof(T));

        newValues[i] = value;

        memcpy(&newValues[i + 1], &values_[i], (nnz_ - i) * sizeof(T));

        delete[] values_;

        values_ = newValues;

        // fix column offsets
        for (int j = c; j < this->columns + 1; j++) {
            colOffsets_[j]++;
        }

        nnz_++;
    }

    [[nodiscard]] T get(const int c, const int r) const override {
        const int start = colOffsets_[c];
        const int end = colOffsets_[c + 1];

        for (int i = start; i < end; i++) {
            if (rowIndices_[i] == r)
                return values_[i];
        }

        return 0;
    }

    [[nodiscard]] int nnz() const override {
        return nnz_;
    }

    [[nodiscard]] int* colOffsets() {
        return colOffsets_;
    }

    [[nodiscard]] const int* colOffsets() const {
        return colOffsets_;
    }

    [[nodiscard]] int* rowIndices() {
        return rowIndices_;
    }

    [[nodiscard]] const int* rowIndices() const {
        return rowIndices_;
    }

    [[nodiscard]] T* values() {
        return values_;
    }

    [[nodiscard]] const T* values() const {
        return values_;
    }

    ~SparseMatrix() override {
        delete[] colOffsets_;
        delete[] rowIndices_;
        delete[] values_;
    }

private:
    int* colOffsets_;
    int* rowIndices_;
    T* values_;
    int nnz_;
};

template<scalar T>
struct SparseMatrixView : SparseMatrixBase<T> {
    SparseMatrixView() = delete;

    SparseMatrixView(SparseMatrixView<T>&& other) noexcept = delete;

    /**
     * @brief Copy constructor for SparseMatrixView.
     *
     * Constructs a view with the same 'owner' as 'other'.
     * Does not allocate new memory.
     *
     * @param other SparseMatrixView to copy from.
     */
    SparseMatrixView(const SparseMatrixView<T>& other) : SparseMatrixBase<T>(other.rows, other.columns), colOffset_(other.colOffset_), rowOffset_(other.rowOffset_), owner_(other.owner_) {}

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
    SparseMatrixView(const SparseMatrix<T>& owner, const int rows, const int columns, const int colOffset, const int rowOffset) : SparseMatrixBase<T>(rows, columns), colOffset_(colOffset), rowOffset_(rowOffset), owner_(owner) {}

    /**
    * @brief Trying to modify a SparseMatrix through a view is invalid.
    * @throws InvalidOperation You cannot modify owner through a view.
    */
    void set(const int, const int, const T) override {
        throw InvalidOperation("Cannot modify owner through view");
    }

    [[nodiscard]] T get(const int c, const int r) const override {
        return owner_.get(c + colOffset_, r + rowOffset_);
    }

    [[nodiscard]] int nnz() const override {
        int nnz = 0;

        for (int c = colOffset_; c < colOffset_ + this->columns; c++) {
            const int start = owner().colOffsets()[c];
            const int end = owner().colOffsets()[c + 1];

            for (int r = start; r < end; r++) {
                const int curIndex = owner().rowIndices()[r];

                if (curIndex >= rowOffset_ && curIndex < rowOffset_ + this->rows) {
                    nnz++;
                }
            }
        }

        return nnz;
    }

    [[nodiscard]] const SparseMatrix<T>& owner() const {
        return owner_;
    }

    ~SparseMatrixView() override = default;

private:
    const int colOffset_;
    const int rowOffset_;

    const SparseMatrix<T>& owner_;
};

template<scalar T>
struct CustomSparseMatrix : SparseMatrixBase<T> {
    CustomSparseMatrix() = delete;
    CustomSparseMatrix(const CustomSparseMatrix<T>& other) = delete;
    CustomSparseMatrix(CustomSparseMatrix<T>&& other) noexcept = delete;

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
    CustomSparseMatrix(const int rows, const int columns, int*& colOffsets, int*& rowIndices, T*& values, int& nnz) : SparseMatrixBase<T>(rows, columns), colOffsets_(colOffsets), rowIndices_(rowIndices), values_(values), nnz_(nnz) {}

    void set(const int c, const int r, const T value) override {
        const int start = colOffsets_[c];
        const int end = colOffsets_[c + 1];

        int i;
        for (i = start; i < end; i++) {
            const int curIndex = rowIndices_[i];

            if (curIndex == r) {
                if (compare(value, 0)) {
                    int* newRowIndices = new int[nnz_ - 1];

                    memcpy(newRowIndices, rowIndices_, i * sizeof(T));

                    memcpy(&newRowIndices[i], &rowIndices_[i + 1], (nnz_ - i - 1) * sizeof(T));

                    delete[] rowIndices_;

                    rowIndices_ = newRowIndices;


                    T* newValues = new T[nnz_ - 1];

                    memcpy(newValues, values_, i * sizeof(T));

                    memcpy(&newValues[i], &values_[i + 1], (nnz_ - i - 1) * sizeof(T));

                    delete[] values_;

                    values_ = newValues;

                    // fix column offsets
                    for (int j = c; j < this->columns + 1; j++) {
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

        int* newRowIndices = new int[nnz_ + 1];

        memcpy(newRowIndices, rowIndices_, i * sizeof(T));

        newRowIndices[i] = r;

        memcpy(&newRowIndices[i + 1], &rowIndices_[i], (nnz_ - i) * sizeof(T));

        delete[] rowIndices_;

        rowIndices_ = newRowIndices;


        T* newValues = new T[nnz_ + 1];

        memcpy(newValues, values_, i * sizeof(T));

        newValues[i] = value;

        memcpy(&newValues[i + 1], &values_[i], (nnz_ - i) * sizeof(T));

        delete[] values_;

        values_ = newValues;

        // fix column offsets
        for (int j = c; j < this->columns + 1; j++) {
            colOffsets_[j]++;
        }

        nnz_++;
    }

    [[nodiscard]] int nnz() const override {
        return nnz_;
    }

    [[nodiscard]] int*& colOffsets() {
        return colOffsets_;
    }

    [[nodiscard]] int* const& colOffsets() const {
        return colOffsets_;
    }

    [[nodiscard]] int*& rowIndices() {
        return rowIndices_;
    }

    [[nodiscard]] int* const& rowIndices() const {
        return rowIndices_;
    }

    [[nodiscard]] T*& values() {
        return values_;
    }

    [[nodiscard]] T* const& values() const {
        return values_;
    }

    [[nodiscard]] T get(const int c, const int r) const override {
        const int start = colOffsets_[c];
        const int end = colOffsets_[c + 1];

        for (int i = start; i < end; i++) {
            if (rowIndices_[i] == r)
                return values_[i];
        }

        return 0;
    }
private:
    int*& colOffsets_;
    int*& rowIndices_;
    T*& values_;
    int& nnz_;
};
