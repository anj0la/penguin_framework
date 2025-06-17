#include <penguin_framework/math/colour.hpp>
#include <penguin_framework/math/math_types.hpp>
#include <cmath>
#include <gtest/gtest.h>

using penguin::math::Colour;

// Helper Functions

void ExpectColourNear(const Colour & expected, const Colour & actual, float tolerance = penguin::math::epsilon) {
    EXPECT_NEAR(expected.r, actual.r, tolerance);
    EXPECT_NEAR(expected.g, actual.g, tolerance);
    EXPECT_NEAR(expected.b, actual.b, tolerance);
    EXPECT_NEAR(expected.a, actual.a, tolerance);
}

// Constructors

TEST(ColourTest, DefaultConstructor) {
    // Arrange & Act
    Colour c;

    // Assert
    EXPECT_FLOAT_EQ(c.r, 0.0f);
    EXPECT_FLOAT_EQ(c.g, 0.0f);
    EXPECT_FLOAT_EQ(c.b, 0.0f);
    EXPECT_FLOAT_EQ(c.a, 1.0f);
}

TEST(ColourTest, RGBAConstructor_Nominal) {
    // Arrange
    float r = 0.1f, g = 0.2f, b = 0.3f, a = 0.4f;

    // Act
    Colour c(r, g, b, a);

    // Assert
    EXPECT_FLOAT_EQ(c.r, r);
    EXPECT_FLOAT_EQ(c.g, g);
    EXPECT_FLOAT_EQ(c.b, b);
    EXPECT_FLOAT_EQ(c.a, a);
}

TEST(ColourTest, RGBAConstructor_Clamping) {
    // Arrange
    float r_low = -0.5f, g_high = 1.5f, b_nominal = 0.5f, a_low = -1.0f;
    float r_high = 2.0f, g_low = -0.1f, b_high = 1.1f, a_high = 3.0f;

    // Act
    Colour c_low_high(r_low, g_high, b_nominal, a_low);
    Colour c_high_low(r_high, g_low, b_high, a_high);

    // Assert
    EXPECT_FLOAT_EQ(c_low_high.r, 0.0f); // Clamped from -0.5f
    EXPECT_FLOAT_EQ(c_low_high.g, 1.0f); // Clamped from 1.5f
    EXPECT_FLOAT_EQ(c_low_high.b, 0.5f);
    EXPECT_FLOAT_EQ(c_low_high.a, 0.0f); // Clamped from -1.0f

    EXPECT_FLOAT_EQ(c_high_low.r, 1.0f); // Clamped from 2.0f
    EXPECT_FLOAT_EQ(c_high_low.g, 0.0f); // Clamped from -0.1f
    EXPECT_FLOAT_EQ(c_high_low.b, 1.0f); // Clamped from 1.1f
    EXPECT_FLOAT_EQ(c_high_low.a, 1.0f); // Clamped from 3.0f
}

TEST(ColourTest, RGBConstructor_Nominal) {
    // Arrange
    float r = 0.1f, g = 0.2f, b = 0.3f;

    // Act
    Colour c(r, g, b);

    // Assert
    EXPECT_FLOAT_EQ(c.r, r);
    EXPECT_FLOAT_EQ(c.g, g);
    EXPECT_FLOAT_EQ(c.b, b);
    EXPECT_FLOAT_EQ(c.a, 1.0f);
}

TEST(ColourTest, RGBConstructor_Clamping) {
    // Arrange
    float r_low = -0.5f, g_high = 1.5f, b_nominal = 0.5f;

    // Act
    Colour c(r_low, g_high, b_nominal);

    // Assert
    EXPECT_FLOAT_EQ(c.r, 0.0f); // Clamped
    EXPECT_FLOAT_EQ(c.g, 1.0f); // Clamped
    EXPECT_FLOAT_EQ(c.b, 0.5f);
    EXPECT_FLOAT_EQ(c.a, 1.0f);
}

TEST(ColourTest, CopyConstructor) {
    // Arrange
    Colour original(0.1f, 0.2f, 0.3f, 0.4f);

    // Act
    Colour copy(original);

    // Assert
    ExpectColourNear(copy, original);
}

