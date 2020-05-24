#pragma once

#include "../general.h"
#include "numbers.h"

class Rational {
    void normalize() {
        ll g = gcd(num, den);
        num /= g;
        den /= g;
    }

public:
    ll num;
    ll den;

    Rational(ll num = 0, ll den = 1) : num(num), den(den) {
        normalize();
    }

    Rational(const Rational& other) : num(other.num), den(other.den) {}

    Rational& operator +=(const Rational& other) {
        ll g = gcd(den, other.den);
        num = num * (other.den / g) + (den / g) * other.num;
        den *= other.den / g;
        normalize();
        return *this;
    }

    Rational& operator -=(const Rational& other) {
        ll g = gcd(den, other.den);
        num = num * (other.den / g) - (den / g) * other.num;
        den *= other.den / g;
        normalize();
        return *this;
    }

    Rational& operator *=(const Rational& other) {
        ll g = gcd(den, other.num);
        num *= other.num / g;
        den /= g;
        den *= other.den;
        normalize();
        return *this;
    }

    Rational& operator /=(const Rational& other) {
        ll g = gcd(den, other.den);
        num *= other.den / g;
        den /= g;
        den *= other.num;
        normalize();
        return *this;
    }
};

Rational operator +(const Rational& a, const Rational& b) {
    Rational res = a;
    res += b;
    return res;
}

Rational operator -(const Rational& a, const Rational& b) {
    Rational res = a;
    res -= b;
    return res;
}

Rational operator *(const Rational& a, const Rational& b) {
    Rational res = a;
    res *= b;
    return res;
}

Rational operator /(const Rational& a, const Rational& b) {
    Rational res = a;
    res /= b;
    return res;
}

Rational operator -(const Rational& a) {
    return Rational(-a.num, a.den);
}

bool operator <(const Rational& a, const Rational& b) {
//    return bigint(a.num) * b.den < bigint(a.den) * b.num;
    return a.num * b.den < a.den * b.num;
}

bool operator >(const Rational& a, const Rational& b) {
    return b < a;
}

bool operator >=(const Rational& a, const Rational& b) {
    return !(a < b);
}

bool operator <=(const Rational& a, const Rational& b) {
    return !(b < a);
}

bool operator ==(const Rational& a, const Rational& b) {
    return a.num == b.num && a.den == b.den;
}

bool operator !=(const Rational& a, const Rational& b) {
    return !(b == a);
}

ostream& operator <<(ostream& out, const Rational& val) {
    return out << val.num << '/' << val.den;
}
