#include "../../include/penguin_framework/math/colour.hpp"
#include <gtest/gtest.h>

TEST(ColourTest, DefaultConstructor) {
	Colour colour;
	EXPECT_EQ(colour.r, 0);
	EXPECT_EQ(colour.g, 0);
	EXPECT_EQ(colour.b, 0);
	EXPECT_EQ(colour.a, 255);
}

TEST(ColourTest, RegularConstructor) {
	Colour colour(255, 255, 255, 255);
	EXPECT_EQ(colour.r, 255);
	EXPECT_EQ(colour.g, 255);
	EXPECT_EQ(colour.b, 255);
	EXPECT_EQ(colour.a, 255);
}

TEST(ColourTest, CopyConstructor) {
	Colour colour(255, 255, 255, 255);
	Colour copy(colour);
	EXPECT_EQ(copy.r, 255);
	EXPECT_EQ(copy.g, 255);
	EXPECT_EQ(copy.b, 255);
	EXPECT_EQ(copy.a, 255);
}

TEST(ColourTest, MoveConstructor) {
	Colour colour(255, 255, 255, 255);
	Colour move(std::move(colour));
	EXPECT_EQ(move.r, 255);
	EXPECT_EQ(move.g, 255);
	EXPECT_EQ(move.b, 255);
	EXPECT_EQ(move.a, 255);
}

TEST(ColourTest, CopyAssignmentOperator) {
	Colour colour(255, 255, 255, 255);
	Colour copy;
	copy = colour;
	EXPECT_EQ(copy.r, 255);
	EXPECT_EQ(copy.g, 255);
	EXPECT_EQ(copy.b, 255);
	EXPECT_EQ(copy.a, 255);
}

TEST(ColourTest, MoveAssignmentOperator) {
	Colour colour(255, 255, 255, 255);
	Colour move;
	move = std::move(colour);
	EXPECT_EQ(move.r, 255);
	EXPECT_EQ(move.g, 255);
	EXPECT_EQ(move.b, 255);
	EXPECT_EQ(move.a, 255);
}