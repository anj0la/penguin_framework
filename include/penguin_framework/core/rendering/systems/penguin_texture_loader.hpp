#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/core/common/native_types.hpp>

#include <penguin_framework/core/rendering/primitives/penguin_texture.hpp>

#include <memory>

namespace penguin::core::rendering::systems {

	class PENGUIN_API TextureLoader {
	public:
		TextureLoader();
		~TextureLoader();

		// Copy & move (including assigment) not allowed

		TextureLoader(const TextureLoader&) = delete;
		TextureLoader& operator=(const TextureLoader&) = delete;
		TextureLoader(TextureLoader&&) noexcept = delete;
		TextureLoader& operator=(TextureLoader&&) noexcept = delete;

		// Load functions
		std::shared_ptr<primitives::Texture> load(NativeRendererPtr renderer, const char* path);
	private:
		// Forward declaration
		struct TextureLoaderImpl;

		std::unique_ptr<TextureLoaderImpl> pimpl_;
	};
}