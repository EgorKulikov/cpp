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
