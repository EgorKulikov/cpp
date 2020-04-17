#pragma once

#include "../general.h"
#include "line.h"

class Segment {
    mutable Line l;
public:
    Point a, b;

    Segment() {}
    Segment(const Point &a, const Point &b) : a(a), b(b) {}

    bool contains(const Point& c) const {
        return distance(line(), c) < eps && c.x > min(a.x, b.x) - eps && c.x < max(a.x, b.x) + eps &&
               c.y > min(a.y, b.y) - eps && c.y < max(a.y, b.y) + eps;
    }

    const Line& line() const {
        if (l.a == 0 && l.b == 0) {
            l = ::line(a, b);
        }
        return l;
    }

    DoubleType length() const {
        return distance(a, b);
    }
};

