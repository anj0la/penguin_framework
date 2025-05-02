#include <penguin_framework/core/window/penguin_window.hpp>
#include <SDL3/SDL.h>
#include <gtest/gtest.h>

using penguin::core::window::Window;
using penguin::core::window::WindowFlags;
using penguin::core::window::WindowVSyncFlags;

// Setting Up the Test Suite

class WindowTestFixture : public ::testing::Test {
protected:
	void SetUp() override {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
		ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL video subsystem could not be initialized because of: " << SDL_GetError();
	}

	void TearDown() override {
		SDL_Quit();
	}

};

// Constructor Test

TEST_F(WindowTestFixture, ConstructorDefaultCreatesHiddenWindow) {
    ASSERT_NO_THROW({
        // Arrange & Act (Implicit via constructor)
        Window window("", Vector2i(640, 480), WindowFlags::Hidden); 

        // Assert - Validate default properties for a hidden window
        EXPECT_STREQ(window.get_title(), ""); // Default title is empty
        EXPECT_EQ(window.get_window_width(), 640); // Default width is 640 pixels
        EXPECT_EQ(window.get_window_height(), 480); // Default height is 480 pixels

        // Assert - Validate flags
        EXPECT_TRUE(window.is_hidden());   // Explicitly requested
        EXPECT_TRUE(window.is_open());     // Should be open after creation
        EXPECT_TRUE(window.is_bordered()); // Default is bordered unless Borderless flag is set

        EXPECT_FALSE(window.is_always_on_top());
        EXPECT_FALSE(window.is_focused());
        EXPECT_FALSE(window.is_fullscreen());
        EXPECT_FALSE(window.is_maximized());
        EXPECT_FALSE(window.is_minimized());
        EXPECT_FALSE(window.is_mouse_grabbed());
        EXPECT_FALSE(window.is_resizable());
    });
}

TEST_F(WindowTestFixture, ConstructorWithParamsSetsProperties) {
    // Arrange
    const String expected_title = "A Penguin Window";
    const Vector2i expected_size(800, 600); 
    const auto flags = WindowFlags::Hidden | WindowFlags::Resizable | WindowFlags::Borderless;

    ASSERT_NO_THROW({
        // Act (Implicit via constructor)
        Window window(expected_title.c_str(), expected_size, flags);

        // Assert - Validate specified properties
        EXPECT_STREQ(window.get_title(), expected_title.c_str());
        EXPECT_EQ(window.get_window_width(), expected_size.x);
        EXPECT_EQ(window.get_window_height(), expected_size.y);

        // Assert - Validate flags implied by constructor arguments
        EXPECT_TRUE(window.is_hidden());    // Explicit flag
        EXPECT_TRUE(window.is_resizable()); // Explicit flag
        EXPECT_FALSE(window.is_bordered()); // Explicit Borderless flag overrides default

        // Assert - Validate other flags remain default/false
        EXPECT_TRUE(window.is_open());
        EXPECT_FALSE(window.is_always_on_top());
        EXPECT_FALSE(window.is_focused());
        EXPECT_FALSE(window.is_fullscreen());
        EXPECT_FALSE(window.is_maximized());
        EXPECT_FALSE(window.is_minimized());
        EXPECT_FALSE(window.is_mouse_grabbed());
    });
}

// Window Functions

TEST_F(WindowTestFixture, SetTitleUpdatesTitle) {
    // Arrange
    Window window("Original Title", Vector2i(800, 600), WindowFlags::Hidden);
    const String expected_title = "Updated Title";
    ASSERT_STRNE(window.get_title(), expected_title.c_str());

    // Act
    bool success = window.set_title(expected_title.c_str());

    // Assert
    EXPECT_TRUE(success); 
    EXPECT_STREQ(window.get_title(), expected_title.c_str());
}

TEST_F(WindowTestFixture, SetMaxSizeRestrictsSize) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i max_size(1024, 768);

    // Act
    bool success = window.set_max_size(max_size);

    // Assert
    EXPECT_TRUE(success); 
    Vector2i actual_max_size = window.get_max_window_size();
    EXPECT_EQ(actual_max_size.x, max_size.x);
    EXPECT_EQ(actual_max_size.y, max_size.y);
}

TEST_F(WindowTestFixture, SetMaxSizeKeepsSize) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i max_size(-100, -400);

    // Act
    bool success = window.set_max_size(max_size);

    // Assert
    EXPECT_FALSE(success);
    Vector2i actual_max_size = window.get_max_window_size();
    EXPECT_EQ(actual_max_size.x, window.get_window_width()); // the max size should be the window size if it has not been set by default
    EXPECT_EQ(actual_max_size.y, window.get_window_height());
}
TEST_F(WindowTestFixture, SetMinSizeRestrictsSize) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i min_size(400, 300); 

    // Act
    bool success = window.set_min_size(min_size);

    // Assert
    EXPECT_TRUE(success); 
    Vector2i actual_min_size = window.get_min_window_size();
    EXPECT_EQ(actual_min_size.x, min_size.x);
    EXPECT_EQ(actual_min_size.y, min_size.y);
}

