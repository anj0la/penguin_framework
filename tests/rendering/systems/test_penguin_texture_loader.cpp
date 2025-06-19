#include <penguin_framework/window/penguin_window.hpp>
#include <penguin_framework/rendering/penguin_renderer.hpp>
#include <penguin_framework/rendering/primitives/penguin_texture.hpp>
#include <penguin_framework/rendering/systems/penguin_texture_loader.hpp>
#include <SDL3/SDL.h>
#include <gtest/gtest.h>
#include <memory>
#include <filesystem>
#include <string>

#include <common/test_helpers.hpp>

using penguin::window::Window;
using penguin::window::WindowFlags;
using penguin::rendering::Renderer;
using penguin::rendering::systems::TextureLoader;
using penguin::rendering::primitives::Texture;
using penguin::math::Vector2i;

class TextureLoaderTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<TextureLoader> loader_ptr;

    std::unique_ptr<Renderer> invalid_renderer_ptr;

    const char* asset_name = "penguin_cute.bmp";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name)).string();

    void SetUp() override {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
        ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError();

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_valid()); // window should be OPEN and VALID

        renderer_ptr = std::make_unique<Renderer>(window_ptr.get()->get_native_ptr(), "software");
        ASSERT_TRUE(renderer_ptr->is_valid());

        loader_ptr = std::make_unique<TextureLoader>();
        ASSERT_TRUE(loader_ptr->is_valid());

        invalid_renderer_ptr = std::make_unique<Renderer>(NativeWindowPtr{ nullptr }, "");
        ASSERT_FALSE(invalid_renderer_ptr->is_valid());
    }

    void TearDown() override {
        SDL_Quit();
    }
};

// Validity
// Note: as we aren't passing any parameters, if the loader is constructed, then it's guaranteed to be valid all the time
// This may change in a later update

TEST_F(TextureLoaderTestFixture, IsValid_WithValidLoader_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool is_valid = loader_ptr->is_valid();

    // Assert
    EXPECT_TRUE(is_valid);
}

TEST_F(TextureLoaderTestFixture, BoolOperator_WithValidLoader_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool bool_result = static_cast<bool>(*loader_ptr);

    // Assert
    EXPECT_TRUE(bool_result);
}

// Load
// Note: No need to test for invalid path as TextureLoader is guaranteed to have a valid path

TEST_F(TextureLoaderTestFixture, LoadFunction_WithValidParameters_ReturnsValidTexture) {
    // Arrange & Act
    std::shared_ptr<Texture> texture_ptr = loader_ptr->load(renderer_ptr->get_native_ptr(), abs_path.c_str());

    // Assert
    EXPECT_TRUE(loader_ptr->is_valid());
    EXPECT_TRUE(texture_ptr->is_valid());

    Vector2i texture_size = texture_ptr->get_size();
    EXPECT_GT(texture_size.x, 0);
    EXPECT_GT(texture_size.y, 0);
}

TEST_F(TextureLoaderTestFixture, LoadFunction_WithInvalidRenderer_ReturnsInvalidTexture) {
    // Arrange & Act
    std::shared_ptr<Texture> texture_ptr = loader_ptr->load(invalid_renderer_ptr->get_native_ptr(), abs_path.c_str());

    // Assert
    EXPECT_TRUE(loader_ptr->is_valid());

    EXPECT_TRUE(texture_ptr || !texture_ptr->is_valid()); // Texture should be null or invalid when created with invalid renderer
}