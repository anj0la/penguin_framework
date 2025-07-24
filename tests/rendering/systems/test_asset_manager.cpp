#include <penguin_framework/window/window.hpp>
#include <penguin_framework/rendering/renderer.hpp>
#include <penguin_framework/rendering/primitives/texture.hpp>
#include <penguin_framework/rendering/primitives/font.hpp>
#include <penguin_framework/rendering/systems/asset_manager.hpp>
#include <penguin_framework/penguin_init.hpp>
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
using penguin::rendering::primitives::Font;
using penguin::math::Vector2i;

class AssetManagerTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Window> invalid_window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<AssetManager> content_ptr;

    std::unique_ptr<Renderer> invalid_renderer_ptr;
    std::unique_ptr<AssetManager> invalid_content_ptr;
    std::unique_ptr<AssetManager> valid_content_ptr;

    const char* asset_name = "penguin_cute.bmp";
    const char* font_asset_name = "pixelify_sans_regular.ttf";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name)).string();
    std::string font_abs_path = std::filesystem::absolute(get_test_asset_path(font_asset_name)).string();

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

        content_ptr = std::make_unique<AssetManager>(*renderer_ptr);
        ASSERT_TRUE(content_ptr->is_valid());

        invalid_content_ptr = std::make_unique<AssetManager>(*invalid_renderer_ptr);
        ASSERT_FALSE(invalid_content_ptr->is_valid());
    }

    void TearDown() override {
        // Manually destroy resources in reverse order
        invalid_content_ptr.reset();
        content_ptr.reset();
        invalid_renderer_ptr.reset();
        renderer_ptr.reset();
        invalid_window_ptr.reset();
        window_ptr.reset();

        // Safe to quit
        penguin::quit();
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

// Load Texture

TEST_F(AssetManagerTestFixture, LoadTexture_WithValidPath_ReturnsValidTexture) {
    // Arrange & Act
    std::shared_ptr<Texture> texture_ptr = content_ptr->load_texture(abs_path.c_str());

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

// Invalid Load Texture

TEST_F(AssetManagerTestFixture, LoadTexture_WithInvalidAssetManager_ReturnsNullPtr) {
    // Arrange & Act
    std::shared_ptr<Texture> texture_ptr = invalid_content_ptr->load_texture(abs_path.c_str());

    // Assert
    EXPECT_FALSE(invalid_content_ptr->is_valid());
    EXPECT_EQ(texture_ptr, nullptr);
}

TEST_F(AssetManagerTestFixture, LoadTexture_WithInvalidPath_ReturnsNullPtr) {
    // Arrange
    const char* invalid_path = "cute_img.png";
    std::string invalid_abs_path = std::filesystem::absolute(get_test_asset_path(invalid_path)).string();

    // Act
    std::shared_ptr<Texture> texture_ptr = content_ptr->load_texture(invalid_abs_path.c_str());

    // Assert
    EXPECT_TRUE(content_ptr->is_valid());
    EXPECT_EQ(texture_ptr, nullptr);
}

TEST_F(AssetManagerTestFixture, LoadTexture_WithInvalidPathExt_ReturnsNullPtr) {
    // Arrange
    const char* invalid_path = "penguin_cute.pcx";
    std::string invalid_abs_path = std::filesystem::absolute(get_test_asset_path(invalid_path)).string();

    // Act
    std::shared_ptr<Texture> texture_ptr = content_ptr->load_texture(invalid_abs_path.c_str());

    // Assert
    EXPECT_TRUE(content_ptr->is_valid());
    EXPECT_EQ(texture_ptr, nullptr);
}

// Load Font

TEST_F(AssetManagerTestFixture, LoadFont_WithValidPath_ReturnsValidTexture) {
    // Arrange & Act
    std::shared_ptr<Font> font_ptr = content_ptr->load_font(font_abs_path.c_str());
    float expected_size = 12.0f;
    int expected_outline = 1;

    // Assert
    EXPECT_TRUE(content_ptr->is_valid());
    EXPECT_TRUE(font_ptr->is_valid());

    float actual_size = font_ptr->get_size();
    int actual_outline = font_ptr->get_outline();

    EXPECT_FLOAT_EQ(actual_size, expected_size);
    EXPECT_EQ(actual_outline, expected_outline);
    EXPECT_TRUE(font_ptr->is_normal());
    EXPECT_FALSE(font_ptr->is_bold());
    EXPECT_FALSE(font_ptr->is_italic());
    EXPECT_FALSE(font_ptr->is_underline());
    EXPECT_FALSE(font_ptr->is_strikethrough());
}

// Invalid Load Font

TEST_F(AssetManagerTestFixture, LoadFont_WithInvalidAssetManager_ReturnsNullPtr) {
    // Arrange & Act
    std::shared_ptr<Font> font_ptr = invalid_content_ptr->load_font(font_abs_path.c_str());

    // Assert
    EXPECT_FALSE(invalid_content_ptr->is_valid());
    EXPECT_EQ(font_ptr, nullptr);
}

TEST_F(AssetManagerTestFixture, LoadFont_WithInvalidPath_ReturnsNullPtr) {
    // Arrange
    const char* invalid_path = "roboto.ttf";
    std::string invalid_abs_path = std::filesystem::absolute(get_test_asset_path(invalid_path)).string();

    // Act
    std::shared_ptr<Font> font_ptr = content_ptr->load_font(invalid_abs_path.c_str());

    // Assert
    EXPECT_TRUE(content_ptr->is_valid());
    EXPECT_EQ(font_ptr, nullptr);
}

TEST_F(AssetManagerTestFixture, LoadFont_WithInvalidPathExt_ReturnsNullPtr) {
    // Arrange
    const char* invalid_path = "pixelify_sans_regular.font";
    std::string invalid_abs_path = std::filesystem::absolute(get_test_asset_path(invalid_path)).string();

    // Act
    std::shared_ptr<Font> font_ptr = content_ptr->load_font(invalid_abs_path.c_str());

    // Assert
    EXPECT_TRUE(content_ptr->is_valid());
    EXPECT_EQ(font_ptr, nullptr);
}