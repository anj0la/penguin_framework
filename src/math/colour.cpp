#include <penguin_framework/math/colour.hpp>

namespace penguin::math {
    Colour Colour::from_rgb(uint8_t red, uint8_t green, uint8_t blue) {
        return Colour(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f); // opaque by default
    }

    Colour Colour::from_rgba(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
        return Colour(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);
    }

    Colour Colour::from_argb(uint32_t p_argb) {
        uint8_t a = (p_argb >> 24) & 0xFF;
        uint8_t r = (p_argb >> 16) & 0xFF;
        uint8_t g = (p_argb >> 8) & 0xFF;
        uint8_t b = p_argb & 0xFF;
        return from_rgba(r, g, b, a);
    }
}

