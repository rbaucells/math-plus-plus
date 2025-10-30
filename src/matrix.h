#pragma once
#include <cassert>
#include <sstream>
#include <stdexcept>
#include <string>
#include "rotation.h"
#include "vector.h"

template<int COLUMNS, int ROWS, typename T = float>
struct Matrix {
    const int rows = ROWS;
    const int columns = COLUMNS;
    static const bool square = ROWS == COLUMNS;

    T data[COLUMNS][ROWS] = {};

    Matrix() = default;

    Matrix(std::initializer_list<std::initializer_list<T>> initializerList) {
        if (initializerList.size() != ROWS) {
            throw std::runtime_error("Incorrect number of rows in initializer list");
        }

        int r = 0;
        for (const auto& row : initializerList) {
            if (row.size() != COLUMNS) {
                throw std::runtime_error("Incorrect number of columns in initializer list");
            }

            int c = 0;

            for (const auto element : row) {
                data[c][r] = element;
                c++;
            }

            r++;
        }
    }

    // copy constructor with same type
    Matrix(const Matrix<COLUMNS, ROWS, T>& other) {
        memcpy(data, other.data, sizeof(T) * ROWS * COLUMNS);
    }

    // copy constructor with different type
    template<IsConvertableTo<T> OTHER_T>
    Matrix(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] = other.data[c][r];
            }
        }
    }

#pragma region Same Type Operators
    // copy assignment operator with same type
    Matrix<COLUMNS, ROWS, T>& operator=(const Matrix<COLUMNS, ROWS, T>& other) {
        if (this != &other) {
            memcpy(data, other.data, sizeof(T) * COLUMNS * ROWS);
        }

        return *this;
    }

    [[nodiscard]] Matrix<COLUMNS, ROWS, T> add(const Matrix<COLUMNS, ROWS, T>& other) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] + other.data[c][r];
            }
        }

        return result;
    }

    Matrix<COLUMNS, ROWS, T> operator+(const Matrix<COLUMNS, ROWS, T>& other) const {
        return add(other);
    }

    void addEquals(const Matrix<COLUMNS, ROWS, T>& other) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] += other.data[c][r];
            }
        }
    }

    Matrix<COLUMNS, ROWS, T>& operator+=(const Matrix<COLUMNS, ROWS, T>& other) {
        addEquals(other);
        return *this;
    }
    [[nodiscard]] Matrix<COLUMNS, ROWS, T> subtract(const Matrix<COLUMNS, ROWS, T>& other) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] - other.data[c][r];
            }
        }

        return result;
    }

    Matrix<COLUMNS, ROWS, T> operator-(const Matrix<COLUMNS, ROWS, T>& other) const {
        return subtract(other);
    }

    void subtractEquals(const Matrix<COLUMNS, ROWS, T>& other) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] -= other.data[c][r];
            }
        }
    }

    Matrix<COLUMNS, ROWS, T> operator-=(const Matrix<COLUMNS, ROWS, T>& other) {
        subtractEquals(other);
        return *this;
    }

    /**
   * @brief Multiplies this matrix by other. (this x other)
   * @param other Matrix to multiply this * other
   * @return The product of the two matrix. Having Number of rows as this, and number of columns as other
   */
    template<int OTHER_COLUMNS>
    Matrix<OTHER_COLUMNS, ROWS, T> multiply(const Matrix<OTHER_COLUMNS, COLUMNS, T>& other) const {
        Matrix<OTHER_COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                for (int x = 0; x < COLUMNS; x++) {
                    result[c][r] += data[x][r] * other.data[c][x];
                }
            }
        }

        return result;
    }

    template<int OTHER_COLUMNS>
    Matrix<OTHER_COLUMNS, ROWS, T> operator*(const Matrix<OTHER_COLUMNS, COLUMNS, T>& other) const {
        return multiply(other);
    }

    /**
     * @brief Compares this matrix with the other (this == other)
     * @param other The Matrix to compare against
     * @return Weather or not the two matrices have the same data
     */
    [[nodiscard]] bool compare(const Matrix<COLUMNS, ROWS, T>& other) const {
        if constexpr (std::is_floating_point_v<T>) {
            T epsilon = std::numeric_limits<T>::epsilon();
            for (int c = 0; c < COLUMNS; c++) {
                for (int r = 0; r < ROWS; r++) {
                    if (std::abs(other.data[c][r] - data[c][r]) > epsilon)
                        return false;
                }
            }

            return true;
        }
        else {
            for (int c = 0; c < COLUMNS; c++) {
                for (int r = 0; r < ROWS; r++) {
                    if (other.data[c][r] == data[c][r])
                        return false;
                }
            }

            return false;
        }
    }

    bool operator==(const Matrix<COLUMNS, ROWS, T>& other) const {
        return compare(other);
    }

