#pragma once

#include <regex>
#include <string>
#include "helper.h"
#include "vector.h"
#include <optional>

template<int ROWS, int COLUMNS, scalar T = float>
struct Matrix {
    static constexpr int columns = COLUMNS;
    static constexpr int rows = ROWS;

    static constexpr bool isSquare = ROWS == COLUMNS;
    static constexpr bool isComplex = is_complex_v<T>;

    using ValueType = T;
    using UnderlyingType = underlying_type<T>::value_type;

    T data[COLUMNS][ROWS] = {};

    Matrix() = default;

    constexpr Matrix(std::initializer_list<std::initializer_list<T>> initializerList);

    Matrix(const Matrix<ROWS, COLUMNS, T>& other);

    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Matrix(const Matrix<ROWS, COLUMNS, OTHER_T>& other);

    static Matrix<ROWS, COLUMNS, T> random(UnderlyingType min = -1, UnderlyingType max = 1);

    // m = m
    Matrix<ROWS, COLUMNS, T>& operator=(const Matrix<ROWS, COLUMNS, T>& other);

    // m == m
    bool equals(const Matrix<ROWS, COLUMNS, T>& other, underlying_type_t<T> precision = ::epsilon<T>()) const;
    bool operator==(const Matrix<ROWS, COLUMNS, T>& other) const;

    // m + m
    Matrix<ROWS, COLUMNS, T> add(const Matrix<ROWS, COLUMNS, T>& other) const;
    Matrix<ROWS, COLUMNS, T> operator+(const Matrix<ROWS, COLUMNS, T>& other) const;

    // m - m
    Matrix<ROWS, COLUMNS, T> subtract(const Matrix<ROWS, COLUMNS, T>& other) const;
    Matrix<ROWS, COLUMNS, T> operator-(const Matrix<ROWS, COLUMNS, T>& other) const;

    // m * m
    template<int OTHER_COLUMNS>
    Matrix<ROWS, OTHER_COLUMNS, T> multiply(const Matrix<COLUMNS, OTHER_COLUMNS, T>& other) const;
    template<int OTHER_COLUMNS>
    Matrix<ROWS, OTHER_COLUMNS, T> operator*(const Matrix<COLUMNS, OTHER_COLUMNS, T>& other) const;

    // m * v
    Vector<COLUMNS, T> multiply(const Vector<COLUMNS, T>& other) const;
    Vector<COLUMNS, T> operator*(const Vector<COLUMNS, T>& other) const;

    // m * #
    Matrix<ROWS, COLUMNS, T> multiply(T val) const;
    Matrix<ROWS, COLUMNS, T> operator*(T val) const;

    // m / #
    Matrix<ROWS, COLUMNS, T> divide(T scalar) const;
    Matrix<ROWS, COLUMNS, T> operator/(T scalar) const;

    // m += m
    Matrix<ROWS, COLUMNS, T>& addEquals(const Matrix<ROWS, COLUMNS, T>& other);
    Matrix<ROWS, COLUMNS, T>& operator+=(const Matrix<ROWS, COLUMNS, T>& other);

    // m -= m
    Matrix<ROWS, COLUMNS, T>& subtractEquals(const Matrix<ROWS, COLUMNS, T>& other);
    Matrix<ROWS, COLUMNS, T> operator-=(const Matrix<ROWS, COLUMNS, T>& other);

    // m *= #
    Matrix<ROWS, COLUMNS, T>& multiplyEquals(T val);
    Matrix<ROWS, COLUMNS, T>& operator*=(T val);

    // m /= #
    Matrix<ROWS, COLUMNS, T>& divideEquals(T scalar);
    Matrix<ROWS, COLUMNS, T>& operator/=(T scalar);

    // m = m
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Matrix<ROWS, COLUMNS, T>& operator=(const Matrix<ROWS, COLUMNS, OTHER_T>& other);

