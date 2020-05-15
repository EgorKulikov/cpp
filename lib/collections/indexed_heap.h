#pragma once

#include "../general.h"
#include "arr.h"

class IndexedHeap {
    arri heap;
    arri pos;
    int sz = 0;
    function<bool(int, int)> cmp;

    void swap(int i, int j) {
        std::swap(heap[i], heap[j]);
        std::swap(pos[heap[i]], pos[heap[j]]);
    }

public:
    IndexedHeap(int capacity = 0, const function<bool(int, int)> cmp = less<int>()) : heap(arri(capacity)), pos(arri(capacity, -1)), cmp(cmp) {}

    int* begin() {
        return heap.begin();
    }

    int* end() {
        return heap.begin() + sz;
    }

    const int* begin() const {
        return heap.begin();
    }

    const int* end() const {
        return heap.begin() + sz;
    }

    int size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    void siftUp(int index) {
#ifdef LOCAL
        if (index < 0 || index >= sz) {
            throw "Out of bounds";
        }
#endif
        int val = heap[index];
        while (index) {
            int parent = (index - 1) >> 1;
            int parVal = heap[parent];
            if (!cmp(val, parVal)) {
                heap[index] = val;
                pos[val] = index;
                return;
            }
            heap[index] = parVal;
            pos[parVal] = index;
            index = parent;
        }
        heap[0] = val;
        pos[val] = 0;
    }

    void siftDown(int index) {
#ifdef LOCAL
        if (index < 0 || index >= sz) {
            throw "Out of bounds";
        }
#endif
        while (true) {
            int child = (index << 1) + 1;
            if (child >= sz) {
                return;
            }
            if (child + 1 < sz && cmp(heap[child + 1], heap[child])) {
                child++;
            }
            if (!cmp(heap[child], heap[index])) {
                return;
            }
            swap(index, child);
            index = child;
        }
    }

    int operator [](int index) const {
#ifdef LOCAL
        if (index < 0 || index >= sz) {
            throw "Out of bounds";
        }
#endif
        return heap[index];
    }

    void push(int element) {
#ifdef LOCAL
        if (element < 0 || element >= pos.size() || pos[element] != -1) {
            throw "Out of bounds";
        }
#endif
        heap[sz] = element;
        pos[element] = sz;
        siftUp(sz++);
    }

    int at(int element) const {
#ifdef LOCAL
        if (element < 0 || element >= pos.size()) {
            throw "Out of bounds";
        }
#endif
        return pos[element];
    }

    int top() const {
#ifdef LOCAL
        if (sz == 0) {
            throw "Out of bounds";
        }
#endif
        return heap[0];
    }

    int pop() {
#ifdef LOCAL
        if (sz == 0) {
            throw "Out of bounds";
        }
#endif
        int res = heap[0];
        pos[res] = -1;
        if (sz == 1) {
            sz = 0;
            return res;
        }
        heap[0] = heap[--sz];
        pos[heap[0]] = 0;
        siftDown(0);
        return res;
    }

    bool erase(int element) {
#ifdef LOCAL
        if (element < 0 || element >= pos.size()) {
            throw "Out of bounds";
        }
#endif
        int index = pos[element];
        if (index == -1) {
            return false;
        }
        pos[element] = -1;
        if (index == sz - 1) {
            sz--;
            return true;
        }
        heap[index] = heap[--sz];
        pos[heap[index]] = index;
        siftDown(index);
        siftUp(index);
        return true;
    }

    void clear() {
        sz = 0;
        fill(all(pos), -1);
    }
};
