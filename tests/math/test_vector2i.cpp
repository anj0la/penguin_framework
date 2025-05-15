#include <penguin_framework/core/math/vector2i.hpp>
#include <gtest/gtest.h>

// Setting Up the Test Suite

class Vector2iTestFixutre : public ::testing::Test {
protected:
	Vector2i vector1, vector2, vector3;

	void SetUp() override {
		vector1 = Vector2i(2, 3);
		vector2 = Vector2i(1, 2);
	};

};

// Constructor Tests

TEST(Vector2iConstructorTest, DefaultConstructor) {
	Vector2i vector;
	EXPECT_EQ(vector.x, 0);
	EXPECT_EQ(vector.y, 0);
}

TEST(Vector2iConstructorTest, RegularConstructor) {
	Vector2i vector(1, 1);
	EXPECT_EQ(vector.x, 1);
	EXPECT_EQ(vector.y, 1);
}

TEST(Vector2iConstructorTest, RegularConstructorScalar) {
	Vector2i vector(1);
	EXPECT_EQ(vector.x, 1);
	EXPECT_EQ(vector.y, 1);
}

// Binary Operator Tests

TEST_F(Vector2iTestFixutre, AddVectors) {
	Vector2i result = vector1 + vector2;
	EXPECT_EQ(result.x, 3);
	EXPECT_EQ(result.y, 5);
}

TEST_F(Vector2iTestFixutre, SubVectors) {
	Vector2i result = vector1 - vector2;
	EXPECT_EQ(result.x, 1);
	EXPECT_EQ(result.y, 1);
}

TEST_F(Vector2iTestFixutre, MultVectors) {
	Vector2i result = vector1 * vector2;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 6);
}

TEST_F(Vector2iTestFixutre, DivVectors) {
	Vector2i result = vector1 / vector2;
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 1);
}

// Assignment Operator Tests

TEST_F(Vector2iTestFixutre, AddVectorsAssignment) {
	vector1 += vector2;
	EXPECT_EQ(vector1.x, 3);
	EXPECT_EQ(vector1.y, 5);
}

TEST_F(Vector2iTestFixutre, SubVectorsAssignment) {
	vector1 -= vector2;
	EXPECT_EQ(vector1.x, 1);
	EXPECT_EQ(vector1.y, 1);
}

TEST_F(Vector2iTestFixutre, MultVectorsAssignment) {
	vector1 *= vector2;
	EXPECT_EQ(vector1.x, 2);
	EXPECT_EQ(vector1.y, 6);
}

TEST_F(Vector2iTestFixutre, DivVectorsAssignment) {
	vector1 /= vector2;
	EXPECT_EQ(vector1.x, 2);
	EXPECT_EQ(vector1.y, 1);
}

// Scalar Operator Tests

TEST_F(Vector2iTestFixutre, AddVectorsScalar) {
	Vector2i result = vector1 + 1;
	EXPECT_EQ(result.x, 3);
	EXPECT_EQ(result.y, 4);
}

TEST_F(Vector2iTestFixutre, SubVectorsScalar) {
	Vector2i result = vector1 - 1;
	EXPECT_EQ(result.x, 1);
	EXPECT_EQ(result.y, 2);
}

TEST_F(Vector2iTestFixutre, MultVectorsScalar) {
	Vector2i result = vector1 * 2;
	EXPECT_EQ(result.x, 4);
	EXPECT_EQ(result.y, 6);
}

TEST_F(Vector2iTestFixutre, DivVectorsScalar) {
	Vector2i result = vector1 / 2;
	EXPECT_EQ(result.x, 1);
	EXPECT_EQ(result.y, 1);
}

// Assignment Operator Tests

TEST_F(Vector2iTestFixutre, AddVectorsScalarAssignment) {
	vector1 += 1;
	EXPECT_EQ(vector1.x, 3);
	EXPECT_EQ(vector1.y, 4);
}

TEST_F(Vector2iTestFixutre, SubVectorsScalarAssignment) {
	vector1 -= 1;
	EXPECT_EQ(vector1.x, 1);
	EXPECT_EQ(vector1.y, 2);
}

TEST_F(Vector2iTestFixutre, MultVectorsScalarAssignment) {
	vector1 *= 2;
	EXPECT_EQ(vector1.x, 4);
	EXPECT_EQ(vector1.y, 6);
}

TEST_F(Vector2iTestFixutre, DivVectorsScalarAssignment) {
	vector1 /= 2;
	EXPECT_EQ(vector1.x, 1);
	EXPECT_EQ(vector1.y, 1);
}

// Comparison Operator Tests

TEST_F(Vector2iTestFixutre, EqualOperator) {
	vector1 -= 1; // (1, 2), vector2 = (1, 2)
	EXPECT_TRUE(vector1 == vector2);
}

TEST_F(Vector2iTestFixutre, EqualOperatorFalse) {
	EXPECT_FALSE(vector1 == vector2);
}

TEST_F(Vector2iTestFixutre, NotEqualOperator) {
	EXPECT_TRUE(vector1 != vector2);
}

TEST_F(Vector2iTestFixutre, NotEqualOperatorFalse) {
	vector1 -= 1; // (1, 2), vector2 = (1, 2)
	EXPECT_FALSE(vector1 != vector2);
}


TEST_F(Vector2iTestFixutre, LessThanOperator) {
	EXPECT_TRUE(vector2 < vector1);
}

