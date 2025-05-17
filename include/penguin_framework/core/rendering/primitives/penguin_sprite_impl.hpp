#pragma once

#include <penguin_framework/core/common/native_types.hpp>
#include <penguin_framework/core/rendering/primitives/penguin_texture.hpp>

#include <penguin_framework/core/math/rect2.hpp>
#include <penguin_framework/core/math/circle2.hpp>
#include <penguin_framework/core/math/colours.hpp>
#include <penguin_framework/core/math/vector2.hpp>
#include <penguin_framework/core/math/vector2i.hpp>

#include <penguin_framework/utils/exception.hpp>

#include <memory>
#include <vector>

namespace penguin::core::rendering::primitives {

	struct SpriteImpl {
		std::shared_ptr<Texture> texture;
		Vector2 position;
		Vector2i size;
		Vector2 scale;
		float angle;
		Vector2 anchor_point;
		bool visible;
		FlipMode mode;
		Colour tint;
		Rect2 bounding_box; // to handle collisions between two sprites (NOTE: Update to BoundingShape struct to store other types of shapes, like Circle2, Polygon2, etc., after adding intersection functions)

		// Constructor
		SpriteImpl(std::shared_ptr<Texture> p_texture, Vector2 p_position = Vector2(0.0f,0.0f), Vector2 p_scale = Vector2(1.0f, 1.0f),
			Vector2 p_anchor_point = Vector2(0.0f, 0.0f), float p_angle = 0.0f, bool p_visible = true, FlipMode p_mode = FlipMode::None, Colour p_modulate = Colours::Transparent);

		// Copy and move constructors

		SpriteImpl(const SpriteImpl&) = default;
		SpriteImpl& operator=(const SpriteImpl&) = default;
		SpriteImpl(SpriteImpl&&) noexcept = default;
		SpriteImpl& operator=(SpriteImpl&&) noexcept = default;

		// Getters

		NativeTexturePtr get_native_ptr() const;
		Vector2 get_position() const;
		Vector2i get_size() const;
		Vector2 get_scale() const;
		float get_angle() const;
		Vector2 get_anchor_point() const;
		bool is_hidden() const;
		FlipMode get_flip_mode() const;
		Colour get_colour_tint() const;
		Rect2 get_bounding_box() const;

		// Setters

		void set_texture(std::shared_ptr<Texture> new_texture);
		void set_position(Vector2 new_position);
		void set_scale(Vector2 new_scale);
		void set_angle(float new_angle);
		void set_anchor_point(Vector2 new_anchor_point);
		void show();
		void hide();
		void set_flip_mode(FlipMode new_mode);
		void set_colour_tint(Colour new_tint);
		void set_bounding_box(Rect2 new_bounding_box);
	};
}