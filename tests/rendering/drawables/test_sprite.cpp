#include <penguin_framework/window/window.hpp>
#include <penguin_framework/rendering/renderer.hpp>
#include <penguin_framework/rendering/drawables/sprite.hpp>
#include <penguin_framework/penguin_init.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <string>

#include <common/test_helpers.hpp>

using penguin::window::Window;
using penguin::window::WindowFlags;
using penguin::rendering::Renderer;
using penguin::rendering::drawables::Sprite;
using penguin::rendering::primitives::Texture;
using penguin::rendering::primitives::FlipMode;
using penguin::math::Vector2;
using penguin::math::Vector2i;
using penguin::math::Rect2;
using penguin::math::Colour;

class SpriteTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    std::shared_ptr<Texture> texture_ptr;
    std::unique_ptr<Sprite> sprite_ptr;
    std::unique_ptr<Sprite> second_sprite_ptr;
    std::unique_ptr<Sprite> invalid_sprite_ptr;
    const char* asset_name = "penguin_cute.bmp";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name)).string();

    void SetUp() override {
        penguin::InitOptions options{ .headless_mode = true };
        ASSERT_TRUE(penguin::init(options));

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_valid()); // window should be OPEN and VALID

        renderer_ptr = std::make_unique<Renderer>(*window_ptr, "software");
        ASSERT_TRUE(renderer_ptr->is_valid());

        texture_ptr = std::make_shared<Texture>(renderer_ptr->get_native_ptr(), abs_path.c_str());
        ASSERT_TRUE(texture_ptr->is_valid());

        sprite_ptr = std::make_unique<Sprite>(texture_ptr);
        ASSERT_TRUE(sprite_ptr->is_valid());

        second_sprite_ptr = std::make_unique<Sprite>(texture_ptr);
        ASSERT_TRUE(second_sprite_ptr->is_valid());

        invalid_sprite_ptr = std::make_unique<Sprite>(nullptr);
        ASSERT_FALSE(invalid_sprite_ptr->is_valid());
    }

    void TearDown() override {
        // Manually destroy resources in reverse order
        invalid_sprite_ptr.reset();
        second_sprite_ptr.reset();
        sprite_ptr.reset();
        texture_ptr.reset();
        renderer_ptr.reset();
        window_ptr.reset();

        // Safe to quit
        penguin::quit();
    }
};

// Properties

TEST_F(SpriteTestFixture, CreatedSprite_HasDefault_PropertiesSet) {
    // Arrange
    Vector2 expected_position(0.0f, 0.0f);
    Vector2i expected_size_i(362, 362);
    Vector2 expected_scale(1.0f, 1.0f);
    double expected_angle = 0.0f;
    Vector2 expected_anchor_point(0.5f, 0.5f);
    bool expected_visibility = true;
    FlipMode expected_mode = FlipMode::None;
    Rect2 expected_bounding_box(expected_position, Vector2(362.0f, 362.0f));

    // Act (Implicit via Construction)
    // Assert - Validate that object was created
    ASSERT_TRUE(sprite_ptr->is_valid());
    ASSERT_TRUE(*sprite_ptr); // Test bool operator

    // Assert - Validate all default properties
    EXPECT_EQ(expected_position, sprite_ptr->get_position());
    EXPECT_EQ(expected_size_i, sprite_ptr->get_size());
    EXPECT_EQ(expected_size_i.x, sprite_ptr->get_width());
    EXPECT_EQ(expected_size_i.y, sprite_ptr->get_height());
    EXPECT_EQ(expected_scale, sprite_ptr->get_scale_factor());
    EXPECT_EQ(expected_angle, sprite_ptr->get_angle());
    EXPECT_EQ(expected_anchor_point, sprite_ptr->get_anchor());
    EXPECT_EQ(expected_visibility, !sprite_ptr->is_hidden());
    EXPECT_EQ(expected_mode, sprite_ptr->get_flip_mode());
    EXPECT_EQ(expected_bounding_box, sprite_ptr->get_bounding_box());
    EXPECT_TRUE(sprite_ptr->has_texture());
}
TEST_F(SpriteTestFixture, Constructor_WithNullTexture_CreatesInvalidSprite) {
    // Arrange
    std::shared_ptr<Texture> null_texture = nullptr;

    // Act
    auto invalid_sprite_ptr = std::make_unique<Sprite>(null_texture);

    // Assert
    EXPECT_FALSE(invalid_sprite_ptr->is_valid());
    EXPECT_FALSE(*invalid_sprite_ptr);
}

