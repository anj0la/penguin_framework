#include <penguin_framework/window/penguin_window.hpp>
#include <SDL3/SDL.h>
#include <gtest/gtest.h>

using penguin::window::Window;
using penguin::window::WindowFlags;
using penguin::math::Vector2i;

// Setting Up the Test Suite

class WindowTestFixture : public ::testing::Test {
protected:
	void SetUp() override {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
		ASSERT_EQ(SDL_Init(SDL_INIT_VIDEO), true) << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError();
	}

	void TearDown() override {
		SDL_Quit();
	}
};

// Constructor Test

TEST_F(WindowTestFixture, ConstructorDefault_Creates_HiddenWindow) {
    // Arrange & Act (Implicit via constructor)
    Window window("", penguin::math::Vector2i(640, 480), WindowFlags::Hidden);

    // Assert - Validate window
    EXPECT_TRUE(window.is_valid());

    // Assert - Validate default properties for a hidden window
    EXPECT_STREQ(window.get_title(), ""); // Default title is empty
    EXPECT_EQ(window.get_width(), 640); // Default width is 640 pixels
    EXPECT_EQ(window.get_height(), 480); // Default height is 480 pixels

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
}

TEST_F(WindowTestFixture, ConstructorWithParams_Sets_Properties) {
    // Arrange
    const char* expected_title = "A Penguin Window";
    const Vector2i expected_size(800, 600); 
    const auto flags = WindowFlags::Hidden | WindowFlags::Resizable | WindowFlags::Borderless;

    // Act (Implicit via constructor)
    Window window(expected_title, expected_size, flags);

    // Assert - Validate window
    EXPECT_TRUE(window.is_valid());

    // Assert - Validate specified properties
    EXPECT_STREQ(window.get_title(), expected_title);
    EXPECT_EQ(window.get_width(), expected_size.x);
    EXPECT_EQ(window.get_height(), expected_size.y);

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
}

// Window Functions

TEST_F(WindowTestFixture, SetTitle_Updates_Title) {
    // Arrange
    Window window("Original Title", Vector2i(800, 600), WindowFlags::Hidden);
    const char* expected_title = "Updated Title";
    ASSERT_STRNE(window.get_title(), expected_title);

    // Act
    window.set_title(expected_title);

    // Assert
    if (window) { // uses the bool() operator which calls is_valid internally
        EXPECT_STREQ(window.get_title(), expected_title);
    }

}

TEST_F(WindowTestFixture, SetMaxSize_Restricts_Size) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i max_size(1024, 768);

    // Act
    window.set_max_size(max_size);

    // Assert
    if (window) {
        Vector2i actual_max_size = window.get_max_size();
        EXPECT_EQ(actual_max_size.x, max_size.x);
        EXPECT_EQ(actual_max_size.y, max_size.y);
    }
}

TEST_F(WindowTestFixture, SetMaxSize_Keeps_Size) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i max_size(-100, -400);

    // Act
    window.set_max_size(max_size);

    // Assert
    if (window) {
        Vector2i actual_max_size = window.get_max_size();
        EXPECT_EQ(actual_max_size.x, window.get_width()); // the max size should be the window size if it has not been set by default
        EXPECT_EQ(actual_max_size.y, window.get_height());
    }
}

TEST_F(WindowTestFixture, SetMinSize_Restricts_Size) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i min_size(400, 300); 

    // Act
    window.set_min_size(min_size);

    // Assert
    if (window) {
        Vector2i actual_min_size = window.get_min_size();
        EXPECT_EQ(actual_min_size.x, min_size.x);
        EXPECT_EQ(actual_min_size.y, min_size.y);
    }
}

TEST_F(WindowTestFixture, SetMinSize_Keeps_Size) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i min_size(-800, -600);

    // Act
    window.set_min_size(min_size);

    // Assert
    if (window) {
        Vector2i actual_min_size = window.get_min_size();
        EXPECT_EQ(actual_min_size.x, window.get_width()); // the min size should be the window size if it has not been set by default
        EXPECT_EQ(actual_min_size.y, window.get_height());
    }
}

TEST_F(WindowTestFixture, Resize_Changes_Size) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i new_size(640, 480);
    ASSERT_NE(window.get_width(), new_size.x); // Ensure size is different initially
    ASSERT_NE(window.get_height(), new_size.y);

    // Act
    window.resize(new_size);

    // Assert
    if (window) {
        EXPECT_EQ(window.get_width(), new_size.x);
        EXPECT_EQ(window.get_height(), new_size.y);
    }
}

TEST_F(WindowTestFixture, Resize_Keeps_Size) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    const Vector2i expected_size(800, 600);
    const Vector2i new_size(-640, -480);
    ASSERT_NE(window.get_width(), new_size.x); // Ensure size is different initially
    ASSERT_NE(window.get_height(), new_size.y);

    // Act
    window.resize(new_size);

    // Assert
    if (window) {
        EXPECT_EQ(window.get_width(), expected_size.x);
        EXPECT_EQ(window.get_height(), expected_size.y);
    }
}

