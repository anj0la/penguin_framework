#include "math/vector2i.hpp"
#include <gtest/gtest.h>

// Constructor Tests

TEST(Vector2iTest, DefaultConstructor) {
	Vector2i vector;
	EXPECT_EQ(vector.x, 0);
	EXPECT_EQ(vector.y, 0);
}

TEST(Vector2iTest, RegularConstructor) {
	Vector2i vector(1, 1);
	EXPECT_EQ(vector.x, 1);
	EXPECT_EQ(vector.y, 1);
}

TEST(Vector2iTest, RegularConstructorScalar) {
	Vector2i vector(1);
	EXPECT_EQ(vector.x, 1);
	EXPECT_EQ(vector.y, 1);
}

TEST(Vector2iTest, CopyConstructor) {
	Vector2i vector(1, 1);
	Vector2i copy(vector);
	EXPECT_EQ(copy.x, 1);
	EXPECT_EQ(copy.y, 1);
}

TEST(Vector2iTest, MoveConstructor) {
	Vector2i vector(1, 1);
	Vector2i move(std::move(vector));
	EXPECT_EQ(move.x, 1);
	EXPECT_EQ(move.y, 1);
}

TEST(Vector2iTest, CopyAssignmentOperator) {
	Vector2i vector(1, 1);
	Vector2i copy;
	copy = vector;
	EXPECT_EQ(copy.x, 1);
	EXPECT_EQ(copy.y, 1);
}

TEST(Vector2iTest, MoveAssignmentOperator) {
	Vector2i vector(1, 1);
	Vector2i move;
	move = std::move(vector);
	EXPECT_EQ(move.x, 1);
	EXPECT_EQ(move.y, 1);
}

// Binary Operator Tests

TEST(Vector2iTest, AddOperator) {
	Vector2i vector1(1, 1);
	Vector2i vector2(1, 1);
	Vector2i result = vector1 + vector2;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 2);
}

TEST(Vector2iTest, SubOperator) {
	Vector2i vector1(1, 1);
	Vector2i vector2(1, 1);
	Vector2i result = vector1 - vector2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 0);
}

TEST(Vector2iTest, MultOperator) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	Vector2i result = vector1 * vector2;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 2);
}

TEST(Vector2iTest, DivOperator) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	Vector2i result = vector1 / vector2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 0);
}

// Assignment Operator Tests

TEST(Vector2iTest, AddAssignmentOperator) {
	Vector2i vector(1, 1);
	vector += Vector2i(1, 1);
	EXPECT_EQ(vector.x, 2);
	EXPECT_EQ(vector.y, 2);
}

TEST(Vector2iTest, SubAssignmentOperator) {
	Vector2i vector(1, 1);
	vector -= Vector2i(1, 1);
	EXPECT_EQ(vector.x, 0);
	EXPECT_EQ(vector.y, 0);
}

TEST(Vector2iTest, MultAssignmentOperator) {
	Vector2i vector(1, 1);
	vector *= Vector2i(2, 2);
	EXPECT_EQ(vector.x, 2);
	EXPECT_EQ(vector.y, 2);
}

TEST(Vector2iTest, DivAssignmentOperator) {
	Vector2i vector(1, 1);
	vector /= Vector2i(2, 2);
	EXPECT_EQ(vector.x, 0);
	EXPECT_EQ(vector.y, 0);
}

// Comparison Operator Tests

TEST(Vector2iTest, EqualOperator) {
	Vector2i vector1(1, 1);
	Vector2i vector2(1, 1);
	EXPECT_TRUE(vector1 == vector2);
}

TEST(Vector2iTest, EqualOperatorFalse) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	EXPECT_FALSE(vector1 == vector2);
}

TEST(Vector2iTest, NotEqualOperator) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	EXPECT_TRUE(vector1 != vector2);
}

TEST(Vector2iTest, NotEqualOperatorFalse) {
	Vector2i vector1(1, 1);
	Vector2i vector2(1, 1);
	EXPECT_FALSE(vector1 != vector2);
}

TEST(Vector2iTest, LessThanOperator) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	EXPECT_TRUE(vector1 < vector2);
}

TEST(Vector2iTest, LessThanOperatorFalse) {
	Vector2i vector1(2, 2);
	Vector2i vector2(1, 1);
	EXPECT_FALSE(vector1 < vector2);
}

TEST(Vector2iTest, GreaterThanOperator) {
	Vector2i vector1(2, 2);
	Vector2i vector2(1, 1);
	EXPECT_TRUE(vector1 > vector2);
}

