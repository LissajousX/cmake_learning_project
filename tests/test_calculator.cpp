#include <iostream>
#include <cassert>
#include <cmath>
#include "mathlib/calculator.h"

using namespace MathLib;

void testAdd() {
    assert(Calculator::add(2, 3) == 5);
    assert(Calculator::add(-1, 1) == 0);
    assert(Calculator::add(0, 0) == 0);
    std::cout << "✓ 加法测试通过" << std::endl;
}

void testSubtract() {
    assert(Calculator::subtract(5, 3) == 2);
    assert(Calculator::subtract(0, 5) == -5);
    assert(Calculator::subtract(10, 10) == 0);
    std::cout << "✓ 减法测试通过" << std::endl;
}

void testMultiply() {
    assert(Calculator::multiply(3, 4) == 12);
    assert(Calculator::multiply(-2, 3) == -6);
    assert(Calculator::multiply(0, 100) == 0);
    std::cout << "✓ 乘法测试通过" << std::endl;
}

void testDivide() {
    assert(Calculator::divide(10, 2) == 5);
    assert(Calculator::divide(7, 2) == 3.5);
    
    try {
        Calculator::divide(10, 0);
        assert(false && "应该抛出异常");
    } catch (const std::invalid_argument&) {
        // 预期的异常
    }
    
    std::cout << "✓ 除法测试通过" << std::endl;
}

void testPower() {
    assert(Calculator::power(2, 3) == 8);
    assert(Calculator::power(5, 0) == 1);
    assert(std::abs(Calculator::power(2, -1) - 0.5) < 0.0001);
    std::cout << "✓ 幂运算测试通过" << std::endl;
}

void testSquareRoot() {
    assert(Calculator::squareRoot(4) == 2);
    assert(Calculator::squareRoot(9) == 3);
    assert(Calculator::squareRoot(0) == 0);
    
    try {
        Calculator::squareRoot(-1);
        assert(false && "应该抛出异常");
    } catch (const std::invalid_argument&) {
        // 预期的异常
    }
    
    std::cout << "✓ 平方根测试通过" << std::endl;
}

int main() {
    std::cout << "运行 Calculator 测试..." << std::endl;
    
    testAdd();
    testSubtract();
    testMultiply();
    testDivide();
    testPower();
    testSquareRoot();
    
    std::cout << "\n所有 Calculator 测试通过! ✓" << std::endl;
    return 0;
}
