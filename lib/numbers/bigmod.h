#pragma once

#include "../general.h"
#include "../range/range.h"
#include "numbers.h"
#include "primes.h"

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

    bigmod& operator+=(const bigmod& other) {
        n += other.n;
        if (n >= mod) {
            n -= mod;
        }
        return *this;
    }

    bigmod& operator-=(const bigmod& other) {
        n -= other.n;
        if (n < 0) {
            n += mod;
        }
        return *this;
    }

    bigmod& operator*=(const bigmod& other) {
        n = li(n) * other.n % mod;
        return *this;
    }

    bigmod& operator/=(const bigmod& other) {
#ifdef LOCAL
        if (other.n == 0) {
            throw "Division by zero";
        }
#endif
        return *this *= other.inverse();
    }

    bigmod operator-() {
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

bigmod operator+(const bigmod& a, const bigmod& b) {
    return bigmod(a) += b;
}

bigmod operator-(const bigmod& a, const bigmod& b) {
    return bigmod(a) -= b;
}

bigmod operator*(const bigmod& a, const bigmod& b) {
    return bigmod(a) *= b;
}

bigmod operator/(const bigmod& a, const bigmod& b) {
    return bigmod(a) /= b;
}

ostream& operator<<(ostream& out, const bigmod& v) {
    return out << v.n;
}

bool operator==(const bigmod& a, const bigmod& b) {
    return a.n == b.n;
}

bool operator!=(const bigmod& a, const bigmod& b) {
    return a.n != b.n;
}

random_device rd;
mt19937_64 gen(rd());

bool isPrimeFast(ll n) {
    if (n == 1) {
        return false;
    }
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

long long brent(long long n, long long x0 = 2, long long c = 1) {
    bigmod x = x0;
    long long g = 1;
    bigmod q = 1;
    bigmod xs;
    bigmod y;
    ll wasMod = mod;
    mod = n;

    int m = 128;
    int l = 1;
    while (g == 1) {
        y = x;
        for (int i = 1; i < l; i++)
            x = x * x + c;
        int k = 0;
        while (k < l && g == 1) {
            xs = x;
            for (int i = 0; i < m && i < l - k; i++) {
                x = x * x + c;
                q *= y - x;
            }
            g = gcd(q.n, n);
            k += m;
        }
        l *= 2;
    }
    if (g == n) {
        do {
            xs = xs * xs + c;
            g = gcd((xs - y).n, n);
        } while (g == 1);
    }
    mod = wasMod;
    return g;
}

ll findDivisor(ll n) {
    if (n == 1) {
        return 1;
    }
    if (n % 2 == 0) {
        return 2;
    }
    if (isPrimeFast(n)) {
        return n;
    }
    while (true) {
        auto res = brent(n, 2 + gen() % (n - 2), 1 + gen() % (n - 1));
        if (res != n) {
            return res;
        }
    }
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