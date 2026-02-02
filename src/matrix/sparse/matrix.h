#pragma once
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

    virtual ~SparseMatrixBase() = default;
};

template<scalar T>
struct SparseMatrix : SparseMatrixBase<T> {
    int* colOffsets = nullptr;
    int* rowIndices = nullptr;
    T* values = nullptr;
    int nnz = 0;


    SparseMatrix(const int rows, const int columns) : SparseMatrixBase<T>(rows, columns) {
        colOffsets = new int[columns + 1];

        for (int i = 0; i < columns + 1; i++) {
            colOffsets[i] = 0;
        }

        nnz = 0;

        rowIndices = new int[nnz];
        values = new T[nnz];
    }

    SparseMatrix(const SparseMatrix<T>& other) : SparseMatrixBase<T>(other.rows, other.columns) {
        colOffsets = new int[other.colOffsetsSize];
        memcpy(colOffsets, other.colOffsets, (this->columns + 1) * sizeof(int));

        nnz = other.nnz;

        rowIndices = new int[nnz];
        memcpy(rowIndices, other.rowIndices, nnz * sizeof(int));

        values = new T[nnz];
        memcpy(values, other.values, nnz * sizeof(T));
    }

    SparseMatrix(const SparseMatrixBase<T>& other) : SparseMatrixBase<T>(other.rows, other.columns) {
        colOffsets = new int[this->columns + 1];

        for (int i = 0; i < this->columns + 1; i++) {
            colOffsets[i] = 0;
        }

        nnz = 0;

        rowIndices = new int[nnz];
        values = new T[nnz];

        for (int c = 0; c < this->columns; c++) {
            for (int r = 0; r < this->rows; r++) {
                SparseMatrix<T>::set(c, r, other.get(c, r));
            }
        }
    }

    SparseMatrix(SparseMatrix&& other) noexcept {
        colOffsets = other.colOffsets;
        other.colOffsets = nullptr;

        rowIndices = other.rowIndices;
        other.rowIndices = nullptr;

        values = other.values;
        other.values = nullptr;

        nnz = other.nnz;
    }

    void set(const int c, const int r, const T value) override {
        const int start = colOffsets[c];
        const int end = colOffsets[c + 1];

        int i;
        for (i = start; i < end; i++) {
            const int curIndex = rowIndices[i];

            if (curIndex == r) {
                if (compare(value, 0)) {
                    int* newRowIndices = new int[nnz - 1];

                    memcpy(newRowIndices, rowIndices, i * sizeof(T));

                    memcpy(&newRowIndices[i], &rowIndices[i + 1], (nnz - i - 1) * sizeof(T));

                    delete[] rowIndices;

                    rowIndices = newRowIndices;


                    T* newValues = new T[nnz - 1];

                    memcpy(newValues, values, i * sizeof(T));

                    memcpy(&newValues[i], &values[i + 1], (nnz - i - 1) * sizeof(T));

                    delete[] values;

                    values = newValues;

                    // fix column offsets
                    for (int j = c; j < this->columns + 1; j++) {
                        colOffsets[j]--;
                    }

                    nnz--;

                    return;
                }

                values[i] = value;

                return;
            }

            if (curIndex > r) {
                break;
            }
        }

        if (compare(value, 0)) {
            return;
        }

        int* newRowIndices = new int[nnz + 1];

        memcpy(newRowIndices, rowIndices, i * sizeof(T));

        newRowIndices[i] = r;

        memcpy(&newRowIndices[i + 1], &rowIndices[i], (nnz - i) * sizeof(T));

        delete[] rowIndices;

        rowIndices = newRowIndices;


        T* newValues = new T[nnz + 1];

        memcpy(newValues, values, i * sizeof(T));

        newValues[i] = value;

        memcpy(&newValues[i + 1], &values[i], (nnz - i) * sizeof(T));

        delete[] values;

        values = newValues;

        // fix column offsets
        for (int j = c; j < this->columns + 1; j++) {
            colOffsets[j]++;
        }

        nnz++;
    }

