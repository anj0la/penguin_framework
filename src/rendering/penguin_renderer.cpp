#include <penguin_framework/rendering/penguin_renderer.hpp>
#include <rendering/internal/penguin_renderer_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::rendering {

	Renderer::Renderer(NativeWindowPtr window_ptr, const char* driver_name) : pimpl_(nullptr) {
		std::string message = "Attempting to create renderer with driver: (" + std::string(driver_name) +  ")...";
		PF_LOG_INFO(message.c_str());

		try {
			pimpl_ = std::make_unique<penguin::internal::rendering::RendererImpl>(window_ptr, driver_name);
				PF_LOG_INFO("Success: Renderer created successfully.");

		} catch (const penguin::internal::error::InternalError& e) {
				// Get the error code and message
				std::string error_code_str = penguin::internal::error::error_code_to_string(e.get_error());
				std::string error_message = error_code_str + ": " + e.what();

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

	Renderer::~Renderer() = default;

	bool Renderer::is_valid() const noexcept {
		if (!pimpl_) {
			return false;
		}

		return pimpl_->renderer.get() != nullptr;
	}

	Renderer::operator bool() const noexcept {
		return is_valid();
	}

	// Displaying / clearing the renderer

	void Renderer::display() { 
		if (!is_valid()) {
			PF_LOG_WARNING("display() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->display(); 

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to display renderer.");
		}
	}

	void Renderer::clear() { 
		if (!is_valid()) {
			PF_LOG_WARNING("display() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->clear(); 

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to clear renderer.");
		}
	}

	// Drawing functions

	void Renderer::draw_line(penguin::math::Vector2 vec1, penguin::math::Vector2 vec2, penguin::math::Colour colour) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_line() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_line(vec1, vec2, colour);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw line to renderer.");
		}

	}

	void Renderer::draw_pixel(penguin::math::Vector2 vec, penguin::math::Colour colour) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_pixel() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_pixel(vec, colour);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw pixel to renderer.");
		}
	}

	void Renderer::draw_rect(penguin::math::Rect2 rect, penguin::math::Colour outline) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_rect() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_rect(rect, outline);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw rect to renderer.");
		}
	}

	void Renderer::draw_filled_rect(penguin::math::Rect2 rect, penguin::math::Colour fill) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_filled_rect() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_filled_rect(rect, fill);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw filled rect to renderer.");
		}
	}
	void Renderer::draw_triangle(penguin::math::Vector2 vec1, penguin::math::Vector2 vec2, penguin::math::Vector2 vec3, penguin::math::Colour outline) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_triangle() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_triangle(vec1, vec2, vec3, outline);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw triangle to renderer.");
		}
	}

	void Renderer::draw_filled_triangle(penguin::math::Vector2 vec1, penguin::math::Vector2 vec2, penguin::math::Vector2 vec3, penguin::math::Colour fill) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_filled_triangle() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_filled_triangle(vec1, vec2, vec3, fill);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw filled triangle to renderer.");
		}
	}

	void Renderer::draw_circle(penguin::math::Circle2 circle, penguin::math::Colour outline) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_circle() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_circle(circle.center, circle.radius, outline);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw circle to renderer.");
		}
	}

	void Renderer::draw_circle(penguin::math::Vector2 center, int radius, penguin::math::Colour outline) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_circle() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_circle(center, radius, outline);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw circle to renderer.");
		}
	}

	void Renderer::draw_filled_circle(penguin::math::Circle2 circle, penguin::math::Colour fill) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_filled_circle() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_filled_circle(circle.center, circle.radius, fill);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw filled circle to renderer.");
		}
	}

	void Renderer::draw_filled_circle(penguin::math::Vector2 center, int radius, penguin::math::Colour fill) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_filled_circle() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_filled_circle(center, radius, fill);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw filled circle to renderer.");
		}
	}

	void Renderer::draw_ellipse(penguin::math::Vector2 center, int radius_x, int radius_y, penguin::math::Colour outline) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_ellipse() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_ellipse(center, radius_x, radius_y, outline);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw ellipse to renderer.");
		}
	}

	void Renderer::draw_filled_ellipse(penguin::math::Vector2 center, int radius_x, int radius_y, penguin::math::Colour fill) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_filled_ellipse() called on an uninitialized or destroyed renderer.");
			return;
		}

		bool res = pimpl_->draw_filled_ellipse(center, radius_x, radius_y, fill);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to draw filled ellipse to renderer.");
		}
	}

	// Drawing functions for Sprites

	void Renderer::draw_sprite(penguin::rendering::primitives::Sprite& spr) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_sprite() called on an uninitialized or destroyed renderer.");
			return;
		}

		// Render sprite onto the screen if it is NOT hidden (i.e., visible)
		if (!spr.is_hidden()) {
			bool res = pimpl_->draw_sprite(spr.get_native_ptr(), spr.get_texture_region(), spr.get_screen_placement());

			if (!res) {
				PF_LOG_WARNING("Internal_System_Error: Failed to draw sprite to renderer.");
			}
		}
	}

	void Renderer::draw_sprite_transformed(penguin::rendering::primitives::Sprite spr) {
		if (!is_valid()) {
			PF_LOG_WARNING("draw_sprite_transformed() called on an uninitialized or destroyed renderer.");
			return;
		}

		// The sprite isn't renderered onto the screen if it is hidden
		if (!spr.is_hidden()) {
			bool res = pimpl_->draw_sprite_transformed(spr.get_native_ptr(), spr.get_texture_region(), spr.get_screen_placement(),
				spr.get_scale_factor(), spr.get_anchor(), spr.get_angle(), spr.get_flip_mode());

			if (!res) {
				PF_LOG_WARNING("Internal_System_Error: Failed to draw transformed sprite to renderer.");
			}
		}
	}

	NativeRendererPtr Renderer::get_native_ptr() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_native_ptr() called on an uninitialized or destroyed renderer.");
			return NativeRendererPtr{ nullptr }; // indicates that the underlying native pointer cannot be accessed
		}
		return NativeRendererPtr{ pimpl_->renderer.get() };
	}
}

