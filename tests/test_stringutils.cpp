#include <gtest/gtest.h>
#include "stringlib/stringutils.h"

using StringLib::StringUtils;

TEST(StringUtilsTest, ToUpper)
{
    EXPECT_EQ(StringUtils::toUpper("hello"), "HELLO");
    EXPECT_EQ(StringUtils::toUpper("Hello World"), "HELLO WORLD");
    EXPECT_EQ(StringUtils::toUpper("123abc"), "123ABC");
}

TEST(StringUtilsTest, ToLower)
{
    EXPECT_EQ(StringUtils::toLower("HELLO"), "hello");
    EXPECT_EQ(StringUtils::toLower("Hello World"), "hello world");
    EXPECT_EQ(StringUtils::toLower("ABC123"), "abc123");
}

TEST(StringUtilsTest, Trim)
{
    EXPECT_EQ(StringUtils::trim("  hello  "), "hello");
    EXPECT_EQ(StringUtils::trim("\t\nworld\r\n"), "world");
    EXPECT_EQ(StringUtils::trim("no spaces"), "no spaces");
    EXPECT_EQ(StringUtils::trim("   "), "");
}

TEST(StringUtilsTest, Split)
{
    auto result1 = StringUtils::split("a,b,c", ',');
    ASSERT_EQ(result1.size(), 3u);
    EXPECT_EQ(result1[0], "a");
    EXPECT_EQ(result1[1], "b");
    EXPECT_EQ(result1[2], "c");

    auto result2 = StringUtils::split("hello world test", ' ');
    ASSERT_EQ(result2.size(), 3u);
    EXPECT_EQ(result2[0], "hello");
    EXPECT_EQ(result2[1], "world");
    EXPECT_EQ(result2[2], "test");
}

TEST(StringUtilsTest, Join)
{
    const std::vector<std::string> words = {"hello", "world", "test"};
    EXPECT_EQ(StringUtils::join(words, " "), "hello world test");
    EXPECT_EQ(StringUtils::join(words, ","), "hello,world,test");

    const std::vector<std::string> empty;
    EXPECT_EQ(StringUtils::join(empty, ","), "");
}

TEST(StringUtilsTest, StartsWith)
{
    EXPECT_TRUE(StringUtils::startsWith("hello world", "hello"));
    EXPECT_FALSE(StringUtils::startsWith("hello world", "world"));
    EXPECT_FALSE(StringUtils::startsWith("test", "testing"));
}

TEST(StringUtilsTest, EndsWith)
{
    EXPECT_TRUE(StringUtils::endsWith("hello world", "world"));
    EXPECT_FALSE(StringUtils::endsWith("hello world", "hello"));
    EXPECT_FALSE(StringUtils::endsWith("test", "testing"));
}

TEST(StringUtilsTest, Reverse)
{
    EXPECT_EQ(StringUtils::reverse("hello"), "olleh");
    EXPECT_EQ(StringUtils::reverse("12345"), "54321");
    EXPECT_EQ(StringUtils::reverse("a"), "a");
    EXPECT_EQ(StringUtils::reverse(""), "");
}

class StringUtilsFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        words = {"foo", "bar", "baz"};
    }

    std::vector<std::string> words;
};

TEST_F(StringUtilsFixture, JoinWithFixture)
{
    EXPECT_EQ(StringUtils::join(words, "-"), "foo-bar-baz");

    words.push_back("qux");
    EXPECT_EQ(StringUtils::join(words, ","), "foo,bar,baz,qux");
}
