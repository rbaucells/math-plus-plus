#ifndef MATHPP_IMPLEMENTATION_MATRIX_DENSE_MATRIX
#define MATHPP_IMPLEMENTATION_MATRIX_DENSE_MATRIX

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <concepts>
#include <cstring>

#include "mathpp/implementation/common/exceptions.h"
#include "mathpp/implementation/common/telemetry.h"

#include "mathpp/implementation/common/traits.h"

#include "traits.h"


/**
 * @brief Owning column major dense matrix.
 * @tparam T Scalar type of matrix elements.
 */
template<scalar T>
struct DenseMatrix {
    using ValueType = T;

    static constexpr bool isComplex = is_complex_v<T>;

    /**
     * @brief Default constructor.
     *
     * Creates a 0x0 matrix.
     * Does not allocate memory on heap.
     * Both rows/columns is set to 0 and data is set to nullptr.
     */
    DenseMatrix() : rows_(0), columns_(0), data_(nullptr) {}

    /**
     * @brief Sized constructor.
     *
     * Creates a rows x columns matrix.
     * Allocates 'rows * columns * sizeof(T)' bytes on heap.
     * Optionally fills the allocated memory with default initialized elements.
     * Emits an allocation.
     *
     * @param rows Number of rows in constructed matrix.
     * @param columns Number of columns in constructed matrix.
     * @param fill If true initializes all elements to default. If false leaves elements uninitialized.
     */
    DenseMatrix(const std::size_t rows, const std::size_t columns, const bool fill = true) : rows_(rows), columns_(columns), data_(fill ? new T[columns_ * rows_]() : new T[columns_ * rows_]) {
        Telemetry::emit_allocation();
    }

    /**
     * @brief Initializer list constructor.
     *
     * Creates a initializerList.size x nestedInitializerList.size matrix.
     * Allocates 'rows * columns * sizeof(T)' bytes on heap.
     * Each nested initializer list represents one row of the constructed matrix.
     * Emits an allocation.
     *
     * @note All nested initializer lists must all have the same size.
     * @param initializerList Nested initializer lists of matrix elements
     * @throws InvalidDimensionException If all nested initializer lists are not of same size.
     */
    DenseMatrix(const std::initializer_list<std::initializer_list<T>>& initializerList) : rows_(initializerList.size()), columns_(initializerList.begin()->size()), data_(new T[rows_ * columns_]) {
        std::size_t r = 0;
        for (const auto& row: initializerList) {
            if (row.size() != columns_) {
                throw InvalidDimensionException("Nested initializer lists must all have the same size");
            }

            std::size_t c = 0;
            for (const T element: row) {
                (*this)[r, c] = element;
                c++;
            }
            r++;
        }

        Telemetry::emit_allocation();
    }

    /**
     * @brief Copy constructor from same type DenseMatrix.
     *
     * Allocates 'rows * columns * sizeof(T)' bytes on heap.
     * Emits an allocation and copy_construct.
     *
     * @param other Same type DenseMatrix to copy from.
     */
    DenseMatrix(const DenseMatrix<T>& other) : rows_(other.rows_), columns_(other.columns_), data_(new T[columns_ * rows_]) {
        std::memcpy(data_, other.data_, rows_ * columns_ * sizeof(T));

        Telemetry::emit_copy_construct();
        Telemetry::emit_allocation();
    }

    /**
     * @brief Copy constructor from different type DenseMatrix.
     *
     * Allocates 'rows * columns * sizeof(T)' bytes on heap.
     * Emits an allocation and copy_construct.
     *
     * @tparam U Scalar type of other DenseMatrix.
     * @param other DenseMatrix to copy from.
     */
    template<scalar U> requires std::is_convertible_v<U, T>
    DenseMatrix(const DenseMatrix<U>& other) : rows_(other.rows()), columns_(other.columns()), data_(new T[columns_ * rows_]) {
        std::copy(other.rawData(), other.rawData() + (rows_ * columns_), data_);

        Telemetry::emit_copy_construct();
        Telemetry::emit_allocation();
    }

