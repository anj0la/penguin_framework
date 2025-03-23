#include "math/vector2.hpp"
#include <gtest/gtest.h>

// Constructor Tests

TEST(Vector2Test, DefaultConstructor) {
	Vector2 vector;
	EXPECT_FLOAT_EQ(vector.x, 0.0f);
	EXPECT_FLOAT_EQ(vector.y, 0.0f);
}

TEST(Vector2Test, RegularConstructor) {
	Vector2 vector(1.0f, 1.0f);
	EXPECT_FLOAT_EQ(vector.x, 1.0f);
	EXPECT_FLOAT_EQ(vector.y, 1.0f);
}

TEST(Vector2Test, RegularConstructorScalar) {
	Vector2 vector(1.0f);
	EXPECT_FLOAT_EQ(vector.x, 1.0f);
	EXPECT_FLOAT_EQ(vector.y, 1.0f);
}

TEST(Vector2Test, CopyConstructor) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 copy(vector);
	EXPECT_FLOAT_EQ(copy.x, 1.0f);
	EXPECT_FLOAT_EQ(copy.y, 1.0f);
}

TEST(Vector2Test, MoveConstructor) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 move(std::move(vector));
	EXPECT_FLOAT_EQ(move.x, 1.0f);
	EXPECT_FLOAT_EQ(move.y, 1.0f);
}

TEST(Vector2Test, CopyAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 copy;
	copy = vector;
	EXPECT_FLOAT_EQ(copy.x, 1.0f);
	EXPECT_FLOAT_EQ(copy.y, 1.0f);
}

TEST(Vector2Test, MoveAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 move;
	move = std::move(vector);
	EXPECT_FLOAT_EQ(move.x, 1.0f);
	EXPECT_FLOAT_EQ(move.y, 1.0f);
}

// Binary Operator Tests

TEST(Vector2Test, AddOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(1.0f, 1.0f);
	Vector2 result = vector1 + vector2;
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, SubOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(1.0f, 1.0f);
	Vector2 result = vector1 - vector2;
	EXPECT_FLOAT_EQ(result.x, 0.0f);
	EXPECT_FLOAT_EQ(result.y, 0.0f);
}

TEST(Vector2Test, MultOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	Vector2 result = vector1 * vector2;
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, DivOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	Vector2 result = vector1 / vector2;
	EXPECT_FLOAT_EQ(result.x, 0.5f);
	EXPECT_FLOAT_EQ(result.y, 0.5f);
}

// Assignment Operator Tests

TEST(Vector2Test, AddAssignmentOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(1.0f, 1.0f);
	vector1 += vector2;
	EXPECT_FLOAT_EQ(vector1.x, 2.0f);
	EXPECT_FLOAT_EQ(vector1.y, 2.0f);
}

TEST(Vector2Test, SubAssignmentOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(1.0f, 1.0f);
	vector1 -= vector2;
	EXPECT_FLOAT_EQ(vector1.x, 0.0f);
	EXPECT_FLOAT_EQ(vector1.y, 0.0f);
}

TEST(Vector2Test, MultAssignmentOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	vector1 *= vector2;
	EXPECT_FLOAT_EQ(vector1.x, 2.0f);
	EXPECT_FLOAT_EQ(vector1.y, 2.0f);
}

TEST(Vector2Test, DivAssignmentOperator) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	vector1 /= vector2;
	EXPECT_FLOAT_EQ(vector1.x, 0.5f);
	EXPECT_FLOAT_EQ(vector1.y, 0.5f);
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
	EXPECT_FLOAT_EQ(result.x, -1.0f);
	EXPECT_FLOAT_EQ(result.y, -1.0f);
}

TEST(Vector2Test, NotOperator) {
	Vector2 vector(1.0f, 1.0f);
	EXPECT_TRUE(!vector);
}

// Scalar Operator Tests

TEST(Vector2Test, AddScalarOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = vector + 1.0f;
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, SubScalarOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = vector - 1.0f;
	EXPECT_FLOAT_EQ(result.x, 0.0f);
	EXPECT_FLOAT_EQ(result.y, 0.0f);
}

TEST(Vector2Test, MultScalarOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = vector * 2.0f;
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, DivScalarOperator) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = vector / 2.0f;
	EXPECT_FLOAT_EQ(result.x, 0.5f);
	EXPECT_FLOAT_EQ(result.y, 0.5f);
}

// Scalar Assignment Operator Tests

TEST(Vector2Test, AddScalarAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	vector += 1.0f;
	EXPECT_FLOAT_EQ(vector.x, 2.0f);
	EXPECT_FLOAT_EQ(vector.y, 2.0f);
}

