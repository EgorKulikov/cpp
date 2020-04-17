#pragma once

#include "mdarr.h"

template <typename T>
class arr3d {
    T* b;
    int d1;
    int d2;
    int d3;
    int shift;
    int sz;

    void allocate(int n) {
#ifdef LOCAL
        if (n < 0) {
            throw "bad alloc";
        }
#endif
        if (n > 0) {
            b = (T*)(::operator new(n * sizeof(T)));
        } else {
            b = nullptr;
        }
    }

public:
    arr3d(int d1 = 0, int d2 = 0, int d3 = 0) : d1(d1), d2(d2), d3(d3), shift(d2 * d3), sz(d1 * d2 * d3) {
#ifdef LOCAL
        if (d1 < 0 || d2 < 0 || d3 < 0) {
            throw "bad alloc";
        }
#endif
        allocate(sz);
        for (int i : range(sz)) {
            ::new((void*)(b + i)) T;
        }
#ifdef LOCAL
        view();
#endif
    }

    arr3d(int d1, int d2, int d3, const T& init) : d1(d1), d2(d2), d3(d3), shift(d2 * d3), sz(d1 * d2 * d3) {
#ifdef LOCAL
        if (d1 < 0 || d2 < 0 || d3 < 0) {
            throw "bad alloc";
        }
#endif
        allocate(sz);
        for (int i : range(sz)) {
            ::new((void*)(b + i)) T(init);
        }
#ifdef LOCAL
        view();
#endif
    }

    arr3d(T* b, int d1, int d2, int d3) : b(b), d1(d1), d2(d2), d3(d3), shift(d2 * d3), sz(d1 * d2 * d3) {}

    int size() const {
        return sz;
    }

    int dim1() const {
        return d1;
    }

    int dim2() const {
        return d2;
    }

    int dim3() const {
        return d3;
    }

    T* begin() {
        return b;
    }

    T* end() {
        return b + sz;
    }

    T& operator()(int i1, int i2, int i3) {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2 || i3 < 0 || i3 >= d3) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * shift + i2 * d3 + i3];
    }

    const T& operator()(int i1, int i2, int i3) const {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2 || i3 < 0 || i3 >= d3) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * shift + i2 * d3 + i3];
    }

    arr2d<T> operator[](int at) {
#ifdef LOCAL
        if (at < 0 || at >= d1) {
            throw "Out of bounds";
        }
#endif
        return arr2d<T>(b + at * shift, d2, d3);
    }

    vector<vector<vector<T>>> view() {
        vector<vector<vector<T>>> res(min(d1, 50));
        for (int i = 0; i < res.size(); ++i) {
            res[i] = (*this)[i].view();
        }
        return res;
    }
};
