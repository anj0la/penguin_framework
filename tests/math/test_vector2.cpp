#include "core/math/vector2.hpp"
#include <gtest/gtest.h>

// Setting Up the Test Suite

class Vector2TestFixture : public ::testing::Test {
protected:
	Vector2 vector1, vector2;

	void SetUp() override {
		vector1 = Vector2(1.0f, 1.0f);
		vector2 = Vector2(2.0f, 2.0f);
	};

};

// Constructor Tests (No Fixture)

TEST(Vector2ConstructorTest, DefaultConstructor) {
	Vector2 vector;
	EXPECT_FLOAT_EQ(vector.x, 0.0f);
	EXPECT_FLOAT_EQ(vector.y, 0.0f);
}

TEST(Vector2ConstructorTest, RegularConstructor) {
	Vector2 vector(1.0f, 1.0f);
	EXPECT_FLOAT_EQ(vector.x, 1.0f);
	EXPECT_FLOAT_EQ(vector.y, 1.0f);
}

TEST(Vector2ConstructorTest, RegularConstructorScalar) {
	Vector2 vector(1.0f);
	EXPECT_FLOAT_EQ(vector.x, 1.0f);
	EXPECT_FLOAT_EQ(vector.y, 1.0f);
}

// Binary Operator Tests

TEST_F(Vector2TestFixture, AddVectors) {
	Vector2 result = vector1 + vector2;
	EXPECT_FLOAT_EQ(result.x, 3.0f);
	EXPECT_FLOAT_EQ(result.y, 3.0f);
}

TEST_F(Vector2TestFixture, SubVectors) {
	Vector2 result = vector2 - vector1;
	EXPECT_FLOAT_EQ(result.x, 1.0f);
	EXPECT_FLOAT_EQ(result.y, 1.0f);
}

