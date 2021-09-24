#pragma once

#include "../general.h"

ll INFTY = 1000000000000000000ll;

struct infint {
    ll vl;

    infint(ll v) {
        if (v >= INFTY) {
            v = INFTY;
        }
        vl = v;
    }

    infint& operator +=(const infint& a) {
        if (INFTY - a.vl <= vl) {
            vl = INFTY;
        } else {
            vl += a.vl;
        }
        return *this;
    }

    infint& operator *=(const infint& a) {
        if (a.vl != 0 && INFTY / a.vl < vl) {
            vl = INFTY;
        } else {
            vl *= a.vl;
        }
        return *this;
    }
};

infint operator +(const infint& a, const infint& b) {
    infint res = a;
    res += b;
    return res;
}

infint operator *(const infint& a, const infint& b) {
    infint res = a;
    res *= b;
    return res;
}

bool operator <(const infint& a, const infint& b) {
    return a.vl < b.vl;
}

bool operator >(const infint& a, const infint& b) {
    return a.vl > b.vl;
}

bool operator <=(const infint& a, const infint& b) {
    return a.vl <= b.vl;
}

bool operator >=(const infint& a, const infint& b) {
    return a.vl >= b.vl;
}
