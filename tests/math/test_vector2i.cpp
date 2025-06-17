#include <penguin_framework/math/vector2i.hpp>
#include <gtest/gtest.h>

using penguin::math::Vector2i;

// Constructors

TEST(Vector2iTest, DefaultConstructor) {
    // Arrange & Act
    Vector2i v;

    // Assert
    EXPECT_EQ(v.x, Vector2i::Origin);
    EXPECT_EQ(v.y, Vector2i::Origin);
}

TEST(Vector2iTest, XYConstructor) {
    // Arrange
    int x_val = 1;
    int y_val = -2;

    // Act
    Vector2i v(x_val, y_val);

    // Assert
    EXPECT_EQ(v.x, x_val);
    EXPECT_EQ(v.y, y_val);
}

TEST(Vector2iTest, ScalarConstructor) {
    // Arrange
    int scalar_val = 5;

    // Act
    Vector2i v(scalar_val);

    // Assert
    EXPECT_EQ(v.x, scalar_val);
    EXPECT_EQ(v.y, scalar_val);
}

TEST(Vector2iTest, CopyConstructor) {
    // Arrange
    Vector2i original(1, 2);

    // Act
    Vector2i copy(original);

    // Assert
    EXPECT_EQ(copy, original);
}

TEST(Vector2iTest, MoveConstructor) {
    // Arrange
    Vector2i original(1, 2);
    Vector2i reference_original = original;

    // Act
    Vector2i moved(std::move(original));

    // Assert
    EXPECT_EQ(moved, reference_original);
}

TEST(Vector2iTest, CopyAssignment) {
    // Arrange
    Vector2i original(3, 4);
    Vector2i copy_assigned;
    ASSERT_NE(copy_assigned, original); // Ensure different before assignment

    // Act
    copy_assigned = original;

    // Assert
    EXPECT_EQ(copy_assigned, original);
}

TEST(Vector2iTest, MoveAssignment) {
    // Arrange
    Vector2i original(5, 6);
    Vector2i reference_original = original; // For comparison
    Vector2i move_assigned;
    ASSERT_NE(move_assigned, original); 

    // Act
    move_assigned = std::move(original);

    // Assert
    EXPECT_EQ(move_assigned, reference_original);
}

// Binary Operators (Vector2i vs Vector2i)

TEST(Vector2iTest, OperatorAddVector) {
    // Arrange
    Vector2i v1(2, 3);
    Vector2i v2(1, 2);
    Vector2i expected(3, 5);

    // Act
    Vector2i result = v1 + v2;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, OperatorSubtractVector) {
    // Arrange
    Vector2i v1(2, 3);
    Vector2i v2(1, 2);
    Vector2i expected(1, 1);

    // Act
    Vector2i result = v1 - v2;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, OperatorMultiplyVector) {
    // Arrange
    Vector2i v1(2, 3);
    Vector2i v2(1, 2);
    Vector2i expected(2, 6);

    // Act
    Vector2i result = v1 * v2;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, OperatorDivideVector) {
    // Arrange
    Vector2i v1(10, 21);
    Vector2i v2(2, 4);
    Vector2i expected(5, 5); // Integer division truncates

    // Act
    Vector2i result = v1 / v2;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, OperatorDivideVectorByZero) {
    // Arrange
    Vector2i v_num(10, 20);
    Vector2i v_den_x_zero(0, 4);
    Vector2i v_den_y_zero(2, 0);
    Vector2i v_den_all_zero(0, 0);
    const char* expected_death_msg = "Vector2i: Division by zero attempted.";

    // Act & Assert
#ifndef NDEBUG
    EXPECT_DEATH((void) (v_num / v_den_x_zero), expected_death_msg);
    EXPECT_DEATH((void) (v_num / v_den_y_zero), expected_death_msg);
    EXPECT_DEATH((void) (v_num / v_den_all_zero), expected_death_msg);
#else
    GTEST_SKIP() << "Skipping death tests for division by zero in release build (NDEBUG defined).";
#endif
}

TEST(Vector2iTest, OperatorModuloVector) {
    // Arrange
    Vector2i v1(7, 10);
    Vector2i v2(3, 4);
    Vector2i expected(1, 2); // 7%3 = 1, 10%4 = 2

    // Act
    Vector2i result = v1 % v2;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, OperatorModuloVectorByZero) {
    // Arrange
    Vector2i v_num(7, 10);
    Vector2i v_den_x_zero(0, 4);
    Vector2i v_den_y_zero(3, 0);
    Vector2i v_den_all_zero(0, 0);
    const char* expected_death_msg = "Vector2i: Modulo by zero attempted in x or y component.";

    // Act & Assert
#ifndef NDEBUG
    EXPECT_DEATH((void) (v_num % v_den_x_zero), expected_death_msg);
    EXPECT_DEATH((void)(v_num % v_den_y_zero), expected_death_msg);
    EXPECT_DEATH((void)(v_num % v_den_all_zero), expected_death_msg);
#else
    GTEST_SKIP() << "Skipping death tests for modulo by zero in release build (NDEBUG defined).";
#endif
}

