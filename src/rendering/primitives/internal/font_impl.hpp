#pragma once

#include <penguin_framework/common/native_types.hpp>
#include <error/internal/internal_error.hpp>

#include <SDL3_ttf/SDL_ttf.h>

#include <memory>
#include <array>
#include <string>

namespace penguin::internal::rendering::primitives {

    struct FontImpl {
        std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> font;
        float size;
        int outline;
        bool normal;
        bool bold;
        bool italic;
        bool underline;
        bool strikethrough;
        TTF_FontStyleFlags applied_styles;
        std::string applied_styles_str;

        FontImpl(const char* path, float p_size = 12.0f, int p_outline = 1);

        void make_normal();
        void make_bold(); 
        void make_italic();
        void make_underline();
        void make_strikethrough();
    };
}