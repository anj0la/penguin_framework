#pragma once

#include <cstdint>

namespace penguin::input::mouse {

    enum class Button : uint8_t {
        Left = 1,
        Middle = 2,
        Right = 3,
        X1 = 4,
        X2 = 5
    };

    enum class ButtonFlags : uint32_t {
        None = 0,
        LeftMask = 1u << 0,    // 1u << (1-1)
        MiddleMask = 1u << 1,  // 1u << (2-1) 
        RightMask = 1u << 2,   // 1u << (3-1)
        X1Mask = 1u << 3,      // 1u << (4-1)
        X2Mask = 1u << 4       // 1u << (5-1)
    };

    // Bitwise operations

    constexpr ButtonFlags operator|(ButtonFlags a, ButtonFlags b) {
        return static_cast<ButtonFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
    }

    constexpr ButtonFlags operator&(ButtonFlags a, ButtonFlags b) {
        return static_cast<ButtonFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    }

    // Utility functions

    constexpr ButtonFlags button_to_mask(Button button) {
        return static_cast<ButtonFlags>(1u << (static_cast<uint32_t>(button) - 1));
    }

    constexpr bool is_pressed(ButtonFlags state, Button button) {
        return (state & button_to_mask(button)) != ButtonFlags::None;
    }
}