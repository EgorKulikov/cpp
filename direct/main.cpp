#include <cstdio>
#include <random>
#include "../lib/bits.h"
#include "../lib/range/range.h"
#include "../lib/io/output.h"

int main() {
    auto maxDigit = [&](ll prefix) -> int {
        int res = 0;
        while (prefix != 0) {
            maxim(res, int(prefix % 10));
            prefix /= 10;
        }
        return res;
    };
    int a = 123;
    int m = 876543;
    int n = 369277;
    for (int i : range(n)) {
        a += maxDigit(a);
        if (a >= m) {
            out.printLine(i + 1, a - m);
        }
        a %= m;
    }
    out.printLine(a);
}
