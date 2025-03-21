#pragma once

#include <cmath>

struct [[nodiscard]] Vector2i {
	static constexpr int ORIGIN = 0.0; /// The origin for all Vector2i objects -> (0, 0)

	int x, y; /// The x and y components of the vector.

	// Default constructor (x, y = ORIGIN)
	constexpr Vector2i() : x{ ORIGIN }, y{ ORIGIN } {};

	// Parameterized constructor
	constexpr Vector2i(int p_x, int p_y) : x{ p_x }, y{ p_y } {}

	// Copy constructor
	constexpr Vector2i(const Vector2i& v) = default;

	// Move constructor
	constexpr Vector2i(Vector2i&& v) noexcept = default;

	// Copy assignment operator
	constexpr Vector2i& operator=(const Vector2i& v) = default;

	// Move assignment operator
	constexpr Vector2i& operator=(Vector2i&& v) noexcept = default;

	// Binary operators

	friend constexpr Vector2i operator+(const Vector2i& v) const { return Vector2i(x + v.x, y + v.y); }
	friend constexpr Vector2i operator-(const Vector2i& v) const { return Vector2i(x - v.x, y - v.y); }
	friend constexpr Vector2i operator*(const Vector2i& v) const { return Vector2i(x * v.x, y * v.y); }
	friend constexpr Vector2i operator/(const Vector2i& v) const { return Vector2i(x / v.x, y / v.y); }

	// Assignment operators

	constexpr Vector2i& operator+=(const Vector2i& v) const { x += v.x; y += v.y; return *this; }
	constexpr Vector2i& operator-=(const Vector2i& v) const { x -= v.x; y -= v.y; return *this; }
	constexpr Vector2i& operator*=(const Vector2i& v) const { x *= v.x; y *= v.y; return *this; }
	constexpr Vector2i& operator/=(const Vector2i& v) const { x /= v.x; y /= v.y; return *this; }

	// Comparison operators

	friend constexpr bool operator==(const Vector2i& v) const { return x == v.x && y == v.y; }
	friend constexpr bool operator!=(const Vector2i& v) const { return x != v.x || y != v.y; }

	// Unary operators

	constexpr Vector2i operator-() const { return Vector2i(-x, -y); }
	// Check if the vector is the origin.
	constexpr bool operator!() const { return x == ORIGIN && y == ORIGIN; }

	// Scalar operators

	friend constexpr Vector2i operator+(int scalar) const { return Vector2i(x + scalar, y + scalar); }
	friend constexpr Vector2i operator-(int scalar) const { return Vector2i(x - scalar, y - scalar); }
	friend constexpr Vector2i operator*(int scalar) const { return Vector2i(x * scalar, y * scalar); }
	friend constexpr Vector2i operator/(int scalar) const { return Vector2i(x / scalar, y / scalar); }

	// Scalar assignment operators

	constexpr Vector2i& operator+=(int scalar) const { x += scalar; y += scalar; return *this; }
	constexpr Vector2i& operator-=(int scalar) const { x -= scalar; y -= scalar; return *this; }
	constexpr Vector2i& operator*=(int scalar) const { x *= scalar; y *= scalar; return *this; }
	constexpr Vector2i& operator/=(int scalar) const { x /= scalar; y /= scalar; return *this; }

	// Scalar comparison operators

	friend constexpr bool operator==(int scalar) const { return x == scalar && y == scalar; }
	friend constexpr bool operator!=(int scalar) const { return x != scalar || y != scalar; }

	// Other comparsion operators

	= constexpr auto operator<=>(const Vector2i&) const noexcept = default; // C++20 three-way comparison generates ==, !=, <, >, <=, and >= automatically

	// Vector operations

	Vector2i abs() const;
	Vector2i floor() const;
	Vector2i ceil() const;
	Vector2i round() const;
	Vector2i min(const Vector2i& v) const;
	Vector2i max(const Vector2i& v) const;
	int dot(const Vector2i& v) const;
	int cross(const Vector2i& v) const;
	int length() const;
	int length_squared() const;
	int distance_to(const Vector2i& v) const;
	int distance_squared_to(const Vector2i& v) const;
};