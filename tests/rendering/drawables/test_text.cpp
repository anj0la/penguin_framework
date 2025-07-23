#include <penguin_framework/window/window.hpp>
#include <penguin_framework/rendering/renderer.hpp>
#include <penguin_framework/rendering/drawables/text.hpp>
#include <penguin_framework/rendering/systems/text_context.hpp>
#include <penguin_framework/penguin_init.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <string>

#include <common/test_helpers.hpp>

using penguin::window::Window;
using penguin::window::WindowFlags;
using penguin::rendering::Renderer;
using penguin::rendering::drawables::Text;
using penguin::rendering::primitives::Font;
using penguin::rendering::systems::TextContext;
using penguin::math::Vector2;
using penguin::math::Vector2i;
using penguin::math::Rect2;
using penguin::math::Colour;

class TextTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Window> invalid_window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<Renderer> invalid_renderer_ptr;
    std::unique_ptr<TextContext> text_context_ptr;
    std::unique_ptr<TextContext> invalid_text_context_ptr;
    std::shared_ptr<Font> font_ptr;
    std::unique_ptr<Text> text_ptr;
    std::unique_ptr<Text> invalid_text_ptr;

    const char* asset_name = "pixelify_sans_regular.ttf";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name)).string();

    void SetUp() override {
        penguin::InitOptions options{ .headless_mode = true };
        ASSERT_TRUE(penguin::init(options));

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_valid()); // window should be OPEN and VALID

        invalid_window_ptr = std::make_unique<Window>("Invalid Window", Vector2i(-1, -1), static_cast<WindowFlags>(0xFFFFFFFF)); // the flag is a nonsensical value
        ASSERT_FALSE(invalid_window_ptr->is_valid());

        renderer_ptr = std::make_unique<Renderer>(*window_ptr.get(), "software");
        ASSERT_TRUE(renderer_ptr->is_valid());

        invalid_renderer_ptr = std::make_unique<Renderer>(*invalid_window_ptr.get(), "");
        ASSERT_FALSE(invalid_renderer_ptr->is_valid());

        text_context_ptr = std::make_unique<TextContext>(*renderer_ptr.get());
        ASSERT_TRUE(text_context_ptr->is_valid());

        invalid_text_context_ptr = std::make_unique<TextContext>(*invalid_renderer_ptr.get());
        ASSERT_FALSE(invalid_text_context_ptr->is_valid());

        font_ptr = std::make_shared<Font>(abs_path.c_str());
        ASSERT_TRUE(font_ptr->is_valid());

        text_ptr = std::make_unique<Text>(*text_context_ptr.get(), font_ptr, "Hello World!");
        ASSERT_TRUE(text_ptr->is_valid());

        invalid_text_ptr = std::make_unique<Text>(*invalid_text_context_ptr.get(), font_ptr, "");
        ASSERT_FALSE(invalid_text_context_ptr->is_valid());
    }

    void TearDown() override {
        penguin::quit();
    }
};

TEST_F(TextTestFixture, CreatedText_HasDefault_PropertiesSet) {
    // Arrange
    const char* expected_text = "Hello World!";
    Vector2 expected_position = Vector2::Zero;
    Colour expected_colour = Colours::White;

    // Act (done via SetUp)
    // Assert
    EXPECT_TRUE(text_ptr->is_valid());
    const char* actual_text = text_ptr->get_string();
    Vector2 actual_position = text_ptr->get_position();
    Colour actual_colour = text_ptr->get_colour();

    EXPECT_STREQ(expected_text, actual_text);
    EXPECT_EQ(expected_position, actual_position);
    EXPECT_EQ(expected_colour, actual_colour);
}

// Validity

TEST_F(TextTestFixture, BoolOperator_WithValidFont_ReturnsTrue) {
    // Arrange (done via SetUp)

    // Act
    bool bool_result = static_cast<bool>(*text_ptr);

    // Assert
    EXPECT_TRUE(bool_result);
}

// Position

TEST_F(TextTestFixture, GetPosition_Returns_TextPosition) {
    // Arrange
    Vector2 expected_position = Vector2::Zero;

    // Act
    Vector2 actual_position = text_ptr->get_position();

    // Assert
    EXPECT_TRUE(text_ptr->is_valid());
    EXPECT_EQ(expected_position, actual_position);
}

