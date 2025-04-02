#pragma once

#include "core/window/pf_windowflags.hpp"
#include "exception.hpp"
#include "core/math/vector2i.hpp"

#include <SDL3/SDL_video.h>

#include <memory>


namespace pf {

	class PF_Window {
	public:
		PF_Window(const char* p_title = "", Vector2i p_size = Vector2i(640, 480), PF_WindowFlags p_flags = PF_WindowFlags::None);

		SDL_Window* get_window();

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

		inline bool is_hidden() const { return hidden; }
		inline bool is_fullscreen() const { return fullscreen; }
		inline bool is_bordered() const { return bordered; }
		inline bool is_resizable() const { return resizable; }
		inline bool is_minimized() const { return minimized; }
		inline bool is_maximized() const { return maximized; }
		inline bool is_open() const { return open; }
		inline bool is_mouse_grabbed() const { return mouse_grabbed; }
		inline bool is_always_on_top() const { return always_on_top; }
		inline bool is_vsync_enabled() const { return vsync_enabled; }
		inline bool is_restored() const { return restored; }
		inline bool is_focused() const { return focused; }

		inline void close() { is_open = false; }

	private:
		std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
		Vector2i size;
		Vector2i min_size;
		Vector2i max_size;

		// Flags

		bool fullscreen = false;
		bool resizable = false;
		bool bordered = false;
		bool hidden = false;
		bool minimized = false;
		bool maximized = false;
		bool open = true;
		bool mouse_grabbed = false;
		bool always_on_top = false;
		bool vsync_enabled = false;
		bool restored = true;
		bool focused = false;
	};

}