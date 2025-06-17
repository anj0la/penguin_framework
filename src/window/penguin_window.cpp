#include <penguin_framework/window/penguin_window.hpp>
#include <window/internal/penguin_window_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::window {

	Window::Window(const char* p_title, penguin::math::Vector2i p_size, WindowFlags p_flags) : pimpl_(nullptr) {
		// Log attempt to create a window
		std::string message = "Attempting to create window with dimensions: (" + std::to_string(p_size.x) + "," + std::to_string(p_size.y) + ")...";
		PF_LOG_INFO(message.c_str());
		
		try {
			pimpl_ = std::make_unique<penguin::internal::window::WindowImpl>(p_title, p_size, p_flags);
			PF_LOG_INFO("Success: Window created successfully.");

		} catch (const penguin::internal::error::InternalError& e) {
			// Get the error code and message
			std::string error_code_str = penguin::internal::error::error_code_to_string(e.get_error());
			std::string error_message = error_code_str + ": " + e.what();;

			// Log the error
			PF_LOG_ERROR(error_message.c_str());

		} catch (const std::exception& e) { // Other specific C++ errors
			// Get error message
			std::string last_error_message = e.what();
			std::string error_message = "Unknown_Error: " + error_message;

			// Log the error
			PF_LOG_ERROR(error_message.c_str());
		}
	}

	Window::~Window() = default;

	// Validity checking

	bool Window::is_valid() const noexcept {
		if (!pimpl_) {
			return false;
		}

		return pimpl_->window.get() != nullptr && pimpl_->open; // pimpl_ is valid, but internal states might not be
	}
	
	Window::operator bool() const noexcept {
		return is_valid();
	}

	void Window::set_title(const char* new_title) { 
		if (!is_valid()) {
			PF_LOG_WARNING("set_title() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->set_title(new_title);

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to set window title.");
			return;
		}
	}

	void Window::set_max_size(penguin::math::Vector2i p_max_size) { 
		if (!is_valid()) {
			PF_LOG_WARNING("set_max_size() called on an uninitialized or destroyed window.");
			return;
		}

		if (p_max_size <= penguin::math::Vector2i::Zero) {
			PF_LOG_WARNING("Argument_Out_Of_Range: New size must be greater than (0, 0).");
			return; // Don't set the max size
		}

		bool res = pimpl_->set_max_size(p_max_size); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to set window max size.");
			return;
		}
	}

	void Window::set_min_size(penguin::math::Vector2i p_min_size) { 
		if (!is_valid()) {
			PF_LOG_WARNING("set_min_size() called on an uninitialized or destroyed window.");
			return;
		}

		if (p_min_size <= penguin::math::Vector2i::Zero) {
			PF_LOG_WARNING("Argument_Out_Of_Range: New size must be greater than (0, 0).");
			return; // Don't set the min size
		}

		bool res = pimpl_->set_min_size(p_min_size);

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to set window min size.");
			return;
		} 
	}

	void Window::resize(penguin::math::Vector2i new_size) { 
		if (!is_valid()) {
			PF_LOG_WARNING("resize() called on an uninitialized or destroyed window.");
			return;
		}

		if (new_size <= penguin::math::Vector2i::Zero) {
			PF_LOG_WARNING("Argument_Out_Of_Range: New size must be greater than (0, 0).");
			return; // Don't set the min size
		}

		bool res = pimpl_->resize(new_size); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to resize window.");
		}
	}

	void Window::show() {
		if (!is_valid()) {
			PF_LOG_WARNING("show() called on an uninitialized or destroyed window.");
			return;
		}

		if (!pimpl_->hidden) {
			PF_LOG_DEBUG("Called show() on a visible window; skipping.");
			return;
		}
		
		bool res = pimpl_->show(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to show window.");
		}
	}

	void Window::hide() { 
		if (!is_valid()) {
			PF_LOG_WARNING("hide() called on an uninitialized or destroyed window.");
			return;
		}

		if (pimpl_->hidden) {
			PF_LOG_DEBUG("Called hide() on a hidden window; skipping.");
			return;
		}

		bool res = pimpl_->hide(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to hide window.");
		}
	}

	void Window::minimize() { 
		if (!is_valid()) {
			PF_LOG_WARNING("minimize() called on an uninitialized or destroyed window.");
			return;
		}

		if (!pimpl_->resizable) {
			PF_LOG_DEBUG("Called minimize() on a fixed window; skipping.");
			return;
		}

		if (pimpl_->resizable && pimpl_->minimized) {
			PF_LOG_DEBUG("Called minimize() on a minimized window; skipping.");
			return;
		}

		bool res = pimpl_->minimize();

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to minimize window.");
		}
	}

	void Window::minimize_async() {
		if (!is_valid()) {
			PF_LOG_WARNING("minimize_async() called on an uninitialized or destroyed window.");
			return;
		}

		if (!pimpl_->resizable) {
			PF_LOG_DEBUG("Called minimize() on a fixed window; skipping.");
			return;
		}

		if (pimpl_->resizable && pimpl_->minimized) {
			PF_LOG_DEBUG("Called minimize_async() on a minimized window; skipping.");
			return;
		}

		bool res = pimpl_->minimize_async();

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to minimize window asynchronously.");
		}
	}

	void Window::maximize() { 
		if (!is_valid()) {
			PF_LOG_WARNING("maximize() called on an uninitialized or destroyed window.");
			return;
		}

		if (!pimpl_->resizable) {
			PF_LOG_DEBUG("Called minimize() on a fixed window; skipping.");
			return;
		}

		if (pimpl_->resizable && pimpl_->maximized) {
			PF_LOG_DEBUG("Called minimize() on a maximized window; skipping.");
			return;
		}

		bool res =  pimpl_->maximize(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to maximize window.");
		}
	}

	void Window::maximize_async() {
		if (!is_valid()) {
			PF_LOG_WARNING("maximize_async() called on an uninitialized or destroyed window.");
			return;
		}

		if (!pimpl_->resizable) {
			PF_LOG_DEBUG("Called minimize() on a fixed window; skipping.");
			return;
		}

		if (pimpl_->resizable && pimpl_->maximized) {
			PF_LOG_DEBUG("Called minimize_async() on a maximized window; skipping.");
			return;
		}

		bool res = pimpl_->maximize_async();

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to maximize window asynchronously.");
		}
	}
	
	void Window::restore() {
		if (!is_valid()) {
			PF_LOG_WARNING("restore() called on an uninitialized or destroyed window.");
			return;
		}

		if (!pimpl_->resizable) {
			PF_LOG_DEBUG("Called restore() on a fixed window; skipping.");
			return;
		}

		bool res = pimpl_->restore();

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to restore window.");
		}
	}
	
	void Window::restore_async() { 
		if (!is_valid()) {
			PF_LOG_WARNING("restore_async() called on an uninitialized or destroyed window.");
			return;
		}

		if (!pimpl_->resizable) {
			PF_LOG_DEBUG("Called restore_async() on a fixed window; skipping.");
			return;
		}

		bool res = pimpl_->restore_async(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to restore window asynchronously.");
		}
	}

	void Window::enable_resizing() { 
		if (!is_valid()) {
			PF_LOG_WARNING("enable_resizing() called on an uninitialized or destroyed window.");
			return;
		}
		bool res = pimpl_->enable_resizing(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to enable window resizing.");
		}
	}

	void Window::disable_resizing() { 
		if (!is_valid()) {
			PF_LOG_WARNING("disable_resizing() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->disable_resizing(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to disable window resizing.");
		}
	}

	void Window::enable_borders() {
		if (!is_valid()) {
			PF_LOG_WARNING("enable_borders() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->enable_borders(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to enable window borders.");
		}
	}

	void Window::disable_borders() { 
		if (!is_valid()) {
			PF_LOG_WARNING("disable_borders() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->disable_borders(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to disable window borders.");
		}
	}

	void Window::enter_fullscreen() { 
		if (!is_valid()) {
			PF_LOG_WARNING("enter_fullscreen() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->enter_fullscreen();

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to enter fullscreen mode.");
		}
	}

	void Window::exit_fullscreen() { 
		if (!is_valid()) {
			PF_LOG_WARNING("exit_fullscreen() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->exit_fullscreen(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to exit fullscreen mode.");
		}
	}

	void Window::grab_mouse() { 
		if (!is_valid()) {
			PF_LOG_WARNING("grab_mouse() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->grab_mouse(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to grab mouse.");
		}
	}

	void Window::release_mouse() { 
		if (!is_valid()) {
			PF_LOG_WARNING("release_mouse() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->release_mouse(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to release mouse.");
		}
	}

	void Window::add_always_on_top() { 
		if (!is_valid()) {
			PF_LOG_WARNING("add_always_on_top() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->add_always_on_top(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to add always on top flag to window.");
		}
	}

	void Window::remove_always_on_top() { 
		if (!is_valid()) {
			PF_LOG_WARNING("remove_always_on_top() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->remove_always_on_top(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to remove always on top flag from window.");
		}
	}

	void Window::gain_focus() { 
		if (!is_valid()) {
			PF_LOG_WARNING("gain_focus() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->gain_focus(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to add focus flag to window.");
		}
	}

	void Window::lose_focus() {
		if (!is_valid()) {
			PF_LOG_WARNING("lose_foucs() called on an uninitialized or destroyed window.");
			return;
		}

		bool res = pimpl_->lose_foucs(); 

		if (!res) {
			// Log the error
			PF_LOG_ERROR("Internal_System_Error: Failed to remove focus flag to window.");
		}
	}

	const char* Window::get_title() { 
		if (!is_valid()) {
			PF_LOG_WARNING("get_title() called on an uninitialized or destroyed window.");
		}

		return pimpl_->title.c_str(); 
	}

	penguin::math::Vector2i Window::get_size() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_size() called on an uninitialized or destroyed window.");
		}

		return pimpl_->size; 
	}

	penguin::math::Vector2i Window::get_max_size() const { 
		if (!is_valid()) {
			PF_LOG_WARNING("get_max_size() called on an uninitialized or destroyed window.");
		}

		return pimpl_->max_size; 
	}

	penguin::math::Vector2i Window::get_min_size() const { 
		if (!is_valid()) {
			PF_LOG_WARNING("get_min_size() called on an uninitialized or destroyed window.");
		}

		return pimpl_->min_size; 
	}

	int Window::get_width() const { 

		if (!is_valid()) {
			PF_LOG_WARNING("get_width() called on an uninitialized or destroyed window.");
		}

		return pimpl_->size.x; 
	}

	int Window::get_height() const { 
		if (!is_valid()) {
			PF_LOG_WARNING("get_height() called on an uninitialized or destroyed window.");
		}

		return pimpl_->size.y; 
	}

	void Window::close() { 
		if (!is_valid()) {
			PF_LOG_WARNING("close() called on an uninitialized or destroyed window.");
		}

		pimpl_->open = false; // the window still exists at this point, but all window operations should not be available anymore

		PF_LOG_DEBUG("Window is now in an INVALID state. Any window operations will fail to run.");
	}

	// Checking for window states

	bool Window::is_resizable() const { 
		return is_valid() && pimpl_->resizable;
	}

	bool Window::is_hidden() const { 
		return is_valid() && pimpl_->hidden;
	}

	bool Window::is_minimized() const { 
		return is_valid() && pimpl_->minimized;
	}

	bool Window::is_maximized() const { 
		return is_valid() && pimpl_->maximized;
	}

	bool Window::is_bordered() const { 
		return is_valid() && pimpl_->bordered;
	}

	bool Window::is_fullscreen() const { 
		return is_valid() && pimpl_->fullscreen;
	}

	bool Window::is_mouse_grabbed() const { 
		return is_valid() && pimpl_->mouse_grabbed;
	}

	bool Window::is_always_on_top() const { 
		return is_valid() && pimpl_->always_on_top;
	}

	bool Window::is_focused() const { 
		return is_valid() && pimpl_->focused;
	}

	bool Window::is_open() const { 
		return is_valid(); // always checks that the window is open
	}

	NativeWindowPtr Window::get_native_ptr() const { 
		if (!is_valid()) {
			PF_LOG_WARNING("get_native_ptr() called on an uninitialized or destroyed window.");
			return NativeWindowPtr{ nullptr }; // indicates that the underlying native pointer cannot be accessed
		}

		return NativeWindowPtr{ pimpl_->window.get() }; 
	}
}