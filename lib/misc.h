#pragma once

const int DX_KNIGHT[] = {2, 1, -1, -2, -2, -1, 1, 2};
const int DY_KNIGHT[] = {1, 2, 2, 1, -1, -2, -2, -1};
const int DX4[] = {1, 0, -1, 0};
const int DY4[] = {0, 1, 0, -1};
const int DX8[] = {1, 1, 1, 0, -1, -1, -1, 0};
const int DY8[] = {-1, 0, 1, 1, 1, 0, -1, -1};

bool isValidCell(int r, int c, int n, int m) {
    return r >= 0 && c >= 0 && r < n && c < m;
}

inline bool isSubset(int set, int subSet) {
    return (set & subSet) == subSet;
}

inline int bitCount(int x) {
    return __builtin_popcount(x);
}

inline int bitCount(ll x) {
    return __builtin_popcountll(x);
}
