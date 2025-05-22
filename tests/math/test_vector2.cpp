#include <penguin_framework/core/math/vector2.hpp>
#include <penguin_framework/core/math/math_types.hpp>
#include <gtest/gtest.h>

// Helper Functions

void ExpectVector2Near(const Vector2& expected, const Vector2& actual, float tolerance = penguin::math::epsilon) {
	EXPECT_NEAR(expected.x, actual.x, tolerance);
	EXPECT_NEAR(expected.y, actual.y, tolerance);
}

// Constructors

TEST(Vector2Test, DefaultConstructor) {
	// Arrange & Act
	Vector2 v;

	// Assert
	EXPECT_FLOAT_EQ(v.x, Vector2::Origin);
	EXPECT_FLOAT_EQ(v.y, Vector2::Origin);
}

TEST(Vector2Test, XYConstructor) {
	// Arrange
	float x = 1.2f, y = 3.4f;

	// Act
	Vector2 v(x, y);

	// Assert
	EXPECT_FLOAT_EQ(v.x, x);
	EXPECT_FLOAT_EQ(v.y, y);
}

TEST(Vector2Test, ScalarConstructor) {
	// Arrange
	float scalar = 5.6f;

	// Act
	Vector2 v(scalar);

	// Assert
	EXPECT_FLOAT_EQ(v.x, scalar);
	EXPECT_FLOAT_EQ(v.y, scalar);
}

TEST(Vector2Test, CopyConstructor) {
	// Arrange
	Vector2 original(1.1f, 2.2f);

	// Act
	Vector2 copy(original);

	// Assert
	EXPECT_EQ(copy, original); // Uses the Vector2::operator== instead of comparing the float values
}

TEST(Vector2Test, MoveConstructor) {
	// Arrange
	Vector2 original(1.1f, 2.2f);
	Vector2 reference_original = original; // Create a copy for comparison

	// Act
	Vector2 moved(std::move(original));

	// Assert
	EXPECT_EQ(moved, reference_original);
}

TEST(Vector2Test, CopyAssignment) {
	// Arrange
	Vector2 original(3.3f, 4.4f);
	Vector2 copy_assigned;
	ASSERT_NE(copy_assigned, original); // Ensure it's different before assignment

	// Act
	copy_assigned = original;

	// Assert
	EXPECT_EQ(copy_assigned, original);
}

TEST(Vector2Test, MoveAssignment) {
	// Arrange
	Vector2 original(5.5f, 6.6f);
	Vector2 reference_original = original; // For comparison
	Vector2 move_assigned;
	ASSERT_NE(move_assigned, original);

	// Act
	move_assigned = std::move(original);

	// Assert
	EXPECT_EQ(move_assigned, reference_original);
}

// Binary Operators (Vector2 vs Vector2)

TEST(Vector2Test, OperatorAddVector) {
	// Arrange
	Vector2 v1(1.0f, 2.0f);
	Vector2 v2(3.0f, 4.0f);
	Vector2 expected(4.0f, 6.0f);

	// Act
	Vector2 result = v1 + v2;

	// Assert
	EXPECT_EQ(result, expected);
}

TEST(Vector2Test, OperatorSubtractVector) {
	// Arrange
	Vector2 v1(5.0f, 2.0f);
	Vector2 v2(3.0f, 4.0f);
	Vector2 expected(2.0f, -2.0f);

	// Act
	Vector2 result = v1 - v2;

	// Assert
	EXPECT_EQ(result, expected);
}

TEST(Vector2Test, OperatorMultiplyVector) {
	// Arrange
	Vector2 v1(2.0f, 3.0f);
	Vector2 v2(4.0f, 5.0f);
	Vector2 expected(8.0f, 15.0f);

	// Act
	Vector2 result = v1 * v2;

	// Assert
	EXPECT_EQ(result, expected);
}

TEST(Vector2Test, OperatorDivideVector) {
	// Arrange
	Vector2 v1(10.0f, 20.0f);
	Vector2 v2(2.0f, 4.0f);
	Vector2 expected(5.0f, 5.0f);

	// Act
	Vector2 result = v1 / v2;

	// Assert
	ExpectVector2Near(expected, result); // EXPECT_FLOAT_EQ has a limit of 4 ULPs, allows to test if the results are near with more ULPs
}

