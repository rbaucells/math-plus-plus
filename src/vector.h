#pragma once
#include <array>
#include <random>
#include "helper.h"

template< int ROWS, int COLUMNS, scalar T>
struct Matrix;

template<int N, scalar T = float>
struct Vector {
    static constexpr int n = N;
    static constexpr bool isComplex = is_complex_v<T>;

    using ValueType = T;
    using UnderlyingType = underlying_type<T>::value_type;

    T data[N] = {};

    Vector() = default;

    constexpr Vector(std::initializer_list<T> list);

    Vector(const Vector<N, T>& other);

    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Vector(const Vector<N, OTHER_T>& other);

    static Vector<N, T> random();

    // v = v
    Vector<N, T>& operator=(const Vector<N, T>& other);

    // v == v
    bool equals(const Vector<N, T>& other, underlying_type_t<T> precision = ::epsilon<T>()) const;
    bool operator==(const Vector<N, T>& other) const;

    // v + v
    Vector<N, T> add(const Vector<N, T>& other) const;
    Vector<N, T> operator+(const Vector<N, T>& other) const;

    // v - v
    Vector<N, T> subtract(const Vector<N, T>& other) const;
    Vector<N, T> operator-(const Vector<N, T>& other) const;

    // v * #
    Vector<N, T> multiply(T scalar) const;
    Vector<N, T> operator*(T scalar) const;

    // v / #
    Vector<N, T> divide(T scalar) const;
    Vector<N, T> operator/(T scalar) const;

    // v += v
    Vector<N, T>& addEquals(const Vector<N, T>& other);
    Vector<N, T>& operator+=(const Vector<N, T>& other);

    // v -= v
    Vector<N, T>& subtractEquals(const Vector<N, T>& other);
    Vector<N, T>& operator-=(const Vector<N, T>& other);

    // v *= #
    Vector<N, T>& multiplyEquals(T scalar);
    Vector<N, T>& operator*=(T scalar);

    // v /= #
    Vector<N, T>& divideEquals(T scalar);
    Vector<N, T>& operator/=(T scalar);

    // v * m
    template<int COLUMNS>
    Vector<COLUMNS, T> multiply(const Matrix<COLUMNS, N, T>& m) const;
    template<int COLUMNS>
    Vector<COLUMNS, T> operator*(const Matrix<COLUMNS, N, T>& m) const;

    // v = v
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Vector<N, T>& operator=(const Vector<N, OTHER_T>& other);

    // v == v
    template<typename OTHER_T> requires std::equality_comparable_with<OTHER_T, T>
    bool equals(const Vector<N, OTHER_T>& other, std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHER_T>> precision = epsilon<std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHER_T>>>()) const;
    template<typename OTHER_T> requires std::equality_comparable_with<OTHER_T, T>
    bool operator==(const Vector<N, OTHER_T>& other) const;

    // v + v
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<N, std::common_type_t<T, OTHER_T>> add(const Vector<N, OTHER_T>& other) const;
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<N, std::common_type_t<T, OTHER_T>> operator+(const Vector<N, OTHER_T>& other) const;

    // v - v
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<N, std::common_type_t<T, OTHER_T>> subtract(const Vector<N, OTHER_T>& other) const;
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<N, std::common_type_t<T, OTHER_T>> operator-(const Vector<N, OTHER_T>& other) const;

    // v * #
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<N, std::common_type_t<T, OTHER_T>> multiply(OTHER_T scalar) const;
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<N, std::common_type_t<T, OTHER_T>> operator*(OTHER_T scalar) const;

    // v / #
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<N, std::common_type_t<T, OTHER_T>> divide(OTHER_T scalar) const;
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<N, std::common_type_t<T, OTHER_T>> operator/(OTHER_T scalar) const;

    // v += v
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Vector<N, T>& addEquals(const Vector<N, OTHER_T>& other);
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Vector<N, T>& operator+=(const Vector<N, OTHER_T>& other);

    // v -= v
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Vector<N, T>& subtractEquals(const Vector<N, OTHER_T>& other);
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Vector<N, T>& operator-=(const Vector<N, OTHER_T>& other);

