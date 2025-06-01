#pragma once

#include <penguin_framework/penguin_api.hpp>
#include <penguin_framework/math/vector2i.hpp>

namespace penguin::math {

	struct PENGUIN_API [[nodiscard]] Rect2i {
		Vector2i position, size;

		// Default constructor

		Rect2i(); // Sets the position and sixe of the rectangle at the origin (0.0, 0.0)

		// Regular constructors

		Rect2i(int x, int y, int width, int height);
		Rect2i(const Vector2i& position, const Vector2i& size);

		// Copy and move constructors

		Rect2i(const Rect2i& r) = default; // Copy constructor
		Rect2i(Rect2i&& r) noexcept = default; // Move constructor
		Rect2i& operator=(const Rect2i& r) = default; // Copy assignment operator
		Rect2i& operator=(Rect2i&& r) noexcept = default; // Move assignment operator

		// Equality operators

		constexpr bool operator==(const Rect2i& r) const { return position == r.position && size == r.size; }
		constexpr bool operator!=(const Rect2i& r) const { return position != r.position || size != r.size; }

		// Other functions

		int area() const;
		int perimeter() const;
		Vector2i center() const;
		bool contains(const Vector2i& point) const;
		bool intersects(const Rect2i& r) const;
	};
}