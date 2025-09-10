#pragma once

#include <penguin_api.hpp>
#include <penguin_framework/events/event_type.hpp>
#include <memory>

namespace penguin::events {

	namespace penguin::internal::events {
		struct EventImpl;
	}

	class PENGUIN_API Event {
	public:
		Event();
		~Event();

		// Can be any of the structs, so with the event, we can check its type using type()

		// We then have easy functions for conversion

		EventType type() const;

		const QuitEvent& as_quit() const;
		const WindowEvent& as_window() const;
		const InputEvent& as_input() const;
		const CustomEvent& as_custom() const;

	private:
		std::unique_ptr<penguin::internal::events::EventImpl> pimpl_;
	};
}