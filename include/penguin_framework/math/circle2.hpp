#pragma once

#include <penguin_framework/penguin_api.hpp>
#include <penguin_framework/core/math/vector2.hpp>
#include <numbers>

struct PENGUIN_API [[nodiscard]] Circle2 {
	Vector2 center;
	float radius;

	// Default constructor

	Circle2();

	// Regular constructors

	Circle2(const Vector2& p_center, float p_radius);
	Circle2(float p_x, float p_y, float p_radius);
	explicit Circle2(float p_radius);

	// Copy and move constructors

	Circle2(const Circle2& c) = default; // Copy constructor
	Circle2(Circle2&& c) noexcept = default; // Move constructor
	Circle2& operator=(const Circle2& c) = default; // Copy assignment operator
	Circle2& operator=(Circle2&& c) noexcept = default; // Move assignment operator

	// Equality operators

	constexpr bool operator==(const Circle2& c) const { return center == c.center && radius == c.radius; }
	constexpr bool operator!=(const Circle2& c) const { return center != c.center || radius != c.radius; }

	// Other functions

	float area() const;
	float circumference() const;
};

