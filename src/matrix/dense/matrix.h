#pragma once
#include "helper.h"
#include "../../telemetry.h"

#include "../../exceptions.h"
#include "../../helper.h"

template<scalar T = float>
struct DenseMatrix {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

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
    DenseMatrix(const std::size_t rows, const std::size_t columns, const bool fill = true) : rows_(rows), columns_(columns), data_(fill ? new T[columns_ * rows_]() : new T[columns_ * rows_]) {
        Telemetry::emit_allocation();
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
    DenseMatrix(const std::initializer_list<std::initializer_list<T>>& initializerList) : rows_(initializerList.size()), columns_(initializerList.begin()->size()), data_(new T[rows_ * columns_]) {
        std::size_t r = 0;
        for (const auto& row: initializerList) {
            if (row.size() != columns_) {
                throw InvalidDimensionException("Nested initializer lists must all have the same size");
            }

            std::size_t c = 0;
            for (const T element: row) {
                at(r, c) = element;
                c++;
            }
            r++;
        }
        Telemetry::emit_allocation();
    }

    /**
     * @brief Copy constructor for DenseMatrix from same type DenseMatrix.
     *
     * Constructs an 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
     * Allocates 'other.rows * other.columns * sizeof(T)' bytes on the heap.
     *
     * @param other DenseMatrix to copy from.
     */
    DenseMatrix(const DenseMatrix<T>& other) : rows_(other.rows_), columns_(other.columns_), data_(new T[columns_ * rows_]) {
        memcpy(data_, other.data_, columns_ * rows_ * sizeof(T));
        Telemetry::emit_copy_construct();
        Telemetry::emit_allocation();
    }

    /**
     * @brief Copy constructor for DenseMatrix from different type DenseMatrix.
     *
     * Constructs an 'other.rows x other.columns' matrix and performs a deep copy of 'other'.
     * Allocates 'other.rows * other.columns * sizeof(T)' bytes on the heap.
     *
     * @param other DenseMatrix to copy from.
     */
    template<scalar OTHER_T>
    DenseMatrix(const DenseMatrix<OTHER_T>& other) : rows_(other.rows()), columns_(other.columns()), data_(new T[columns_ * rows_]) {
        const OTHER_T* otherData = other.data();

        for (std::size_t i = 0; i < columns_ * rows_; i++) {
            data_[i] = otherData[i];
        }

        Telemetry::emit_copy_construct();
        Telemetry::emit_allocation();
    }

    template<dense_matrix_like U>
    DenseMatrix(const U& other) : rows_(other.rows()), columns_(other.columns()), data_(new T[columns_ * rows_]) {
        for (std::size_t c = 0; c < columns_; c++) {
            for (std::size_t r = 0; r < rows_; r++) {
                data_[c * rows_ + r] = other.at(r, c);
            }
        }
        Telemetry::emit_allocation();
    }

    /**
     * @brief Move constructor for DenseMatrix from same type DenseMatrix.
     *
     * Constructs an 'other.rows' x 'other.columns' matrix and uses the same 'data' pointer of 'other'.
     * Does not allocate memory.
     *
     * @param other DenseMatrix to move from.
     */
    DenseMatrix(DenseMatrix<T>&& other) noexcept : rows_(other.rows_), columns_(other.columns_), data_(other.data_) {
        other.data_ = nullptr;
        other.rows_ = 0;
        other.columns_ = 0;
        Telemetry::emit_move_construct();
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
        if (this != &other) {
            if (rows_ != other.rows_ || columns_ != other.columns_) {
                Telemetry::emit_deallocation();
                delete[] data_;
                rows_ = other.rows_;
                columns_ = other.columns_;
                data_ = new T[rows_ * columns_];
                Telemetry::emit_allocation();
            }
            memcpy(data_, other.data_, columns_ * rows_ * sizeof(T));
            Telemetry::emit_copy_assign();
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
        if (this->rows_ != other.rows() || this->columns_ != other.columns()) {
            Telemetry::emit_deallocation();
            delete[] data_;
            rows_ = other.rows();
            columns_ = other.columns();
            data_ = new T[rows_ * columns_];
            Telemetry::emit_allocation();
        }

        const OTHER_T* otherData = other.data();

        for (std::size_t i = 0; i < columns_ * rows_; i++) {
            data_[i] = otherData[i];
        }

        Telemetry::emit_copy_assign();
        return *this;
    }

    template<dense_matrix_like U>
    DenseMatrix<T>& operator=(const U& other) {
        if (this->rows_ != other.rows() || this->columns_ != other.columns()) {
            Telemetry::emit_deallocation();
            delete[] data_;
            rows_ = other.rows();
            columns_ = other.columns();
            data_ = new T[rows_ * columns_];
            Telemetry::emit_allocation();
        }

        for (int c = 0; c < columns_; c++) {
            for (int r = 0; r < rows_; r++) {
                at(r, c) = other.at(r, c);
            }
        }

        Telemetry::emit_copy_assign();
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
    DenseMatrix<T>& operator=(DenseMatrix<T>&& other) noexcept {
        if (this != &other) {
            Telemetry::emit_deallocation();
            delete[] data_;
            data_ = other.data_;
            other.data_ = nullptr;

            rows_ = other.rows_;
            other.rows_ = 0;

            columns_ = other.columns_;
            other.columns_ = 0;
            Telemetry::emit_move_assign();
        }

        return *this;
    }

    static DenseMatrix<T> identity(const std::size_t n) {
        DenseMatrix<T> m(n, n, true);

        for (std::size_t i = 0; i < n; i++) {
            m.at(i, i) = 1;
        }

        return std::move(m);
    }

    [[nodiscard]] T& at(const std::size_t r, const std::size_t c) {
        return data_[c * rows_ + r];
    }

    [[nodiscard]] const T& at(const std::size_t r, const std::size_t c) const {
        return data_[c * rows_ + r];
    }

    [[nodiscard]] T& operator[](const std::size_t r, const std::size_t c) {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return at(r, c);
    }

    [[nodiscard]] const T& operator[](const std::size_t r, const std::size_t c) const {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return at(r, c);
    }

    [[nodiscard]] std::size_t rows() const {
        return rows_;
    }

    [[nodiscard]] std::size_t columns() const {
        return columns_;
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

    ~DenseMatrix() {
        if (data_ != nullptr) {
            Telemetry::emit_deallocation();
        }
        delete[] data_;
    }

private:
    std::size_t rows_;
    std::size_t columns_;

    T* data_;
};

template<scalar T = float>
struct DenseMatrixView {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

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
    DenseMatrixView(const DenseMatrix<T>& owner, const std::size_t rows, const std::size_t columns, const std::size_t colOffset, const std::size_t rowOffset) : rows_(rows), columns_(columns), colOffset_(colOffset), rowOffset_(rowOffset), owner_(owner) {
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
    [[nodiscard]] T& at(const std::size_t, const std::size_t) {
        throw InvalidOperationException("Cannot modify owner through view");
    }

    [[nodiscard]] const T& at(const std::size_t r, const std::size_t c) const {
        return owner_.at(r + rowOffset_, c + colOffset_);
    }

    [[nodiscard]] T& operator[](const std::size_t r, const std::size_t c) {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return at(r, c);
    }

    [[nodiscard]] const T& operator[](const std::size_t r, const std::size_t c) const {
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
    [[nodiscard]] const DenseMatrix<T>& owner() const {
        return owner_;
    }

    ~DenseMatrixView() = default;

private:
    std::size_t rows_;
    std::size_t columns_;
    const std::size_t colOffset_;
    const std::size_t rowOffset_;

    const DenseMatrix<T>& owner_;
};

template<scalar T = float>
struct CustomDenseMatrix {
    using ValueType = T;
    using UnderlyingType = underlying_type_t<T>;

    static constexpr bool isComplex = is_complex_v<T>;

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
    CustomDenseMatrix(T* data, const std::size_t rows, const std::size_t columns, const std::size_t stride) : rows_(rows), columns_(columns), stride_(stride), data_(data) {
    }

    [[nodiscard]] T& at(const std::size_t r, const std::size_t c) {
        return data_[c * stride_ + r];
    }

    [[nodiscard]] const T& at(const std::size_t r, const std::size_t c) const {
        return data_[c * stride_ + r];
    }

    [[nodiscard]] T& operator[](const std::size_t r, const std::size_t c) {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return at(r, c);
    }

    [[nodiscard]] const T& operator[](const std::size_t r, const std::size_t c) const {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return at(r, c);
    }

    /**
     * @brief Gets the stride or how far to jump between elements.
     * @return The stride.
     */
    [[nodiscard]] std::size_t stride() const {
        return stride_;
    }

    [[nodiscard]] std::size_t rows() const {
        return rows_;
    }

    [[nodiscard]] std::size_t columns() const {
        return columns_;
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

    ~CustomDenseMatrix() = default;

private:
    std::size_t rows_;
    std::size_t columns_;
    const std::size_t stride_;

    T* const data_;
};
