#include <penguin_framework/core/rendering/penguin_renderer.hpp>
#include <SDL3/SDL.h>
#include <gtest/gtest.h>

//
//using penguin::core::window::Window;
//using penguin::core::window::WindowFlags;
//using penguin::core::rendering::Renderer;
//
//// Setting Up the Test Suite
//
//class RendererTestFixture : public ::testing::Test {
//protected:
//    Window window;
//    Renderer renderer;
//
//    void SetUp() override {
//        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
//        ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL video subsystem could not be initialized because of: " << SDL_GetError();
//
//        window = Window("A Penguin Window", Vector2i(800, 600), WindowFlags::Hidden);
//        renderer = Renderer(window, "software");
//    }
//
//    void TearDown() override {
//        SDL_Quit();
//    }
//};

