#include <penguin_framework/window/penguin_window.hpp>
#include <window/internal/penguin_window_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::window {

	Window::Window(const char* p_title, penguin::math::Vector2i p_size, WindowFlags p_flags) : pimpl_(nullptr), valid_state_(false) {
		// Log attempt to create a window
		std::string message = "Attempting to create window with dimensions: (" + std::to_string(p_size.x) + "," + std::to_string(p_size.y) + ").";
		penguin::log::Logger::get_instance().info(message.c_str());
		
		try {
			pimpl_ = std::make_unique<penguin::internal::window::WindowImpl>(p_title, p_size, p_flags);
			valid_state_ = true;
		} catch (const penguin::internal::error::InternalError& e) {
			// Get the error code and message
			std::string error_code_str = penguin::internal::error::error_code_to_string(e.get_error());
			std::string error_message = e.what();
			std::string error_message = error_code_str + ": " + error_message;

			// Log the error
			penguin::log::Logger::get_instance().error(error_message.c_str());

		} catch (const std::exception& e) { // Other specific C++ errors
			// Get error message
			std::string last_error_message = e.what();
			std::string error_message = "Unknown: " + error_message;

			// Log the error
			penguin::log::Logger::get_instance().error(error_message.c_str());
		}
	}

	Window::~Window() = default;

	// Validity checking

	bool Window::is_valid() const noexcept {
		return valid_state_;
	}
	
	explicit Window::operator bool() const noexcept {
		is_valid();
	}

	void Window::set_title(const char* new_title) { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->set_title(new_title);
		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to set window title.");
			return;
		}
	}

	void Window::set_max_size(penguin::math::Vector2i p_max_size) { 
		if (!is_valid()) {
			return;
		}

		// If size is less than 0, log warning
		penguin::log::Logger::get_instance().warning("The x or y component of the new size is less than or equal to 0. The window size will NOT be set.");

		bool res = pimpl_->set_max_size(p_max_size); 
		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to set window max size.");
			return;
		}
	}

	void Window::set_min_size(penguin::math::Vector2i p_min_size) { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->set_min_size(p_min_size);
		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to set window min size.");
			return;
		} 
	}

	void Window::resize(penguin::math::Vector2i new_size) { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->resize(new_size); 
		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to resize window.");
		}
	}

	void Window::show() {
		if (!is_valid()) {
			return;
		}
		
		bool res = pimpl_->show(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to show window.");
		}
	}

	void Window::hide() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->hide(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to hide window.");
		}
	}

	void Window::minimize() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->minimize();

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to minimize window.");
		}
	}

	void Window::minimize_async() {
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->minimize_async();

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to minimize window asynchronously.");
		}
	}

	void Window::maximize() { 
		if (!is_valid()) {
			return;
		}

		bool res =  pimpl_->maximize(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to maximize window.");
		}
	}

	void Window::maximize_async() {
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->maximize_async();

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to maximize window asynchronously.");
		}
	}
	
	void Window::restore() {
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->restore();

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to restore window.");
		}
	}
	
	void Window::restore_async() { 
		if (!is_valid()) {
			return;
		}
		
		bool res = pimpl_->restore_async(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to restore window asynchronously.");
		}
	}

	void Window::enable_resizing() { 
		if (!is_valid()) {
			return;
		}
		bool res = pimpl_->enable_resizing(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to enable window resizing.");
		}
	}

	void Window::disable_resizing() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->disable_resizing(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to disable window resizing.");
		}
	}

	void Window::enable_borders() {
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->enable_borders(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to enable window borders.");
		}
	}

	void Window::disable_borders() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->disable_borders(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to disable window borders.");
		}
	}

	void Window::enter_fullscreen() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->enter_fullscreen();

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to enter fullscreen mode.");
		}
	}

	void Window::exit_fullscreen() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->exit_fullscreen(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to exit fullscreen mode.");
		}
	}

	void Window::grab_mouse() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->grab_mouse(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to grab mouse.");
		}
	}

	void Window::release_mouse() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->release_mouse(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to release mouse.");
		}
	}

	void Window::add_always_on_top() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->add_always_on_top(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to add always on top flag to window.");
		}
	}

	void Window::remove_always_on_top() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->remove_always_on_top(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to remove always on top flag from window.");
		}
	}

	void Window::gain_focus() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->gain_focus(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to add focus flag to window.");
		}
	}

	void Window::lose_foucs() { 
		if (!is_valid()) {
			return;
		}

		bool res = pimpl_->lose_foucs(); 

		if (!res) {
			// Log the error
			penguin::log::Logger::get_instance().error("Window_Function_Failed: Failed to remove focus flag to window.");
		}
	}

	const char* Window::get_title() { 
		return pimpl_->title.c_str(); 
	}

	penguin::math::Vector2i Window::get_window_size() const {
		return pimpl_->size; 
	}

	penguin::math::Vector2i Window::get_max_window_size() const { 
		return pimpl_->max_size; 
	}

	penguin::math::Vector2i Window::get_min_window_size() const { 
		return pimpl_->min_size; 
	}

	int Window::get_window_width() const { 
		return pimpl_->size.x; 
	}

	int Window::get_window_height() const { 
		return pimpl_->size.y; 
	}

	void Window::close() { 
		pimpl_->open = false; 
		valid_state_ = false; // the window still exists at this point, but all window operations should not be available anymore
	}

	// Checking for window states

	bool Window::is_resizable() const { 
		return valid_state_ && pimpl_->resizable;
	}

	bool Window::is_hidden() const { 
		return valid_state_ && pimpl_->hidden;
	}

	bool Window::is_minimized() const { 
		return valid_state_ && pimpl_->minimized;
	}

	bool Window::is_maximized() const { 
		return valid_state_ && pimpl_->maximized;
	}

	bool Window::is_bordered() const { 
		return valid_state_ && pimpl_->bordered;
	}

	bool Window::is_fullscreen() const { 
		return valid_state_ && pimpl_->fullscreen;
	}

	bool Window::is_mouse_grabbed() const { 
		return valid_state_ && pimpl_->mouse_grabbed;
	}

	bool Window::is_always_on_top() const { 
		return valid_state_ && pimpl_->always_on_top;
	}

	bool Window::is_focused() const { 
		return valid_state_ && pimpl_->focused;
	}

	bool Window::is_open() const { 
		return valid_state_ && pimpl_->open; 
	}

	// Implicit SDL_Window* -> void* conversion; no need for static_cast<NativeWindowPtr>.
	NativeWindowPtr Window::get_native_ptr() const { return NativeWindowPtr{ pimpl_->window.get() }; }
}