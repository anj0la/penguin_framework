#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/core/window/penguin_windowflags.hpp>
#include <penguin_framework/core/math/vector2i.hpp>
#include <penguin_framework/utils/string.hpp>

#include <memory>

using NativeWindowPtr = void*;

namespace penguin::core::window {

	class PENGUIN_API Window {
	public:
		Window(const char* p_title = "", Vector2i p_size = Vector2i(640, 480), WindowFlags p_flags = WindowFlags::None);
		~Window();

		// Move constructor & assignment destructors (copy constructor / assignment not allowed)

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) noexcept = default;         
		Window& operator=(Window&&) noexcept = default;

		// Functions to change window title / sizes

		bool set_title(const char* new_title);
		bool set_max_size(Vector2i p_max_size);
		bool set_min_size(Vector2i p_min_size);
		bool resize(Vector2i new_size);

		// Functions to change window visibility

		bool show();
		bool hide();
		bool minimize();
		bool maximize();
		bool restore(); // used to restore a minimized / maximized window. Has no effect on a fullscreen window.
		bool restore_async();

		// Functions to toggle window states

		bool enable_resizing();
		bool disable_resizing();

		bool enable_borders();
		bool disable_borders();

		bool enter_fullscreen();
		bool exit_fullscreen();

		bool enable_vsync();
		bool disable_vsync();

		bool grab_mouse();
		bool release_mouse();

		bool add_always_on_top();
		bool remove_always_on_top();

		bool gain_focus();
		bool lose_foucs();

		// Functions to get window title / size

		const char* get_title();
		Vector2i get_window_size() const;
		Vector2i get_max_window_size() const;
		Vector2i get_min_window_size() const;

		int get_window_width();
		int get_window_height();

		// Function to close window

		void close();

		// Functions to check window states

		bool is_resizable() const;
		bool is_hidden() const;
		bool is_minimized() const;
		bool is_maximized() const;
		bool is_bordered() const;
		bool is_fullscreen() const;
		bool is_vsync_enabled() const;
		bool is_mouse_grabbed() const;
		bool is_always_on_top() const;
		bool is_focused() const;
		bool is_open() const;

		// Access to internal window pointer 
		// NOTE: This is needed to create the renderer and other objects.
		// It will be deleted once I have figured out how to connect the window, renderer and other objects.
		NativeWindowPtr get_native_ptr() const;

	private:
		// Forward declaration
		struct WindowImpl;

		std::unique_ptr<WindowImpl> pimpl_;
	};
}