#include <cstdio>
#include "../lib/io/output.h"

int main() {
    freopen("input.txt", "w", stdout);
    int n = 1000000;
    out.printLine(n);
    out.printLine(vi(n, 1));
    for (int i : range(2, n + 1)) {
        out.printLine(i / 10 + 1, i);
    }
    out.flush();
    return 0;
}
