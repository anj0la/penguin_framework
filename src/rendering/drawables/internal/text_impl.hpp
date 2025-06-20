#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/math/colours.hpp>
#include <penguin_framework/math/vector2.hpp>

#include <error/internal/internal_error.hpp>

#include <SDL3_ttf/SDL_ttf.h>

#include <memory>
#include <string>

namespace penguin::internal::rendering::drawables {

    struct TextImpl {
        std::unique_ptr<TTF_Text, void(*)(TTF_Text*)> text;
        std::string str;
        penguin::math::Vector2 position;
        penguin::math::Colour colour;

        TextImpl(NativeTextContextPtr text_renderer_ptr, NativeFontPtr font, const char* str, penguin::math::Colour colour = Colours::White, penguin::math::Vector2 position = penguin::math::Vector2::Zero);

    };
}