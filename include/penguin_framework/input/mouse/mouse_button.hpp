#pragma once

#include <cstdint>

namespace penguin::input::mouse {

    enum class MouseButton : uint8_t {
        Left = 1,
        Middle = 2,
        Right = 3,
        X1 = 4,
        X2 = 5
    };

    enum class MouseButtonFlags : uint32_t {
        None = 0,
        LeftMask = 1u << 0,    // 1u << (1-1)
        MiddleMask = 1u << 1,  // 1u << (2-1) 
        RightMask = 1u << 2,   // 1u << (3-1)
        X1Mask = 1u << 3,      // 1u << (4-1)
        X2Mask = 1u << 4       // 1u << (5-1)
    };

    // Bitwise operations

    constexpr MouseButtonFlags operator|(MouseButtonFlags a, MouseButtonFlags b) {
        return static_cast<MouseButtonFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
    }

    constexpr MouseButtonFlags operator&(MouseButtonFlags a, MouseButtonFlags b) {
        return static_cast<MouseButtonFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    }

    // Utility functions

    constexpr MouseButtonFlags button_to_mask(MouseButton button) {
        return static_cast<MouseButtonFlags>(1u << (static_cast<uint32_t>(button) - 1));
    }

    constexpr bool is_pressed(MouseButtonFlags state, MouseButton button) {
        return (state & button_to_mask(button)) != MouseButtonFlags::None;
    }
}