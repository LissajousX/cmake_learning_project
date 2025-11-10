#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "mathlib/statistics.h"

using MathLib::Statistics;

TEST(StatisticsTest, Mean)
{
    EXPECT_DOUBLE_EQ(Statistics::mean({1, 2, 3, 4, 5}), 3.0);
    EXPECT_DOUBLE_EQ(Statistics::mean({10, 20, 30}), 20.0);
}

TEST(StatisticsTest, Median)
{
    EXPECT_DOUBLE_EQ(Statistics::median({1, 2, 3, 4, 5}), 3.0);
    EXPECT_DOUBLE_EQ(Statistics::median({1, 2, 3, 4}), 2.5);
    EXPECT_DOUBLE_EQ(Statistics::median({5, 1, 3}), 3.0);
}

TEST(StatisticsTest, Variance)
{
    EXPECT_NEAR(Statistics::variance({2, 4, 4, 4, 5, 5, 7, 9}), 4.0, 1e-4);
}

TEST(StatisticsTest, StandardDeviation)
{
    EXPECT_NEAR(Statistics::standardDeviation({2, 4, 4, 4, 5, 5, 7, 9}), 2.0, 1e-4);
}

TEST(StatisticsTest, MinMax)
{
    const std::vector<double> data = {3, 1, 4, 1, 5, 9, 2, 6};
    EXPECT_DOUBLE_EQ(Statistics::min(data), 1.0);
    EXPECT_DOUBLE_EQ(Statistics::max(data), 9.0);
}
