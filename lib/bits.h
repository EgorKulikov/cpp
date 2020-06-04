#pragma once

#include "general.h"

inline bool isSubset(unsigned set, unsigned subSet) {
    return (set & subSet) == subSet;
}

inline int bitCount(unsigned x) {
    return __builtin_popcount(x);
}

inline int bitCount(ull x) {
    return __builtin_popcountll(x);
}

inline int bitCount(uli x) {
    return __builtin_popcountll(x) + __builtin_popcountll(x >> 64);
}

inline int highestOneBit(unsigned x) {
    return 1 << (31 - __builtin_clz(x | 1));
}

inline int binaryDigits(unsigned x) {
    return 32 - __builtin_clz(x | 1);
}

inline ull setBit(ull mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 64) {
        throw "Bad index";
    }
#endif
    mask |= ull(1) << bit;
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

inline uli setBit(uli mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 128) {
        throw "Bad index";
    }
#endif
    mask |= uli(1) << bit;
    return mask;
}

inline ull unsetBit(ull mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 64) {
        throw "Bad index";
    }
#endif
    mask &= ~(ull(1) << bit);
    return mask;
}

inline unsigned unsetBit(unsigned mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 32) {
        throw "Bad index";
    }
#endif
    mask &= ~(unsigned(1) << bit);
    return mask;
}

inline uli unsetBit(uli mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 128) {
        throw "Bad index";
    }
#endif
    mask &= ~(uli(1) << bit);
    return mask;
}

inline bool isSet(ull mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 64) {
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

inline bool isSet(uli mask, int bit) {
#ifdef LOCAL
    if (bit < 0 || bit >= 128) {
        throw "Bad index";
    }
#endif
    return mask >> bit & 1;
}

inline unsigned allBits(int n) {
#ifdef LOCAL
    if (n < 0 || n >= 32) {
        throw "Bad index";
    }
#endif
    return (1u << n) - 1;
}

inline ull allBitsLL(int n) {
#ifdef LOCAL
    if (n < 0 || n >= 64) {
        throw "Bad index";
    }
#endif
    return (1ull << n) - 1;
}

inline uli allBits128(int n) {
#ifdef LOCAL
    if (n < 0 || n >= 128) {
        throw "Bad index";
    }
#endif
    return (uli(1) << n) - 1;
}
