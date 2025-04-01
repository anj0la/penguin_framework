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
		void set_max_size(Vector2i max_size);
		void set_min_size(Vector2i min_size);
		void resize(Vector2i new_size);

		void show();
		void hide();
		void restore();

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

	private:
		std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
		int width;
		int height;

	};

}