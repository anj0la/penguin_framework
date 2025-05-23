#include <penguin_framework/core/window/penguin_window.hpp>
#include <penguin_framework/core/window/penguin_window_impl.hpp>

using penguin::core::window::Window;
using penguin::core::window::WindowImpl;

// Define WindowImpl Methods

WindowImpl::WindowImpl(const char* p_title, Vector2i p_size, WindowFlags p_flags)
	: window(SDL_CreateWindow(p_title, p_size.x, p_size.y, static_cast<SDL_WindowFlags>(p_flags)), &SDL_DestroyWindow), title(p_title) {

	Exception::throw_if(
		!window,
		SDL_GetError(),
		Error::Window
	);

	size = p_size;
	min_size = p_size;
	max_size = p_size;

	set_flags(p_flags);
}

void WindowImpl::set_flags(WindowFlags& flags) {
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

bool WindowImpl::set_title(const char* new_title) {
	title = new_title;
	return SDL_SetWindowTitle(window.get(), title.c_str());
}

bool WindowImpl::set_max_size(Vector2i p_max_size) {
	if (p_max_size.x < 0 || p_max_size.y < 0) return false; // the vector's x and y coordinates must be a positive integer
	max_size = p_max_size;
	return SDL_SetWindowMaximumSize(window.get(), max_size.x, max_size.y);
}
bool WindowImpl::set_min_size(Vector2i p_min_size) {
	if (p_min_size.x < 0 || p_min_size.y < 0) return false; // the vector's x and y coordinates must be a positive integer
	min_size = p_min_size;
	return SDL_SetWindowMinimumSize(window.get(), min_size.x, min_size.y);
}
bool WindowImpl::resize(Vector2i new_size) {
	if (new_size.x <= 0 || new_size.y <= 0) return false; // the vector's x and y coordinates must be greater than 0
	size = new_size;
	return SDL_SetWindowSize(window.get(), size.x, size.y);
}

bool WindowImpl::show() {
	if (hidden) {
		hidden = false;
		return SDL_ShowWindow(window.get());
	}
	return true; // indicates that no error occured (hidden is already false, indicating the window is already visible)
}
bool WindowImpl::hide() {
	if (!hidden) {
		hidden = true;
		return SDL_HideWindow(window.get());
	}
	return true; // indicates that no error occured (hidden is already true, indicating the window is already invisible)
}
bool WindowImpl::minimize() {
	if (resizable && !minimized) {
		minimized = true;
		maximized = false; // Ensures the window isn't also marked as "maximized"
		return SDL_MinimizeWindow(window.get());
	}
	return true; // if the window is already minimized OR not resizable, we still mark as true as it ran without error
}
bool WindowImpl::maximize() {
	if (resizable && !maximized) {
		maximized = true;
		minimized = false; // Ensures the window isn't also marked as "minimized"

		return SDL_MaximizeWindow(window.get());
	}
	return true; // if the window is already minimized OR not resizable, we still mark as true as it ran without error
}

bool WindowImpl::restore() {
	if (resizable) {
		bool res = SDL_RestoreWindow(window.get());
		bool res_sync = SDL_SyncWindow(window.get());

		maximized = false; // both flags should be false
		minimized = false;

		return res && res_sync;
	}
	return true; // no error occurs if not resizable

}
bool WindowImpl::restore_async() {
	if (resizable) {
		maximized = false; // both flags should be false
		minimized = false;

		return SDL_RestoreWindow(window.get());
	}
	return true; // no error occurs if not resizable
}

// Functions to toggle window states

bool WindowImpl::enable_resizing() {
	resizable = true;
	return SDL_SetWindowResizable(window.get(), resizable);
}
bool WindowImpl::disable_resizing() {
	resizable = false;
	return SDL_SetWindowResizable(window.get(), resizable);
}
bool WindowImpl::enable_borders() {
	bordered = true;
	return SDL_SetWindowBordered(window.get(), bordered);
}
bool WindowImpl::disable_borders() {
	bordered = false;
	return SDL_SetWindowBordered(window.get(), bordered);
}
bool WindowImpl::enter_fullscreen() {
	fullscreen = true;
	return SDL_SetWindowFullscreen(window.get(), fullscreen);
}
bool WindowImpl::exit_fullscreen() {
	fullscreen = false;
	return SDL_SetWindowFullscreen(window.get(), fullscreen);
}

bool WindowImpl::grab_mouse() {
	mouse_grabbed = true;
	return SDL_SetWindowMouseGrab(window.get(), mouse_grabbed);
}
bool WindowImpl::release_mouse() {
	mouse_grabbed = false;
	return SDL_SetWindowMouseGrab(window.get(), mouse_grabbed);
}
bool WindowImpl::add_always_on_top() {
	always_on_top = true;
	return SDL_SetWindowAlwaysOnTop(window.get(), always_on_top);
}
bool WindowImpl::remove_always_on_top() {
	always_on_top = false;
	return SDL_SetWindowAlwaysOnTop(window.get(), always_on_top);
}
bool WindowImpl::gain_focus() {
	focused = true;
	return SDL_SetWindowFocusable(window.get(), focused);
}
bool WindowImpl::lose_foucs() {
	focused = false;
	return SDL_SetWindowFocusable(window.get(), focused);
}

// Define Window Methods

Window::Window(const char* p_title, Vector2i p_size, WindowFlags p_flags) : pimpl_(std::make_unique<WindowImpl>(p_title, p_size, p_flags)) {}
Window::~Window() = default;

bool Window::set_title(const char* new_title) { return pimpl_->set_title(new_title); }
bool Window::set_max_size(Vector2i p_max_size) { return pimpl_->set_max_size(p_max_size); }
bool Window::set_min_size(Vector2i p_min_size) { return pimpl_->set_min_size(p_min_size); }
bool Window::resize(Vector2i new_size) { return pimpl_->resize(new_size); }

bool Window::show() { return pimpl_->show(); }
bool Window::hide() { return pimpl_->hide(); }
bool Window::minimize() { return pimpl_->minimize(); }
bool Window::maximize() { return pimpl_->maximize(); }
bool Window::restore() { return pimpl_->restore(); }
bool Window::restore_async() { return pimpl_->restore_async(); }

bool Window::enable_resizing() { return pimpl_->enable_resizing(); }
bool Window::disable_resizing() { return pimpl_->disable_resizing(); }

bool Window::enable_borders() { return pimpl_->enable_borders(); }
bool Window::disable_borders() { return pimpl_->disable_borders(); }

bool Window::enter_fullscreen() { return pimpl_->enter_fullscreen(); }
bool Window::exit_fullscreen() { return pimpl_->exit_fullscreen(); }

bool Window::grab_mouse() { return pimpl_->grab_mouse(); }
bool Window::release_mouse() { return pimpl_->release_mouse(); }

bool Window::add_always_on_top() { return pimpl_->add_always_on_top(); }
bool Window::remove_always_on_top() { return pimpl_->remove_always_on_top(); }

bool Window::gain_focus() { return pimpl_->gain_focus(); }
bool Window::lose_foucs() { return pimpl_->lose_foucs(); }

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
bool Window::is_mouse_grabbed() const { return pimpl_->mouse_grabbed; }
bool Window::is_always_on_top() const { return pimpl_->always_on_top; }
bool Window::is_focused() const { return pimpl_->focused; }
bool Window::is_open() const { return pimpl_->open; }

// Implicit SDL_Window* -> void* conversion; no need for static_cast<NativeWindowPtr>.
NativeWindowPtr Window::get_native_ptr() const { return NativeWindowPtr{ pimpl_->window.get() }; }