    // m == m
    template<typename OTHER_T> requires std::equality_comparable_with<underlying_type_t<OTHER_T>, underlying_type_t<T>>
    bool equals(const Matrix<ROWS, COLUMNS, OTHER_T>& other, std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHER_T>> precision = epsilon<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHER_T>>>()) const;
    template<typename OTHER_T> requires std::equality_comparable_with<underlying_type_t<OTHER_T>, underlying_type_t<T>>
    bool operator==(const Matrix<ROWS, COLUMNS, OTHER_T>& other) const;

    // m + m
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> add(const Matrix<ROWS, COLUMNS, OTHER_T>& other) const;
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> operator+(const Matrix<ROWS, COLUMNS, OTHER_T>& other) const;

    // m - m
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> subtract(const Matrix<ROWS, COLUMNS, OTHER_T>& other) const;
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> operator-(const Matrix<ROWS, COLUMNS, OTHER_T>& other) const;

    // m * m
    template<int OTHER_COLUMNS, typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS, OTHER_COLUMNS, std::common_type_t<T, OTHER_T>> multiply(const Matrix<COLUMNS, OTHER_COLUMNS, OTHER_T>& other) const;
    template<int OTHER_COLUMNS, typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS, OTHER_COLUMNS, std::common_type_t<T, OTHER_T>> operator*(const Matrix<COLUMNS, OTHER_COLUMNS, OTHER_T>& other) const;

    // m * v
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<COLUMNS, std::common_type_t<T, OTHER_T>> multiply(const Vector<COLUMNS, OTHER_T>& other) const;
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<COLUMNS, std::common_type_t<T, OTHER_T>> operator*(const Vector<COLUMNS, OTHER_T>& other) const;

    // m * #
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> multiply(OTHER_T val) const;
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> operator*(OTHER_T val) const;

    // m / #
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> divide(OTHER_T scalar) const;
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> operator/(OTHER_T scalar) const;

    // m += m
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Matrix<ROWS, COLUMNS, T>& addEquals(const Matrix<ROWS, COLUMNS, OTHER_T>& other);
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Matrix<ROWS, COLUMNS, T>& operator+=(const Matrix<ROWS, COLUMNS, OTHER_T>& other);

    // m -= m
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Matrix<ROWS, COLUMNS, T>& subtractEquals(const Matrix<ROWS, COLUMNS, OTHER_T>& other);
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Matrix<ROWS, COLUMNS, T> operator-=(const Matrix<ROWS, COLUMNS, OTHER_T>& other);

    // m *= #
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Matrix<ROWS, COLUMNS, T>& multiplyEquals(OTHER_T val);
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Matrix<ROWS, COLUMNS, T>& operator*=(OTHER_T val);

    // m /= #
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Matrix<ROWS, COLUMNS, T>& divideEquals(OTHER_T scalar);
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Matrix<ROWS, COLUMNS, T>& operator/=(OTHER_T scalar);

    template<int N>
    Vector<N, T> applyHomogeneousTransformation(const Vector<N, T>& point) const requires (isSquare);
    template<int N, typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<N, std::common_type_t<T, OTHER_T>> applyHomogeneousTransformation(const Vector<N, OTHER_T>& point) const requires (isSquare);

    T* operator[](int index);
    const T* operator[](int index) const;

    Matrix<ROWS, COLUMNS, T> operator-() const;

    Matrix<COLUMNS, ROWS, T> transpose() const;
    Matrix<COLUMNS, ROWS, T> conjugateTranspose() const;

    Matrix<ROWS, COLUMNS, T> inverse() const requires (isSquare);

    enum class DeterminantAlgorithm {
        laplace,
        triangular,
        tridiagonal,
        lu
    };

    T determinant(DeterminantAlgorithm algorithm = DeterminantAlgorithm::laplace) const requires (isSquare);

private:
    T laplaceDeterminant() const requires (isSquare);
    T triangularDeterminant() const requires (isSquare);
    T tridiagonalDeterminant() const requires (isSquare);
    T luDeterminant() const requires (isSquare);

public:
    static Matrix<ROWS, COLUMNS, T> scalingMatrix(const Vector<COLUMNS, T>& factors) requires (isSquare);
    static Matrix<ROWS, COLUMNS, T> shearMatrix(int i, int j, T k) requires (isSquare);
    static Matrix<ROWS, COLUMNS, T> squeezeMatrix(int i, int j, T k) requires (isSquare);

