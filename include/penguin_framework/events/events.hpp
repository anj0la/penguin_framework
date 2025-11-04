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

		void poll();

		// The event needs references to the input and the window events
		// The event will then call them to handle the events respectively
		// No need to add a callback function to try and decouple input from the events
		// event.input

	private:
		std::unique_ptr<penguin::internal::events::EventsImpl> pimpl_;
	};
}