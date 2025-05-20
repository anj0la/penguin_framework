#pragma once

#include <penguin_framework/penguin_api.hpp>
#include <penguin_framework/core/common/native_types.hpp>

#include <penguin_framework/core/rendering/primitives/penguin_texture.hpp>

#include <memory>

namespace penguin::core::rendering::primitives {

	struct SpriteImpl;

	enum class FlipMode : int {
		None = 0,
		Horizontal = 1,
		Vertical = 2
	};

	class PENGUIN_API Sprite {
	public:
		Sprite(std::shared_ptr<Texture> tex, Vector2 position = Vector2(0.0f, 0.0f), Vector2 scale = Vector2(1.0f, 1.0f),
			double angle = 0.0, Vector2 p_anchor_point = Vector2(0.5f, 0.5f), bool visible = true, FlipMode mode = FlipMode::None, Colour modulate = Colours::NoTint);
		~Sprite();

		Sprite(Sprite&&) noexcept;
		Sprite& operator=(Sprite&&) noexcept;

		NativeTexturePtr get_native_ptr() const;
		Vector2 get_position() const;
		Vector2i get_size() const;
		Vector2 get_scale() const;
		double get_angle() const;
		Vector2 get_anchor_point() const;
		bool is_hidden() const;
		FlipMode get_flip_mode() const;
		Colour get_colour_tint() const;
		Rect2 get_bounding_box() const;

		void set_texture(std::shared_ptr<Texture> texture);
		void set_position(Vector2 new_position);
		void set_position(float x, float y);
		void set_scale(Vector2 new_scale);
		void set_scale(float x, float y);
		void set_angle(double new_angle);
		void set_anchor_point(Vector2 new_center);
		void set_anchor_point(float x, float y);
		void show();
		void hide();
		void set_flip_mode(FlipMode new_mode);
		void set_colour_tint(Colour new_tint);
		void set_bounding_box(Rect2 new_bounding_bix);

		bool intersects(const Sprite& other) const;

	private:
		std::unique_ptr<SpriteImpl> pimpl_;

	};


}