    static Matrix<ROWS, COLUMNS, T> rotationMatrixAboutOrigin(T rot, RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS == 2);
    static Matrix<ROWS + 1, COLUMNS + 1, T> rotationMatrixAboutPoint(const Vector<COLUMNS, T>& p, T rot, RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS == 2);
    static Matrix<ROWS, COLUMNS, T> rotationMatrixAroundAxisThroughOrigin(const Vector<COLUMNS, T>& axis, T rot, RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS == 3);
    static Matrix<ROWS + 1, COLUMNS + 1, T> rotationMatrixAroundAxisNotThroughOrigin(const Vector<COLUMNS, T>& axis, const Vector<COLUMNS, T>& point, T rot, RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS == 3);
    static Matrix<ROWS, COLUMNS, T> rotationMatrixInPlaneThroughOrigin(const Vector<COLUMNS, T>& v1, const Vector<COLUMNS, T>& v2, T rot, RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS >= 3);
    static Matrix<ROWS, COLUMNS, T> rotationMatrixInPLaneNotThroughOrigin(const Vector<COLUMNS, T>& v1, const Vector<COLUMNS, T>& v2, const Vector<COLUMNS, T>& point, T rot, RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS >= 3);

    static Matrix<ROWS, COLUMNS, T> reflectionMatrixAlongAxisThroughOrigin(const Vector<COLUMNS, T>& axis) requires (isSquare);
    static Matrix<ROWS + 1, COLUMNS + 1, T> reflectionMatrixAlongAxisNotThroughOrigin(const Vector<COLUMNS, T>& axis, const Vector<COLUMNS, T>& point) requires (isSquare);

    static Matrix<ROWS + 1, COLUMNS + 1, T> translationMatrix(const Vector<COLUMNS, T>& translation) requires (isSquare);

    static Matrix<ROWS, COLUMNS, T> orthoMatrix(T left, T right, T bottom, T top, T near, T far) requires (isSquare && COLUMNS == 4);

    [[nodiscard]] std::string toString() const;
    [[nodiscard]] std::string toLaTex() const;

    template<int NUM_COLUMNS_TO_REMOVE>
    Matrix<ROWS, COLUMNS - NUM_COLUMNS_TO_REMOVE, T> removeColumns(const std::array<int, NUM_COLUMNS_TO_REMOVE>& columnsToRemove) const;
    template<int NUM_ROWS_TO_REMOVE>
    Matrix<ROWS, COLUMNS - NUM_ROWS_TO_REMOVE, T> removeRows(const std::array<int, NUM_ROWS_TO_REMOVE>& rowsToRemove) const;
    template<int NUM_COLUMNS_TO_REMOVE, int NUM_ROWS_TO_REMOVE>
    Matrix<ROWS, COLUMNS - NUM_COLUMNS_TO_REMOVE - NUM_ROWS_TO_REMOVE, T> removeColumnsAndRows(const std::array<int, NUM_COLUMNS_TO_REMOVE>& columnsToRemove, const std::array<int, NUM_ROWS_TO_REMOVE>& rowsToRemove) const;

    Matrix<ROWS, COLUMNS - 1, T> removeColumn(int columnToRemove) const;
    Matrix<ROWS, COLUMNS - 1, T> removeRow(int rowToRemove) const;
    Matrix<ROWS - 1, COLUMNS - 1, T> removeColumnAndRow(int columnToRemove, int rowToRemove) const;

    Matrix<ROWS, COLUMNS, T> swapRows(int rowA, int rowB) const;
    Matrix<ROWS, COLUMNS, T> swapColumns(int columnA, int columnB) const;

    explicit operator const T*() const;

    explicit operator T*();

    constexpr static Matrix<ROWS, COLUMNS, T> identity() requires (isSquare);

    [[nodiscard]] bool isRowEchelon(bool pivotMustBeOne = false) const;
    Matrix<ROWS, COLUMNS, T> toRowEchelon(bool doRowSwaps = true) const;