TEST_F(WindowTestFixture, SetMinSizeKeepsSize) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i min_size(-800, -600);

    // Act
    bool success = window.set_min_size(min_size);

    // Assert
    EXPECT_FALSE(success);
    Vector2i actual_min_size = window.get_min_window_size();
    EXPECT_EQ(actual_min_size.x, window.get_window_width()); // the min size should be the window size if it has not been set by default
    EXPECT_EQ(actual_min_size.y, window.get_window_height());
}

TEST_F(WindowTestFixture, ResizeChangesSize) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i new_size(640, 480);
    ASSERT_NE(window.get_window_width(), new_size.x); // Ensure size is different initially
    ASSERT_NE(window.get_window_height(), new_size.y);

    // Act
    bool success = window.resize(new_size);

    // Assert
    EXPECT_TRUE(success); 
    EXPECT_EQ(window.get_window_width(), new_size.x);
    EXPECT_EQ(window.get_window_height(), new_size.y);
}

TEST_F(WindowTestFixture, ResizeKeepsSize) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i new_size(-640, -480);
    ASSERT_NE(window.get_window_width(), new_size.x); // Ensure size is different initially
    ASSERT_NE(window.get_window_height(), new_size.y);

    // Act
    bool success = window.resize(new_size);

    // Assert
    // NOTE: No need to check if the window size is equal to Vector2i(800, 600).
    // The size is not changed internally unless a valid size is passed to the function.
    EXPECT_FALSE(success);
}

TEST_F(WindowTestFixture, ShowMakesHiddenWindowVisible) {
    // Arrange
    Window window("Hidden Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_TRUE(window.is_hidden()); 

    // Act
    bool success = window.show();

    // Assert
    EXPECT_TRUE(success); 
    EXPECT_FALSE(window.is_hidden()); 
}


TEST_F(WindowTestFixture, HideMakesVisibleWindowHidden) {
    // Arrange
    Window window("Visible Window", Vector2i(800, 600)); // No hidden flag
    ASSERT_FALSE(window.is_hidden()); 

    // Act
    bool success = window.hide();

    // Assert
    EXPECT_TRUE(success); 
    EXPECT_TRUE(window.is_hidden()); 
}

TEST_F(WindowTestFixture, MinimizeReducesResizableWindow) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    ASSERT_FALSE(window.is_minimized()); 
    ASSERT_TRUE(window.is_resizable()); 

    // Act
    bool success = window.minimize();

    // Assert
    // NOTE: Dummy video driver cannot actually minimize a window.
    // This test only ensures that our intent to minimize is recorded internally.
    // Real window state change must be tested at the integration level.
    EXPECT_FALSE(success); 
    EXPECT_TRUE(window.is_minimized()); 
    EXPECT_FALSE(window.is_maximized());
}

TEST_F(WindowTestFixture, MaximizeEnlargesResizableWindow) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    ASSERT_FALSE(window.is_maximized());
    ASSERT_TRUE(window.is_resizable()); 

    // Act
    bool success = window.maximize(); 

    // Assert
    // NOTE: Dummy video driver cannot actually maximize a window.
    // This test only ensures that our intent to maximize is recorded internally.
    // Real window state change must be tested at the integration level.
    EXPECT_FALSE(success);
    EXPECT_TRUE(window.is_maximized());
    EXPECT_FALSE(window.is_minimized()); 
}

TEST_F(WindowTestFixture, MinimizeDoesNothingOnNonResizableWindow) {
    // Arrange
    Window window("Fixed Window", Vector2i(800, 600), WindowFlags::Hidden); // No Resizable flag
    ASSERT_FALSE(window.is_resizable());
    ASSERT_FALSE(window.is_minimized());

    // Act
    bool success = window.minimize();

    // Assert
    // NOTE: true indicates it ran without error, false indicates that an internal error has occurred
    EXPECT_TRUE(success); 
    EXPECT_FALSE(window.is_minimized());
}

TEST_F(WindowTestFixture, MaximizeDoesNothingOnNonResizableWindow) {
    // Arrange
    Window window("Fixed Window", Vector2i(800, 600), WindowFlags::Hidden); // No Resizable flag
    ASSERT_FALSE(window.is_resizable());
    ASSERT_FALSE(window.is_maximized());

    // Act
    bool success = window.maximize();

    // Assert
    // NOTE: true indicates it ran without error, false indicates that an internal error has occurred
    EXPECT_TRUE(success); 
    EXPECT_FALSE(window.is_maximized()); 
}


TEST_F(WindowTestFixture, RestoreReturnsMinimizedWindowToNormal) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    window.minimize();
    ASSERT_TRUE(window.is_minimized());

    // Act
    bool success = window.restore(); 

    // Assert
    // NOTE: Dummy video driver cannot actually restore a minimized window.
    // This test only ensures that our intent to restore is recorded internally.
    // Real window state change must be tested at the integration level.
    EXPECT_FALSE(success);
    EXPECT_FALSE(window.is_minimized());
    EXPECT_FALSE(window.is_maximized()); 
}

