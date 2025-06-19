#include <penguin_framework/window/penguin_window.hpp>
#include <penguin_framework/rendering/penguin_renderer.hpp>
#include <penguin_framework/rendering/primitives/penguin_texture.hpp>

#include <SDL3/SDL.h>
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
    std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<Renderer> invalid_renderer_ptr;
    const char* asset_name = "penguin_cute.bmp";
    const char* invalid_asset_name = "non_existent.bmp";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name)).string();
    std::string invalid_abs_path = std::filesystem::absolute(get_test_asset_path(invalid_asset_name)).string();

    void SetUp() override {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
        ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError();

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_valid()); // window should be OPEN and VALID

        renderer_ptr = std::make_unique<Renderer>(window_ptr.get()->get_native_ptr(), "software");
        ASSERT_TRUE(renderer_ptr->is_valid());

        invalid_renderer_ptr = std::make_unique<Renderer>(NativeWindowPtr{ nullptr }, "");
    }

    void TearDown() override {
        SDL_Quit();
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
}