// Assignment Operators (Vector2i vs Vector2i)

TEST(Vector2iTest, OperatorAddAssignVector) {
    // Arrange
    Vector2i v(2, 3);
    Vector2i v_add(1, 2);
    Vector2i expected(3, 5);

    // Act
    v += v_add;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2iTest, OperatorSubtractAssignVector) {
    // Arrange
    Vector2i v(2, 3);
    Vector2i v_sub(1, 2);
    Vector2i expected(1, 1);

    // Act
    v -= v_sub;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2iTest, OperatorMultiplyAssignVector) {
    // Arrange
    Vector2i v(2, 3);
    Vector2i v_mul(1, 2);
    Vector2i expected(2, 6);

    // Act
    v *= v_mul;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2iTest, OperatorDivideAssignVector) {
    // Arrange
    Vector2i v(10, 21);
    Vector2i v_div(2, 4);
    Vector2i expected(5, 5);

    // Act
    v /= v_div;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2iTest, OperatorDivideAssignVectorByZero) {
    // Arrange
    Vector2i v_orig(10, 20);
    Vector2i v_den_x_zero(0, 4);
    Vector2i v_den_y_zero(2, 0);
    Vector2i v_den_all_zero(0, 0);
    const char* expected_death_msg = "Vector2i: Division by zero attempted in x or y component.";

    // Act & Assert
#ifndef NDEBUG
    Vector2i v_test1 = v_orig;
    EXPECT_DEATH({ v_test1 /= v_den_x_zero; }, expected_death_msg);

    Vector2i v_test2 = v_orig;
    EXPECT_DEATH({ v_test2 /= v_den_y_zero; }, expected_death_msg);

    Vector2i v_test3 = v_orig;
    EXPECT_DEATH({ v_test3 /= v_den_all_zero; }, expected_death_msg);
#else
    GTEST_SKIP() << "Skipping death tests for division by zero in release build (NDEBUG defined).";
#endif
}

TEST(Vector2iTest, OperatorModuloAssignVector) {
    // Arrange
    Vector2i v(7, 10);
    Vector2i v_mod(3, 4);
    Vector2i expected(1, 2);

    // Act
    v %= v_mod;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2iTest, OperatorModuloAssignVectorByZero) {
    // Arrange
    Vector2i v_orig(7, 10);
    Vector2i v_den_x_zero(0, 4);
    Vector2i v_den_y_zero(3, 0);
    Vector2i v_den_all_zero(0, 0);
    const char* expected_death_msg = "Vector2i: Modulo by zero attempted in x or y component.";

    // Act & Assert
#ifndef NDEBUG
    Vector2i v_test1 = v_orig;
    EXPECT_DEATH({ v_test1 %= v_den_x_zero; }, expected_death_msg);

    Vector2i v_test2 = v_orig;
    EXPECT_DEATH({ v_test2 %= v_den_y_zero; }, expected_death_msg);

    Vector2i v_test3 = v_orig;
    EXPECT_DEATH({ v_test3 %= v_den_all_zero; }, expected_death_msg);
#else
    GTEST_SKIP() << "Skipping death tests for modulo by zero in release build (NDEBUG defined).";
#endif
}

// Comparison Operators (Vector2i vs Vector2i)

TEST(Vector2iTest, OperatorEqual) {
    // Arrange
    Vector2i v1(1, 2);
    Vector2i v2(1, 2);
    Vector2i v3(1, 3);
    Vector2i v4(0, 2);

    // Act & Assert
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
    EXPECT_FALSE(v1 == v4);
}

TEST(Vector2iTest, OperatorNotEqual) {
    // Arrange
    Vector2i v1(1, 2);
    Vector2i v2(1, 2);
    Vector2i v3(1, 3);
    Vector2i v4(0, 2);

    // Act & Assert
    EXPECT_FALSE(v1 != v2);
    EXPECT_TRUE(v1 != v3);
    EXPECT_TRUE(v1 != v4);
}

