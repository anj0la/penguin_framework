#include "utils/string.hpp"
#include <gtest/gtest.h>

// Constructor Tests

TEST(StringConstructorTest, DefaultConstructor) {
	String str;
	EXPECT_STREQ(str.c_str(), ""); // the buf is a nullptr, but the c_str should return "" as buf is null
}

TEST(StringConstructorTest, RegularConstructor) {
	String str("Hello world!");
	EXPECT_STREQ(str.c_str(), "Hello world!");
}

TEST(StringConstructorTest, CopyConstructor) {
	String original("Copied string!");
	String copy(original);
	EXPECT_STREQ(copy.c_str(), "Copied string!");
}

TEST(StringConstructorTest, MoveConstructor) {
	String moved_from("Temp string!");
	String moved_to(std::move(moved_from));
	EXPECT_STREQ(moved_to.c_str(), "Temp string!");
	EXPECT_STREQ(moved_from.c_str(), ""); // moved-from string should be empty
}

TEST(StringAssignmentTest, CopyAssignment) {
	String str1("Hello assignment!");
	String str2;
	str2 = str1;
	EXPECT_STREQ(str2.c_str(), "Hello assignment!");
}

TEST(StringAssignmentTest, MoveAssignment) {
	String str1("Move me!");
	String str2;
	str2 = std::move(str1);
	EXPECT_STREQ(str2.c_str(), "Move me!");
	EXPECT_STREQ(str1.c_str(), "");
}

// Other tests

TEST(StringStaticTest, LengthFunction) {
	EXPECT_EQ(String::length("abcd"), 4);
	EXPECT_EQ(String::length(""), 0);
}

TEST(StringStaticTest, CompareFunction) {
	EXPECT_TRUE(String::compare("abc", "abc"));
	EXPECT_FALSE(String::compare("abc", "ab"));
	EXPECT_FALSE(String::compare("abc", "abcd"));
	EXPECT_FALSE(String::compare("abc", "xyz"));
}

TEST(StringAssignmentTest, SelfAssignment) {
	String str("Hello!");
	str = str;
	EXPECT_STREQ(str.c_str(), "Hello!");
}
