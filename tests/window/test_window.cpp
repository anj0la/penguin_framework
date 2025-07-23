#include <penguin_framework/window/window.hpp>
#include <penguin_framework/penguin_init.hpp>
#include <gtest/gtest.h>

using penguin::window::Window;
using penguin::window::WindowFlags;
using penguin::math::Vector2i;

class WindowTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Window> window_ptr;
    std::unique_ptr<Window> invalid_window_ptr;

	void SetUp() override {
        penguin::InitOptions options{ .headless_mode = true };
        ASSERT_TRUE(penguin::init(options));

        window_ptr = std::make_unique<Window>("Test Window", Vector2i(640, 480), WindowFlags::Hidden | WindowFlags::Resizable); 
        ASSERT_TRUE(window_ptr->is_valid());

        invalid_window_ptr = std::make_unique<Window>("Invalid Window", Vector2i(-1, -1), static_cast<WindowFlags>(0xFFFFFFFF)); // the flag is a nonsensical value
        ASSERT_FALSE(invalid_window_ptr->is_valid());
	}

	void TearDown() override {
		penguin::quit();
	}
};

// Constructor
TEST_F(WindowTestFixture, Constructor_Creates_HiddenWindow) {
    // Arrange & Act (Implicit via constructor)
    const char* expected_title = "Test Window";
    const Vector2i expected_size(640, 480);

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_TRUE(*window_ptr); // testing bool() operator

    EXPECT_STREQ(window_ptr->get_title(), expected_title);
    EXPECT_EQ(window_ptr->get_width(), expected_size.x);
    EXPECT_EQ(window_ptr->get_height(), expected_size.y); 

    EXPECT_TRUE(window_ptr->is_hidden()); 
    EXPECT_TRUE(window_ptr->is_open());   
    EXPECT_TRUE(window_ptr->is_resizable());
    EXPECT_TRUE(window_ptr->is_bordered()); // Default is bordered unless Borderless flag is set

    EXPECT_FALSE(window_ptr->is_always_on_top());
    EXPECT_FALSE(window_ptr->is_focused());
    EXPECT_FALSE(window_ptr->is_fullscreen());
    EXPECT_FALSE(window_ptr->is_maximized());
    EXPECT_FALSE(window_ptr->is_minimized());
    EXPECT_FALSE(window_ptr->is_mouse_grabbed());
}

// Window Functions

TEST_F(WindowTestFixture, IsValid_WithValidWindow_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool is_valid = window_ptr->is_valid();

    // Assert
    EXPECT_TRUE(is_valid);
}

TEST_F(WindowTestFixture, BoolOperator_WithValidWindow_ReturnsTrue) {
    // Arrange (done in SetUp)

    // Act
    bool bool_result = static_cast<bool>(*window_ptr);

    // Assert
    EXPECT_TRUE(bool_result);
}

TEST_F(WindowTestFixture, SetTitle_Updates_Title) {
    // Arrange
    const char* expected_title = "Updated Title";
    ASSERT_STRNE(window_ptr->get_title(), expected_title);

    // Act
    window_ptr->set_title(expected_title);

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_STREQ(window_ptr->get_title(), expected_title);
}
TEST_F(WindowTestFixture, SetMaxSize_Restricts_Size) {
    // Arrange
    const Vector2i max_size(1024, 768);

    // Act
    window_ptr->set_max_size(max_size);

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    Vector2i actual_max_size = window_ptr->get_max_size();
    EXPECT_EQ(actual_max_size.x, max_size.x);
    EXPECT_EQ(actual_max_size.y, max_size.y);
}
TEST_F(WindowTestFixture, SetMaxSize_Keeps_Size) {
    // Arrange
    const Vector2i max_size(-100, -400);

    // Act
    window_ptr->set_max_size(max_size);

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    Vector2i actual_max_size = window_ptr->get_max_size();
    EXPECT_EQ(actual_max_size.x, window_ptr->get_width()); // the max size should be the window size if it has not been set by default
    EXPECT_EQ(actual_max_size.y, window_ptr->get_height());
}

TEST_F(WindowTestFixture, SetMinSize_Restricts_Size) {
    // Arrange
    const Vector2i min_size(400, 300);

    // Act
    window_ptr->set_min_size(min_size);

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    Vector2i actual_min_size = window_ptr->get_min_size();
    EXPECT_EQ(actual_min_size.x, min_size.x);
    EXPECT_EQ(actual_min_size.y, min_size.y);
}

