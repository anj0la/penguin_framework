#pragma once

#include <penguin_framework/penguin_api.hpp>
#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/primitives/flip_modes.hpp>

#include <penguin_framework/rendering/primitives/penguin_texture.hpp>

#include <memory>

namespace penguin::internal::rendering::primitives {
	class SpriteImpl;
}

namespace penguin::rendering::primitives {

	class PENGUIN_API Sprite {
	public:
		Sprite(std::shared_ptr<Texture> p_texture);
		~Sprite();

		Sprite(Sprite&&) noexcept;
		Sprite& operator=(Sprite&&) noexcept;

		// Validity checking

		[[nodiscard]] bool is_valid() const noexcept;
		[[nodiscard]] explicit operator bool() const noexcept;

		NativeTexturePtr get_native_ptr() const;
		penguin::math::Vector2 get_position() const;
		penguin::math::Vector2i get_size() const;
		penguin::math::Vector2 get_scale() const;
		double get_angle() const;
		penguin::math::Vector2 get_anchor_point() const;
		bool is_hidden() const;
		FlipMode get_flip_mode() const;
		penguin::math::Colour get_colour_tint() const;
		penguin::math::Rect2 get_bounding_box() const;

		void set_texture(std::shared_ptr<Texture> texture);
		void set_position(const penguin::math::Vector2& new_position);
		void set_position(float x, float y);
		void set_scale(penguin::math::Vector2 new_scale);
		void set_scale(float x, float y);
		void set_angle(double new_angle);
		void set_anchor_point(const penguin::math::Vector2& new_center);
		void set_anchor_point(float x, float y);
		void show();
		void hide();
		void set_flip_mode(FlipMode new_mode);
		void set_colour_tint(const penguin::math::Colour& new_tint);
		void set_bounding_box(const penguin::math::Rect2& new_bounding_box);
	
		bool is_anchor_point_set() const;
		bool clear_anchor_point() const;

		bool intersects(const Sprite& other) const;

	private:
		std::unique_ptr<penguin::internal::rendering::primitives::SpriteImpl> pimpl_;
		bool valid_state_;

	};


}