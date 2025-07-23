#pragma once

#include <penguin_api.hpp>
#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/primitives/flip_modes.hpp>

#include <penguin_framework/rendering/primitives/texture.hpp>

#include <memory>

namespace penguin::internal::rendering::drawables {
	class SpriteImpl;
}

namespace penguin::rendering::drawables {

	class PENGUIN_API Sprite {
	public:
		Sprite(std::shared_ptr<primitives::Texture> p_texture);
		~Sprite();

		Sprite(Sprite&&) noexcept;
		Sprite& operator=(Sprite&&) noexcept;

		// Validity checking

		[[nodiscard]] bool is_valid() const noexcept;
		[[nodiscard]] explicit operator bool() const noexcept;

		penguin::math::Vector2 get_position() const;
		penguin::math::Vector2i get_size() const;
		int get_width() const;
		int get_height() const;
		penguin::math::Rect2 get_texture_region() const;
		penguin::math::Rect2 get_screen_placement() const;
		penguin::math::Vector2 get_scale_factor() const;
		double get_angle() const;
		penguin::math::Vector2 get_anchor() const;
		bool is_hidden() const;
		penguin::math::Colour get_colour_tint() const;
		primitives::FlipMode get_flip_mode() const;
		penguin::math::Rect2 get_bounding_box() const;

		void set_texture(std::shared_ptr<primitives::Texture> new_texture);
		void set_position(const penguin::math::Vector2& new_position);
		void set_position(float x, float y);
		void set_texture_region(const penguin::math::Rect2& new_region);
		void set_screen_placement(const penguin::math::Rect2& new_placement);
		void set_scale_factor(const penguin::math::Vector2& new_scale_factor);
		void set_scale_factor(float x, float y);
		void set_angle(double new_angle);
		void set_anchor(const penguin::math::Vector2& new_anchor);
		void set_anchor(float x, float y);
		void show();
		void hide();
		void set_flip_mode(primitives::FlipMode new_mode);
		void set_colour_tint(const penguin::math::Colour& new_tint);
		void set_bounding_box(const penguin::math::Rect2& new_bounding_box);

		bool intersects(const Sprite& other) const;
		void clear_colour_tint();
		bool has_texture() const;
		void use_full_region();
		void use_default_screen_placement();

		NativeTexturePtr get_native_ptr() const;

	private:
		std::unique_ptr<penguin::internal::rendering::drawables::SpriteImpl> pimpl_;
	};


}