#pragma once

#include "core/window/pf_windowflags.hpp"
#include "exception.hpp"
#include "core/math/vector2i.hpp"
#include "core/events/pf_event.hpp"

#include <SDL3/SDL_video.h>

#include <functional>
#include <memory>

namespace pf {

	namespace core {

		class PF_Window {
		public:

			// Callback types for various events
			using PF_EventCallback = std::function<void()>;

			PF_Window(const char* p_title = "", Vector2i p_size = Vector2i(640, 480), PF_WindowFlags p_flags = PF_WindowFlags::None);

			// Needed for objects requiring the raw SDL pointer. Only used internally, should not be used AT all otherwise.
			SDL_Window* get_window();

			// Regular functions

			void set_title(const char* new_title);
			void set_max_size(Vector2i p_max_size);
			void set_min_size(Vector2i p_min_size);
			void resize(Vector2i new_size);

			void show();
			void hide();
			void minimize();
			void maximize();
			void restore(); // used to restore a minimized / maximized window. Has no effect on a fullscreen window.
			void restore_async();

			void enable_resizing();
			void disable_resizing();

			void enable_borders();
			void disable_borders();

			void enter_fullscreen();
			void exit_fullscreen();

			void enable_vsync();
			void disable_vsync();

			void grab_mouse();
			void release_mouse();

			void always_on_top();
			void remove_always_on_top();

			void gain_focus();
			void lose_foucs();

			inline void close() { open = false; }

			// Checking for window states

			inline bool is_resizable() const { return resizable; }
			inline bool is_hidden() const { return hidden; }
			inline bool is_minimized() const { return minimized; }
			inline bool is_maximized() const { return maximized; }
			inline bool is_restored() const { return restored; }
			inline bool is_bordered() const { return bordered; }
			inline bool is_fullscreen() const { return fullscreen; }
			inline bool is_vsync_enabled() const { return vsync_enabled; }
			inline bool is_mouse_grabbed() const { return mouse_grabbed; }
			inline bool is_always_on_top() const { return always_on_top; }
			inline bool is_focused() const { return focused; }
			inline bool is_open() const { return open; }

			// Callback functions

			inline void on_resized(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::Resized, callback); }

			inline void on_hidden(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::Hidden, callback); }
			inline void on_shown(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::Shown, callback); }
			inline void on_minimized(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::Minimized, callback); }
			inline void on_maximized(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::Maximized, callback); }
			inline void on_restored(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::Restored, callback); }

			inline void on_fullscreen_entered(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::FullscreenEntered, callback); }
			inline void on_fullscreen_exited(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::FullscreenExited, callback); }

			inline void on_mouse_grabbed(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::MouseGrabbed, callback); }
			inline void on_mouse_released(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::MouseReleased, callback); }

			inline void on_focus_gained(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::FocusGained, callback); }
			inline void on_focus_lost(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::FocusLost, callback); }

			inline void on_close(const PF_EventCallback& callback) { pf::events::PF_WindowEvent::register_callback(pf::events::PF_WindowEventIndex::Close, callback); }

			inline void poll_events() { pf::events::PF_Event::poll_events(); } // Poll events from Event class

		private:
			std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
			Vector2i size;
			Vector2i min_size;
			Vector2i max_size;

			// Flags

			bool resizable = false;
			bool hidden = false;
			bool minimized = false;
			bool maximized = false;
			bool restored = true;
			bool bordered = false;
			bool fullscreen = false;
			bool vsync_enabled = false;
			bool mouse_grabbed = false;
			bool always_on_top = false;
			bool focused = false;
			bool open = true;
		};
	}
}