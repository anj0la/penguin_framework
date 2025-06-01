#include <penguin_framework/core/math/circle2.hpp>

// Constructors

Circle2::Circle2() : center(Vector2()), radius(0.0f) {}
Circle2::Circle2(const Vector2& p_center, float p_radius) : center(p_center), radius(p_radius) {}
Circle2::Circle2(float p_x, float p_y, float p_radius) : center(Vector2(p_x, p_y)), radius(p_radius) {}
Circle2::Circle2(float p_radius) : center(Vector2()), radius(p_radius) {}

// Other functions

float Circle2::area() const { return std::numbers::pi * radius * radius; }
float Circle2::circumference() const { return 2.0f * std::numbers::pi * radius; }