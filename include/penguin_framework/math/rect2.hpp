#pragma once

#include <penguin_framework/penguin_api.hpp>
#include <penguin_framework/math/vector2.hpp>

namespace penguin::math {

	struct PENGUIN_API [[nodiscard]] Rect2 {

		Vector2 position, size;

		// Default constructor

		Rect2();

		// Regular constructors

		Rect2(float x, float y, float width, float height);
		Rect2(const Vector2& position, const Vector2& size);

		// Copy and move constructors

		Rect2(const Rect2& r) = default; // Copy constructor
		Rect2(Rect2&& r) noexcept = default; // Move constructor
		Rect2& operator=(const Rect2& r) = default; // Copy assignment operator
		Rect2& operator=(Rect2&& r) noexcept = default; // Move assignment operator

		// Equality operators

		constexpr bool operator==(const Rect2& r) const { return position == r.position && size == r.size; }
		constexpr bool operator!=(const Rect2& r) const { return position != r.position || size != r.size; }

		// Other functions

		float area() const;
		float perimeter() const;
		Vector2 center() const;
		bool contains(const Vector2& point) const;
		bool intersects(const Rect2& r) const;
	};

}

