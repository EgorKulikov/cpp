#pragma once

#include "../general.h"

template<typename T>
class vec : public vector<T> {
public:
    vec() : vector<T>() {}
    explicit vec(size_t __n) : vector<T>(__n) {}
    vec(size_t __n, const T& __value) : vector<T>(__n, __value) {}
    explicit vec(const vector<T>& __x) : vector<T>(__x) {}
    vec(const vec& __x) : vector<T>(__x) {}
    vec(vec&& __x) noexcept : vector<T>(std::move(__x)) {}
    vec(initializer_list<T> __l) : vector<T>(__l) {}
    template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
    vec(_InputIterator __first, _InputIterator __last) : vector<T>(__first, __last) {}

    const T& operator[](size_t ind) const {
        return vector<T>::at(ind);
    }

    T& operator[](size_t ind) {
        return vector<T>::at(ind);
    }
};
