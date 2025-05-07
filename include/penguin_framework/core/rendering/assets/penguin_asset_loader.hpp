#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/core/rendering/assets/penguin_texture.hpp>

#include <memory>

namespace penguin::core::rendering::assets {

	class PENGUIN_API AssetLoader {
	public:
		AssetLoader(NativeRendererPtr renderer_ptr); // add text_renderer later

		// Move constructor & assignment destructors (copy constructor / assignment not allowed)

		AssetLoader(const AssetLoader&) = delete;
		AssetLoader& operator=(const AssetLoader&) = delete;
		AssetLoader(AssetLoader&&) noexcept = default;
		AssetLoader& operator=(AssetLoader&&) noexcept = default;

		// Various load functions

		Texture load(const char* path);

	private:
		// Forward declaration
		struct AssetLoaderImpl;
		
		std::unique_ptr<AssetLoaderImpl> pimpl_;
	};
}