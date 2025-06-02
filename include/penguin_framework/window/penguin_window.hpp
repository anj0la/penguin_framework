#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/window/penguin_windowflags.hpp>
#include <penguin_framework/math/Vector2i.hpp>

#include <memory>

namespace penguin::internal::window {
	// Forward declaration
	class WindowImpl;
}

namespace penguin::window {

	class PENGUIN_API Window {
	public:
		Window(const char* p_title = "", penguin::math::Vector2i p_size = penguin::math::Vector2i(640, 480), WindowFlags p_flags = WindowFlags::None);
		~Window();

		// Move semantics

		Window(const Window&) = default;
		Window& operator=(const Window&) = default;

		// Validity checking

		[[nodiscard]] bool is_valid() const noexcept;
		[[nodiscard]] explicit operator bool() const noexcept;

		// Functions to change window title / sizes

		void set_title(const char* new_title);
		void set_max_size(penguin::math::Vector2i p_max_size);
		void set_min_size(penguin::math::Vector2i p_min_size);
		void resize(penguin::math::Vector2i new_size);

		// Functions to change window visibility

		void show();
		void hide();
		void minimize();
		void minimize_async();
		void maximize();
		void maximize_async();
		void restore(); // used to restore a minimized / maximized window. Has no effect on a fullscreen window.
		void restore_async();

		// Functions to toggle window states

		void enable_resizing();
		void disable_resizing();

		void enable_borders();
		void disable_borders();

		void enter_fullscreen();
		void exit_fullscreen();

		void grab_mouse();
		void release_mouse();

		void add_always_on_top();
		void remove_always_on_top();

		void gain_focus();
		void lose_foucs();

		// Functions to get window title / size

		const char* get_title();
		penguin::math::Vector2i get_size() const;
		penguin::math::Vector2i get_max_size() const;
		penguin::math::Vector2i get_min_size() const;

		int get_width() const;
		int get_height() const;

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

		NativeWindowPtr get_native_ptr() const;

	private:
		std::unique_ptr<penguin::internal::window::WindowImpl> pimpl_;
		bool valid_state_;

		// Private constructor
		explicit Window(std::unique_ptr<penguin::internal::window::WindowImpl> impl) noexcept;
	};
}