TEST_F(WindowTestFixture, Show_Makes_HiddenWindow_Visible) {
    // Arrange
    Window window("Hidden Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_TRUE(window.is_hidden()); 

    // Act
    window.show();

    // Assert
    if (window) {
        EXPECT_FALSE(window.is_hidden());
    }
}

TEST_F(WindowTestFixture, Hide_Makes_VisibleWindow_Hidden) {
    // Arrange
    Window window("Visible Window", Vector2i(800, 600)); // No hidden flag
    ASSERT_FALSE(window.is_hidden()); 

    // Act
    window.hide();

    // Assert
    if (window) {
        EXPECT_TRUE(window.is_hidden());
    }
}

TEST_F(WindowTestFixture, Minimize_Reduces_ResizableWindow) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    ASSERT_FALSE(window.is_minimized()); 
    ASSERT_TRUE(window.is_resizable()); 

    // Act
    window.minimize();

    // Assert
    // NOTE: The dummy video driver cannot actually minimize a window.
    // This test only ensures that our intent to minimize is recorded internally.
    if (window) {
        EXPECT_TRUE(window.is_minimized());
        EXPECT_FALSE(window.is_maximized());
    }
}

TEST_F(WindowTestFixture, MinimizeAsync_Reduces_ResizableWindow) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    ASSERT_FALSE(window.is_minimized());
    ASSERT_TRUE(window.is_resizable());

    // Act
    window.minimize_async();

    // Assert
    // NOTE: The dummy video driver cannot actually minimize a window.
    // This test only ensures that our intent to minimize is recorded internally.
    if (window) {
        EXPECT_TRUE(window.is_minimized());
        EXPECT_FALSE(window.is_maximized());
    }
}

TEST_F(WindowTestFixture, Maximize_Enlarges_ResizableWindow) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    ASSERT_FALSE(window.is_maximized());
    ASSERT_TRUE(window.is_resizable()); 

    // Act
    window.maximize(); 

    // Assert
    // NOTE: Dummy video driver cannot actually maximize a window.
    // This test only ensures that our intent to maximize is recorded internally.
    // Real window state change must be tested at the integration level.
    if (window) {
        EXPECT_TRUE(window.is_maximized());
        EXPECT_FALSE(window.is_minimized());
    }
}

TEST_F(WindowTestFixture, MaximizeAsync_Enlarges_ResizableWindow) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    ASSERT_FALSE(window.is_maximized());
    ASSERT_TRUE(window.is_resizable());

    // Act
    window.maximize_async();

    // Assert
    // NOTE: Dummy video driver cannot actually maximize a window.
    // This test only ensures that our intent to maximize is recorded internally.
    // Real window state change must be tested at the integration level.
    if (window) {
        EXPECT_TRUE(window.is_maximized());
        EXPECT_FALSE(window.is_minimized());
    }
}

TEST_F(WindowTestFixture, Minimize_DoesNothing_On_NonResizableWindow) {
    // Arrange
    Window window("Fixed Window", Vector2i(800, 600), WindowFlags::Hidden); // No Resizable flag
    ASSERT_FALSE(window.is_resizable());
    ASSERT_FALSE(window.is_minimized());

    // Act
    window.minimize();

    // Assert
    if (window) {
        EXPECT_FALSE(window.is_minimized());
    }
}

TEST_F(WindowTestFixture, Maximize_DoesNothing_On_NonResizableWindow) {
    // Arrange
    Window window("Fixed Window", Vector2i(800, 600), WindowFlags::Hidden); // No Resizable flag
    ASSERT_FALSE(window.is_resizable());
    ASSERT_FALSE(window.is_maximized());

    // Act
    window.maximize();

    // Assert
    if (window) {
        EXPECT_FALSE(window.is_maximized());
    }
}

TEST_F(WindowTestFixture, Restore_Returns_MinimizedWindow_ToNormal) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    window.minimize();
    ASSERT_TRUE(window.is_minimized());

    // Act
    window.restore(); 

    // Assert
    // NOTE: The dummy video driver cannot actually restore a minimized window.
    // This test only ensures that our intent to restore is recorded internally.
    // Real window state change must be tested at the integration level.
    if (window) {
        EXPECT_FALSE(window.is_minimized());
        EXPECT_FALSE(window.is_maximized());
    }
}

TEST_F(WindowTestFixture, Restore_Returns_MaximizedWindow_ToNormal) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    window.maximize();
    ASSERT_TRUE(window.is_maximized());

    // Act
    window.restore(); 

    // Assert
    // NOTE: The dummy video driver cannot actually restore a maximized window.
    // This test only ensures that our intent to restore is recorded internally.
    // Real window state change must be tested at the integration level.
    if (window) {
        EXPECT_FALSE(window.is_maximized());
        EXPECT_FALSE(window.is_minimized());
    }
}