#pragma endregion
#pragma region Different Type Operators
    // copy assignment operator with different type
    template<IsConvertableTo<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T>& operator=(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        if (*this != other) {
            for (int c = 0; c < COLUMNS; c++) {
                for (int r = 0; r < ROWS; r++) {
                    data[c][r] = other.data[c][r];
                }
            }
        }

        return *this;
    }

    template<IsConvertableTo<T> OTHER_T>
    [[nodiscard]] Matrix<COLUMNS, ROWS, T> add(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] + other.data[c][r];
            }
        }

        return result;
    }

    template<IsConvertableTo<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T> operator+(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        return add(other);
    }

    template<IsConvertableTo<T> OTHER_T>
    void addEquals(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] += other.data[c][r];
            }
        }
    }

    template<IsConvertableTo<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T>& operator+=(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        addEquals(other);
        return *this;
    }

    template<IsConvertableTo<T> OTHER_T>
    [[nodiscard]] Matrix<COLUMNS, ROWS, T> subtract(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] - other.data[c][r];
            }
        }

        return result;
    }

    template<IsConvertableTo<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T> operator-(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        return subtract(other);
    }

    template<IsConvertableTo<T> OTHER_T>
    void subtractEquals(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] -= other.data[c][r];
            }
        }
    }

    template<IsConvertableTo<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T>& operator-=(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        subtractEquals(other);
        return *this;
    }

    /**
   * @brief Multiplies this matrix by other. (this x other)
   * @param other Matrix to multiply this * other
   * @return The product of the two matrix. Having Number of rows as this, and number of columns as other
   */
    template<int OTHER_COLUMNS, IsConvertableTo<T> OTHER_T>
    Matrix<OTHER_COLUMNS, ROWS, T> multiply(const Matrix<OTHER_COLUMNS, COLUMNS, OTHER_T>& other) const {
        Matrix<OTHER_COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                for (int x = 0; x < COLUMNS; x++) {
                    result[c][r] += data[x][r] * other.data[c][x];
                }
            }
        }

        return result;
    }

    template<int OTHER_COLUMNS, IsConvertableTo<T> OTHER_T>
    Matrix<OTHER_COLUMNS, ROWS, T> operator*(const Matrix<OTHER_COLUMNS, COLUMNS, OTHER_T>& other) const {
        return multiply(other);
    }

    /**
     * @brief Compares this matrix with the other (this == other)
     * @param other The Matrix to compare against
     * @return Weather or not the two matrices have the same data
     */
    template<IsConvertableTo<T> OTHER_T>
    [[nodiscard]] bool compare(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        if constexpr (std::is_floating_point_v<T>) {
            T epsilon = std::numeric_limits<T>::epsilon();
            for (int c = 0; c < COLUMNS; c++) {
                for (int r = 0; r < ROWS; r++) {
                    if (std::abs(static_cast<T>(other.data[c][r]) - data[c][r]) > epsilon)
                        return false;
                }
            }

            return true;
        }
        else {
            for (int c = 0; c < COLUMNS; c++) {
                for (int r = 0; r < ROWS; r++) {
                    if (static_cast<T>(other.data[c][r]) == data[c][r])
                        return false;
                }
            }

            return false;
        }
    }

    template<IsConvertableTo<T> OTHER_T>
    bool operator==(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        return compare(other);
    }

