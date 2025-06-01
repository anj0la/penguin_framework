#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/math/rect2.hpp>
#include <penguin_framework/math/circle2.hpp>
#include <penguin_framework/math/colours.hpp>
#include <penguin_framework/math/vector2i.hpp>

#include <memory>
#include <vector>

namespace penguin::internal::rendering::primitives {
	// Forward declaration
	struct TextureImpl;
}

namespace penguin::rendering::primitives {

	class PENGUIN_API Texture {
	public:
		Texture(NativeRendererPtr renderer_ptr, const char* path);
		~Texture();

		Texture(Texture&&) noexcept;
		Texture& operator=(Texture&&) noexcept;

		// Validity checking

		[[nodiscard]] bool is_valid() const noexcept;
		[[nodiscard]] explicit operator bool() const noexcept;

		NativeTexturePtr get_native_ptr() const;
		penguin::math::Vector2i get_size() const;

	private:
		std::unique_ptr<penguin::internal::rendering::primitives::TextureImpl> pimpl_;
		bool valid_state_;
	};
}