TEST(ColourTest, MoveConstructor) {
    // Arrange
    Colour original(0.1f, 0.2f, 0.3f, 0.4f);
    Colour reference_original = original;

    // Act
    Colour moved(std::move(original));

    // Assert
    ExpectColourNear(moved, reference_original);
}

TEST(ColourTest, CopyAssignment) {
    // Arrange
    Colour original(0.1f, 0.2f, 0.3f, 0.4f);
    Colour copy_assigned;
    ASSERT_NE(copy_assigned, original);

    // Act
    copy_assigned = original;

    // Assert
    ExpectColourNear(copy_assigned, original);
}

TEST(ColourTest, MoveAssignment) {
    // Arrange
    Colour original(0.1f, 0.2f, 0.3f, 0.4f);
    Colour reference_original = original;
    Colour move_assigned;
    ASSERT_NE(move_assigned, original);

    // Act
    move_assigned = std::move(original);

    // Assert
    ExpectColourNear(move_assigned, reference_original);
}

// Comparison Operators

TEST(ColourTest, OperatorEqual) {
    // Arrange
    Colour c1(0.1f, 0.2f, 0.3f, 0.4f);
    Colour c2(0.1f, 0.2f, 0.3f, 0.4f);
    Colour c3(0.11f, 0.2f, 0.3f, 0.4f); // R differs
    Colour c4(0.1f, 0.22f, 0.3f, 0.4f); // G differs
    Colour c5(0.1f, 0.2f, 0.33f, 0.4f); // B differs
    Colour c6(0.1f, 0.2f, 0.3f, 0.44f); // A differs

    // Act & Assert
    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 == c3);
    EXPECT_FALSE(c1 == c4);
    EXPECT_FALSE(c1 == c5);
    EXPECT_FALSE(c1 == c6);
}

TEST(ColourTest, OperatorNotEqual) {
    // Arrange
    Colour c1(0.1f, 0.2f, 0.3f, 0.4f);
    Colour c2(0.1f, 0.2f, 0.3f, 0.4f);
    Colour c3(0.11f, 0.2f, 0.3f, 0.4f);

    // Act & Assert
    EXPECT_FALSE(c1 != c2);
    EXPECT_TRUE(c1 != c3);
}

// Binary Operators (Colour vs Colour)

TEST(ColourTest, OperatorAddColour) {
    // Arrange
    Colour c1(0.1f, 0.2f, 0.3f, 0.4f);
    Colour c2(0.2f, 0.3f, 0.4f, 0.5f);
    Colour expected(0.3f, 0.5f, 0.7f, 0.9f);

    // Act
    Colour result = c1 + c2;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorAddColour_Clamping) {
    // Arrange
    Colour c1(0.8f, 0.9f, 0.7f, 0.6f);
    Colour c2(0.5f, 0.4f, 0.6f, 0.7f);
    Colour expected(1.0f, 1.0f, 1.0f, 1.0f);

    // Act
    Colour result = c1 + c2;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorSubtractColour) {
    // Arrange
    Colour c1(0.5f, 0.6f, 0.7f, 0.8f);
    Colour c2(0.2f, 0.3f, 0.1f, 0.4f);
    Colour expected(0.3f, 0.3f, 0.6f, 0.4f);

    // Act
    Colour result = c1 - c2;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorSubtractColour_Clamping) {
    // Arrange
    Colour c1(0.1f, 0.2f, 0.3f, 0.0f);
    Colour c2(0.5f, 0.4f, 0.6f, 0.7f);
    Colour expected(0.0f, 0.0f, 0.0f, 0.0f);

    // Act
    Colour result = c1 - c2;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorMultiplyColour) {
    // Arrange
    Colour c1(0.5f, 0.4f, 0.8f, 1.0f);
    Colour c2(0.5f, 0.2f, 0.1f, 0.5f);
    Colour expected(0.25f, 0.08f, 0.08f, 0.5f);

    // Act
    Colour result = c1 * c2;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorDivideColour) {
    // Arrange
    Colour c1(0.8f, 0.6f, 0.4f, 1.0f);
    Colour c2(0.2f, 0.3f, 0.5f, 0.5f);
    Colour expected(1.0f, 1.0f, 0.8f, 1.0f);

    // Act
    Colour result = c1 / c2;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorDivideColourByZeroComponent) {
    // Arrange
    Colour c1(0.5f, 0.5f, 0.5f, 0.5f);
    Colour c_zero_r(0.0f, 0.5f, 0.5f, 0.5f);
    Colour c_zero_g(0.5f, 0.0f, 0.5f, 0.5f);
    Colour c_zero_b(0.5f, 0.5f, 0.0f, 0.5f);
    Colour c_zero_a(0.5f, 0.5f, 0.5f, 0.0f);
    Colour c_all_zero(0.0f, 0.0f, 0.0f, 0.0f);

    // Act
    Colour res_zero_r = c1 / c_zero_r;
    Colour res_zero_g = c1 / c_zero_g;
    Colour res_zero_b = c1 / c_zero_b;
    Colour res_zero_a = c1 / c_zero_a;
    Colour res_all_zero = c1 / c_all_zero; 

    Colour c_neg_num(0.0f, 0.0f, 0.0f, 0.0f);
    Colour res_neg_inf = c_neg_num / c_zero_r;

    // Assert
    ExpectColourNear(res_zero_r, Colour(1.0f, 1.0f, 1.0f, 1.0f));
    ExpectColourNear(res_zero_g, Colour(1.0f, 1.0f, 1.0f, 1.0f));
    ExpectColourNear(res_zero_b, Colour(1.0f, 1.0f, 1.0f, 1.0f));
    ExpectColourNear(res_zero_a, Colour(1.0f, 1.0f, 1.0f, 1.0f));
    ExpectColourNear(res_all_zero, Colour(1.0f, 1.0f, 1.0f, 1.0f));
    ExpectColourNear(res_neg_inf, Colour(0.0f, 0.0f, 0.0f, 0.0f));
}

