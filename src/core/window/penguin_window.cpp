#include <penguin_framework/core/window/penguin_window.hpp>
#include <penguin_framework/utils/exception.hpp>
#include <SDL3/SDL_video.h>

// --- Define WindowImpl ---

namespace penguin::core::window {

	struct Window::WindowImpl {
		// Window variables
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

		// Constructors
		WindowImpl(const char* p_title = "", Vector2i p_size = Vector2i(640, 480), WindowFlags p_flags = WindowFlags::None) 
			: window(SDL_CreateWindow(p_title, p_size.x, p_size.y, to_sdl_flags(p_flags)), &SDL_DestroyWindow), title(p_title) {

			Exception::throw_if(
				!window,
				SDL_GetError(),
				PF_Error::Window
			);

			size = p_size;
			min_size = p_size;
			max_size = p_size;

			set_flags(p_flags);

		}

		WindowImpl(const char* p_title = "", int width = 640, int height = 480, WindowFlags p_flags = WindowFlags::None) : WindowImpl(p_title, Vector2i(width, height), p_flags) {}

		// Move constructor & assignment destructors

		WindowImpl(const WindowImpl&) = delete;
		WindowImpl& operator=(const WindowImpl&) = delete;
		WindowImpl(WindowImpl&&) noexcept = default;
		WindowImpl& operator=(WindowImpl&&) noexcept = default;

		// Functions to change window title / sizes

