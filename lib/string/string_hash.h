#pragma once

#include "../general.h"
#include "../numbers/modulo.h"
#include "../numbers/primes.h"

namespace string_hash {
    bool initDone = false;
    int firstMod;
    int secondMod;
    modint multiplier;
    modint firstRevMultiplier;
    modint secondRevMultiplier;

    void stringHashInit() {
        int wasMod = mod;
        random_device rd;
        mt19937_64 gen(rd());
        firstMod = nextPrime(500000000 + gen() % 500000000);
        secondMod = nextPrime(500000000 + gen() % 500000000);
        mod = firstMod;
        multiplier = 257 + gen() % (500000000 - 257);
        firstRevMultiplier = multiplier.inverse();
        mod = secondMod;
        secondRevMultiplier = multiplier.inverse();
        mod = wasMod;
        initDone = true;
    }


    vector<modint> firstRevPow;
    vector<modint> secondRevPow;
    vector<modint> firstPower;
    vector<modint> secondPower;

    void ensureCapacity(int n) {
        int wasMod = mod;
        mod = firstMod;
        while (firstRevPow.size() < n) {
            if (firstRevPow.empty()) {
                firstRevPow.push_back(1);
            } else {
                firstRevPow.push_back(firstRevPow.back() * firstRevMultiplier);
            }
        }
        while (firstPower.size() < n) {
            if (firstPower.empty()) {
                firstPower.push_back(1);
            } else {
                firstPower.push_back(firstPower.back() * multiplier);
            }
        }
        mod = secondMod;
        while (secondRevPow.size() < n) {
            if (secondRevPow.empty()) {
                secondRevPow.push_back(1);
            } else {
                secondRevPow.push_back(secondRevPow.back() * secondRevMultiplier);
            }
        }
        while (secondPower.size() < n) {
            if (secondPower.empty()) {
                secondPower.push_back(1);
            } else {
                secondPower.push_back(secondPower.back() * multiplier);
            }
        }
        mod = wasMod;
    }
}

class StringHash {
    arr<modint> firstHash;
    arr<modint> secondHash;

    template <typename Collection>
    void doPower(arr<modint>& hash, int cMod, const Collection& str) {
        using namespace string_hash;
        int wasMod = mod;
        mod = cMod;
        hash = arr<modint>(str.size() + 1);
        hash[0] = 0;
        modint power = 1;
        for (int i : range(str.size())) {
            hash[i + 1] = hash[i] + str[i] * power;
            power *= multiplier;
        }
        mod = wasMod;
    }

public:
    template <typename Collection>
    explicit StringHash(const Collection& str) {
        using namespace string_hash;
        if (!initDone) {
            stringHashInit();
        }
        ensureCapacity(str.size() + 1);
        doPower(firstHash, firstMod, str);
        doPower(secondHash, secondMod, str);
    }

    ll hash(int from, int to) const {
#ifdef LOCAL
        if (from < 0 || to < from || to > length()) {
            throw "Out of bounds";
        }
#endif
        using namespace string_hash;
        int wasMod = mod;
        mod = firstMod;
        ll first = ((firstHash[to] - firstHash[from]) * firstRevPow[from]).n;
        mod = secondMod;
        ll second = ((secondHash[to] - secondHash[from]) * secondRevPow[from]).n;
        mod = wasMod;
        return (first << 32) + second;
    }

    int length() const {
        return firstHash.size() - 1;
    }

    ll hash(int from) const {
        return hash(from, length());
    }
};

template <class Hash>
struct SubstringHash {
    const Hash& base;
    const int from;
    const int to;

    SubstringHash(const Hash& base, int from, int to) : base(base), from(from), to(to) {}

    SubstringHash(const Hash& base, int from) : SubstringHash(base, from, base.length()) {}

    ll hash(int from, int to) const {
#ifdef LOCAL
        if (from < 0 || to < from || to > length()) {
            throw "Out of bounds";
        }
#endif
        return base.hash(from + this->from, to + this->to);
    }

    int length() const {
        return to - from;
    }

    ll hash(int from) const {
        return hash(from, length());
    }
};

template <class Hash>
SubstringHash<Hash> substringHash(const Hash& base, int from, int to) {
    return SubstringHash<Hash>(base, from, to);
}

template <class Hash>
SubstringHash<Hash> substringHash(const Hash& base, int from) {
    return SubstringHash<Hash>(base, from);
}

template <class Hash1, class Hash2>
struct CompositeHash {
    const Hash1& base1;
    const Hash2& base2;

    CompositeHash(const Hash1& base1, const Hash2& base2) : base1(base1), base2(base2) {
        using namespace string_hash;
        ensureCapacity(base1.length() + 1);
    }

    ll hash(int from, int to) {
#ifdef LOCAL
        if (from < 0 || to < from || to > length()) {
            throw "Out of bounds";
        }
#endif
        using namespace string_hash;
        if (to <= base1.length()) {
            return base1.hash(from, to);
        }
        if (from >= base1.length()) {
            return base2.hash(from - base1.length(), to - base1.length());
        }
        ll h1 = base1.hash(from);
        ll h2 = base2.hash(0, to - base1.length());
        int wasMod = mod;
        mod = firstMod;
        ll first = (modint(h1 >> 32) * firstPower[base1.length() - from] + modint(h2 >> 32)).n;
        mod = secondMod;
        ll second = (modint(h1 & numeric_limits<unsigned>::max()) * firstPower[base1.length() - from] + modint(h2 & numeric_limits<unsigned>::max())).n;
        mod = wasMod;
        return (first << 32) + second;
    }

    int length() const {
        return base1.length() + base2.length();
    }

    ll hash(int from) const {
        return hash(from, length());
    }
};

template <class Hash1, class Hash2>
CompositeHash<Hash1, Hash2> compositeHash(const Hash1& base1, const Hash2& base2) {
    return CompositeHash<Hash1, Hash2>(base1, base2);
}
