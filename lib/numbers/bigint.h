#pragma once

#include "../general.h"

int TEN = 10000;

class BigInt {
private:
    bool sign;
    vi n;

    BigInt(bool sign, vi n) : sign(sign), n(move(n)) {}

    static bool less(const vi& a, const vi& b) {
        if (a.size() != b.size()) {
            return a.size() < b.size();
        }
        for (int i = a.size() - 1; i >= 0; i--) {
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
        }
        return false;
    }

    static vi sumImpl(const vi& a, const vi& b) {
        vi res;
        int carry = 0;
        for (int i = 0; i < max(a.size(), b.size()); i++) {
            if (i < a.size()) {
                carry += a[i];
            }
            if (i < b.size()) {
                carry += b[i];
            }
            res.push_back(carry % TEN);
            carry /= TEN;
        }
        while (carry > 0) {
            res.push_back(carry % TEN);
            carry /= TEN;
        }
        return res;
    }

    static BigInt subImpl(const vi& a, const vi& b) {
        if (less(a, b)) {
            BigInt res = subImpl(b, a);
            res.sign = true;
            return res;
        }
        vi res;
        int carry = 0;
        for (int i = 0; i < a.size(); i++) {
            carry += a[i];
            if (i < b.size()) {
                carry -= b[i];
            }
            int nextCarry = 0;
            if (carry < 0) {
                carry += TEN;
                nextCarry = -1;
            }
            res.push_back(carry);
            carry = nextCarry;
        }
        while (res.size() > 1 && res.back() == 0) {
            res.pop_back();
        }
        return BigInt(false, res);
    }

public:
    BigInt(ll val = 0) {
        sign = val < 0;
        val = abs(val);
        while (val > 0) {
            n.push_back(val % TEN);
            val /= TEN;
        }
        if (n.empty()) {
            n.push_back(0);
        }
    }

    friend BigInt operator +(const BigInt& a, const BigInt& b) {
        if (a.sign == b.sign) {
            vi digs = sumImpl(a.n, b.n);
            return BigInt(a.sign, digs);
        }
        auto res = subImpl(a.n, b.n);
        res.sign ^= a.sign;
        return res;
    }

    friend BigInt operator -(const BigInt& a, const BigInt& b) {
        if (a.sign != b.sign) {
            vi digs = sumImpl(a.n, b.n);
            return BigInt(a.sign, digs);
        }
        auto res = subImpl(a.n, b.n);
        res.sign ^= a.sign;
        return res;
    }

    friend bool operator <(const BigInt& a, const BigInt& b) {
        if (a.sign != b.sign) {
            return a.sign;
        }
        return a.sign ^ less(a.n, b.n);
    }

    friend bool operator >(const BigInt& a, const BigInt& b) {
        return b < a;
    }

    friend bool operator >=(const BigInt& a, const BigInt& b) {
        return !(a < b);
    }

    friend bool operator <=(const BigInt& a, const BigInt& b) {
        return !(a > b);
    }

    BigInt& operator +=(const BigInt& a) {
        return *this = *this + a;
    }

    BigInt& operator -=(const BigInt& a) {
        return *this = *this - a;
    }

    BigInt& operator *=(ll val) {
        if (val < 0) {
            sign ^= true;
            val = -val;
        }
        ll carry = 0;
        for (int i = 0; i < n.size(); ++i) {
            carry += val * n[i];
            n[i] = carry % TEN;
            carry /= TEN;
        }
        while (carry > 0) {
            n.push_back(carry % TEN);
            carry /= TEN;
        }
        return *this;
    }

    friend ostream& operator <<(ostream& out, const BigInt& val) {
        if (val.sign) {
            out << '-';
        }
        out << val.n.back();
        for (int i = int(val.n.size()) - 2; i >= 0; i--) {
            int cur = val.n[i];
            for (int j = TEN / 10; j >= 1; j /= 10) {
                out << cur / j;
                cur %= j;
            }
        }
        return out;
    }
};
