#include <penguin_framework/math/vector2i.hpp>

namespace penguin::math {
	Vector2i Vector2i::abs() const {
		return Vector2i(std::abs(x), std::abs(y));
	}
	Vector2i Vector2i::min(const Vector2i& v) const {
		return Vector2i(static_cast<int>(std::fmin(x, v.x)), static_cast<int>(std::fmin(y, v.y)));
	}

	Vector2i Vector2i::max(const Vector2i& v) const {
		return Vector2i(static_cast<int>(std::fmax(x, v.x)), static_cast<int>(std::fmax(y, v.y)));
	}

	int Vector2i::dot(const Vector2i& v) const {
		return x * v.x + y * v.y;
	}

	int Vector2i::cross(const Vector2i& v) const {
		return x * v.y - y * v.x;
	}

	float Vector2i::length() const {
		return std::sqrtf(x * x + y * y);
	}

	int Vector2i::length_squared() const {
		return x * x + y * y;
	}

	float Vector2i::distance_to(const Vector2i& v) const {
		return std::sqrtf((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
	}

	int Vector2i::distance_squared_to(const Vector2i& v) const {
		return (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y);
	}

	// Special Vectors

	const Vector2i Vector2i::Zero{ 0, 0 };
	const Vector2i Vector2i::One{ 1, 1 };
	const Vector2i Vector2i::UnitX{ 1, 0 };
	const Vector2i Vector2i::UnitY{ 0, 1 };
}
