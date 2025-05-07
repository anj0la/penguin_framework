#pragma once

#include <penguin_framework/core/common/native_types.hpp>

#include <penguin_framework/core/rendering/assets/penguin_texture.hpp>
#include <penguin_framework/utils/exception.hpp>
#include <penguin_framework/utils/string.hpp>
#include <penguin_framework/core/math/rect2.hpp>
#include <penguin_framework/core/math/circle2.hpp>
#include <penguin_framework/core/math/colours.hpp>
#include <penguin_framework/core/math/vector2i.hpp>

#include <SDL3/SDL_render.h>

#include <memory>
#include <vector>
#include <unordered_map>

namespace penguin::core::rendering::assets {

	struct AssetLoader::AssetLoaderImpl {
	public:
		AssetLoaderImpl(NativeRendererPtr renderer); // add text_renderer later

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

	private:

		// AssetLoader MUST NOT outlive Renderer
		// Created by the framework and managed:
		//
		// Renderer renderer;
		// AssetLoader content(renderer.get_native_ptr());
		//
		// Then when the destructor is called, the AssetLoader is destroyed FIRST before the renderer

		NativeRendererPtr ptr;
		std::unordered_map<String, Texture> texture_cache; // need to figure out how to handle caching
	};
}