    /**
     * @brief Copy constructor from any dense matrix like object.
     *
     * Allocates 'rows * columns * sizeof(T)' bytes on heap.
     * Emits an allocation and copy_construct.
     *
     * @tparam U Type that fulfills 'dense_matrix_like' concept.
     * @param other Dense matrix like object to copy from.
     */
    template<dense_matrix_like U> requires std::is_convertible_v<typename U::ValueType, T>
    DenseMatrix(const U& other) : rows_(other.rows()), columns_(other.columns()), data_(new T[columns_ * rows_]) {
        for (std::size_t c = 0; c < columns_; c++) {
            for (std::size_t r = 0; r < rows_; r++) {
                (*this)[r, c] = other[r, c];
            }
        }

        Telemetry::emit_copy_construct();
        Telemetry::emit_allocation();
    }

    /**
     * @brief Move constructor from same type DenseMatrix.
     *
     * Does not allocate memory on heap.
     * Emits a move_construct.
     *
     * @param other DenseMatrix to move from.
     * @note Invalidates 'other' matrix and leaves in an empty state.
     */
    DenseMatrix(DenseMatrix<T>&& other) noexcept : rows_(other.rows_), columns_(other.columns_), data_(other.data_) {
        other.rows_ = 0;
        other.columns_ = 0;
        other.data_ = nullptr;
        Telemetry::emit_move_construct();
    }

    /**
     * @brief Copy assignment operator from same type DenseMatrix.
     *
     * If this matrix is not resized, emits a copy_assign.
     * If this matrix is resized, emits a deallocation, allocation, and copy_assign.
     * If this matrix is resized, allocates 'other.rows * other.columns * sizeof(T)' bytes of memory.
     *
     * @param other DenseMatrix to copy from.
     * @return Reference to this matrix.
     */
    DenseMatrix<T>& operator=(const DenseMatrix<T>& other) {
        if (this != &other) {
            if (rows_ != other.rows_ || columns_ != other.columns_) {
                rows_ = other.rows_;
                columns_ = other.columns_;
                delete[] data_;
                Telemetry::emit_deallocation();
                data_ = new T[rows_ * columns_];
                Telemetry::emit_allocation();
            }
            std::memcpy(data_, other.data_, columns_ * rows_ * sizeof(T));
            Telemetry::emit_copy_assign();
        }

        return *this;
    }

    /**
     * @brief Copy assignment operator from diff type DenseMatrix.
     *
     * If this matrix is not resized, emits a copy_assign.
     * If this matrix is resized, emits a deallocation, allocation, and copy_assign.
     * If this matrix is resized, allocates 'other.rows * other.columns * sizeof(T)' bytes of memory.
     *
     * @tparam U Scalar type of other DenseMatrix.
     * @param other DenseMatrix to copy from.
     * @return Reference to this matrix.
     */
    template<scalar U> requires std::convertible_to<U, T>
    DenseMatrix<T>& operator=(const U& other) {
        if (this->rows_ != other.rows() || this->columns_ != other.columns()) {
            Telemetry::emit_deallocation();
            rows_ = other.rows();
            columns_ = other.columns();
            delete[] data_;
            data_ = new T[rows_ * columns_];
            Telemetry::emit_allocation();
        }

        std::copy(other.rawData(), other.rawData() + (rows_ * columns_), data_);

        Telemetry::emit_copy_assign();
        return *this;
    }

    /**
     * @brief Copy assignment operator from any dense matrix like object.
     *
     * If this matrix is not resized, emits a copy_assign.
     * If this matrix is resized, emits a deallocation, allocation, and copy_assign.
     * If this matrix is resized, allocates 'other.rows * other.columns * sizeof(T)' bytes of memory.
     *
     * @tparam U Type that fulfills 'dense_matrix_like' concept.
     * @param other Dense matrix like object to copy from.
     * @return Reference to this matrix
     */
    template<dense_matrix_like U> requires std::convertible_to<typename U::ValueType, T>
    DenseMatrix<T>& operator=(const U& other) {
        if (this->rows_ != other.rows() || this->columns_ != other.columns()) {
            Telemetry::emit_deallocation();
            rows_ = other.rows();
            columns_ = other.columns();
            delete[] data_;
            data_ = new T[rows_ * columns_];
            Telemetry::emit_allocation();
        }

        for (std::size_t c = 0; c < columns_; c++) {
            for (std::size_t r = 0; r < rows_; r++) {
                (*this)[r, c] = other[r, c];
            }
        }

        Telemetry::emit_copy_assign();
        return *this;
    }

