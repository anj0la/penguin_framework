#pragma once

#include <limits>

namespace penguin::math {
	inline constexpr double pos_inf = std::numeric_limits<double>::infinity();
	inline constexpr double neg_inf = -std::numeric_limits<double>::infinity();
	inline constexpr double nan = std::numeric_limits<double>::quiet_NaN();
	inline constexpr double epsilon = 1e-6;
}

