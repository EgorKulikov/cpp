#pragma once

#include "../general.h"

void iterate(ll from, ll to, function<void(ll, int)> process, int base = 10) {
    vector<ll> power;
    ll max = numeric_limits<ll>::max();
    power.push_back(1);
    while (max / power.back() >= base) {
        power.push_back(power.back() * base);
    }
    to++;
    for (int i = 0; ; i++) {
        if (i != power.size() - 1 && from / power[i + 1] != to && from / power[i] % base == 0) {
            continue;
        }
        if (i != power.size() - 1 && from / power[i + 1] != to / power[i + 1] && from / power[i] % base != 0) {
            ll prefix = from / power[i + 1] * base;
            for (int j = (int) (from / power[i] % base); j < base; j++) {
                process(prefix + j, i);
            }
            from /= power[i + 1];
            from++;
            from *= power[i + 1];
        } else {
            ll upTo = to / power[i] % base;
            ll prefix = from / power[i] / base * base;
            for (int j = (int) (from / power[i] % base); j < upTo; j++) {
                process(prefix + j, i);
            }
            for (int k = i - 1; k >= 0; k--) {
                upTo = to / power[k] % base;
                prefix = to / power[k + 1] * base;
                for (int j = 0; j < upTo; j++) {
                    process(prefix + j, k);
                }
            }
            break;
        }
    }
}