// Assignment Operators (Colour vs Colour)

TEST(ColourTest, OperatorAddAssignColour) {
    // Arrange
    Colour c(0.1f, 0.2f, 0.3f, 0.4f);
    Colour c_add(0.2f, 0.3f, 0.4f, 0.5f);
    Colour expected(0.3f, 0.5f, 0.7f, 0.9f);

    // Act
    c += c_add;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorAddAssignColour_Clamping) {
    // Arrange
    Colour c(0.8f, 0.9f, 0.7f, 0.6f);
    Colour c_add(0.5f, 0.4f, 0.6f, 0.7f);
    Colour expected(1.0f, 1.0f, 1.0f, 1.0f);

    // Act
    c += c_add;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorSubtractAssignColour) {
    // Arrange
    Colour c(0.5f, 0.6f, 0.7f, 0.8f);
    Colour c_sub(0.2f, 0.3f, 0.1f, 0.4f);
    Colour expected(0.3f, 0.3f, 0.6f, 0.4f);

    // Act
    c -= c_sub;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorSubtractAssignColour_Clamping) {
    // Arrange
    Colour c(0.1f, 0.2f, 0.3f, 0.4f);
    Colour c_sub(0.5f, 0.4f, 0.6f, 0.7f);
    Colour expected(0.0f, 0.0f, 0.0f, 0.0f);

    // Act
    c -= c_sub;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorMultiplyAssignColour) {
    // Arrange
    Colour c(0.5f, 0.4f, 0.8f, 1.0f);
    Colour c_mul(0.5f, 0.2f, 0.1f, 0.5f);
    Colour expected(0.25f, 0.08f, 0.08f, 0.5f);

    // Act
    c *= c_mul;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorDivideAssignColour) {
    // Arrange
    Colour c(0.8f, 0.6f, 0.4f, 1.0f);
    Colour c_div(0.2f, 0.3f, 0.5f, 0.5f);
    Colour expected(1.0f, 1.0f, 0.8f, 1.0f); // Clamped

    // Act
    c /= c_div;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorDivideAssignColourByZeroComponent) {
    // Arrange
    Colour c1(0.5f, 0.5f, 0.5f, 0.5f);
    Colour c_orig = c1;
    Colour c_zero_r(0.0f, 0.5f, 0.5f, 0.5f);
    Colour expected_r_zero(1.0f, 1.0f, 1.0f, 1.0f);

    Colour c2(0.0f, 0.0f, 0.0f, 0.0f);
    Colour expected_all_zero(0.0f, 0.0f, 0.0f, 0.0f);


    // Act & Assert
    Colour test_c1 = c_orig;
    test_c1 /= c_zero_r;
    ExpectColourNear(test_c1, expected_r_zero);

    Colour test_c2 = c2; 
    test_c2 /= c_zero_r;
    ExpectColourNear(test_c2, expected_all_zero);
}

