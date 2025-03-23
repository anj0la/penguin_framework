#pragma once

#include "math/vector2.hpp"

struct [[nodiscard]] Rect2 {
	Vector2 position, size;

	// Default constructor

	Rect2() = default; // Sets the position and sixe of the rectangle at the origin (0.0, 0.0)

	// Regular constructors

	constexpr Rect2(float x, float y, float width, float height) : position(Vector2(x, y)), size(Vector2(width, height)) {}
	constexpr Rect2(const Vector2& position, const Vector2& size) : position(position), size(size) {}

	// Copy and move constructors
	constexpr Rect2(const Rect2& r) = default; // Copy constructor
	constexpr Rect2(Rect2&& r) noexcept = default; // Move constructor
	constexpr Rect2& operator=(const Rect2& r) = default; // Copy assignment operator
	constexpr Rect2& operator=(Rect2&& r) noexcept = default; // Move assignment operator

	// Equality operators

	constexpr bool operator==(const Rect2& r) const { return position == r.position && size == r.size; }
	constexpr bool operator!=(const Rect2& r) const { return position != r.position || size != r.size; }

	// Binary operators

	constexpr Rect2 operator+(const Rect2& r) const { return Rect2{ position + r.position, size + r.size }; }
	constexpr Rect2 operator-(const Rect2& r) const { return Rect2{ position - r.position, size - r.size }; }

	// Assignment operators

	constexpr Rect2& operator+=(const Rect2& r) { position += r.position; size += r.size; return *this; }
	constexpr Rect2& operator-=(const Rect2& r) { position -= r.position; size -= r.size; return *this; }
	constexpr Rect2& operator*=(const Rect2& r) { position *= r.position; size *= r.size; return *this; }
	constexpr Rect2& operator/=(const Rect2& r) { position /= r.position; size /= r.size; return *this; }

	 // Scalar operators

	constexpr Rect2 operator+(float scalar) const { return Rect2{ position + scalar, size + scalar }; }
	constexpr Rect2 operator-(float scalar) const { return Rect2{ position - scalar, size - scalar }; }
	constexpr Rect2 operator*(float scalar) const { return Rect2{ position * scalar, size * scalar }; }
	constexpr Rect2 operator/(float scalar) const { return Rect2{ position / scalar, size / scalar }; }

	// Scalar assignment operators

	constexpr Rect2& operator+=(float scalar) { position += scalar; size += scalar; return *this; }
	constexpr Rect2& operator-=(float scalar) { position -= scalar; size -= scalar; return *this; }
	constexpr Rect2& operator*=(float scalar) { position *= scalar; size *= scalar; return *this; }
	constexpr Rect2& operator/=(float scalar) { position /= scalar; size /= scalar; return *this; }

	// Other functions
	
	inline float area() const { return size.x * size.y; }
	inline float perimeter() const { return 2.0f * (size.x + size.y); }
	inline Vector2 center() const { return position + size / 2.0f; }

	inline bool contains(const Vector2& point) const {
		return point.x >= position.x && point.x <= position.x + size.x &&
			point.y >= position.y && point.y <= position.y + size.y;
	}

	inline bool intersects(const Rect2& r) const {
		return position.x < r.position.x + r.size.x && position.x + size.x > r.position.x &&
			position.y < r.position.y + r.size.y && position.y + size.y > r.position.y;
	}

};