#pragma once

#include "../general.h"

ll INFTY = 1000000000000000000ll;

struct infint {
    ll val;

    infint(ll v) {
        if (v >= INFTY) {
            v = INFTY;
        }
        val = v;
    }

    infint& operator +=(const infint& a) {
        if (INFTY - a.val <= val) {
            val = INFTY;
        } else {
            val += a.val;
        }
        return *this;
    }

    infint& operator *=(const infint& a) {
        if (a.val != 0 && INFTY / a.val <= val) {
            val = INFTY;
        } else {
            val *= a.val;
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
    return a.val < b.val;
}

bool operator >(const infint& a, const infint& b) {
    return a.val > b.val;
}

bool operator <=(const infint& a, const infint& b) {
    return a.val <= b.val;
}

bool operator >=(const infint& a, const infint& b) {
    return a.val >= b.val;
}
