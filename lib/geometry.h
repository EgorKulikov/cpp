#pragma once

#include "general.h"

double eps = 1e-9;

using DoubleType = double;

class Point {
public:
    const DoubleType x;
    const DoubleType y;

    Point() : x(0), y(0) {}
    Point(const DoubleType x, const DoubleType y) : x(x), y(y) {}
};

class Line {
public:
    const DoubleType a;
    const DoubleType b;
    const DoubleType c;

    Line(const DoubleType a, const DoubleType b, const DoubleType c) : a(a), b(b), c(c) {}
};

class Circle {
public:
    const Point center;
    const DoubleType r;

    Circle(const Point &center, const DoubleType r) : center(center), r(r) {}
};

Line getLine(DoubleType a, DoubleType b, DoubleType c) {
    DoubleType g = hypot(a, b);
    return Line(a / g, b / g, c / g);
}

Line line(const Point& p, const Point& q) {
    DoubleType a = p.y - q.y;
    DoubleType b = q.x - p.x;
    DoubleType c = -a * p.x - b * p.y;
    return getLine(a, b, c);
}

DoubleType distance(const Line& l, const Point& p) {
    return abs(l.a * p.x + l.b * p.y + l.c);
}

DoubleType distance(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

class Segment {
public:
    const Point a, b;
    const Line l;

    Segment(const Point &a, const Point &b) : a(a), b(b), l(line(a, b)) {}

    bool contains(const Point& c) {
        return distance(l, c) < eps && c.x > min(a.x, b.x) - eps && c.x < max(a.x, b.x) + eps &&
            c.y > min(a.y, b.y) - eps && c.y < max(a.y, b.y) + eps;
    }

    DoubleType length() {
        return distance(a, b);
    }
};

Line perpendicular(const Line& l, const Point& p) {
    return Line(-l.b, l.a, p.x * l.b - p.y * l.a);
}

Point intersect(const Line& a, const Line& b) {
    DoubleType det = a.b * b.a - a.a * b.b;
    return Point((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
}

vec<Point> intersect(const Circle& c, const Line& l) {
    DoubleType dist = distance(l, c.center);
    if (dist > c.r + eps) {
        return vec<Point>(0);
    }
    auto perp = perpendicular(l, c.center);
    auto base = intersect(l, perp);
    if (dist > c.r - eps) {
        return vec<Point>(1, base);
    }
    DoubleType delta = sqrt(c.r * c.r - dist * dist);
    vec<Point> result;
    result.reserve(2);
    result.push_back(Point(base.x + perp.a * delta, base.y + perp.b * delta));
    result.push_back(Point(base.x - perp.a * delta, base.y - perp.b * delta));
    return result;
}

vec<Point> intersect(const Circle& c, const Circle& d) {
    DoubleType dist = distance(c.center, d.center);
    if (dist < eps) {
        return vec<Point>(0);
    }
    DoubleType a = 2 * (d.center.x - c.center.x);
    DoubleType b = 2 * (d.center.y - c.center.y);
    DoubleType f = d.r * d.r - c.r * c.r + c.center.x * c.center.x - d.center.x * d.center.x + c.center.y * c.center.y - d.center.y * d.center.y;
    auto l = getLine(a, b, f);
    return intersect(c, l);
}

vec<Point> touchingPoints(const Circle& c, const Point& p) {
    DoubleType dist = distance(c.center, p);
    if (dist < c.r - eps) {
        return vec<Point>(0);
    }
    if (dist < c.r + eps) {
        return vec<Point>(1, p);
    }
    Circle power(p, sqrt((dist - c.r) * (dist + c.r)));
    return intersect(c, power);
}