    [[nodiscard]] bool isReducedRowEchelon() const;
    Matrix<ROWS, COLUMNS, T> toReducedRowEchelon() const;

    [[nodiscard]] bool isRowEchelonOfThis(const Matrix<ROWS, COLUMNS, T>& ref, UnderlyingType precision = 0.01) const;

    [[nodiscard]] int rank() const;

    [[nodiscard]] bool isSymmetrical() const requires (isSquare);
    [[nodiscard]] bool isSkewSymmetrical() const requires (isSquare);

    [[nodiscard]] bool isHermitian() const requires (isSquare);
    [[nodiscard]] bool isSkewHermitian() const requires (isSquare);

    template<int K>
    Matrix<K, K, T> upperLeftSubMatrix() const requires (isSquare);

    Matrix<ROWS, COLUMNS, T> symmetricPart() const requires (isSquare);
    Matrix<ROWS, COLUMNS, T> antiSymmetricPart() const requires (isSquare);

    Matrix<ROWS, COLUMNS, T> hermitianPart() const requires (isSquare);
    Matrix<ROWS, COLUMNS, T> antiHermitianPart() const requires (isSquare);

    enum class PositiveDefiniteAlgorithm {
        cholesky,
        cholesky_non_symmetric,
        ldl,
        ldl_non_symmetric,
        pivots,
        pivots_non_symmetric,
        sylvester,
        sylvester_non_symmetric,
    };

    [[nodiscard]] bool isPositiveDefinite(PositiveDefiniteAlgorithm algorithm = PositiveDefiniteAlgorithm::sylvester) const requires (isSquare);

private:
    template<int K = 1>
    [[nodiscard]] bool isPositiveDefiniteSylvester() const requires (isSquare);
    [[nodiscard]] bool isPositiveDefiniteLdl() const requires (isSquare);
    [[nodiscard]] bool isPositiveDefiniteCholesky() const requires (isSquare);
    [[nodiscard]] bool isPositiveDefinitePivots() const requires (isSquare);

public:
    enum class PositiveSemiDefiniteAlgorithm {
        sylvester,
        sylvester_non_symmetric,
        ldl,
        ldl_non_symmetric
    };

    [[nodiscard]] bool isPositiveSemiDefinite(PositiveSemiDefiniteAlgorithm algorithm = PositiveSemiDefiniteAlgorithm::sylvester) const requires (isSquare);

private:
    template<int K = 1>
    [[nodiscard]] bool isPositiveSemiDefiniteSylvester() const requires (isSquare);
    [[nodiscard]] bool isPositiveSemiDefiniteLdl() const requires (isSquare);
    [[nodiscard]] bool isPositiveSemiDefinitePivots() const requires (isSquare);

public:
    [[nodiscard]] bool isNegativeDefinite() const requires (isSquare);
    [[nodiscard]] bool isNegativeSemiDefinite() const requires (isSquare);

    Vector<ROWS, T> getColumnVector(int i) const;
    std::array<Vector<ROWS>, COLUMNS> getColumnVectors() const;
    Vector<COLUMNS, T> getRowVector(int i) const;
    std::array<Vector<COLUMNS>, ROWS> getRowVectors() const;

    void setColumnVectors(const std::array<Vector<ROWS, T>, COLUMNS>& columnVectors);
    void setColumnVector(int i, const Vector<ROWS, T>& v);
    void setRowVectors(std::array<Vector<COLUMNS, T>, ROWS> rowVectors);
    void setRowVector(int i, const Vector<COLUMNS, T>& v);

    T trace() const requires (isSquare);

    [[nodiscard]] bool isUnitary() const requires (isSquare);
    [[nodiscard]] bool isSpecialUnitary() const requires (isSquare);

    [[nodiscard]] bool isOrthogonal() const requires (!isComplex && isSquare);
    [[nodiscard]] bool isSpecialOrthogonal() const requires (!isComplex && isSquare);

    [[nodiscard]] bool isSemiOrthogonal() const requires (!isComplex && !isSquare);