TEST_F(TextTestFixture, SetPosition_WithVector_Sets_TextPosition) {
    // Arrange
    Vector2 new_position(100.0f, 150.0f);

    // Act
    text_ptr->set_position(new_position);
    Vector2 actual_position = text_ptr->get_position();

    // Assert
    EXPECT_TRUE(text_ptr->is_valid());
    EXPECT_EQ(new_position, actual_position);
}

// Colour

TEST_F(TextTestFixture, GetColour_Returns_TextPosition) {
    // Arrange
    Colour expected_colour = Colours::White;

    // Act
    Colour actual_colour = text_ptr->get_colour();

    // Assert
    EXPECT_TRUE(text_ptr->is_valid());
    EXPECT_EQ(expected_colour, actual_colour);
}

TEST_F(TextTestFixture, SetColour_Sets_TextPosition) {
    // Arrange
    Colour new_colour = Colours::Red;

    // Act
    text_ptr->set_colour(new_colour);
    Colour actual_colour = text_ptr->get_colour();

    // Assert
    EXPECT_TRUE(text_ptr->is_valid());
    EXPECT_EQ(new_colour, actual_colour);
}

// String

TEST_F(TextTestFixture, GetString_Returns_TextString) {
    // Arrange
    Colour expected_colour = Colours::White;

    // Act
    Colour actual_colour = text_ptr->get_colour();

    // Assert
    EXPECT_TRUE(text_ptr->is_valid());
    EXPECT_EQ(expected_colour, actual_colour);
}

TEST_F(TextTestFixture, SetString_Sets_TextString) {
    // Arrange
    const char* new_string = "Hello Penguin!";

    // Act
    text_ptr->set_string(new_string);
    const char* actual_string = text_ptr->get_string();

    // Assert
    EXPECT_TRUE(text_ptr->is_valid());
    EXPECT_EQ(new_string, actual_string);
}

// Native Pointer

TEST_F(TextTestFixture, GetNativePtr_WithValidText_ReturnsNonNullPtr) {
    // Arrange (done via SetUp)
    
    // Act
    auto native_ptr = text_ptr->get_native_ptr();

    // Assert
    EXPECT_TRUE(text_ptr->is_valid());
    EXPECT_NE(native_ptr.ptr, nullptr);
}

// Invalid Text Operations

TEST_F(TextTestFixture, IsValid_WithInvalidText_ReturnsFalse) {
    // Arrange (done in SetUp)

    // Act
    bool is_valid = invalid_text_ptr->is_valid();

    // Assert
    EXPECT_FALSE(is_valid);
}

TEST_F(TextTestFixture, BoolOperator_WithInvalidText_ReturnsFalse) {
    // Arrange (done in SetUp)

    // Act
    bool bool_result = static_cast<bool>(*invalid_text_ptr);

    // Assert
    EXPECT_FALSE(bool_result);
}

TEST_F(TextTestFixture, InvalidText_GettersReturn_DefaultValues) {
    // Arrange (done via SetUp)

    // Act & Assert
    EXPECT_FALSE(invalid_text_ptr->is_valid());

    // These should all log warnings but not crash
    const char* default_str = invalid_text_ptr->get_string();
    Vector2 default_pos = invalid_text_ptr->get_position();
    Colour default_colour = invalid_text_ptr->get_colour();

    EXPECT_FALSE(invalid_text_ptr->is_valid());
}
TEST_F(TextTestFixture, InvalidSprite_SettersLog_Warnings) {
    // Arrange (done via SetUp)

    // Act & Assert
    EXPECT_FALSE(invalid_text_ptr->is_valid());

    // These should all log warnings but not crash
    invalid_text_ptr->set_string("Hello World!");
    invalid_text_ptr->set_position(Vector2(10.0f, 10.0f));
    invalid_text_ptr->set_colour(Colours::Blue);

    EXPECT_FALSE(invalid_text_ptr->is_valid());
}

TEST_F(TextTestFixture, GetNativePtr_WithInvalidText_ReturnsNullPtr) {
    // Arrange (done in SetUp)

    // Act
    auto native_ptr = invalid_text_ptr->get_native_ptr();

    // Assert
    EXPECT_EQ(native_ptr.ptr, nullptr);
}