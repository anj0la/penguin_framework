#include "core/math/colour.hpp"
#include <gtest/gtest.h>

TEST(ColourTest, DefaultConstructor) {
	Colour colour;
	EXPECT_EQ(colour.r, 0);
	EXPECT_EQ(colour.g, 0);
	EXPECT_EQ(colour.b, 0);
	EXPECT_EQ(colour.a, 255);
}

TEST(ColourTest, RegularConstructor) {
	Colour colour(100, 150, 200, 255);
	EXPECT_EQ(colour.r, 100);
	EXPECT_EQ(colour.g, 150);
	EXPECT_EQ(colour.b, 200);
	EXPECT_EQ(colour.a, 255);
}

TEST(ColourTest, RegularConstructorClamped) {
	Colour colour(-10, 300, 100, 500);
	EXPECT_EQ(colour.r, 255); // Representation is unsigned, so clamped to max by default
	EXPECT_EQ(colour.g, 255); // Clamped to max
	EXPECT_EQ(colour.b, 100); // Not clamped
	EXPECT_EQ(colour.a, 255); // Clamped to max
}