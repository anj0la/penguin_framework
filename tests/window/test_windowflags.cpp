#include "core/window/pf_windowflags.hpp"
#include <gtest/gtest.h>

using pf::core::PF_WindowFlags;

// Simple tests to ensure that the flag operators work correctly
// Since the flags map to SDL flags, they are essentially the same values as their SDL counterparts
// This means that there's no need to test that the flags == SDL_flah

TEST(WindowFlagsTest, OrCombinesFlagsCorrectly) {
    PF_WindowFlags flags = PF_WindowFlags::Hidden | PF_WindowFlags::Resizable;
    EXPECT_TRUE(has_flag(flags, PF_WindowFlags::Hidden));
    EXPECT_TRUE(has_flag(flags, PF_WindowFlags::Resizable));
}

TEST(WindowFlagsTest, AndChecksCorrectly) {
    PF_WindowFlags flags = PF_WindowFlags::Borderless | PF_WindowFlags::Fullscreen;
    EXPECT_TRUE(has_flag(flags, PF_WindowFlags::Fullscreen));
    EXPECT_FALSE(has_flag(flags, PF_WindowFlags::Resizable));
}

TEST(WindowFlagsTest, NotInvertsFlag) {
    PF_WindowFlags all = PF_WindowFlags::Hidden | PF_WindowFlags::Resizable | PF_WindowFlags::AlwaysOnTop;
    PF_WindowFlags not_hidden = all & ~PF_WindowFlags::Hidden;
    EXPECT_FALSE(has_flag(not_hidden, PF_WindowFlags::Hidden));
    EXPECT_TRUE(has_flag(not_hidden, PF_WindowFlags::Resizable));
}
