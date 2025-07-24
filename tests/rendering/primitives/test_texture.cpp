#include <penguin_framework/window/window.hpp>
#include <penguin_framework/rendering/renderer.hpp>
#include <penguin_framework/rendering/primitives/texture.hpp>
#include <penguin_framework/penguin_init.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <string>

#include <common/test_helpers.hpp>

using penguin::window::Window;
using penguin::window::WindowFlags;
using penguin::rendering::Renderer;
using penguin::rendering::primitives::Texture;
using penguin::math::Vector2i;

class TextureTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Window> invalid_window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<Renderer> invalid_renderer_ptr;
    const char* asset_name = "penguin_cute.bmp";
    const char* invalid_asset_name = "non_existent.bmp";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name)).string();
    std::string invalid_abs_path = std::filesystem::absolute(get_test_asset_path(invalid_asset_name)).string();

    void SetUp() override {
        penguin::InitOptions options{ .headless_mode = true };
        ASSERT_TRUE(penguin::init(options));

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_valid()); // window should be OPEN and VALID

        invalid_window_ptr = std::make_unique<Window>("Invalid Window", Vector2i(-1, -1), static_cast<WindowFlags>(0xFFFFFFFF)); // the flag is a nonsensical value
        ASSERT_FALSE(invalid_window_ptr->is_valid());

        renderer_ptr = std::make_unique<Renderer>(*window_ptr, "software");
        ASSERT_TRUE(renderer_ptr->is_valid());

        invalid_renderer_ptr = std::make_unique<Renderer>(*invalid_window_ptr, "");
        ASSERT_FALSE(invalid_renderer_ptr->is_valid());
    }

    void TearDown() override {
        // Manually destroy resources in reverse order
        invalid_renderer_ptr.reset();
        renderer_ptr.reset();
        invalid_window_ptr.reset();
        window_ptr.reset();

        // Safe to quit
        penguin::quit();
    }
};

TEST_F(TextureTestFixture, Constructor_ValidPath_CreatesTexture) {
    // Arrange
    Vector2i expected_size(362, 362);

    // Act
    std::unique_ptr<Texture> texture_ptr = std::make_unique<Texture>(renderer_ptr->get_native_ptr(), abs_path.c_str());

    // Assert
    EXPECT_TRUE(texture_ptr->is_valid());

    Vector2i texture_size = texture_ptr->get_size();
    EXPECT_GT(texture_size.x, 0);
    EXPECT_GT(texture_size.y, 0);
    EXPECT_EQ(texture_size.x, expected_size.x);
    EXPECT_EQ(texture_size.y, expected_size.y);
}

// Validity

TEST_F(TextureTestFixture, BoolOperator_WithValidTexture_ReturnsTrue) {
    // Arrange
    std::unique_ptr<Texture> texture_ptr = std::make_unique<Texture>(renderer_ptr->get_native_ptr(), abs_path.c_str());

    // Act
    bool bool_result = static_cast<bool>(*texture_ptr);

    // Assert
    EXPECT_TRUE(bool_result);
}

// Native Pointer

TEST_F(TextureTestFixture, GetNativePtr_WithValidTexture_ReturnsNonNullPtr) {
    // Arrange
    std::unique_ptr<Texture> texture_ptr = std::make_unique<Texture>(renderer_ptr->get_native_ptr(), abs_path.c_str());

    // Act
    auto native_ptr = texture_ptr->get_native_ptr();

    // Assert
    EXPECT_TRUE(texture_ptr->is_valid());
    EXPECT_NE(native_ptr.ptr, nullptr);
}

// Texture Size

TEST_F(TextureTestFixture, GetSize_WithValidTexture_ReturnsCorrectSize) {
    // Arrange
    std::unique_ptr<Texture> texture_ptr = std::make_unique<Texture>(renderer_ptr->get_native_ptr(), abs_path.c_str());
    Vector2i expected_size(362, 362);

    // Act
    Vector2i texture_size = texture_ptr->get_size();

    // Assert
    EXPECT_TRUE(texture_ptr->is_valid());
    EXPECT_EQ(texture_size.x, expected_size.x);
    EXPECT_EQ(texture_size.y, expected_size.y);
}

// Invalid Texture Operations

TEST_F(TextureTestFixture, Constructor_InvalidRenderer_CreatesInvalidTexture) {
    // Arrange & Act
    std::unique_ptr<Texture> texture_ptr = std::make_unique<Texture>(invalid_renderer_ptr->get_native_ptr(), abs_path.c_str());

    // Assert
    EXPECT_FALSE(texture_ptr->is_valid());
}

TEST_F(TextureTestFixture, BoolOperator_WithInvalidTexture_ReturnsFalse) {
    // Arrange
    std::unique_ptr<Texture> texture_ptr = std::make_unique<Texture>(invalid_renderer_ptr->get_native_ptr(), abs_path.c_str());

    // Act
    bool bool_result = static_cast<bool>(*texture_ptr);

    // Assert
    EXPECT_FALSE(bool_result);
}

TEST_F(TextureTestFixture, GetNativePtr_WithInvalidTexture_ReturnsNullPtr) {
    // Arrange
    std::unique_ptr<Texture> texture_ptr = std::make_unique<Texture>(invalid_renderer_ptr->get_native_ptr(), abs_path.c_str());

    // Act
    auto native_ptr = texture_ptr->get_native_ptr();

    // Assert
    EXPECT_EQ(native_ptr.ptr, nullptr);
}