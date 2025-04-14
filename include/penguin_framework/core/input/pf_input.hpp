#pragma once

#include "core/input/keyboard/keyboard.hpp"
#include <SDL3/SDL_events.h>

namespace pf::core::input {
	class PF_Input {
		static void handle_events(const SDL_Event& p_event);
		static void update();
		// static void register_callback(const PF_EventCallback& callback);
		// static void trigger_event();
	};
}