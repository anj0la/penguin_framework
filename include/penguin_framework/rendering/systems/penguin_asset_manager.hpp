#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/rendering/primitives/penguin_texture.hpp>

#include <memory>

namespace penguin::internal::rendering::systems {
	// Forward declaration
	struct AssetManagerImpl;
}

namespace penguin::rendering::systems {

	class PENGUIN_API AssetManager {
	public:
		AssetManager(NativeRendererPtr renderer_ptr); // add text_renderer later
		~AssetManager();

		// Deleting move semantics

		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;

		// Various load functions
		std::shared_ptr<primitives::Texture> load(const char* path);

	private:
		std::unique_ptr<penguin::internal::rendering::systems::AssetManagerImpl> pimpl_;
	};
}