    [[nodiscard]] T get(const int c, const int r) const override {
        const int start = colOffsets[c];
        const int end = colOffsets[c + 1];

        for (int i = start; i < end; i++) {
            if (rowIndices[i] == r)
                return values[i];
        }

        return 0;
    }

    ~SparseMatrix() override {
        delete[] colOffsets;
        delete[] rowIndices;
        delete[] values;
    }
};

template<scalar T>
struct SparseMatrixView : SparseMatrixBase<T> {
    SparseMatrix<T>& owner;

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
    SparseMatrixView(const SparseMatrixView<T>& other) : SparseMatrixBase<T>(other.rows, other.columns), owner(other.owner), colOffset_(other.colOffset_), rowOffset_(other.rowOffset_) {}

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
    SparseMatrixView(SparseMatrix<T>& owner, const int rows, const int columns, const int colOffset, const int rowOffset) : SparseMatrixBase<T>(rows, columns), owner(owner), colOffset_(colOffset), rowOffset_(rowOffset) {}

    void set(int c, int r, T value) override {
        owner.set(c + colOffset_, r + rowOffset_, value);
    }

    [[nodiscard]] T get(int c, int r) const override {
        return owner.get(c + colOffset_, r + rowOffset_);
    }

    ~SparseMatrixView() override = default;

private:
    const int colOffset_;
    const int rowOffset_;
};

template<scalar T>
struct CustomSparseMatrix : SparseMatrixBase<T> {
    int*& colOffsets;
    int*& rowIndices;
    T*& values;
    int& nnz;

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
    CustomSparseMatrix(const int rows, const int columns, int*& colOffsets, int*& rowIndices, T*& values, int& nnz) : SparseMatrixBase<T>(rows, columns), colOffsets(colOffsets), rowIndices(rowIndices), values(values), nnz(nnz) {}

    void set(const int c, const int r, const T value) override {
        const int start = colOffsets[c];
        const int end = colOffsets[c + 1];

        int i;
        for (i = start; i < end; i++) {
            const int curIndex = rowIndices[i];

            if (curIndex == r) {
                if (compare(value, 0)) {
                    int* newRowIndices = new int[nnz - 1];

                    memcpy(newRowIndices, rowIndices, i * sizeof(T));

                    memcpy(&newRowIndices[i], &rowIndices[i + 1], (nnz - i - 1) * sizeof(T));

                    delete[] rowIndices;

                    rowIndices = newRowIndices;


                    T* newValues = new T[nnz - 1];

                    memcpy(newValues, values, i * sizeof(T));

                    memcpy(&newValues[i], &values[i + 1], (nnz - i - 1) * sizeof(T));

                    delete[] values;

                    values = newValues;

                    // fix column offsets
                    for (int j = c; j < this->columns + 1; j++) {
                        colOffsets[j]--;
                    }

                    nnz--;

                    return;
                }

                values[i] = value;

                return;
            }

            if (curIndex > r) {
                break;
            }
        }

        if (compare(value, 0)) {
            return;
        }

        int* newRowIndices = new int[nnz + 1];

        memcpy(newRowIndices, rowIndices, i * sizeof(T));

        newRowIndices[i] = r;

        memcpy(&newRowIndices[i + 1], &rowIndices[i], (nnz - i) * sizeof(T));

        delete[] rowIndices;

        rowIndices = newRowIndices;


        T* newValues = new T[nnz + 1];

        memcpy(newValues, values, i * sizeof(T));

        newValues[i] = value;

        memcpy(&newValues[i + 1], &values[i], (nnz - i) * sizeof(T));

        delete[] values;

        values = newValues;

        // fix column offsets
        for (int j = c; j < this->columns + 1; j++) {
            colOffsets[j]++;
        }

        nnz++;
    }

    [[nodiscard]] T get(const int c, const int r) const override {
        const int start = colOffsets[c];
        const int end = colOffsets[c + 1];

        for (int i = start; i < end; i++) {
            if (rowIndices[i] == r)
                return values[i];
        }

        return 0;
    }
};
