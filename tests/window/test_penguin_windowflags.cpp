#include <penguin_framework/window/penguin_windowflags.hpp>
#include <gtest/gtest.h>

using penguin::window::WindowFlags;
using penguin::window::has_flag;

// Simple tests to ensure that the flag operators work correctly
// Since the flags map to SDL flags, they are essentially the same values as their SDL counterparts
// This means that there's no need to test that a flags == SDL_flag equivaent

TEST(WindowFlagsTest, OrCombinesFlagsCorrectly) {
    // Arrange
    auto flags = WindowFlags::Hidden | WindowFlags::Resizable;

    // Act
    bool res1 = has_flag(flags, WindowFlags::Hidden);
    bool res2 = has_flag(flags, WindowFlags::Resizable);

    // Assert - Validate that both flags exist
    EXPECT_TRUE(res1);
    EXPECT_TRUE(res2);
}

TEST(WindowFlagsTest, NotInvertsFlag) {
    // Arrange
    auto all = WindowFlags::Hidden | WindowFlags::Resizable | WindowFlags::AlwaysOnTop;

    // Act
    auto not_hidden = all & ~WindowFlags::Hidden;
    bool res1 = has_flag(not_hidden, WindowFlags::Resizable);
    bool res2 = has_flag(not_hidden, WindowFlags::Hidden);

    // Assert - Validate flag checks
    EXPECT_TRUE(res1);
    EXPECT_FALSE(res2);
}
