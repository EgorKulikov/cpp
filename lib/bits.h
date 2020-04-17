#pragma once

#include "general.h"

inline bool isSubset(int set, int subSet) {
    return (set & subSet) == subSet;
}

inline int bitCount(int x) {
    return __builtin_popcount(x);
}

inline int bitCount(ll x) {
    return __builtin_popcountll(x);
}

inline int highestOneBit(int x) {
    return 1 << (31 - __builtin_clz(x | 1));
}

inline int binaryDigits(int x) {
    return 32 - __builtin_clz(x | 1);
}

inline void setBit(ll& mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 64) {
        throw "Bad index";
    }
#endif
    mask |= 1ll << bit;
}

inline void setBit(int& mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 32) {
        throw "Bad index";
    }
#endif
    mask |= 1 << bit;
}

inline bool isSet(ll mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 64) {
        throw "Bad index";
    }
#endif
    return mask >> bit & 1;
}

inline bool isSet(int mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 32) {
        throw "Bad index";
    }
#endif
    return mask >> bit & 1;
}
