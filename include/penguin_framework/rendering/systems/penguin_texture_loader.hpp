#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/primitives/penguin_texture.hpp>

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

		// Deleting move semantics

		TextureLoader(const TextureLoader&) = delete;
		TextureLoader& operator=(const TextureLoader&) = delete;

		// Validity checking

		[[nodiscard]] bool is_valid() const noexcept;
		[[nodiscard]] explicit operator bool() const noexcept;

		// Load function
		std::shared_ptr<primitives::Texture> load(NativeRendererPtr renderer, const char* path);

	private:
		std::unique_ptr<penguin::internal::rendering::systems::TextureLoaderImpl> pimpl_;
		bool valid_state_;
	};
}