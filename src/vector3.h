#pragma once

struct Vector3 {
    float x = {};
    float y = {};
    float z = {};

    // operator overloads
    Vector3 operator+(const Vector3 &other) const;

    Vector3 operator-(const Vector3 &other) const;

    Vector3 operator*(float scalar) const;

    Vector3 operator/(float scalar) const;

    Vector3 &operator+=(const Vector3 &other);

    Vector3 &operator-=(const Vector3 &other);

    Vector3 &operator*=(float scalar);

    Vector3 &operator/=(float scalar);

    [[nodiscard]] float magnitude() const;

    [[nodiscard]] Vector3 normalized() const;

    [[nodiscard]] float dot(const Vector3 &other) const;

    [[nodiscard]] Vector3 cross(const Vector3 &other) const;
};