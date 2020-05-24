#pragma once

#include "numbers.h"
#include "modulo.h"

arr<modint> inverses(int length) {
    arr<modint> result(length);
    if (length > 1) {
        result[1] = 1;
    }
    for (int i = 2; i < length; i++) {
        result[i] = -(mod / i) * result[mod % i];
    }
    return result;
}

arr<modint> inverseFactorials(int length) {
    auto result = inverses(length);
    if (length > 0) {
        result[0] = 1;
    }
    for (int i = 1; i < length; i++) {
        result[i] *= result[i - 1];
    }
    return result;
}

class Combinations {
private:
    arr<modint> fact;
    arr<modint> invFactorial;

public:
    Combinations(int length) {
        fact = factorials<modint>(length);
        invFactorial = inverseFactorials(length);
    }

public:
    modint c(int n, int k) const {
        if (k < 0 || k > n) {
            return 0;
        }
        return fact[n] * invFactorial[k] * invFactorial[n - k];
    }

    modint operator ()(int n, int k) const {
        return c(n, k);
    }

    modint factorial(int n) const {
        return fact[n];
    }

    modint inverseFactorial(int n) const {
        return invFactorial[n];
    }
};