TEST(Vector2Test, OperatorDivideVectorByZero_Extended) {
    // Arrange
    Vector2 v_num_pos(10.0f, 20.0f);
    Vector2 v_num_neg(-10.0f, -20.0f);
    Vector2 v_num_x_zero(0.0f, 20.0f);
    Vector2 v_num_y_zero(10.0f, 0.0f);
    Vector2 v_num_all_zero(0.0f, 0.0f);

    Vector2 v_den_x_zero(0.0f, 4.0f);
    Vector2 v_den_y_zero(2.0f, 0.0f);
    Vector2 v_den_all_zero(0.0f, 0.0f);

    // Act & Assert
    // Case 1: (NonZero / Zero, NonZero / NonZero)
    Vector2 res1 = v_num_pos / v_den_x_zero;
    EXPECT_TRUE(std::isinf(res1.x) && res1.x > 0);
    EXPECT_FLOAT_EQ(res1.y, 5.0f);

    // Case 2: (NonZero / NonZero, NonZero / Zero) with negative numerator
    Vector2 res2 = v_num_neg / v_den_y_zero;
    EXPECT_FLOAT_EQ(res2.x, -5.0f);
    EXPECT_TRUE(std::isinf(res2.y) && res2.y < 0);

    // Case 3: (Zero / Zero, NonZero / NonZero)
    Vector2 res3 = v_num_x_zero / v_den_x_zero;
    EXPECT_TRUE(std::isnan(res3.x));
    EXPECT_FLOAT_EQ(res3.y, 5.0f);

    // Case 4: (NonZero / Zero, Zero / Zero)
    Vector2 res4 = v_num_y_zero / v_den_all_zero;
    EXPECT_TRUE(std::isinf(res4.x) && res4.x > 0);
    EXPECT_TRUE(std::isnan(res4.y));

    // Case 5: (Zero / Zero, Zero / Zero)
    Vector2 res5 = v_num_all_zero / v_den_all_zero;
    EXPECT_TRUE(std::isnan(res5.x));
    EXPECT_TRUE(std::isnan(res5.y));

    // Case 6: (NonZero / Zero, NonZero / Zero)
    Vector2 res6 = v_num_pos / v_den_all_zero;
    EXPECT_TRUE(std::isinf(res6.x) && res6.x > 0);
    EXPECT_TRUE(std::isinf(res6.y) && res6.y > 0);

    // Case 7: (NonZero / Zero, NonZero / Zero) with negative numerator
    Vector2 res7 = v_num_neg / v_den_all_zero;
    EXPECT_TRUE(std::isinf(res7.x) && res7.x < 0);
    EXPECT_TRUE(std::isinf(res7.y) && res7.y < 0);
}

// Assignment Operators (Vector2 vs Vector2)

TEST(Vector2Test, OperatorAddAssignVector) {
	// Arrange
	Vector2 v(1.0f, 2.0f);
	Vector2 v_add(3.0f, 4.0f);
	Vector2 expected(4.0f, 6.0f);

	// Act
	v += v_add;

	// Assert
	EXPECT_EQ(v, expected);
}

TEST(Vector2Test, OperatorSubtractAssignVector) {
	// Arrange
	Vector2 v(5.0f, 2.0f);
	Vector2 v_sub(3.0f, 4.0f);
	Vector2 expected(2.0f, -2.0f);

	// Act
	v -= v_sub;

	// Assert
	EXPECT_EQ(v, expected);
}

TEST(Vector2Test, OperatorMultiplyAssignVector) {
	// Arrange
	Vector2 v(2.0f, 3.0f);
	Vector2 v_mul(4.0f, 5.0f);
	Vector2 expected(8.0f, 15.0f);

	// Act
	v *= v_mul;

	// Assert
	EXPECT_EQ(v, expected);
}

TEST(Vector2Test, OperatorDivideAssignVector) {
	// Arrange
	Vector2 v(10.0f, 20.0f);
	Vector2 v_div(2.0f, 4.0f);
	Vector2 expected(5.0f, 5.0f);

	// Act
	v /= v_div;

	// Assert
	ExpectVector2Near(expected, v);
}

