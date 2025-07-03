#pragma once


#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/primitives/font.hpp>

#include <error/internal/internal_error.hpp>

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

namespace penguin::internal::rendering::systems {

	struct FontLoaderImpl {

		std::unordered_map<std::string, std::shared_ptr<penguin::rendering::primitives::Font>> font_cache;

		FontLoaderImpl() = default;

		// Copy & move (including assigment) not allowed

		FontLoaderImpl(const FontLoaderImpl&) = delete;
		FontLoaderImpl& operator=(const FontLoaderImpl&) = delete;
		FontLoaderImpl(FontLoaderImpl&&) noexcept = delete;
		FontLoaderImpl& operator=(FontLoaderImpl&&) noexcept = delete;

		// Load function

		std::shared_ptr<penguin::rendering::primitives::Font> load(const char* path, float size);
	};
}