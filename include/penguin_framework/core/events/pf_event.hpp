#pragma once

#include "core/events/pf_windowevent.hpp"

#include <SDL3/SDL_events.h>

#include <vector>
#include <functional>

namespace pf::core::events {

	class PF_Event {
		static void poll_events();
	};
}