// Unary Operators

TEST(ColourTest, OperatorInvert) {
    // Arrange
    Colour c(0.2f, 0.8f, 0.0f, 0.5f);
    Colour expected(0.8f, 0.2f, 1.0f, 0.5f);

    // Act
    Colour result = ~c;

    // Assert
    ExpectColourNear(result, expected);
}

// Scalar Operators

TEST(ColourTest, OperatorAddScalar) {
    // Arrange
    Colour c(0.1f, 0.2f, 0.3f, 0.4f);
    float scalar = 0.1f;
    Colour expected(0.2f, 0.3f, 0.4f, 0.5f);

    // Act
    Colour result = c + scalar;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorAddScalar_Clamping) {
    // Arrange
    Colour c(0.8f, 0.9f, 0.95f, 1.0f);
    float scalar = 0.3f;
    Colour expected(1.0f, 1.0f, 1.0f, 1.0f);

    // Act
    Colour result = c + scalar;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorSubtractScalar) {
    // Arrange
    Colour c(0.5f, 0.6f, 0.7f, 0.8f);
    float scalar = 0.1f;
    Colour expected(0.4f, 0.5f, 0.6f, 0.7f);

    // Act
    Colour result = c - scalar;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorSubtractScalar_Clamping) {
    // Arrange
    Colour c(0.1f, 0.2f, 0.0f, 0.05f);
    float scalar = 0.3f;
    Colour expected(0.0f, 0.0f, 0.0f, 0.0f);

    // Act
    Colour result = c - scalar;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorMultiplyScalar) {
    // Arrange
    Colour c(0.2f, 0.3f, 0.4f, 0.5f);
    float scalar = 2.0f;
    Colour expected(0.4f, 0.6f, 0.8f, 1.0f);

    // Act
    Colour result = c * scalar;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorMultiplyScalar_Clamping) {
    // Arrange
    Colour c(0.4f, 0.5f, 0.6f, 0.8f);
    float scalar = 3.0f;
    Colour expected(1.0f, 1.0f, 1.0f, 1.0f);

    // Act
    Colour result = c * scalar;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorDivideScalar) {
    // Arrange
    Colour c(0.4f, 0.6f, 0.8f, 1.0f);
    float scalar = 2.0f;
    Colour expected(0.2f, 0.3f, 0.4f, 0.5f);

    // Act
    Colour result = c / scalar;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorDivideScalar_Clamping) {
    // Arrange
    Colour c(0.5f, 0.8f, 1.0f, 0.2f);
    float scalar = 0.1f;
    Colour expected(1.0f, 1.0f, 1.0f, 1.0f);

    // Act
    Colour result = c / scalar;

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, OperatorDivideScalarByZero) {
    // Arrange
    Colour c_pos(0.5f, 0.5f, 0.5f, 0.5f);
    Colour c_zero_val(0.0f, 0.0f, 0.0f, 0.0f);
    float scalar_zero = 0.0f;

    // Act
    Colour result_pos_div_zero = c_pos / scalar_zero;
    Colour result_zero_div_zero = c_zero_val / scalar_zero;

    // Assert
    ExpectColourNear(result_pos_div_zero, Colour(1.0f, 1.0f, 1.0f, 1.0f));
    ExpectColourNear(result_zero_div_zero, Colour(0.0f, 0.0f, 0.0f, 0.0f));
}

// Scalar Assignment Operators

