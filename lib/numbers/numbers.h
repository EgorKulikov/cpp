#pragma once

#include "../general.h"
#include "modulo.h"
#include "../collections/arr.h"

template <typename T>
T gcd(T a, T b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        a = a % b;
        swap(a, b);
    }
    return a;
}

template <typename T>
T lcm(T a, T b) {
    return a / gcd(a, b) * b;
}

template <typename T>
T power(const T& a, ll b) {
    if (b == 0) {
        return 1;
    }
    if ((b & 1) == 0) {
        T res = power(a, b >> 1);
        return res * res;
    } else {
        return power(a, b - 1) * a;
    }
}

template <typename T>
arr<T> generateFactorial(int length) {
    arr<T> result(length);
    if (length > 0) {
        result[0] = 1;
    }
    for (int i = 1; i < length; i++) {
        result[i] = result[i - 1] * i;
    }
    return result;
}

arr<modint> generateInverse(int length) {
    arr<modint> result(length);
    if (length > 1) {
        result[1] = 1;
    }
    for (int i = 2; i < length; i++) {
        result[i] = -(mod / i) * result[mod % i];
    }
    return result;
}

template <typename T>
arr<T> generatePowers(T base, int length) {
    arr<T> result(length);
    if (length > 0) {
        result[0] = 1;
    }
    for (int i = 1; i < length; i++) {
        result[i] = result[i - 1] * base;
    }
    return result;
}

arr<modint> generateInverseFactorial(int length) {
    auto result = generateInverse(length);
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
        fact = generateFactorial<modint>(length);
        invFactorial = generateInverseFactorial(length);
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
