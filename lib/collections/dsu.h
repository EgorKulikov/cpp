#pragma once

#include "../general.h"
#include "../algo.h"
#include "arr.h"

class DSU {
    mutable arri id;
    arri sz;
    int count;

public:
    DSU(int n) {
        id = createOrder(n);
        sz = arri(n, 1);
        count = n;
    }
    int get(int i) const {
        if (id[i] == i) {
            return i;
        }
        return id[i] = get(id[i]);
    }
    int operator[](int i) const { return get(i); }
    int size(int i) const { return sz[get(i)]; }
    int setCount() const { return count; }
    bool join(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) {
            return false;
        }
        sz[a] += sz[b];
        sz[b] = 0;
        id[b] = a;
        count--;
        return true;
    }
    void reset() {
        count = sz.size();
        for (int i : range(count)) {
            id[i] = i;
            sz[i] = 1;
        }
    }
};
