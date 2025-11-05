#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

namespace MathLib {

class Statistics {
public:
    // 统计函数
    static double mean(const std::vector<double>& data);
    static double median(std::vector<double> data);
    static double variance(const std::vector<double>& data);
    static double standardDeviation(const std::vector<double>& data);
    static double min(const std::vector<double>& data);
    static double max(const std::vector<double>& data);
};

} // namespace MathLib

#endif // STATISTICS_H
