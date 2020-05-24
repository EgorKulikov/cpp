#pragma once

#include "../general.h"
#include "../range/range.h"
#include "modulo.h"
#include "prime_fft.h"

constexpr int base = 1000000000;
constexpr int base_digits = 9;
constexpr int FFT_MIN_SIZE = 50000;

using vll = vector<ll>;

struct bigint {
    vi z;
    int sign;

    bigint() : sign(1) {}

    bigint(ll v) { *this = v; }

    bigint& operator=(ll v) {
        sign = v < 0 ? -1 : 1;
        v *= sign;
        z.clear();
        for (; v > 0; v = v / base) z.push_back((int) (v % base));
        return *this;
    }

    bigint(const string& s) { read(s); }

    bigint& operator+=(const bigint& other) {
        if (sign == other.sign) {
            for (int i = 0, carry = 0; i < other.z.size() || carry; ++i) {
                if (i == z.size()) {
                    z.push_back(0);
                }
                z[i] += carry + (i < other.z.size() ? other.z[i] : 0);
                carry = z[i] >= base;
                if (carry) {
                    z[i] -= base;
                }
            }
        } else if (other != 0) {
            *this -= -other;
        }
        return *this;
    }

    friend bigint operator+(bigint a, const bigint& b) { return a += b; }

    bigint& operator-=(const bigint& other) {
        if (sign == other.sign) {
            if (sign == 1 && *this >= other || sign == -1 && *this <= other) {
                for (int i = 0, carry = 0; i < other.z.size() || carry; ++i) {
                    z[i] -= carry + (i < other.z.size() ? other.z[i] : 0);
                    carry = z[i] < 0;
                    if (carry)
                        z[i] += base;
                }
                trim();
            } else {
                *this = other - *this;
                this->sign = -this->sign;
            }
        } else {
            *this += -other;
        }
        return *this;
    }

    friend bigint operator-(bigint a, const bigint& b) { return a -= b; }

