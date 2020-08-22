#pragma once

#include "../general.h"
#include "../range/range.h"

template<typename T>
class NeedFill
{
    struct Fallback { int begin; }; // add member name "find"
    struct Derived : T, Fallback { };

    template<typename U, U> struct Check;

    typedef char Yes[1];  // typedef for an array of size one.
    typedef char No[2];  // typedef for an array of size two.

    template<typename U>
    static No& func(Check<int Fallback::*, &U::begin> *);

    template<typename U>
    static Yes& func(...);

public:
    typedef NeedFill type;
    enum { value = sizeof(func<Derived>(0)) == sizeof(Yes) };
};

template <>
class NeedFill<int> {
public:
    const static bool value = false;
};

template <>
class NeedFill<bool> {
public:
    const static bool value = true;
};

template <>
class NeedFill<ll> {
public:
    const static bool value = false;
};

template <>
class NeedFill<double> {
public:
    const static bool value = false;
};

template <typename T>
class arr {
    T* b;
    int n;

    void allocate(int sz) {
#ifdef LOCAL
        if (sz < 0) {
            throw "bad alloc";
        }
#endif
        n = sz;
        if (sz > 0) {
            b = (T*)(::operator new(sz * sizeof(T)));
        } else {
            b = nullptr;
        }
    }

public:
    arr(int n = 0) {
        allocate(n);
        if (NeedFill<T>::value) {
            for (int i : range(n)) {
                ::new((void*)(b + i)) T;
            }
        }
#ifdef LOCAL
        view();
#endif
    }

    arr(int n, const T& init) {
        allocate(n);
        for (int i : range(n)) {
            ::new((void*)(b + i)) T(init);
        }
#ifdef LOCAL
        view();
#endif
    }

    arr(T* b, int n) : arr(b, b + n) {}
    arr(T* b, T* e) : b(b), n(e - b) {}

    arr(initializer_list<T> l) : arr(l.size()) {
        if (n > 0) {
            memcpy(b, l.begin(), n * sizeof(T));
        }
    }

    int size() const {
        return n;
    }

    T* begin() {
        return b;
    }

    const T* begin() const {
        return b;
    }

    T* end() {
        return b + n;
    }

    const T* end() const {
        return b + n;
    }

    arr<T> clone() const {
        arr<T> res(n);
        copy(b, b + n, res.begin());
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

    bool operator ==(const arr& other) const {
        if (n != other.n) {
            return false;
        }
        for (int i : range(n)) {
            if (b[i] != other.b[i]) {
                return false;
            }
        }
        return true;
    }

    vector<T> view() {
        return vector<T>(b, b + n);
    }
};

typedef arr<int> arri;

void decreaseByOne() {}

template <typename T, class...Vs>
void decreaseByOne(arr<T>& array, Vs&...vs) {
    int n = array.size();
    for (int i : range(n)) {
        array[i]--;
    }
    decreaseByOne(vs...);
}

