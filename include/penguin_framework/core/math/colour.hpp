#pragma once

#include <penguin_framework/penguin_api.hpp>
#include <algorithm>

struct PENGUIN_API [[nodiscard]] Colour {

    unsigned int r, g, b, a; 

    // Default constructor

    Colour();

    // Regular constructors

    Colour(unsigned int p_r, unsigned int p_g, unsigned int p_b, unsigned int p_a);

    // Copy and move constructors

    Colour(const Colour& c) = default; // Copy constructor
    Colour(Colour&& c) noexcept = default; // Move constructor
    Colour& operator=(const Colour& c) = default; // Copy assignment operator
    Colour& operator=(Colour&& c) noexcept = default; // Move assignment operator
};


