#pragma once

#include "../general.h"
#include "../collections/arr.h"

vec<bool> primalityTable(int n) {
    vec<bool> res(n, true);
    if (n > 0) {
        res[0] = false;
    }
    if (n > 1) {
        res[1] = false;
    }
    for (int i = 2; i * i < n; i++) {
        if (res[i]) {
            for (int j = i * i; j < n; j += i) {
                res[j] = false;
            }
        }
    }
    return res;
}

arri divisorTable(int n) {
    arri res(n, 0);
    if (n > 1) {
        res[1] = 1;
    }
    for (int i = 2; i < n; i++) {
        if (res[i] == 0) {
            res[i] = i;
            if (ll(i) * i < n) {
                for (int j = i * i; j < n; j += i) {
                    res[j] = i;
                }
            }
        }
    }
    return res;
}

vi primes(int n) {
    auto isPrime = primalityTable(n);
    vi res;
    for (int i = 0; i < n; ++i) {
        if (isPrime[i]) {
            res.push_back(i);
        }
    }
    return res;
}
