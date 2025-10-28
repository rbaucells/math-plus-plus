#pragma once

struct Vector4 {
    float x = {};
    float y = {};
    float z = {};
    float w = {};

    Vector4 operator+(const Vector4 &other) const;

    Vector4 operator-(const Vector4 &other) const;

    Vector4 operator*(float scalar) const;

    Vector4 operator/(float scalar) const;

    Vector4 &operator+=(const Vector4 &other);

    Vector4 &operator-=(const Vector4 &other);

    Vector4 &operator*=(float scalar);

    Vector4 &operator/=(float scalar);

    [[nodiscard]] float magnitude() const;

    [[nodiscard]] Vector4 normalized() const;

    [[nodiscard]] float dot(const Vector4 &other) const;
};