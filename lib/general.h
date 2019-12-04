#pragma once

#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const double PI = atan(1) * 4;

template <typename T>
T minim(T& was, T cand) {
    return was = min(was, cand);
}

template <typename T>
T maxim(T& was, T cand) {
    return was = max(was, cand);
}

template <typename T, typename U>
void decreaseByOne(vector<pair<T, U> >& v) {
    for (auto& p : v) {
        p.first--;
        p.second--;
    }
}

void decreaseByOne() {}

template <typename T, class...Vs>
void decreaseByOne(vector<T>& arr, Vs&...vs) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        arr[i]--;
    }
    decreaseByOne(vs...);
}
