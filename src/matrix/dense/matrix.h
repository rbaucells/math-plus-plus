#pragma once
#include "helper.h"

#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T = float>
struct DenseMatrixBase {

    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

    [[nodiscard]] int rows() const {
        return rows_;
    }

    [[nodiscard]] int columns() const {
        return columns_;
    }

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
    DenseMatrixBase(const int rows, const int columns) : rows_(rows), columns_(columns) {}

    const int rows_;
    const int columns_;

public:
    /**
     * @brief Accesses the element at column 'c' and row 'r'.
     *
     * @param c Zero-based column index.
     * @param r Zero-based row index.
     * @return Reference to the element at column 'c' and row 'r'.
     */
    [[nodiscard]] virtual T& at(int c, int r) = 0;

    /**
     * @brief Accesses the element at column 'c' and row 'r' (const).
     *
     * @param c Zero-based column index.
     * @param r Zero-based row index.
     * @return Const reference to the element at column 'c' and row 'r' .
     */
    [[nodiscard]] virtual const T& at(int c, int r) const = 0;

    [[nodiscard]] T& operator[](const int c, const int r) {
        if (c > columns_ - 1 || c < 0 || r > rows_ - 1 || r < 0) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return at(c, r);
    }

    [[nodiscard]] const T& operator[](const int c, const int r) const {
        if (c > columns_ - 1 || c < 0 || r > rows_ - 1 || r < 0) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return at(c, r);
    }

    virtual ~DenseMatrixBase() = default;
};

template<scalar T = float>
struct DenseMatrix : DenseMatrixBase<T> {
    DenseMatrix() = delete;

    /**
     * @brief Constructs a DenseMatrix of size 'rows x columns'.
     *
     * Allocates 'rows * columns * sizeof(T)' bytes of memory on the heap.
     * Optionally fills all elements with zero.
     *
     * @param columns Number of columns.
     * @param rows Number of rows.
     * @param fill If true, initializes all elements to zero; otherwise leaves elements uninitialized.
     */
    DenseMatrix(const int rows, const int columns, const bool fill = true) : DenseMatrixBase<T>(rows, columns) {
        data_ = new T[columns * rows];

        if (fill) {
            for (int i = 0; i < columns * rows; i++) {
                data_[i] = 0;
            }
        }
    }

    /**
     * @brief Constructs a DenseMatrix from a nested initializer list of size 'initializerList.size() x initializerList.begin()->size()'.
     *
     * Allocates 'rows * columns * sizeof(T)' bytes on the heap.
     * All nested initializer lists must have the same size.
     *
     * @param initializerList Nested initializer_list representing matrix elements.
     * @throws InvalidDimensionException If nested initializer_lists are not all the same size.
     */
    DenseMatrix(const std::initializer_list<std::initializer_list<T>>& initializerList) : DenseMatrixBase<T>(initializerList.size(), initializerList.begin()->size()) {
        data_ = new T[this->columns_ * this->rows_];

        int r = 0;
        for (const auto& row : initializerList) {
            if (row.size() != this->columns_) {
                throw InvalidDimensionException("Nested initializer lists must all have the same size");
            }

            int c = 0;
            for (const T element : row) {
                DenseMatrix<T>::at(c, r) = element;
                c++;
            }
            r++;
        }
    }

    /**
     * @brief Copy constructor for DenseMatrix from same type DenseMatrix.
     *
     * Constructs an 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
     * Allocates 'other.rows * other.columns * sizeof(T)' bytes on the heap.
     *
     * @param other DenseMatrix to copy from.
     */
    DenseMatrix(const DenseMatrix<T>& other) : DenseMatrixBase<T>(other.rows_, other.columns_) {
        data_ = new T[this->columns_ * this->rows_];
        memcpy(data_, other.data_, this->columns_ * this->rows_ * sizeof(T));
    }