    /**
     * @brief Move assignment operator from same type DenseMatrix.
     *
     * Does not allocate memory on heap.
     * Emits a deallocation and move_assign.
     *
     * @param other DenseMatrix to move from.
     * @return Reference to this matrix.
     * @note Invalidates other matrix and leaves in a empty state.
     */
    DenseMatrix<T>& operator=(DenseMatrix<T>&& other) noexcept {
        if (this != &other) {
            Telemetry::emit_deallocation();
            rows_ = other.rows_;
            other.rows_ = 0;

            columns_ = other.columns_;
            other.columns_ = 0;

            delete[] data_;
            data_ = other.data_;
            other.data_ = nullptr;

            Telemetry::emit_move_assign();
        }

        return *this;
    }

    /**
     * @brief Reshapes the matrix to be 'newRows x newColumns' in size.
     *
     * Does nothing if specified new dimensions are identical to current.
     * If specified new dimensions are different to current, emits an allocation and deallocation.
     *
     * @param newRows Number of rows for the reshaped matrix to have.
     * @param newColumns Number of columns for the reshaped matrix to have.
     * @param preserve Whether to preserve data or leave uninitialized.
     *
     * @note When preserve is false, ALL matrix elements will be left uninitialized.
     */
    void reshape(const std::size_t newRows, const std::size_t newColumns, const bool preserve) {
        if (newRows == rows_ && newColumns == columns_) {
            return;
        }

        T* newData = new T[newRows * newColumns];
        Telemetry::emit_allocation();

        if (preserve) {
            for (std::size_t c = 0; c < newColumns; c++) {
                for (std::size_t r = 0; r < newRows; r++) {
                    if (c < columns_ && r < rows_) {
                        newData[c * newRows + r] = data_[c * rows_ + r];
                    }
                }
            }
        }

        rows_ = newRows;
        columns_ = newColumns;

        delete[] data_;
        Telemetry::emit_deallocation();

        data_ = newData;
    }

    /**
     * @brief Reshapes the matrix to be 'newRows x newColumns' in size.
     *
     * Does nothing if specified new dimensions are identical to current.
     * If specified new dimensions are different to current, emits an allocation and deallocation.
     *
     * @param newRows Number of rows for the reshaped matrix to have.
     * @param newColumns Number of columns for the reshaped matrix to have.
     * @param preserve Whether to preserve data or leave initialized to value.
     * @param value Value to set all uninitialized elements too.
     *
     * @note When preserve is true, ONLY matrix elements not initialized by old data will be initialized to value.
     * @note When preserve is false, ALL matrix elements will be left initialized to value.
     */
    void reshape(const std::size_t newRows, const std::size_t newColumns, const bool preserve, const T value) {
        if (newRows == rows_ && newColumns == columns_) {
            return;
        }

        T* newData = new T[newRows * newColumns];
        Telemetry::emit_allocation();

            for (std::size_t c = 0; c < newColumns; c++) {
                for (std::size_t r = 0; r < newRows; r++) {
                    if (c < columns_ && r < rows_ && preserve) {
                        newData[c * newRows + r] = data_[c * rows_ + r];
                    }
                    else {
                        newData[c * newRows + r] = value;
                    }
                }
            }

        rows_ = newRows;
        columns_ = newColumns;

        delete[] data_;
        Telemetry::emit_deallocation();

        data_ = newData;
    }

    /**
     * @brief Accesses the element at a provided row and column.
     *
     * Retrieves a reference to the element at coordinates (r, c).
     * Checks bounds of provided r and c indices.
     * Does not allocate memory on the heap.
     *
     * @param r Zero-based row index of element.
     * @param c Zero-based columns index of element.
     *
     * @see DenseMatrix::operator[](const std::size_t r, const std::size_t c).
     *
     * @return Reference to the element at (r, c).
     * @note Indices must be withing matrix bounds.
     * @throws InvalidIndexException If r or c indices are out of bounds (ie. greater than rows/columns).
     */
    [[nodiscard]] T& at(const std::size_t r, const std::size_t c) {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return data_[c * rows_ + r];
    }

