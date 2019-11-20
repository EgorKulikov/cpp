#ifndef CPP_GEOMETRY_H
#define CPP_GEOMETRY_H

#include "general.h"

double EPS = 1e-9;

template <typename T>
class Point {
public:
    const T x;
    const T y;

    Point() : x(0), y(0) {}
    Point(const T x, const T y) : x(x), y(y) {}
};

template <typename T>
class Line {
public:
    const T a;
    const T b;
    const T c;

    Line(const T a, const T b, const T c) : a(a), b(b), c(c) {}
};

template <typename T>
class Circle {
public:
    const Point<T> center;
    const T r;

    Circle(const Point<T> &center, const T r) : center(center), r(r) {}
};

template <typename T>
class Segment {
public:
    const Point<T> a, b;
    const Line<T> l;

    Segment(const Point<T> &a, const Point<T> &b) : a(a), b(b), l(line(a, b)) {}

    bool contains(const Point<T>& c) {
        return distance(l, c) < EPS && c.x > min(a.x, b.x) - EPS && c.x < max(a.x, b.x) + EPS &&
            c.y > min(a.y, b.y) - EPS && c.y < max(a.y, b.y) + EPS;
    }

    T length() {
        return distance(a, b);
    }
};

template <typename T>
Line<T> getLine(T a, T b, T c) {
    T g = hypot(a, b);
    return Line<T>(a / g, b / g, c / g);
}

template <typename T>
Line<T> line(const Point<T>& p, const Point<T>& q) {
    T a = p.y - q.y;
    T b = q.x - p.x;
    T c = -a * p.x - b * p.y;
    return getLine(a, b, c);
}

template <typename T>
T distance(const Line<T>& l, const Point<T>& p) {
    return abs(l.a * p.x + l.b * p.y + l.c);
}

template <typename T>
Line<T> perpendicular(const Line<T>& l, const Point<T>& p) {
    return Line<T>(-l.b, l.a, p.x * l.b - p.y * l.a);
}

template <typename T>
Point<T> intersect(const Line<T>& a, const Line<T>& b) {
    T det = a.b * b.a - a.a * b.b;
    return Point<T>((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
}

template <typename T>
vector<Point<T> > intersect(const Circle<T>& c, const Line<T>& l) {
    T dist = distance(l, c.center);
    if (dist > c.r + EPS) {
        return vector<Point<T> >(0);
    }
    auto perp = perpendicular(l, c.center);
    auto base = intersect(l, perp);
    if (dist > c.r - EPS) {
        return vector<Point<T> >(1, base);
    }
    T delta = sqrt(c.r * c.r - dist * dist);
    vector<Point<T> > result;
    result.reserve(2);
    result.push_back(Point<T>(base.x + perp.a * delta, base.y + perp.b * delta));
    result.push_back(Point<T>(base.x - perp.a * delta, base.y - perp.b * delta));
    return result;
}

template <typename T>
T distance(const Point<T>& a, const Point<T>& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

template <typename T>
vector<Point<T> > intersect(const Circle<T>& c, const Circle<T>& d) {
    T dist = distance(c, d);
    if (dist < EPS) {
        return vector<Point<T> >(0);
    }
    T a = 2 * (d.center.x - c.center.x);
    T b = 2 * (d.center.y - c.center.y);
    T f = d.r * d.r - c.r * c.r + c.center.c * c.center.x - d.center.x * d.center.x + c.center.y * c.center.y - d.center.y * d.center.y;
    auto l = getLine(a, b, f);
    return intersect(c, l);
}

template <typename T>
vector<Point<T> > touchingPoints(const Circle<T>& c, const Point<T>& p) {
    T dist = distance(c.center, p);
    if (dist < c.r - EPS) {
        return vector<Point<T> >(0);
    }
    if (dist < c.r + EPS) {
        return vector<Point<T> >(1, p);
    }
    Circle<T> power(p, sqrt((dist - c.r) * (dist + c.r)));
    return intersect(c, power);
}

#endif //CPP_GEOMETRY_H
