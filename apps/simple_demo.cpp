#include <iostream>
#include <nlohmann/json.hpp>
#include "mathlib/calculator.h"
#include "stringlib/stringutils.h"

int main() {
    std::cout << "=== 简单演示程序 ===" << std::endl;
    
    // 数学运算演示
    std::cout << "\n数学运算:" << std::endl;
    std::cout << "10 + 5 = " << MathLib::Calculator::add(10, 5) << std::endl;
    std::cout << "10 - 5 = " << MathLib::Calculator::subtract(10, 5) << std::endl;
    std::cout << "10 * 5 = " << MathLib::Calculator::multiply(10, 5) << std::endl;
    std::cout << "10 / 5 = " << MathLib::Calculator::divide(10, 5) << std::endl;
    std::cout << "2 ^ 8 = " << MathLib::Calculator::power(2, 8) << std::endl;
    std::cout << "√16 = " << MathLib::Calculator::squareRoot(16) << std::endl;
    
    // 字符串处理演示
    std::cout << "\n字符串处理:" << std::endl;
    std::string text = "Hello CMake World";
    std::cout << "原始: " << text << std::endl;
    std::cout << "大写: " << StringLib::StringUtils::toUpper(text) << std::endl;
    std::cout << "小写: " << StringLib::StringUtils::toLower(text) << std::endl;
    std::cout << "反转: " << StringLib::StringUtils::reverse(text) << std::endl;
    
    // JSON 演示
    std::cout << "\nJSON 输出:" << std::endl;
    nlohmann::json result = {
        {"math", {
            {"add", MathLib::Calculator::add(3, 4)},
            {"power", MathLib::Calculator::power(2, 5)}
        }},
        {"string", {
            {"original", text},
            {"upper", StringLib::StringUtils::toUpper(text)}
        }}
    };

    std::cout << result.dump(4) << std::endl;

    return 0;
}
