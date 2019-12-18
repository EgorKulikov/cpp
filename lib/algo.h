#pragma once

#include "general.h"
#include "collections/arr.h"

template <typename T>
inline void unique(vec<T>& v) {
    v.resize(unique(all(v)) - v.begin());
}

arri createOrder(int n) {
    arri order(n);
    for (int i = 0; i < n; i++) {
        order[i] = i;
    }
    return order;
}

template <class Collection, typename Iterator>
inline void addAll(Collection& v, Iterator begin, Iterator end) {
    v.insert(v.end(), begin, end);
}

template <typename Collection>
arri getQty(const Collection& arr, int length) {
    arri res(length);
    for (int i : arr) {
        res[i]++;
    }
    return res;
}

template <typename Collection>
arri getQty(const Collection& arr) {
    return getQty(arr, *max_element(all(arr)) + 1);
}

template <class Collection>
void collect(Collection&) {}

template <class Collection, class ...Vs>
void collect(Collection& all, Collection& a, Vs&...vs) {
    addAll(all, all(a));
    collect(all, vs...);
}

void replace(const vi&) {}

template <class ...Vs>
void replace(const vi& all, vi& a, Vs&...vs) {
    for (int& i : a) {
        i = lower_bound(all(all), i) - all.begin();
    }
    replace(all, vs...);
}

template <class ...Vs>
void replace(const vi& all, arri& a, Vs&...vs) {
    for (int& i : a) {
        i = lower_bound(all(all), i) - all.begin();
    }
    replace(all, vs...);
}

template <class ...Vs>
vi compress(Vs&...vs) {
    vi vals;
    collect(vals, vs...);
    sort(all(vals));
    unique(vals);
    replace(vals, vs...);
    return vals;
}
