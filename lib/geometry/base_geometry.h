#pragma once

#include "../general.h"

using DoubleType = long double;

DoubleType eps = 1e-9;

const DoubleType PI = atan(DoubleType(1)) * 4;

DoubleType canonicalAngle(DoubleType angle) {
    while (angle > PI) {
        angle -= 2 * PI;
    }
    while (angle < -PI) {
        angle += 2 * PI;
    }
    return angle;
}