TEST(Vector2Test, OperatorDivideAssignVectorByZero_Extended) {
    // Arrange
    Vector2 v_num_pos_orig(10.0f, 20.0f);
    Vector2 v_num_neg_orig(-10.0f, -20.0f);
    Vector2 v_num_x_zero_orig(0.0f, 20.0f);
    Vector2 v_num_y_zero_orig(10.0f, 0.0f);
    Vector2 v_num_all_zero_orig(0.0f, 0.0f);

    Vector2 v_den_x_zero(0.0f, 4.0f);
    Vector2 v_den_y_zero(2.0f, 0.0f);
    Vector2 v_den_all_zero(0.0f, 0.0f);

    // Act & Assert
    // Case 1: (NonZero / Zero, NonZero / NonZero)
    Vector2 v_case1 = v_num_pos_orig; 
    v_case1 /= v_den_x_zero;
    EXPECT_TRUE(std::isinf(v_case1.x) && v_case1.x > 0);
    EXPECT_FLOAT_EQ(v_case1.y, 5.0f);

    // Case 2: (NonZero / NonZero, NonZero / Zero) with negative numerator
    Vector2 v_case2 = v_num_neg_orig;
    v_case2 /= v_den_y_zero;
    EXPECT_FLOAT_EQ(v_case2.x, -5.0f);
    EXPECT_TRUE(std::isinf(v_case2.y) && v_case2.y < 0);

    // Case 3: (Zero / Zero, NonZero / NonZero)
    Vector2 v_case3 = v_num_x_zero_orig;
    v_case3 /= v_den_x_zero;
    EXPECT_TRUE(std::isnan(v_case3.x));
    EXPECT_FLOAT_EQ(v_case3.y, 5.0f);

    // Case 4: (NonZero / Zero, Zero / Zero)
    Vector2 v_case4 = v_num_y_zero_orig;
    v_case4 /= v_den_all_zero;
    EXPECT_TRUE(std::isinf(v_case4.x) && v_case4.x > 0);
    EXPECT_TRUE(std::isnan(v_case4.y));

    // Case 5: (Zero / Zero, Zero / Zero)
    Vector2 v_case5 = v_num_all_zero_orig;
    v_case5 /= v_den_all_zero;
    EXPECT_TRUE(std::isnan(v_case5.x));
    EXPECT_TRUE(std::isnan(v_case5.y));

    // Case 6: (NonZero / Zero, NonZero / Zero)
    Vector2 v_case6 = v_num_pos_orig;
    v_case6 /= v_den_all_zero;
    EXPECT_TRUE(std::isinf(v_case6.x) && v_case6.x > 0);
    EXPECT_TRUE(std::isinf(v_case6.y) && v_case6.y > 0);

    // Case 7: (NonZero / Zero, NonZero / Zero) with negative numerator
    Vector2 v_case7 = v_num_neg_orig;
    v_case7 /= v_den_all_zero;
    EXPECT_TRUE(std::isinf(v_case7.x) && v_case7.x < 0);
    EXPECT_TRUE(std::isinf(v_case7.y) && v_case7.y < 0);
}

// Comparison Operators

TEST(Vector2Test, OperatorEqual) {
    // Arrange
    Vector2 v1(1.23f, 4.56f);
    Vector2 v2(1.23f, 4.56f);
    Vector2 v3(1.23f, 7.89f);
    Vector2 v4(0.0f, 4.56f);

    // Act & Assert
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
    EXPECT_FALSE(v1 == v4);
}

TEST(Vector2Test, OperatorNotEqual) {
    // Arrange
    Vector2 v1(1.23f, 4.56f);
    Vector2 v2(1.23f, 4.56f);
    Vector2 v3(1.23f, 7.89f);
    Vector2 v4(0.0f, 4.56f);

    // Act & Assert
    EXPECT_FALSE(v1 != v2);
    EXPECT_TRUE(v1 != v3);
    EXPECT_TRUE(v1 != v4);
}

