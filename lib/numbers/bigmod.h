#pragma once

#include "../general.h"
#include "../range/range.h"
#include "numbers.h"

ll mod = 1000000007;

li gcd(li a, li b, li& x, li& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int d = gcd(b % a, a, y, x);
    x -= (b / a) * y;
    return d;
}

class bigmod {
public:
    ll n;
    bigmod() : n(0) {}
    bigmod(ll n) {
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
    bigmod& operator +=(const bigmod& other) {
        n += other.n;
        if (n >= mod) {
            n -= mod;
        }
        return *this;
    }
    bigmod& operator -=(const bigmod& other) {
        n -= other.n;
        if (n < 0) {
            n += mod;
        }
        return *this;
    }
    bigmod& operator *=(const bigmod& other) {
        n = li(n) * other.n % mod;
        return *this;
    }
    bigmod& operator /=(const bigmod& other) {
#ifdef LOCAL
        if (other.n == 0) {
            throw "Division by zero";
        }
#endif
        return *this *= other.inverse();
    }
    bigmod operator -() {
        if (n == 0) {
            return 0;
        }
        return bigmod(mod - n);
    }
    bigmod inverse() const {
        li x, y;
        li g = gcd(__int128(n), __int128(mod), x, y);
#ifdef LOCAL
        if (g != 1) {
            throw "not inversable";
        }
#endif
        return x;
    }
};

bigmod operator +(const bigmod& a, const bigmod& b) {
    return bigmod(a) += b;
}

bigmod operator -(const bigmod& a, const bigmod& b) {
    return bigmod(a) -= b;
}

bigmod operator *(const bigmod& a, const bigmod& b) {
    return bigmod(a) *= b;
}

bigmod operator /(const bigmod& a, const bigmod& b) {
    return bigmod(a) /= b;
}

ostream& operator <<(ostream& out, const bigmod& val) {
    return out << val.n;
}

bool operator==(const bigmod& a, const bigmod& b) {
    return a.n == b.n;
}

bool operator!=(const bigmod& a, const bigmod& b) {
    return a.n != b.n;
}

bool isPrime(ll n) {
    random_device rd;
    mt19937_64 gen(rd());

    int s = 0;
    ll d = n - 1;
    while (d % 2 == 0) {
        s++;
        d /= 2;
    }
    if (s == 0) {
        return n == 2;
    }
    ll wasMod = mod;
    mod = n;
    for (int x : range(20)) {
        bigmod a = gen() % (n - 1);
        if (a == 0) {
            continue;
        }
        if (power(a, d) == 1) {
            continue;
        }
        ll dd = d;
        bool good = true;
        for (int y : range(s)) {
            if (power(a, dd) == n - 1) {
                good = false;
                break;
            }
            dd *= 2;
        }
        if (good) {
            mod = wasMod;
            return false;
        }
    }
    mod = wasMod;
    return true;
}

ll findDivisor(ll n) {
    if (n == 1) {
        return 1;
    }
    if (n % 2 == 0) {
        return 2;
    }
    if (isPrime(n)) {
        return n;
    }
    ll wasMod = mod;
    mod = n;
    bigmod x = 0;
    bigmod y = 0;
    int i = 1;
    ll d = 1;

    while (true) {
        x = ++i;
        y = x * x + 1;
        d = 1;
        while (d == 1) {
            x = x * x + 1;
            y = y * y + 1;
            y = y * y + 1;
            d = gcd(abs(x.n - y.n), n);
        }
        if (d != n) {
            break;
        }
    }
    mod = wasMod;
    return d;
}

vector<pair<ll, int>> divisors(ll n) {
    if (n == 1) {
        return {};
    }
    ll d = findDivisor(n);
    if (d == n) {
        return {{d, 1}};
    }
    auto left = divisors(d);
    auto right = divisors(n / d);
    vector<pair<ll, int>> result;
    int i = 0;
    int j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i].first < right[j].first) {
            result.push_back(left[i++]);
        } else if (left[i].first > right[j].first) {
            result.push_back(right[j++]);
        } else {
            result.emplace_back(left[i].first, left[i].second + right[j].second);
            i++;
            j++;
        }
    }
    for (int k : range(i, left.size())) {
        result.push_back(left[k]);
    }
    for (int k : range(j, right.size())) {
        result.push_back(right[k]);
    }
    return result;
}