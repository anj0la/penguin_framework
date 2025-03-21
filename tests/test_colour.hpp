#include "include/penguin_framework/math/colour.hpp"
#include <gtest/gtest.h>

TEST(ColourTest, DefaultConstructor) {
	Colour colour;
	EXPECT_EQ(colour.r, 0);
	EXPECT_EQ(colour.g, 0);
	EXPECT_EQ(colour.b, 0);
	EXPECT_EQ(colour.a, 0);
}