    bigint& operator*=(int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < z.size() || carry; ++i) {
            if (i == z.size())
                z.push_back(0);
            ll cur = (ll) z[i] * v + carry;
            carry = (int) (cur / base);
            z[i] = (int) (cur % base);
        }
        trim();
        return *this;
    }

    bigint operator*(int v) const { return bigint(*this) *= v; }

    friend pair<bigint, bigint> divmod(const bigint& a1, const bigint& b1) {
        int norm = base / (b1.z.back() + 1);
        bigint a = a1.abs() * norm;
        bigint b = b1.abs() * norm;
        bigint q, r;
        q.z.resize(a.z.size());

        for (int i = (int) a.z.size() - 1; i >= 0; i--) {
            r *= base;
            r += a.z[i];
            int s1 = b.z.size() < r.z.size() ? r.z[b.z.size()] : 0;
            int s2 = b.z.size() - 1 < r.z.size() ? r.z[b.z.size() - 1] : 0;
            int d = (int) (((ll) s1 * base + s2) / b.z.back());
            r -= b * d;
            while (r < 0)
                r += b, --d;
            q.z[i] = d;
        }

        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return {q, r / norm};
    }

    friend bigint sqrt(const bigint& a1) {
        bigint a = a1;
        while (a.z.empty() || a.z.size() % 2 == 1)
            a.z.push_back(0);

        int n = a.z.size();

        int firstDigit = (int) ::sqrt((double) a.z[n - 1] * base + a.z[n - 2]);
        int norm = base / (firstDigit + 1);
        a *= norm;
        a *= norm;
        while (a.z.empty() || a.z.size() % 2 == 1)
            a.z.push_back(0);

        bigint r = (ll) a.z[n - 1] * base + a.z[n - 2];
        firstDigit = (int) ::sqrt((double) a.z[n - 1] * base + a.z[n - 2]);
        int q = firstDigit;
        bigint res;

        for (int j = n / 2 - 1; j >= 0; j--) {
            for (;; --q) {
                bigint r1 = (r - (res * 2 * base + q) * q) * base * base +
                            (j > 0 ? (ll) a.z[2 * j - 1] * base + a.z[2 * j - 2] : 0);
                if (r1 >= 0) {
                    r = r1;
                    break;
                }
            }
            res *= base;
            res += q;

            if (j > 0) {
                int d1 = res.z.size() + 2 < r.z.size() ? r.z[res.z.size() + 2] : 0;
                int d2 = res.z.size() + 1 < r.z.size() ? r.z[res.z.size() + 1] : 0;
                int d3 = res.z.size() < r.z.size() ? r.z[res.z.size()] : 0;
                q = (int) (((ll) d1 * base * base + (ll) d2 * base + d3) / (firstDigit * 2));
            }
        }

        res.trim();
        return res / norm;
    }

    bigint operator/(const bigint& v) const { return divmod(*this, v).first; }

    bigint operator%(const bigint& v) const { return divmod(*this, v).second; }

    bigint& operator/=(int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = (int) z.size() - 1, rem = 0; i >= 0; --i) {
            ll cur = z[i] + rem * (ll) base;
            z[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
        return *this;
    }

    bigint operator/(int v) const { return bigint(*this) /= v; }

    int operator%(int v) const {
        if (v < 0) v = -v;
        int m = 0;
        for (int i = (int) z.size() - 1; i >= 0; --i)
            m = (int) ((z[i] + m * (ll) base) % v);
        return m * sign;
    }

    bigint& operator*=(const bigint& v) { return *this = *this * v; }

    bigint& operator/=(const bigint& v) { return *this = *this / v; }

    bool operator<(const bigint& v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (z.size() != v.z.size())
            return z.size() * sign < v.z.size() * v.sign;
        for (int i = (int) z.size() - 1; i >= 0; i--)
            if (z[i] != v.z[i])
                return z[i] * sign < v.z[i] * sign;
        return false;
    }

    bool operator>(const bigint& v) const { return v < *this; }

    bool operator<=(const bigint& v) const { return !(v < *this); }

    bool operator>=(const bigint& v) const { return !(*this < v); }

    bool operator==(const bigint& v) const { return !(*this < v) && !(v < *this); }

    bool operator!=(const bigint& v) const { return *this < v || v < *this; }

    void trim() {
        while (!z.empty() && z.back() == 0) z.pop_back();
        if (z.empty()) sign = 1;
    }

    bool isZero() const { return z.empty(); }

    friend bigint operator-(bigint v) {
        if (!v.z.empty()) v.sign = -v.sign;
        return v;
    }

    bigint abs() const {
        return sign == 1 ? *this : -*this;
    }

    ll longValue() const {
        ll res = 0;
        for (int i = (int) z.size() - 1; i >= 0; i--)
            res = res * base + z[i];
        return res * sign;
    }

    friend bigint gcd(const bigint& a, const bigint& b) {
        if (b.isZero()) {
            return a;
        }
        if (a.isZero()) {
            return b;
        }
        if (a % 2 == 0) {
            if (b % 2 == 0) {
                return gcd(a / 2, b / 2) * 2;
            }
            return gcd(a / 2, b);
        }
        if (b % 2 == 0) {
            return gcd(a, b / 2);
        }
        if (a >= b) {
            return gcd(a - b, b);
        }
        return gcd(a, b - a);
    }

    friend bigint lcm(const bigint& a, const bigint& b) {
        return a / gcd(a, b) * b;
    }

    void read(const string& s) {
        sign = 1;
        z.clear();
        int pos = 0;
        while (pos < s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = (int) s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            z.push_back(x);
        }
        trim();
    }

    friend istream& operator>>(istream& stream, bigint& v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream& operator<<(ostream& stream, const bigint& v) {
        if (v.sign == -1)
            stream << '-';
        stream << (v.z.empty() ? 0 : v.z.back());
        for (int i = (int) v.z.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.z[i];
        return stream;
    }

    string toString() {
        ostringstream out;
        out << *this;
        return out.str();
    }


    static vector<modint> convert(const vi& z) {
        vector<modint> res;
        for (int i : z) {
            for (int j : range(base_digits)) {
                res.push_back(i % 10);
                i /= 10;
            }
        }
        return res;
    }

    bigint operator*(const bigint& v) const {
        if (z.size() == 0 || v.z.size() == 0) {
            return 0;
        }
        if (ll(z.size()) * v.z.size() < FFT_MIN_SIZE) {
            ll carry = 0;
            vi nz;
            for (int i : range(z.size() + v.z.size() - 1)) {
                ll cur = carry;
                carry = 0;
                for (int j : range(max(0, i - (int(v.z.size()) - 1)), min(i + 1, int(z.size())))) {
                    ll term = ll(z[j]) * v.z[i - j];
                    cur += term % base;
                    carry += term / base;
                }
                carry += cur / base;
                nz.push_back(cur % base);
            }
            while (carry > 0) {
                nz.push_back(carry % base);
                carry /= base;
            }
            bigint res = 0;
            res.z = nz;
            res.sign = sign * v.sign;
            return res;
        }
        auto a = convert(z);
        auto b = convert(v.z);
        int wasMod = mod;
        mod = MODF;
        auto c = multiply(a, b);
        mod = wasMod;
        vi nz;
        ll carry = 0;
        for (int i = 0; i < c.size(); i += base_digits) {
            ll times = 1;
            for (int j : range(min(int(c.size()) - i, base_digits))) {
                carry += c[i + j].n * times;
                times *= 10;
            }
            nz.push_back(carry % base);
            carry /= base;
        }
        while (carry > 0) {
            nz.push_back(carry % base);
            carry /= base;
        }
        bigint res = 0;
        res.z = nz;
        res.sign = sign * v.sign;
        return res;
    }

};
