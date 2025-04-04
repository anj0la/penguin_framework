#pragma once

#include "core/math/vector2i.hpp"

struct [[nodiscard]] Rect2i {
	Vector2i position, size;

	// Default constructor

	Rect2i() = default; // Sets the position and sixe of the rectangle at the origin (0.0, 0.0)

	// Regular constructors

	constexpr Rect2i(int x, int y, int width, int height) : position(Vector2i(x, y)), size(Vector2i(width, height)) {}
	constexpr Rect2i(const Vector2i& position, const Vector2i& size) : position(position), size(size) {}

	// Copy and move constructors

	constexpr Rect2i(const Rect2i& r) = default; // Copy constructor
	constexpr Rect2i(Rect2i&& r) noexcept = default; // Move constructor
	constexpr Rect2i& operator=(const Rect2i& r) = default; // Copy assignment operator
	constexpr Rect2i& operator=(Rect2i&& r) noexcept = default; // Move assignment operator

	// Equality operators

	constexpr bool operator==(const Rect2i& r) const { return position == r.position && size == r.size; }
	constexpr bool operator!=(const Rect2i& r) const { return position != r.position || size != r.size; }


	// Other functions

	inline int area() const { return size.x * size.y; }
	inline int perimeter() const { return 2 * (size.x + size.y); }
	inline Vector2i center() const { return position + size / 2; }

	inline bool contains(const Vector2i& point) const {
		return point.x >= position.x && point.x <= position.x + size.x &&
			point.y >= position.y && point.y <= position.y + size.y;
	}

	inline bool intersects(const Rect2i& r) const {
		return position.x < r.position.x + r.size.x && position.x + size.x > r.position.x &&
			position.y < r.position.y + r.size.y && position.y + size.y > r.position.y;
	}

};