TEST(Vector2Test, SubScalarAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	vector -= 1.0f;
	EXPECT_FLOAT_EQ(vector.x, 0.0f);
	EXPECT_FLOAT_EQ(vector.y, 0.0f);
}

TEST(Vector2Test, MultScalarAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	vector *= 2.0f;
	EXPECT_FLOAT_EQ(vector.x, 2.0f);
	EXPECT_FLOAT_EQ(vector.y, 2.0f);
}

TEST(Vector2Test, DivScalarAssignmentOperator) {
	Vector2 vector(1.0f, 1.0f);
	vector /= 2.0f;
	EXPECT_FLOAT_EQ(vector.x, 0.5f);
	EXPECT_FLOAT_EQ(vector.y, 0.5f);
}

// Other Tests

TEST(Vector2Test, AbsFunction) {
	Vector2 vector(-1.0f, -1.0f);
	Vector2 result = vector.abs();
	EXPECT_FLOAT_EQ(result.x, 1.0f);
	EXPECT_FLOAT_EQ(result.y, 1.0f);
}

TEST(Vector2Test, FloorFunction) {
	Vector2 vector(1.5f, 1.5f);
	Vector2 result = vector.floor();
	EXPECT_FLOAT_EQ(result.x, 1.0f);
	EXPECT_FLOAT_EQ(result.y, 1.0f);
}

TEST(Vector2Test, CeilFunction) {
	Vector2 vector(1.5f, 1.5f);
	Vector2 result = vector.ceil();
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, RoundFunction) {
	Vector2 vector(1.5f, 1.5f);
	Vector2 result = vector.round();
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, MinFunction) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	Vector2 result = vector1.min(vector2);
	EXPECT_FLOAT_EQ(result.x, 1.0f);
	EXPECT_FLOAT_EQ(result.y, 1.0f);
}

TEST(Vector2Test, MaxFunction) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	Vector2 result = vector1.max(vector2);
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST(Vector2Test, LerpFunction) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	Vector2 result = vector1.lerp(vector2, 0.5f);
	EXPECT_FLOAT_EQ(result.x, 1.5f);
	EXPECT_FLOAT_EQ(result.y, 1.5f);
}

TEST(Vector2Test, DotFunction) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	float result = vector1.dot(vector2);
	EXPECT_FLOAT_EQ(result, 4.0f);
}

TEST(Vector2Test, CrossFunction) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	float result = vector1.cross(vector2);
	EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST(Vector2Test, LengthFunction) {
	Vector2 vector(0.0f, 1.0f);
	float result = vector.length();
	EXPECT_FLOAT_EQ(result, 1.0f);
}

TEST(Vector2Test, LengthSquaredFunction) {
	Vector2 vector(1.0f, 1.0f);
	float result = vector.length_squared();
	EXPECT_FLOAT_EQ(result, 2.0f);
}

TEST(Vector2Test, NormalizeFunction) {
	Vector2 vector(1.0f, 1.0f);
	vector.normalize();
	EXPECT_FLOAT_EQ(vector.x, 0.707106769f);
	EXPECT_FLOAT_EQ(vector.y, 0.707106769f);
}

TEST(Vector2Test, NormalizeFunctionUnitVector) {
	Vector2 vector(0.0f, 1.0f);
	vector.normalize();
	EXPECT_FLOAT_EQ(vector.x, 0.0f);
	EXPECT_FLOAT_EQ(vector.y, 1.0f);
}

TEST(Vector2Test, NormalizeFunctionZeroVector) {
	Vector2 vector(0.0f, 0.0f);
	vector.normalize();
	EXPECT_FLOAT_EQ(vector.x, 0.0f);
	EXPECT_FLOAT_EQ(vector.y, 0.0f);
}

TEST(Vector2Test, NormalizedFunction) {
	Vector2 vector(1.0f, 1.0f);
	Vector2 result = vector.normalized();
	EXPECT_FLOAT_EQ(result.x, 0.707106769f);
	EXPECT_FLOAT_EQ(result.y, 0.707106769f);
}

TEST(Vector2Test, NormalizedFunctionUnitVector) {
	Vector2 vector(0.0f, 1.0f);
	Vector2 result = vector.normalized();
	EXPECT_FLOAT_EQ(result.x, 0.0f);
	EXPECT_FLOAT_EQ(result.y, 1.0f);
}

TEST(Vector2Test, DistanceToFunction) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	float result = vector1.distance_to(vector2);
	EXPECT_FLOAT_EQ(result, 1.41421354f);
}

TEST(Vector2Test, DistanceSquaredToFunction) {
	Vector2 vector1(1.0f, 1.0f);
	Vector2 vector2(2.0f, 2.0f);
	float result = vector1.distance_squared_to(vector2);
	EXPECT_FLOAT_EQ(result, 2.0f);
}