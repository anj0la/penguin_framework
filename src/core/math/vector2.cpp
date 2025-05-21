#include <penguin_framework/core/math/vector2.hpp>

Vector2 Vector2::abs() const {
	return Vector2(std::fabs(x), std::fabs(y));
}

Vector2 Vector2::floor() const {
	return Vector2(std::floorf(x), std::floorf(y));
}
Vector2 Vector2::ceil() const {
	return Vector2(std::ceilf(x), std::ceilf(y));
}
Vector2 Vector2::round() const {
	return Vector2(std::roundf(x), std::roundf(y));
}

Vector2 Vector2::min(const Vector2& v) const {
	return Vector2(std::fmin(x, v.x), std::fmin(y, v.y));
}

Vector2 Vector2::max(const Vector2& v) const {
	return Vector2(std::fmax(x, v.x), std::fmax(y, v.y));
}

Vector2 Vector2::lerp(const Vector2& v, float weight) const {
	return Vector2(x + weight * (v.x - x), y + weight * (v.y - y));
}

float Vector2::dot(const Vector2& v) const {
	return x * v.x + y * v.y;
}

float Vector2::cross(const Vector2& v) const {
	return x * v.y - y * v.x;
}

float Vector2::length() const {
	return std::hypotf(x, y);
}

float Vector2::length_squared() const {
	return x * x + y * y;
}

void Vector2::normalize() {
	float len = length();
	if (penguin::math::is_zero_approx(len)) {
		return; // Avoids division by zero
	}
	x /= len;
	y /= len;
}

Vector2 Vector2::normalized() const {
	Vector2 v = *this;
	v.normalize();
	return v;
}

float Vector2::distance_to(const Vector2& v) const {
	return std::hypotf(x - v.x, y - v.y);
}

float Vector2::distance_squared_to(const Vector2& v) const {
	return (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y);
}

// Special Vectors

const Vector2 Vector2::Zero{ 0.0f, 0.0f };
const Vector2 Vector2::One{ 1.0f, 1.0f };
const Vector2 Vector2::UnitX{ 1.0f, 0.0f };
const Vector2 Vector2::UnitY{ 0.0f, 1.0f };