#pragma once

#include "general.h"

inline bool isSubset(int set, int subSet) {
    return (set & subSet) == subSet;
}

inline int bitCount(int x) {
    return __builtin_popcount(x);
}

inline int bitCount(unsigned x) {
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

inline ll setBit(ll mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 64) {
        throw "Bad index";
    }
#endif
    mask |= 1ll << bit;
    return mask;
}

inline int setBit(int mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 32) {
        throw "Bad index";
    }
#endif
    mask |= 1 << bit;
    return mask;
}

inline unsigned setBit(unsigned mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 32) {
        throw "Bad index";
    }
#endif
    mask |= unsigned(1) << bit;
    return mask;
}

inline ll unsetBit(ll mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 64) {
        throw "Bad index";
    }
#endif
    mask &= ~(1ll << bit);
    return mask;
}

inline int unsetBit(int mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 32) {
        throw "Bad index";
    }
#endif
    mask &= ~(1 << bit);
    return mask;
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

inline bool isSet(unsigned mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 32) {
        throw "Bad index";
    }
#endif
    return mask >> bit & 1;
}
