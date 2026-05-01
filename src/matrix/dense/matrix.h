#pragma once
#include "../../helper.h"
#include "../../telemetry.h"
#include <cstddef>
#include "../../exceptions.h"
#include <cstring>
#include "helper.h"
#include <initializer_list>

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
        std::memcpy(data_, other.data_, columns_ * rows_ * sizeof(T));
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
            std::memcpy(data_, other.data_, columns_ * rows_ * sizeof(T));
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
