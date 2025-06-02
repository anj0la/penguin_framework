#pragma once

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/primitives/penguin_texture.hpp>
#include <penguin_framework/rendering/primitives/flip_modes.hpp>

#include <penguin_framework/math/rect2.hpp>
#include <penguin_framework/math/colours.hpp>
#include <penguin_framework/math/vector2.hpp>
#include <penguin_framework/math/vector2i.hpp>

#include <error/internal/internal_error.hpp>

#include <memory>
#include <vector>
#include <algorithm>

namespace penguin::internal::rendering::primitives {

	class SpriteImpl {
	public:
		std::shared_ptr<penguin::rendering::primitives::Texture> texture;
		penguin::math::Vector2 position;
		penguin::math::Vector2i size;
		penguin::math::Rect2 texture_region;
		penguin::math::Rect2 screen_placement;
		penguin::math::Vector2 scale_factor;
		double angle;
		penguin::math::Vector2 anchor;
		bool visible;
		penguin::rendering::primitives::FlipMode mode;
		penguin::math::Colour tint;
		penguin::math::Rect2 bounding_box; // to handle collisions between two sprites (NOTE: Update to BoundingShape struct to store other types of shapes, like Circle2, Polygon2, etc., after adding intersection functions)

		// Constructor
		SpriteImpl(std::shared_ptr<penguin::rendering::primitives::Texture> p_texture);

		// Copy and move constructors

		SpriteImpl(const SpriteImpl&) = default;
		SpriteImpl& operator=(const SpriteImpl&) = default;
		SpriteImpl(SpriteImpl&&) noexcept = default;
		SpriteImpl& operator=(SpriteImpl&&) noexcept = default;

		// Getters

		NativeTexturePtr get_native_ptr() const;

		// Other functions

		bool update_screen_placement();
	};
}