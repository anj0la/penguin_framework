#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/systems/text_context.hpp>
#include <penguin_framework/rendering/primitives/font.hpp>
#include <penguin_framework/math/colours.hpp>
#include <penguin_framework/math/vector2.hpp>

#include <memory>

namespace penguin::internal::rendering::drawables {
    // Forward declaration
    struct TextImpl;
}

namespace penguin::rendering::drawables {

    class PENGUIN_API Text { // TODO -> create TextContext
    public:
        Text(systems::TextContext text_context, std::shared_ptr<penguin::rendering::primitives::Font> font, const char* str, penguin::math::Colour colour = Colours::White, penguin::math::Vector2 position = penguin::math::Vector2::Zero);
        ~Text();

        Text(Text&&) noexcept;
        Text& operator=(Text&&) noexcept;

        // Validity checking

        [[nodiscard]] bool is_valid() const noexcept;
        [[nodiscard]] explicit operator bool() const noexcept;

        penguin::math::Vector2 get_position() const;
        penguin::math::Colour get_colour() const;
        const char* get_string() const;

        void set_position(penguin::math::Vector2 new_position);
        void set_colour(penguin::math::Colour new_colour);
        void set_string(const char* new_string);

        NativeTextPtr get_native_ptr();

    private:
        std::unique_ptr<penguin::internal::rendering::drawables::TextImpl> pimpl_;
    };
}