// Validity

TEST_F(SpriteTestFixture, IsValid_WithValidSprite_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool is_valid = sprite_ptr->is_valid();

    // Assert
    EXPECT_TRUE(is_valid);
}

TEST_F(SpriteTestFixture, BoolOperator_WithInvalidSprite_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool bool_result = static_cast<bool>(*sprite_ptr);

    // Assert
    EXPECT_TRUE(bool_result);
}

// Position

TEST_F(SpriteTestFixture, GetPosition_Returns_SpritePosition) {
    // Arrange
    Vector2 expected_position(0.0f, 0.0f);

    // Act
    Vector2 actual_position = sprite_ptr->get_position();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_position, actual_position);
}
TEST_F(SpriteTestFixture, SetPosition_WithVector_Sets_SpritePosition) {
    // Arrange
    Vector2 new_position(100.0f, 150.0f);

    // Act
    sprite_ptr->set_position(new_position);
    Vector2 actual_position = sprite_ptr->get_position();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(new_position, actual_position);
}
TEST_F(SpriteTestFixture, SetPosition_WithFloats_Sets_SpritePosition) {
    // Arrange
    float x = 200.0f, y = 250.0f;
    Vector2 expected_position(x, y);

    // Act
    sprite_ptr->set_position(x, y);
    Vector2 actual_position = sprite_ptr->get_position();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_position, actual_position);
}

// Size
TEST_F(SpriteTestFixture, GetSize_Returns_SpriteSize) {
    // Arrange
    Vector2i expected_size(362, 362);

    // Act
    Vector2i actual_size = sprite_ptr->get_size();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_size, actual_size);
}
TEST_F(SpriteTestFixture, GetWidth_Returns_SpriteWidth) {
    // Arrange
    int expected_width = 362;

    // Act
    int actual_width = sprite_ptr->get_width();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_width, actual_width);
}
TEST_F(SpriteTestFixture, GetHeight_Returns_SpriteHeight) {
    // Arrange
    int expected_height = 362;

    // Act
    int actual_height = sprite_ptr->get_height();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_height, actual_height);
}

// Scale
TEST_F(SpriteTestFixture, GetScaleFactor_Returns_SpriteScale) {
    // Arrange
    Vector2 expected_scale(1.0f, 1.0f);

    // Act
    Vector2 actual_scale = sprite_ptr->get_scale_factor();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_scale, actual_scale);
}
TEST_F(SpriteTestFixture, SetScaleFactor_WithVector_Sets_SpriteScale) {
    // Arrange
    Vector2 new_scale(2.0f, 3.0f);

    // Act
    sprite_ptr->set_scale_factor(new_scale);
    Vector2 actual_scale = sprite_ptr->get_scale_factor();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(new_scale, actual_scale);
}
TEST_F(SpriteTestFixture, SetScaleFactor_WithFloats_Sets_SpriteScale) {
    // Arrange
    float x = 1.5f, y = 2.5f;
    Vector2 expected_scale(x, y);

    // Act
    sprite_ptr->set_scale_factor(x, y);
    Vector2 actual_scale = sprite_ptr->get_scale_factor();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_scale, actual_scale);
}

// Angle

TEST_F(SpriteTestFixture, GetAngle_Returns_SpriteAngle) {
    // Arrange
    double expected_angle = 0.0;

    // Act
    double actual_angle = sprite_ptr->get_angle();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_DOUBLE_EQ(expected_angle, actual_angle);
}

TEST_F(SpriteTestFixture, SetAngle_Sets_SpriteAngle) {
    // Arrange
    double new_angle = 45.0;

    // Act
    sprite_ptr->set_angle(new_angle);
    double actual_angle = sprite_ptr->get_angle();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_DOUBLE_EQ(new_angle, actual_angle);
}

// Anchor

TEST_F(SpriteTestFixture, GetAnchor_Returns_SpriteAnchor) {
    // Arrange
    Vector2 expected_anchor(0.5f, 0.5f);

    // Act
    Vector2 actual_anchor = sprite_ptr->get_anchor();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_anchor, actual_anchor);
}

