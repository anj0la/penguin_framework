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
		float angle;
		Vector2 anchor_point;
		bool visible;
		FlipMode mode;
		Rect2 bounding_box; // to handle collisions between two sprites (NOTE: Update to BoundingShape struct to store other types of shapes, like Circle2, Polygon2, etc., after adding intersection functions)

		// Constructor
		SpriteImpl(std::shared_ptr<Texture> tex);

		// Copy and move constructors

		SpriteImpl(const SpriteImpl&) = default;
		SpriteImpl& operator=(const SpriteImpl&) = default;
		SpriteImpl(SpriteImpl&&) noexcept = default;
		SpriteImpl& operator=(SpriteImpl&&) noexcept = default;

		// Getters

		NativeTexturePtr get_native_ptr() const;
		Vector2 get_position() const;
		Vector2i get_size() const;
		float get_angle() const;
		Vector2 get_anchor_point() const;
		bool is_hidden() const;
		FlipMode get_flip_mode() const;
		Rect2 get_bounding_box() const;

		// Setters

		void set_texture(std::shared_ptr<Texture> tex);
		void set_position(Vector2 new_pos);
		void set_angle(float new_angle);
		void set_anchor_point(Vector2 new_anchor_point);
		void show();
		void hide();
		void set_flip_mode(FlipMode new_mode);
		void set_bounding_box(Rect2 bound_box);
	};
}