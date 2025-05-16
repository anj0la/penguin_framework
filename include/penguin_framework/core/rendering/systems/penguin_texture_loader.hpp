#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/core/common/native_types.hpp>
#include <penguin_framework/core/rendering/primitives/penguin_texture.hpp>

#include <memory>

namespace penguin::core::rendering::systems {

	// Forward declaration
	struct TextureLoaderImpl;

	class PENGUIN_API TextureLoader {
	public:
		TextureLoader();
		~TextureLoader();

		// Deleting move semantics

		TextureLoader(const TextureLoader&) = delete;
		TextureLoader& operator=(const TextureLoader&) = delete;

		// Load functions
		std::shared_ptr<primitives::Texture> load(NativeRendererPtr renderer, const char* path);
	private:
		std::unique_ptr<TextureLoaderImpl> pimpl_;
	};
}