TEST_F(SpriteTestFixture, SetAnchor_WithVector_Sets_SpriteAnchor) {
    // Arrange
    Vector2 new_anchor(0.0f, 1.0f);

    // Act
    sprite_ptr->set_anchor(new_anchor);
    Vector2 actual_anchor = sprite_ptr->get_anchor();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(new_anchor, actual_anchor);
}

TEST_F(SpriteTestFixture, SetAnchor_WithFloats_Sets_SpriteAnchor) {
    // Arrange
    float x = 0.25f, y = 0.75f;
    Vector2 expected_anchor(x, y);

    // Act
    sprite_ptr->set_anchor(x, y);
    Vector2 actual_anchor = sprite_ptr->get_anchor();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_anchor, actual_anchor);
}

TEST_F(SpriteTestFixture, SetAnchor_ClampsValues_ToBounds) {
    // Arrange
    Vector2 out_of_bounds_anchor(-1.0f, 2.0f);
    Vector2 expected_clamped_anchor(0.0f, 1.0f);

    // Act
    sprite_ptr->set_anchor(out_of_bounds_anchor);
    Vector2 actual_anchor = sprite_ptr->get_anchor();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_clamped_anchor, actual_anchor);
}

TEST_F(SpriteTestFixture, SetAnchor_WithFloats_ClampsValues_ToBounds) {
    // Arrange
    float x = -0.50f, y = 1.25f;
    Vector2 expected_anchor(0.0f, 1.0f);

    // Act
    sprite_ptr->set_anchor(x, y);
    Vector2 actual_anchor = sprite_ptr->get_anchor();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_anchor, actual_anchor);
}

// Visibility

TEST_F(SpriteTestFixture, IsHidden_Returns_SpriteVisibility) {
    // Arrange
    bool expected_hidden = false; // Default is visible

    // Act
    bool actual_hidden = sprite_ptr->is_hidden();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_hidden, actual_hidden);
}

TEST_F(SpriteTestFixture, Hide_Makes_SpriteHidden) {
    // Arrange
    EXPECT_FALSE(sprite_ptr->is_hidden()); // Ensure sprite starts visible

    // Act
    sprite_ptr->hide();
    bool actual_hidden = sprite_ptr->is_hidden();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_TRUE(actual_hidden);
}

TEST_F(SpriteTestFixture, Show_Makes_SpriteVisible) {
    // Arrange
    sprite_ptr->hide(); // First hide the sprite
    EXPECT_TRUE(sprite_ptr->is_hidden()); // Ensure sprite is hidden

    // Act
    sprite_ptr->show();
    bool actual_hidden = sprite_ptr->is_hidden();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_FALSE(actual_hidden);
}

// Flip Mode

TEST_F(SpriteTestFixture, GetFlipMode_Returns_SpriteFlipMode) {
    // Arrange
    FlipMode expected_mode = FlipMode::None;

    // Act
    FlipMode actual_mode = sprite_ptr->get_flip_mode();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_mode, actual_mode);
}

TEST_F(SpriteTestFixture, SetFlipMode_Sets_SpriteFlipMode) {
    // Arrange
    FlipMode new_mode = FlipMode::Horizontal;

    // Act
    sprite_ptr->set_flip_mode(new_mode);
    FlipMode actual_mode = sprite_ptr->get_flip_mode();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(new_mode, actual_mode);
}

// Texture Region
TEST_F(SpriteTestFixture, GetTextureRegion_Returns_SpriteTextureRegion) {
    // Arrange & Act
    Rect2 actual_region = sprite_ptr->get_texture_region();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_GE(actual_region.size.x, 0.0f);
    EXPECT_GE(actual_region.size.y, 0.0f);
}
TEST_F(SpriteTestFixture, SetTextureRegion_Sets_SpriteTextureRegion) {
    // Arrange
    Rect2 new_region(10.0f, 10.0f, 100.0f, 100.0f);

    // Act
    sprite_ptr->set_texture_region(new_region);
    Rect2 actual_region = sprite_ptr->get_texture_region();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(new_region, actual_region);
}
TEST_F(SpriteTestFixture, UseFullRegion_Sets_TextureRegionToFullSize) {
    // Arrange
    Vector2i sprite_size = sprite_ptr->get_size();
    Rect2 expected_region(0.0f, 0.0f, static_cast<float>(sprite_size.x), static_cast<float>(sprite_size.y));

    // Act
    sprite_ptr->use_full_region();
    Rect2 actual_region = sprite_ptr->get_texture_region();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_region, actual_region);
}

