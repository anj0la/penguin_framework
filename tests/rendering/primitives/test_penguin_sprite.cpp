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
    String asset_name = "penguin_cute.bmp";

    void SetUp() override {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
        ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError();

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden);
        ASSERT_TRUE(window_ptr->is_open()) << "Window is open after creation.";

        renderer_ptr = std::make_unique<Renderer>(window_ptr.get()->get_native_ptr(), "software");
        ASSERT_NE(renderer_ptr->get_native_ptr().as<SDL_Renderer>(), nullptr) << "Native renderer is null.";
    }

    void TearDown() override {
        SDL_Quit();
    }
};

TEST_F(SpriteTestFixture, ConstructorWithTextureOnlyCreatesSprite) {
    // Arrange
    std::string abs_path = std::filesystem::absolute(get_test_asset_path(asset_name.c_str())).string();
    std::shared_ptr<Texture> texture_obj; // the Sprite class needs a shared texture (it doesn't "own" the texture but needs to have access to it)
    std::unique_ptr<Sprite> sprite_obj;
    Vector2 expected_position(0.0f, 0.0f);
    Vector2 expected_scale(1.0f, 1.0f);
    Vector2 expected_size(362.0f, 362.0f);
    Vector2i expected_size_i(362, 362);
    double expected_angle = 0.0f;
    Vector2 expected_anchor_point(0.5f, 0.5f);
    bool expected_visiblility = true;
    FlipMode expected_mode = FlipMode::None;
    Colour expected_tint = Colours::NoTint;
    Rect2 expected_bounding_box(expected_position, expected_size); // The size of the penguin_cute image is 362 x 362 pixels

    // Expected bounding position should be at Rect2(expected_position, size)

    // Act & Assert (Construction)
    ASSERT_NO_THROW({
        texture_obj = std::make_shared<Texture>(renderer_ptr->get_native_ptr(), abs_path.c_str());
        sprite_obj = std::make_unique<Sprite>(texture_obj);
        });

    // Assert - Validate that object was created
    ASSERT_NE(sprite_obj, nullptr);
    ASSERT_NE(sprite_obj->get_native_ptr().ptr, nullptr); // equivalent to texture_obj->get_native_ptr()

    // Assert - Validate all variables are set
    EXPECT_EQ(expected_position, sprite_obj->get_position());

    Vector2i texture_size = sprite_obj->get_size();
    ASSERT_GT(texture_size.x, 0);
    ASSERT_GT(texture_size.y, 0);
    EXPECT_EQ(texture_size.x, expected_size_i.x);
    EXPECT_EQ(texture_size.y, expected_size_i.y);

    EXPECT_EQ(expected_scale, sprite_obj->get_scale());
    EXPECT_EQ(expected_angle, sprite_obj->get_angle());
    EXPECT_EQ(expected_anchor_point, sprite_obj->get_anchor_point());
    EXPECT_EQ(expected_visiblility, sprite_obj->is_hidden());
    EXPECT_EQ(expected_mode, sprite_obj->get_flip_mode());
    EXPECT_EQ(expected_tint, sprite_obj->get_colour_tint());
    EXPECT_EQ(expected_bounding_box, sprite_obj->get_bounding_box());
}