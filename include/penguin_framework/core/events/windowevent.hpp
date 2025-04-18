#pragma once

#include <SDL3/SDL_events.h>
#include <functional>
#include <array>

namespace pf::core::events {

	enum class PF_WindowEventIndex : size_t {
		Resized,
		Hidden,
		Shown,
		Minimized,
		Maximized,
		Restored,
		FullscreenEntered,
		FullscreenExited,
		MouseGrabbed,
		MouseReleased,
		FocusGained,
		FocusLost,
		Close,
		End
	};

	class PF_WindowEvent {
	public:
		// Callback types for various events
		using PF_EventCallback = std::function<void()>;

		// Handling events at the high level

		static void handle_events(const SDL_Event& p_event);
		static void register_callback(PF_WindowEventIndex index, const PF_EventCallback& callback);
		static void trigger_event(PF_WindowEventIndex index);

	private:
		static inline std::array<PF_EventCallback, size_t>(PF_WindowEventIndex::End) callbacks = {};
	};
}