#include <cstdio>
#include <random>
#include "../lib/bits.h"
#include "../lib/range/range.h"
#include "../lib/io/output.h"

int main() {
    arr2d<ll> ans(11, 11, 0);
    for (int i : range(1, 11)) {
        for (int j : range(1, 11)) {
            for (int dx : range(1, min(i, j) + 1)) {
                for (int dy : range(0, min(i, j) - dx + 1)) {
                    int sum = dx + dy;
                    ans(i, j) += (dx * dx + dy * dy) * (i + 1 - sum) * (j + 1 - sum);
                }
            }
        }
    }
    out.printLine(ans);
    out.flush();
}
