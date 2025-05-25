#include <penguin_framework/core/window/penguin_window.hpp>
#include <penguin_framework/core/rendering/penguin_renderer.hpp>
#include <penguin_framework/core/rendering/primitives/penguin_sprite.hpp>
#include <SDL3/SDL.h>
#include <gtest/gtest.h>
#include <memory>
#include <filesystem>
#include <string>

using penguin::core::window::Window;
using penguin::core::window::WindowFlags;
using penguin::core::rendering::Renderer;
using penguin::core::rendering::primitives::Sprite;
using penguin::core::rendering::primitives::Texture;
using penguin::core::rendering::primitives::FlipMode;

// Helper Functions

std::filesystem::path get_test_asset_path(const char* name) {
    return std::filesystem::path(TEST_ASSETS_DIR) / name;
}

// Setting Up the Test Suite

class SpriteTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    std::shared_ptr<Texture> texture_ptr;
    std::unique_ptr<Sprite> sprite_ptr;
    String asset_name = "penguin_cute.bmp";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name.c_str())).string();

    void SetUp() override {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
        ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError();

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_open());

        renderer_ptr = std::make_unique<Renderer>(window_ptr.get()->get_native_ptr(), "software");
        ASSERT_NE(renderer_ptr->get_native_ptr().as<SDL_Renderer>(), nullptr);

        texture_ptr = std::make_shared<Texture>(renderer_ptr->get_native_ptr(), abs_path.c_str());
        sprite_ptr = std::make_unique<Sprite>(texture_ptr);
        ASSERT_NE(sprite_ptr, nullptr);
        ASSERT_NE(sprite_ptr->get_native_ptr().ptr, nullptr); // equivalent to texture_obj->get_native_ptr()
    }

    void TearDown() override {
        SDL_Quit();
    }
};

TEST_F(SpriteTestFixture, CreatedSprite_HasDefault_PropertiesSet) {
    // Arrange
    Vector2 expected_position(0.0f, 0.0f);
    Vector2 expected_size(362.0f, 362.0f);
    Vector2i expected_size_i(362, 362);
    Vector2 expected_scale(1.0f, 1.0f);
    double expected_angle = 0.0f;
    Vector2 expected_anchor_point(0.5f, 0.5f);
    bool expected_visiblility = true;
    FlipMode expected_mode = FlipMode::None;
    Colour expected_tint = Colours::NoTint;
    Rect2 expected_bounding_box(expected_position, expected_size); // The size of the penguin_cute image is 362 x 362 pixels

    // Act (Implict via Construction)
    // Assert - Validate that object was created
    ASSERT_NE(sprite_ptr, nullptr);
    ASSERT_NE(sprite_ptr->get_native_ptr().ptr, nullptr); // equivalent to texture_obj->get_native_ptr()

    // Assert - Validate all variables are set
    EXPECT_EQ(expected_position, sprite_ptr->get_position());

    Vector2i texture_size = sprite_ptr->get_size();
    ASSERT_GT(texture_size.x, 0);
    ASSERT_GT(texture_size.y, 0);
    EXPECT_EQ(texture_size.x, expected_size_i.x);
    EXPECT_EQ(texture_size.y, expected_size_i.y);

    EXPECT_EQ(expected_scale, sprite_ptr->get_scale());
    EXPECT_EQ(expected_angle, sprite_ptr->get_angle());
    EXPECT_EQ(expected_anchor_point, sprite_ptr->get_anchor_point());
    EXPECT_EQ(expected_visiblility, sprite_ptr->is_hidden());
    EXPECT_EQ(expected_mode, sprite_ptr->get_flip_mode());
    EXPECT_EQ(expected_tint, sprite_ptr->get_colour_tint());
    EXPECT_EQ(expected_bounding_box, sprite_ptr->get_bounding_box());
}

// Getters

TEST_F(SpriteTestFixture, GetPosition_Returns_SpritePosition) {
    // Arrange
    Vector2 expected_position(0.0f, 0.0f);

    // Act
    Vector2 actual_position = sprite_ptr->get_position();

    // Assert
    EXPECT_FLOAT_EQ(expected_position.x, actual_position.x);
    EXPECT_FLOAT_EQ(expected_position.y, actual_position.y);
}

