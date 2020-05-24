#pragma once

#include "general.h"
#include "collections/arr.h"
#include "range/range.h"

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

arri inverse(const arri& p) {
    arri res(p.size());
    for (int i : range(p.size())) {
        res[p[i]] = i;
    }
    return res;
}

template <typename T, typename Iterator>
inline void addAll(vector<T>& v, Iterator begin, Iterator end) {
    v.insert(v.end(), begin, end);
}

template <class Collection, typename Iterator>
inline void addAll(Collection& v, Iterator begin, Iterator end) {
    v.insert(begin, end);
}

template <typename Iterator>
arri getQty(Iterator begin, Iterator end, int length) {
    arri res(length, 0);
    for (Iterator it = begin; it != end; it++) {
        res[*it]++;
    }
    return res;
}

template <typename Iterator>
arri getQty(Iterator begin, Iterator end) {
    return getQty(begin, end, *max_element(begin, end) + 1);
}

template <class Collection>
void collect(Collection&) {}

template <class Collection, class Other, class ...Vs>
void collect(Collection& all, Other& a, Vs&...vs) {
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