TEST(Vector2Test, OperatorThreeWayComparison) {
    // Arrange
    Vector2 v1(1.0f, 2.0f);
    Vector2 v2(1.0f, 3.0f);
    Vector2 v3(2.0f, 1.0f);
    Vector2 v_equal(1.0f, 2.0f);

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

TEST(Vector2Test, OperatorUnaryMinus) {
    // Arrange
    Vector2 v(1.5f, -2.5f);
    Vector2 expected(-1.5f, 2.5f);

    // Act
    Vector2 result = -v;

    // Assert
    EXPECT_EQ(result, expected);
}

// Scalar Operators

TEST(Vector2Test, OperatorAddScalar) {
    // Arrange
    Vector2 v(1.0f, 2.0f);
    float scalar = 5.0f;
    Vector2 expected(6.0f, 7.0f);

    // Act
    Vector2 result = v + scalar;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2Test, OperatorSubtractScalar) {
    // Arrange
    Vector2 v(10.0f, 20.0f);
    float scalar = 5.0f;
    Vector2 expected(5.0f, 15.0f);

    // Act
    Vector2 result = v - scalar;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2Test, OperatorMultiplyScalar) {
    // Arrange
    Vector2 v(2.0f, 3.0f);
    float scalar = 4.0f;
    Vector2 expected(8.0f, 12.0f);

    // Act
    Vector2 result = v * scalar;

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2Test, OperatorDivideScalar) {
    // Arrange
    Vector2 v(10.0f, 20.0f);
    float scalar = 2.0f;
    Vector2 expected(5.0f, 10.0f);

    // Act
    Vector2 result = v / scalar;

    // Assert
    ExpectVector2Near(expected, result);
}

TEST(Vector2Test, OperatorDivideScalarByZero_NonZeroNumerator) {
    // Arrange
    Vector2 v_pos(10.0f, 20.0f);
    Vector2 v_neg(-5.0f, -15.0f);
    float scalar = 0.0f;

    // Act
    Vector2 result_pos = v_pos / scalar;
    Vector2 result_neg = v_neg / scalar;

    // Assert (for positive numerator)
    EXPECT_TRUE(std::isinf(result_pos.x));
    EXPECT_TRUE(std::isinf(result_pos.y));
    EXPECT_GT(result_pos.x, 0.0f);
    EXPECT_GT(result_pos.y, 0.0f);
    EXPECT_GT(result_pos.x * v_pos.x, 0);

    // Assert (for negative numerator)
    EXPECT_TRUE(std::isinf(result_neg.x));
    EXPECT_TRUE(std::isinf(result_neg.y));
    EXPECT_LT(result_neg.x, 0.0f);
    EXPECT_LT(result_neg.y, 0.0f);
    EXPECT_GT(result_neg.x * v_neg.x, 0); // (-inf * -5.0f) is +inf > 0
}

TEST(Vector2Test, OperatorDivideScalarByZero_ZeroNumerator) {
    // Arrange
    Vector2 v(0.0f, 0.0f);
    float scalar = 0.0f;

    // Act
    Vector2 result = v / scalar; // Expect (NaN, NaN)

    // Assert
    EXPECT_TRUE(std::isnan(result.x));
    EXPECT_TRUE(std::isnan(result.y));
}

TEST(Vector2Test, OperatorDivideScalarByZero_MixedNumerator) {
    // Arrange
    Vector2 v_x_zero(0.0f, 20.0f);
    Vector2 v_y_zero(10.0f, 0.0f);
    Vector2 v_y_neg_zero(10.0f, -0.0f);
    float scalar = 0.0f;

    // Act
    Vector2 result1 = v_x_zero / scalar; // Expect (NaN, +Inf)
    Vector2 result2 = v_y_zero / scalar; // Expect (+Inf, NaN)
    Vector2 result3 = v_y_neg_zero / scalar; // Expect (+Inf, NaN or -NaN depending on -0.0f/0.0f behavior)

    // Assert for result1
    EXPECT_TRUE(std::isnan(result1.x));
    EXPECT_TRUE(std::isinf(result1.y));
    EXPECT_GT(result1.y, 0.0f); // Positive infinity

    // Assert for result2
    EXPECT_TRUE(std::isinf(result2.x));
    EXPECT_TRUE(std::isnan(result2.y));
    EXPECT_GT(result2.x, 0.0f); // Positive infinity

    // Assert for result3 (0.0f/0.0f is NaN, -0.0f/0.0f is also NaN)
    EXPECT_TRUE(std::isinf(result3.x));
    EXPECT_TRUE(std::isnan(result3.y));
    EXPECT_GT(result3.x, 0.0f);
}

// Scalar Assignment Operators

TEST(Vector2Test, OperatorAddAssignScalar) {
    // Arrange
    Vector2 v(1.0f, 2.0f);
    float scalar = 5.0f;
    Vector2 expected(6.0f, 7.0f);

    // Act
    v += scalar;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2Test, OperatorSubtractAssignScalar) {
    // Arrange
    Vector2 v(10.0f, 20.0f);
    float scalar = 5.0f;
    Vector2 expected(5.0f, 15.0f);

    // Act
    v -= scalar;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2Test, OperatorMultiplyAssignScalar) {
    // Arrange
    Vector2 v(2.0f, 3.0f);
    float scalar = 4.0f;
    Vector2 expected(8.0f, 12.0f);

    // Act
    v *= scalar;

    // Assert
    EXPECT_EQ(v, expected);
}

TEST(Vector2Test, OperatorDivideAssignScalar) {
    // Arrange
    Vector2 v(10.0f, 20.0f);
    float scalar = 2.0f;
    Vector2 expected(5.0f, 10.0f);

    // Act
    v /= scalar;

    // Assert
    ExpectVector2Near(expected, v);
}

TEST(Vector2Test, OperatorDivideAssignScalarByZero_NonZeroNumerator) {
    // Arrange
    Vector2 v_pos(10.0f, 20.0f);
    Vector2 v_neg(-5.0f, -15.0f);
    Vector2 v_pos_orig = v_pos;
    Vector2 v_neg_orig = v_neg;
    float scalar = 0.0f;

    // Act
    v_pos /= scalar;
    v_neg /= scalar;

    // Assert (for positive numerator)
    EXPECT_TRUE(std::isinf(v_pos.x));
    EXPECT_TRUE(std::isinf(v_pos.y));
    EXPECT_GT(v_pos.x, 0.0f);
    EXPECT_GT(v_pos.y, 0.0f);
    EXPECT_GT(v_pos.x * v_pos_orig.x, 0);

    // Assert (for negative numerator)
    EXPECT_TRUE(std::isinf(v_neg.x));
    EXPECT_TRUE(std::isinf(v_neg.y));
    EXPECT_LT(v_neg.x, 0.0f);
    EXPECT_LT(v_neg.y, 0.0f);
    EXPECT_GT(v_neg.x * v_neg_orig.x, 0); // (-inf * -5.0f) is +inf > 0
}

TEST(Vector2Test, OperatorDivideAssignScalarByZero_ZeroNumerator) {
    // Arrange
    Vector2 v(0.0f, 0.0f);
    float scalar = 0.0f;

    // Act
    v /= scalar; // Expect (NaN, NaN)

    // Assert
    EXPECT_TRUE(std::isnan(v.x));
    EXPECT_TRUE(std::isnan(v.y));
}

TEST(Vector2Test, OperatorDivideAssignScalarByZero_MixedNumerator) {
    // Arrange
    Vector2 v_x_zero(0.0f, 20.0f);
    Vector2 v_y_zero(10.0f, 0.0f);
    Vector2 v_y_neg_zero(10.0f, -0.0f);
    float scalar = 0.0f;

    // Act
    v_x_zero /= scalar; // Expect (NaN, +Inf)
    v_y_zero /= scalar; // Expect (+Inf, NaN)
    v_y_neg_zero /= scalar; // Expect (+Inf, NaN or -NaN depending on -0.0f/0.0f behavior)

    // Assert for v_x_zero
    EXPECT_TRUE(std::isnan(v_x_zero.x));
    EXPECT_TRUE(std::isinf(v_x_zero.y));
    EXPECT_GT(v_x_zero.y, 0.0f); // Positive infinity

    // Assert for v_y_zero
    EXPECT_TRUE(std::isinf(v_y_zero.x));
    EXPECT_TRUE(std::isnan(v_y_zero.y));
    EXPECT_GT(v_y_zero.x, 0.0f); // Positive infinity

    // Assert for v_y_neg_zero (0.0f/0.0f is NaN, -0.0f/0.0f is also NaN)
    EXPECT_TRUE(std::isinf(v_y_neg_zero.x));
    EXPECT_TRUE(std::isnan(v_y_neg_zero.y));
    EXPECT_GT(v_y_neg_zero.x, 0.0f);
}

// Vector Operations

TEST(Vector2Test, Abs) {
    // Arrange
    Vector2 v(-1.5f, 2.0f);
    Vector2 v_positive(1.5f, 2.0f);
    Vector2 v_negative(-1.5f, -2.0f);
    Vector2 expected_v(1.5f, 2.0f);
    Vector2 expected_v_positive(1.5f, 2.0f);
    Vector2 expected_v_negative(1.5f, 2.0f);

    // Act
    Vector2 result_v = v.abs();
    Vector2 result_v_positive = v_positive.abs();
    Vector2 result_v_negative = v_negative.abs();

    // Assert
    EXPECT_EQ(result_v, expected_v);
    EXPECT_EQ(result_v_positive, expected_v_positive);
    EXPECT_EQ(result_v_negative, expected_v_negative);
}

TEST(Vector2Test, Floor) {
    // Arrange
    Vector2 v(1.7f, -2.3f);
    Vector2 expected(1.0f, -3.0f);

    // Act
    Vector2 result = v.floor();

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2Test, Ceil) {
    // Arrange
    Vector2 v(1.2f, -2.8f);
    Vector2 expected(2.0f, -2.0f);

    // Act
    Vector2 result = v.ceil();

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2Test, Round) {
    // Arrange
    Vector2 v1(1.2f, -2.8f);
    Vector2 v2(1.5f, -2.5f);
    Vector2 v3(1.7f, -2.3f);
    Vector2 expected1(1.0f, -3.0f);
    Vector2 expected2(2.0f, -3.0f);
    Vector2 expected3(2.0f, -2.0f);

    // Act
    Vector2 result1 = v1.round();
    Vector2 result2 = v2.round();
    Vector2 result3 = v3.round();

    // Assert
    EXPECT_EQ(result1, expected1);
    EXPECT_EQ(result2, expected2);
    EXPECT_EQ(result3, expected3);
}

TEST(Vector2Test, Min) {
    // Arrange
    Vector2 v1(1.0f, 5.0f);
    Vector2 v2(3.0f, 2.0f);
    Vector2 expected(1.0f, 2.0f);

    // Act
    Vector2 result = v1.min(v2);

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2Test, Max) {
    // Arrange
    Vector2 v1(1.0f, 5.0f);
    Vector2 v2(3.0f, 2.0f);
    Vector2 expected(3.0f, 5.0f);

    // Act
    Vector2 result = v1.max(v2);

    // Assert
    EXPECT_EQ(result, expected);
}

TEST(Vector2Test, Lerp) {
    // Arrange
    Vector2 v_from(0.0f, 0.0f);
    Vector2 v_to(10.0f, 20.0f);

    Vector2 midpoint = Vector2(5.0f, 10.0f);
    Vector2 extrapolate1 = Vector2(-5.0f, -10.0f);
    Vector2 extrapolate2 = Vector2(15.0f, 30.0f);

    // Act & Assert
    ExpectVector2Near(v_from.lerp(v_to, 0.0f), v_from);
    ExpectVector2Near(v_from.lerp(v_to, 1.0f), v_to);
    ExpectVector2Near(v_from.lerp(v_to, 0.5f), midpoint);
    ExpectVector2Near(v_from.lerp(v_to, -0.5f), extrapolate1);
    ExpectVector2Near(v_from.lerp(v_to, 1.5f), extrapolate2);
}

TEST(Vector2Test, Dot) {
    // Arrange
    Vector2 v1(1.0f, 2.0f);
    Vector2 v2(3.0f, 4.0f);
    float expected = 1.0f * 3.0f + 2.0f * 4.0f; 

    // Act
    float result = v1.dot(v2);

    // Assert
    EXPECT_FLOAT_EQ(result, expected);
}

TEST(Vector2Test, Cross) {
    // Arrange
    Vector2 v1(1.0f, 2.0f);
    Vector2 v2(3.0f, 4.0f);
    float expected = 1.0f * 4.0f - 2.0f * 3.0f;

    // Act
    float result = v1.cross(v2);

    // Assert
    EXPECT_FLOAT_EQ(result, expected);
}

TEST(Vector2Test, Length) {
    // Arrange
    Vector2 v1(3.0f, 4.0f);
    float expected1 = 5.0f;
    Vector2 v2(0.0f, 0.0f);
    float expected2 = 0.0f;
    Vector2 v3(-1.0f, 0.0f);
    float expected3 = 1.0f;

    // Act
    float result1 = v1.length();
    float result2 = v2.length();
    float result3 = v3.length();

    // Assert
    EXPECT_FLOAT_EQ(result1, expected1);
    EXPECT_FLOAT_EQ(result2, expected2);
    EXPECT_FLOAT_EQ(result3, expected3);
}

TEST(Vector2Test, LengthSquared) {
    // Arrange
    Vector2 v1(3.0f, 4.0f);
    float expected1 = 3.0f * 3.0f + 4.0f * 4.0f; 
    Vector2 v2(0.0f, 0.0f);
    float expected2 = 0.0f;

    // Act
    float result1 = v1.length_squared();
    float result2 = v2.length_squared();

    // Assert
    EXPECT_FLOAT_EQ(result1, expected1);
    EXPECT_FLOAT_EQ(result2, expected2);
}

TEST(Vector2Test, Normalize) {
    // Arrange
    Vector2 v_to_normalize(3.0f, 4.0f);
    Vector2 expected_normalized(3.0f / 5.0f, 4.0f / 5.0f);

    Vector2 v_zero(0.0f, 0.0f);
    Vector2 expected_zero_normalized(0.0f, 0.0f);

    float val_len_is_zero = 1e-7f; // 0.0000001f -> LESS than epsilon (1e-6f)
    Vector2 v_len_is_zero(val_len_is_zero, 0.0f); // Length is 1e-7f, considered to be zero approximately
    Vector2 expected_len_is_zero = v_len_is_zero;

    float val_len_is_not_zero = 1e-4f; // 0.0001f -> GREATER than epsilon (1e-6f)
    Vector2 v_len_is_not_zero(val_len_is_not_zero, 0.0f); // Length is 1e-4f, not considered to be zero approximately
    Vector2 expected_len_is_not_zero_normalized(1.0f, 0.0f);

    // Act
    Vector2 v_copy = v_to_normalize;
    v_copy.normalize();

    Vector2 v_zero_copy = v_zero;
    v_zero_copy.normalize();

    Vector2 v_len_is_zero_copy = v_len_is_zero;
    v_len_is_zero_copy.normalize();

    Vector2 v_len_is_not_zero_copy = v_len_is_not_zero;
    v_len_is_not_zero_copy.normalize();

    // Assert
    // Standard case
    ExpectVector2Near(expected_normalized, v_copy);
    EXPECT_NEAR(v_copy.length(), 1.0f, penguin::math::epsilon);

    // Zero vector case
    ExpectVector2Near(expected_zero_normalized, v_zero_copy);
    EXPECT_FLOAT_EQ(v_zero_copy.length(), 0.0f);

    // Length is effectively zero (1e-7f < 1e-6f)
    ExpectVector2Near(expected_len_is_zero, v_len_is_zero_copy);
    EXPECT_FLOAT_EQ(v_len_is_zero_copy.length(), val_len_is_zero);

    // Length is small but not zero (1e-4f > 1e-6f)
    ExpectVector2Near(expected_len_is_not_zero_normalized, v_len_is_not_zero_copy);
    EXPECT_NEAR(v_len_is_not_zero_copy.length(), 1.0f, penguin::math::epsilon);
}

TEST(Vector2Test, Normalized) {
    // Arrange
    Vector2 v_to_normalize(3.0f, 4.0f);
    Vector2 expected_normalized(3.0f / 5.0f, 4.0f / 5.0f);

    Vector2 v_zero(0.0f, 0.0f);
    Vector2 expected_zero_normalized(0.0f, 0.0f);

    float val_len_is_zero = 1e-7f; // 0.0000001f -> LESS than epsilon (1e-6f)
    Vector2 v_len_is_zero(val_len_is_zero, 0.0f); // Length is 1e-7f, considered to be zero approximately
    Vector2 expected_len_is_zero = v_len_is_zero;

    float val_len_is_not_zero = 1e-4f; // 0.0001f -> GREATER than epsilon (1e-6f)
    Vector2 v_len_is_not_zero(val_len_is_not_zero, 0.0f); // Length is 1e-4f, not considered to be zero approximately
    Vector2 expected_len_is_not_zero_normalized(1.0f, 0.0f);

    // Act
    Vector2 v_normalized_result = v_to_normalize.normalized();
    Vector2 v_zero_normalized_result = v_zero.normalized();
    Vector2 v_len_is_zero_normalized_result = v_len_is_zero.normalized();
    Vector2 v_len_is_not_zero_normalized_result = v_len_is_not_zero.normalized();

    // Assert
    // Standard case
    ExpectVector2Near(expected_normalized, v_normalized_result);
    EXPECT_NEAR(v_normalized_result.length(), 1.0f, penguin::math::epsilon);
    EXPECT_EQ(v_to_normalize, Vector2(3.0f, 4.0f));

    // Zero vector case
    ExpectVector2Near(expected_zero_normalized, v_zero_normalized_result);
    EXPECT_FLOAT_EQ(v_zero_normalized_result.length(), 0.0f);
    EXPECT_EQ(v_zero, Vector2(0.0f, 0.0f));

    // Length is effectively zero by is_zero_approx (e.g., 1e-7f)
    ExpectVector2Near(expected_len_is_zero, v_len_is_zero_normalized_result);
    EXPECT_FLOAT_EQ(v_len_is_zero_normalized_result.length(), val_len_is_zero);
    EXPECT_EQ(v_len_is_zero, Vector2(val_len_is_zero, 0.0f)); 


    // Length is small but not effectively zero (e.g., 1e-4f)
    ExpectVector2Near(expected_len_is_not_zero_normalized, v_len_is_not_zero_normalized_result);
    EXPECT_NEAR(v_len_is_not_zero_normalized_result.length(), 1.0f, penguin::math::epsilon);
    EXPECT_EQ(v_len_is_not_zero, Vector2(val_len_is_not_zero, 0.0f));
}

TEST(Vector2Test, DistanceTo) {
    // Arrange
    Vector2 v1(1.0f, 2.0f);
    Vector2 v2(4.0f, 6.0f);
    float expected_distance = 5.0f;

    // Act
    float distance = v1.distance_to(v2);

    // Assert
    EXPECT_FLOAT_EQ(distance, expected_distance);
}

TEST(Vector2Test, DistanceSquaredTo) {
    // Arrange
    Vector2 v1(1.0f, 2.0f);
    Vector2 v2(4.0f, 6.0f);
    float expected_distance_sq = 3.0f * 3.0f + 4.0f * 4.0f;

    // Act
    float distance_sq = v1.distance_squared_to(v2);

    // Assert
    EXPECT_FLOAT_EQ(distance_sq, expected_distance_sq);
}

// Special Vectors

TEST(Vector2Test, SpecialVectorZero) {
    // Arrange & Act (Static member)
    // Assert
    EXPECT_EQ(Vector2::Zero, Vector2(0.0f, 0.0f));
}

TEST(Vector2Test, SpecialVectorOne) {
    // Arrange & Act (Static member)
    // Assert
    EXPECT_EQ(Vector2::One, Vector2(1.0f, 1.0f));
}

TEST(Vector2Test, SpecialVectorUnitX) {
    // Arrange & Act (Static member)
    // Assert
    EXPECT_EQ(Vector2::UnitX, Vector2(1.0f, 0.0f));
}

TEST(Vector2Test, SpecialVectorUnitY) {
    // Arrange & Act (Static member)
    // Assert
    EXPECT_EQ(Vector2::UnitY, Vector2(0.0f, 1.0f));
}