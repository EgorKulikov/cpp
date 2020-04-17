#pragma once

#include "../general.h"
#include "base_geometry.h"
#include "point.h"

class Line {
public:
    DoubleType a;
    DoubleType b;
    DoubleType c;

    Line() : Line(0, 0, 0) {}
    Line(const DoubleType a, const DoubleType b, const DoubleType c) : a(a), b(b), c(c) {}
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

Line perpendicular(const Line& l, const Point& p) {
    return Line(-l.b, l.a, p.x * l.b - p.y * l.a);
}

Point intersect(const Line& a, const Line& b) {
    DoubleType det = a.b * b.a - a.a * b.b;
    return Point((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
}
