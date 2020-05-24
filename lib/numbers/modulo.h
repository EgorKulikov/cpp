#pragma once

#include "../general.h"

const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int MODF = 998244353;

int mod = MOD7;

ll gcd(ll a, ll b, ll& x, ll& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int d = gcd(b % a, a, y, x);
    x -= (b / a) * y;
    return d;
}

class modint {
public:
    int n;
    modint() : n(0) {}
    modint(ll n, bool special = false) {
        if (special) {
            this->n = -1;
            return;
        }
        if (n >= 0 && n < mod) {
            this->n = n;
            return;
        }
        n %= mod;
        if (n < 0) {
            n += mod;
        }
        this->n = n;
    }
    modint& operator +=(const modint& other) {
#ifdef LOCAL
        if (n == -1 || other.n == -1) {
            throw "Illegal state";
        }
#endif
        n += other.n;
        if (n >= mod) {
            n -= mod;
        }
        return *this;
    }
    modint& operator -=(const modint& other) {
#ifdef LOCAL
        if (n == -1 || other.n == -1) {
            throw "Illegal state";
        }
#endif
        n -= other.n;
        if (n < 0) {
            n += mod;
        }
        return *this;
    }
    modint& operator *=(const modint& other) {
#ifdef LOCAL
        if (n == -1 || other.n == -1) {
            throw "Illegal state";
        }
#endif
        n = ll(n) * other.n % mod;
        return *this;
    }
    modint& operator /=(const modint& other) {
#ifdef LOCAL
        if (other.n == 0) {
            throw "Division by zero";
        }
        if (n == -1 || other.n == -1) {
            throw "Illegal state";
        }
#endif
        return *this *= other.inverse();
    }
    modint operator -() {
#ifdef LOCAL
        if (n == -1) {
            throw "Illegal state";
        }
#endif
        if (n == 0) {
            return 0;
        }
        return modint(mod - n);
    }
    modint inverse() const {
#ifdef LOCAL
        if (n == -1) {
            throw "Illegal state";
        }
#endif
        ll x, y;
        ll g = gcd(ll(n), ll(mod), x, y);
#ifdef LOCAL
        if (g != 1) {
            throw "not inversable";
        }
#endif
        return x;
    }
    int log(modint alpha);
};

modint nullModint(-1, true);

modint operator +(const modint& a, const modint& b) {
    return modint(a) += b;
}

modint operator -(const modint& a, const modint& b) {
    return modint(a) -= b;
}

modint operator *(const modint& a, const modint& b) {
    return modint(a) *= b;
}

modint operator /(const modint& a, const modint& b) {
    return modint(a) /= b;
}

ostream& operator <<(ostream& out, const modint& val) {
    return out << val.n;
}

bool operator==(const modint& a, const modint& b) {
    return a.n == b.n;
}

bool operator!=(const modint& a, const modint& b) {
    return a.n != b.n;
}

namespace std {
    template <>
    struct hash<modint> {
        size_t operator ()(const modint& n) const {
            return n.n;
        }
    };
}

int modint::log(modint alpha) {
#ifdef LOCAL
    if (n == -1 || alpha.n == -1) {
        throw "Illegal state";
    }
#endif
    unordered_map<modint, int> base;
    int exp = 0;
    modint pow = 1;
    modint inv = *this;
    modint alInv = alpha.inverse();
    while (exp * exp < mod) {
        if (inv == 1) {
            return exp;
        }
        base[inv] = exp++;
        pow *= alpha;
        inv *= alInv;
    }
    modint step = pow;
    for (int i = 1; ; i++) {
        if (base.count(pow)) {
            return exp * i + base[pow];
        }
        pow *= step;
    }
}
