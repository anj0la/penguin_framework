#pragma once

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/primitives/font_style.hpp>

#include <error/internal/internal_error.hpp>

#include <SDL3_ttf/SDL_ttf.h>

#include <memory>
#include <array>

namespace penguin::internal::rendering::primitives {

    struct FontImpl {
        std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> font;
        float size;
        int outline;
        TTF_FontStyleFlags applied_styles;

        FontImpl(const char* path, float p_size = 12.0f, int p_outline = 1);

        void add_style(penguin::rendering::primitives::FontStyle style_flags);
        void remove_style(penguin::rendering::primitives::FontStyle style_flags);
        void replace_style(penguin::rendering::primitives::FontStyle style_flag);

        const char* get_styles() const;
    };

    constexpr std::array<const char*, 16> style_names = {
        "normal", "bold", "italic", "bold, italic",
        "underline", "bold, underline", "italic, underline", "bold, italic, underline",
        "strikethrough", "bold, strikethrough", "italic, strikethrough", "bold, italic, strikethrough",
        "underline, strikethrough", "bold, underline, strikethrough", "italic, underline, strikethrough",
        "bold, italic, underline, strikethrough"
    };

}