TEST_F(WindowTestFixture, SetMinSize_Keeps_Size) {
    // Arrange
    const Vector2i min_size(-800, -600);

    // Act
    window_ptr->set_min_size(min_size);

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    Vector2i actual_min_size = window_ptr->get_min_size();
    EXPECT_EQ(actual_min_size.x, window_ptr->get_width()); // the min size should be the window size if it has not been set by default
    EXPECT_EQ(actual_min_size.y, window_ptr->get_height());
}

TEST_F(WindowTestFixture, Resize_Changes_Size) {
    // Arrange
    const Vector2i new_size(800, 600);
    ASSERT_NE(window_ptr->get_width(), new_size.x); 
    ASSERT_NE(window_ptr->get_height(), new_size.y);

    // Act
    window_ptr->resize(new_size);

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_EQ(window_ptr->get_width(), new_size.x);
    EXPECT_EQ(window_ptr->get_height(), new_size.y);
}

TEST_F(WindowTestFixture, Resize_Keeps_Size) {
    // Arrange
    const Vector2i expected_size(640, 480);
    const Vector2i new_size(-800, -600);
    ASSERT_NE(window_ptr->get_width(), new_size.x);
    ASSERT_NE(window_ptr->get_height(), new_size.y);

    // Act
    window_ptr->resize(new_size);

    // Assert
    EXPECT_TRUE(*window_ptr);
    EXPECT_EQ(window_ptr->get_width(), expected_size.x);
    EXPECT_EQ(window_ptr->get_height(), expected_size.y);
}

TEST_F(WindowTestFixture, Show_Makes_HiddenWindow_Visible) {
    // Arrange
    ASSERT_TRUE(window_ptr->is_hidden());

    // Act
    window_ptr->show();

    // Assert
    EXPECT_TRUE(*window_ptr);
    EXPECT_FALSE(window_ptr->is_hidden());
}

TEST_F(WindowTestFixture, Hide_Makes_VisibleWindow_Hidden) {
    // Arrange
    window_ptr->show();
    ASSERT_FALSE(window_ptr->is_hidden());

    // Act
    window_ptr->hide();

    // Assert
    EXPECT_TRUE(*window_ptr);
    EXPECT_TRUE(window_ptr->is_hidden());
}

TEST_F(WindowTestFixture, Minimize_Reduces_ResizableWindow) {
    // Arrange
    ASSERT_FALSE(window_ptr->is_minimized());
    ASSERT_TRUE(window_ptr->is_resizable());

    // Act
    window_ptr->minimize();

    // Assert
    // NOTE: The dummy video driver cannot actually minimize a window.
    // This test only ensures that our intent to minimize is recorded internally.
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_TRUE(window_ptr->is_minimized());
    EXPECT_FALSE(window_ptr->is_maximized());
}

TEST_F(WindowTestFixture, MinimizeAsync_Reduces_ResizableWindow) {
    // Arrange
    ASSERT_FALSE(window_ptr->is_minimized());
    ASSERT_TRUE(window_ptr->is_resizable());

    // Act
    window_ptr->minimize_async();

    // Assert
    // NOTE: The dummy video driver cannot actually minimize a window.
    // This test only ensures that our intent to minimize is recorded internally.
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_TRUE(window_ptr->is_minimized());
    EXPECT_FALSE(window_ptr->is_maximized());
}

TEST_F(WindowTestFixture, Maximize_Enlarges_ResizableWindow) {
    // Arrange
    ASSERT_FALSE(window_ptr->is_maximized());
    ASSERT_TRUE(window_ptr->is_resizable());

    // Act
    window_ptr->maximize();

    // Assert
    // NOTE: The dummy video driver cannot actually maximize a window.
    // This test only ensures that our intent to maximize is recorded internally.
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_TRUE(window_ptr->is_maximized());
    EXPECT_FALSE(window_ptr->is_minimized());
}

TEST_F(WindowTestFixture, MaximizeAsync_Enlarges_ResizableWindow) {
    // Arrange
    ASSERT_FALSE(window_ptr->is_maximized());
    ASSERT_TRUE(window_ptr->is_resizable());

    // Act
    window_ptr->maximize_async();

    // Assert
    // NOTE: The dummy video driver cannot actually maximize a window.
    // This test only ensures that our intent to maximize is recorded internally.
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_TRUE(window_ptr->is_maximized());
    EXPECT_FALSE(window_ptr->is_minimized());
}

