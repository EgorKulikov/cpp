#pragma once

#include "../general.h"

const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int MODF = 998244353;

int mod = MOD7;

class ModuloInt {
public:
    ll n;
    ModuloInt() : n(0) {}
    ModuloInt(ll n) {
        n %= mod;
        if (n < 0) {
            n += mod;
        }
        this->n = n;
    }
//    ModuloInt(const ModuloInt&) = default;
//    ModuloInt(ModuloInt&&) = default;
    ModuloInt& operator +=(const ModuloInt& other);
    ModuloInt& operator -=(const ModuloInt& other);
    ModuloInt& operator *=(const ModuloInt& other);
    ModuloInt operator -();
    friend ostream&operator <<(ostream& out, const ModuloInt& val);
};

ModuloInt &ModuloInt::operator+=(const ModuloInt& other) {
    n += other.n;
    if (n >= mod) {
        n -= mod;
    }
    return *this;
}

ModuloInt &ModuloInt::operator-=(const ModuloInt& other) {
    n -= other.n;
    if (n < 0) {
        n += mod;
    }
    return *this;
}

ModuloInt &ModuloInt::operator*=(const ModuloInt& other) {
    n *= other.n;
    n %= mod;
    return *this;
}

ModuloInt operator +(const ModuloInt& a, const ModuloInt& b) {
    return ModuloInt(a) += b;
}

ModuloInt operator -(const ModuloInt& a, const ModuloInt& b) {
    return ModuloInt(a) -= b;
}

ModuloInt operator *(const ModuloInt& a, const ModuloInt& b) {
    return ModuloInt(a) *= b;
}

ostream& operator <<(ostream& out, const ModuloInt& val) {
    return out << val.n;
}

ModuloInt ModuloInt::operator-() {
    if (n == 0) {
        return 0;
    }
    return ModuloInt(mod - n);
}

bool operator==(const ModuloInt& a, const ModuloInt& b) {
    return a.n == b.n;
}

bool operator!=(const ModuloInt& a, const ModuloInt& b) {
    return a.n != b.n;
}
