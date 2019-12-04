#pragma once

#include "../general.h"
#include "../algo.h"

class VectorDSU {
private:
    vi id;
    vector<vi> parts;
    int setCount;

public:
    VectorDSU(int n);
    int get(int i) { return id[i]; }
    int operator[](int i) { return id[i]; }
    int getSize(int i) { return parts[id[i]].size() + 1; }
    int getSetCount() { return setCount; }
    bool join(int a, int b);
};

VectorDSU::VectorDSU(int n) {
    id = createOrder(n);
    parts = vector<vi>(n);
    setCount = n;
}

bool VectorDSU::join(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) {
        return false;
    }
    if (getSize(a) < getSize(b)) {
        swap(a, b);
    }
    for (int i : parts[b]) {
        parts[a].push_back(i);
        id[i] = a;
    }
    parts[a].push_back(b);
    id[b] = a;
    parts[b].clear();
    setCount--;
    return true;
}