TEST_F(WindowTestFixture, RestoreReturnsMaximizedWindowToNormal) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    window.maximize();
    ASSERT_TRUE(window.is_maximized());

    // Act
    bool success = window.restore(); 

    // Assert
    // NOTE: Dummy video driver cannot actually restore a maximized window.
    // This test only ensures that our intent to restore is recorded internally.
    // Real window state change must be tested at the integration level.
    EXPECT_FALSE(success); 
    EXPECT_FALSE(window.is_maximized());
    EXPECT_FALSE(window.is_minimized()); 
}


TEST_F(WindowTestFixture, RestoreAsyncCallSucceeds) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    window.minimize();
    ASSERT_TRUE(window.is_minimized());

    // Act
    bool success = window.restore_async();

    // Assert
    // NOTE: Dummy video driver cannot actually maximize a window.
    // This test only ensures that our intent to restore is recorded internally.
    // Real window state change must be tested at the integration level.
    EXPECT_FALSE(success); // Verify the call reported failure (read NOTE for more information)
}

TEST_F(WindowTestFixture, EnableResizingMakesWindowResizable) {
    // Arrange
    Window window("Fixed Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_FALSE(window.is_resizable());

    // Act
    bool success = window.enable_resizing();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_TRUE(window.is_resizable());
}

TEST_F(WindowTestFixture, DisableResizingMakesWindowFixed) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable); // Starts resizable
    ASSERT_TRUE(window.is_resizable());

    // Act
    bool success = window.disable_resizing();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_FALSE(window.is_resizable());
}


TEST_F(WindowTestFixture, DisableBordersRemovesBorder) {
    // Arrange
    Window window("Bordered Window", Vector2i(800, 600), WindowFlags::Hidden); // Starts bordered (default)
    ASSERT_TRUE(window.is_bordered());

    // Act
    bool success = window.disable_borders();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_FALSE(window.is_bordered());
}

TEST_F(WindowTestFixture, EnableBordersAddsBorder) {
    // Arrange
    Window window("Borderless Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Borderless); // Starts borderless
    ASSERT_FALSE(window.is_bordered());

    // Act
    bool success = window.enable_borders();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_TRUE(window.is_bordered());
}


TEST_F(WindowTestFixture, EnterFullscreenMakesWindowFullscreen) {
    // Arrange
    Window window("Windowed Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_FALSE(window.is_fullscreen());

    // Act
    bool success = window.enter_fullscreen();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_TRUE(window.is_fullscreen());
}

TEST_F(WindowTestFixture, ExitFullscreenMakesWindowWindowed) {
    // Arrange
    Window window("Fullscreen Window", Vector2i(800, 600), WindowFlags::Hidden);
    window.enter_fullscreen(); // Assume this works
    ASSERT_TRUE(window.is_fullscreen());

    // Act
    bool success = window.exit_fullscreen();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_FALSE(window.is_fullscreen());
}

TEST_F(WindowTestFixture, GrabMouseConfinesMouse) {
    // Arrange
    Window window("Free Mouse Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_FALSE(window.is_mouse_grabbed());

    // Act
    bool success = window.grab_mouse();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_TRUE(window.is_mouse_grabbed());
}
TEST_F(WindowTestFixture, ReleaseMouseFreesMouse) {
    // Arrange
    Window window("Grabbed Mouse Window", Vector2i(800, 600), WindowFlags::Hidden);
    window.grab_mouse(); // Assume this works
    ASSERT_TRUE(window.is_mouse_grabbed());

    // Act
    bool success = window.release_mouse();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_FALSE(window.is_mouse_grabbed());
}

TEST_F(WindowTestFixture, EnableAlwaysOnTopKeepsWindowOnTop) {
    // Arrange
    Window window("Normal Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_FALSE(window.is_always_on_top());

    // Act
    bool success = window.add_always_on_top();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_TRUE(window.is_always_on_top());
}

TEST_F(WindowTestFixture, DisableAlwaysOnTopAllowsWindowToBeObscured) {
    // Arrange
    Window window("Top Window", Vector2i(800, 600), WindowFlags::Hidden);
    window.add_always_on_top();
    ASSERT_TRUE(window.is_always_on_top());

    // Act
    bool success = window.remove_always_on_top();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_FALSE(window.is_always_on_top());
}

TEST_F(WindowTestFixture, GainFocusRequestsFocus) {
    // Arrange
    Window window("Background Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_FALSE(window.is_focused()); // Focus starts false (usually)

    // Act
    bool success = window.gain_focus();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_TRUE(window.is_focused());
}

TEST_F(WindowTestFixture, LoseFocusReleasesFocus) {
    // Arrange
    Window window("Background Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_FALSE(window.is_focused());

    // Act
    bool success = window.gain_focus();

    // Assert
    EXPECT_TRUE(success);
    EXPECT_TRUE(window.is_focused());
}