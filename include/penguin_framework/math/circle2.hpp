#pragma once

#include "math/vector2.hpp"

constexpr float PI = 3.14159265358979323846f;

struct [[nodiscard]] Circle2 {
	Vector2 center;
	float radius;

	// Default constructor

	constexpr Circle2() : center(Vector2()), radius(0.0f) {}

	// Regular constructors

	constexpr Circle2(const Vector2& p_center, float p_radius) : center(p_center), radius(p_radius) {}
	constexpr Circle2(float p_x, float p_y, float p_radius) : center(Vector2(p_x, p_y)), radius(p_radius) {}
	constexpr explicit Circle2(float p_radius) : center(Vector2()), radius(p_radius) {}

	// Copy and move constructors

	constexpr Circle2(const Circle2& c) = default; // Copy constructor
	constexpr Circle2(Circle2&& c) noexcept = default; // Move constructor
	constexpr Circle2& operator=(const Circle2& c) = default; // Copy assignment operator
	constexpr Circle2& operator=(Circle2&& c) noexcept = default; // Move assignment operator

	// Equality operators

	constexpr bool operator==(const Circle2& c) const { return center == c.center && radius == c.radius; }
	constexpr bool operator!=(const Circle2& c) const { return center != c.center || radius != c.radius; }

	// Other functions

	inline float area() const { return PI * radius * radius; }
	inline float circumference() const { return 2.0f * PI * radius; }
};

