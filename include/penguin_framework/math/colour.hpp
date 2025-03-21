#pragma once

struct [[nodiscard]] Colour {

    static constexpr unsigned int OPAQUE = 255;
    static constexpr unsigned int TRANSPARENT = 0; 

    unsigned int r, g, b, a; 

    // Default constructors

    constexpr Colour() : r(0), g(0), b(0), ai(OPAQUE) {}

    // Regular constructors

    constexpr Colour(unsigned int p_r, unsigned int p_g, unsigned int p_b, unsigned int p_a) : r(p_r), g(p_g), b(p_b), a(p_a) {}

    // Copy and move constructors

    constexpr Colour(const Colour& c) = default; // Copy constructor
    constexpr Colour(Colour&& c) noexcept = default; // Move constructor
    constexpr Colour& operator=(const Colour& c) = default; // Copy assignment operator
    constexpr Colour& operator=(Colour&& c) noexcept = default; // Move assignment operator

    // Conversion operators

    constexpr Colour to_float() const { return Colour(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f); }
};


