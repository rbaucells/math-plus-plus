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
    virtual void set(int c, int r, T value) = 0;
    [[nodiscard]] virtual T get(int c, int r) const = 0;

    virtual ~SparseMatrixBase() = default;
};

template<scalar T>
struct SparseMatrix : SparseMatrixBase<T> {
    int* colOffsets = nullptr;
    int colOffsetsSize = 0;
    int* rowIndices = nullptr;
    int rowIndicesSize = 0;
    T* values = nullptr;
    int valuesSize = 0;

    SparseMatrix(const int rows, const int columns) : SparseMatrixBase<T>(rows, columns) {
        colOffsets = new int[0];
        rowIndices = new int[0];
        values = new T[0];
    }

    SparseMatrix(const SparseMatrix<T>& other) : SparseMatrixBase<T>(other.rows, other.columns) {
        colOffsets = new int[other.colOffsetsSize];
        colOffsetsSize = other.colOffsetsSize;

        memcpy(colOffsets, other.colOffsets, colOffsetsSize * sizeof(int));

        rowIndices = new int[other.rowIndicesSize];
        rowIndicesSize = other.rowIndicesSize;

        memcpy(rowIndices, other.rowIndices, rowIndicesSize * sizeof(int));

        values = new T[other.values];
        valuesSize = other.valuesSize;

        memcpy(values, other.values, valuesSize * sizeof(T));
    }

    SparseMatrix(const SparseMatrixBase<T>& other) : SparseMatrixBase<T>(other.rows, other.columns) {
        for (int c = 0; c < this->columns; c++) {
            for (int r = 0; r < this->rows; r++) {
                SparseMatrix<T>::set(c, r, other.get(c, r));
            }
        }
    }

    SparseMatrix(SparseMatrix&& other) noexcept {
        colOffsets = other.colOffsets;
        other.colOffsets = nullptr;
        colOffsetsSize = other.colOffsetsSize;

        rowIndices = other.rowIndices;
        other.rowIndices = nullptr;
        rowIndicesSize = other.rowIndicesSize;

        values = other.values;
        other.values = nullptr;
        valuesSize = other.valuesSize;
    }

    void set(const int c, const int r, const T value) override {
        const int start = colOffsets[c];
        const int end = colOffsets[c + 1];

        for (int i = start; i < end; i++) {
            const int curRowIndex = rowIndices[i];
            // there is alr a non-zero element there
            if (curRowIndex == r) {
                if (compare(value, 0)) {
                    // first resize the rowIndices
                    const int newRowIndicesSize = rowIndicesSize - 1;
                    int* newRowIndices = new int[rowIndicesSize - 1];

                    // copy all the indices before the new index we are about to remove
                    memcpy(newRowIndices, rowIndices, i * sizeof(T));

                    // copy the rest of the indices
                    memcpy(&newRowIndices[i], &rowIndices[i + 1], rowIndicesSize - (i + 1));

                    delete[] rowIndices;

                    rowIndicesSize = newRowIndicesSize;
                    rowIndices = newRowIndices;

                    // now we need to fix the column offsets indices
                    for (int j = c + 1; j < colOffsetsSize; j++) {
                        colOffsets[j]--;
                    }

                    // now set the actual value
                    const int newValuesSize = valuesSize - 1;
                    int* newValues = new int[valuesSize - 1];

                    // copy all the indices before the new index we are about to remove
                    memcpy(newValues, values, i * sizeof(T));

                    // copy the rest of the indices
                    memcpy(&newValues[i], &values[i + 1], valuesSize - (i + 1));

                    delete[] values;

                    valuesSize = newValuesSize;
                    values = newValues;
                }
                else {
                    values[i] = value;
                }
                return;
            }

            // if rowIndices[i] > r, that means we passed r already (since its sorted), that means there is currently a zero there
            if (curRowIndex > r) {
                if (compare(value, 0))
                    return;

                // first resize the rowIndices and place the value
                const int newRowIndicesSize = rowIndicesSize + 1;
                int* newRowIndices = new int[rowIndicesSize + 1];

                // copy all the indices before the new index we are about to put
                memcpy(newRowIndices, rowIndices, i * sizeof(T));

                newRowIndices[i] = r;

                // copy the rest of the indices
                memcpy(&newRowIndices[i + 1], &rowIndices[i], rowIndicesSize - i);

                delete[] rowIndices;

                rowIndicesSize = newRowIndicesSize;
                rowIndices = newRowIndices;

                // now we need to fix the column offsets indices
                for (int j = c + 1; j < colOffsetsSize; j++) {
                    colOffsets[j]++;
                }

                // now set the actual value
                const int newValuesSize = valuesSize + 1;
                int* newValues = new int[valuesSize + 1];

                // copy all the indices before the new index we are about to put
                memcpy(newValues, values, i * sizeof(T));

                newValues[i] = value;

                // copy the rest of the indices
                memcpy(&newValues[i + 1], &values[i], valuesSize - i);

                delete[] values;

                valuesSize = newValuesSize;
                values = newValues;
            }
        }
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
     * @brief Copy constructor for SparseMatrixView
     *
     * Constructs a view with the same 'owner' as 'other'.
     * Does not allocate new memory.
     *
     * @param other SparseMatrixView to copy from
     */
    SparseMatrixView(const SparseMatrixView<T>& other) : SparseMatrixBase<T>(other.rows, other.columns), owner(other.owner), colOffset_(other.colOffset_), rowOffset_(other.rowOffset_) {}

    /**
     * @brief Constructs a SparseMatrixView into an existing SparseMatrix.
     *
     * Creates a view of size `rows x columns` into the `owner` matrix,
     * starting at the colOffset and rowOffset.
     * Does not allocate new memory.
     * The view holds a const pointer to the owner.
     *
     * @param owner SparseMatrix to create a view from.
     * @param rows Number of rows in the view.
     * @param columns Number of columns in the view.
     * @param colOffset Starting column offset in the owner matrix.
     * @param rowOffset Starting row offset in the owner matrix.
     */
    SparseMatrixView(SparseMatrix<T>& owner, const int rows, const int columns, const int colOffset, const int rowOffset) : SparseMatrixBase<T>(rows, columns), owner(owner), colOffset_(colOffset), rowOffset_(rowOffset) {}

    void set(int c, int r, T value) override {
        owner.set(c, r, value);
    }

    [[nodiscard]] T get(int c, int r) const override {
        return owner.get(c, r);
    }

    ~SparseMatrixView() override = default;

private:
    const int colOffset_;
    const int rowOffset_;
};

template<scalar T>
struct CustomSparseMatrix : SparseMatrixBase<T> {
    int*& colOffsets;
    int colOffsetsSize = 0;
    int*& rowIndices;
    int rowIndicesSize = 0;
    T*& values;
    int valuesSize = 0;

