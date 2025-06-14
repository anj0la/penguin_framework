#include <penguin_framework/core/window/penguin_window.hpp>
#include <penguin_framework/core/rendering/penguin_renderer.hpp>
#include <penguin_framework/core/rendering/primitives/penguin_texture.hpp>
#include <penguin_framework/core/rendering/systems/penguin_asset_manager.hpp>
#include <SDL3/SDL.h>
#include <gtest/gtest.h>
#include <memory>
#include <filesystem>
#include <string>

using penguin::core::window::Window;
using penguin::core::window::WindowFlags;
using penguin::core::rendering::Renderer;
using penguin::core::rendering::systems::AssetManager;
using penguin::core::rendering::primitives::Texture;

// Helper Functions

std::filesystem::path get_test_asset_path(const char* name) {
    return std::filesystem::path(TEST_ASSETS_DIR) / name;
}

// Setting Up the Test Suite

class AssetManagerTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<AssetManager> content_ptr;
    std::shared_ptr<Texture> texture_ptr;

    String asset_name = "penguin_cute.bmp";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name.c_str())).string();

    void SetUp() override {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
        ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError();

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_open());

        renderer_ptr = std::make_unique<Renderer>(window_ptr.get()->get_native_ptr(), "software");
        ASSERT_NE(renderer_ptr->get_native_ptr().as<SDL_Renderer>(), nullptr);

        content_ptr = std::make_unique<AssetManager>(renderer_ptr->get_native_ptr());
        ASSERT_NE(content_ptr, nullptr);
    }

    void TearDown() override {
        SDL_Quit();
    }
};

TEST_F(AssetManagerTestFixture, LoadFunction_Returns_Valid_Texture) {
    // Arrange & Act
    texture_ptr = content_ptr->load(abs_path.c_str());

    // Assert - texture is not null
    EXPECT_NE(texture_ptr, nullptr);

    // Assert - texture size is greater than 0
    Vector2i texture_size = texture_ptr->get_size();
    EXPECT_GT(texture_size.x, 0);
    EXPECT_GT(texture_size.y, 0);
}

TEST_F(AssetManagerTestFixture, LoadFunction_Returns_NullPointer) {
    // Arrange
    const char* invalid_path = "cute_img.png";

    // Act
    texture_ptr = content_ptr->load(invalid_path);

    // Assert - texture is null
    EXPECT_EQ(texture_ptr, nullptr);
}