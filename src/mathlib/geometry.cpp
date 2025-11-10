#include "mathlib/geometry.h"
#include <cmath>

namespace MathLib {
double Geometry::circleArea(double radius) {
    return M_PI * radius * radius;
}

double Geometry::rectangleArea(double width, double height) {
    return width * height;
}
}