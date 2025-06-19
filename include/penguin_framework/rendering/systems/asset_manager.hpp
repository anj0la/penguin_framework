#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/rendering/primitives/texture.hpp>

#include <memory>

namespace penguin::internal::rendering::systems {
	// Forward declaration
	class AssetManagerImpl;
}

namespace penguin::rendering::systems {

	class PENGUIN_API AssetManager {
	public:
		AssetManager(NativeRendererPtr renderer_ptr); // add text_renderer later
		~AssetManager();

		// Move semantics

		AssetManager(const AssetManager&) = default;
		AssetManager& operator=(const AssetManager&) = default;

		// Validity checking

		[[nodiscard]] bool is_valid() const noexcept;
		[[nodiscard]] explicit operator bool() const noexcept;

		// Various load functions
		std::shared_ptr<primitives::Texture> load(const char* path);

	private:
		std::unique_ptr<penguin::internal::rendering::systems::AssetManagerImpl> pimpl_;
	};
}