		void set_title(const char* new_title) {
			title = new_title;

			Exception::throw_if(
				!SDL_SetWindowTitle(window.get(), title.c_str()),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void set_max_size(Vector2i p_max_size) {
			max_size = p_max_size;

			Exception::throw_if(
				!SDL_SetWindowMaximumSize(window.get(), max_size.x, max_size.y),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void set_min_size(Vector2i p_min_size) {
			min_size = p_min_size;

			Exception::throw_if(
				!SDL_SetWindowMinimumSize(window.get(), min_size.x, min_size.y),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void resize(Vector2i new_size) {
			size = new_size;

			Exception::throw_if(
				!SDL_SetWindowSize(window.get(), size.x, size.y),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		
		// Functions to change window visibility

		void show() {
			if (hidden) {
				hidden = false;

				Exception::throw_if(
					!SDL_ShowWindow(window.get()),
					SDL_GetError(),
					PF_Error::Window
				);
			}
		}
		void hide() {
			if (!hidden) {
				hidden = true;

				Exception::throw_if(
					!SDL_ShowWindow(window.get()),
					SDL_GetError(),
					PF_Error::Window
				);
			}
		}
		void minimize() {
			if (resizable && !minimized) {
				minimized = true;
				maximized = false; // Ensures the window isn't also marked as "maximized"

				Exception::throw_if(
					!SDL_MinimizeWindow(window.get()),
					SDL_GetError(),
					PF_Error::Window
				);
			}
		}
		// ONLY WORKS IF is_resizable is true
		void maximize() {
			if (resizable && !maximized) {
				maximized = true;
				minimized = false; // Ensures the window isn't also marked as "minimized"

				Exception::throw_if(
					!SDL_MaximizeWindow(window.get()),
					SDL_GetError(),
					PF_Error::Window
				);
			}
		}
		void restore() {
			if (resizable) {

				Exception::throw_if(
					!SDL_RestoreWindow(window.get()),
					SDL_GetError(),
					PF_Error::Window
				);

				Exception::throw_if(
					!SDL_SyncWindow(window.get()),
					SDL_GetError(),
					PF_Error::Window
				);
			}
		}
		void restore_async() {
			if (resizable) {

				Exception::throw_if(
					!SDL_RestoreWindow(window.get()),
					SDL_GetError(),
					PF_Error::Window
				);
			}
		}

		// Functions to toggle window states

		void enable_resizing() {
			resizable = true;

			Exception::throw_if(
				!SDL_SetWindowResizable(window.get(), resizable),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void disable_resizing() {
			resizable = false;

			Exception::throw_if(
				!SDL_SetWindowResizable(window.get(), resizable),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void enable_borders() {
			bordered = true;

			Exception::throw_if(
				!SDL_SetWindowBordered(window.get(), bordered),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void disable_borders() {
			bordered = false;

			Exception::throw_if(
				!SDL_SetWindowBordered(window.get(), bordered),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void enter_fullscreen() {
			fullscreen = true;

			Exception::throw_if(
				!SDL_SetWindowFullscreen(window.get(), fullscreen),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void exit_fullscreen() {
			fullscreen = false;

			Exception::throw_if(
				!SDL_SetWindowFullscreen(window.get(), fullscreen),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void enable_vsync() {
			vsync_enabled = true;

			Exception::throw_if(
				!SDL_SetWindowSurfaceVSync(window.get(), static_cast<int>(PF_WindowVSyncFlags::VSync_Adaptive)),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void disable_vsync() {
			vsync_enabled = false;

			Exception::throw_if(
				!SDL_SetWindowSurfaceVSync(window.get(), static_cast<int>(PF_WindowVSyncFlags::VSync_Disabled)),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void grab_mouse() {
			mouse_grabbed = true;

			Exception::throw_if(
				!SDL_SetWindowMouseGrab(window.get(), mouse_grabbed),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void release_mouse() {
			mouse_grabbed = false;

			Exception::throw_if(
				!SDL_SetWindowMouseGrab(window.get(), mouse_grabbed),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void add_always_on_top() {
			always_on_top = true;

			Exception::throw_if(
				!SDL_SetWindowAlwaysOnTop(window.get(), always_on_top),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void remove_always_on_top() {
			always_on_top = false;

			Exception::throw_if(
				!SDL_SetWindowAlwaysOnTop(window.get(), always_on_top),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void gain_focus() {
			focused = true;

			Exception::throw_if(
				!SDL_SetWindowFocusable(window.get(), focused),
				SDL_GetError(),
				PF_Error::Window
			);
		}
		void lose_foucs() {
			focused = false;

			Exception::throw_if(
				!SDL_SetWindowFocusable(window.get(), focused),
				SDL_GetError(),
				PF_Error::Window
			);
		}

		void set_flags(WindowFlags& flags) {
			resizable = has_flag(flags, WindowFlags::Resizable);
			hidden = has_flag(flags, WindowFlags::Hidden);
			minimized = has_flag(flags, WindowFlags::Maximized);
			maximized = has_flag(flags, WindowFlags::Minimized);
			bordered = !(has_flag(flags, WindowFlags::Borderless)); // If the borderless flag is set, we need to set bordered to be false
			fullscreen = has_flag(flags, WindowFlags::Fullscreen);
			mouse_grabbed = has_flag(flags, WindowFlags::MouseGrabbed);
			always_on_top = has_flag(flags, WindowFlags::AlwaysOnTop);
			focused = has_flag(flags, WindowFlags::InputFocus) || has_flag(flags, WindowFlags::MouseFocus);
		}
	};

	// --- Define Window Methods ---

	Window::~Window() = default;
	Window::Window(Window&&) = default;
	Window& Window::operator=(Window&&) = default;

	void Window::set_title(const char* new_title) { pimpl_->set_title(new_title);}
	void Window::set_max_size(Vector2i p_max_size) { pimpl_->set_max_size(p_max_size); }
	void Window::set_min_size(Vector2i p_min_size) { pimpl_->set_min_size(p_min_size); }
	void Window::resize(Vector2i new_size) { pimpl_->resize(new_size); }

	void Window::show() { pimpl_->show(); }
	void Window::hide() { pimpl_->hide(); }
	void Window::minimize() { pimpl_->minimize(); }
	void Window::maximize() {pimpl_->maximize();}
	void Window::restore() { pimpl_->restore();}
	void Window::restore_async() { pimpl_->restore_async(); }

	void Window::enable_resizing() { pimpl_->enable_resizing(); }
	void Window::disable_resizing() { pimpl_->disable_resizing();}

	void Window::enable_borders() { pimpl_->enable_borders(); }
	void Window::disable_borders() { pimpl_->disable_borders(); }

	void Window::enter_fullscreen() { pimpl_->enter_fullscreen(); }
	void Window::exit_fullscreen() { pimpl_->exit_fullscreen(); }

	void Window::enable_vsync() { pimpl_->enable_vsync(); }
	void Window::disable_vsync() { pimpl_->disable_vsync(); }

	void Window::grab_mouse() { pimpl_->grab_mouse(); }
	void Window::release_mouse() { pimpl_->release_mouse(); }

	void Window::add_always_on_top() { pimpl_->add_always_on_top(); }
	void Window::remove_always_on_top() { pimpl_->remove_always_on_top(); }

	void Window::gain_focus() { pimpl_->gain_focus();}
	void Window::lose_foucs() { pimpl_->lose_foucs(); }

	const char* Window::get_title() { return pimpl_->title.c_str(); }
	Vector2i Window::get_window_size() const { return pimpl_->size; }
	Vector2i Window::get_max_window_size() const { return pimpl_->max_size; }
	Vector2i Window::get_min_window_size() const { return pimpl_->min_size; }

	int Window::get_window_width() { return pimpl_->size.x; }
	int Window::get_window_height() { return pimpl_->size.y; }

	void Window::close() { pimpl_->open = false; }

	// Checking for window states

	bool Window::is_resizable() const { return pimpl_->resizable; }
	bool Window::is_hidden() const { return pimpl_->hidden; }
	bool Window::is_minimized() const { return pimpl_->minimized; }
	bool Window::is_maximized() const { return pimpl_->maximized; }
	bool Window::is_bordered() const { return pimpl_->bordered; }
	bool Window::is_fullscreen() const { return pimpl_->fullscreen; }
	bool Window::is_vsync_enabled() const { return pimpl_->vsync_enabled; }
	bool Window::is_mouse_grabbed() const { return pimpl_->mouse_grabbed; }
	bool Window::is_always_on_top() const { return pimpl_->always_on_top; }
	bool Window::is_focused() const { return pimpl_->focused; }
	bool Window::is_open() const { return pimpl_->open; }
}
