#include <penguin_framework/window/window.hpp>
#include <penguin_framework/rendering/renderer.hpp>
#include <penguin_framework/rendering/primitives/sprite.hpp> 
#include <SDL3/SDL.h>
#include <gtest/gtest.h>
#include <memory>
#include <filesystem>

#include <common/test_helpers.hpp>

using penguin::window::Window;
using penguin::window::WindowFlags;
using penguin::rendering::Renderer;
using penguin::rendering::primitives::Sprite;
using penguin::rendering::primitives::Texture;
using penguin::rendering::primitives::FlipMode;
using penguin::math::Vector2;
using penguin::math::Rect2;
using penguin::math::Vector2i;
using penguin::math::Circle2;
using penguin::math::Colour;

class RendererTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    std::unique_ptr<Renderer> invalid_renderer_ptr;
    std::shared_ptr<Texture> texture_ptr;
    std::unique_ptr<Sprite> sprite_ptr;
    const char* asset_name = "penguin_cute.bmp";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name)).string();

    const Vector2 test_vec1{ 10, 10 };
    const Vector2 test_vec2{ 50, 50 };
    const Vector2 test_vec3{ 30, 70 };
    const Rect2 test_rect{ test_vec1, Vector2(100, 100)};      
    const Circle2 test_circle{ test_vec1, 20.0f };              
    const int test_radius_x = 25;
    const int test_radius_y = 15;

    void SetUp() override {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
        ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError();

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_valid()); // window should be OPEN and VALID

        renderer_ptr = std::make_unique<Renderer>(window_ptr.get()->get_native_ptr(), "software");
        ASSERT_TRUE(renderer_ptr->is_valid());

        invalid_renderer_ptr = std::make_unique<Renderer>(NativeWindowPtr{ nullptr }, "");
        ASSERT_FALSE(invalid_renderer_ptr->is_valid());

        texture_ptr = std::make_shared<Texture>(renderer_ptr->get_native_ptr(), abs_path.c_str());
        ASSERT_TRUE(texture_ptr->is_valid());

        sprite_ptr = std::make_unique<Sprite>(texture_ptr);
        ASSERT_TRUE(sprite_ptr->is_valid());
    }

    void TearDown() override {
        SDL_Quit();
    }
};

// Renderer Functions

TEST_F(RendererTestFixture, IsValid_WithValidRenderer_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool is_valid = renderer_ptr->is_valid();

    // Assert
    EXPECT_TRUE(is_valid);
}

TEST_F(RendererTestFixture, BoolOperator_WithValidRenderer_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool bool_result = static_cast<bool>(*renderer_ptr);

    // Assert
    EXPECT_TRUE(bool_result);
}

TEST_F(RendererTestFixture, Display_WithValidRenderer_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->display();

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, Clear_WithValidRenderer_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->clear();

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

// Tests for drawing primitive shapes

TEST_F(RendererTestFixture, DrawPixel_WithValidParameters_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_pixel(test_vec1, Colours::Red);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawLine_WithValidParameters_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_line(test_vec1, test_vec2, Colours::Green);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawRect_WithValidParameters_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_rect(test_rect, Colours::Blue);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawFilledRect_WithValidParameters_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_filled_rect(test_rect, Colours::Yellow);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawTriangle_WithValidParameters_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_triangle(test_vec1, test_vec2, test_vec3, Colours::Magenta);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawFilledTriangle_WithValidParameters_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_filled_triangle(test_vec1, test_vec2, test_vec3, Colours::Cyan);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawCircle_WithVectorAndRadius_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_circle(test_circle.center, static_cast<int>(test_circle.radius), Colours::Orange);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawCircle_WithCircle2Object_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_circle(test_circle, Colours::Purple);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawFilledCircle_WithVectorAndRadius_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_filled_circle(test_circle.center, static_cast<int>(test_circle.radius), Colours::Brown);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawFilledCircle_WithCircle2Object_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_filled_circle(test_circle, Colours::Pink);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawEllipse_WithValidParameters_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_ellipse(test_circle.center, test_radius_x, test_radius_y, Colours::Silver);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawFilledEllipse_WithValidParameters_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_filled_ellipse(test_circle.center, test_radius_x, test_radius_y, Colours::Gold);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

// Tests for sprite rendering

TEST_F(RendererTestFixture, DrawSprite_WithValidParameters_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_sprite(*sprite_ptr);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawSpriteTransformed_WithValidParameters_RendererRemainsValid) {
    // Arrange (done in SetUp)

    // Act
    renderer_ptr->draw_sprite_transformed(*sprite_ptr);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawSprite_WithHiddenSprite_RendererRemainsValid) {
    // Arrange
    sprite_ptr->hide();

    // Act
    renderer_ptr->draw_sprite(*sprite_ptr);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawSpriteTransformed_WithHiddenSprite_RendererRemainsValid) {
    // Arrange
    sprite_ptr->hide();

    // Act
    renderer_ptr->draw_sprite_transformed(*sprite_ptr);

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, GetNativePtr_WithValidRenderer_ReturnsNonNullPtr) {
    // Arrange (done in SetUp)

    // Act
    auto native_ptr = renderer_ptr->get_native_ptr();

    // Assert
    EXPECT_TRUE(renderer_ptr->is_valid());
    EXPECT_NE(native_ptr.ptr, nullptr);
}

// Invalid Renderer Operations

TEST_F(RendererTestFixture, IsValid_WithInvalidRenderer_ReturnsFalse) {
    // Arrange (done in SetUp)

    // Act
    bool is_valid = invalid_renderer_ptr->is_valid();

    // Assert
    EXPECT_FALSE(is_valid);
}

TEST_F(RendererTestFixture, BoolOperator_WithInvalidRenderer_ReturnsFalse) {
    // Arrange (done in SetUp)

    // Act
    bool bool_result = static_cast<bool>(*invalid_renderer_ptr);

    // Assert
    EXPECT_FALSE(bool_result);
}

TEST_F(RendererTestFixture, Display_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->display();

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, Clear_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->clear();

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawPixel_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->draw_pixel(test_vec1, Colours::Red);

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawLine_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->draw_line(test_vec1, test_vec2, Colours::Green);

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawRect_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->draw_rect(test_rect, Colours::Blue);

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawFilledRect_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->draw_filled_rect(test_rect, Colours::Yellow);

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawTriangle_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->draw_triangle(test_vec1, test_vec2, test_vec3, Colours::Magenta);

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawFilledTriangle_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->draw_filled_triangle(test_vec1, test_vec2, test_vec3, Colours::Cyan);

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawCircle_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->draw_circle(test_circle, Colours::Purple);

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawFilledCircle_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->draw_filled_circle(test_circle, Colours::Pink);

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawEllipse_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->draw_ellipse(test_circle.center, test_radius_x, test_radius_y, Colours::Silver);

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, DrawFilledEllipse_WithInvalidRenderer_RendererRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_renderer_ptr->draw_filled_ellipse(test_circle.center, test_radius_x, test_radius_y, Colours::Gold);

    // Assert
    EXPECT_FALSE(invalid_renderer_ptr->is_valid());
}

TEST_F(RendererTestFixture, GetNativePtr_WithInvalidRenderer_ReturnsNullPtr) {
    // Arrange (done in SetUp)

    // Act
    auto native_ptr = invalid_renderer_ptr->get_native_ptr();

    // Assert
    EXPECT_EQ(native_ptr.ptr, nullptr);
}