TEST_F(SpriteTestFixture, GetSize_Returns_SpriteSize) {
    // Arrange
    Vector2i expected_size(362, 362);

    // Act
    Vector2i actual_size = sprite_ptr->get_size();

    // Assert
    EXPECT_EQ(expected_size.x, actual_size.x);
    EXPECT_EQ(expected_size.y, actual_size.y);
}

TEST_F(SpriteTestFixture, GetScale_Returns_SpriteScale) {
    // Arrange
    Vector2 expected_scale(1.0f, 1.0f);

    // Act
    Vector2 actual_scale = sprite_ptr->get_scale();

    // Assert
    EXPECT_FLOAT_EQ(expected_scale.x, actual_scale.x);
    EXPECT_FLOAT_EQ(expected_scale.y, actual_scale.y);
}

TEST_F(SpriteTestFixture, GetAngle_Returns_SpriteAngle) {
    // Arrange
    double expected_angle = 0.0f;
  
    // Act
    double actual_angle = sprite_ptr->get_angle();

    // Assert
    EXPECT_FLOAT_EQ(expected_angle, actual_angle);
}

TEST_F(SpriteTestFixture, GetAnchorPoint_Returns_SpriteAnchorPoint) {
    // Arrange
    Vector2 expected_anchor_point(0.5f, 0.5f);

    // Act
    Vector2 actual_anchor_point = sprite_ptr->get_anchor_point();

    // Assert
    EXPECT_FLOAT_EQ(expected_anchor_point.x, actual_anchor_point.x);
    EXPECT_FLOAT_EQ(expected_anchor_point.y, actual_anchor_point.y);
}

TEST_F(SpriteTestFixture, GetVisibility_Returns_SpriteVisibility) {
    // Arrange
    bool expected_visiblility = true;

    // Act
    bool actual_visibility = sprite_ptr->is_hidden();

    // Assert
    EXPECT_TRUE(actual_visibility);
    EXPECT_EQ(expected_visiblility, actual_visibility);
}

TEST_F(SpriteTestFixture, GetFlipMode_Returns_SpriteFlipMode) {
    // Arrange
    FlipMode expected_mode = FlipMode::None;

    // Act
    FlipMode actual_mode = sprite_ptr->get_flip_mode();

    // Assert
    EXPECT_EQ(expected_mode, actual_mode);
}

TEST_F(SpriteTestFixture, GetColourTint_Returns_SpriteColourTint) {
    // Arrange
    Colour expected_tint = Colours::NoTint;

    // Act
    Colour actual_tint = sprite_ptr->get_colour_tint();

    // Assert
    EXPECT_EQ(expected_tint, actual_tint);
}

TEST_F(SpriteTestFixture, GetBoundingBox_Returns_SpriteBoundingBox) {
    // Arrange
    Vector2 expected_position(0.0f, 0.0f);
    Vector2 expected_size(362.0f, 362.0f);    
    Rect2 expected_bounding_box(expected_position, expected_size); // The size of the penguin_cute image is 362 x 362 pixels

    // Act
    Rect2 actual_bounding_box = sprite_ptr->get_bounding_box();

    // Assert
    EXPECT_EQ(expected_position.x, actual_bounding_box.position.x);
    EXPECT_EQ(expected_position.y, actual_bounding_box.position.y);
    EXPECT_EQ(expected_size.x, actual_bounding_box.size.x);
    EXPECT_EQ(expected_size.y, actual_bounding_box.size.y);
}

// Setters

TEST_F(SpriteTestFixture, SetPosition_Sets_SpritePosition) {
    // Arrange
    Vector2 new_position(100.0f, 100.0f);
    Vector2 expected_position = new_position;
    EXPECT_NE(new_position, sprite_ptr->get_position()); // Ensure that the position is not equal to the new position

    // Act
    sprite_ptr->set_position(new_position);
    Vector2 actual_position = sprite_ptr->get_position();

    // Assert
    EXPECT_FLOAT_EQ(expected_position.x, actual_position.x);
    EXPECT_FLOAT_EQ(expected_position.y, actual_position.y);
}

