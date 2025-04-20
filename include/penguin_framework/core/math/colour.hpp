#pragma once

#include <penguin_framework/penguin_api.hpp>
#include <algorithm>

struct PENGUIN_API [[nodiscard]] Colour {

    static constexpr unsigned int OPAQUE = 255;
    static constexpr unsigned int TRANSPARENT = 0; 

    unsigned int r, g, b, a; 

    // Default constructors

    constexpr Colour() : r(0), g(0), b(0), a(OPAQUE) {}

    // Regular constructors

    constexpr Colour(unsigned int p_r, unsigned int p_g, unsigned int p_b, unsigned int p_a) : 
        r(std::clamp(p_r, 0u, 255u)), 
        g(std::clamp(p_g, 0u, 255u)), 
        b(std::clamp(p_b, 0u, 255u)),
        a(std::clamp(p_a, 0u, 255u)) {}

    // Copy and move constructors

    constexpr Colour(const Colour& c) = default; // Copy constructor
    constexpr Colour(Colour&& c) noexcept = default; // Move constructor
    constexpr Colour& operator=(const Colour& c) = default; // Copy assignment operator
    constexpr Colour& operator=(Colour&& c) noexcept = default; // Move assignment operator
};