// Screen Placement

TEST_F(SpriteTestFixture, GetScreenPlacement_Returns_SpriteScreenPlacement) {
    // Arrange & Act
    Rect2 actual_placement = sprite_ptr->get_screen_placement();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_GE(actual_placement.size.x, 0.0f);
    EXPECT_GE(actual_placement.size.y, 0.0f);
}
TEST_F(SpriteTestFixture, SetScreenPlacement_Sets_SpriteScreenPlacement) {
    // Arrange
    Rect2 new_placement(50.0f, 50.0f, 200.0f, 200.0f);

    // Act
    sprite_ptr->set_screen_placement(new_placement);
    Rect2 actual_placement = sprite_ptr->get_screen_placement();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(new_placement, actual_placement);
}

TEST_F(SpriteTestFixture, UseDefaultScreenPlacement_Sets_ScreenPlacementToDefault) {
    // Arrange
    Vector2i sprite_size = sprite_ptr->get_size();
    Rect2 expected_placement(0.0f, 0.0f, static_cast<float>(sprite_size.x), static_cast<float>(sprite_size.y));

    // Act
    sprite_ptr->use_default_screen_placement();
    Rect2 actual_placement = sprite_ptr->get_screen_placement();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_placement, actual_placement);
}

// Bounding Box

TEST_F(SpriteTestFixture, GetBoundingBox_Returns_SpriteBoundingBox) {
    // Arrange
    Vector2 expected_position(0.0f, 0.0f);
    Vector2 expected_size(362.0f, 362.0f);
    Rect2 expected_bounding_box(expected_position, expected_size);

    // Act
    Rect2 actual_bounding_box = sprite_ptr->get_bounding_box();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_bounding_box, actual_bounding_box);
}

TEST_F(SpriteTestFixture, SetBoundingBox_Sets_SpriteBoundingBox) {
    // Arrange
    Vector2 new_position(100.0f, 100.0f);
    Vector2 new_size(200.0f, 200.0f);
    Rect2 new_bounding_box(new_position, new_size);

    // Act
    sprite_ptr->set_bounding_box(new_bounding_box);
    Rect2 actual_bounding_box = sprite_ptr->get_bounding_box();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(new_bounding_box, actual_bounding_box);
}

// Colour Tint

TEST_F(SpriteTestFixture, SetColourTint_Sets_SpriteColourTint) {
    // Arrange
    Colour new_tint = Colours::Red;

    // Act
    sprite_ptr->set_colour_tint(new_tint);
    Colour actual_tint = sprite_ptr->get_colour_tint();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(new_tint, actual_tint);
}
TEST_F(SpriteTestFixture, ClearColourTint_Clears_SpriteColourTint) {
    // Arrange
    sprite_ptr->set_colour_tint(Colours::Blue);
    Colour expected_tint = Colours::NoTint;

    // Act
    sprite_ptr->clear_colour_tint();
    Colour actual_tint = sprite_ptr->get_colour_tint();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_EQ(expected_tint, actual_tint);
}

// Texture

TEST_F(SpriteTestFixture, HasTexture_Returns_True_WhenTextureExists) {
    // Arrange & Act
    bool has_texture = sprite_ptr->has_texture();

    // Assert
    EXPECT_TRUE(has_texture);
}
TEST_F(SpriteTestFixture, SetTexture_Sets_NewTexture) {
    // Arrange
    auto new_texture = std::make_shared<Texture>(renderer_ptr->get_native_ptr(), abs_path.c_str());

    // Act
    sprite_ptr->set_texture(new_texture);

    // Assert
    EXPECT_TRUE(sprite_ptr->has_texture());
    EXPECT_TRUE(sprite_ptr->is_valid());
}

// Collisions

TEST_F(SpriteTestFixture, Intersects_Returns_True_WhenSpritesOverlap) {
    // Arrange
    sprite_ptr->set_position(0.0f, 0.0f);
    second_sprite_ptr->set_position(100.0f, 100.0f); // Overlapping with first sprite

    // Act
    bool intersects = sprite_ptr->intersects(*second_sprite_ptr);

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_TRUE(second_sprite_ptr->is_valid());
    EXPECT_TRUE(intersects);
}
TEST_F(SpriteTestFixture, Intersects_Returns_False_WhenSpritesDoNotOverlap) {
    // Arrange
    sprite_ptr->set_position(0.0f, 0.0f);
    second_sprite_ptr->set_position(500.0f, 500.0f); // Far away from first sprite

    // Act
    bool intersects = sprite_ptr->intersects(*second_sprite_ptr);

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_TRUE(second_sprite_ptr->is_valid());
    EXPECT_FALSE(intersects);
}

