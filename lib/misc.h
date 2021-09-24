#pragma once

#include "general.h"
#include "io/input.h"

const int DX_KNIGHT[] = {2, 1, -1, -2, -2, -1, 1, 2};
const int DY_KNIGHT[] = {1, 2, 2, 1, -1, -2, -2, -1};
const int DX4[] = {1, 0, -1, 0};
const int DY4[] = {0, 1, 0, -1};
const int DX8[] = {1, 1, 1, 0, -1, -1, -1, 0};
const int DY8[] = {-1, 0, 1, 1, 1, 0, -1, -1};

bool isValidCell(int r, int c, int n, int m) {
    return r >= 0 && c >= 0 && r < n && c < m;
}

bool isValidCell(pii pos, int n, int m) {
    return isValidCell(pos.first, pos.second, n, m);
}

arr<ll> facebookGen(int n, int k, int add = 0) {
    arr<ll> res(n);
    for (int i : range(k)) {
        res[i] = in.readLong();
    }
    ll a = in.readLong();
    ll b = in.readLong();
    ll c = in.readLong();
    ll d = in.readLong();
    for (int i : range(k, n)) {
        res[i] = (a * res[i - 2] + b * res[i - 1] + c) % d + add;
    }
    return res;
}

arr<ll> facebookGenFixedMod(int n, int k, ll d, int add = 0) {
    arr<ll> res(n);
    for (int i : range(k)) {
        res[i] = in.readLong();
    }
    ll a = in.readLong();
    ll b = in.readLong();
    ll c = in.readLong();
    for (int i : range(k, n)) {
        res[i] = (a * res[i - 2] + b * res[i - 1] + c) % d + add;
    }
    return res;
}

arr<ll> facebookGenTree(int n, int k, int add = 0) {
    arr<ll> res(n);
    for (int i : range(k)) {
        res[i] = in.readLong();
    }
    ll a = in.readLong();
    ll b = in.readLong();
    ll c = in.readLong();
    for (int i : range(k, n)) {
        res[i] = (a * res[i - 2] + b * res[i - 1] + c) % i + add;
    }
    return res;
}
