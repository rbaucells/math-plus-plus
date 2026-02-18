#pragma once
#include "helper.h"

#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T = float>
struct SparseMatrixBase {
    const int rows;
    const int columns;

    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

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

    /**
     * @brief Gets the number of non-zero elements in the sparse matrix.
     * @return Number of non-zero elements.
     */
    [[nodiscard]] virtual int nnz() const = 0;

    virtual ~SparseMatrixBase() = default;
};

template<scalar T = float>
struct SparseMatrix : SparseMatrixBase<T> {
    SparseMatrix() = delete;

    /**
     * @brief Constructs a SparseMatrix of size 'rows x columns'.
     * Allocates '(columns + 1) * sizeof(int)' bytes of memory on the heap.
     * @param rows Number of rows.
     * @param columns Number of columns.
     */
    SparseMatrix(const int rows, const int columns) : SparseMatrixBase<T>(rows, columns) {
        colOffsets_ = new int[columns + 1];

        for (int i = 0; i < columns + 1; i++) {
            colOffsets_[i] = 0;
        }

        nnz_ = 0;

        rowIndices_ = new int[nnz_];
        values_ = new T[nnz_];
    }

    /**
     * @brief Copy constructor for SparseMatrix from same type SparseMatrix.
     *
     * Constructs a 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
     * Allocates '(other.columns + 1) * sizeof(int) + other.nnz * sizeof(int) + other.nnz * sizeof(T)' bytes on the heap.
     *
     * @param other SparseMatrix to copy from.
     */
    SparseMatrix(const SparseMatrix<T>& other) : SparseMatrixBase<T>(other.rows, other.columns) {
        colOffsets_ = new int[this->columns + 1];
        memcpy(colOffsets_, other.colOffsets_, (this->columns + 1) * sizeof(int));

        nnz_ = other.nnz_;

        rowIndices_ = new int[nnz_];
        memcpy(rowIndices_, other.rowIndices_, nnz_ * sizeof(int));

        values_ = new T[nnz_];
        memcpy(values_, other.values_, nnz_ * sizeof(T));
    }

    /**
    * @brief Copy constructor for SparseMatrix from different type SparseMatrix.
    *
    * Constructs a 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
    * Allocates '(other.columns + 1) * sizeof(int) + other.nnz * sizeof(int) + other.nnz * sizeof(T)' bytes on the heap.
    *
    * @tparam OTHER_T Scalar type of the 'other' SparseMatrix.
    * @param other SparseMatrix to copy from.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    SparseMatrix(const SparseMatrix<OTHER_T>& other) : SparseMatrixBase<T>(other.rows, other.columns) {
        colOffsets_ = new int[this->columns + 1];

        const int* otherColOffsets = other.colOffsets();

        memcpy(colOffsets_, otherColOffsets, (this->columns + 1) * sizeof(int));

        const int otherNnz = other.nnz();

        nnz_ = otherNnz;

        rowIndices_ = new int[nnz_];

        const int* otherRowIndices = other.rowIndices();

        memcpy(rowIndices_, otherRowIndices, nnz_ * sizeof(int));

        values_ = new T[nnz_];

        const OTHER_T* otherValues = other.values();

        for (int i = 0; i < nnz_; i++) {
            values_[i] = otherValues[i];
        }
    }

    /**
     * @brief Copy constructor for SparseMatrix from same type SparseMatrixBase.
     *
     * Constructs a 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
     * Allocates '(columns + 1) * sizeof(int) + other.nnz * sizeof(int) + other.nnz * sizeof(T)' bytes on the heap.
     *
     * @param other SparseMatrixBase to copy from.
     */
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

