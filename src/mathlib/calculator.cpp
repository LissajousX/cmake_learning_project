#include "mathlib/calculator.h"
#include <cmath>
#include <stdexcept>

namespace MathLib {

double Calculator::add(double a, double b) {
    return a + b;
}

double Calculator::subtract(double a, double b) {
    return a - b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

double Calculator::divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("除数不能为零");
    }
    return a / b;
}

double Calculator::power(double base, double exponent) {
    return std::pow(base, exponent);
}

double Calculator::squareRoot(double value) {
    if (value < 0.0) {
        throw std::invalid_argument("不能对负数求平方根");
    }
    return std::sqrt(value);
}

} // namespace MathLib
