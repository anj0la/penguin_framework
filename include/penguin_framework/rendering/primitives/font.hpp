#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/rendering/primitives/font_style.hpp>

#include <memory>

namespace penguin::internal::rendering::primitives {
    // Forward declaration
    struct FontImpl;
}

namespace penguin::rendering::primitives {

    class PENGUIN_API Font {
    public:
        Font(const char* path, float size);
        ~Font();

        Font(Font&&) noexcept;
        Font& operator=(Font&&) noexcept;

        // Validity checking

        [[nodiscard]] bool is_valid() const noexcept;
        [[nodiscard]] explicit operator bool() const noexcept;

        float get_size();
        int get_outline();
        const char* get_styles() const;

        void set_size(float new_size);
        void set_outline(int new_outline);
        void add_style(FontStyle style);
        void remove_style(FontStyle style);
        void replace_style(FontStyle style);

        NativeFontPtr get_native_ptr();

    private:
        std::unique_ptr<penguin::internal::rendering::primitives::FontImpl> pimpl_;
    };
}