#pragma once

#include "../collections/arr.h"

arri oddPalindromes(const string& s) {
    int n = s.size();
    arri d1(n, 0);
    int l = 0;
    int r = -1;
    for (int i = 0; i < n; ++i) {
        int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
        while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) {
            k++;
        }
        d1[i] = k;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    return d1;
}

arri evenPalindromes(const string& s) {
    int n = s.size();
    arri d2(n, 0);
    int l = 0;
    int r = -1;
    for (int i = 0; i < n; ++i) {
        int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i + k < n && i - k - 1 >= 0 && s[i + k] == s[i - k - 1]) {
            k++;
        }
        d2[i] = k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }
    return d2;
}