    /**
    * @brief Copy constructor for DenseMatrix from different type DenseMatrix.
    *
    * Constructs an 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
    * Allocates 'other.rows * other.columns * sizeof(T)' bytes on the heap.
    *
    * @tparam OTHER_T Scalar type of the 'other' DenseMatrix.
    * @param other DenseMatrix to copy from.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    */
    template<scalar OTHER_T> requires std::convertible_to<OTHER_T, T>
    DenseMatrix(const DenseMatrix<OTHER_T>& other) : DenseMatrixBase<T>(other.rows(), other.columns()) {
        data_ = new T[this->columns_ * this->rows_];

        for (int c = 0; c < this->columns_; c++) {
            for (int r = 0; r < this->rows_; r++) {
                DenseMatrix<T>::at(c, r) = other[c, r];
            }
        }
    }

    /**
     * @brief Copy constructor for DenseMatrix from same type DenseMatrixBase.
     *
     * Constructs an 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
     * Allocates 'other.rows * other.columns * sizeof(T)' bytes on the heap.
     *
     * @param other DenseMatrixBase to copy from.
     */
    DenseMatrix(const DenseMatrixBase<T>& other) : DenseMatrixBase<T>(other.rows(), other.columns()) {
        data_ = new T[this->columns_ * this->rows_];

        for (int c = 0; c < this->columns_; c++) {
            for (int r = 0; r < this->rows_; r++) {
                DenseMatrix<T>::at(c, r) = other[c, r];
            }
        }
    }

    /**
    * @brief Copy constructor for DenseMatrix from different type DenseMatrixBase.
    *
    * Constructs an 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
    * Allocates 'other.rows * other.columns * sizeof(T)' bytes on the heap.
    *
    * @tparam OTHER_T Scalar type of the 'other' DenseMatrixBase.
    * @param other DenseMatrixBase to copy from.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    */
    template<scalar OTHER_T> requires std::convertible_to<OTHER_T, T>
    DenseMatrix(const DenseMatrixBase<OTHER_T>& other) : DenseMatrixBase<T>(other.rows(), other.columns()) {
        data_ = new T[this->columns_ * this->rows_];

        for (int c = 0; c < this->columns_; c++) {
            for (int r = 0; r < this->rows_; r++) {
                DenseMatrix<T>::at(c, r) = other[c, r];
            }
        }
    }

    /**
     * @brief Move constructor for DenseMatrix from same type DenseMatrix.
     *
     * Constructs an 'other.rows' x 'other.columns' matrix and uses the same 'data' pointer of 'other'.
     * Does not allocate memory.
     *
     * @param other DenseMatrix to move from.
     */
    DenseMatrix(DenseMatrix<T>&& other) noexcept : DenseMatrixBase<T>(other.rows_, other.columns_) {
        data_ = other.data_;
        other.data_ = nullptr;
    }

    /**
     * @brief Copy assignment operator for DenseMatrix from same type DenseMatrix.
     * Replaces all elements with elements of 'other'.
     * Does not allocate memory on the heap.
     * @param other DenseMatrix to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same dimensions as this.
     * @note 'other' must be of same dimensions as this.
     */
    DenseMatrix<T>& operator=(const DenseMatrix<T>& other) {
        if (data_ != other.data_) {
            assert_same_dimensions(*this, other);
            memcpy(data_, other.data_, this->columns_ * this->rows_ * sizeof(T));
        }

        return *this;
    }

    /**
    * @brief Copy assignment operator for DenseMatrix from different type DenseMatrix.
    * Replaces all elements with elements of 'other'.
    * Does not allocate memory on the heap.
    * @tparam OTHER_T Scalar type of the 'other' DenseMatrix.
    * @param other DenseMatrix to copy from.
    * @return Reference to this.
    * @throws InvalidDimensionException If 'other' does not have same dimensions as this.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    * @note 'other' must be of same dimensions as this.
    */
    template<scalar OTHER_T> requires std::convertible_to<OTHER_T, T>
    DenseMatrix<T>& operator=(const DenseMatrix<OTHER_T>& other) {
        assert_same_dimensions(*this, other);

        const OTHER_T* otherData = other.data();

        for (int i = 0; i < this->columns_ * this->rows_; i++) {
            data_[i] = otherData[i];
        }

        return *this;
    }

