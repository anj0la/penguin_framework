#include <events/internal/events_impl.hpp>

namespace penguin::internal::events {

	void EventsImpl::subscribe(const std::function<void(const InputEvent&)>& callback) {
		input_func = callback;
	}

	void EventsImpl::poll() {
		SDL_Event sdl_event;
		while (SDL_PollEvent(&sdl_event)) {
			if (sdl_event == SDL_EVENT_QUIT) {
				quit_requested = true;
			}
			else {
				InputEvent e(NativeEventPtr{ sdl_event });
				Input::update(e);
				input_func(e);
			}
		}
	}
	
	bool EventsImpl::should_quit() {
		return quit_requested;
	}
}