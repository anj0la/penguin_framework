#include <penguin_framework/core/math/circle2.hpp>
#include <gtest/gtest.h>

// Setting Up the Test Suite

class Circle2TestFixture : public ::testing::Test {
protected:
	Circle2 circle1, circle2;
	void SetUp() override {
		circle1 = Circle2(Vector2(100.0f, 150.0f), 50.0f);
		circle2 = Circle2(Vector2(200.0f, 100.0f), 25.0f);
	};
};

// Constructor Tests

TEST(Circle2ConstructorTest, DefaultConstructor) {
	Circle2 circle;
	EXPECT_FLOAT_EQ(circle.center.x, 0.0f);
	EXPECT_FLOAT_EQ(circle.center.y, 0.0f);
	EXPECT_FLOAT_EQ(circle.radius, 0.0f);
}

TEST(Circle2ConstructorTest, RegularConstructor) {
	Circle2 circle(100.0f, 150.0f, 50.0f);
	EXPECT_FLOAT_EQ(circle.center.x, 100.0f);
	EXPECT_FLOAT_EQ(circle.center.y, 150.0f);
	EXPECT_FLOAT_EQ(circle.radius, 50.0f);
}

TEST(Circle2ConstructorTest, RegularConstructorVector) {
	Circle2 circle(Vector2(100.0f, 150.0f), 50.0f);
	EXPECT_FLOAT_EQ(circle.center.x, 100.0f);
	EXPECT_FLOAT_EQ(circle.center.y, 150.0f);
	EXPECT_FLOAT_EQ(circle.radius, 50.0f);
}

// Equality Operators

TEST_F(Circle2TestFixture, EqualityOperator) {
	EXPECT_FALSE(circle1 == circle2);
}

TEST_F(Circle2TestFixture, NotEqualOperator) {
	EXPECT_TRUE(circle1 != circle2);
}

// Other Function Tests

TEST_F(Circle2TestFixture, AreaFunction) {
	float result = circle1.area();
	EXPECT_FLOAT_EQ(result, 7853.98193359375f);
}

TEST_F(Circle2TestFixture, CircumferenceFunction) {
	float result = circle1.circumference();
	EXPECT_FLOAT_EQ(result, 314.1592712402344f);
}