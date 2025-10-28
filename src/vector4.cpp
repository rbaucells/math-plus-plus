#include <cmath>
#include "vector4.h"

Vector4 Vector4::operator+(const Vector4 &other) const {
    return Vector4{x + other.x, y + other.y, z + other.z, w + other.w};
}

Vector4 Vector4::operator-(const Vector4 &other) const {
    return Vector4{x - other.x, y - other.y, z - other.z, w - other.w};
}

Vector4 Vector4::operator*(const float scalar) const {
    return Vector4{x * scalar, y * scalar, z * scalar, w * scalar};
}

Vector4 Vector4::operator/(const float scalar) const {
    if (scalar == 0) {
        // Handle division by zero to prevent crashes
        return Vector4{0, 0, 0, 0};
    }
    return Vector4{x / scalar, y / scalar, z / scalar, w / scalar};
}

Vector4 &Vector4::operator+=(const Vector4 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Vector4 &Vector4::operator-=(const Vector4 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Vector4 &Vector4::operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Vector4 &Vector4::operator/=(const float scalar) {
    if (scalar != 0) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
    }
    return *this;
}

float Vector4::magnitude() const {
    return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

Vector4 Vector4::normalized() const {
    float mag = magnitude();
    if (mag != 0) {
        return Vector4{x / mag, y / mag, z / mag, w / mag};
    }
    return Vector4{0, 0, 0, 0};
}

float Vector4::dot(const Vector4 &other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}
