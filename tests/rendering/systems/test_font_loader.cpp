#include <penguin_framework/window/window.hpp>
#include <penguin_framework/rendering/renderer.hpp>
#include <penguin_framework/rendering/primitives/font.hpp>
#include <penguin_framework/rendering/systems/font_loader.hpp>
#include <penguin_framework/penguin_init.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <filesystem>
#include <string>

#include <common/test_helpers.hpp>

using penguin::window::Window;
using penguin::window::WindowFlags;
using penguin::rendering::Renderer;
using penguin::rendering::systems::FontLoader;
using penguin::rendering::primitives::Font;
using penguin::math::Vector2i;

class FontLoaderTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<FontLoader> loader_ptr;

    const char* asset_name = "pixelify_sans_regular.ttf"; 
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name)).string();

    void SetUp() override {
        penguin::InitOptions options{ .headless_mode = true };
        ASSERT_TRUE(penguin::init(options));

        loader_ptr = std::make_unique<FontLoader>();
        ASSERT_TRUE(loader_ptr->is_valid());
    }

    void TearDown() override {
        // Manually destroy resources in reverse order
        loader_ptr.reset();

        // Safe to quit
        penguin::quit();
    }
};

// Validity
// Note: as we aren't passing any parameters, if the loader is constructed, then it's guaranteed to be valid all the time
// This may change in a later update

TEST_F(FontLoaderTestFixture, IsValid_WithValidLoader_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool is_valid = loader_ptr->is_valid();

    // Assert
    EXPECT_TRUE(is_valid);
}

TEST_F(FontLoaderTestFixture, BoolOperator_WithValidLoader_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool bool_result = static_cast<bool>(*loader_ptr);

    // Assert
    EXPECT_TRUE(bool_result);
}

// Load
// Note: No need to test for invalid path as FontLoader is guaranteed to have a valid path

TEST_F(FontLoaderTestFixture, LoadFunction_WithValidParameters_ReturnsValidFont) {
    // Arrange
    float expected_size = 12.0f;
    int expected_outline = 1;

    // Act
    std::shared_ptr<Font> font_ptr = loader_ptr->load(abs_path.c_str());

    // Assert
    EXPECT_TRUE(loader_ptr->is_valid());
    EXPECT_TRUE(font_ptr->is_valid());

    float actual_size = font_ptr->get_size();
    int actual_outline = font_ptr->get_outline();

    EXPECT_FLOAT_EQ(expected_size, actual_size);
    EXPECT_EQ(expected_outline, actual_outline);
    EXPECT_TRUE(font_ptr->is_normal());
    EXPECT_FALSE(font_ptr->is_bold());
    EXPECT_FALSE(font_ptr->is_italic());
    EXPECT_FALSE(font_ptr->is_underline());
    EXPECT_FALSE(font_ptr->is_strikethrough());
}