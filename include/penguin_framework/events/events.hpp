#pragma once

#include <penguin_api.hpp>
#include <memory>

namespace penguin::internal::events {
	class EventsImpl;
}

namespace penguin::events {

	class PENGUIN_API Events {
	public:
		Events();
		~Events();

		void poll(); // inside events_impl.cpp, the corresponding SDL event will be grabbed, afterwards, the SDL event will be converted into an InputEvent
		// and then the update function for the Input Singleton will be called

		// E.g.,
		// void EventsImpl::poll() {
		//		SDL_Event sdl_event;
		//		SDL_PollEvent(&sdl_event);
		//		InputEvent event(sdl_event);
		//		Input.update(event);
		//		and other code...

		// The event needs references to the input and the window events
		// The event will then call them to handle the events respectively
		// No need to add a callback function to try and decouple input from the events
		// event.input

	private:
		std::unique_ptr<penguin::internal::events::EventsImpl> pimpl_;
	};
}