#pragma once

#include "../general.h"
#include "arr.h"

template <typename T>
class arr2d {
    T* b;
    int d1;
    int d2;
    int sz;

public:
    arr2d() : arr2d(0, 0) {}

    arr2d(int d1, int d2) : d1(d1), d2(d2), sz(d1 * d2) {
#ifdef LOCAL
        if (d1 < 0 || d2 < 0) {
            throw "bad alloc";
        }
#endif
        if (sz == 0) {
            b = nullptr;
        } else {
            b = new T[sz];
        }
#ifdef LOCAL
        view();
#endif
    }

    arr2d(int d1, int d2, const T& init) : arr2d(d1, d2) {
        fill(b, b + sz, init);
    }

    arr2d(T* b, int d1, int d2) : b(b), d1(d1), d2(d2), sz(d1 * d2) {}

    int size() const {
        return sz;
    }

    int dim1() const {
        return d1;
    }

    int dim2() const {
        return d2;
    }

    T* begin() {
        return b;
    }

    T* end() {
        return b + sz;
    }

    T& operator()(int i1, int i2) {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * d2 + i2];
    }

    const T& operator()(int i1, int i2) const {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * d2 + i2];
    }

    arr<T> operator[](int at) {
#ifdef LOCAL
        if (at < 0 || at >= d1) {
            throw "Out of bounds";
        }
#endif
        return arr<T>(b + at * d2, d2);
    }

    vector<vector<T>> view() {
        vector<vector<T>> res(min(d1, 50));
        for (int i = 0; i < res.size(); ++i) {
            res[i] = (*this)[i].view();
        }
        return res;
    }

    arr2d<T> clone() {
        arr2d<T> res(d1, d2);
        copy(b, b + sz, res.b);
        return res;
    }
};

template <typename T>
class arr3d {
    T* b;
    int d1;
    int d2;
    int d3;
    int shift;
    int sz;

public:
    arr3d() : arr3d(0, 0, 0) {}

    arr3d(int d1, int d2, int d3) : d1(d1), d2(d2), d3(d3), shift(d2 * d3), sz(d1 * d2 * d3) {
#ifdef LOCAL
        if (d1 < 0 || d2 < 0 || d3 < 0) {
            throw "bad alloc";
        }
#endif
        if (sz == 0) {
            b = nullptr;
        } else {
            b = (T*) malloc(sz * sizeof(T));
        }
#ifdef LOCAL
        view();
#endif
    }

    arr3d(int d1, int d2, int d3, const T& init) : arr3d(d1, d2, d3) {
        fill(b, b + sz, init);
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

template <typename T>
class arr4d {
    T* b;
    int d1;
    int d2;
    int d3;
    int d4;
    int shift1;
    int shift2;
    int sz;

public:
    arr4d() : arr4d(0, 0, 0, 0) {}

    arr4d(int d1, int d2, int d3, int d4) : d1(d1), d2(d2), d3(d3), d4(d4), shift1(d2 * d3 * d4), shift2(d3 * d4), sz(d1 * d2 * d3 * d4) {
#ifdef LOCAL
        if (d1 < 0 || d2 < 0 || d3 < 0) {
            throw "bad alloc";
        }
#endif
        if (sz == 0) {
            b = nullptr;
        } else {
            b = (T*) malloc(sz * sizeof(T));
        }
#ifdef LOCAL
        view();
#endif
    }

    arr4d(int d1, int d2, int d3, int d4, const T& init) : arr4d(d1, d2, d3, d4) {
        fill(b, b + sz, init);
    }

    arr4d(T* b, int d1, int d2, int d3, int d4) : b(b), d1(d1), d2(d2), d3(d3), d4(d4), shift1(d2 * d3 * d4), shift2(d3 * d4), sz(d1 * d2 * d3 * d4) {
    }

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

    int dim4() const {
        return d4;
    }

    T* begin() {
        return b;
    }

    T* end() {
        return b + sz;
    }

    T& operator()(int i1, int i2, int i3, int i4) {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2 || i3 < 0 || i3 >= d3 || i4 < 0 || i4 >= d4) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * shift1 + i2 * shift2 + i3 * d4 + i4];
    }

    const T& operator()(int i1, int i2, int i3, int i4) const {
#ifdef LOCAL
        if (i1 < 0 || i1 >= d1 || i2 < 0 || i2 >= d2 || i3 < 0 || i3 >= d3 || i4 < 0 || i4 >= d4) {
            throw "Out of bounds";
        }
#endif
        return b[i1 * shift1 + i2 * shift2 + i3 * d4 + i4];
    }

    arr3d<T> operator[](int at) {
#ifdef LOCAL
        if (at < 0 || at >= d1) {
            throw "Out of bounds";
        }
#endif
        return arr3d<T>(b + at * shift1, d2, d3, d4);
    }

    vector<vector<vector<vector<T>>>> view() {
        vector<vector<vector<vector<T>>>> res(min(d1, 50));
        for (int i = 0; i < res.size(); ++i) {
            res[i] = (*this)[i].view();
        }
        return res;
    }
};
