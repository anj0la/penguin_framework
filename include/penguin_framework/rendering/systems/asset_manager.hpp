#pragma once

#include <penguin_api.hpp>

#include <penguin_framework/rendering/renderer.hpp>
#include <penguin_framework/rendering/primitives/texture.hpp>
#include <penguin_framework/rendering/primitives/font.hpp>

#include <memory>

namespace penguin::internal::rendering::systems {
	// Forward declaration
	class AssetManagerImpl;
}

namespace penguin::rendering::systems {

	class PENGUIN_API AssetManager {
	public:
		AssetManager(const rendering::Renderer& renderer);
		~AssetManager();

		// Move semantics

		AssetManager(const AssetManager&) = default;
		AssetManager& operator=(const AssetManager&) = default;

		// Validity checking

		[[nodiscard]] bool is_valid() const noexcept;
		[[nodiscard]] explicit operator bool() const noexcept;

		// Various load functions

		std::shared_ptr<primitives::Texture> load_texture(const char* path);
		std::shared_ptr<primitives::Font> load_font(const char* path, float size = 12.0f, int outline = 1);

	private:
		std::unique_ptr<penguin::internal::rendering::systems::AssetManagerImpl> pimpl_;
	};
}