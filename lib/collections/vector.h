#pragma once

#include <bits/stdc++.h>

using namespace std;

template<typename T>
class Vector : public vector<T> {
    using parent = vector<T>;
public:
    Vector() : parent() {}
    explicit Vector(size_t __n) : parent(__n) {}
    Vector(size_t __n, const T& __value) : parent(__n, __value) {}
    explicit Vector(const parent& __x) : parent(__x) {}
    Vector(const Vector& __x) : parent(__x) {}
    Vector(Vector&& __x) noexcept : parent(move(__x)) {}
    Vector(initializer_list<T> __l) : parent(__l) {}
    template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
    Vector(_InputIterator __first, _InputIterator __last) : parent(__first, __last) {}

    const T& operator[](size_t ind) const {
#ifdef LOCAL
        if (ind >= parent::size() || ind < 0) {
            throw "Out of bounds";
        }
#endif
        return *(parent::_M_impl._M_start + ind);
    }

    T& operator[](size_t ind) {
#ifdef LOCAL
        if (ind >= parent::size() || ind < 0) {
            throw "Out of bounds";
        }
#endif
        return *(parent::_M_impl._M_start + ind);
    }

    Vector<T>& operator =(Vector<T>&& __x) noexcept {
        parent::operator=(__x);
        return *this;
    }

    Vector<T>& operator =(const Vector<T>& __x) {
        parent::operator=(__x);
        return *this;
    }
};

template<>
class Vector<bool> : public vector<bool> {
    using parent = vector<bool>;
public:
    Vector() : parent() {}
    explicit Vector(size_t __n) : parent(__n) {}
    Vector(size_t __n, const bool& __value) : parent(__n, __value) {}
    explicit Vector(const parent& __x) : parent(__x) {}
    Vector(const Vector& __x) : parent(__x) {}
    Vector(Vector&& __x) noexcept : parent(move(__x)) {}
    Vector(initializer_list<bool> __l) : parent(__l) {}
    template<typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
    Vector(_InputIterator __first, _InputIterator __last) : parent(__first, __last) {}

    parent::const_reference operator[](size_t ind) const {
#ifdef LOCAL
        if (ind >= parent::size() || ind < 0) {
            throw "Out of bounds";
        }
#endif
        return *const_iterator(this->_M_impl._M_start._M_p
                               + ind / int(_S_word_bit), ind % int(_S_word_bit));
    }

    parent::reference operator[](size_t ind) {
#ifdef LOCAL
        if (ind >= parent::size() || ind < 0) {
            throw "Out of bounds";
        }
#endif
        return *iterator(this->_M_impl._M_start._M_p
                         + ind / int(_S_word_bit), ind % int(_S_word_bit));
    }

    Vector<bool>& operator =(Vector<bool>&& __x) noexcept {
        parent::operator=(__x);
        return *this;
    }

    Vector<bool>& operator =(const Vector<bool>& __x) {
        parent::operator=(__x);
        return *this;
    }
};

#ifdef LOCAL
#define vec Vector
#else
#define vec vector
#endif

using vi = vec<int>;
