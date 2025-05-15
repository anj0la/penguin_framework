#pragma once

#include <penguin_framework/core/common/native_types.hpp>
#include <penguin_framework/core/rendering/systems/penguin_texture_loader.hpp>
#include <penguin_framework/core/rendering/primitives/penguin_texture.hpp>
#include <penguin_framework/utils/string.hpp>
#include <penguin_framework/core/math/rect2.hpp>
#include <penguin_framework/core/math/circle2.hpp>
#include <penguin_framework/core/math/colours.hpp>
#include <penguin_framework/core/math/vector2i.hpp>

#include <memory>
#include <filesystem>

namespace penguin::core::rendering::systems {

	struct AssetManagerImpl {
	public:
		// AssetManager MUST NOT outlive Renderer
		// Created by the framework and managed:
		//
		// Renderer renderer;
		// AssetManager content(renderer.get_native_ptr());
		//
		// Then when the destructor is called, the AssetManager is destroyed FIRST before the renderer
		NativeRendererPtr renderer_ptr;
		TextureLoader texture_loader;

		AssetManagerImpl(NativeRendererPtr renderer); // add text_renderer later

		// Copy & move (including assigment) not allowed

		AssetManagerImpl(const AssetManagerImpl&) = delete;
		AssetManagerImpl& operator=(const AssetManagerImpl&) = delete;
		AssetManagerImpl(AssetManagerImpl&&) noexcept = delete;
		AssetManagerImpl& operator=(AssetManagerImpl&&) noexcept = delete;

		std::shared_ptr<primitives::Texture> load(const char* path);
	};
}