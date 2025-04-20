#pragma once

#include <penguin_framework/penguin_api.hpp>


#include <cmath>
#include <compare>

struct PENGUIN_API [[nodiscard]] Vector2i {
	static constexpr int ORIGIN = 0; /// The origin for all Vector2i objects -> (0, 0)

	int x, y; /// The x and y components of the vector.

	// Default constructor (x, y = ORIGIN)
	constexpr Vector2i() : x(ORIGIN), y(ORIGIN) {}

	// Regular constructors

	constexpr Vector2i(int p_x, int p_y) : x(p_x), y(p_y) {}
	constexpr explicit Vector2i(int scalar) : x(scalar), y(scalar) {}

	// Copy and move constructors

	constexpr Vector2i(const Vector2i& v) = default; // Copy constructor
	constexpr Vector2i(Vector2i&& v) noexcept = default; // Move constructor
	constexpr Vector2i& operator=(const Vector2i& v) = default; // Copy assignment operator
	constexpr Vector2i& operator=(Vector2i&& v) noexcept = default;	// Move assignment operator

	// Binary operators

	constexpr Vector2i operator+(const Vector2i& v) const { return Vector2i(x + v.x, y + v.y); }
	constexpr Vector2i operator-(const Vector2i& v) const { return Vector2i(x - v.x, y - v.y); }
	constexpr Vector2i operator*(const Vector2i& v) const { return Vector2i(x * v.x, y * v.y); }
	constexpr Vector2i operator/(const Vector2i& v) const { return Vector2i(x / v.x, y / v.y); }

	// Assignment operators

	constexpr Vector2i& operator+=(const Vector2i& v) { x += v.x; y += v.y; return *this; }
	constexpr Vector2i& operator-=(const Vector2i& v) { x -= v.x; y -= v.y; return *this; }
	constexpr Vector2i& operator*=(const Vector2i& v) { x *= v.x; y *= v.y; return *this; }
	constexpr Vector2i& operator/=(const Vector2i& v) { x /= v.x; y /= v.y; return *this; }

	// Comparison operators

	constexpr bool operator==(const Vector2i& v) const { return x == v.x && y == v.y; }
	constexpr bool operator!=(const Vector2i& v) const { return x != v.x || y != v.y; }

	// Unary operators

	constexpr Vector2i operator%(const Vector2i& v) const { return Vector2i(x % v.x, y % v.y); }
	constexpr Vector2i operator%(int scalar) const { return Vector2i(x % scalar, y % scalar); }
	constexpr Vector2i operator-() const { return Vector2i(-x, -y); }
	constexpr bool operator!() const { return x != ORIGIN && y != ORIGIN; }

	// Scalar operators

	constexpr Vector2i operator+(int scalar) const { return Vector2i(x + scalar, y + scalar); }
	constexpr Vector2i operator-(int scalar) const { return Vector2i(x - scalar, y - scalar); }
	constexpr Vector2i operator*(int scalar) const { return Vector2i(x * scalar, y * scalar); }
	constexpr Vector2i operator/(int scalar) const { return Vector2i(x / scalar, y / scalar); }

	// Scalar assignment operators

	constexpr Vector2i& operator+=(int scalar) { x += scalar; y += scalar; return *this; }
	constexpr Vector2i& operator-=(int scalar) { x -= scalar; y -= scalar; return *this; }
	constexpr Vector2i& operator*=(int scalar) { x *= scalar; y *= scalar; return *this; }
	constexpr Vector2i& operator/=(int scalar) { x /= scalar; y /= scalar; return *this; } // need to handle division by 0
	constexpr Vector2i& operator%=(int scalar) { x %= scalar; y %= scalar; return *this; }

	// Scalar comparison operators

	constexpr bool operator==(int scalar) const { return x == scalar && y == scalar; }
	constexpr bool operator!=(int scalar) const { return x != scalar || y != scalar; }

	// Other comparsion operators

	constexpr auto operator<=>(const Vector2i&) const noexcept = default; // C++20 three-way comparison generates ==, !=, <, >, <=, and >= automatically

	// Vector operations

	Vector2i abs() const;
	Vector2i min(const Vector2i& v) const;
	Vector2i max(const Vector2i& v) const;
	int dot(const Vector2i& v) const;
	int cross(const Vector2i& v) const;
	float length() const;
	int length_squared() const;
	float distance_to(const Vector2i& v) const;
	int distance_squared_to(const Vector2i& v) const;
};