#pragma endregion

    // subscript
    T* operator[](const int index) {
        return &data[index][0];
    }

    // const subscript
    const T* operator[](const int index) const {
        return &data[index][0];
    }

    /**
     * @brief Swaps elements on row r and column c to row c and column r (Reflection across main diagonal; data[c][r] = data[r][c])
     * @note Matrix must be a square matrix (n x n)
     * @return Matrix with columns and rows swapped
     */
    [[nodiscard]] Matrix<ROWS, COLUMNS, T> transpose() const {
        Matrix<ROWS, COLUMNS, T> result;

        for (int c = 0; c < ROWS; c++) {
            for (int r = 0; r < COLUMNS; r++) {
                result[c][r] = data[r][c];
            }
        }

        return result;
    }

    /**
     * @brief Finds the inverse of the matrix if invertible (1 / matrix)
     * @throws Runtime errors if matrix is singular (not invertible)
     * @return The inverse of the matrix
     */
    [[nodiscard]] Matrix<COLUMNS, ROWS, T> inverse() const requires (square) {
        // its a one by one, we can just return 1 / value
        if constexpr (ROWS == 1) {
            if (data[0][0] == 0) {
                throw std::runtime_error("Cannot find inverse of singular matrix");
            }

            Matrix<1, 1, T> result;

            result[0][0] = 1 / data[0][0];
            return result;
        }
        // its a two by two, we can do the special fast thing
        else if constexpr (ROWS == 2) {
            T det = determinant();

            if (det == 0) {
                throw std::runtime_error("Cannot find inverse of singular matrix");
            }

            Matrix<2, 2, T> result;

            result[0][0] = data[1][1] / det;
            result[0][1] = -data[0][1] / det;
            result[1][0] = -data[1][0] / det;
            result[1][1] = data[0][0] / det;

            return result;
        }
        else {
            const Matrix<COLUMNS, ROWS, T> identityMatrix = Matrix<COLUMNS, ROWS, T>::identity();
            Matrix<COLUMNS * 2, ROWS, T> temp;

            for (int c = 0; c < COLUMNS; c++) {
                for (int r = 0; r < ROWS; r++) {
                    temp[c][r] = data[c][r];
                }
            }

            for (int c = 0; c < COLUMNS; c++) {
                for (int r = 0; r < ROWS; r++) {
                    temp[c + COLUMNS][r] = identityMatrix[c][r];
                }
            }

            for (int c = 0; c < COLUMNS; c++) {
                // if the pivot is zero
                if (temp[c][c] == 0) {
                    int rowIndex = -1;
                    for (int r = c + 1; r < ROWS; r++) {
                        if (temp[c][r] != 0 && (rowIndex == -1 || std::abs(temp[c][r]) > std::abs(temp[c][rowIndex]))) {
                            rowIndex = r;
                        }
                    }

                    if (rowIndex == -1) {
                        throw std::runtime_error("Cannot find inverse of singular matrix");
                    }

                    // since c (column) = r (row), the dest row is at temp[row (aka, c}] the src row is the memory address of the start of the biggest row so &temp[c][biggestRow]
                    temp = temp.swapRows(c, rowIndex);
                }

                // normalize pivot row to 1
                T value = temp[c][c];
                for (int cc = c + 1; cc < temp.columns; cc++) {
                    temp[cc][c] /= value;
                }
                temp[c][c] = 1;

                for (int r = 0; r < ROWS; r++) {
                    // the current value is on the main diagonal. (expected to be a 1). Should be good
                    if (r == c) {
                        // we dont want to affect the pivot
                        continue;
                    }
                    // it isnt on the main diagonal, (expected to be a 0)
                    T k = temp[c][r];
                    for (int cc = c + 1; cc < temp.columns; cc++) {
                        temp[cc][r] += -k * temp[cc][c];
                    }
                    temp[c][r] = 0;
                }
            }

            Matrix<COLUMNS, ROWS, T> result;

            for (int c = 0; c < COLUMNS; ++c) {
                for (int r = 0; r < ROWS; r++) {
                    result[c][r] = temp[c + COLUMNS][r];
                }
            }

            return result;
        }
    }

    /**
     * @warning if zero do not attempt to find inverse of this matrix
     * @return The determinant of this matrix
     */
    [[nodiscard]] T determinant() const requires (square) {
        if constexpr (ROWS == 1) {
            return data[0][0];
        }
        else if constexpr (ROWS == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }
        else {
            T result = 0;
            int sign = 1;

            for (int c = 0; c < COLUMNS; c++) {
                Matrix<COLUMNS - 1, ROWS - 1, T> insideMatrix = getSubMatrix(0, c);

                result += sign * data[c][0] * insideMatrix.determinant();
                sign *= -1;
            }

            return result;
        }
    }

