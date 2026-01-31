#pragma once
#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T = float>
struct DenseMatrixBase {
    const int rows;
    const int columns;

    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    DenseMatrixBase() = delete;
    DenseMatrixBase(const DenseMatrixBase<T>& other) = delete;
    DenseMatrixBase(DenseMatrixBase&& other) noexcept = delete;

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
    DenseMatrixBase(const int rows, const int columns) : rows(rows), columns(columns) {}

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
        return at(c, r);
    }

    [[nodiscard]] const T& operator[](const int c, const int r) const {
        return at(c, r);
    }

    virtual ~DenseMatrixBase() = default;
};

template<scalar T = float>
struct DenseMatrix : DenseMatrixBase<T> {
    mutable T* data = nullptr;

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
        data = new T[columns * rows];

        if (fill) {
            for (int i = 0; i < columns * rows; i++)
                data[i] = 0;
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
    DenseMatrix(std::initializer_list<std::initializer_list<T>> initializerList) : DenseMatrixBase<T>(initializerList.size(), initializerList.begin()->size()) {
        data = new T[this->columns * this->rows];

        int r = 0;
        for (const auto& row : initializerList) {
            if (row.size() != this->columns)
                throw InvalidDimensionException("Nested initializer lists must all have the same size");

            int c = 0;
            for (const T element : row) {
                DenseMatrix<T>::at(c, r) = element;
                c++;
            }
            r++;
        }
    }

    /**
     * @brief Copy constructor for DenseMatrix.
     *
     * Constructs a 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
     * Allocates 'other.rows * other.columns * sizeof(T)' bytes on the heap.
     *
     * @param other DenseMatrix to copy from.
     */
    DenseMatrix(const DenseMatrix<T>& other) : DenseMatrixBase<T>(other.rows, other.columns) {
        data = new T[this->columns * this->rows];
        memcpy(data, other.data, this->columns * this->rows * sizeof(T));
    }

    /**
     * @brief Copy constructor for DenseMatrix from DenseMatrixBase.
     *
     * Constructs a 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
     * Allocates 'other.rows * other.columns * sizeof(T)' bytes on the heap.
     *
     * @param other DenseMatrixBase to copy from.
     */
    DenseMatrix(const DenseMatrixBase<T>& other) : DenseMatrixBase<T>(other.rows, other.columns) {
        data = new T[this->columns * this->rows];

        for (int c = 0; c < this->columns; c++) {
            for (int r = 0; r < this->rows; r++) {
                DenseMatrix<T>::at(c, r) = other[c, r];
            }
        }
    }

    /**
     * @brief Move constructor for DenseMatrix.
     *
     * Constructs a 'other.rows' x 'other.columns' matrix and uses the same data pointer of other.
     * Does not allocate memory
     *
     * @param other DenseMatrix to move from.
     */
    DenseMatrix(DenseMatrix<T>&& other) noexcept : DenseMatrixBase<T>(other.rows, other.columns) {
        data = other.data;
        other.data = nullptr;
    }

    /**
     * @brief Constructs an identity matrix of size 'size x size'.
     *
     * Allocates 'size * size * sizeof(T)' bytes on the heap.
     * The matrix contains 1s on the diagonal and 0s elsewhere.
     *
     * @param size Size of the square matrix.
     * @return Identity matrix of the given 'size'.
     */
    static DenseMatrix<T> identity(int size) {
        DenseMatrix<T> result(size, size, false);

        for (int i = 0; i < size * size; i++)
            result.data[i] = (i % (size + 1) == 0) ? 1 : 0;

        return result;
    }

    [[nodiscard]] T& at(const int c, const int r) override {
        return data[c * this->rows + r];
    }

    [[nodiscard]] const T& at(const int c, const int r) const override {
        return data[c * this->rows + r];
    }

    ~DenseMatrix() override {
        delete[] data;
    }
};

template<scalar T = float>
struct DenseMatrixView : DenseMatrixBase<T> {
    const int stride;

    mutable T* data = nullptr;

    DenseMatrixView() = delete;
    DenseMatrixView(const DenseMatrixView<T>& other) = delete;
    DenseMatrixView(DenseMatrixView<T>&& other) noexcept = delete;

    /**
     * @brief Constructs a DenseMatrixView into an existing DenseMatrix.
     *
     * Creates a view of size `rows x columns` into the `owner` matrix, starting
     * at the colOffset and rowOffset.
     * Does not allocate new memory.
     * The view uses the same data pointer of the owner matrix.
     *
     * @param owner DenseMatrix to create a view from.
     * @param rows Number of rows in the view.
     * @param columns Number of columns in the view.
     * @param colOffset Starting column offset in the owner matrix.
     * @param rowOffset Starting row offset in the owner matrix.
     */
    DenseMatrixView(const DenseMatrix<T>& owner, const int rows, const int columns, const int colOffset, const int rowOffset) : DenseMatrixBase<T>(rows, columns), stride(owner.rows), colOffset_(colOffset), rowOffset_(rowOffset) {
        data = owner.data;
    }

    /**
     * @brief Constructs a DenseMatrixView into an existing array of elements.
     *
     * Creates a view of size 'rows x columns' into the 'data' array.
     * Does not allocate new memory. The view uses the 'data' pointer you pass in
     *
     * @param data Array of elements of size >= 'rows * columns * stride'.
     * @param rows Number of rows in the view.
     * @param columns Number of columns in the view.
     * @param stride How much you need to jump from one element to another
     * @note The 'data' array must be in column-major ordering
     */
    DenseMatrixView(const T* data, const int rows, const int columns, const int stride) : DenseMatrixBase<T>(rows, columns), stride(stride), colOffset_(0), rowOffset_(0) {
        this->data = data;
    }

    [[nodiscard]] T& at(const int c, const int r) override {
        return data[(c + colOffset_) * stride + (r + rowOffset_)];
    }

    [[nodiscard]] const T& at(const int c, const int r) const override {
        return data[(c + colOffset_) * stride + (r + rowOffset_)];
    }

    ~DenseMatrixView() override = default;

private:
    const int colOffset_;
    const int rowOffset_;
};
