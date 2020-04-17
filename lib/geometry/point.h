#pragma once

#include "../general.h"
#include "base_geometry.h"

class Point {
public:
    DoubleType x;
    DoubleType y;

    Point() {}
    Point(const DoubleType x, const DoubleType y) : x(x), y(y) {}
};

DoubleType distance(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}