    /**
     * @brief Copy assignment operator for DenseMatrix from same type DenseMatrixBase.
     * Replaces all elements with elements of 'other'.
     * Does not allocate memory on the heap.
     * @param other DenseMatrixBase to copy from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same dimensions as this.
     * @note 'other' must be of same dimensions as this.
     */
    DenseMatrix<T>& operator=(const DenseMatrixBase<T>& other) {
        assert_same_dimensions(*this, other);
        for (int c = 0; c < this->columns_; c++) {
            for (int r = 0; r < this->rows_; r++) {
                DenseMatrix<T>::at(c, r) = other[c, r];
            }
        }

        return *this;
    }

    /**
    * @brief Copy assignment operator for DenseMatrix from different type DenseMatrixBase.
    * Replaces all elements with elements of 'other'.
    * Does not allocate memory on the heap.
    * @param other DenseMatrixBase to copy from.
    * @return Reference to this.
    * @throws InvalidDimensionException If 'other' does not have same dimensions as this.
    * @note 'other' must be of same dimensions as this.
    * @note 'OTHER_T' must be able to implicitly convert to 'T'.
    * @tparam OTHER_T Scalar type of the 'other' DenseMatrixBase.
    */
    template<scalar OTHER_T> requires std::is_convertible_v<OTHER_T, T>
    DenseMatrix<T>& operator=(const DenseMatrixBase<OTHER_T>& other) {
        assert_same_dimensions(*this, other);
        for (int c = 0; c < this->columns_; c++) {
            for (int r = 0; r < this->rows_; r++) {
                DenseMatrix<T>::at(c, r) = other[c, r];
            }
        }

        return *this;
    }

    /**
     * @brief Move assignment operator for DenseMatrix from same type DenseMatrix.
     * Takes ownership of 'other' data.
     * Does not allocate memory on the heap.
     * @param other DenseMatrix to move from.
     * @return Reference to this.
     * @throws InvalidDimensionException If 'other' does not have same dimensions as this.
     * @note 'other' must be of same dimensions as this.
     */
    DenseMatrix<T>& operator=(DenseMatrix<T>&& other) {
        if (data_ != other.data_) {
            assert_same_dimensions(*this, other);
            delete[] data_;
            data_ = other.data_;
            other.data_ = nullptr;
        }

        return *this;
    }

    static DenseMatrix<T> identity(const int n) {
        DenseMatrix<T> m(n, n, false);

        for (int c = 0; c < n; c++) {
            for (int r = 0; r < n; r++) {
                if (c == r) {
                    m[c, r] = 1;
                }
                else {
                    m[c, r] = 0;
                }
            }
        }

        return std::move(m);
    }

    [[nodiscard]] T& at(const int c, const int r) override {
        return data_[c * this->rows_ + r];
    }

    [[nodiscard]] const T& at(const int c, const int r) const override {
        return data_[c * this->rows_ + r];
    }

    /**
     * @brief Gets the data pointer storing the matrices elements.
     * @return Pointer to array of elements.
     */
    [[nodiscard]] T* data() {
        return data_;
    }

    /**
    * @brief Gets the const data pointer storing the matrices elements.
    * @return Const pointer to array of elements.
    */
    [[nodiscard]] const T* data() const {
        return data_;
    }

    ~DenseMatrix() override {
        delete[] data_;
    }

private:
    T* data_;
};