TEST_F(Vector2TestFixture, MultVectors) {
	Vector2 result = vector1 * vector2;
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST_F(Vector2TestFixture, DivVectors) {
	Vector2 result = vector2 / vector1;
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

// Assignment Operator Tests

TEST_F(Vector2TestFixture, AddVectorsAssignment) {
	vector1 += vector2;
	EXPECT_FLOAT_EQ(vector1.x, 3.0f);
	EXPECT_FLOAT_EQ(vector1.y, 3.0f);
}

TEST_F(Vector2TestFixture, SubVectorsAssignment) {
	vector1 -= vector2;
	EXPECT_FLOAT_EQ(vector1.x, -1.0f);
	EXPECT_FLOAT_EQ(vector1.y, -1.0f);
}

TEST_F(Vector2TestFixture, MultVectorsAssignment) {
	vector1 *= vector2;
	EXPECT_FLOAT_EQ(vector1.x, 2.0f);
	EXPECT_FLOAT_EQ(vector1.y, 2.0f);
}

TEST_F(Vector2TestFixture, DivVectorsAssignment) {
	vector1 /= vector2;
	EXPECT_FLOAT_EQ(vector1.x, 0.5f);
	EXPECT_FLOAT_EQ(vector1.y, 0.5f);
}

// Comparison Operator Tests

TEST_F(Vector2TestFixture, EqualVectors) {
	vector1 += 1.0f; // vector2 == (2.0f, 2.0f), so this should be true
	EXPECT_TRUE(vector1 == vector1);
}

TEST_F(Vector2TestFixture, EqualsVectorsNot) {
	EXPECT_FALSE(vector1 == vector2);
}

TEST_F(Vector2TestFixture, NotEqualOperator) {
	EXPECT_TRUE(vector1 != vector2);
}

TEST_F(Vector2TestFixture, NotEqualOperatorFalse) {
	vector1 += 1.0f; // vector2 == (2.0f, 2.0f)
	EXPECT_FALSE(vector1 != vector2);
}

TEST_F(Vector2TestFixture, LessThanVectors) {
	EXPECT_TRUE(vector1 < vector2);
}

TEST_F(Vector2TestFixture, LessThanVectorsFalse) {
	EXPECT_FALSE(vector2 < vector1);
}

TEST_F(Vector2TestFixture, GreaterThanVectors) {
	EXPECT_TRUE(vector2 > vector1);
}

TEST_F(Vector2TestFixture, GreaterThanVectorsFalse) {
	EXPECT_FALSE(vector1 > vector2);
}

TEST_F(Vector2TestFixture, LessThanEqualVectors) {
	EXPECT_TRUE(vector1 <= vector2);
}

TEST_F(Vector2TestFixture, LessThanEqualVectorsFalse) {
	EXPECT_FALSE(vector2 <= vector1);
}

TEST_F(Vector2TestFixture, GreaterThanEqualVectors) {
	EXPECT_TRUE(vector2 >= vector1);
}

TEST_F(Vector2TestFixture, GreaterThanEqualVectorsFalse) {
	EXPECT_FALSE(vector1 >= vector2);
}

// Unary Operator Tests

TEST_F(Vector2TestFixture, NegVectors) {
	Vector2 result = -vector1;
	EXPECT_FLOAT_EQ(result.x, -1.0f);
	EXPECT_FLOAT_EQ(result.y, -1.0f);
}

TEST_F(Vector2TestFixture, NotVectors) {
	EXPECT_TRUE(!vector1);
}

// Scalar Operator Tests

TEST_F(Vector2TestFixture, AddVectorsScalar) {
	Vector2 result = vector1 + 1.0f;
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST_F(Vector2TestFixture, SubVectorsScalar) {
	Vector2 result = vector1 - 1.0f;
	EXPECT_FLOAT_EQ(result.x, 0.0f);
	EXPECT_FLOAT_EQ(result.y, 0.0f);
}

TEST_F(Vector2TestFixture, MultVectorsScalar) {
	Vector2 result = vector1 * 2.0f;
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST_F(Vector2TestFixture, DivVectorsScalar) {
	Vector2 result = vector1 / 2.0f;
	EXPECT_FLOAT_EQ(result.x, 0.5f);
	EXPECT_FLOAT_EQ(result.y, 0.5f);
}

// Scalar Assignment Operator Tests

TEST_F(Vector2TestFixture, AddVectorsScalarAssignment) {
	vector2 += 1.0f;
	EXPECT_FLOAT_EQ(vector2.x, 3.0f);
	EXPECT_FLOAT_EQ(vector2.y, 3.0f);
}

TEST_F(Vector2TestFixture, SubVectorsScalarAssignment) {
	vector2 -= 1.0f;
	EXPECT_FLOAT_EQ(vector2.x, 1.0f);
	EXPECT_FLOAT_EQ(vector2.y, 1.0f);
}

TEST_F(Vector2TestFixture, MultVectorsScalarAssignment) {
	vector2 *= 2.0f;
	EXPECT_FLOAT_EQ(vector2.x, 4.0f);
	EXPECT_FLOAT_EQ(vector2.y, 4.0f);
}

TEST_F(Vector2TestFixture, DivVectorsScalarAssignment) {
	vector2 /= 2.0f;
	EXPECT_FLOAT_EQ(vector2.x, 1.0f);
	EXPECT_FLOAT_EQ(vector2.y, 1.0f);
}

// Other Tests

TEST_F(Vector2TestFixture, AbsFunction) {
	Vector2 result = (-vector1).abs();
	EXPECT_FLOAT_EQ(result.x, 1.0f);
	EXPECT_FLOAT_EQ(result.y, 1.0f);
}

TEST_F(Vector2TestFixture, FloorFunction) {
	vector2 += 0.5; // (2.5f, 2.5f)
	Vector2 result = vector2.floor();
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST_F(Vector2TestFixture, CeilFunction) {
	vector2 += 0.5; // (2.5f, 2.5f)
	Vector2 result = vector2.ceil();
	EXPECT_FLOAT_EQ(result.x, 3.0f);
	EXPECT_FLOAT_EQ(result.y, 3.0f);
}

TEST_F(Vector2TestFixture, RoundFunction) {
	vector2 += 0.25; // (2.25f, 2.25f)
	Vector2 result = vector2.round();
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST_F(Vector2TestFixture, MinFunction) {
	Vector2 result = vector1.min(vector2);
	EXPECT_FLOAT_EQ(result.x, 1.0f);
	EXPECT_FLOAT_EQ(result.y, 1.0f);
}

TEST_F(Vector2TestFixture, MaxFunction) {
	Vector2 result = vector1.max(vector2);
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST_F(Vector2TestFixture, LerpFunction) {
	Vector2 result = vector1.lerp(vector2, 0.5f);
	EXPECT_FLOAT_EQ(result.x, 1.5f);
	EXPECT_FLOAT_EQ(result.y, 1.5f);
}

TEST_F(Vector2TestFixture, DotFunction) {
	float result = vector1.dot(vector2);
	EXPECT_FLOAT_EQ(result, 4.0f);
}

TEST_F(Vector2TestFixture, CrossFunction) {
	float result = vector1.cross(vector2);
	EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(Vector2TestFixture, LengthFunction) {
	float result = vector1.length();
	EXPECT_FLOAT_EQ(result, 1.41421354f);
}

TEST_F(Vector2TestFixture, LengthSquaredFunction) {
	float result = vector1.length_squared();
	EXPECT_FLOAT_EQ(result, 2.0f);
}

TEST_F(Vector2TestFixture, NormalizeFunction) {
	vector1.normalize();
	EXPECT_FLOAT_EQ(vector1.x, 0.707106769f);
	EXPECT_FLOAT_EQ(vector1.y, 0.707106769f);
}

TEST_F(Vector2TestFixture, NormalizedFunction) {
	Vector2 result = vector1.normalized();
	EXPECT_FLOAT_EQ(result.x, 0.707106769f);
	EXPECT_FLOAT_EQ(result.y, 0.707106769f);
}

TEST_F(Vector2TestFixture, DistanceToFunction) {
	float result = vector1.distance_to(vector2);
	EXPECT_FLOAT_EQ(result, 1.41421354f);
}

TEST_F(Vector2TestFixture, DistanceSquaredToFunction) {
	float result = vector1.distance_squared_to(vector2);
	EXPECT_FLOAT_EQ(result, 2.0f);
}

// Regular Tests (No Fixture) - Edge Cases

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

TEST(Vector2Test, NormalizedFunctionUnitVector) {
	Vector2 vector(0.0f, 1.0f);
	Vector2 result = vector.normalized();
	EXPECT_FLOAT_EQ(result.x, 0.0f);
	EXPECT_FLOAT_EQ(result.y, 1.0f);
}