#include <penguin_framework/core/math/rect2i.hpp>
#include <gtest/gtest.h>

// Setting Up the Test Suite

class Rect2iTestFixture : public ::testing::Test {
protected:
	Rect2i rect1, rect2;
	void SetUp() override {
		rect1 = Rect2i(50, 75, 100, 25);
		rect2 = Rect2i(100, 150, 150, 75);
	};
};

// Constructor Tests

TEST(Rect2iConstructorTest, DefaultConstructor) {
	Rect2i rect;
	EXPECT_EQ(rect.position.x, 0);
	EXPECT_EQ(rect.position.y, 0);
	EXPECT_EQ(rect.size.x, 0);
	EXPECT_EQ(rect.size.y, 0);
}

TEST(Rect2iConstructorTest, RegularConstructor) {
	Rect2i rect(50, 75, 100, 25);
	EXPECT_EQ(rect.position.x, 50);
	EXPECT_EQ(rect.position.y, 75);
	EXPECT_EQ(rect.size.x, 100);
	EXPECT_EQ(rect.size.y, 25);
}

TEST(Rect2iConstructorTest, RegularConstructorVector) {
	Rect2i rect(Vector2i(50, 75), Vector2i(100, 25));
	EXPECT_EQ(rect.position.x, 50);
	EXPECT_EQ(rect.position.y, 75);
	EXPECT_EQ(rect.size.x, 100);
	EXPECT_EQ(rect.size.y, 25);
}
// Comparison Operator Tests

TEST_F(Rect2iTestFixture, EqualityOperator) {
	EXPECT_FALSE(rect1 == rect2);
}

TEST_F(Rect2iTestFixture, NotEqualOperator) {
	EXPECT_TRUE(rect1 != rect2);
}

// Other Function Tests

TEST_F(Rect2iTestFixture, AreaFunction) {
	EXPECT_EQ(rect1.area(), 2500);
}

TEST_F(Rect2iTestFixture, PerimeterFunction) {
	EXPECT_EQ(rect1.perimeter(), 250);
}

TEST_F(Rect2iTestFixture, CenterFunction) {
	Vector2i result = rect1.center();
	EXPECT_EQ(result.x, 100);
	EXPECT_EQ(result.y, 87);
}

TEST_F(Rect2iTestFixture, ContainsFunction) {
	Vector2i point(150, 200);
	bool result = rect1.contains(point);
	EXPECT_FALSE(result);
}

TEST_F(Rect2iTestFixture, IntersectsFunction) {
	// Rectangle 1: (50, 75, 100, 25)
	// Rectangle 2: (100, 150, 150, 75)

	// Checking intersection conditions:
	// 50 < 100 + 150 (50 < 250)
	// 50 + 100 > 100 (150 > 100)
	// 75 < 150 + 75 (75 < 225)
	// 75 + 25 > 150 (100 > 150) - Fails, no vertical overlap

	bool result = rect1.intersects(rect2); // The rects do NOT intersect since at least one condition fails
	EXPECT_FALSE(result);
}

// Regular Tests (No Fixture) - Edge Cases

TEST(Rect2iTest, ContainsFunctionEdgeCase) {
	Rect2i rect(0, 0, 0, 0);
	Vector2i point(0, 0);
	bool result = rect.contains(point);
	EXPECT_TRUE(result);
}

TEST(Rect2iTest, IntersectsFunctionEdgeCase) {
	Rect2i rect1(0, 0, 0, 0);
	Rect2i rect2(0, 0, 0, 0);
	bool result = rect1.intersects(rect2);
	EXPECT_FALSE(result);
}