    [[nodiscard]] bool isUpperTriangleMatrix() const requires (isSquare);
    [[nodiscard]] bool isLowerTriangleMatrix() const requires (isSquare);

    [[nodiscard]] bool isDiagonalMatrix() const requires (isSquare);

    [[nodiscard]] bool isUpperUnitriangularMatrix() const requires (isSquare);
    [[nodiscard]] bool isLowerUnitriangularMatrix() const requires (isSquare);

    [[nodiscard]] bool isStrictlyUpperTriangularMatrix() const requires (isSquare);
    [[nodiscard]] bool isStrictlyLowerTriangularMatrix() const requires (isSquare);

    [[nodiscard]] bool isFrobeniusMatrix() const requires (isSquare);

    Vector<ROWS, T> forwardSubstitution(const Vector<ROWS, T>& b) const requires (isSquare);
    Vector<ROWS, T> backwardSubstitution(const Vector<ROWS, T>& b) const requires (isSquare);

    enum class LinearSystemAlgorithm {
        inverse,
        lu_factorization,
        row_reduction
    };

    Vector<COLUMNS, T> solveLinearSystem(const Vector<ROWS, T>& b, LinearSystemAlgorithm algorithm) const;

private:
    Vector<COLUMNS, T> solveLinearSystemThroughInverse(const Vector<ROWS, T>& b) const requires (isSquare);
    Vector<COLUMNS, T> solveLinearSystemThroughLu(const Vector<ROWS, T>& b) const requires (isSquare);
    Vector<COLUMNS, T> solveLinearSystemThroughRowReduction(const Vector<ROWS, T>& b) const requires (isSquare);

public:
    Matrix<ROWS, COLUMNS, T> hadamardProduct(const Matrix<ROWS, COLUMNS, T>& other) const;

    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> hadamardProduct(const Matrix<ROWS, COLUMNS, OTHER_T>& other) const;

    template<int OTHER_COLUMNS, int OTHER_ROWS>
    Matrix<ROWS * OTHER_ROWS, COLUMNS * OTHER_COLUMNS, T> kroneckerProduct(const Matrix<OTHER_ROWS, OTHER_COLUMNS, T>& other) const;

    template<int OTHER_COLUMNS, int OTHER_ROWS, typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<ROWS * OTHER_ROWS, COLUMNS * OTHER_COLUMNS, std::common_type_t<T, OTHER_T>> kroneckerProduct(const Matrix<OTHER_ROWS, OTHER_COLUMNS, OTHER_T>& other) const;

    template<typename L_TYPE, typename U_TYPE>
    struct LUDecomposition {
        L_TYPE l;
        U_TYPE u;
    };

    /**
     * @brief Uses gaussian elimination to produce 2 unique matrices: l and u, that multiplied together give the original matrix.\n
     * The algorithm has a time complexity of O(n^3) and 2/3 n^3 FLOPS.
     *
     * The l matrix is a ROWS x ROWS, lower unitriangular matrix that contains the multipliers used in gaussian elimination. \n
     * The u matrix is a COLUMNS x ROWS, upper triangular matrix.
     *
     * This algorithm can be used to solve Ax = b, by factoring A into l and u, then using y =  l.@a forwardSubstitution(b) and then doing x = u.@a backwardSubstitution(y). See @a solveLinearSystem()
     *
     * @param skipZeroColumns Allows the algorithm to skip a column of only zeroes
     *
     * @returns A templated struct the contains the l and u matrices
     *
     * @throws ZeroPivotException If a zero pivot is found. If @a skipZeroColumns is true, will only throw if a zero pivot is found and the column is not a zero column
     * @warning If @a skipZeroColumns is set to true, the resulting u matrix may be singular and the decomposition may not be unique
     *
     * @note This algorithm is not numerically stable. See @a fullLupDecomposition() or @a fullLupqDecomposition()
     */
    LUDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> fullLuDecomposition(bool skipZeroColumns = false) const;

    template<typename L_TYPE, typename D_TYPE, typename U_TYPE>
    struct LDUDecomposition {
        L_TYPE l;
        D_TYPE d;
        U_TYPE u;
    };

