#include "core/events/pf_event.hpp"

using pf::core::events::PF_Event;
using pf::core::events::PF_WindowEvent;
using pf::core::input::PF_Input;

void PF_Event::poll_events() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// Handle window events separately
		PF_WindowEvent::handle_events(event);

		// Handle input events seperately
		PF_Input::handle_events(event);
	}
}