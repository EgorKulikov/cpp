//
// Created by egor on 30.10.2019.
//

#ifndef JHELPER_EXAMPLE_PROJECT_GENERAL_H
#define JHELPER_EXAMPLE_PROJECT_GENERAL_H

#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int MAX_INT = 2147483647;

const double PI = atan(1) * 4;

const int DX_KNIGHT[] = {2, 1, -1, -2, -2, -1, 1, 2};
const int DY_KNIGHT[] = {1, 2, 2, 1, -1, -2, -2, -1};
const int DX4[] = {1, 0, -1, 0};
const int DY4[] = {0, 1, 0, -1};

bool isValidCell(int x, int y, int rows, int cols) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

void decreaseByOne() {
}

template <typename T, class...Vargs>
void decreaseByOne(vector<T>& arr, Vargs&...arrs) {
    for (int& i : arr) {
        i--;
    }
    decreaseByOne(arrs...);
}

template <typename T>
T minim(T& was, T cand) {
    return was = min(was, cand);
}

template <typename T>
T maxim(T& was, T cand) {
    return was = max(was, cand);
}

inline int bitCount(int number) {
    return __builtin_popcount(number);
}

inline int bitCount(ll number) {
    return __builtin_popcount(number);
}

#endif //JHELPER_EXAMPLE_PROJECT_GENERAL_H