TEST(ColourTest, OperatorAddAssignScalar) {
    // Arrange
    Colour c(0.1f, 0.2f, 0.3f, 0.4f);
    float scalar = 0.1f;
    Colour expected(0.2f, 0.3f, 0.4f, 0.5f);

    // Act
    c += scalar;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorAddAssignScalar_Clamping) {
    // Arrange
    Colour c(0.8f, 0.9f, 0.95f, 1.0f);
    float scalar = 0.3f;
    Colour expected(1.0f, 1.0f, 1.0f, 1.0f);

    // Act
    c += scalar;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorSubtractAssignScalar) {
    // Arrange
    Colour c(0.5f, 0.6f, 0.7f, 0.8f);
    float scalar = 0.1f;
    Colour expected(0.4f, 0.5f, 0.6f, 0.7f);

    // Act
    c -= scalar;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorSubtractAssignScalar_Clamping) {
    // Arrange
    Colour c(0.1f, 0.2f, 0.0f, 0.05f);
    float scalar = 0.3f;
    Colour expected(0.0f, 0.0f, 0.0f, 0.0f);

    // Act
    c -= scalar;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorMultiplyAssignScalar) {
    // Arrange
    Colour c(0.2f, 0.3f, 0.4f, 0.5f);
    float scalar = 2.0f;
    Colour expected(0.4f, 0.6f, 0.8f, 1.0f);

    // Act
    c *= scalar;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorMultiplyAssignScalar_Clamping) {
    // Arrange
    Colour c(0.4f, 0.5f, 0.6f, 0.8f);
    float scalar = 3.0f;
    Colour expected(1.0f, 1.0f, 1.0f, 1.0f);

    // Act
    c *= scalar;

    // Assert
    ExpectColourNear(c, expected);
}


TEST(ColourTest, OperatorDivideAssignScalar) {
    // Arrange
    Colour c(0.4f, 0.6f, 0.8f, 1.0f);
    float scalar = 2.0f;
    Colour expected(0.2f, 0.3f, 0.4f, 0.5f);

    // Act
    c /= scalar;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorDivideAssignScalar_Clamping) {
    // Arrange
    Colour c(0.5f, 0.8f, 1.0f, 0.2f);
    float scalar = 0.1f;
    Colour expected(1.0f, 1.0f, 1.0f, 1.0f);

    // Act
    c /= scalar;

    // Assert
    ExpectColourNear(c, expected);
}

TEST(ColourTest, OperatorDivideAssignScalarByZero) {
    // Arrange
    Colour c_pos(0.5f, 0.5f, 0.5f, 0.5f);
    Colour c_zero_val(0.0f, 0.0f, 0.0f, 0.0f);
    float scalar_zero = 0.0f;

    Colour expected_pos_clamped(1.0f, 1.0f, 1.0f, 1.0f);
    Colour expected_zero_clamped(0.0f, 0.0f, 0.0f, 0.0f);

    // Act
    c_pos /= scalar_zero;
    c_zero_val /= scalar_zero;

    // Assert
    ExpectColourNear(c_pos, expected_pos_clamped);
    ExpectColourNear(c_zero_val, expected_zero_clamped);
}

// Static Functions

TEST(ColourTest, FromRGB) {
    // Arrange
    uint8_t r_byte = 255, g_byte = 128, b_byte = 0;
    Colour expected(1.0f, 128.0f / 255.0f, 0.0f, 1.0f);

    // Act
    Colour result = Colour::from_rgb(r_byte, g_byte, b_byte);

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, FromRGBA) {
    // Arrange
    uint8_t r_byte = 255, g_byte = 128, b_byte = 0, a_byte = 64;
    Colour expected(1.0f, 128.0f / 255.0f, 0.0f, 64.0f / 255.0f);

    // Act
    Colour result = Colour::from_rgba(r_byte, g_byte, b_byte, a_byte);

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, FromARGB_Opaque) {
    // Arrange
    uint32_t argb_val = 0xFF804020; // A = 0xFF (255), R = 0x80 (128), G = 0x40 (64), B = 0x20 (32)
    Colour expected(128.0f / 255.0f, 64.0f / 255.0f, 32.0f / 255.0f, 1.0f);

    // Act
    Colour result = Colour::from_argb(argb_val);

    // Assert
    ExpectColourNear(result, expected);
}

TEST(ColourTest, FromARGB_Transparent) {
    // Arrange
    uint32_t argb_val = 0xAAFF00CC; // A = 0xAA (170), R = 0xFF (255), G = 0x00 (0), B = 0xCC (204)
    Colour expected(1.0f, 0.0f, 204.0f / 255.0f, 170.0f / 255.0f);

    // Act
    Colour result = Colour::from_argb(argb_val);

    // Assert
    ExpectColourNear(result, expected);
}