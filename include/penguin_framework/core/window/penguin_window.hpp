#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/core/window/penguin_windowflags.hpp>
#include <penguin_framework/core/math/vector2i.hpp>
#include <penguin_framework/utils/string.hpp>

#include <memory>

// Forward declaration of GraphicsSystem
namespace penguin::core::system {
	class GraphicsSystem;
}

namespace penguin::core::window {

	class PENGUIN_API Window {
	public:
		Window(const char* p_title = "", Vector2i p_size = Vector2i(640, 480), WindowFlags p_flags = WindowFlags::None);
		Window(const char* p_title = "", int width = 640, int height = 480, WindowFlags p_flags = WindowFlags::None) : Window(p_title, Vector2i(width, height), p_flags) {}
		~Window();

		// Move constructor & assignment destructors (copy constructor / assignment not allowed)

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) noexcept;         
		Window& operator=(Window&&) noexcept;

		// Functions to change window title / sizes

		void set_title(const char* new_title);
		void set_max_size(Vector2i p_max_size);
		void set_min_size(Vector2i p_min_size);
		void resize(Vector2i new_size);

		// Functions to change window visibility

		void show();
		void hide();
		void minimize();
		void maximize();
		void restore(); // used to restore a minimized / maximized window. Has no effect on a fullscreen window.
		void restore_async();

		// Functions to toggle window states

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

		void add_always_on_top();
		void remove_always_on_top();

		void gain_focus();
		void lose_foucs();

		// Functions to get window title / sizes

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

	private:
		// Forward declaration
		struct WindowImpl;

		// Gives access to internal implementation (needed to create renderer)
		friend class GraphicsSystem;

		std::unique_ptr<WindowImpl> pimpl_;
	};
}