TEST_F(Vector2iTestFixutre, LessThanOperatorFalse) {
	EXPECT_FALSE(vector1 < vector2);
}

TEST_F(Vector2iTestFixutre, GreaterThanOperator) {
	EXPECT_TRUE(vector1 > vector2);
}

TEST_F(Vector2iTestFixutre, GreaterThanOperatorFalse) {
	EXPECT_FALSE(vector2 > vector1);
}

TEST_F(Vector2iTestFixutre, LessThanEqualOperator) {
	EXPECT_TRUE(vector2 <= vector1);
}

TEST_F(Vector2iTestFixutre, LessThanEqualOperatorFalse) {
	EXPECT_FALSE(vector1 <= vector2);
}

TEST_F(Vector2iTestFixutre, GreaterThanEqualOperator) {
	EXPECT_TRUE(vector1 >= vector2);
}

TEST_F(Vector2iTestFixutre, GreaterThanEqualOperatorFalse) {
	EXPECT_FALSE(vector2 >= vector1);
}

// Unary Operator Tests

TEST_F(Vector2iTestFixutre, ModuloOperator) {
	Vector2i result = vector1 % vector2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 1);
}

TEST_F(Vector2iTestFixutre, ModuloScalarOperator) {
	Vector2i result = vector1 % 2;
	EXPECT_EQ(result.x, 0);
	EXPECT_EQ(result.y, 1);
}

TEST_F(Vector2iTestFixutre, NegationOperator) {
	Vector2i result = -vector1;
	EXPECT_EQ(result.x, -2);
	EXPECT_EQ(result.y, -3);
}

TEST_F(Vector2iTestFixutre, NotOperator) {
	EXPECT_TRUE(!vector1);
}

// Scalar Operator Tests

TEST_F(Vector2iTestFixutre, AddScalarOperator) {
	Vector2i result = vector1 + 1;
	EXPECT_EQ(result.x, 3);
	EXPECT_EQ(result.y, 4);
}

TEST_F(Vector2iTestFixutre, SubScalarOperator) {
	Vector2i result = vector1 - 1;
	EXPECT_EQ(result.x, 1);
	EXPECT_EQ(result.y, 2);
}

TEST_F(Vector2iTestFixutre, MultScalarOperator) {
	Vector2i result = vector1 * 2;
	EXPECT_EQ(result.x, 4);
	EXPECT_EQ(result.y, 6);
}

TEST_F(Vector2iTestFixutre, DivScalarOperator) {
	Vector2i result = vector1 / 2;
	EXPECT_EQ(result.x, 1);
	EXPECT_EQ(result.y, 1);
}

// Scalar Assignment Operator Tests

TEST_F(Vector2iTestFixutre, AddScalarAssignmentOperator) {
	vector1 += 1;
	EXPECT_EQ(vector1.x, 3);
	EXPECT_EQ(vector1.y, 4);
}

TEST_F(Vector2iTestFixutre, SubScalarAssignmentOperator) {
	vector1 -= 1;
	EXPECT_EQ(vector1.x, 1);
	EXPECT_EQ(vector1.y, 2);
}

TEST_F(Vector2iTestFixutre, MultScalarAssignmentOperator) {
	vector1 *= 2;
	EXPECT_EQ(vector1.x, 4);
	EXPECT_EQ(vector1.y, 6);
}

TEST_F(Vector2iTestFixutre, DivScalarAssignmentOperator) {
	vector1 /= 2;
	EXPECT_EQ(vector1.x, 1);
	EXPECT_EQ(vector1.y, 1);
}

TEST_F(Vector2iTestFixutre, ModuloScalarAssignmentOperator) {
	vector1 %= 2;
	EXPECT_EQ(vector1.x, 0);
	EXPECT_EQ(vector1.y, 1);
}

// Other Tests

TEST_F(Vector2iTestFixutre, AbsFunction) {
	Vector2i result = (-vector1).abs();
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 3);
}

TEST_F(Vector2iTestFixutre, MinFunction) {
	Vector2i result = vector1.min(vector2);
	EXPECT_EQ(result.x, 1);
	EXPECT_EQ(result.y, 2);
}

TEST_F(Vector2iTestFixutre, MaxFunction) {
	Vector2i result = vector1.max(vector2);
	EXPECT_EQ(result.x, 2);
	EXPECT_EQ(result.y, 3);
}

TEST_F(Vector2iTestFixutre, DotFunction) {
	int result = vector1.dot(vector2);
	EXPECT_EQ(result, 8);
}

TEST_F(Vector2iTestFixutre, CrossFunction) {
	int result = vector1.cross(vector2);
	EXPECT_EQ(result, 1);
}

TEST_F(Vector2iTestFixutre, LengthFunction) {
	float result = vector1.length();
	EXPECT_FLOAT_EQ(result, 3.6055512f);
}

TEST_F(Vector2iTestFixutre, LengthSquaredFunction) {
	int result = vector1.length_squared();
	EXPECT_EQ(result, 13);
}

TEST_F(Vector2iTestFixutre, DistanceToFunction) {
	Vector2i vector(0, 0);
	float result = vector1.distance_to(vector);
	EXPECT_FLOAT_EQ(result, 3.6055512f);
}

TEST_F(Vector2iTestFixutre, DistanceSquaredToFunction) {
	Vector2i vector(0, 0);
	int result = vector1.distance_squared_to(vector);
	EXPECT_EQ(result, 13);
}