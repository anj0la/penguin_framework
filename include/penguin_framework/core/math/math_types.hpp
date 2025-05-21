#pragma once

#include <limits>

namespace penguin::math {
	inline constexpr double Inf = std::numeric_limits<double>::infinity();
	inline constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
	inline constexpr double epsilon = 1e-6;
}