#pragma region 4x4 stuffs
    /**
     * @brief Uniformly scales the matrix along all dimensions (this * scaleMatrix)
     * @param value The scalar to multiply with each element
     * @return The matrix scaled Uniformly
     */
    [[nodiscard]] Matrix<4, 4, T> scale(const T value) const requires (square && COLUMNS == 4) {
        Matrix<4, 4, T> scalingMatrix = Matrix<4, 4, T>::identity();

        scalingMatrix.data[0][0] = value;
        scalingMatrix.data[1][1] = value;
        scalingMatrix.data[2][2] = value;

        return multiply(scalingMatrix);
    }

    /**
     * @brief Scales matrix non-uniformly along the x, y, and z axis (this * scaleMatrix)
     * @param x The scale factor for the x-axis.
     * @param y The scale factor for the y-axis.
     * @param z The scale factor for the z-axis.
     * @return The matrix scaled along {x, y, z}
     */
    [[nodiscard]] Matrix<4, 4, T> scaleAnisotropic(const T x, const T y, const T z) const requires (square && COLUMNS == 4) {
        Matrix<4, 4, T> scaleMatrix = Matrix<4, 4, T>::identity();

        scaleMatrix.data[0][0] = x;
        scaleMatrix.data[1][1] = y;
        scaleMatrix.data[2][2] = z;

        return multiply(scaleMatrix);
    }

    /**
     * @brief Translates matrix by x, y, and z (this * translationMatrix)
     * @param x How much to translate along the x
     * @param y How much to translate along the y
     * @param z How much to translate along the z
     * @return The matrix translated by x, y, and z
     */
    [[nodiscard]] Matrix<4, 4, T> translate(const T x, const T y, const T z) const requires (square && COLUMNS == 4) {
        Matrix<4, 4, T> translationMatrix = Matrix<4, 4, T>::identity();

        translationMatrix.data[3][0] = x;
        translationMatrix.data[3][1] = y;
        translationMatrix.data[3][2] = z;

        return multiply(translationMatrix);
    }

    /**
     * @brief Rotates the matrix by angle along the x (this * rotationMatrix)
     * @param amount How many DEGREES to rotate along the x
     * @param type Rotation type of angle
     * @return Matrix rotated by angle
     */
    [[nodiscard]] Matrix<4, 4, T> rotateX(const T amount, const RotationType type = RotationType::degrees) const requires (square && COLUMNS == 4) {
        T sin = std::sin(convert(type, RotationType::radians, amount));
        T cos = std::cos(convert(type, RotationType::radians, amount));

        Matrix<4, 4, T> rotationMatrix = Matrix<4, 4, T>::identity();

        rotationMatrix.data[1][1] = cos;
        rotationMatrix.data[2][1] = -sin;
        rotationMatrix.data[1][2] = sin;
        rotationMatrix.data[2][2] = cos;

        return multiply(rotationMatrix);
    }

    /**
     * @brief Rotates the matrix by angle along the y (this * rotationMatrix)
     * @param amount How many DEGREES to rotate along the y
     * * @param type Rotation type of angle
     * @return Matrix rotated by angle
     */
    [[nodiscard]] Matrix<4, 4, T> rotateY(const T amount, const RotationType type = RotationType::degrees) const requires (square && COLUMNS == 4) {
        T sin = std::sin(convert(type, RotationType::radians, amount));
        T cos = std::cos(convert(type, RotationType::radians, amount));

        Matrix<4, 4, T> rotationMatrix = Matrix<4, 4, T>::identity();

        rotationMatrix.data[0][0] = cos;
        rotationMatrix.data[2][0] = sin;
        rotationMatrix.data[0][2] = -sin;
        rotationMatrix.data[2][2] = cos;

        return multiply(rotationMatrix);
    }

    /**
     * @brief Rotates the matrix by angle along the y (this * rotationMatrix)
     * @param amount How many DEGREES to rotate along the y
     * * @param type Rotation type of angle
     * @return Matrix rotated by angle
     */
    [[nodiscard]] Matrix<4, 4, T> rotateZ(const T amount, const RotationType type = RotationType::degrees) const requires (square && COLUMNS == 4) {
        T sin = std::sin(convert(type, RotationType::radians, amount));
        T cos = std::cos(convert(type, RotationType::radians, amount));

        Matrix<4, 4, T> rotationMatrix = Matrix<4, 4, T>::identity();

        rotationMatrix.data[0][0] = cos;
        rotationMatrix.data[1][0] = -sin;
        rotationMatrix.data[0][1] = sin;
        rotationMatrix.data[1][1] = cos;

        return multiply(rotationMatrix);
    }

    /**
     * @brief Creates an orthographic projection matrix.
     * @param left The coordinate of the left vertical clipping plane
     * @param right The coordinate of the right vertical clipping plane
     * @param bottom The coordinate of the bottom horizontal clipping plane
     * @param top The coordinate of the top horizontal clipping plane
     * @param near The coordinate of the near depth clipping plane
     * @param far The coordinate of the far depth clipping plane
     * @return A 4x4 orthographic projection matrix
     */
    static Matrix<4, 4, T> ortho(const T left, const T right, const T bottom, const T top, const T near, const T far) {
        // identity
        Matrix<4, 4, T> transformation = Matrix<4, 4, T>::identity();
        // transformation
        transformation.data[0][0] = 2.0f / (right - left);
        transformation.data[1][1] = 2.0f / (top - bottom);
        transformation.data[2][2] = -2.0f / (far - near);
        transformation.data[3][0] = -(right + left) / (right - left);
        transformation.data[3][1] = -(top + bottom) / (top - bottom);
        transformation.data[3][2] = -(far + near) / (far - near);
        // return
        return transformation;
    }

