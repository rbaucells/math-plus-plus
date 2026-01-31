#pragma once
#include <string>

#include "../../exceptions.h"

#include "gtest/gtest.h"

template<typename T = float>
struct DenseMatrixBase {
    const int columns;
    const int rows;

    using ValueType = T;
    // using UnderlyingType = underlying_type_t<T>;

    DenseMatrixBase() = delete;
    DenseMatrixBase(const DenseMatrixBase<T>& other) = delete;
    DenseMatrixBase(DenseMatrixBase&& other) noexcept = delete;

protected:
    /**
     * @brief Initializes the size of the matrix.
     *
     * Internal constructor that initializes the 'columns' and 'rows' fields.
     * Does not allocate memory for matrix elements.
     *
     * @param columns Number of columns.
     * @param rows Number of rows.
     */
    DenseMatrixBase(const int columns, const int rows) : columns(columns), rows(rows) {}

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

template<typename T = float>
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
    DenseMatrix(const int columns, const int rows, const bool fill = true) : DenseMatrixBase<T>(columns, rows) {
        data = new T[columns * rows];

        if (fill) {
            for (int i = 0; i < columns * rows; i++)
                data[i] = 0;
        }
    }

    /**
     * @brief Constructs a DenseMatrix from a nested initializer list.
     *
     * Allocates 'rows * columns * sizeof(T)' bytes on the heap.
     * All nested initializer lists must have the same size.
     *
     * @param initializerList Nested initializer_list representing matrix elements.
     * @throws InvalidDimensionException If nested initializer_lists are not all the same size.
     */
    DenseMatrix(std::initializer_list<std::initializer_list<T>> initializerList) : DenseMatrixBase<T>(initializerList.begin()->size(), initializerList.size()) {
        data = new T[this->columns * this->rows];

        int r = 0;
        for (const auto& row : initializerList) {
            if (row.size() != this->columns)
                throw InvalidDimensionException("Nested initializer lists must all have the same size");

            int c = 0;
            for (const auto element : row) {
                DenseMatrix<T>::at(c, r) = element;
                c++;
            }
            r++;
        }
    }

    /**
     * @brief Copy constructor for DenseMatrix.
     *
     * Constructs a 'rows x columns' matrix and performs a deep copy of 'other'.
     * Allocates 'rows * columns * sizeof(T)' bytes on the heap.
     *
     * @param other DenseMatrix to copy from.
     */
    DenseMatrix(const DenseMatrix<T>& other) : DenseMatrixBase<T>(other.columns, other.rows) {
        data = new T[this->columns * this->rows];
        memcpy(data, other.data, this->columns * this->rows * sizeof(T));
    }

