#include <cstdio>
#include <random>
#include "../lib/io/output.h"
#include "../lib/bits.h"

int main() {
    random_device rd;
    int b = 4;
    uniform_int_distribution gen(0, b - 1);
    freopen("input.txt", "w", stdout);
    int n = 100;
    string s;
    for (int i : range(n)) {
        s += char('0' + gen(rd));
    }
    int m = ((1 << b) - 1) * b;
    out.printLine(n, m, b);
    out.printLine(s);
    vi answer;
    for (int i : range(1, (1 << b))) {
        for (int j : range(b)) {
            string cur;
            for (int k : range(b)) {
                if (isSet(i, k)) {
                    cur += char('0' + k);
                }
            }
            out.printLine(j, cur);
            int res = 0;
            for (int l : range(n)) {
                for (int k : range(l + 1)) {
                    int sum = 0;
                    for (int o : range(k, l + 1)) {
                        sum += s[o] - '0';
                    }
                    int ss = sum;
                    if (sum > 0) {
                        ss = ss % (b - 1);
                        if (ss == 0) {
                            ss = b - 1;
                        }
                    }
                    if (ss == j) {
                        res++;
                    } else {
                        bool found = false;
                        for (int x : range(k, l + 1)) {
                            sum -= s[x] - '0';
                            for (int y : range(b)) {
                                if (isSet(i, y)) {
                                    int ss = sum + y;
                                    if (ss > 0) {
                                        ss = ss % (b - 1);
                                        if (ss == 0) {
                                            ss = b - 1;
                                        }
                                    }
                                    if (ss == j) {
                                        found = true;
                                        res++;
                                        break;
                                    }
                                }
                            }
                            if (found) {
                                break;
                            }
                            sum += s[x] - '0';
                        }
                    }
                }
            }
            answer.push_back(res);
        }
    }
    out.flush();
    freopen("answer.txt", "w", stdout);
    for (int i : answer) {
        out.printLine(i);
    }
    out.flush();
    return 0;
}
