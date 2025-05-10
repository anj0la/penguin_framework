#pragma once

#include <penguin_framework/core/common/native_types.hpp>

#include <penguin_framework/core/rendering/primitives/penguin_texture.hpp>
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

namespace penguin::core::rendering::systems {

	struct TextureLoader::TextureLoaderImpl {

		std::unordered_map<String, std::shared_ptr<primitives::Texture>> texture_cache;

		TextureLoaderImpl() = default;

		// Copy & move (including assigment) not allowed

		TextureLoaderImpl(const TextureLoaderImpl&) = delete;
		TextureLoaderImpl& operator=(const TextureLoaderImpl&) = delete;
		TextureLoaderImpl(TextureLoaderImpl&&) noexcept = delete;
		TextureLoaderImpl& operator=(TextureLoaderImpl&&) noexcept = delete;

		// Load functions
		std::shared_ptr<primitives::Texture> load(NativeRendererPtr renderer, const char* path);
	};
}