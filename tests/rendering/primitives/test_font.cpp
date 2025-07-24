#include <penguin_framework/window/window.hpp>
#include <penguin_framework/rendering/renderer.hpp>
#include <penguin_framework/rendering/primitives/font.hpp>
#include <penguin_framework/penguin_init.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <string>

#include <common/test_helpers.hpp>

using penguin::window::Window;
using penguin::window::WindowFlags;
using penguin::rendering::Renderer;
using penguin::rendering::primitives::Font;
using penguin::math::Vector2i;

class FontTestFixture : public ::testing::Test {
protected:
    //std::unique_ptr<Window> window_ptr;
    //std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<Font> font_ptr;
    std::unique_ptr<Font> invalid_font_ptr;

    const char* asset_name = "pixelify_sans_regular.ttf";
    const char* invalid_asset_name = "roboto.ttf";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name)).string();
    std::string invalid_abs_path = std::filesystem::absolute(get_test_asset_path(invalid_asset_name)).string();

    void SetUp() override {
        penguin::InitOptions options{ .headless_mode = true };
        ASSERT_TRUE(penguin::init(options));

        font_ptr = std::make_unique<Font>(abs_path.c_str());
        ASSERT_TRUE(font_ptr->is_valid());

        invalid_font_ptr = std::make_unique<Font>(invalid_abs_path.c_str());
        ASSERT_FALSE(invalid_font_ptr->is_valid());
    }

    void TearDown() override {
        // Manually destroy resources
        invalid_font_ptr.reset();
        font_ptr.reset();

        // Safe to quit
        penguin::quit();
    }
};