    /**
     * @brief Accesses the element at a provided row and column.
     *
     * Retrieves a const-reference to the element at coordinates (r, c).
     * Checks bounds of provided r and c indices.
     * Does not allocate memory on the heap.
     *
     * @param r Zero-based row index of element.
     * @param c Zero-based columns index of element.
     *
     * @see DenseMatrix::operator[](const std::size_t r, const std::size_t c).
     *
     * @return Const-reference to the element at (r, c).
     * @note Indices must be withing matrix bounds.
     * @throws InvalidIndexException If r or c indices are out of bounds (ie. greater than rows/columns).
     */
    [[nodiscard]] const T& at(const std::size_t r, const std::size_t c) const {
        if (r >= rows_ || c >= columns_) {
            throw InvalidIndexException("Cannot access matrix at invalid index");
        }

        return data_[c * rows_ + r];
    }

    /**
     * @brief Accesses the element at a provided row and column.
     *
     * Retrieves a reference to the element at coordinates (r, c).
     * Does not check bounds of provided r and c indices.
     * Does not allocate memory on the heap.
     *
     * @param r Zero-based row index of element.
     * @param c Zero-based columns index of element.
     *
     * @see DenseMatrix::at(const std::size_t r, const std::size_t c).
     *
     * @return Reference to the element at (r, c).
     * @note Undefined behavior if r or c are out of bounds.
     */
    [[nodiscard]] T& operator[](const std::size_t r, const std::size_t c) {
        return data_[c * rows_ + r];
    }

    /**
     * @brief Accesses the element at a provided row and column.
     *
     * Retrieves a const-reference to the element at coordinates (r, c).
     * Does not check bounds of provided r and c indices.
     * Does not allocate memory on the heap.
     *
     * @param r Zero-based row index of element.
     * @param c Zero-based columns index of element.
     *
     * @see DenseMatrix::at(const std::size_t r, const std::size_t c).
     *
     * @return Const-reference to the element at (r, c).
     * @note Undefined behavior if r or c are out of bounds.
     */
    [[nodiscard]] const T& operator[](const std::size_t r, const std::size_t c) const {
        return data_[c * rows_ + r];
    }

    /**
     * @return Number of rows in DenseMatrix.
     */
    [[nodiscard]] std::size_t rows() const {
        return rows_;
    }

    /**
     * @return Number of columns in DenseMatrix.
     */
    [[nodiscard]] std::size_t columns() const {
        return columns_;
    }

    /**
     * @brief Accesses the matrix's data array at a provided index.
     *
     * Does not check bounds of index i.
     * Does not allocate memory.
     *
     * @param i Zero-based linear index to index into data array.
     * @return Const-reference to element at index i of data array.
     */
    const T& data(const std::size_t i) const {
        return data_[i];
    }

    /**
     * @brief Accesses the matrix's data array at a provided index.
     *
     * Does not check bounds of index i.
     * Does not allocate memory.
     *
     * @param i Zero-based linear index to index into data array.
     * @return Reference to element at index i of data array.
     */
    T& data(const std::size_t i) {
        return data_[i];
    }

    /**
    * @return Pointer to flat array containing all matrix elements in column major order.
    * @note Pointer to array of size rows * columns.
    */
    [[nodiscard]] T* rawData() {
        return data_;
    }

    /**
     * @return Const-pointer to flat array containing all matrix elements in column major order.
     * @note Const-pointer to array of size rows * columns.
     */
    [[nodiscard]] const T* rawData() const {
        return data_;
    }

    /**
     * @brief Destructor for DenseMatrix.
     * If data is not nullptr, emits a deallocation.
     * Deallocates data array.
     */
    ~DenseMatrix() {
        if (data_ != nullptr) {
            Telemetry::emit_deallocation();
            delete[] data_;
        }
    }

private:
    // number of rows
    std::size_t rows_;
    // number of columns
    std::size_t columns_;

    // data array
    T* data_;
};

#endif // MATHPP_IMPLEMENTATION_MATRIX_DENSE_MATRIX