    // v *= #
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Vector<N, T>& multiplyEquals(OTHER_T scalar);
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Vector<N, T>& operator*=(OTHER_T scalar);

    // v /= #
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Vector<N, T>& divideEquals(OTHER_T scalar);
    template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
    Vector<N, T>& operator/=(OTHER_T scalar);

    template<int COLUMNS, typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<COLUMNS, std::common_type_t<T, OTHER_T>> multiply(const Matrix<COLUMNS, N, OTHER_T>& m) const;
    template<int COLUMNS, typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Vector<COLUMNS, std::common_type_t<T, OTHER_T>> operator*(const Matrix<COLUMNS, N, OTHER_T>& m) const;

    Vector<N, T> operator-() const;

    explicit operator T*();
    explicit operator const T*() const;

    T& operator[](int index);
    const T& operator[](int index) const;

    template<int V_SIZE>
    static std::array<Vector<N, T>, V_SIZE> orthonormalize(const std::array<Vector<N, T>, V_SIZE>& v);

    template<int V_SIZE>
    static std::array<Vector<N, T>, V_SIZE> orthogonalize(const std::array<Vector<N, T>, V_SIZE>& v);

    template<int V_SIZE>
    static bool isOrthogonal(const std::array<Vector<N, T>, V_SIZE>& vectors);
    template<int V_SIZE>
    static bool isOrthonormal(const std::array<Vector<N, T>, V_SIZE>& vectors);

    Vector<N, T> conjugate() const;

    UnderlyingType taxicabNorm() const;
    UnderlyingType euclidianNorm() const;
    UnderlyingType euclidianNormSquared() const;
    UnderlyingType maxNorm() const;

    [[nodiscard]] std::string toString() const;

    enum DotProductConjugationBehavior {
        first_argument,
        second_argument,
        neither
    };

    [[nodiscard]] T dot(const Vector<N, T>& other, DotProductConjugationBehavior behavior = first_argument) const;
    T operator*(const Vector<N, T>& other) const;

    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    [[nodiscard]] std::common_type_t<T, OTHER_T> dot(const Vector<N, OTHER_T>& other, DotProductConjugationBehavior behavior = first_argument) const;
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    std::common_type_t<T, OTHER_T> operator*(const Vector<N, OTHER_T>& other) const;

    template<int OTHER_N>
    Matrix<OTHER_N, N, T> outerProductMatrix(const Vector<OTHER_N, T>& other) const;
    template<int OTHER_N, typename OTHER_T> requires HasCommonType<OTHER_T, T>
    Matrix<OTHER_N, N, std::common_type_t<T, OTHER_T>> outerProductMatrix(const Vector<OTHER_N, OTHER_T>& other) const;

    Vector<N, T> cross(const Vector<N, T>& other) const requires (N == 3);
    Matrix<N, N, T> crossProductMatrix() const requires (N == 3);

    Vector<N, std::common_type_t<T, UnderlyingType>> normalized() const;

    UnderlyingType angle(const Vector<N, T>& other, RotationType type = RotationType::radians) const;
    template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
    std::common_type_t<UnderlyingType, typename Vector<N, OTHER_T>::UnderlyingType> angle(const Vector<N, OTHER_T>& other, RotationType type = RotationType::radians) const;

    std::common_type_t<T, UnderlyingType> scalarProjection(const Vector<N, T>& other) const;
    template<typename OTHER_T> requires HasCommonType<T, OTHER_T, typename Vector<N, OTHER_T>::UnderlyingType>
    std::common_type_t<T, OTHER_T, typename Vector<N, OTHER_T>::UnderlyingType> scalarProjection(const Vector<N, OTHER_T>& other) const;
};

template<int N, scalar T>
Vector<N, T> operator*(T scalar, const Vector<N, T>& vector);

template<int N, scalar T, typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<N, std::common_type_t<T, OTHER_T>> operator*(OTHER_T scalar, const Vector<N, T>& vector);
