#pragma once

#ifndef JHELPER_EXAMPLE_PROJECT_NUMBERS_H
#define JHELPER_EXAMPLE_PROJECT_NUMBERS_H

#include "../general.h"
#include "modulo.h"

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
vector<T> generateFactorial(int length) {
    vector<T> result(length);
    if (length > 0) {
        result[0] = 1;
    }
    for (int i = 1; i < length; i++) {
        result[i] = result[i - 1] * i;
    }
    return result;
}

template <typename T>
vector<T> generateReverse(int length) {
    vector<T> result(length);
    if (length > 1) {
        result[1] = 1;
    }
    for (int i = 2; i < length; i++) {
        result[i] = -(mod / i) * result[mod % i];
    }
    return result;
}

template <typename T>
vector<T> generatePowers(T base, int length) {
    vector<T> result(length);
    if (length > 0) {
        result[0] = 1;
    }
    for (int i = 1; i < length; i++) {
        result[i] = result[i - 1] * base;
    }
    return result;
}

template <typename T>
vector<T> generateReverseFactorial(int length) {
    auto result = generateReverse<T>(length);
    if (length > 0) {
        result[0] = 1;
    }
    for (int i = 1; i < length; i++) {
        result[i] *= result[i - 1];
    }
    return result;
}

template <typename T>
class Combinations {
private:
    vector<T> fact;
    vector<T> revFactorial;

public:
    Combinations(int length) {
        fact = generateFactorial<T>(length);
        revFactorial = generateReverseFactorial<T>(length);
    }

public:
    T c(int n, int k) {
        if (k < 0 || k > n) {
            return 0;
        }
        return fact[n] * revFactorial[k] * revFactorial[n - k];
    }

    T factorial(int n) {
        return fact[n];
    }

    T reverseFactorial(int n) {
        return revFactorial[n];
    }
};
