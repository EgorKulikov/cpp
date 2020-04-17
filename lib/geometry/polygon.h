#pragma once

#include "../general.h"
#include "../collections/arr.h"
#include "segment.h"

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
