#include "core/window/pf_window.hpp"
#include "core/window/pf_windowflags.hpp"
#include <SDL3/SDL_init.h>
#include <gtest/gtest.h>

using pf::core::PF_Window;
using pf::core::PF_WindowFlags;

// Setting Up the Test Suite

class PF_WindowTestFixture : public ::testing::Test {

	void SetUp() {
		ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), 0) << "SDL was not initialized.";
	}

	void TearDown() {
		SDL_Quit();
	}

};

// Constructor Test

TEST_F(PF_WindowTest, CreateDefaultWindow) {
	PF_Window window(PF_WindowFlags::Hidden); // we use the hidden flag to hide the window during test

    // Validate window creation
    ASSERT_NE(window.get_ptr(), nullptr); // ensure that the window's raw pointer is not NULL

    // Validate title
    const char* title = window.get_title();
    EXPECT_STREQ(title, ""); // the default title should be blank, or ""

    // Validate size
    Vector2i size = window.get_window_size();
    EXPECT_EQ(640, size.x); // window size is 640 pixels wide by default
    EXPECT_EQ(480, size.y); // window size is 480 pixels wide by default

    // Validate flags
    EXPECT_FALSE(window.is_always_on_top());
    EXPECT_FALSE(window.is_bordered());
    EXPECT_FALSE(window.is_focused());
    EXPECT_FALSE(window.is_fullscreen());
    EXPECT_FALSE(window.is_maximized());
    EXPECT_FALSE(window.is_minimized());
    EXPECT_FALSE(window.is_mouse_grabbed());
    EXPECT_FALSE(window.is_vsync_enabled());
    EXPECT_FALSE(window.is_resizable());

    EXPECT_TRUE(window.is_open()); // this should be the only true variable (other than the hidden - which is for testing purposes)
    EXPECT_TRUE(window.is_hidden());
}


TEST_F(PF_WindowTest, CreateWindowWithAllParams) {
    PF_Window window("A Penguin Window", Vector2i(800, 600), PF_WindowFlags::Hidden | PF_WindowFlags::Resizable | PF_WindowFlags::Borderless);

    // Validate window creation
    ASSERT_NE(window.get_ptr(), nullptr); // ensure that the window's raw pointer is not NULL

    // Validate title
    const char* title = window.get_title();
    EXPECT_STREQ(title, ""); // the default title should be blank, or ""

    // Validate size
    Vector2i size = window.get_window_size();
    EXPECT_EQ(640, size.x); // window size is 640 pixels wide by default
    EXPECT_EQ(480, size.y); // window size is 480 pixels wide by default

    // Validate flags
    EXPECT_FALSE(window.is_always_on_top());
    EXPECT_FALSE(window.is_focused());
    EXPECT_FALSE(window.is_fullscreen());
    EXPECT_FALSE(window.is_maximized());
    EXPECT_FALSE(window.is_minimized());
    EXPECT_FALSE(window.is_mouse_grabbed());
    EXPECT_FALSE(window.is_vsync_enabled());

    EXPECT_TRUE(window.is_open()); 
    EXPECT_TRUE(window.is_bordered());
    EXPECT_TRUE(window.is_resizable());
    EXPECT_TRUE(window.is_hidden());
}

TEST_F(PF_WindowTest, CreateWindowWithAllParamsInt) {
    PF_Window window("A Penguin Window", 600, 600, PF_WindowFlags::Hidden | PF_WindowFlags::InputFocus | PF_WindowFlags::AlwaysOnTop);

    // Validate window creation
    ASSERT_NE(window.get_ptr(), nullptr); // ensure that the window's raw pointer is not NULL

    // Validate title
    const char* title = window.get_title();
    EXPECT_STREQ(title, ""); // the default title should be blank, or ""

    // Validate size
    Vector2i size = window.get_window_size();
    EXPECT_EQ(640, size.x); // window size is 640 pixels wide by default
    EXPECT_EQ(480, size.y); // window size is 480 pixels wide by default

    // Validate flags
    EXPECT_FALSE(window.is_bordered());
    EXPECT_FALSE(window.is_fullscreen());
    EXPECT_FALSE(window.is_maximized());
    EXPECT_FALSE(window.is_minimized());
    EXPECT_FALSE(window.is_mouse_grabbed());
    EXPECT_FALSE(window.is_vsync_enabled());
    EXPECT_FALSE(window.is_resizable());

    EXPECT_TRUE(window.is_open()); 
    EXPECT_TRUE(window.is_always_on_top());
    EXPECT_TRUE(window.is_focused());
    EXPECT_TRUE(window.is_hidden());
}
