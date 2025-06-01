#include <penguin_framework/math/rect2.hpp>

namespace penguin::math {
	// Constructors

	Rect2::Rect2() = default;
	Rect2::Rect2(float x, float y, float width, float height) : position(Vector2(x, y)), size(Vector2(width, height)) {}
	Rect2::Rect2(const Vector2& position, const Vector2& size) : position(position), size(size) {}

	// Other functions

	float Rect2::area() const { return size.x * size.y; }
	float Rect2::perimeter() const { return 2.0f * (size.x + size.y); }
	Vector2 Rect2::center() const { return position + size / 2.0f; }

	bool Rect2::contains(const Vector2& point) const {
		return point.x >= position.x && point.x <= position.x + size.x &&
			point.y >= position.y && point.y <= position.y + size.y;
	}
	bool Rect2::intersects(const Rect2& r) const {
		return position.x < r.position.x + r.size.x && position.x + size.x > r.position.x &&
			position.y < r.position.y + r.size.y && position.y + size.y > r.position.y;
	}
}