TEST(Vector2iTest, OperatorThreeWayComparison) {
    // Arrange
    Vector2i v1(1, 2);
    Vector2i v2(1, 3);
    Vector2i v3(2, 1);
    Vector2i v_equal(1, 2);

    // Act & Assert
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v1 < v3);
    EXPECT_FALSE(v2 < v1);
    EXPECT_FALSE(v3 < v1);

    EXPECT_TRUE(v2 > v1);
    EXPECT_TRUE(v3 > v1);

    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 <= v_equal);
    EXPECT_FALSE(v2 <= v1);

    EXPECT_TRUE(v1 >= v_equal);
    EXPECT_TRUE(v2 >= v1);
    EXPECT_FALSE(v1 >= v2);
}

// Unary Operators

TEST(Vector2iTest, OperatorUnaryMinus) {
    // Arrange
    Vector2i v(2, -3);
    Vector2i expected(-2, 3);

    // Act
    Vector2i result = -v;

    // Assert
    EXPECT_EQ(result, expected);
}

// Scalar Operators

TEST(Vector2iTest, OperatorAddScalar) {
    // Arrange
    Vector2i v(2, 3);
    int scalar = 1;
    Vector2i expected(3, 4);

    // Act
    Vector2i result = v + scalar;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, OperatorSubtractScalar) {
    // Arrange
    Vector2i v(2, 3);
    int scalar = 1;
    Vector2i expected(1, 2);

    // Act
    Vector2i result = v - scalar;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, OperatorMultiplyScalar) {
    // Arrange
    Vector2i v(2, 3);
    int scalar = 2;
    Vector2i expected(4, 6);

    // Act
    Vector2i result = v * scalar;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, OperatorDivideScalar) {
    // Arrange
    Vector2i v(7, 10);
    int scalar = 2;
    Vector2i expected(3, 5); // 7/2=3, 10/2=5

    // Act
    Vector2i result = v / scalar;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, OperatorDivideScalarByZero) {
    // Arrange
    Vector2i v(7, 10);
    int scalar_zero = 0;
    const char* expected_death_msg = "Vector2i: Division by zero attempted.";

    // Act & Assert
#ifndef NDEBUG
    EXPECT_DEATH((void) (v / scalar_zero), expected_death_msg);
#else
    GTEST_SKIP() << "Skipping death tests for division by zero in release build (NDEBUG defined).";
#endif
}

TEST(Vector2iTest, OperatorModuloScalar) {
    // Arrange
    Vector2i v(7, 10);
    int scalar = 3;
    Vector2i expected(1, 1);

    // Act
    Vector2i result = v % scalar;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, OperatorModuloScalarByZero) {
    // Arrange
    Vector2i v(7, 10);
    int scalar_zero = 0;
    const char* expected_death_msg = "Vector2i: Modulo by zero scalar attempted.";

    // Act & Assert
#ifndef NDEBUG
    EXPECT_DEATH((void) (v % scalar_zero), expected_death_msg);
#else
    GTEST_SKIP() << "Skipping death tests for modulo by zero in release build (NDEBUG defined).";
#endif
}

// Scalar Assignment Operators

TEST(Vector2iTest, OperatorAddAssignScalar) {
    // Arrange
    Vector2i v(2, 3);
    int scalar = 1;
    Vector2i expected(3, 4);

    // Act
    v += scalar;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2iTest, OperatorSubtractAssignScalar) {
    // Arrange
    Vector2i v(2, 3);
    int scalar = 1;
    Vector2i expected(1, 2);

    // Act
    v -= scalar;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2iTest, OperatorMultiplyAssignScalar) {
    // Arrange
    Vector2i v(2, 3);
    int scalar = 2;
    Vector2i expected(4, 6);

    // Act
    v *= scalar;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2iTest, OperatorDivideAssignScalar) {
    // Arrange
    Vector2i v(7, 10);
    int scalar = 2;
    Vector2i expected(3, 5);

    // Act
    v /= scalar;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2iTest, OperatorDivideAssignScalarByZero) {
    // Arrange
    Vector2i v(7, 10); // Original value
    int scalar_zero = 0;
    const char* expected_death_msg = "Vector2i: Division by zero attempted.";

    // Act & Assert
#ifndef NDEBUG
    EXPECT_DEATH({ v /= scalar_zero; }, expected_death_msg);
#else
    GTEST_SKIP() << "Skipping death tests for division by zero in release build (NDEBUG defined).";
#endif
}

