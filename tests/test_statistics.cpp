#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include "mathlib/statistics.h"

using namespace MathLib;

void testMean() {
    std::vector<double> data = {1, 2, 3, 4, 5};
    assert(Statistics::mean(data) == 3.0);
    
    std::vector<double> data2 = {10, 20, 30};
    assert(Statistics::mean(data2) == 20.0);
    
    std::cout << "✓ 平均值测试通过" << std::endl;
}

void testMedian() {
    std::vector<double> data1 = {1, 2, 3, 4, 5};
    assert(Statistics::median(data1) == 3.0);
    
    std::vector<double> data2 = {1, 2, 3, 4};
    assert(Statistics::median(data2) == 2.5);
    
    std::vector<double> data3 = {5, 1, 3};
    assert(Statistics::median(data3) == 3.0);
    
    std::cout << "✓ 中位数测试通过" << std::endl;
}

void testVariance() {
    std::vector<double> data = {2, 4, 4, 4, 5, 5, 7, 9};
    double var = Statistics::variance(data);
    assert(std::abs(var - 4.0) < 0.0001);
    
    std::cout << "✓ 方差测试通过" << std::endl;
}

void testStandardDeviation() {
    std::vector<double> data = {2, 4, 4, 4, 5, 5, 7, 9};
    double sd = Statistics::standardDeviation(data);
    assert(std::abs(sd - 2.0) < 0.0001);
    
    std::cout << "✓ 标准差测试通过" << std::endl;
}

void testMinMax() {
    std::vector<double> data = {3, 1, 4, 1, 5, 9, 2, 6};
    assert(Statistics::min(data) == 1.0);
    assert(Statistics::max(data) == 9.0);
    
    std::cout << "✓ 最小值/最大值测试通过" << std::endl;
}

int main() {
    std::cout << "运行 Statistics 测试..." << std::endl;
    
    testMean();
    testMedian();
    testVariance();
    testStandardDeviation();
    testMinMax();
    
    std::cout << "\n所有 Statistics 测试通过! ✓" << std::endl;
    return 0;
}
