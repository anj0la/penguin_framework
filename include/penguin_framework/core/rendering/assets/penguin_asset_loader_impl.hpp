#pragma once

#include <penguin_framework/core/rendering/penguin_renderer.hpp>
#include <penguin_framework/core/rendering/assets/penguin_texture.hpp>
#include <penguin_framework/utils/exception.hpp>
#include <penguin_framework/utils/string.hpp>
#include <penguin_framework/core/math/rect2.hpp>
#include <penguin_framework/core/math/circle2.hpp>
#include <penguin_framework/core/math/colours.hpp>
#include <penguin_framework/core/math/vector2i.hpp>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>

#include <memory>
#include <vector>
#include <unordered_map>

namespace penguin::core::rendering::assets {

	struct AssetLoader::AssetLoaderImpl {
	public:
		AssetLoaderImpl(rendering::Renderer& renderer); // add text_renderer later

		// Move constructor & assignment destructors (copy constructor / assignment not allowed)
		
		AssetLoaderImpl(const AssetLoaderImpl&) = delete;
		AssetLoaderImpl& operator=(const AssetLoaderImpl&) = delete;
		AssetLoaderImpl(AssetLoaderImpl&&) noexcept = default;
		AssetLoaderImpl& operator=(AssetLoaderImpl&&) noexcept = default;

		// Various load functions

		// MOVE THE UNIQUE PTR FROM ASSETLOADER TO TEXTURE
		Texture load(const char* path); // loads a texture that will be associated with a Sprite

		// Texture img = content.load('player.png');
		// Sprite player(img);
		
		// Font load(const char* path, int font_size);
		// Text load(Font& font, const char* str, Vector2 position, Colour colour);

		// text_renderer -> LATER
		// image_cache
		// font_cache -> LATER

	private:
		rendering::Renderer renderer;
		std::unordered_map<String, Texture> texture_cache;
	};
}