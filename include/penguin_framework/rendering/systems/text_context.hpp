#pragma once

#include <penguin_api.hpp>

#include <penguin_framework/rendering/renderer.hpp>
#include <penguin_framework/common/native_types.hpp>
#include <memory>

namespace penguin::internal::rendering::systems {
    // Forward declaration
    struct TextContextImpl;
}

namespace penguin::rendering::systems {

    class PENGUIN_API TextContext {
    public:
        TextContext(const rendering::Renderer& renderer);
        ~TextContext();

        // Move semantics

        TextContext(const TextContext&) = default;
        TextContext& operator=(const TextContext&) = default;

        // Validity checking

        [[nodiscard]] bool is_valid() const noexcept;
        [[nodiscard]] explicit operator bool() const noexcept;

        NativeTextContextPtr get_native_ptr() const;

    private:
        std::unique_ptr<penguin::internal::rendering::systems::TextContextImpl> pimpl_;
    };
}

