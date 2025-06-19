#pragma once

#include <penguin_framework/common/native_types.hpp>

#include <error/internal/internal_error.hpp>
#include <penguin_framework/math/rect2.hpp>
#include <penguin_framework/math/circle2.hpp>
#include <penguin_framework/math/colours.hpp>
#include <penguin_framework/math/vector2i.hpp>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>

#include <memory>
#include <vector>

namespace penguin::internal::rendering::primitives {

	struct TextureImpl {

		std::unique_ptr <SDL_Texture, void(*)(SDL_Texture*)> texture;
		penguin::math::Vector2i size;

		// Constructor
		TextureImpl(NativeRendererPtr ptr, const char* path);

		TextureImpl(const TextureImpl&) = delete;
		TextureImpl& operator=(const TextureImpl&) = delete;
		TextureImpl(TextureImpl&&) noexcept = default;
		TextureImpl& operator=(TextureImpl&&) noexcept = default;
	};

}