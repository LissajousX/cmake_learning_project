#include <iostream>
#include <iomanip>
#include "mathlib/calculator.h"
#include "mathlib/statistics.h"
#include "stringlib/stringutils.h"

using namespace std;

void printMenu() {
    cout << "\n========== 计算器应用程序 ==========" << endl;
    cout << "1. 基本运算 (加减乘除)" << endl;
    cout << "2. 高级运算 (幂运算、平方根)" << endl;
    cout << "3. 统计分析" << endl;
    cout << "4. 字符串处理演示" << endl;
    cout << "0. 退出" << endl;
    cout << "===================================" << endl;
    cout << "请选择: ";
}

void basicOperations() {
    double a, b;
    cout << "\n--- 基本运算 ---" << endl;
    cout << "输入第一个数: ";
    cin >> a;
    cout << "输入第二个数: ";
    cin >> b;
    
    cout << fixed << setprecision(2);
    cout << a << " + " << b << " = " << MathLib::Calculator::add(a, b) << endl;
    cout << a << " - " << b << " = " << MathLib::Calculator::subtract(a, b) << endl;
    cout << a << " * " << b << " = " << MathLib::Calculator::multiply(a, b) << endl;
    
    try {
        cout << a << " / " << b << " = " << MathLib::Calculator::divide(a, b) << endl;
    } catch (const exception& e) {
        cout << "错误: " << e.what() << endl;
    }
}

void advancedOperations() {
    double base, exponent;
    cout << "\n--- 高级运算 ---" << endl;
    cout << "输入底数: ";
    cin >> base;
    cout << "输入指数: ";
    cin >> exponent;
    
    cout << fixed << setprecision(2);
    cout << base << " ^ " << exponent << " = " << MathLib::Calculator::power(base, exponent) << endl;
    
    try {
        cout << "√" << base << " = " << MathLib::Calculator::squareRoot(base) << endl;
    } catch (const exception& e) {
        cout << "错误: " << e.what() << endl;
    }
}

void statisticsDemo() {
    cout << "\n--- 统计分析 ---" << endl;
    cout << "输入数据个数: ";
    int n;
    cin >> n;
    
    vector<double> data;
    cout << "输入 " << n << " 个数据:" << endl;
    for (int i = 0; i < n; ++i) {
        double value;
        cin >> value;
        data.push_back(value);
    }
    
    cout << fixed << setprecision(2);
    cout << "平均值: " << MathLib::Statistics::mean(data) << endl;
    cout << "中位数: " << MathLib::Statistics::median(data) << endl;
    cout << "方差: " << MathLib::Statistics::variance(data) << endl;
    cout << "标准差: " << MathLib::Statistics::standardDeviation(data) << endl;
    cout << "最小值: " << MathLib::Statistics::min(data) << endl;
    cout << "最大值: " << MathLib::Statistics::max(data) << endl;
}

void stringDemo() {
    cout << "\n--- 字符串处理演示 ---" << endl;
    cin.ignore(); // 清除输入缓冲
    
    string text;
    cout << "输入一个字符串: ";
    getline(cin, text);
    
    cout << "原始字符串: \"" << text << "\"" << endl;
    cout << "大写: \"" << StringLib::StringUtils::toUpper(text) << "\"" << endl;
    cout << "小写: \"" << StringLib::StringUtils::toLower(text) << "\"" << endl;
    cout << "去空格: \"" << StringLib::StringUtils::trim(text) << "\"" << endl;
    cout << "反转: \"" << StringLib::StringUtils::reverse(text) << "\"" << endl;
    
    auto words = StringLib::StringUtils::split(text, ' ');
    cout << "分词结果 (" << words.size() << " 个):" << endl;
    for (const auto& word : words) {
        cout << "  - \"" << word << "\"" << endl;
    }
}

int main() {
    cout << "欢迎使用 CMake 学习项目!" << endl;
    cout << "版本: 1.0.0" << endl;
    
    int choice;
    do {
        printMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                basicOperations();
                break;
            case 2:
                advancedOperations();
                break;
            case 3:
                statisticsDemo();
                break;
            case 4:
                stringDemo();
                break;
            case 0:
                cout << "感谢使用,再见!" << endl;
                break;
            default:
                cout << "无效选择,请重试!" << endl;
        }
    } while (choice != 0);
    
    return 0;
}
