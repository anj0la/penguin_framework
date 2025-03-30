#include "math/rect2.hpp"
#include <gtest/gtest.h>

// Setting Up the Test Suite

class Rect2TestFixture : public ::testing::Test {
protected:
	Rect2 rect1, rect2;

	void SetUp() override {
		rect1 = Rect2(100.0f, 150.0f, 100.0f, 100.0f);
		rect2 = Rect2(200.0f, 100.0f, 50.0f, 50.0f);
	};

};

// Constructor Tests

TEST(Rect2ConstructorTest, DefaultConstructor) {
	Rect2 rect;
	EXPECT_FLOAT_EQ(rect.position.x, 0.0f);
	EXPECT_FLOAT_EQ(rect.position.y, 0.0f);
	EXPECT_FLOAT_EQ(rect.size.x, 0.0f);
	EXPECT_FLOAT_EQ(rect.size.y, 0.0f);
}

TEST(Rect2ConstructorTest, RegularConstructor) {
	Rect2 rect(100.0f, 150.0f, 100.0f, 100.0f);
	EXPECT_FLOAT_EQ(rect.position.x, 100.0f);
	EXPECT_FLOAT_EQ(rect.position.y, 150.0f);
	EXPECT_FLOAT_EQ(rect.size.x, 100.0f);
	EXPECT_FLOAT_EQ(rect.size.y, 100.0f);
}

TEST(Rect2ConstructorTest, RegularConstructorVector) {
	Rect2 rect(Vector2(100.0f, 150.0f), Vector2(100.0f, 100.0f));
	EXPECT_FLOAT_EQ(rect.position.x, 100.0f);
	EXPECT_FLOAT_EQ(rect.position.y, 150.0f);
	EXPECT_FLOAT_EQ(rect.size.x, 100.0f);
	EXPECT_FLOAT_EQ(rect.size.y, 100.0f);
}

// Comparison Operator Tests

TEST_F(Rect2TestFixture, EqualityOperator) {
	EXPECT_FALSE(rect1 == rect2);
}

TEST_F(Rect2TestFixture, NotEqualOperator) {
	EXPECT_TRUE(rect1 != rect2);
}

// Binary Operator Tests

TEST_F(Rect2TestFixture, AddRects) {
	Rect2 result = rect1 + rect2;
	EXPECT_FLOAT_EQ(result.position.x, 300.0f);
	EXPECT_FLOAT_EQ(result.position.y, 250.0f);
	EXPECT_FLOAT_EQ(result.size.x, 150.0f);
	EXPECT_FLOAT_EQ(result.size.y, 150.0f);
}

TEST_F(Rect2TestFixture, SubRects) {
	Rect2 result = rect1 - rect2;
	EXPECT_FLOAT_EQ(result.position.x, -100.0f);
	EXPECT_FLOAT_EQ(result.position.y, 50.0f);
	EXPECT_FLOAT_EQ(result.size.x, 50.0f);
	EXPECT_FLOAT_EQ(result.size.y, 50.0f);
}

// Assignment Operator Tests

TEST_F(Rect2TestFixture, AddRectsAssignment) {
	rect1 += rect2;
	EXPECT_FLOAT_EQ(rect1.position.x, 300.0f);
	EXPECT_FLOAT_EQ(rect1.position.y, 250.0f);
	EXPECT_FLOAT_EQ(rect1.size.x, 150.0f);
	EXPECT_FLOAT_EQ(rect1.size.y, 150.0f);
}

TEST_F(Rect2TestFixture, SubRectsAssignment) {
	rect1 -= rect2;
	EXPECT_FLOAT_EQ(rect1.position.x, -100.0f);
	EXPECT_FLOAT_EQ(rect1.position.y, 50.0f);
	EXPECT_FLOAT_EQ(rect1.size.x, 50.0f);
	EXPECT_FLOAT_EQ(rect1.size.y, 50.0f);
}

// Scalar Operator Tests

TEST_F(Rect2TestFixture, AddRectsScalar) {
	Rect2 result = rect1 + 50.0f;
	EXPECT_FLOAT_EQ(result.position.x, 150.0f);
	EXPECT_FLOAT_EQ(result.position.y, 200.0f);
	EXPECT_FLOAT_EQ(result.size.x, 150.0f);
	EXPECT_FLOAT_EQ(result.size.y, 150.0f);
}

TEST_F(Rect2TestFixture, SubRectsScalar) {
	Rect2 result = rect1 - 50.0f;
	EXPECT_FLOAT_EQ(result.position.x, 50.0f);
	EXPECT_FLOAT_EQ(result.position.y, 100.0f);
	EXPECT_FLOAT_EQ(result.size.x, 50.0f);
	EXPECT_FLOAT_EQ(result.size.y, 50.0f);
}

