#pragma once

#include <cmath>

struct [[nodiscard]] Vector2 {
	static constexpr float ORIGIN = 0.0; /// The origin for all Vector2 objects -> (0, 0)

	float x, y; /// The x and y components of the vector.

	// Default constructor (x, y = ORIGIN)
	constexpr Vector2() : x{ ORIGIN }, y{ ORIGIN } {};

	// Parameterized constructor
	constexpr Vector2(float p_x, float p_y) : x{ p_x }, y{ p_y } {}

	// Copy constructor
	constexpr Vector2(const Vector2& v) = default;

	// Move constructor
	constexpr Vector2(Vector2&& v) noexcept = default;

	// Copy assignment operator
	constexpr Vector2& operator=(const Vector2& v) = default;

	// Move assignment operator
	constexpr Vector2& operator=(Vector2&& v) noexcept = default;

    // Binary operators

	friend constexpr Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
	friend constexpr Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
	friend constexpr Vector2 operator*(const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
	friend constexpr Vector2 operator/(const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

	// Assignment operators
 
	constexpr Vector2& operator+=(const Vector2& v) const { x += v.x; y += v.y; return *this; }
	constexpr Vector2& operator-=(const Vector2& v) const { x -= v.x; y -= v.y; return *this; }
	constexpr Vector2& operator*=(const Vector2& v) const { x *= v.x; y *= v.y; return *this; }
	constexpr Vector2& operator/=(const Vector2& v) const { x /= v.x; y /= v.y; return *this; }

	// Comparison operators

	friend constexpr bool operator==(const Vector2& v) const { return x == v.x && y == v.y; }
	friend constexpr bool operator!=(const Vector2& v) const { return x != v.x || y != v.y; }

	// Unary operators

	constexpr Vector2 operator-() const { return Vector2(-x, -y); }
	// Check if the vector is the origin.
	constexpr bool operator!() const { return x == ORIGIN && y == ORIGIN; }

	// Scalar operators

	friend constexpr Vector2 operator+(float scalar) const { return Vector2(x + scalar, y + scalar); }
	friend constexpr Vector2 operator-(float scalar) const { return Vector2(x - scalar, y - scalar); }
	friend constexpr Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }
	friend constexpr Vector2 operator/(float scalar) const { return Vector2(x / scalar, y / scalar); }

	// Scalar assignment operators

	constexpr Vector2& operator+=(float scalar) const { x += scalar; y += scalar; return *this; }
	constexpr Vector2& operator-=(float scalar) const { x -= scalar; y -= scalar; return *this; }
	constexpr Vector2& operator*=(float scalar) const { x *= scalar; y *= scalar; return *this; }
	constexpr Vector2& operator/=(float scalar) const { x /= scalar; y /= scalar; return *this; }

	// Scalar comparison operators

	friend constexpr bool operator==(float scalar) const { return x == scalar && y == scalar; }
	friend constexpr bool operator!=(float scalar) const { return x != scalar || y != scalar; }

	// Other comparsion operators
	
=	constexpr auto operator<=>(const Vector2 &) const noexcept = default; // C++20 three-way comparison generates ==, !=, <, >, <=, and >= automatically

	// Vector operations

	Vector2 abs() const;
	Vector2 floor() const;
	Vector2 ceil() const;
	Vector2 round() const;
	Vector2 min(const Vector2& v) const;
	Vector2 max(const Vector2& v) const;
	Vector2 lerp(const Vector2& v, float weight) const;
	float dot(const Vector2& v) const;
	float cross(const Vector2& v) const;
	float length() const;
	float length_squared() const;
	void normalize();
	Vector2 normalized() const;
	float distance_to(const Vector2& v) const;
	float distance_squared_to(const Vector2& v) const;
};