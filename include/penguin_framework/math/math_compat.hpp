#pragma once

#include <limits>
#include <cfloat> 

// abs, isnan and isinf are NOT constexpr in C++ 20.
// We define them here so that they are constexpr to support C++ 20.
// 
// Note that C++ 23 and C++ 26 make these functions constexpr, but as the project requires C++ 20, this ensures that
// the framework will work on C++ 20.

namespace penguin::math::compat {

    template <typename T>
    constexpr T p_abs(T val) {
        return (val < static_cast<T>(0)) ? -val : val;
    }

    template <typename T>
    constexpr bool p_isnan(T val) {
        return !(val == val);
    }

    template <typename T>
    constexpr bool p_isinf(T val) {
        if (!std::numeric_limits<T>::has_infinity) {
            return false; // Type doesn't support infinity
        }
        return val == std::numeric_limits<T>::infinity() ||
            val == -std::numeric_limits<T>::infinity();
    }
}