#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/core/rendering/primitives/penguin_texture.hpp>

#include <memory>

namespace penguin::core::rendering::systems {

	class PENGUIN_API AssetManager {
	public:
		AssetManager(NativeRendererPtr renderer_ptr); // add text_renderer later
		~AssetManager();

		// Move constructor & assignment destructors (copy constructor / assignment not allowed)

		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;
		AssetManager(AssetManager&&) noexcept = default;
		AssetManager& operator=(AssetManager&&) noexcept = default;

		// Various load functions
		std::shared_ptr<primitives::Texture> load(const char* path);

	private:
		// Forward declaration
		struct AssetManagerImpl;

		std::unique_ptr<AssetManagerImpl> pimpl_;
	};
}