TEST_F(SpriteTestFixture, SetScale_Sets_SpriteScale) {
    // Arrange
    Vector2 new_scale(2.0f, 2.0f);
    Vector2 expected_scale = new_scale;

    // Act
    sprite_ptr->set_scale(new_scale);
    Vector2 actual_scale = sprite_ptr->get_scale();

    // Assert
    EXPECT_FLOAT_EQ(expected_scale.x, actual_scale.x);
    EXPECT_FLOAT_EQ(expected_scale.y, actual_scale.y);
}

TEST_F(SpriteTestFixture, SetAngle_Sets_SpriteAngle) {
    // Arrange
    double new_angle = 90.0f;
    double expected_angle = new_angle;

    // Act
    sprite_ptr->set_angle(new_angle);
    double actual_angle = sprite_ptr->get_angle();

    // Assert
    EXPECT_FLOAT_EQ(expected_angle, actual_angle);
}

TEST_F(SpriteTestFixture, SetAnchorPoint_Sets_SpriteAnchorPoint) {
    // Arrange
    Vector2 new_anchor_point(0.0f, 0.50);
    Vector2 expected_anchor_point = new_anchor_point;

    // Act
    sprite_ptr->set_anchor_point(new_anchor_point);
    Vector2 actual_anchor_point = sprite_ptr->get_anchor_point();

    // Assert
    EXPECT_FLOAT_EQ(expected_anchor_point.x, actual_anchor_point.x);
    EXPECT_FLOAT_EQ(expected_anchor_point.y, actual_anchor_point.y);
}

TEST_F(SpriteTestFixture, Hide_Makes_SpriteHidden) {
    // Arrange (Implicit via constructor)
    // Act
    sprite_ptr->hide();
    bool actual_visibility = sprite_ptr->is_hidden();

    // Assert
    EXPECT_TRUE(actual_visibility);
}

TEST_F(SpriteTestFixture, Show_Makes_SpriteVisible) {
    // Arrange (Implicit via constructor)
    // Act
    sprite_ptr->show();
    bool actual_visibility = sprite_ptr->is_hidden();

    // Assert
    EXPECT_FALSE(actual_visibility);
}

TEST_F(SpriteTestFixture, SetFlipMode_Sets_SpriteFlipMode) {
    // Arrange
    FlipMode new_mode = FlipMode::Horizontal;
    FlipMode expected_mode = new_mode;

    // Act
    sprite_ptr->set_flip_mode(new_mode);
    FlipMode actual_mode = sprite_ptr->get_flip_mode();

    // Assert
    EXPECT_EQ(expected_mode, actual_mode);
}

TEST_F(SpriteTestFixture, SetColourTint_Sets_SpriteColourTint) {
    // Arrange
    Colour new_tint = Colours::Red;
    Colour expected_tint = new_tint;

    // Act
    sprite_ptr->set_colour_tint(new_tint);
    Colour actual_tint = sprite_ptr->get_colour_tint();

    // Assert
    EXPECT_EQ(expected_tint, actual_tint);
}

TEST_F(SpriteTestFixture, SetBoundingBox_Sets_SpriteBoundingBox) {
    // Arrange
    Vector2 new_position(200.0f, 200.0f);
    Vector2 expected_size(362.0f, 362.0f);
    Vector2 expected_position = new_position;
    Rect2 new_bounding_box(new_position, expected_size); // The size of the penguin_cute image is 362 x 362 pixels
    Rect2 expected_bounding_box = new_bounding_box;

    // Act
    sprite_ptr->set_bounding_box(new_bounding_box);
    Rect2 actual_bounding_box = sprite_ptr->get_bounding_box();

    // Assert
    EXPECT_EQ(expected_position.x, actual_bounding_box.position.x);
    EXPECT_EQ(expected_position.y, actual_bounding_box.position.y);
    EXPECT_EQ(expected_size.x, actual_bounding_box.size.x);
    EXPECT_EQ(expected_size.y, actual_bounding_box.size.y);
}
