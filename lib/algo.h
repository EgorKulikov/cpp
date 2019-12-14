#pragma once

#include "general.h"

template <typename T>
inline void unique(vector<T>& v) {
    v.resize(unique(all(v)) - v.begin());
}

arri createOrder(int n) {
    arri order(n);
    for (int i = 0; i < n; i++) {
        order[i] = i;
    }
    return order;
}

template <typename T, typename Iterator>
inline void addAll(vector<T>& v, Iterator begin, Iterator end) {
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

template <typename T>
void collect(vector<T>& all) {}

template <typename T, class ...Vs>
void collect(vector<T>& all, vector<T>& a, Vs&...vs) {
    addAll(all, all(a));
    collect(all, vs...);
}

void replace(const vi& all) {}

template <class ...Vs>
void replace(const vi& all, vi& a, Vs&...vs) {
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