TEST_F(WindowTestFixture, RestoreAsync_Call_Succeeds) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable);
    window.minimize();
    ASSERT_TRUE(window.is_minimized());

    // Act
    window.restore_async();

    // Assert
    // NOTE: The dummy video driver cannot actually maximize a window.
    // This test only ensures that our intent to restore is recorded internally.
    // Real window state change must be tested at the integration level.
    if (window) {
        EXPECT_FALSE(window.is_maximized());
        EXPECT_FALSE(window.is_minimized());
    }
}

TEST_F(WindowTestFixture, EnableResizing_Makes_Window_Resizable) {
    // Arrange
    Window window("Fixed Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_FALSE(window.is_resizable());

    // Act
    window.enable_resizing();

    // Assert
    if (window) {
        EXPECT_TRUE(window.is_resizable());
    }
}

TEST_F(WindowTestFixture, DisableResizing_Makes_Window_Fixed) {
    // Arrange
    Window window("Resizable Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Resizable); // Starts resizable
    ASSERT_TRUE(window.is_resizable());

    // Act
    window.disable_resizing();

    // Assert
    if (window) {
        EXPECT_FALSE(window.is_resizable());
    }
}

TEST_F(WindowTestFixture, DisableBorders_Removes_Border) {
    // Arrange
    Window window("Bordered Window", Vector2i(800, 600), WindowFlags::Hidden); // Starts bordered (default)
    ASSERT_TRUE(window.is_bordered());

    // Act
    window.disable_borders();

    // Assert
    if (window) {
        EXPECT_FALSE(window.is_bordered());
    }
}

TEST_F(WindowTestFixture, EnableBorders_Adds_Border) {
    // Arrange
    Window window("Borderless Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::Borderless); // Starts borderless
    ASSERT_FALSE(window.is_bordered());

    // Act
    window.enable_borders();

    // Assert
    if (window) {
        EXPECT_TRUE(window.is_bordered());
    }
    
}

TEST_F(WindowTestFixture, EnterFullscreen_Makes_Window_Fullscreen) {
    // Arrange
    Window window("Windowed Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_FALSE(window.is_fullscreen());

    // Act
    window.enter_fullscreen();

    // Assert
    if (window) {
        EXPECT_TRUE(window.is_fullscreen());
    }
}

TEST_F(WindowTestFixture, ExitFullscreen_Makes_Window_Windowed) {
    // Arrange
    Window window("Fullscreen Window", Vector2i(800, 600), WindowFlags::Hidden);
    window.enter_fullscreen(); // Assume this works
    ASSERT_TRUE(window.is_fullscreen());

    // Act
    window.exit_fullscreen();

    // Assert
    if (window) {
        EXPECT_FALSE(window.is_fullscreen());
    }
}

TEST_F(WindowTestFixture, GrabMouse_Confines_Mouse) {
    // Arrange
    Window window("Free Mouse Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_FALSE(window.is_mouse_grabbed());

    // Act
    window.grab_mouse();

    // Assert
    if (window) {
        EXPECT_TRUE(window.is_mouse_grabbed());
    }
}

TEST_F(WindowTestFixture, ReleaseMouse_Frees_Mouse) {
    // Arrange
    Window window("Grabbed Mouse Window", Vector2i(800, 600), WindowFlags::Hidden);
    window.grab_mouse(); // Assume this works
    ASSERT_TRUE(window.is_mouse_grabbed());

    // Act
    window.release_mouse();

    // Assert
    if (window) {
        EXPECT_FALSE(window.is_mouse_grabbed());
    }
}

TEST_F(WindowTestFixture, EnableAlwaysOnTop_Keeps_Window_OnTop) {
    // Arrange
    Window window("Normal Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_FALSE(window.is_always_on_top());

    // Act
    window.add_always_on_top();

    // Assert
    if (window) {
        EXPECT_TRUE(window.is_always_on_top());
    }
}

TEST_F(WindowTestFixture, DisableAlwaysOnTop_Allows_Window_ToBeObscured) {
    // Arrange
    Window window("Top Window", Vector2i(800, 600), WindowFlags::Hidden);
    window.add_always_on_top();
    ASSERT_TRUE(window.is_always_on_top());

    // Act
    window.remove_always_on_top();

    // Assert
    if (window) {
        EXPECT_FALSE(window.is_always_on_top());
    }
}

TEST_F(WindowTestFixture, GainFocus_Requests_Focus) {
    // Arrange
    Window window("Background Window", Vector2i(800, 600), WindowFlags::Hidden);
    ASSERT_FALSE(window.is_focused()); // Focus starts false (usually)

    // Act
    window.gain_focus();

    // Assert
    if (window) {
        EXPECT_TRUE(window.is_focused());
    }
}

TEST_F(WindowTestFixture, LoseFocus_Releases_Focus) {
    // Arrange
    Window window("Background Window", Vector2i(800, 600), WindowFlags::Hidden | WindowFlags::InputFocus);
    ASSERT_TRUE(window.is_focused());

    // Act
    window.lose_focus();

    // Assert
    if (window) {
        EXPECT_FALSE(window.is_focused());
    }
}