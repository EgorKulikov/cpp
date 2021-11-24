#pragma once

#include "../general.h"
#include "../collections/arr.h"

vector<string> split(const string& s, const string& delimiter) {
    vector<string> answer;
    size_t at = 0;
    while (true) {
        auto pos = s.find(delimiter, at);
        if (pos == string::npos) {
            answer.push_back(s.substr(at));
            break;
        }
        answer.push_back(s.substr(at, pos - at));
        at = pos + delimiter.size();
    }
    return answer;
}

arri prefixFunction(const string& s) {
    int n = (int) s.length();
    arri pi(n);
    pi[0] = 0;
    for (int i : range(1, n)) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

arri zAlgorithm(const string& s) {
    int n = s.size();
    arri z(n, 0);
    int l = 0;
    int r = 0;
    z[0] = -1;
    for (int i: range(1, n)) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}