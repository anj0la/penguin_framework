#include <rendering/primitives/internal/sprite_impl.hpp>

namespace penguin::internal::rendering::primitives {

	SpriteImpl::SpriteImpl(std::shared_ptr<penguin::rendering::primitives::Texture> p_texture) : texture(std::move(p_texture)) {
		
		penguin::internal::error::InternalError::throw_if(
			!texture,
			"Failed to load the texture.",
			penguin::internal::error::ErrorCode::Resource_Load_Failed
		);

		position = penguin::math::Vector2::Zero; // the top-left corner represents the position of the Sprite
		size = texture->get_size();
		texture_region = penguin::math::Rect2{ position.x, position.y, static_cast<float>(size.x), static_cast<float>(size.y) }; // position -> (0,0), size -> (texture_width, texture_height) for the full texture
		screen_placement = penguin::math::Rect2{ position.x, position.y, static_cast<float>(size.x), static_cast<float>(size.y) };
		scale_factor = penguin::math::Vector2::One;
		angle = 0.0;
		anchor = penguin::math::Vector2{ 0.5f, 0.5f }; // center
		visible = true;
		mode = penguin::rendering::primitives::FlipMode::None;
		tint = Colours::NoTint;
		bounding_box = penguin::math::Rect2{ position.x, position.y, static_cast<float>(size.x), static_cast<float>(size.y) }; // initally the size of the texture
	}

	// Getters

	NativeTexturePtr SpriteImpl::get_native_ptr() const {
		return texture->get_native_ptr();
	}

	// Other functions

	bool SpriteImpl::update_screen_placement() {
		// Texture is invalid, nothing should be rendered onto the screen
		if (!texture) {
			screen_placement = penguin::math::Rect2{ penguin::math::Vector2::Zero, penguin::math::Vector2::Zero };
			return false;
		}

		// Otherwise, we update the screen placement with the position and scale_factor
		penguin::math::Vector2 base_size{ texture_region.size.x, texture_region.size.y };

		// Texture is valid, but the source portion defines a zero-area
		if (base_size.x <= 0 || base_size.y <= 0) { // same as base_size <= Vector2::Zero, but more readable
			screen_placement = penguin::math::Rect2{ penguin::math::Vector2::Zero, penguin::math::Vector2::Zero };
			return false;
		}

		// Texture is valid, and the source portion defines a valid non-zero area
		penguin::math::Vector2 final_size = base_size * scale_factor;
		penguin::math::Vector2 pixel_anchor = anchor * final_size;
		penguin::math::Vector2 final_position = position - pixel_anchor;

		screen_placement = penguin::math::Rect2{ final_position, final_size };

		return true; // successfuly updated screen placement
	}

	bool SpriteImpl::set_colour_tint(const penguin::math::Colour& new_tint) {
		tint = new_tint;
		SDL_Texture* texture = get_native_ptr().as<SDL_Texture>();

		return SDL_SetTextureColorModFloat(texture, tint.r, tint.g, tint.b) && SDL_SetTextureAlphaModFloat(texture, tint.a);
	}

	bool SpriteImpl::clear_colour_tint() {
		tint = Colours::NoTint;
		SDL_Texture* texture = get_native_ptr().as<SDL_Texture>();

		return SDL_SetTextureColorModFloat(texture, tint.r, tint.g, tint.b) && SDL_SetTextureAlphaModFloat(texture, tint.a);
	}
}