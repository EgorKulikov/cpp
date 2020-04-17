#pragma once

#include "../general.h"
#include "base_geometry.h"
#include "line.h"

class Circle {
public:
    const Point center;
    const DoubleType r;

    Circle(const Point &center, const DoubleType r) : center(center), r(r) {}
};

vector<Point> intersect(const Circle& c, const Line& l) {
    DoubleType dist = distance(l, c.center);
    if (dist > c.r + eps) {
        return vector<Point>(0);
    }
    auto perp = perpendicular(l, c.center);
    auto base = intersect(l, perp);
    if (dist > c.r - eps) {
        return vector<Point>(1, base);
    }
    DoubleType delta = sqrt(c.r * c.r - dist * dist);
    vector<Point> result;
    result.reserve(2);
    result.push_back(Point(base.x + perp.a * delta, base.y + perp.b * delta));
    result.push_back(Point(base.x - perp.a * delta, base.y - perp.b * delta));
    return result;
}

vector<Point> intersect(const Circle& c, const Circle& d) {
    DoubleType dist = distance(c.center, d.center);
    if (dist < eps) {
        return vector<Point>(0);
    }
    DoubleType a = 2 * (d.center.x - c.center.x);
    DoubleType b = 2 * (d.center.y - c.center.y);
    DoubleType f = d.r * d.r - c.r * c.r + c.center.x * c.center.x - d.center.x * d.center.x + c.center.y * c.center.y - d.center.y * d.center.y;
    auto l = getLine(a, b, f);
    return intersect(c, l);
}

vector<Point> touchingPoints(const Circle& c, const Point& p) {
    DoubleType dist = distance(c.center, p);
    if (dist < c.r - eps) {
        return vector<Point>(0);
    }
    if (dist < c.r + eps) {
        return vector<Point>(1, p);
    }
    Circle power(p, sqrt((dist - c.r) * (dist + c.r)));
    return intersect(c, power);
}

