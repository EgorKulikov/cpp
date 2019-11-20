//
// Created by egor on 31.10.2019.
//

#ifndef JHELPER_EXAMPLE_PROJECT_ALGO_H
#define JHELPER_EXAMPLE_PROJECT_ALGO_H

#include "general.h"

template <typename T>
inline void unique(vector<T>& v) {
    v.resize(unique(all(v)) - v.begin());
}

vi createOrder(int n) {
    vi order(n);
    for (int i = 0; i < n; i++) {
        order[i] = i;
    }
    return order;
}

template <typename T>
inline vector<vector<T> > makeArray(int a, int b) {
    return vector<vector<T> >(a, vector<T>(b));
}

//template <typename T>
//inline vector<vector<vector<T> > > makeArray(int a, int b, int c) {
//    return vector<vector<vector<T> > >(a, makeArray<T>(b, c));
//}

template <typename T>
inline vector<vector<T> > makeArray(int a, int b, T init) {
    return vector<vector<T> >(a, vector<T>(b, init));
}

template <typename T>
inline vector<vector<vector<T> > > makeArray(int a, int b, int c, T init) {
    return vector<vector<vector<T> > >(a, makeArray<T>(b, c, init));
}

template <typename T>
inline void addAll(vector<T>& v, const vector<T>& toAdd) {
    v.insert(v.end(), toAdd.begin(), toAdd.end());
}

vi getQty(const vi& arr, int length) {
    vi res(length);
    int n = arr.size();
    for (int i : arr) {
        res[i]++;
    }
    return res;
}

vi getQty(const vi& arr) {
    return getQty(arr, *max_element(all(arr)) + 1);
}

#endif //JHELPER_EXAMPLE_PROJECT_ALGO_H