TEST_F(WindowTestFixture, Restore_Returns_MinimizedWindow_ToNormal) {
    // Arrange
    window_ptr->minimize();
    ASSERT_TRUE(window_ptr->is_minimized());

    // Act
    window_ptr->restore();

    // Assert
    // NOTE: The dummy video driver cannot actually restore a minimized window.
    // This test only ensures that our intent to restore is recorded internally.
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_FALSE(window_ptr->is_minimized());
    EXPECT_FALSE(window_ptr->is_maximized());
}

TEST_F(WindowTestFixture, Restore_Returns_MaximizedWindow_ToNormal) {
    // Arrange
    window_ptr->maximize();
    ASSERT_TRUE(window_ptr->is_maximized());

    // Act
    window_ptr->restore();

    // Assert
    // NOTE: The dummy video driver cannot actually restore a maximized window.
    // This test only ensures that our intent to restore is recorded internally.
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_FALSE(window_ptr->is_maximized());
    EXPECT_FALSE(window_ptr->is_minimized());
}

TEST_F(WindowTestFixture, RestoreAsync_Call_Succeeds) {
    // Arrange
    window_ptr->minimize();
    ASSERT_TRUE(window_ptr->is_minimized());

    // Act
    window_ptr->restore_async();

    // Assert
    // NOTE: The dummy video driver cannot actually maximize a window.
    // This test only ensures that our intent to restore is recorded internally.
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_FALSE(window_ptr->is_maximized());
    EXPECT_FALSE(window_ptr->is_minimized());
}

TEST_F(WindowTestFixture, EnableResizing_Makes_Window_Resizable) {
    // Arrange
    window_ptr->disable_resizing();
    ASSERT_FALSE(window_ptr->is_resizable());

    // Act
    window_ptr->enable_resizing();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_TRUE(window_ptr->is_resizable());
}

TEST_F(WindowTestFixture, DisableResizing_Makes_Window_Fixed) {
    // Arrange
    ASSERT_TRUE(window_ptr->is_resizable());

    // Act
    window_ptr->disable_resizing();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_FALSE(window_ptr->is_resizable());
}

TEST_F(WindowTestFixture, DisableBorders_Removes_Border) {
    // Arrange
    ASSERT_TRUE(window_ptr->is_bordered()); // Starts bordered (default)

    // Act
    window_ptr->disable_borders();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_FALSE(window_ptr->is_bordered());
}

TEST_F(WindowTestFixture, EnableBorders_Adds_Border) {
    // Arrange
    window_ptr->disable_borders(); // Make it borderless first
    ASSERT_FALSE(window_ptr->is_bordered());

    // Act
    window_ptr->enable_borders();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_TRUE(window_ptr->is_bordered());
}

TEST_F(WindowTestFixture, EnterFullscreen_Makes_Window_Fullscreen) {
    // Arrange
    ASSERT_FALSE(window_ptr->is_fullscreen());

    // Act
    window_ptr->enter_fullscreen();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_TRUE(window_ptr->is_fullscreen());
}

TEST_F(WindowTestFixture, ExitFullscreen_Makes_Window_Windowed) {
    // Arrange
    window_ptr->enter_fullscreen(); // Assume this works
    ASSERT_TRUE(window_ptr->is_fullscreen());

    // Act
    window_ptr->exit_fullscreen();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_FALSE(window_ptr->is_fullscreen());
}

TEST_F(WindowTestFixture, GrabMouse_Confines_Mouse) {
    // Arrange
    ASSERT_FALSE(window_ptr->is_mouse_grabbed());

    // Act
    window_ptr->grab_mouse();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_TRUE(window_ptr->is_mouse_grabbed());
}

TEST_F(WindowTestFixture, ReleaseMouse_Frees_Mouse) {
    // Arrange
    window_ptr->grab_mouse(); // Assume this works
    ASSERT_TRUE(window_ptr->is_mouse_grabbed());

    // Act
    window_ptr->release_mouse();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_FALSE(window_ptr->is_mouse_grabbed());
}

TEST_F(WindowTestFixture, EnableAlwaysOnTop_Keeps_Window_OnTop) {
    // Arrange
    ASSERT_FALSE(window_ptr->is_always_on_top());

    // Act
    window_ptr->add_always_on_top();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_TRUE(window_ptr->is_always_on_top());
}

