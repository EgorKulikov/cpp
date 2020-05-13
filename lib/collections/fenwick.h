#pragma once

#include "../general.h"
#include "arr.h"

template <typename T>
class FenwickTree {
    arr<T> value;

    T get(int to) const {
        minim(to, int(value.size()) - 1);
        T result = 0;
        while (to >= 0) {
            result += value[to];
            to = (to & (to + 1)) - 1;
        }
        return result;
    }

public:
    FenwickTree(int size) {
        value = arr<T>(size, 0);
    }

    void add(int at, T val) {
        while (at < value.size()) {
            value[at] += val;
            at = at | (at + 1);
        }
    }

    T get(int from, int to) const {
        if (from >= to) {
            return 0;
        }
        return get(to - 1) - get(from - 1);
    }

    void clear() {
        fill(all(value), 0);
    }
};
