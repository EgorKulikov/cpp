#pragma once

#include "../general.h"

template <typename T>
class arr {
    T* b;
    T* e;
    int n;
public:
    arr() : b(nullptr), e(nullptr), n(0) {}

    arr(int n) : n(n) {
        b = new T[n];
        e = b + n;
    }

    arr(int n, const T& init) : n(n) {
        b = new T[n];
        e = b + n;
        fill(b, e, init);
    }

    arr(T* b, int n) : b(b), e(b + n), n(n) {}
    arr(T* b, T* e) : b(b), e(e), n(e - b) {}

    size_t size() const {
        return n;
    }

    T* begin() {
        return b;
    }

    T* end() {
        return e;
    }

    arr<T> clone() const {
        arr<T> res(n);
        copy(b, e, res.begin());
        return res;
    }

    T& operator[](int at) {
#ifdef LOCAL
        if (at < 0 || at >= n) {
            throw "Out of bounds";
        }
#endif
        return b[at];
    }

    const T& operator[](int at) const {
#ifdef LOCAL
        if (at < 0 || at >= n) {
            throw "Out of bounds";
        }
#endif
        return b[at];
    }
};

typedef arr<int> arri;

void decreaseByOne() {}

template <typename T, class...Vs>
void decreaseByOne(arr<T>& array, Vs&...vs) {
    int n = array.size();
    for (int i = 0; i < n; ++i) {
        array[i]--;
    }
    decreaseByOne(vs...);
}

template <typename T, typename U>
void decreaseByOne(arr<pair<T, U> >& v) {
    for (auto& p : v) {
        p.first--;
        p.second--;
    }
}