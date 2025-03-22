#include "include/penguin_framework/math/vector2.hpp"
#include <gtest/gtest.h>

// Constructor Tests

TEST(Vector2Test, DefaultConstructor) {
	Vector2 vector;
	EXPECT_EQ(vector.x, 0.0f);
	EXPECT_EQ(vector.y, 0.0f);
}

TEST(Vector2Test, RegularConstructor) {
	Vector2 vector(1.0f, 1.0f);
	EXPECT_EQ(vector.x, 1.0f);
	EXPECT_EQ(vector.y, 1.0f);
}

TEST(Vector2Test, RegularConstructorScalar) {
	Vector2 vector(1.0f);
	EXPECT_EQ(vector.x, 1.0f);
	EXPECT_EQ(vector.y, 1.0f);
}

TEST(Vector2Test, CopyConstructor) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 copy(vector);
	EXPECT_EQ(copy.x, 1.0f);
	EXPECT_EQ(copy.y, 1.0f);
}

TEST(Vector2Test, MoveConstructor) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 move(std::move(vector));
	EXPECT_EQ(move.x, 1.0f);
	EXPECT_EQ(move.y, 1.0f);
}

TEST(Vector2Test, CopyAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 copy;
	copy = vector;
	EXPECT_EQ(copy.x, 1.0f);
	EXPECT_EQ(copy.y, 1.0f);
}

TEST(Vector2Test, MoveAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 move;
	move = std::move(vector);
	EXPECT_EQ(move.x, 1.0f);
	EXPECT_EQ(move.y, 1.0f);
}

// Binary Operator Tests

TEST(Vector2Test, AddOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(1.0f, 1.0f);
	Vector2 result = vector1 + vector2;
	EXPECT_EQ(result.x, 2.0f);
	EXPECT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, SubOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(1.0f, 1.0f);
	Vector2 result = vector1 - vector2;
	EXPECT_EQ(result.x, 0.0f);
	EXPECT_EQ(result.y, 0.0f);
}

TEST(Vector2Test, MultOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	Vector2 result = vector1 * vector2;
	EXPECT_EQ(result.x, 2.0f);
	EXPECT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, DivOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	Vector2 result = vector1 / vector2;
	EXPECT_EQ(result.x, 0.5f);
	EXPECT_EQ(result.y, 0.5f);
}

// Assignment Operator Tests

TEST(Vector2Test, AddAssignmentOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(1.0f, 1.0f);
	vector1 += vector2;
	EXPECT_EQ(vector1.x, 2.0f);
	EXPECT_EQ(vector1.y, 2.0f);
}

TEST(Vector2Test, SubAssignmentOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(1.0f, 1.0f);
	vector1 -= vector2;
	EXPECT_EQ(vector1.x, 0.0f);
	EXPECT_EQ(vector1.y, 0.0f);
}

TEST(Vector2Test, MultAssignmentOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	vector1 *= vector2;
	EXPECT_EQ(vector1.x, 2.0f);
	EXPECT_EQ(vector1.y, 2.0f);
}

TEST(Vector2Test, DivAssignmentOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	vector1 /= vector2;
	EXPECT_EQ(vector1.x, 0.5f);
	EXPECT_EQ(vector1.y, 0.5f);
}

// Comparison Operator Tests

TEST(Vector2Test, EqualOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(1.0f, 1.0f);
	EXPECT_TRUE(vector1 == vector2);
}

TEST(Vector2Test, EqualOperatorFalse) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	EXPECT_FALSE(vector1 == vector2);
}

TEST(Vector2Test, NotEqualOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	EXPECT_TRUE(vector1 != vector2);
}

TEST(Vector2Test, NotEqualOperatorFalse) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(1.0f, 1.0f);
	EXPECT_FALSE(vector1 != vector2);
}

TEST(Vector2Test, LessThanOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	EXPECT_TRUE(vector1 < vector2);
}
	
TEST(Vector2Test, LessThanOperatorFalse) {
	Vector2 vector1(2.0f, 2.0f);
	Vector2 vector2(1.0f, 1.0f);
	EXPECT_FALSE(vector1 < vector2);
}

TEST(Vector2Test, GreaterThanOperator) {
	Vector2 vector1(2.0f, 2.0f);
	Vector2 vector2(1.0f, 1.0f);
	EXPECT_TRUE(vector1 > vector2);
}

TEST(Vector2Test, GreaterThanOperatorFalse) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	EXPECT_FALSE(vector1 > vector2);
}

TEST(Vector2Test, LessThanEqualOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	EXPECT_TRUE(vector1 <= vector2);
}

TEST(Vector2Test, LessThanEqualOperatorFalse) {
	Vector2 vector1(2.0f, 2.0f);
	Vector2 vector2(1.0f, 1.0f);
	EXPECT_FALSE(vector1 <= vector2);
}

TEST(Vector2Test, GreaterThanEqualOperator) {
	Vector2 vector1(2.0f, 2.0f);
	Vector2 vector2(1.0f, 1.0f);
	EXPECT_TRUE(vector1 >= vector2);
}

TEST(Vector2Test, GreaterThanEqualOperatorFalse) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	EXPECT_FALSE(vector1 >= vector2);
}

// Unary Operator Tests

TEST(Vector2Test, NegationOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = -vector;
	EXPECT_EQ(result.x, -1.0f);
	EXPECT_EQ(result.y, -1.0f);
}

TEST(Vector2Test, NotOperator) {
	Vector2 vector(1.0f, 1.0f);
	EXPECT_TRUE(!vector);
}

// Scalar Operator Tests

TEST(Vector2Test, AddScalarOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = vector + 1.0f;
	EXPECT_EQ(result.x, 2.0f);
	EXPECT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, AddScalarRightOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = 1.0f + vector;
	EXPECT_EQ(result.x, 2.0f);
	EXPECT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, SubScalarOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = vector - 1.0f;
	EXPECT_EQ(result.x, 0.0f);
	EXPECT_EQ(result.y, 0.0f);
}

TEST(Vector2Test, SubScalarRightOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = 1.0f - vector;
	EXPECT_EQ(result.x, 0.0f);
	EXPECT_EQ(result.y, 0.0f);
}

TEST(Vector2Test, MultScalarOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = vector * 2.0f;
	EXPECT_EQ(result.x, 2.0f);
	EXPECT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, MultScalarRightOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = 2.0f * vector;
	EXPECT_EQ(result.x, 2.0f);
	EXPECT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, DivScalarOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = vector / 2.0f;
	EXPECT_EQ(result.x, 0.5f);
	EXPECT_EQ(result.y, 0.5f);
}

TEST(Vector2Test, DivScalarRightOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = 2.0f / vector;
	EXPECT_EQ(result.x, 2.0f);
	EXPECT_EQ(result.y, 2.0f);
}

// Scalar Assignment Operator Tests

TEST(Vector2Test, AddScalarAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	vector += 1.0f;
	EXPECT_EQ(vector.x, 2.0f);
	EXPECT_EQ(vector.y, 2.0f);
}

TEST(Vector2Test, SubScalarAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	vector -= 1.0f;
	EXPECT_EQ(vector.x, 0.0f);
	EXPECT_EQ(vector.y, 0.0f);
}

TEST(Vector2Test, MultScalarAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	vector *= 2.0f;
	EXPECT_EQ(vector.x, 2.0f);
	EXPECT_EQ(vector.y, 2.0f);
}

TEST(Vector2Test, DivScalarAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	vector /= 2.0f;
	EXPECT_EQ(vector.x, 0.5f);
	EXPECT_EQ(vector.y, 0.5f);
}

// Other Tests