    /**
     * @brief Uses gaussian elimination to produce 3 unique matrices, l, d, and u, that multiplied together give the original matrix. \n
     * Very similar to the @fullLuDecomposition(). \n
     * The algorithm has a time complexity of O(n^3) and 2/3 n^3 FLOPS.
     *
     * The l matrix is a ROWS x ROWS, lower unitriangular matrix that contains the multipliers used in gaussian elimination. \n
     * The d matrix is a ROWS x ROWS, diagonal matrix that stores the elements on the main diagonal of the u matrix. \n
     * The u matrix is a COLUMNS x ROWS, upper unitriangular matrix.
     *
     * The algorithm can be used to solve Ax = b by getting y = l.@a forwardSubstitution(b), dividing each element of y by the corresponding diagonal element of d, then solving x = u.@a backwardSubstitution(y).
     *
     * @returns A templated struct the contains the l, d, and u matrices
     *
     * @throws ZeroPivotException If a zero pivot is found.
     *
     * @note This algorithm is not numerically stable. See @a fullLupDecomposition() or @a fullLupqDecomposition()
     */
    LDUDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> fullLduDecomposition() const;

    template<typename L_TYPE, typename U_TYPE, typename P_TYPE>
    struct LUPDecomposition {
        L_TYPE l;
        U_TYPE u;
        P_TYPE p;
    };

    struct LUPDecompositionParams {
        bool skipZeroColumns = false;
        int* numRowSwaps = nullptr;
    };

    LUPDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, ROWS, T>> fullLupDecomposition(const LUPDecompositionParams& params = {}) const;

    template<typename L_TYPE, typename U_TYPE, typename P_TYPE, typename Q_TYPE>
    struct LUPQDecomposition {
        L_TYPE l;
        U_TYPE u;
        P_TYPE p;
        Q_TYPE q;
    };

    struct LUPQDecompositionParams {
        bool skipZeroSections = false;
        int* numRowSwaps = nullptr;
        int* numColumnSwaps = nullptr;
    };

    // not unique
    LUPQDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, COLUMNS, T>> fullLupqDecomposition(const LUPQDecompositionParams& params = {}) const;

    template<typename L_TYPE, typename L_TRANSPOSE_TYPE>
    struct CholeskyDecomposition {
        L_TYPE l;
        L_TRANSPOSE_TYPE lTranspose;
    };

    struct CholeskyDecompositionParams {
        bool allowPositiveSemiDefinite = false;
        bool skipChecks = false;
        UnderlyingType precision = 0.001;
    };

    // uses Cholesky–Banachiewicz and Cholesky–Crout algorithms
    CholeskyDecomposition<Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, COLUMNS, T>> choleskyDecomposition(CholeskyDecompositionParams params = {}) const requires (isSquare);

    template<typename L_TYPE, typename L_TRANSPOSE_TYPE, typename P_TYPE, typename P_TRANSPOSE_TYPE>
    struct PivotedCholeskyDecomposition {
        L_TYPE l;
        L_TRANSPOSE_TYPE lTranspose;
        P_TYPE p;
        P_TRANSPOSE_TYPE pTranspose;
    };

    struct PivotedCholeskyDecompositionParams {
        bool skipChecks = false;
        UnderlyingType precision = 0.001;
    };

    PivotedCholeskyDecomposition<Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, COLUMNS, T>> pivotedCholeskyDecomposition(PivotedCholeskyDecompositionParams params = {}) const requires (isSquare);

    template<typename L_TYPE, typename D_TYPE, typename L_TRANSPOSE_TYPE>
    struct LDLDecomposition {
        L_TYPE l;
        D_TYPE d;
        L_TRANSPOSE_TYPE lTranspose;
    };

    LDLDecomposition<Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> ldlDecomposition(bool allowSemidefinite = false, UnderlyingType precision = 0.001) const requires (isSquare);

    template<typename Q_TYPE, typename R_TYPE>
    struct QRDecomposition {
        Q_TYPE q;
        R_TYPE r;
    };

    QRDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> qrDecomposition() const requires (isSquare);

    T minorOfElement(int c, int r) const requires (isSquare);

    Matrix<ROWS, COLUMNS, T> minorMatrix() const requires (isSquare);

    T cofactorOfElement(int c, int r) const requires (isSquare);

    Matrix<ROWS, COLUMNS, T> cofactorMatrix() const requires (isSquare);

    Matrix<ROWS, COLUMNS, T> adjoint() const requires (isSquare);

    [[nodiscard]] bool isUpperHessenberg() const requires (isSquare);
    [[nodiscard]] bool isUnreducedUpperHessenberg() const requires (isSquare);

    [[nodiscard]] bool isLowerHessenberg() const requires (isSquare);
    [[nodiscard]] bool isUnreducedLowerHessenberg() const requires (isSquare);

    [[nodiscard]] bool isTridiagonal() const requires (isSquare);

    template<typename T_TYPE, typename Q_TYPE>
    struct LanczosAlgorithm {
        T_TYPE t;
        Q_TYPE q;
    };

    template<int ITER>
    LanczosAlgorithm<Matrix<ITER, ITER, T>, Matrix<COLUMNS, ITER + 1, T>> lanczosAlgorithm() const requires (isSquare);

    T rayleighQuotient(const Vector<COLUMNS, T>& vec) const;

    template<typename VECTOR_TYPE, typename VALUE_TYPE>
    struct EigenPair {
        VECTOR_TYPE eigenVector;
        VALUE_TYPE eigenValue;
    };

    template<typename VECTOR_TYPE, typename VALUE_TYPE, typename TOLERANCE_TYPE>
    struct InverseIterationParams {
        const VALUE_TYPE valueApproximation;

        const int maxIterations = 100;
        const VECTOR_TYPE vectorApproximation = VECTOR_TYPE::random();
        const TOLERANCE_TYPE tolerance = 1e-12;
    };

    // eigen-vector approximation from eigen-value approximation
    Vector<COLUMNS, T> inverseIteration(InverseIterationParams<Vector<COLUMNS, T>, T, UnderlyingType> params) const;

    template<typename VECTOR_TYPE, typename VALUE_TYPE, typename TOLERANCE_TYPE>
    struct RayleighQuotientIterationParams {
        const int maxIterations = 100;
        const VECTOR_TYPE vectorApproximation = VECTOR_TYPE::random();
        const std::optional<VALUE_TYPE> valueApproximation = std::nullopt;
        const TOLERANCE_TYPE tolerance = 1e-12;
    };

    EigenPair<Vector<COLUMNS, T>, T> rayleighQuotientIteration(RayleighQuotientIterationParams<Vector<COLUMNS, T>, T, UnderlyingType> params = RayleighQuotientIterationParams<Vector<COLUMNS, T>, T, T>()) const;

    template<typename VECTOR_TYPE, typename TOLERANCE_TYPE>
    struct PowerIterationParams {
        const int maxIterations = 100;
        const VECTOR_TYPE vectorApproximation = VECTOR_TYPE::random();
        const TOLERANCE_TYPE tolerance = 1e-12;
    };

    // greatest eigen-value and eigen-vector approximation
    EigenPair<Vector<COLUMNS, T>, T> powerIteration(PowerIterationParams<Vector<COLUMNS, T>, UnderlyingType> params = PowerIterationParams<Vector<COLUMNS, T>, UnderlyingType>()) const;
};

// Non member operators
template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> multiply(T scalar, const Matrix<ROWS, COLUMNS, T>& matrix);

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> operator*(T scalar, const Matrix<ROWS, COLUMNS, T>& matrix);

template<int ROWS, int COLUMNS, scalar T, typename OTHER_T> requires HasCommonType<OTHER_T, T>
Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> multiply(OTHER_T scalar, const Matrix<ROWS, COLUMNS, T>& matrix);

template<int ROWS, int COLUMNS, scalar T, typename OTHER_T> requires HasCommonType<OTHER_T, T>
Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> operator*(OTHER_T scalar, const Matrix<ROWS, COLUMNS, T>& matrix);