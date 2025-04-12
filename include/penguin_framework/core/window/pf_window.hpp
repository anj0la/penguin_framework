#pragma once

#include "core/window/pf_windowflags.hpp"
#include "exception.hpp"
#include "core/math/vector2i.hpp"
#include "core/events/pf_event.hpp"

#include "utils/string.hpp"

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
			PF_Window(const char* p_title = "", int width = 640, int height = 480, PF_WindowFlags p_flags = PF_WindowFlags::None) : PF_Window(p_title, Vector2i(width, height), p_flags) {}

			// Needed for objects requiring the raw SDL pointer. Only used internally, should not be used AT all otherwise.
			SDL_Window* get_ptr();

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

			// The String class is very minimal, but std::string is not stable
			// So the String class allows me to store string information more safely
			// But it has much less functions than std::string, so for now, it's expected
			// to wrap this c_str() around an std::string if needing to store the title somewhere.
			
			inline const char* get_title() { return title.c_str(); } 

			inline Vector2i get_window_size() const { return size; }
			inline Vector2i get_max_window_size() const { return max_size; }
			inline Vector2i get_min_window_size() const { return min_size; }

			inline int get_window_width() { return size.x; }
			inline int get_window_height() { return size.y; }

			inline void close() { open = false; }

			// Checking for window states

			inline bool is_resizable() const { return resizable; }
			inline bool is_hidden() const { return hidden; }
			inline bool is_minimized() const { return minimized; }
			inline bool is_maximized() const { return maximized; }
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
			String title;
			Vector2i size;
			Vector2i min_size;
			Vector2i max_size;

			// Flags

			bool resizable;
			bool hidden;
			bool minimized;
			bool maximized;
			bool bordered;
			bool fullscreen;
			bool vsync_enabled = false; // disabled by default
			bool mouse_grabbed;
			bool always_on_top;
			bool focused;
			bool open = true;

			// Private functions

			void set_flags(PF_WindowFlags& flags);
		};
	}
}