TEST_F(WindowTestFixture, DisableAlwaysOnTop_Allows_Window_ToBeObscured) {
    // Arrange
    window_ptr->add_always_on_top();
    ASSERT_TRUE(window_ptr->is_always_on_top());

    // Act
    window_ptr->remove_always_on_top();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_FALSE(window_ptr->is_always_on_top());
}

TEST_F(WindowTestFixture, GainFocus_Requests_Focus) {
    // Arrange
    ASSERT_FALSE(window_ptr->is_focused()); // Focus starts false (usually)

    // Act
    window_ptr->gain_focus();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_TRUE(window_ptr->is_focused());
}

TEST_F(WindowTestFixture, LoseFocus_Releases_Focus) {
    // Arrange
    window_ptr->gain_focus(); // Make it focused first
    ASSERT_TRUE(window_ptr->is_focused());

    // Act
    window_ptr->lose_focus();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_FALSE(window_ptr->is_focused());
}


TEST_F(WindowTestFixture, GetNativePtr_WithValidWindow_ReturnsNonNullPtr) {
    // Arrange (done in SetUp)

    // Act
    auto native_ptr = window_ptr->get_native_ptr();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_NE(native_ptr.ptr, nullptr);
}

// Other Window Tests

TEST_F(WindowTestFixture, Minimize_DoesNothing_On_NonResizableWindow) {
    // Arrange
    window_ptr->disable_resizing(); // Make it non-resizable
    ASSERT_FALSE(window_ptr->is_resizable());
    ASSERT_FALSE(window_ptr->is_minimized());

    // Act
    window_ptr->minimize();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_FALSE(window_ptr->is_minimized());
}

TEST_F(WindowTestFixture, Maximize_DoesNothing_On_NonResizableWindow) {
    // Arrange
    window_ptr->disable_resizing(); // Make it non-resizable
    ASSERT_FALSE(window_ptr->is_resizable());
    ASSERT_FALSE(window_ptr->is_maximized());

    // Act
    window_ptr->maximize();

    // Assert
    EXPECT_TRUE(window_ptr->is_valid());
    EXPECT_FALSE(window_ptr->is_maximized());
}

// Invalid Window Operations

TEST_F(WindowTestFixture, IsValid_WithInvalidWindow_ReturnsFalse) {
    // Arrange (done in SetUp)

    // Act
    bool is_valid = invalid_window_ptr->is_valid();

    // Assert
    EXPECT_FALSE(is_valid);
}

TEST_F(WindowTestFixture, BoolOperator_WithInvalidWindow_ReturnsFalse) {
    // Arrange (done in SetUp)

    // Act
    bool bool_result = static_cast<bool>(*invalid_window_ptr);

    // Assert
    EXPECT_FALSE(bool_result);
}

TEST_F(WindowTestFixture, SetTitle_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->set_title("New Title");

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, SetMaxSize_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->set_max_size(Vector2i(1024, 768));

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, SetMinSize_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->set_min_size(Vector2i(400, 300));

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, Resize_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->resize(Vector2i(640, 480));

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, Show_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->show();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, Hide_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->hide();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, Minimize_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->minimize();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, MinimizeAsync_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->minimize_async();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, Maximize_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->maximize();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, MaximizeAsync_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->maximize_async();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, Restore_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->restore();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, RestoreAsync_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->restore_async();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, EnableResizing_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->enable_resizing();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, DisableResizing_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->disable_resizing();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, DisableBorders_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->disable_borders();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, EnableBorders_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->enable_borders();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, EnterFullscreen_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->enter_fullscreen();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, ExitFullscreen_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->exit_fullscreen();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, GrabMouse_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->grab_mouse();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, ReleaseMouse_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->release_mouse();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, EnableAlwaysOnTop_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->add_always_on_top();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, DisableAlwaysOnTop_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->remove_always_on_top();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, GainFocus_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->gain_focus();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, LoseFocus_WithInvalidWindow_WindowRemainsInvalid) {
    // Arrange (done in SetUp)

    // Act
    invalid_window_ptr->lose_focus();

    // Assert
    EXPECT_FALSE(invalid_window_ptr->is_valid());
}

TEST_F(WindowTestFixture, GetNativePtr_WithInvalidWindow_ReturnsNullPtr) {
    // Arrange (done in SetUp)

    // Act
    auto native_ptr = invalid_window_ptr->get_native_ptr();

    // Assert
    EXPECT_EQ(native_ptr.ptr, nullptr);
}