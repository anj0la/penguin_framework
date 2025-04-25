#include <penguin_framework/core/math/colour.hpp>
#include <algorithm> // For std::clamp

Colour::Colour() : r(0u), g(0u), b(0u), a(255u) {}

Colour::Colour(unsigned int p_r, unsigned int p_g, unsigned int p_b, unsigned int p_a) :
    r(std::clamp(p_r, 0u, 255u)),
    g(std::clamp(p_g, 0u, 255u)),
    b(std::clamp(p_b, 0u, 255u)),
    a(std::clamp(p_a, 0u, 255u)) {
}