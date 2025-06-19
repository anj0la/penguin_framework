#include <penguin_framework/window/penguin_window.hpp>
#include <penguin_framework/rendering/penguin_renderer.hpp>
#include <penguin_framework/rendering/primitives/penguin_texture.hpp>
#include <penguin_framework/rendering/systems/penguin_asset_manager.hpp>
#include <SDL3/SDL.h>
#include <gtest/gtest.h>
#include <memory>
#include <filesystem>
#include <string>

#include <common/test_helpers.hpp>

using penguin::window::Window;
using penguin::window::WindowFlags;
using penguin::rendering::Renderer;
using penguin::rendering::systems::AssetManager;
using penguin::rendering::primitives::Texture;
using penguin::math::Vector2i;

class AssetManagerTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<AssetManager> content_ptr;

    std::unique_ptr<Renderer> invalid_renderer_ptr;
    std::unique_ptr<AssetManager> invalid_content_ptr;
    std::unique_ptr<AssetManager> valid_content_ptr;

    const char* asset_name = "penguin_cute.bmp";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name)).string();

    void SetUp() override {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
        ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError();

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_valid()); // window should be OPEN and VALID

        renderer_ptr = std::make_unique<Renderer>(window_ptr.get()->get_native_ptr(), "software");
        ASSERT_TRUE(renderer_ptr->is_valid());

        content_ptr = std::make_unique<AssetManager>(renderer_ptr->get_native_ptr());
        ASSERT_TRUE(content_ptr->is_valid());

        invalid_renderer_ptr = std::make_unique<Renderer>(NativeWindowPtr{ nullptr }, "");
        ASSERT_FALSE(invalid_renderer_ptr->is_valid());

        invalid_content_ptr = std::make_unique<AssetManager>(invalid_renderer_ptr->get_native_ptr());
        ASSERT_FALSE(invalid_content_ptr->is_valid());
    }

    void TearDown() override {
        SDL_Quit();
    }
};

// Validity

TEST_F(AssetManagerTestFixture, IsValid_WithValidAssetManager_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool is_valid = content_ptr->is_valid();

    // Assert
    EXPECT_TRUE(is_valid);
}

TEST_F(AssetManagerTestFixture, BoolOperator_WithValidAssetManager_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool bool_result = static_cast<bool>(*content_ptr);

    // Assert
    EXPECT_TRUE(bool_result);
}

// Load

TEST_F(AssetManagerTestFixture, LoadFunction_WithValidPath_ReturnsValidTexture) {
    // Arrange & Act
    std::shared_ptr<Texture> texture_ptr = content_ptr->load(abs_path.c_str());

    // Assert
    EXPECT_TRUE(content_ptr->is_valid());
    EXPECT_TRUE(texture_ptr->is_valid());

    Vector2i texture_size = texture_ptr->get_size();
    EXPECT_GT(texture_size.x, 0);
    EXPECT_GT(texture_size.y, 0);
}

// Invalid AssetManager Operations

TEST_F(AssetManagerTestFixture, IsValid_WithInvalidAssetManager_ReturnsFalse) {
    // Arrange (done in SetUp)

    // Act
    bool is_valid = invalid_content_ptr->is_valid();

    // Assert
    EXPECT_FALSE(is_valid);
}

TEST_F(AssetManagerTestFixture, BoolOperator_WithInvalidAssetManager_ReturnsFalse) {
    // Arrange (done in SetUp)

    // Act
    bool bool_result = static_cast<bool>(*invalid_content_ptr);

    // Assert
    EXPECT_FALSE(bool_result);
}

TEST_F(AssetManagerTestFixture, LoadFunction_WithInvalidAssetManager_ReturnsNullPtr) {
    // Arrange & Act
    std::shared_ptr<Texture> texture_ptr = invalid_content_ptr->load(abs_path.c_str());

    // Assert
    EXPECT_FALSE(invalid_content_ptr->is_valid());
    EXPECT_EQ(texture_ptr, nullptr);
}

TEST_F(AssetManagerTestFixture, LoadFunction_WithInvalidPath_ReturnsNullPtr) {
    // Arrange
    const char* invalid_path = "cute_img.png";

    // Act
    std::shared_ptr<Texture> texture_ptr = content_ptr->load(invalid_path);

    // Assert
    EXPECT_TRUE(content_ptr->is_valid());
    EXPECT_EQ(texture_ptr, nullptr);
}

TEST_F(AssetManagerTestFixture, LoadFunction_WithInvalidPathExt_ReturnsNullPtr) {
    // Arrange
    const char* invalid_path = "penguin_cute.svg";

    // Act
    std::shared_ptr<Texture> texture_ptr = content_ptr->load(invalid_path);

    // Assert
    EXPECT_TRUE(content_ptr->is_valid());
    EXPECT_EQ(texture_ptr, nullptr);
}

TEST_F(AssetManagerTestFixture, LoadFunction_InvalidPath_Returns_NullPointer) {
    // Arrange
    const char* invalid_path = "cute_img.png";

    // Act
    std::shared_ptr<Texture> texture_ptr = content_ptr->load(invalid_path);

    // Assert
    EXPECT_EQ(texture_ptr, nullptr);
}

TEST_F(AssetManagerTestFixture, LoadFunction_InvalidPathExt_Returns_NullPointer) {
    // Arrange
    const char* invalid_path = "penguin_cute.svg";

    // Act
    std::shared_ptr<Texture> texture_ptr = content_ptr->load(invalid_path);


    // Assert
    EXPECT_EQ(texture_ptr, nullptr);
}