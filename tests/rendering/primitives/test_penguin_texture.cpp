#include <penguin_framework/window/penguin_window.hpp>
#include <penguin_framework/rendering/penguin_renderer.hpp>
#include <penguin_framework/rendering/primitives/penguin_texture.hpp>

#include <SDL3/SDL.h>
#include <gtest/gtest.h>
#include <memory>
#include <filesystem>
#include <string>

using penguin::window::Window;
using penguin::window::WindowFlags;
using penguin::rendering::Renderer;
using penguin::rendering::primitives::Texture;
using penguin::math::Vector2i;

// Helper Functions

std::filesystem::path get_test_asset_path(const char* name) {
    return std::filesystem::path(TEST_ASSETS_DIR) / name;
}

// Setting Up the Test Suite

class TextureTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    const char* asset_name = "penguin_cute.bmp";

    void SetUp() override {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
        ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError();

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_valid()); // window should be OPEN and VALID

        renderer_ptr = std::make_unique<Renderer>(window_ptr.get()->get_native_ptr(), "software");
        ASSERT_TRUE(renderer_ptr->is_valid());
    }

    void TearDown() override {
        SDL_Quit();
    }
};

TEST_F(TextureTestFixture, Constructor_ValidPath_CreatesTexture) {
    // Arrange
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name)).string();
    std::unique_ptr<Texture> texture_ptr;
    Vector2i expected_size(362, 362);

    // Act (Construction)
    texture_ptr = std::make_unique<Texture>(renderer_ptr->get_native_ptr(), abs_path.c_str());

    // Assert - Validate that object was created
    ASSERT_TRUE(texture_ptr); // calls the bool() operator which checks that the impl has been created along with the native texture ptr

    // Assert - Validate the width and height are greater than 0
    Vector2i texture_size = texture_ptr->get_size();
    ASSERT_GT(texture_size.x, 0);
    ASSERT_GT(texture_size.y, 0);
    EXPECT_EQ(texture_size.x, expected_size.x);
    EXPECT_EQ(texture_size.y, expected_size.y);
}