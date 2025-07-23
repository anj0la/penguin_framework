#pragma once

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/systems/texture_loader.hpp>
#include <penguin_framework/rendering/systems/font_loader.hpp>
#include <penguin_framework/rendering/primitives/texture.hpp>
#include <penguin_framework/rendering/primitives/font.hpp>

#include <penguin_framework/math/rect2.hpp>
#include <penguin_framework/math/circle2.hpp>
#include <penguin_framework/math/colours.hpp>
#include <penguin_framework/math/vector2i.hpp>

#include <error/internal/internal_error.hpp>

#include <memory>
#include <unordered_set>
#include <filesystem>

namespace penguin::internal::rendering::systems {

	class AssetManagerImpl {
	public:
		NativeRendererPtr renderer_ptr;
		penguin::rendering::systems::TextureLoader texture_loader;
		penguin::rendering::systems::FontLoader font_loader;

		AssetManagerImpl(NativeRendererPtr renderer);

		// Copy & move (including assigment) not allowed

		AssetManagerImpl(const AssetManagerImpl&) = delete;
		AssetManagerImpl& operator=(const AssetManagerImpl&) = delete;
		AssetManagerImpl(AssetManagerImpl&&) noexcept = delete;
		AssetManagerImpl& operator=(AssetManagerImpl&&) noexcept = delete;

		std::shared_ptr<penguin::rendering::primitives::Texture> load_texture(const char* path);
		std::shared_ptr<penguin::rendering::primitives::Font> load_font(const char* path, float size, int outline);

	private:
		bool has_valid_image_ext(const std::filesystem::path& path);
		bool has_valid_font_ext(const std::filesystem::path& path);
		const std::unordered_set<std::string> valid_image_ext = { ".png", ".jpg", ".jpeg", ".bmp", ".gif", ".svg"};
		const std::unordered_set<std::string> valid_font_ext = { ".ttf", ".otf" };
	};
}