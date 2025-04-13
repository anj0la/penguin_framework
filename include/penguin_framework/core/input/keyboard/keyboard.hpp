#pragma once

#include "core/input/keyboard/keyboard_keys.hpp"

#include <array>

namespace pf::core::input::keyboard {
	class Keyboard {
	public:
		static void is_key_pressed(PF_Key key);
		static void is_any_key_pressed();

	private:
		std::array<bool, NUM_KEYS> key_pressed{}; // no keys are pressed initally

	};
}