    /**
     * @brief Copy constructor from DenseMatrixBase.
     *
     * Constructs a 'rows x columns' matrix and performs a deep copy of 'other'.
     * Allocates 'rows * columns * sizeof(T)' bytes on the heap.
     *
     * @param other DenseMatrixBase to copy from.
     */
    DenseMatrix(const DenseMatrixBase<T>& other) : DenseMatrixBase<T>(other.columns, other.rows) {
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
    DenseMatrix(DenseMatrix<T>&& other) noexcept : DenseMatrixBase<T>(other.columns, other.rows) {
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

template<typename T = float>
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
     * @param columns Number of columns in the view.
     * @param rows Number of rows in the view.
     * @param colOffset Starting column offset in the owner matrix.
     * @param rowOffset Starting row offset in the owner matrix.
     */
    DenseMatrixView(const DenseMatrix<T>& owner, const int columns, const int rows, const int colOffset, const int rowOffset) : DenseMatrixBase<T>(columns, rows), stride(owner.rows), colOffset_(colOffset), rowOffset_(rowOffset) {
        data = owner.data;
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

/**
 * @brief Asserts that 'a' and 'b' have the same dimensions
 * @tparam T Scalar type of DenseMatrixBase<T>
 * @param a First matrix param
 * @param b Second matrix param
 * @param operation The name of the operation being done (e.g. "add", "multiply")
 * @throws InvalidDimensionException if the 'a' and 'b' matrices don't have the same dimensions
 */
template<typename T>
inline void assert_same_size(const DenseMatrixBase<T>& a, const DenseMatrixBase<T>& b, const std::string& operation) {
    if (a.columns != b.columns || a.rows != b.rows) {
        throw InvalidDimensionException(std::string("Cannot ") + operation + " with matrices of different size");
    }
}

/**
 * @brief Asserts that the 'a' matrix is square
 * @tparam T Scalar type of DenseMatrixBase<T>
 * @param m Matrix param
 * @param operation The name of the operation being done (e.g. "add", "multiply")
 * @throws InvalidDimensionException if the 'a' matrix is not square
 */
template<typename T>
inline void assert_square(const DenseMatrixBase<T>& m, const std::string& operation) {
    if (m.columns != m.rows) {
        throw InvalidDimensionException(std::string("Cannot") + operation + " with non square matrix");
    }
}

namespace Mathpp {
    /**
     * @brief Adds together all the matrices supplied
     * @tparam T Scalar type of DenseMatrix<T>
     * @tparam OTHERS The types of the other matrices being added (must derive fromm DenseMatrixBase)
     * @param a The first matrix param
     * @param others All the other matrices to be added to a
     * @return A DenseMatrix<T> made from adding each element of each matrix together
     */
    template<typename T, typename... OTHERS>
    DenseMatrix<std::common_type_t<T, typename OTHERS::ValueType...>> add(const DenseMatrixBase<T>& a, const OTHERS&... others) {
        static_assert((std::is_base_of_v<DenseMatrixBase<typename OTHERS::ValueType>, OTHERS> && ...), "All arguments must derive from DenseMatrixBase");
        (assert_same_size(a, others, "add"), ...);

        const int columns = a.columns;
        const int rows = a.rows;

        DenseMatrix<std::common_type_t<T, typename OTHERS::ValueType...>> result(a.columns, a.rows);

        std::cout << "looping" << std::endl;

        for (int c = 0; c < columns; c++) {
            for (int r = 0; r < rows; r++) {
                result[c, r] = (a[c, r] + ... + others[c, r]);
            }
        }

        return result;
    }
}

/**
 * Base class for all math Expressions.
 * To be used for operators ONLY.
 * Common uses are + and - operators,
 * where you do all additions and subtractions in one loop instead of multiple
 * @tparam RESULT What the Expression will get turned into implicitly
 * @tparam OTHERS The types of all the other parameters
 */
template<typename RESULT, typename... OTHERS>
struct Expression {
    // All the parameters being passed to the main function
    const std::tuple<const OTHERS&...> others;

    Expression(const OTHERS&... args) : others(args...) {}

    operator RESULT() const {
        return this->evaluate();
    }

    virtual RESULT evaluate() const = 0;

    virtual ~Expression() = default;
};

template<typename... OTHERS>
struct DenseMatrixSumExpr : Expression<DenseMatrix<std::common_type_t<typename OTHERS::ValueType...>>, OTHERS...> {
    using Expression<DenseMatrix<std::common_type_t<typename OTHERS::ValueType...>>, OTHERS...>::Expression;

    DenseMatrix<std::common_type_t<typename OTHERS::ValueType...>> evaluate() const override {
        return std::apply([](const auto&... args) {
            return Mathpp::add(args...);
        }, this->others);
    }

    template<typename OTHER>
    DenseMatrixSumExpr<OTHER, OTHERS...> operator+(const OTHER& other) const {
        return std::apply([&](const auto&... args) {
            return DenseMatrixSumExpr<OTHER, OTHERS...>(other, args...);
        }, this->others);
    }
};

template<typename T, typename OTHER_T>
DenseMatrixSumExpr<DenseMatrixBase<T>, DenseMatrixBase<OTHER_T>> operator+(const DenseMatrixBase<T>& a, const DenseMatrixBase<OTHER_T>& b) {
    return DenseMatrixSumExpr<DenseMatrixBase<T>, DenseMatrixBase<OTHER_T>>(a, b);
}

// template<typename T, typename OTHER_T>
// DenseMatrix<std::common_type_t<T, OTHER_T>> operator+(const DenseMatrixBase<T>& a, const DenseMatrixBase<OTHER_T>& b) {
//     return Mathpp::add(a, b);
// }

