#include "core/window/pf_window.hpp"
#include "core/window/pf_windowflags.hpp"
#include <SDL3/SDL_init.h>
#include <gtest/gtest.h>

using pf::core::PF_Window;
using pf::core::PF_WindowFlags;

// Note: The vsync functions cannot be tested with the window, but with the renderer once made.

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

TEST_F(PF_WindowTestFixture, CreatesDefaultWindow) {
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


TEST_F(PF_WindowTestFixture, CreatesWindowWithAllParams) {
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

TEST_F(PF_WindowTestFixture, CreatesWindowWithAllParamsInt) {
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

// Window Functions

TEST_F(PF_WindowTestFixture, SetsWindowTitleCorrectly) {
    PF_Window window("Original Title", Vector2i(800, 600), PF_WindowFlags::Hidden);

    String new_title = "Updated Title"; // using String class instead of std::string, but doesn't really matter
    window.set_title(new_title.c_str());

    // Validate title
    const char* actual_title = window.get_title();
    EXPECT_STREQ(actual_title, new_title.c_str());
}


TEST_F(PenguinWindowTest, SetsMaxSizeCorrectly) {
    PF_Window window("Resizable Window", Vector2i(800, 600), PF_WindowFlags::Hidden | PF_WindowFlags::Resizable);

    Vector2i max_size(1024, 768);
    window.set_max_size(max_size);

    // Validate max size
    Vector2i actual_max_size = window.get_max_window_size();
    EXPECT_EQ(max_size.x, actual_max_size.x);
    EXPECT_EQ(max_size.y, actual_max_size.y);
}


TEST_F(PenguinWindowTest, SetsMinSizeCorrectly) {
    PF_Window window("Resizable Window", Vector2i(800, 600), PF_WindowFlags::Hidden | PF_WindowFlags::Resizable);

    Vector2i min_size(400, 300);
    window.set_min_size(min_size);

    // Validate min size
    Vector2i actual_min_size = window.get_min_window_size();
    EXPECT_EQ(min_size.x, actual_min_size.x);
    EXPECT_EQ(min_size.y, actual_min_size.y);
}


TEST_F(PenguinWindowTest, ResizesWindowCorrectly) {
    PF_Window window("Resizable Window", Vector2i(800, 600), PF_WindowFlags::Hidden | PF_WindowFlags::Resizable);

    Vector2i new_size(640, 480);
    window.resize(new_size);

    // Validate new size
    Vector2i actual_size = window.get_window_size();
    EXPECT_EQ(new_size.x, actual_size.x);
    EXPECT_EQ(new_size.y, actual_size.y);
}

TEST_F(PenguinWindowTest, ShowsandHidesWindowCorrectly) {
    PF_Window window("Hidden Window", Vector2i(800, 600), PF_WindowFlags::Hidden);

    window.show();

    // Validate window is shown
    EXPECT_FALSE(window.is_hidden());

    window.hide();

    // Validate window is hidden
    EXPECT_TRUE(window.is_hidden());
    EXPECT_TRUE(window.is_hidden());

}

TEST_F(PenguinWindowTest, MinimizesAndMaximizesWindowCorrectly) {
    PF_Window window("Hidden Window", Vector2i(800, 600), PF_WindowFlags::Hidden | PF_WindowFlags::Resizable);

    // Validate that window is resizable and NOT minimized OR maximized
    EXPECT_TRUE(window.is_resizable());
    EXPECT_FALSE(window.is_minimized());
    EXPECT_FALSE(window.is_maximized());

    window.minimize();

    // Validate that window is resizable AND minimized but NOT maximized
    EXPECT_TRUE(window.is_resizable());
    EXPECT_TRUE(window.is_minimized());
    EXPECT_FALSE(window.is_maximized());

    window.maximize();

    // Validate that window is resizable AND maximized but NOT minimized
    EXPECT_TRUE(window.is_resizable());
    EXPECT_TRUE(window.is_maximized());
    EXPECT_FALSE(window.is_minimized());
}

TEST_F(PenguinWindowTest, DoesNotMinimizesAndMaximizesWindow) {
    PF_Window window("Hidden Window", Vector2i(800, 600), PF_WindowFlags::Hidden);

    // Validate that window is NOT resizable and NOT minimized OR maximized
    EXPECT_FALSE(window.is_resizable());
    EXPECT_FALSE(window.is_minimized());
    EXPECT_FALSE(window.is_maximized());

    window.minimize();

    // Validate that window is NOT resizable AND NOT minimized OR maximized
    EXPECT_FALSE(window.is_resizable());
    EXPECT_FALSE(window.is_minimized());
    EXPECT_FALSE(window.is_maximized());

    window.maximize();

    // Validate that window is NOT resizable AND NOT minimized OR maximized
    EXPECT_FALSE(window.is_resizable());
    EXPECT_FALSE(window.is_maximized());
    EXPECT_FALSE(window.is_minimized());
}

TEST_F(PenguinWindowTest, RestoresWindowCorrectly) {
    PF_Window window("Hidden Window", Vector2i(800, 600), PF_WindowFlags::Hidden | PF_WindowFlags::Resizable);

  
}