// Native Pointer

TEST_F(SpriteTestFixture, GetNativePtr_Returns_ValidPointer_WhenSpriteValid) {
    // Arrange & Act
    NativeTexturePtr native_ptr = sprite_ptr->get_native_ptr();

    // Assert
    EXPECT_TRUE(sprite_ptr->is_valid());
    EXPECT_NE(native_ptr.ptr, nullptr);
}

TEST_F(SpriteTestFixture, GetNativePtr_Returns_NullPointer_WhenSpriteInvalid) {
    // Arrange (done via SetUp)

    // Act
    NativeTexturePtr native_ptr = invalid_sprite_ptr->get_native_ptr();

    // Assert
    EXPECT_FALSE(invalid_sprite_ptr->is_valid());
    EXPECT_EQ(native_ptr.ptr, nullptr);
}

// Invalid Sprite Operations

TEST_F(SpriteTestFixture, IsValid_WithInvalidSprite_ReturnsFalse) {
    // Arrange (done in SetUp)

    // Act
    bool is_valid = invalid_sprite_ptr->is_valid();

    // Assert
    EXPECT_FALSE(is_valid);
}

TEST_F(SpriteTestFixture, BoolOperator_WithInvalidSprite_ReturnsFalse) {
    // Arrange (done in SetUp)

    // Act
    bool bool_result = static_cast<bool>(*invalid_sprite_ptr);

    // Assert
    EXPECT_FALSE(bool_result);
}

TEST_F(SpriteTestFixture, InvalidSprite_GettersReturn_DefaultValues) {
    // Arrange (done via SetUp)

    // Act & Assert
    EXPECT_FALSE(invalid_sprite_ptr->is_valid());
    EXPECT_FALSE(invalid_sprite_ptr->has_texture());

    // These should all log warnings but not crash
    Vector2 default_pos = invalid_sprite_ptr->get_position();
    Vector2i default_size = invalid_sprite_ptr->get_size();
    int default_width = invalid_sprite_ptr->get_width();
    int default_height = invalid_sprite_ptr->get_height();
    Vector2 default_scale_factor = invalid_sprite_ptr->get_scale_factor();
    float default_angle = invalid_sprite_ptr->get_angle();
    Vector2 default_anchor = invalid_sprite_ptr->get_anchor();
    bool default_visibility = invalid_sprite_ptr->is_hidden();
    FlipMode default_mode = invalid_sprite_ptr->get_flip_mode();
    Rect2 default_bounding_box = invalid_sprite_ptr->get_bounding_box();
    Rect2 default_texture_region = invalid_sprite_ptr->get_texture_region();
    Rect2 default_screen_placement = invalid_sprite_ptr->get_screen_placement();

    EXPECT_FALSE(invalid_sprite_ptr->is_valid());
}
TEST_F(SpriteTestFixture, InvalidSprite_SettersLog_Warnings) {
    // Arrange (done via SetUp)

    // Act & Assert
    EXPECT_FALSE(invalid_sprite_ptr->is_valid());

    // These should all log warnings but not crash
    invalid_sprite_ptr->set_position(Vector2(10.0f, 10.0f));
    invalid_sprite_ptr->set_scale_factor(Vector2(2.0f, 2.0f));
    invalid_sprite_ptr->set_angle(45.0);
    invalid_sprite_ptr->set_anchor(Vector2(0.5f, 0.5f));
    invalid_sprite_ptr->show();
    invalid_sprite_ptr->hide();
    invalid_sprite_ptr->set_flip_mode(FlipMode::Horizontal);
    invalid_sprite_ptr->set_texture_region(Rect2(0, 0, 100, 100));
    invalid_sprite_ptr->set_screen_placement(Rect2(0, 0, 100, 100));
    invalid_sprite_ptr->set_bounding_box(Rect2(0, 0, 100, 100));

    EXPECT_FALSE(invalid_sprite_ptr->is_valid());
}
