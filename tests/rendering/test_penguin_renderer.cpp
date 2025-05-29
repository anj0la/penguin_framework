#include <penguin_framework/core/window/penguin_window.hpp>
#include <penguin_framework/core/rendering/penguin_renderer.hpp>
#include <penguin_framework/core/rendering/primitives/penguin_sprite.hpp> 
#include <SDL3/SDL.h>
#include <gtest/gtest.h>
#include <memory>
#include <filesystem>

using penguin::core::window::Window;
using penguin::core::window::WindowFlags;
using penguin::core::rendering::Renderer;
using penguin::core::rendering::primitives::Sprite;
using penguin::core::rendering::primitives::Texture;
using penguin::core::rendering::primitives::FlipMode;

// Helper Functions (note: The AssetManager will actually be used to load a Texture) 

std::filesystem::path get_test_asset_path(const char* name) {
    return std::filesystem::path(TEST_ASSETS_DIR) / name;
}

// Setting Up the Test Suite

class RendererTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;
    std::shared_ptr<Texture> texture_ptr;
    std::unique_ptr<Sprite> sprite_ptr;
    String asset_name = "penguin_cute.bmp";
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name.c_str())).string();

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

TEST_F(RendererTestFixture, Display_WhenCalled_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->display();

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, Clear_WhenCalled_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->clear();

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawPixel_WithValidParameters_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_pixel(test_vec1, Colours::Red);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawLine_WithValidParameters_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_line(test_vec1, test_vec2, Colours::Green);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawRect_WithValidParameters_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_rect(test_rect, Colours::Blue);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawFilledRect_WithValidParameters_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_filled_rect(test_rect, Colours::Yellow);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawTriangle_WithValidParameters_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_triangle(test_vec1, test_vec2, test_vec3, Colours::Magenta);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawFilledTriangle_WithValidParameters_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_filled_triangle(test_vec1, test_vec2, test_vec3, Colours::Cyan);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawCircle_WithVectorAndRadius_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_circle(test_circle.center, static_cast<int>(test_circle.radius), Colours::Orange);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawCircle_WithCircle2Object_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_circle(test_circle, Colours::Purple);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawFilledCircle_WithVectorAndRadius_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_filled_circle(test_circle.center, static_cast<int>(test_circle.radius), Colours::Brown);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawFilledCircle_WithCircle2Object_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_filled_circle(test_circle, Colours::Pink);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawEllipse_WithValidParameters_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_ellipse(test_circle.center, test_radius_x, test_radius_y, Colours::Silver);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawFilledEllipse_WithValidParameters_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_filled_ellipse(test_circle.center, test_radius_x, test_radius_y, Colours::Gold);

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawSprite_WithValidParameters_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_sprite(*sprite_ptr.get()); // deferencing the Sprite
    
    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawSpriteFrom_WithValidParameters_ReturnsSuccess) {
    // Arrange
    Rect2 source{ 100.0f, 100.0f, 100.0f, 100.0f };

    // Act
    bool success = renderer_ptr->draw_sprite_from(*sprite_ptr.get(), source); // deferencing the Sprite

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawSpriteTo_WithValidParameters_ReturnsSuccess) {
    // Arrange
    Rect2 dest_override{ 100.0f, 100.0f, 100.0f, 100.0f };

    // Act
    bool success = renderer_ptr->draw_sprite_to(*sprite_ptr.get(), dest_override); // deferencing the Sprite

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawSpriteFromTo_WithValidParameters_ReturnsSuccess) {
    // Arrange
    Rect2 source{ 100.0f, 100.0f, 100.0f, 100.0f };
    Rect2 dest_override{ 200.0f, 200.0f, 200.0f, 200.0f };

    // Act
    bool success = renderer_ptr->draw_sprite_from_to(*sprite_ptr.get(), source, dest_override); // deferencing the Sprite

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawSpriteTransformed_WithValidParameters_ReturnsSuccess) {
    // Arrange (done in SetUp)
    // Act
    bool success = renderer_ptr->draw_sprite_transformed(*sprite_ptr.get()); // deferencing the Sprite

    // Assert
    EXPECT_TRUE(success);
}

TEST_F(RendererTestFixture, DrawSpriteTransformedEx_WithValidParameters_ReturnsSuccess) {
    // Arrange
    Vector2 anchor_point(0.25f, 0.25f);
    // Act
    bool success = renderer_ptr->draw_sprite_transformed_ex(*sprite_ptr.get(), anchor_point); // deferencing the Sprite

    // Assert
    EXPECT_TRUE(success);
}


//bool draw_sprite_transformed(primitives::Sprite spr);
//bool draw_sprite_transformed_ex(primitives::Sprite spr, Vector2 anchor_point);
//bool draw_sprite_from_transformed(primitives::Sprite spr, Rect2 source);
//bool draw_sprite_from_transformed_ex(primitives::Sprite spr, Rect2 source, Vector2 anchor_point);
//bool draw_sprite_to_transformed(primitives::Sprite spr, Rect2 dest_override);
//bool draw_sprite_to_transformed_ex(primitives::Sprite spr, Rect2 dest_override, Vector2 anchor_point);
//bool draw_sprite_from_to_transformed(primitives::Sprite spr, Rect2 source, Rect2 dest_override);
//bool draw_sprite_from_to_transformed_ex(primitives::Sprite spr, Rect2 source, Rect2 dest_override, Vector2 anchor_point);
//
//bool draw_sprite_global_scaled(primitives::Sprite spr);
//bool draw_sprite_from_scaled(primitives::Sprite spr, Rect2 source);
//bool draw_sprite_to_scaled(primitives::Sprite spr, Rect2 dest_override);
//bool draw_sprite_from_to_scaled(primitives::Sprite spr, Rect2 source, Rect2 dest_override);