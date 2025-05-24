#include <penguin_framework/core/window/penguin_window.hpp>
#include <penguin_framework/core/rendering/penguin_renderer.hpp>
#include <penguin_framework/core/rendering/primitives/penguin_texture.hpp>
#include <SDL3/SDL.h>
#include <gtest/gtest.h>
#include <memory>
#include <filesystem>
#include <string>

using penguin::core::window::Window;
using penguin::core::window::WindowFlags;
using penguin::core::rendering::Renderer;
using penguin::core::rendering::primitives::Texture;

// Helper Functions

std::filesystem::path get_test_asset_path(const char* name) {
    return std::filesystem::path(TEST_ASSETS_DIR) / name;
}

// Setting Up the Test Suite

class TextureTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    String asset_name = "penguin_cute.bmp";

    void SetUp() override {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
        ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError();

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_open()) << "Window is open after creation.";

        renderer_ptr = std::make_unique<Renderer>(window_ptr.get()->get_native_ptr(), "software");
        ASSERT_NE(renderer_ptr->get_native_ptr().as<SDL_Renderer>(), nullptr) << "Native renderer is null.";
    }

    void TearDown() override {
        SDL_Quit();
    }
};

TEST_F(TextureTestFixture, ConstructorCreatesTexture) {
    // Arrange
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name.c_str())).string();
    std::unique_ptr<Texture> texture_obj;
    Vector2i expected_size(362, 362);

    // Act & Assert (Construction)
    ASSERT_NO_THROW({
        texture_obj = std::make_unique<Texture>(renderer_ptr->get_native_ptr(), abs_path.c_str());
        });

    // Assert - Validate that object was created
    ASSERT_NE(texture_obj, nullptr);
    ASSERT_NE(texture_obj->get_native_ptr().ptr, nullptr);

    // Assert - Validate the width and height are greater than 0
    Vector2i texture_size = texture_obj->get_size();
    ASSERT_GT(texture_size.x, 0);
    ASSERT_GT(texture_size.y, 0);
    EXPECT_EQ(texture_size.x, expected_size.x);
    EXPECT_EQ(texture_size.y, expected_size.y);
}
 
// Note: This will not happen in practice as the path will be validated with the AssetManager, so it is guaranteed
// that the Texture will receive a valid path. This is to ensure that an exception is actually being thrown.
TEST_F(TextureTestFixture, ConstructorInvalidPathThrowsException) {
    // Arrange
    std::string invalid_path = "path/to/nonexistent/texture.png";

    // Act & Assert
    ASSERT_THROW({
        Texture texture(renderer_ptr->get_native_ptr(), invalid_path.c_str());
        }, std::exception);
}