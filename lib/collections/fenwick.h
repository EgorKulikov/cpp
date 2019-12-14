#pragma once

#include "../general.h"
#include "arr.h"

class FenwickTree {
    arr<ll> value;

    ll get(int to) const {
        minim(to, int(value.size()) - 1);
        ll result = 0;
        while (to >= 0) {
            result += value[to];
            to = (to & (to + 1)) - 1;
        }
        return result;
    }

public:
    FenwickTree(int size) {
        value = arr<ll>(size);
    }

    void add(int at, ll val) {
        while (at < value.size()) {
            value[at] += val;
            at = at | (at + 1);
        }
    }

    ll get(int from, int to) const {
        if (from >= to) {
            return 0;
        }
        return get(to - 1) - get(from - 1);
    }
};