#pragma endregion

    [[nodiscard]] std::string toString() const {
        std::stringstream ss;
        ss.precision(2);

        ss << "[";

        for (int r = 0; r < ROWS; r++) {
            ss << "[";
            for (int c = 0; c < COLUMNS; c++) {
                ss << data[c][r];

                if (c < COLUMNS - 1)
                    ss << ", ";
            }

            ss << "]";

            if (r < ROWS - 1)
                ss << ", ";
        }

        ss << "]";
        return ss.str();
    }

    [[nodiscard]] std::string toLaTex() const {
        std::stringstream ss;
        ss.precision(2);

        ss << "\\begin{bmatrix}";

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLUMNS; c++) {
                ss << data[c][r];

                if (c < COLUMNS - 1)
                    ss << " & ";
            }

            if (r < ROWS - 1)
                ss << "\\\\";
        }

        ss << "\\end{bmatrix}";
        return ss.str();
    }

    /**
     * @brief Makes a matrix made up of this matrix without rowToRemove and without columnToRemove
     * @param rowToRemove What row shouldnt be included
     * @param columnToRemove What column shouldnt be included
     * @return A matrix of <ROWS - 1, COLUMNS - 1> without the rowToRemove and columnToRemove
     */
    [[nodiscard]] Matrix<COLUMNS - 1, ROWS - 1, T> getSubMatrix(const int rowToRemove, const int columnToRemove) const {
        Matrix<COLUMNS - 1, ROWS - 1, T> subMatrix;
        int subMatrixR = 0;
        for (int r = 0; r < ROWS; r++) {
            if (r == rowToRemove)
                continue;

            int subMatrixC = 0;
            for (int c = 0; c < COLUMNS; c++) {
                if (c == columnToRemove)
                    continue;

                subMatrix.data[subMatrixC][subMatrixR] = data[c][r];
                subMatrixC++;
            }
            subMatrixR++;
        }

        return subMatrix;
    }

    /**
     * @brief swap row a with row b
     * @param rowA The index of the first row
     * @param rowB The index of the second row
     * @return This with row a and row b swapped
     */
    Matrix<COLUMNS, ROWS, T> swapRows(const int rowA, const int rowB) {
        Matrix<COLUMNS, ROWS, T> m = *this;

        T temp[COLUMNS] = {};

        for (int c = 0; c < COLUMNS; c++) {
            temp[c] = m[c][rowA];
        }

        for (int c = 0; c < COLUMNS; c++) {
            m[c][rowA] = m[c][rowB];
        }

        for (int c = 0; c < COLUMNS; c++) {
            m[c][rowB] = temp[c];
        }

        return m;
    }

    /**
     * @brief swap column a with column b
     * @param columnA The index of the first column
     * @param columnB The index of the second column
     * @return This with column a and column b swapped
     */
    Matrix<COLUMNS, ROWS, T> swapColumns(const int columnA, const int columnB) {
        Matrix<COLUMNS, ROWS, T> m = *this;

        T temp[ROWS] = {};

        for (int r = 0; r < ROWS; r++) {
            temp[r] = m[columnA][r];
        }

        for (int r = 0; r < COLUMNS; r++) {
            m[columnA][r] = m[columnB][r];
        }

        for (int r = 0; r < COLUMNS; r++) {
            m[columnB][r] = temp[r];
        }

        return m;
    }

    explicit operator const T*() const {
        return &data[0][0];
    }

    explicit operator T*() {
        return &data[0][0];
    }

    /**
     * @brief Generates the identity matrix of size this Rows x this Rows
     * @return Matrix with 1s on main diagonal, 0s everywhere else
     */
    static Matrix<COLUMNS, ROWS, T> identity() requires (square) {
        Matrix<COLUMNS, ROWS, T> result;

        for (int i = 0; i < COLUMNS; i++) {
            result[i][i] = 1;
        }

        return result;
    }
};