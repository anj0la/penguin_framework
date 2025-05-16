#include <penguin_framework/core/rendering/penguin_renderer.hpp>
#include <SDL3/SDL.h>
#include <gtest/gtest.h>
#include <memory>

using penguin::core::window::Window;
using penguin::core::window::WindowFlags;
using penguin::core::rendering::Renderer;

// Setting Up the Test Suite

class RendererTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Renderer> renderer_ptr;

    // Common test data
    const Vector2 test_vec1{ 10, 10 };
    const Vector2 test_vec2{ 50, 50 };
    const Vector2 test_vec3{ 30, 70 };
    const Rect2 test_rect{ test_vec1, Vector2(100, 100)};        // Position, Size
    const Circle2 test_circle{ test_vec1, 20.0f };               // Center, Radius
    const int test_radius_x = 25;
    const int test_radius_y = 15;

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