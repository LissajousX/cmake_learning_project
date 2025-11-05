#include "mathlib/statistics.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>

namespace MathLib {

double Statistics::mean(const std::vector<double>& data) {
    if (data.empty()) {
        throw std::invalid_argument("数据集不能为空");
    }
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double Statistics::median(std::vector<double> data) {
    if (data.empty()) {
        throw std::invalid_argument("数据集不能为空");
    }
    
    std::sort(data.begin(), data.end());
    size_t n = data.size();
    
    if (n % 2 == 0) {
        return (data[n/2 - 1] + data[n/2]) / 2.0;
    } else {
        return data[n/2];
    }
}

double Statistics::variance(const std::vector<double>& data) {
    if (data.empty()) {
        throw std::invalid_argument("数据集不能为空");
    }
    
    double avg = mean(data);
    double sum = 0.0;
    
    for (double value : data) {
        double diff = value - avg;
        sum += diff * diff;
    }
    
    return sum / data.size();
}

double Statistics::standardDeviation(const std::vector<double>& data) {
    return std::sqrt(variance(data));
}

double Statistics::min(const std::vector<double>& data) {
    if (data.empty()) {
        throw std::invalid_argument("数据集不能为空");
    }
    return *std::min_element(data.begin(), data.end());
}

double Statistics::max(const std::vector<double>& data) {
    if (data.empty()) {
        throw std::invalid_argument("数据集不能为空");
    }
    return *std::max_element(data.begin(), data.end());
}

} // namespace MathLib
