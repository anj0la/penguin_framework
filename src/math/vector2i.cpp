#include "include/penguin_framework/math/vector2i.hpp"

Vector2i::abs() const {
	return Vector2i(std::abs(x), std::abs(y));
}

Vector2i::floor() const {
	return Vector2i(static_cast<int>(std::floor(x)), static_cast<int>(std::floor(y)));
}

Vector2i::ceil() const {
	return Vector2i(static_cast<int>(std::ceil(x)), static_cast<int>(std::ceil(y));
}

Vector2i::round() const {
	return Vector2i(static_cast<int>(std::round(x)), static_cast<int>(std::round(y));
}

Vector2i::min(const Vector2i& v) const {
	return Vector2i(static_cast<int>(std::fmin(x, v.x)), static_cast<int>(std::fmin(y, v.y)));
}

Vector2i::max(const Vector2i& v) const {
	return Vector2i(static_cast<int>(std::fmax(x, v.x)), static_cast<int>(std::fmax(y, v.y)));
}

int Vector2i::dot(const Vector2i& v) const {
	return x * v.x + y * v.y;
}

int Vector2i::cross(const Vector2i& v) const {
	return x * v.y - y * v.x;
}

int Vector2i::length() const {
	return static_cast<int>(std::sqrt(x * x + y * y));
}

int Vector2i::length_squared() const {
	return x * x + y * y;
}

int Vector2i::distance_to(const Vector2i& v) const {
	return static_cast<int>(std::sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y)));
}

int Vector2i::distance_squared_to(const Vector2i& v) const {
	return (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y);
}