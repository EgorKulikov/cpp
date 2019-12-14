#pragma once

#include "collections/vector.h"

#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef pair<int, int> pii;

const double PI = atan(1) * 4;

template <typename T>
T minim(T& was, T cand) {
    return was = min(was, cand);
}

template <typename T>
T maxim(T& was, T cand) {
    return was = max(was, cand);
}
