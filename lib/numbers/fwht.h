#pragma once

#include "../general.h"
#include "../collections/arr.h"

template <typename T>
void fwht(arr<T>& p, bool inverse) {
    for (int len = 1; 2 * len <= p.size(); len <<= 1) {
        for (int i = 0; i < p.size(); i += 2 * len) {
            for (int j = 0; j < len; j++) {
                auto u = p[i + j];
                auto v = p[i + len + j];
                p[i + j] = u + v;
                p[i + len + j] = u - v;
            }
        }
    }

    if (inverse) {
        for (int i = 0; i < p.size(); i++)
            p[i] = p[i] / size;
    }
}
