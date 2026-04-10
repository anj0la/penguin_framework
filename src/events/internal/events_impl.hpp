#pragma once

#include <memory>
#include <functional>
#include <SDL3/SDL_events.h>
#include <penguin_framework/events/input_event.hpp>
#include <penguin_framework/input/input.hpp>

namespace penguin::internal::events {

	class EventsImpl {
	public:
		EventsImpl() = default;
		~EventsImpl() = default;

		void subscribe(const std::function<void(const InputEvent&)>& callback);
		void poll();
		bool should_quit(); // marks application for closure

	private:
		std::function<void(const InputEvent&)>& input_func;
		bool quit_requested = false;
	};
}