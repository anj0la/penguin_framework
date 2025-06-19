#pragma once

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/systems/texture_loader.hpp>
#include <penguin_framework/rendering/primitives/texture.hpp>
#include <penguin_framework/math/rect2.hpp>
#include <penguin_framework/math/circle2.hpp>
#include <penguin_framework/math/colours.hpp>
#include <penguin_framework/math/vector2i.hpp>

#include <error/internal/internal_error.hpp>

#include <memory>
#include <vector>
#include <filesystem>

namespace penguin::internal::rendering::systems {

	class AssetManagerImpl {
	public:
		// AssetManager MUST NOT outlive Renderer
		// Created by the framework and managed:
		//
		// Renderer renderer;
		// AssetManager content(renderer.get_native_ptr());
		//
		// Then when the destructor is called, the AssetManager is destroyed FIRST before the renderer
		NativeRendererPtr renderer_ptr;
		penguin::rendering::systems::TextureLoader texture_loader;

		AssetManagerImpl(NativeRendererPtr renderer); // add text_renderer later

		// Copy & move (including assigment) not allowed

		AssetManagerImpl(const AssetManagerImpl&) = delete;
		AssetManagerImpl& operator=(const AssetManagerImpl&) = delete;
		AssetManagerImpl(AssetManagerImpl&&) noexcept = delete;
		AssetManagerImpl& operator=(AssetManagerImpl&&) noexcept = delete;

		std::shared_ptr<penguin::rendering::primitives::Texture> load(const char* path);
	private:
		bool has_supported_image_ext(const std::filesystem::path& path);
		const std::vector<std::string> supported = { ".png", ".jpg", ".jpeg", ".bmp", ".gif" };
	};
}