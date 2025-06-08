#pragma once

#include <penguin_framework/common/native_types.hpp>

#include <penguin_framework/rendering/primitives/penguin_texture.hpp>
#include <error/internal/internal_error.hpp>

#include <SDL3/SDL_render.h>

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

namespace penguin::internal::rendering::systems {

	struct TextureLoaderImpl {

		std::unordered_map<std::string, std::shared_ptr<penguin::rendering::primitives::Texture>> texture_cache;

		TextureLoaderImpl() = default;

		// Copy & move (including assigment) not allowed

		TextureLoaderImpl(const TextureLoaderImpl&) = delete;
		TextureLoaderImpl& operator=(const TextureLoaderImpl&) = delete;
		TextureLoaderImpl(TextureLoaderImpl&&) noexcept = delete;
		TextureLoaderImpl& operator=(TextureLoaderImpl&&) noexcept = delete;

		// Load functions
		std::shared_ptr<penguin::rendering::primitives::Texture> load(NativeRendererPtr renderer, const char* path);
	};
}