TEST_F(Rect2TestFixture, MultRectsScalar) {
	Rect2 result = rect1 * 2.0f;
	EXPECT_FLOAT_EQ(result.position.x, 200.0f);
	EXPECT_FLOAT_EQ(result.position.y, 300.0f);
	EXPECT_FLOAT_EQ(result.size.x, 200.0f);
	EXPECT_FLOAT_EQ(result.size.y, 200.0f);
}

TEST_F(Rect2TestFixture, DivRectsScalar) {
	Rect2 result = rect1 / 2.0f;
	EXPECT_FLOAT_EQ(result.position.x, 50.0f);
	EXPECT_FLOAT_EQ(result.position.y, 75.0f);
	EXPECT_FLOAT_EQ(result.size.x, 50.0f);
	EXPECT_FLOAT_EQ(result.size.y, 50.0f);
}

// Scalar Assignment Operator Tests

TEST_F(Rect2TestFixture, AddRectsScalarAssignment) {
	rect1 += 50.0f;
	EXPECT_FLOAT_EQ(rect1.position.x, 150.0f);
	EXPECT_FLOAT_EQ(rect1.position.y, 200.0f);
	EXPECT_FLOAT_EQ(rect1.size.x, 150.0f);
	EXPECT_FLOAT_EQ(rect1.size.y, 150.0f);
}

TEST_F(Rect2TestFixture, SubRectsScalarAssignment) {
	rect1 -= 50.0f;
	EXPECT_FLOAT_EQ(rect1.position.x, 50.0f);
	EXPECT_FLOAT_EQ(rect1.position.y, 100.0f);
	EXPECT_FLOAT_EQ(rect1.size.x, 50.0f);
	EXPECT_FLOAT_EQ(rect1.size.y, 50.0f);
}

TEST_F(Rect2TestFixture, MultRectsScalarAssignment) {
	rect1 *= 2.0f;
	EXPECT_FLOAT_EQ(rect1.position.x, 200.0f);
	EXPECT_FLOAT_EQ(rect1.position.y, 300.0f);
	EXPECT_FLOAT_EQ(rect1.size.x, 200.0f);
	EXPECT_FLOAT_EQ(rect1.size.y, 200.0f);
}

TEST_F(Rect2TestFixture, DivRectsScalarAssignment) {
	rect1 /= 2.0f;
	EXPECT_FLOAT_EQ(rect1.position.x, 50.0f);
	EXPECT_FLOAT_EQ(rect1.position.y, 75.0f);
	EXPECT_FLOAT_EQ(rect1.size.x, 50.0f);
	EXPECT_FLOAT_EQ(rect1.size.y, 50.0f);
}	

// Other Function Tests

TEST_F(Rect2TestFixture, AreaFunction) {
	float result = rect1.area();
	EXPECT_FLOAT_EQ(result, 10000.0f);
}

TEST_F(Rect2TestFixture, PerimeterFunction) {
	float result = rect1.perimeter();
	EXPECT_FLOAT_EQ(result, 400.0f);
}

TEST_F(Rect2TestFixture, CenterFunction) {
	Vector2 result = rect1.center();
	EXPECT_FLOAT_EQ(result.x, 150.0f);
	EXPECT_FLOAT_EQ(result.y, 200.0f);
}

TEST_F(Rect2TestFixture, ContainsFunction) {
	Vector2 point(150.0f, 200.0f);
	bool result = rect1.contains(point);
	EXPECT_TRUE(result);
}

TEST_F(Rect2TestFixture, IntersectsFunction) {
	// Rectangle 1: (100.0f, 150.0f, 100.0f, 100.0f)
	// Rectangle 2: (200.0f, 100.0f, 50.0f, 50.0f)

	// Checking intersection conditions:
	// 100.0f < 200.0f + 50.0f (100.0f < 250.0f) 
	// 100.0f + 100.0f > 200.0f (200.0f > 200.0f) - Fails, no horizontal overlap
	// 150.0f < 100.0f + 50.0f (150.0f < 150.0f) - Fails, no vertical overlap
	// 150.0f + 100.0f > 100.0f (250.0f > 100.0f)

	bool result = rect1.intersects(rect2);
	EXPECT_FALSE(result); // The rects do NOT intersect since at least one condition fails
}

// Regular Tests (No Fixture) - Edge Cases

TEST(Rect2Test, ContainsFunctionEdgeCase) {
	Rect2 rect(0.0f, 0.0f, 0.0f, 0.0f);
	Vector2 point(0.0f, 0.0f);
	bool result = rect.contains(point);
	EXPECT_TRUE(result);
}

TEST(Rect2Test, IntersectsFunctionEdgeCase) {
	Rect2 rect1(0.0f, 0.0f, 0.0f, 0.0f);
	Rect2 rect2(0.0f, 0.0f, 0.0f, 0.0f);
	bool result = rect1.intersects(rect2);
	EXPECT_FALSE(result);
}