TEST_F(FontTestFixture, Constructor_ValidPath_CreatesFont) {
    // Arrange
    float expected_size = 12.0f;
    int expected_outline = 1;

    // Act (done via SetUp)

    // Assert
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

// Validity

TEST_F(FontTestFixture, BoolOperator_WithValidFont_ReturnsTrue) {
    // Arrange (done via SetUp)

    // Act
    bool bool_result = static_cast<bool>(*font_ptr);

    // Assert
    EXPECT_TRUE(bool_result);
}

// Size

TEST_F(FontTestFixture, GetSize_WithValidFont_ReturnsCorrectSize) {
    // Arrange
    float expected_size = 12.0f;

    // Act
    float actual_size = font_ptr->get_size();

    // Assert
    EXPECT_TRUE(font_ptr->is_valid());
    EXPECT_FLOAT_EQ(actual_size, expected_size);
}

TEST_F(FontTestFixture, SetSize_WithValidFont_ChangesSize) {
    // Arrange
    float expected_size = 14.0f;
    
    // Act
    font_ptr->set_size(14.0f);

    // Assert
    EXPECT_TRUE(font_ptr->is_valid());
    float actual_size = font_ptr->get_size();
    EXPECT_FLOAT_EQ(actual_size, expected_size);
}

// Outline

TEST_F(FontTestFixture, GetOutline_WithValidFont_ReturnsCorrectOutline) {
    // Arrange
    int expected_outline = 1;

    // Act
    int actual_outline = font_ptr->get_outline();

    // Assert
    EXPECT_TRUE(font_ptr->is_valid());
    EXPECT_EQ(actual_outline, expected_outline);
}

TEST_F(FontTestFixture, SetOutline_WithValidFont_ChangesOutline) {
    // Arrange
    int expected_outline = 4;

    // Act
    font_ptr->set_outline(4);

    // Assert
    EXPECT_TRUE(font_ptr->is_valid());
    int actual_outline = font_ptr->get_outline();
    EXPECT_EQ(actual_outline, expected_outline);
}

// Styles

TEST_F(FontTestFixture, MakeBold_WithValidFont_ChangesFontStyle) {
    // Arrange (done via SetUp)

    // Act
    font_ptr->make_bold();

    // Assert
    EXPECT_TRUE(font_ptr->is_valid());
    EXPECT_TRUE(font_ptr->is_bold());

    EXPECT_FALSE(font_ptr->is_normal());
    EXPECT_FALSE(font_ptr->is_italic());
    EXPECT_FALSE(font_ptr->is_underline());
    EXPECT_FALSE(font_ptr->is_strikethrough());
}

TEST_F(FontTestFixture, MakeItalic_WithValidFont_ChangesFontStyle) {
    // Arrange (done via SetUp)

    // Act
    font_ptr->make_italic();

    // Assert
    EXPECT_TRUE(font_ptr->is_valid());
    EXPECT_TRUE(font_ptr->is_italic());

    EXPECT_FALSE(font_ptr->is_normal());
    EXPECT_FALSE(font_ptr->is_bold());
    EXPECT_FALSE(font_ptr->is_underline());
    EXPECT_FALSE(font_ptr->is_strikethrough());
}

TEST_F(FontTestFixture, MakeUnderline_WithValidFont_ChangesFontStyle) {
    // Arrange (done via SetUp)

    // Act
    font_ptr->make_underline();

    // Assert
    EXPECT_TRUE(font_ptr->is_valid());
    EXPECT_TRUE(font_ptr->is_underline());

    EXPECT_FALSE(font_ptr->is_normal());
    EXPECT_FALSE(font_ptr->is_bold());
    EXPECT_FALSE(font_ptr->is_italic());
    EXPECT_FALSE(font_ptr->is_strikethrough());
}

TEST_F(FontTestFixture, MakeStrikethrough_WithValidFont_ChangesFontStyle) {
    // Arrange (done via SetUp)

    // Act
    font_ptr->make_strikethrough();

    // Assert
    EXPECT_TRUE(font_ptr->is_valid());
    EXPECT_TRUE(font_ptr->is_strikethrough());

    EXPECT_FALSE(font_ptr->is_normal());
    EXPECT_FALSE(font_ptr->is_bold());
    EXPECT_FALSE(font_ptr->is_italic());
    EXPECT_FALSE(font_ptr->is_underline());
}

TEST_F(FontTestFixture, MakeNormal_WithValidFont_ChangesFontStyle) {
    // Arrange (done via SetUp)

    // Act
    font_ptr->make_normal();

    // Assert
    EXPECT_TRUE(font_ptr->is_valid());
    EXPECT_TRUE(font_ptr->is_normal());

    EXPECT_FALSE(font_ptr->is_bold());
    EXPECT_FALSE(font_ptr->is_italic());
    EXPECT_FALSE(font_ptr->is_underline());
    EXPECT_FALSE(font_ptr->is_strikethrough());
}

TEST_F(FontTestFixture, Clear_WithValidFont_ClearsFontStyles) {
    // Arrange (done via SetUp)

    // Act
    font_ptr->clear();

    // Assert
    EXPECT_TRUE(font_ptr->is_valid());
    EXPECT_TRUE(font_ptr->is_normal());

    EXPECT_FALSE(font_ptr->is_bold());
    EXPECT_FALSE(font_ptr->is_italic());
    EXPECT_FALSE(font_ptr->is_underline());
    EXPECT_FALSE(font_ptr->is_strikethrough());
}

// Native Pointer

TEST_F(FontTestFixture, GetNativePtr_WithValidFont_ReturnsNonNullPtr) {
    // Arrange (done via SetUp)

    // Act
    auto native_ptr = font_ptr->get_native_ptr();

    // Assert
    EXPECT_TRUE(font_ptr->is_valid());
    EXPECT_NE(native_ptr.ptr, nullptr);
}

TEST_F(FontTestFixture, GetNativePtr_WithInvalidFont_ReturnsNullPtr) {
    // Arrange (done via SetUp)

    // Act
    auto native_ptr = invalid_font_ptr->get_native_ptr();

    // Assert
    EXPECT_FALSE(invalid_font_ptr->is_valid());
    EXPECT_EQ(native_ptr.ptr, nullptr);
}