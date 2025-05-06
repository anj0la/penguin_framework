#pragma once

#include <penguin_framework/utils/exception.hpp>
#include <penguin_framework/core/math/rect2.hpp>
#include <penguin_framework/core/math/circle2.hpp>
#include <penguin_framework/core/math/colours.hpp>
#include <penguin_framework/core/math/vector2i.hpp>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>

#include <memory>
#include <vector>

namespace penguin::core::rendering::assets {

	struct Texture::TextureImpl {

		std::unique_ptr <SDL_Texture, void(*)(SDL_Texture*)> img;
		Vector2i size;

		// Constructor
		TextureImpl(std::unique_ptr <SDL_Texture, void(*)(SDL_Texture*)> image, const char* filepath);

		TextureImpl(const TextureImpl&) = delete;
		TextureImpl& operator=(const TextureImpl&) = delete;
		TextureImpl(TextureImpl&&) noexcept = default;
		TextureImpl& operator=(TextureImpl&&) noexcept = default;
	};

}