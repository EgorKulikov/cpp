#pragma once

#include "general.h"
#include "collections/arr.h"
#include "range/range.h"

double eps = 1e-9;

using DoubleType = double;

const DoubleType PI = atan(DoubleType(1)) * 4;

class Point {
public:
    DoubleType x;
    DoubleType y;

    Point() {}
    Point(const DoubleType x, const DoubleType y) : x(x), y(y) {}
};

class Line {
public:
    DoubleType a;
    DoubleType b;
    DoubleType c;

    Line() : Line(0, 0, 0) {}
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

DoubleType canonicalAngle(DoubleType angle) {
    while (angle > PI) {
        angle -= 2 * PI;
    }
    while (angle < -PI) {
        angle += 2 * PI;
    }
    return angle;
}

class Polygon {
    mutable double ar = -1;
    mutable arr<Segment> sid;

public:
    arr<Point> vert;

    Polygon() {}
    Polygon(const arr<Point> &vert) : vert(vert) {}
    double area() const {
        if (ar == -1) {
            ar = 0;
            for (int i : range(vert.size())) {
                const Point& a = vert[i];
                const Point& b = vert[(i + 1) % vert.size()];
                ar += (a.x - b.x) * (a.y + b.y);
            }
            ar = abs(ar) / 2;
        }
        return ar;
    }

    bool inside(const Point& p, bool strict = false) const {
        bool onSide = false;
        for (const auto& s : sides()) {
            if (s.contains(p)) {
                onSide = true;
                break;
            }
        }
        if (onSide) {
            return !strict;
        }
        double totalAngle = canonicalAngle(atan2(vert[0].y - p.y, vert[0].x - p.x) - atan2(vert[vert.size() - 1].y - p.y, vert[vert.size() - 1].x - p.x));
        for (int i = 1; i < vert.size(); i++) {
            totalAngle += canonicalAngle(atan2(vert[i].y - p.y, vert[i].x - p.x) - atan2(vert[i - 1].y - p.y, vert[i - 1].x - p.x));
        }
        return abs(totalAngle) > PI;
    }

    const arr<Segment>& sides() const {
        if (sid.size() == 0) {
            sid = arr<Segment>(vert.size());
            for (int i : range(vert.size())) {
                sid[i] = Segment(vert[i], vert[(i + 1) % vert.size()]);
            }
        }
        return sid;
    }
};
