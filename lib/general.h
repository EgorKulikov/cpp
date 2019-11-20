#ifndef JHELPER_EXAMPLE_PROJECT_GENERAL_H
#define JHELPER_EXAMPLE_PROJECT_GENERAL_H

#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int MAX_INT = 2147483647;

const double PI = atan(1) * 4;

const int DX_KNIGHT[] = {2, 1, -1, -2, -2, -1, 1, 2};
const int DY_KNIGHT[] = {1, 2, 2, 1, -1, -2, -2, -1};
const int DX4[] = {1, 0, -1, 0};
const int DY4[] = {0, 1, 0, -1};
const int DX8[] = {1, 1, 1, 0, -1, -1, -1, 0};
const int DY8[] = {-1, 0, 1, 1, 1, 0, -1, -1};

template <typename T>
T minim(T& was, T cand) {
    return was = min(was, cand);
}

template <typename T>
T maxim(T& was, T cand) {
    return was = max(was, cand);
}

bool isValidCell(int r, int c, int n, int m) {
    return r >= 0 && c >= 0 && r < n && c < m;
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

inline bool isSubset(int set, int subSet) {
    return (set & subSet) == subSet;
}

#endif //JHELPER_EXAMPLE_PROJECT_GENERAL_H
