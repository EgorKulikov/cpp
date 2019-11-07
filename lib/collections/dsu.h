//
// Created by egor on 31.10.2019.
//

#ifndef JHELPER_EXAMPLE_PROJECT_DSU_H
#define JHELPER_EXAMPLE_PROJECT_DSU_H

#include "../general.h"
#include "../algo.h"

class DSU {
private:
    vi id;
    vi size;
    int setCount;

public:
    DSU(int n);
    int get(int i);
    int getSize(int i) { return size[get(i)]; }
    int getSetCount() { return setCount; }
    bool join(int a, int b);
};

DSU::DSU(int n) {
    id = createOrder(n);
    size = vi(n, 1);
    setCount = n;
}

int DSU::get(int i) {
    if (id[i] == i) {
        return i;
    }
    return id[i] = get(id[i]);
}

bool DSU::join(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) {
        return false;
    }
    size[a] += size[b];
    size[b] = 0;
    id[b] = a;
    setCount--;
    return true;
}

#endif //JHELPER_EXAMPLE_PROJECT_DSU_H