TEST(Vector2iTest, OperatorModuloAssignScalar) {
    // Arrange
    Vector2i v(7, 10);
    int scalar = 3;
    Vector2i expected(1, 1);

    // Act
    v %= scalar;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2iTest, OperatorModuloAssignScalarByZero) {
    // Arrange
    Vector2i v(7, 10); // Original value
    int scalar_zero = 0;
    const char* expected_death_msg = "Vector2i: Modulo by zero scalar attempted.";

    // Act & Assert
#ifndef NDEBUG
    EXPECT_DEATH({ v %= scalar_zero; }, expected_death_msg);
#else
    GTEST_SKIP() << "Skipping death tests for modulo by zero in release build (NDEBUG defined).";
#endif
}

// Vector Operations

TEST(Vector2iTest, Abs) {
    // Arrange
    Vector2i v1(2, -3);
    Vector2i v2(-2, 3);
    Vector2i v3(-2, -3);
    Vector2i expected(2, 3);

    // Act & Assert
    EXPECT_EQ(v1.abs(), expected);
    EXPECT_EQ(v2.abs(), expected);
    EXPECT_EQ(v3.abs(), expected);
    EXPECT_EQ(Vector2i(0, 0).abs(), Vector2i(0, 0));
}

TEST(Vector2iTest, Min) {
    // Arrange
    Vector2i v1(2, 5);
    Vector2i v2(4, 3);
    Vector2i expected(2, 3);

    // Act
    Vector2i result = v1.min(v2);

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, Max) {
    // Arrange
    Vector2i v1(2, 5);
    Vector2i v2(4, 3);
    Vector2i expected(4, 5);

    // Act
    Vector2i result = v1.max(v2);

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2iTest, Dot) {
    // Arrange
    Vector2i v1(2, 3);
    Vector2i v2(1, 2);
    int expected_dot = 2 * 1 + 3 * 2;

    // Act
    int result = v1.dot(v2);

    // Assert
    EXPECT_EQ(result, expected_dot);
}

TEST(Vector2iTest, Cross) {
    // Arrange
    Vector2i v1(2, 3);
    Vector2i v2(1, 2);
    int expected_cross = 2 * 2 - 3 * 1;

    // Act
    int result = v1.cross(v2);

    // Assert
    EXPECT_EQ(result, expected_cross);
}

TEST(Vector2iTest, Length) {
    // Arrange
    Vector2i v_pythagorean(3, 4);
    Vector2i v_general(2, 3);
    Vector2i v_zero(0, 0);

    // Act
    float result_pythagorean = v_pythagorean.length();
    float result_general = v_general.length();
    float result_zero = v_zero.length();

    // Assert
    EXPECT_FLOAT_EQ(result_pythagorean, 5.0f);
    EXPECT_FLOAT_EQ(result_general, std::sqrt(static_cast<float>(2 * 2 + 3 * 3)));
    EXPECT_FLOAT_EQ(result_zero, 0.0f);
}

TEST(Vector2iTest, LengthSquared) {
    // Arrange
    Vector2i v(2, 3);
    int expected_len_sq = 2 * 2 + 3 * 3;

    // Act
    int result = v.length_squared();

    // Assert
    EXPECT_EQ(result, expected_len_sq);
    EXPECT_EQ(Vector2i(0, 0).length_squared(), 0);
}

TEST(Vector2iTest, DistanceTo) {
    // Arrange
    Vector2i v1(1, 1);
    Vector2i v2(4, 5); 
    float expected_distance = 5.0f;

    // Act
    float result = v1.distance_to(v2);

    // Assert
    EXPECT_FLOAT_EQ(result, expected_distance);
}

TEST(Vector2iTest, DistanceSquaredTo) {
    // Arrange
    Vector2i v1(1, 1);
    Vector2i v2(4, 5); 
    int expected_dist_sq = 3 * 3 + 4 * 4;

    // Act
    int result = v1.distance_squared_to(v2);

    // Assert
    EXPECT_EQ(result, expected_dist_sq);
}

// Special Vectors

TEST(Vector2iTest, SpecialVectorZero) {
    // Arrange & Act (Static member)
    // Assert
    EXPECT_EQ(Vector2i::Zero, Vector2i(0, 0));
}

TEST(Vector2iTest, SpecialVectorOne) {
    // Arrange & Act (Static member)
    // Assert
    EXPECT_EQ(Vector2i::One, Vector2i(1, 1));
}

TEST(Vector2iTest, SpecialVectorUnitX) {
    // Arrange & Act (Static member)
    // Assert
    EXPECT_EQ(Vector2i::UnitX, Vector2i(1, 0));
}

TEST(Vector2iTest, SpecialVectorUnitY) {
    // Arrange & Act (Static member)
    // Assert
    EXPECT_EQ(Vector2i::UnitY, Vector2i(0, 1));
}