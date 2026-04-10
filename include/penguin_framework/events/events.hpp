#pragma once

#include <penguin_api.hpp>
#include <penguin_framework/events/input_event.hpp>
#include <memory>

namespace penguin::internal::events {
	class EventsImpl;
}

namespace penguin::events {

	class PENGUIN_API Events {
	public:
		Events();
		~Events();

		void subscribe(const std::function<void(const InputEvent&)>& callback);
		void poll();
		bool should_quit(); 

	private:
		std::unique_ptr<penguin::internal::events::EventsImpl> pimpl_;
	};
}