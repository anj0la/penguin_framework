#include <penguin_framework/math/rect2i.hpp>

namespace penguin::math {
	// Constructors

	Rect2i::Rect2i() = default; // Sets the position and sixe of the rectangle at the origin (0.0, 0.0)
	Rect2i::Rect2i(int x, int y, int width, int height) : position(Vector2i(x, y)), size(Vector2i(width, height)) {}
	Rect2i::Rect2i(const Vector2i& position, const Vector2i& size) : position(position), size(size) {}

	// Other functions

	int Rect2i::area() const { return size.x * size.y; }
	int Rect2i::perimeter() const { return 2 * (size.x + size.y); }
	Vector2i Rect2i::center() const { return position + size / 2; }

	bool Rect2i::contains(const Vector2i& point) const {
		return point.x >= position.x && point.x <= position.x + size.x &&
			point.y >= position.y && point.y <= position.y + size.y;
	}

	bool Rect2i::intersects(const Rect2i& r) const {
		return position.x < r.position.x + r.size.x && position.x + size.x > r.position.x &&
			position.y < r.position.y + r.size.y && position.y + size.y > r.position.y;
	}
}