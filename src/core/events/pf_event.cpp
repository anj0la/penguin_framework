#include "core/events/pf_event.hpp"

using pf::events::PF_Event;
using pf::events::PF_WindowEvent;

void PF_Event::poll_events() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Handle window events separately
		PF_WindowEvent::handle_events(event);
		// Handle input events seperately
		// Input::handle_events(event);
	}
}