    CustomSparseMatrix() = delete;
    CustomSparseMatrix(const CustomSparseMatrix<T>& other) = delete;
    CustomSparseMatrix(CustomSparseMatrix<T>&& other) noexcept = delete;

    /**
     * Constructs a CustomSparseMatrix from the provided arrays of size 'rows x columns'
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
     * @param colOffsetsSize Length of 'colOffsets'.
     * @param rowIndices Array of row indices.
     * @param rowIndicesSize Length of 'rowIndices'.
     * @param values Array of values.
     * @param valuesSize Length of 'values'.
     *
     * @note Assumes csc storage.
     * @note Assumes rowIndices are sorted by column and within each column
     */
    CustomSparseMatrix(const int rows, const int columns, int*& colOffsets, const int colOffsetsSize, int*& rowIndices, const int rowIndicesSize, T*& values, const int valuesSize) : SparseMatrixBase<T>(rows, columns), colOffsets(colOffsets), colOffsetsSize(colOffsetsSize), rowIndices(rowIndices), rowIndicesSize(rowIndicesSize), values(values), valuesSize(valuesSize) {}

    void set(const int c, const int r, T value) override {
        const int start = colOffsets[c];
        const int end = colOffsets[c + 1];

        for (int i = start; i < end; i++) {
            const int curRowIndex = rowIndices[i];
            // there is alr a non-zero element there
            if (curRowIndex == r) {
                if (compare(value, 0)) {
                    // first resize the rowIndices
                    const int newRowIndicesSize = rowIndicesSize - 1;
                    int* newRowIndices = new int[rowIndicesSize - 1];

                    // copy all the indices before the new index we are about to remove
                    memcpy(newRowIndices, rowIndices, i * sizeof(T));

                    // copy the rest of the indices
                    memcpy(&newRowIndices[i], &rowIndices[i + 1], rowIndicesSize - (i + 1));

                    delete[] rowIndices;

                    rowIndicesSize = newRowIndicesSize;
                    rowIndices = newRowIndices;

                    // now we need to fix the column offsets indices
                    for (int j = c + 1; j < colOffsetsSize; j++) {
                        colOffsets[j]--;
                    }

                    // now set the actual value
                    const int newValuesSize = valuesSize - 1;
                    int* newValues = new int[valuesSize - 1];

                    // copy all the indices before the new index we are about to remove
                    memcpy(newValues, values, i * sizeof(T));

                    // copy the rest of the indices
                    memcpy(&newValues[i], &values[i + 1], valuesSize - (i + 1));

                    delete[] values;

                    valuesSize = newValuesSize;
                    values = newValues;
                }
                else {
                    values[i] = value;
                }
                return;
            }

            // if rowIndices[i] > r, that means we passed r already (since its sorted), that means there is currently a zero there
            if (curRowIndex > r) {
                if (compare(value, 0))
                    return;

                // first resize the rowIndices and place the value
                const int newRowIndicesSize = rowIndicesSize + 1;
                int* newRowIndices = new int[rowIndicesSize + 1];

                // copy all the indices before the new index we are about to put
                memcpy(newRowIndices, rowIndices, i * sizeof(T));

                newRowIndices[i] = r;

                // copy the rest of the indices
                memcpy(&newRowIndices[i + 1], &rowIndices[i], rowIndicesSize - i);

                delete[] rowIndices;

                rowIndicesSize = newRowIndicesSize;
                rowIndices = newRowIndices;

                // now we need to fix the column offsets indices
                for (int j = c + 1; j < colOffsetsSize; j++) {
                    colOffsets[j]++;
                }

                // now set the actual value
                const int newValuesSize = valuesSize + 1;
                int* newValues = new int[valuesSize + 1];

                // copy all the indices before the new index we are about to put
                memcpy(newValues, values, i * sizeof(T));

                newValues[i] = value;

                // copy the rest of the indices
                memcpy(&newValues[i + 1], &values[i], valuesSize - i);

                delete[] values;

                valuesSize = newValuesSize;
                values = newValues;
            }
        }
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
