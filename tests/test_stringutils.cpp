#include <iostream>
#include <cassert>
#include "stringlib/stringutils.h"

using namespace StringLib;

void testToUpper() {
    assert(StringUtils::toUpper("hello") == "HELLO");
    assert(StringUtils::toUpper("Hello World") == "HELLO WORLD");
    assert(StringUtils::toUpper("123abc") == "123ABC");
    std::cout << "✓ 大写转换测试通过" << std::endl;
}

void testToLower() {
    assert(StringUtils::toLower("HELLO") == "hello");
    assert(StringUtils::toLower("Hello World") == "hello world");
    assert(StringUtils::toLower("ABC123") == "abc123");
    std::cout << "✓ 小写转换测试通过" << std::endl;
}

void testTrim() {
    assert(StringUtils::trim("  hello  ") == "hello");
    assert(StringUtils::trim("\t\nworld\r\n") == "world");
    assert(StringUtils::trim("no spaces") == "no spaces");
    assert(StringUtils::trim("   ") == "");
    std::cout << "✓ 去空格测试通过" << std::endl;
}

void testSplit() {
    auto result1 = StringUtils::split("a,b,c", ',');
    assert(result1.size() == 3);
    assert(result1[0] == "a");
    assert(result1[1] == "b");
    assert(result1[2] == "c");
    
    auto result2 = StringUtils::split("hello world test", ' ');
    assert(result2.size() == 3);
    assert(result2[0] == "hello");
    
    std::cout << "✓ 分割测试通过" << std::endl;
}

void testJoin() {
    std::vector<std::string> words = {"hello", "world", "test"};
    assert(StringUtils::join(words, " ") == "hello world test");
    assert(StringUtils::join(words, ",") == "hello,world,test");
    
    std::vector<std::string> empty;
    assert(StringUtils::join(empty, ",") == "");
    
    std::cout << "✓ 连接测试通过" << std::endl;
}

void testStartsWith() {
    assert(StringUtils::startsWith("hello world", "hello") == true);
    assert(StringUtils::startsWith("hello world", "world") == false);
    assert(StringUtils::startsWith("test", "testing") == false);
    std::cout << "✓ 前缀测试通过" << std::endl;
}

void testEndsWith() {
    assert(StringUtils::endsWith("hello world", "world") == true);
    assert(StringUtils::endsWith("hello world", "hello") == false);
    assert(StringUtils::endsWith("test", "testing") == false);
    std::cout << "✓ 后缀测试通过" << std::endl;
}

void testReverse() {
    assert(StringUtils::reverse("hello") == "olleh");
    assert(StringUtils::reverse("12345") == "54321");
    assert(StringUtils::reverse("a") == "a");
    assert(StringUtils::reverse("") == "");
    std::cout << "✓ 反转测试通过" << std::endl;
}

int main() {
    std::cout << "运行 StringUtils 测试..." << std::endl;
    
    testToUpper();
    testToLower();
    testTrim();
    testSplit();
    testJoin();
    testStartsWith();
    testEndsWith();
    testReverse();
    
    std::cout << "\n所有 StringUtils 测试通过! ✓" << std::endl;
    return 0;
}
