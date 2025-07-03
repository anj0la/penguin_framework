#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/primitives/font.hpp>

#include <memory>

namespace penguin::internal::rendering::systems {
	// Forward declaration
	struct FontLoaderImpl;
}

namespace penguin::rendering::systems {

	class PENGUIN_API FontLoader {
	public:
		FontLoader();
		~FontLoader();

		// Move semantics

		FontLoader(const FontLoader&) = default;
		FontLoader& operator=(const FontLoader&) = default;

		// Validity checking

		[[nodiscard]] bool is_valid() const noexcept;
		[[nodiscard]] explicit operator bool() const noexcept;

		// Load function
		std::shared_ptr<primitives::Font> load(const char* path, float size);

	private:
		std::unique_ptr<penguin::internal::rendering::systems::FontLoaderImpl> pimpl_;
	};
}