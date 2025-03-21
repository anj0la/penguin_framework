#include "include/penguin_framework/math/vector2.hpp"

Vector2::abs() const {
	return Vector2(std::fabsf(x), std::fabsf(y));
}

Vector2::floor() const {
	return Vector2(std::floorf(x), std::floorf(y));
}
Vector2::ceil() const {
	return Vector2(std::ceilf(x), std::ceilf(y));
}
Vector2::round() const {
	return Vector2(std::roundf(x), std::roundf(y));
}

Vector2::min(const Vector2& v) const {
	return Vector2(std::min(x, v.x), std::min(y, v.y));
}

Vector2::max(const Vector2& v) const {
	return Vector2(std::max(x, v.x), std::max(y, v.y));
}

Vector2::lerp(const Vector2& v, float weight) const {
	return Vector2(x + weight * (v.x - x), y + weight * (v.y - y));
}

float Vector2::dot(const Vector2& v) const {
	return x * v.x + y * v.y;
}

float Vector2::cross(const Vector2& v) const {
	return x * v.y - y * v.x;
}

float Vector2::length() const {
	return std::sqrtf(x * x + y * y);
}

float Vector2::length_squared() const {
	return x * x + y * y;
}

void Vector2::normalize() {
	float len = length_squared();
	if (len == 0) {
		return;
	}
	len = std::sqrtf(len);
	x /= len;
	y /= len;
}

Vector2 Vector2::normalized() const {
	float len = length_squared();
	if (len == 0) {
		return Vector2();
	}
	len = std::sqrtf(len);
	return Vector2(x / len, y / len);
}

float Vector2::distance_to(const Vector2& v) const {
	return std::sqrtf((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
}

float Vector2::distance_squared_to(const Vector2& v) const {
	return (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y);
}