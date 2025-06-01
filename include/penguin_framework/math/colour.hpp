#pragma once

#include <penguin_framework/penguin_api.hpp>
#include <penguin_framework/math/math_funcs.hpp>
#include <algorithm>
#include <cstdint>

namespace penguin::math {

    struct PENGUIN_API [[nodiscard]] Colour {

        float r, g, b, a;

        // Default constructor

        constexpr Colour() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

        // Regular constructors

        constexpr Colour(float p_r, float p_g, float p_b, float p_a) :
            r(std::clamp(compat::p_isnan(p_r) ? 0.0f : p_r, 0.0f, 1.0f)),
            g(std::clamp(compat::p_isnan(p_g) ? 0.0f : p_g, 0.0f, 1.0f)),
            b(std::clamp(compat::p_isnan(p_b) ? 0.0f : p_b, 0.0f, 1.0f)),
            a(std::clamp(compat::p_isnan(p_a) ? 0.0f : p_a, 0.0f, 1.0f)) {
        }

        constexpr Colour(float p_r, float p_g, float p_b) :
            Colour(p_r, p_g, p_b, 1.0f) {
        } // propagate to regular constructor to handle NaN values

// Copy and move constructors

        constexpr Colour(const Colour& c) = default; // Copy constructor
        constexpr Colour(Colour&& c) noexcept = default; // Move constructor
        constexpr Colour& operator=(const Colour& c) = default; // Copy assignment operator
        constexpr Colour& operator=(Colour&& c) noexcept = default; // Move assignment operator

        // Comparision operators

        constexpr bool operator==(const Colour& c) const {
            return is_almost_equal(r, c.r) &&
                is_almost_equal(g, c.g) &&
                is_almost_equal(b, c.b) &&
                is_almost_equal(a, c.a);
        }

        constexpr bool operator!=(const Colour& c) const {
            return !(*this == c);
        }

        // Binary operators

        constexpr Colour operator+(const Colour& c) const { return Colour(r + c.r, g + c.g, b + c.b, a + c.a); }
        constexpr Colour operator-(const Colour& c) const { return Colour(r - c.r, g - c.g, b - c.b, a - c.a); }
        constexpr Colour operator*(const Colour& c) const { return Colour(r * c.r, g * c.g, b * c.b, a * c.a); }
        constexpr Colour operator/(const Colour& c) const { return Colour(r / c.r, g / c.g, b / c.b, a / c.a); }

        // Assignment operators

        constexpr Colour& operator+=(const Colour& c) {
            r = std::clamp(r + c.r, 0.0f, 1.0f);
            g = std::clamp(g + c.g, 0.0f, 1.0f);
            b = std::clamp(b + c.b, 0.0f, 1.0f);
            a = std::clamp(a + c.a, 0.0f, 1.0f);

            return *this;
        }

        constexpr Colour& operator-=(const Colour& c) {
            r = std::clamp(r - c.r, 0.0f, 1.0f);
            g = std::clamp(g - c.g, 0.0f, 1.0f);
            b = std::clamp(b - c.b, 0.0f, 1.0f);
            a = std::clamp(a - c.a, 0.0f, 1.0f);

            return *this;
        }

        constexpr Colour& operator*=(const Colour& c) {
            r = std::clamp(r * c.r, 0.0f, 1.0f);
            g = std::clamp(g * c.g, 0.0f, 1.0f);
            b = std::clamp(b * c.b, 0.0f, 1.0f);
            a = std::clamp(a * c.a, 0.0f, 1.0f);

            return *this;
        }

        constexpr Colour& operator/=(const Colour& c) {
            float res_r = r / c.r;
            float res_g = g / c.g;
            float res_b = b / c.b;
            float res_a = a / c.a;

            r = std::clamp(std::isnan(res_r) ? 0.0f : res_r, 0.0f, 1.0f);
            g = std::clamp(std::isnan(res_g) ? 0.0f : res_g, 0.0f, 1.0f);
            b = std::clamp(std::isnan(res_b) ? 0.0f : res_b, 0.0f, 1.0f);
            a = std::clamp(std::isnan(res_a) ? 0.0f : res_a, 0.0f, 1.0f);

            return *this;
        }

        // Unary operators

        constexpr Colour operator~() const { return Colour(1.0f - r, 1.0f - g, 1.0f - b, a); } // Inverts colour

        // Scalar operators

        constexpr Colour operator+(float scalar) const { return Colour(r + scalar, g + scalar, b + scalar, a + scalar); }
        constexpr Colour operator-(float scalar) const { return Colour(r - scalar, g - scalar, b - scalar, a - scalar); }
        constexpr Colour operator*(float scalar) const { return Colour(r * scalar, g * scalar, b * scalar, a * scalar); }
        constexpr Colour operator/(float scalar) const { return Colour(r / scalar, g / scalar, b / scalar, a / scalar); }

        // Scalar assignment operators

        constexpr Colour& operator+=(float scalar) {
            r = std::clamp(r + scalar, 0.0f, 1.0f);
            g = std::clamp(g + scalar, 0.0f, 1.0f);
            b = std::clamp(b + scalar, 0.0f, 1.0f);
            a = std::clamp(a + scalar, 0.0f, 1.0f);

            return *this;
        }

        constexpr Colour& operator-=(float scalar) {
            r = std::clamp(r - scalar, 0.0f, 1.0f);
            g = std::clamp(g - scalar, 0.0f, 1.0f);
            b = std::clamp(b - scalar, 0.0f, 1.0f);
            a = std::clamp(a - scalar, 0.0f, 1.0f);

            return *this;
        }
        constexpr Colour& operator*=(float scalar) {
            r = std::clamp(r * scalar, 0.0f, 1.0f);
            g = std::clamp(g * scalar, 0.0f, 1.0f);
            b = std::clamp(b * scalar, 0.0f, 1.0f);
            a = std::clamp(a * scalar, 0.0f, 1.0f);

            return *this;
        }

        constexpr Colour& operator/=(float scalar) {
            float res_r = r / scalar;
            float res_g = g / scalar;
            float res_b = b / scalar;
            float res_a = a / scalar;

            r = std::clamp(std::isnan(res_r) ? 0.0f : res_r, 0.0f, 1.0f);
            g = std::clamp(std::isnan(res_g) ? 0.0f : res_g, 0.0f, 1.0f);
            b = std::clamp(std::isnan(res_b) ? 0.0f : res_b, 0.0f, 1.0f);
            a = std::clamp(std::isnan(res_a) ? 0.0f : res_a, 0.0f, 1.0f);

            return *this;
        }

        // Static functions 

        static Colour from_rgb(uint8_t red, uint8_t green, uint8_t blue);
        static Colour from_rgba(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
        static Colour from_argb(uint32_t p_argb);
    };


}

