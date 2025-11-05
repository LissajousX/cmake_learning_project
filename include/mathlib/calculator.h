#ifndef CALCULATOR_H
#define CALCULATOR_H

namespace MathLib {

class Calculator {
public:
    // 基本运算
    static double add(double a, double b);
    static double subtract(double a, double b);
    static double multiply(double a, double b);
    static double divide(double a, double b);
    
    // 高级运算
    static double power(double base, double exponent);
    static double squareRoot(double value);
};

} // namespace MathLib

#endif // CALCULATOR_H