    /**
     * @brief Copy constructor for SparseMatrix from different type SparseMatrixBase.
     *
     * Constructs a 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
     * Allocates '(columns + 1) * sizeof(int) + other.nnz * sizeof(int) + other.nnz * sizeof(T)' bytes on the heap.
     *
     * @tparam OTHER_T Scalar type of the 'other' SparseMatrixBase.
     * @param other SparseMatrixBase to copy from.
     * @note 'OTHER_T' must be able to implicitly convert to 'T'.
     */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    SparseMatrix(const SparseMatrixBase<OTHER_T>& other) : SparseMatrixBase<T>(other.rows, other.columns) {
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

    /**
     * @brief Move constructor for SparseMatrix from same type SparseMatrix.
     *
     * Constructs a 'other.rows' x 'other.columns' matrix and uses the same arrays of 'other'.
     * Does not allocate memory.
     *
     * @param other SparseMatrix to move from.
     */
    SparseMatrix(SparseMatrix&& other) noexcept : SparseMatrixBase<T>(other.rows, other.columns) {
        colOffsets_ = other.colOffsets_;
        other.colOffsets_ = nullptr;

        rowIndices_ = other.rowIndices_;
        other.rowIndices_ = nullptr;

        values_ = other.values_;
        other.values_ = nullptr;

        nnz_ = other.nnz_;
    }

    /**
     * @brief Copy assignment operator for SparseMatrix from same type SparseMatrix.
     * Replaces all elements with elements of 'other'.
     * May allocate memory if nnz != other.nnz, if not then 'nnz * sizeof(T) + nnz * sizeof(int)' bytes of memory are allocated on the heap.
     * @param other SparseMatrix to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same dimensions as this.
     * @note 'other' must be of same dimensions as this.
     */
    SparseMatrix<T>& operator=(const SparseMatrix<T>& other) {
        assert_same_dimensions(*this, other, "copy assign");

        if (values_ != other.values_ && colOffsets_ != other.colOffsets_ && rowIndices_ != other.rowIndices_) {
            if (nnz_ != other.nnz_) {
                nnz_ = other.nnz_;

                delete[] values_;
                values_ = new T[nnz_];

                delete[] rowIndices_;
                rowIndices_ = new int[nnz_];
            }

            memcpy(values_, other.values_, nnz_ * sizeof(T));
            memcpy(rowIndices_, other.rowIndices_, nnz_ * sizeof(int));
            memcpy(colOffsets_, other.colOffsets_, (this->columns + 1) * sizeof(int));
        }

        return *this;
    }

    /**
     * @brief Copy assignment operator for SparseMatrix from different type SparseMatrix.
     * Replaces all elements with elements of 'other'.
     * May allocate memory if nnz != other.nnz, if not then 'nnz * sizeof(T) + nnz * sizeof(int)' bytes of memory are allocated on the heap.
     * @param other SparseMatrix to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same dimensions as this.
     * @note 'other' must be of same dimensions as this.
     * @note 'OTHER_T' must be able to implicitly convert to 'T'.
     * @tparam OTHER_T Scalar type of the 'other' SparseMatrix.
     */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    SparseMatrix<T>& operator=(const SparseMatrix<OTHER_T>& other) {
        assert_same_dimensions(*this, other, "copy assign");

        const int* otherColOffsets = other.colOffsets();
        const int* otherRowIndices = other.rowIndices();

        const OTHER_T* otherValues = other.values();

        const int otherNnz = other.nnz();

        if (colOffsets_ != otherColOffsets && rowIndices_ != otherRowIndices) {
            if (nnz_ != otherNnz) {
                nnz_ = otherNnz;

                delete[] values_;
                values_ = new T[nnz_];

                delete[] rowIndices_;
                rowIndices_ = new int[nnz_];
            }

            for (int i = 0; i < nnz_; i++) {
                values_[i] = otherValues[i];
            }

            memcpy(rowIndices_, otherRowIndices, nnz_ * sizeof(int));
            memcpy(colOffsets_, otherColOffsets, (this->columns + 1) * sizeof(int));
        }

        return *this;
    }

    /**
     * @brief Copy assignment operator for DenseMatrix from same type SparseMatrixBase.
     * Replaces all elements with elements of 'other'.
     * Allocates 'other.nnz * sizeof(T) + other.nnz * sizeof(int)' bytes of memory on the heap.
     * @param other SparseMatrixBase to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same dimensions as this.
     * @note 'other' must be of same dimensions as this.
     */
    SparseMatrix<T>& operator=(const SparseMatrixBase<T>& other) {
        assert_same_dimensions(*this, other, "copy assign");

        for (int i = 0; i < this->columns + 1; i++) {
            colOffsets_[i] = 0;
        }

        nnz_ = 0;

        delete[] rowIndices_;
        rowIndices_ = new int[nnz_];

        delete[] values_;
        values_ = new T[nnz_];

        for (int c = 0; c < this->columns; c++) {
            for (int r = 0; r < this->columns; r++) {
                SparseMatrix<T>::set(c, r, other.get(c, r));
            }
        }

        return *this;
    }

    /**
     * @brief Copy assignment operator for DenseMatrix from different type SparseMatrixBase.
     * Replaces all elements with elements of 'other'.
     * Allocates 'other.nnz * sizeof(T) + other.nnz * sizeof(int)' bytes of memory on the heap.
     * @param other SparseMatrixBase to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same dimensions as this.
     * @note 'other' must be of same dimensions as this.
     * @note 'OTHER_T' must be able to implicitly convert to 'T'.
     * @tparam OTHER_T Scalar type of the 'other' SparseMatrixBase.
     */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    SparseMatrix<T>& operator=(const SparseMatrixBase<OTHER_T>& other) {
        assert_same_dimensions(*this, other, "copy assign");

        for (int i = 0; i < this->columns + 1; i++) {
            colOffsets_[i] = 0;
        }

        nnz_ = 0;

        delete[] rowIndices_;
        rowIndices_ = new int[nnz_];

        delete[] values_;
        values_ = new T[nnz_];

        for (int c = 0; c < this->columns; c++) {
            for (int r = 0; r < this->columns; r++) {
                SparseMatrix<T>::set(c, r, other.get(c, r));
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
    * @throws InvalidDimensionException If 'other' does not have same dimensions as this.
    * @note 'other' must be of same dimensions as this.
    */
    SparseMatrix<T>& operator=(SparseMatrix<T>&& other) noexcept {
        if (values_ != other.values_ && rowIndices_ != other.rowIndices_ && colOffsets_ != other.colOffsets_) {
            assert_same_dimensions(*this, other, "move assign");

            delete[] values_;
            values_ = other.values_;
            other.values_ = nullptr;

            delete[] rowIndices_;
            rowIndices_ = other.rowIndices_;
            other.rowIndices_ = nullptr;

            delete[] colOffsets_;
            colOffsets_ = other.colOffsets_;
            other.colOffsets_ = nullptr;

            nnz_ = other.nnz_;
        }

        return *this;
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

    /**
     * @brief Gets the array containing the column offsets.
     * Always of size 'columns + 1'.
     * @return Pointer to array of column offsets.
     */
    [[nodiscard]] int* colOffsets() {
        return colOffsets_;
    }

    /**
    * @brief Gets the array containing the column offsets.
    * Always of size 'columns + 1'.
    * @return Const pointer to array of column offsets.
    */
    [[nodiscard]] const int* colOffsets() const {
        return colOffsets_;
    }

    /**
    * @brief Gets the array containing the row indices.
    * @return Pointer to array of row indices.
    */
    [[nodiscard]] int* rowIndices() {
        return rowIndices_;
    }

    /**
    * @brief Gets the array containing the row indices.
    * @return Const pointer to array of row indices.
    */
    [[nodiscard]] const int* rowIndices() const {
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

template<scalar T = float>
struct SparseMatrixView : SparseMatrixBase<T> {
    SparseMatrixView() = delete;
    SparseMatrixView(SparseMatrixView<T>&& other) noexcept = delete;
    SparseMatrixView<T>& operator=(const SparseMatrixView<T>& other) = delete;
    SparseMatrixView<T>& operator=(SparseMatrixView<T>&& other) noexcept = delete;

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
     * @brief Copy constructor for SparseMatrixView.
     *
     * Constructs a view with the same 'owner' as 'other'.
     * Does not allocate new memory.
     *
     * @param other SparseMatrixView to copy from.
     */
    SparseMatrixView(const SparseMatrixView<T>& other) : SparseMatrixBase<T>(other.rows, other.columns), colOffset_(other.colOffset_), rowOffset_(other.rowOffset_), owner_(other.owner_) {}

    /**
    * @brief Trying to modify a SparseMatrix through a view is invalid.
    * @throws InvalidOperationException You cannot modify owner through a view.
    */
    void set(const int, const int, const T) override {
        throw InvalidOperationException("Cannot modify owner through view");
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

    /**
    * @brief Gets the column offset relative to the 'owner'.
    * @return The column offset.
    */
    [[nodiscard]] int colOffset() const {
        return colOffset_;
    }

    /**
     * @brief Gets the row offset relative to the 'owner'.
     * @return The row offset.
     */
    [[nodiscard]] int rowOffset() const {
        return rowOffset_;
    }

    /**
     * @brief Gets the const reference to the DenseMatrix owner.
     * @return Const reference to denseMatrix owner.
     */
    [[nodiscard]] const SparseMatrix<T>& owner() const {
        return owner_;
    }

    ~SparseMatrixView() override = default;

private:
    const int colOffset_;
    const int rowOffset_;

    const SparseMatrix<T>& owner_;
};

template<scalar T = float>
struct CustomSparseMatrix : SparseMatrixBase<T> {
    CustomSparseMatrix() = delete;
    CustomSparseMatrix(const CustomSparseMatrix<T>& other) = delete;
    CustomSparseMatrix(CustomSparseMatrix<T>&& other) noexcept = delete;
    CustomSparseMatrix<T>& operator=(const CustomSparseMatrix<T>& other) = delete;
    CustomSparseMatrix<T>& operator=(CustomSparseMatrix<T>&& other) noexcept = delete;

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

    /**
    * @brief Gets the reference to the pointer storing the column offsets.
    * @return Reference to pointer containing the column offsets.
    */
    [[nodiscard]] int*& colOffsets() {
        return colOffsets_;
    }

    /**
    * @brief Gets the const reference to the const pointer storing the column offsets.
    * @return Const reference to const pointer containing the column offsets.
    */
    [[nodiscard]] const int* const& colOffsets() const {
        return colOffsets_;
    }

    /**
    * @brief Gets the reference to the pointer storing the row indices.
    * @return Reference to pointer containing the row indices.
    */
    [[nodiscard]] int*& rowIndices() {
        return rowIndices_;
    }

    /**
    * @brief Gets the const reference to the const pointer storing the row indices.
    * @return Const reference to const pointer containing the row indices.
    */
    [[nodiscard]] const int* const& rowIndices() const {
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

private:
    int*& colOffsets_;
    int*& rowIndices_;
    T*& values_;
    int& nnz_;
};
