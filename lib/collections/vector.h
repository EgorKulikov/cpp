#pragma once

#include <bits/stdc++.h>

using namespace std;

template<typename T>
class vec : public vector<T> {
    typedef vector<T> parent;
public:
    vec() : parent() {}
    explicit vec(size_t __n) : parent(__n) {}
    vec(size_t __n, const T& __value) : parent(__n, __value) {}
    explicit vec(const parent& __x) : parent(__x) {}
    vec(const vec& __x) : parent(__x) {}
    vec(vec&& __x) noexcept : parent(move(__x)) {}
    vec(initializer_list<T> __l) : parent(__l) {}
    template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
    vec(_InputIterator __first, _InputIterator __last) : parent(__first, __last) {}

    const T& operator[](size_t ind) const {
#ifdef LOCAL
        if (ind >= parent::size()) {
            throw "Out of bounds";
        }
#endif
        return *(parent::_M_impl._M_start + ind);
    }

    T& operator[](size_t ind) {
#ifdef LOCAL
        if (ind >= parent::size()) {
            throw "Out of bounds";
        }
#endif
        return *(parent::_M_impl._M_start + ind);
    }

    vec<T>& operator =(vec<T>&& __x) noexcept {
        parent::operator=(__x);
        return *this;
    }

    vec<T>& operator =(const vec<T>& __x) {
        parent::operator=(__x);
        return *this;
    }

};

typedef vec<int> vi;
