#pragma once

#include <penguin_api.hpp>
#include <penguin_framework/math/math_funcs.hpp>

#include <cmath>
#include <compare>

namespace penguin::math {
	struct PENGUIN_API [[nodiscard]] Vector2 {
		static constexpr float Origin = 0.0f; /// The origin for all Vector2 objects -> (0.0, 0.0)

		float x, y; /// The x and y components of the vector.

		// Default constructor (x, y = ORIGIN)

		constexpr Vector2() : x(Origin), y(Origin) {}

		// Regular constructors

		constexpr Vector2(float p_x, float p_y) : x(p_x), y(p_y) {}
		constexpr explicit Vector2(float scalar) : x(scalar), y(scalar) {}

		// Copy and move constructors

		constexpr Vector2(const Vector2& v) = default; // Copy constructor
		constexpr Vector2(Vector2&& v) noexcept = default; // Move constructor
		constexpr Vector2& operator=(const Vector2& v) = default; // Copy assignment operator
		constexpr Vector2& operator=(Vector2&& v) noexcept = default; // Move assignment operator

		// Binary operators

		constexpr Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		constexpr Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
		constexpr Vector2 operator*(const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
		constexpr Vector2 operator/(const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

		// Assignment operators

		constexpr Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
		constexpr Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		constexpr Vector2& operator*=(const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		constexpr Vector2& operator/=(const Vector2& v) { x /= v.x; y /= v.y; return *this; }

		// Comparison operators

		constexpr bool operator==(const Vector2& v) const { return penguin::math::is_almost_equal(x, v.x) && penguin::math::is_almost_equal(y, v.y); }
		constexpr bool operator!=(const Vector2& v) const { return !(*this == v); }

		// Unary operators

		constexpr Vector2 operator-() const { return Vector2(-x, -y); }

		// Scalar operators

		constexpr Vector2 operator+(float scalar) const { return Vector2(x + scalar, y + scalar); }
		constexpr Vector2 operator-(float scalar) const { return Vector2(x - scalar, y - scalar); }
		constexpr Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }
		constexpr Vector2 operator/(float scalar) const { return Vector2(x / scalar, y / scalar); }

		// Scalar assignment operators

		constexpr Vector2& operator+=(float scalar) { x += scalar; y += scalar; return *this; }
		constexpr Vector2& operator-=(float scalar) { x -= scalar; y -= scalar; return *this; }
		constexpr Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
		constexpr Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

		// Other comparsion operators

		constexpr auto operator<=>(const Vector2&) const noexcept = default; // C++20 three-way comparison generates ==, !=, <, >, <=, and >= automatically

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

		// Special vectors

		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
	};
}

