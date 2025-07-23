#pragma once

#include <penguin_api.hpp>

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/primitives/texture.hpp>

#include <memory>

namespace penguin::internal::rendering::systems {
	// Forward declaration
	struct TextureLoaderImpl;
}

namespace penguin::rendering::systems {

	class PENGUIN_API TextureLoader {
	public:
		TextureLoader();
		~TextureLoader();

		// Move semantics

		TextureLoader(const TextureLoader&) = default;
		TextureLoader& operator=(const TextureLoader&) = default;

		// Validity checking

		[[nodiscard]] bool is_valid() const noexcept;
		[[nodiscard]] explicit operator bool() const noexcept;

		// Load function
		std::shared_ptr<primitives::Texture> load(NativeRendererPtr renderer, const char* path);

	private:
		std::unique_ptr<penguin::internal::rendering::systems::TextureLoaderImpl> pimpl_;
	};
}