#pragma once

#include "../general.h"
#include "primes.h"

struct MultiplicativeFunction {
    function<ll(ll, int, ll)> value;

    MultiplicativeFunction(const function<ll(ll, int, ll)>& value) : value(value) {}

    ll operator ()(ll argument) {
        ll val = 1;
        for (ll i = 2; i * i <= argument; i++) {
            if (argument % i == 0) {
                int exponent = 0;
                ll power = 1;
                do {
                    exponent++;
                    power *= i;
                    argument /= i;
                } while (argument % i == 0);
                val *= value(i, exponent, power);
            }
        }
        if (argument != 1) {
            val *= value(argument, 1, argument);
        }
        return val;
    }

    arr<ll> calculateUpTo(int n) {
        auto divisor = divisorTable(n);
        arr<ll> result(n);
        if (n >= 1) {
            result[0] = 0;
        }
        if (n <= 1) {
            return result;
        }
        result[1] = 1;
        for (int i : range(2, n)) {
            int iDivided = i;
            int exponent = 0;
            do {
                iDivided /= divisor[i];
                exponent++;
            } while (iDivided % divisor[i] == 0);
            result[i] = result[iDivided] * value(divisor[i], exponent, i / iDivided);
        }
        return result;
    }
};

MultiplicativeFunction divisorCount([](ll, int exponent, ll) -> ll {
    return exponent + 1;
});

MultiplicativeFunction divisorSum([](ll p, int, ll power) -> ll {
    return (power * p - 1) / (p - 1);
});

MultiplicativeFunction phi([](ll p, int, ll power) -> ll {
    return power / p * (p - 1);
});

MultiplicativeFunction mobius([](ll, int exponent, ll) -> ll {
    return exponent == 1 ? -1 : 0;
});
