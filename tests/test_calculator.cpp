#include <gtest/gtest.h>
#include <cmath>
#include "mathlib/calculator.h"

using MathLib::Calculator;

TEST(CalculatorTest, Add)
{
    EXPECT_EQ(Calculator::add(2, 3), 5);
    EXPECT_EQ(Calculator::add(-1, 1), 0);
    EXPECT_EQ(Calculator::add(0, 0), 0);
}

TEST(CalculatorTest, Subtract)
{
    EXPECT_EQ(Calculator::subtract(5, 3), 2);
    EXPECT_EQ(Calculator::subtract(0, 5), -5);
    EXPECT_EQ(Calculator::subtract(10, 10), 0);
}

TEST(CalculatorTest, Multiply)
{
    EXPECT_EQ(Calculator::multiply(3, 4), 12);
    EXPECT_EQ(Calculator::multiply(-2, 3), -6);
    EXPECT_EQ(Calculator::multiply(0, 100), 0);
}

TEST(CalculatorTest, Divide)
{
    EXPECT_DOUBLE_EQ(Calculator::divide(10, 2), 5.0);
    EXPECT_DOUBLE_EQ(Calculator::divide(7, 2), 3.5);
    EXPECT_THROW(Calculator::divide(10, 0), std::invalid_argument);
}

TEST(CalculatorTest, Power)
{
    EXPECT_EQ(Calculator::power(2, 3), 8);
    EXPECT_EQ(Calculator::power(5, 0), 1);
    EXPECT_NEAR(Calculator::power(2, -1), 0.5, 1e-4);
}

TEST(CalculatorTest, SquareRoot)
{
    EXPECT_EQ(Calculator::squareRoot(4), 2);
    EXPECT_EQ(Calculator::squareRoot(9), 3);
    EXPECT_EQ(Calculator::squareRoot(0), 0);
    EXPECT_THROW(Calculator::squareRoot(-1), std::invalid_argument);
}
