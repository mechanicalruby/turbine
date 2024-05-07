#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>

struct Vector2 {
	float x, y;
	
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2() : x(0.0f), y(0.0f) {}

    // Print coordinates in cout
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
        os << vec.x << ", " << vec.y;
        return os;
    }

    Vector2 operator-() const {
        return {-x, -y};
    }

    Vector2 operator+(const Vector2& other) const {
	return {x + other.x, y + other.y};
    }

    Vector2 operator-(const Vector2& other) const {
        return {x - other.x, y - other.y};
    }

    Vector2 operator*(float scalar) const {
        return {x * scalar, y * scalar};
    }

    Vector2 operator/(float scalar) const {
        // Make sure it isn't zero; we don't want to divide by zero
        if (scalar != 0.0f) {
            return {x / scalar, y / scalar};
        } else {
            // If it IS zero, return zero
            return {0.0f, 0.0f};
        }
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(float scalar) {
        if (scalar != 0.0f) {
            x /= scalar;
            y /= scalar;
        } else {
            x = 0.0f;
            y = 0.0f;
        }
        return *this;
    }
};

#endif