template<scalar T = float>
struct DenseMatrixView : DenseMatrixBase<T> {
    DenseMatrixView() = delete;
    DenseMatrixView(DenseMatrixView<T>&& other) noexcept = delete;
    DenseMatrixView<T>& operator=(const DenseMatrixView<T>& other) = delete;
    DenseMatrixView<T>& operator=(DenseMatrixView<T>&& other) noexcept = delete;

    /**
    * @brief Constructs a DenseMatrixView into an existing DenseMatrix.
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
    DenseMatrixView(const DenseMatrix<T>& owner, const int rows, const int columns, const int colOffset, const int rowOffset) : DenseMatrixBase<T>(rows, columns), colOffset_(colOffset), rowOffset_(rowOffset), owner_(owner) {}


    /**
     * @brief Copy constructor for DenseMatrixView.
     *
     * Constructs a view with the same 'owner' as 'other'.
     * Does not allocate new memory.
     *
     * @param other DenseMatrixView to copy from.
     */
    DenseMatrixView(const DenseMatrixView<T>& other) : DenseMatrixBase<T>(other.rows_, other.columns_), colOffset_(other.colOffset_), rowOffset_(other.rowOffset_), owner_(other.owner_) {}

    /**
     * @brief Trying to modify a DenseMatrix through a view is invalid.
     * @throws InvalidOperationException You cannot modify owner through a view.
     */
    [[nodiscard]] T& at(const int, const int) override {
        throw InvalidOperationException("Cannot modify owner through view");
    }

    [[nodiscard]] const T& at(const int c, const int r) const override {
        return owner_.at(c + colOffset_, r + rowOffset_);
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
    [[nodiscard]] const DenseMatrix<T>& owner() const {
        return owner_;
    }

    ~DenseMatrixView() override = default;

private:
    const int colOffset_;
    const int rowOffset_;

    const DenseMatrix<T>& owner_;
};

template<scalar T = float>
struct CustomDenseMatrix : DenseMatrixBase<T> {
    CustomDenseMatrix() = delete;
    CustomDenseMatrix(const CustomDenseMatrix<T>& other) = delete;
    CustomDenseMatrix(CustomDenseMatrix<T>&& other) noexcept = delete;
    CustomDenseMatrix<T>& operator=(const CustomDenseMatrix<T>& other) = delete;
    CustomDenseMatrix<T>& operator=(CustomDenseMatrix<T>&& other) noexcept = delete;

    /**
     * @brief Constructs a CustomDenseMatrix of size 'rows x columns'.
     *
     * Does not allocate any memory on the heap.
     * CustomDenseMatrix instance does not own 'data' pointer.
     * Think of it as a view on an arbitrary 'data' pointer.
     *
     * @param data Flat 1d array containing all matrix elements in column major ordering.
     * @param rows Number of rows in matrix.
     * @param columns Number of columns in matrix.
     * @param stride How many elements to skip when accessing elements.
     *
     * @note Length of 'data' array must be greater than '(columns - 1) x stride + (rows - 1)'.
     * @note 'data' array must be in column major ordering.
     */
    CustomDenseMatrix(T* data, const int rows, const int columns, const int stride) : DenseMatrixBase<T>(rows, columns), stride_(stride), data_(data) {}

    [[nodiscard]] T& at(const int c, const int r) override {
        return data_[c * stride_ + r];
    }

    [[nodiscard]] const T& at(const int c, const int r) const override {
        return data_[c * stride_ + r];
    }

    /**
     * @brief Gets the stride or how far to jump between elements.
     * @return The stride.
     */
    [[nodiscard]] int stride() const {
        return stride_;
    }

    /**
     * @brief Gets the data pointer storing the matrices elements.
     * @return Pointer to array of elements.
     */
    [[nodiscard]] T* data() {
        return data_;
    }

    /**
    * @brief Gets the const data pointer storing the matrices elements.
    * @return Const pointer to array of elements.
    */
    [[nodiscard]] const T* data() const {
        return data_;
    }

    ~CustomDenseMatrix() override = default;

private:
    const int stride_;
    T* const data_;
};