TEST(Vector2iTest, GreaterThanOperatorFalse) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	EXPECT_FALSE(vector1 > vector2);
}

TEST(Vector2iTest, LessThanEqualOperator) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	EXPECT_TRUE(vector1 <= vector2);
}

TEST(Vector2iTest, LessThanEqualOperatorFalse) {
	Vector2i vector1(2, 2);
	Vector2i vector2(1, 1);
	EXPECT_FALSE(vector1 <= vector2);
}

TEST(Vector2iTest, GreaterThanEqualOperator) {
	Vector2i vector1(2, 2);
	Vector2i vector2(1, 1);
	EXPECT_TRUE(vector1 >= vector2);
}

TEST(Vector2iTest, GreaterThanEqualOperatorFalse) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	EXPECT_FALSE(vector1 >= vector2);
}

// Unary Operator Tests

TEST(Vector2iTest, NegationOperator) {
	Vector2i vector(1, 1);
	Vector2i result = -vector;
	EXPECT_EQ(result.x, -1);
	EXPECT_EQ(result.y, -1);
}

TEST(Vector2iTest, NotOperator) {
	Vector2i vector(1, 1);
	EXPECT_TRUE(!vector);
}

// Scalar Operator Tests

TEST(Vector2iTest, AddScalarOperator) {
	Vector2i vector(1, 1);
	Vector2i result = vector + 1;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 2);
}

TEST(Vector2iTest, SubScalarOperator) {
	Vector2i vector(1, 1);
	Vector2i result = vector - 1;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 0);
}

TEST(Vector2iTest, MultScalarOperator) {
	Vector2i vector(1, 1);
	Vector2i result = vector * 2;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 2);
}

TEST(Vector2iTest, DivScalarOperator) {
	Vector2i vector(1, 1);
	Vector2i result = vector / 2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 0);
}

// Scalar Assignment Operator Tests

TEST(Vector2iTest, AddScalarAssignmentOperator) {
	Vector2i vector(1, 1);
	vector += 1;
	EXPECT_EQ(vector.x, 2);
	EXPECT_EQ(vector.y, 2);
}

TEST(Vector2iTest, SubScalarAssignmentOperator) {
	Vector2i vector(1, 1);
	vector -= 1;
	EXPECT_EQ(vector.x, 0);
	EXPECT_EQ(vector.y, 0);
}

TEST(Vector2iTest, MultScalarAssignmentOperator) {
	Vector2i vector(1, 1);
	vector *= 2;
	EXPECT_EQ(vector.x, 2);
	EXPECT_EQ(vector.y, 2);
}

TEST(Vector2iTest, DivScalarAssignmentOperator) {
	Vector2i vector(1, 1);
	vector /= 2;
	EXPECT_EQ(vector.x, 0);
	EXPECT_EQ(vector.y, 0);
}

// Other Tests

TEST(Vector2iTest, AbsFunction) {
	Vector2i vector(-1, -1);
	Vector2i result = vector.abs();
	EXPECT_EQ(result.x, 1);
	EXPECT_EQ(result.y, 1);
}

TEST(Vector2iTest, MinFunction) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	Vector2i result = vector1.min(vector2);
	EXPECT_EQ(result.x, 1);
	EXPECT_EQ(result.y, 1);
}

TEST(Vector2iTest, MaxFunction) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	Vector2i result = vector1.max(vector2);
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 2);
}

TEST(Vector2iTest, DotFunction) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	int result = vector1.dot(vector2);
	EXPECT_EQ(result, 4);
}

TEST(Vector2iTest, CrossFunction) {
	Vector2i vector1(1, 1);
	Vector2i vector2(2, 2);
	int result = vector1.cross(vector2);
	EXPECT_EQ(result, 0);
}

TEST(Vector2iTest, LengthFunction) {
	Vector2i vector(0, 1);
	float result = vector.length();
	EXPECT_FLOAT_EQ(result, 1.0f);
}

TEST(Vector2iTest, LengthSquaredFunction) {
	Vector2i vector(0, 1);
	int result = vector.length_squared();
	EXPECT_EQ(result, 1);
}

TEST(Vector2iTest, DistanceToFunction) {
	Vector2i vector1(0, 0);
	Vector2i vector2(0, 1);
	float result = vector1.distance_to(vector2);
	EXPECT_FLOAT_EQ(result, 1.0f);
}

TEST(Vector2iTest, DistanceSquaredToFunction) {
	Vector2i vector1(0, 0);
	Vector2i vector2(0, 1);
	int result = vector1.distance_squared_to(vector2);
	EXPECT_EQ(result, 1);
}