#pragma once

#include <penguin_framework/common/native_types.hpp>
#include <error/internal/internal_error.hpp>

#include <SDL3_ttf/SDL_textengine.h>
#include <memory>

namespace penguin::internal::rendering::systems {
    struct TextContextImpl {
        std::unique_ptr<TTF_TextEngine, void(*)(TTF_TextEngine*)> context;

        TextContextImpl(NativeRendererPtr renderer);
    };
}