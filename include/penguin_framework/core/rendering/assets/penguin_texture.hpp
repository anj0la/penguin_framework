#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/core/common/native_types.hpp>
#include <penguin_framework/core/rendering/penguin_renderer.hpp>
#include <penguin_framework/utils/exception.hpp>
#include <penguin_framework/core/math/rect2.hpp>
#include <penguin_framework/core/math/circle2.hpp>
#include <penguin_framework/core/math/colours.hpp>
#include <penguin_framework/core/math/vector2i.hpp>

#include <memory>
#include <vector>

namespace penguin::core::rendering::assets {

	class PENGUIN_API Texture {
	public:
		Texture(penguin::core::rendering::Renderer& renderer, const char* path);
		~Texture();

		// Move constructor & assignment destructors (copy constructor / assignment not allowed)

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture(Texture&&) noexcept = default;
		Texture& operator=(Texture&&) noexcept = default;

		NativeTexturePtr get_native_ptr() const;

	private:
		struct TextureImpl;

		std::unique_ptr<TextureImpl> pimpl_;

	};


}