#include <cstdio>
#include <random>
#include "../lib/io/output.h"
#include "../lib/bits.h"

int main() {
    random_device rd;
    uniform_int_distribution gen(1, 1000);
    freopen("input.txt", "w", stdout);
    int n = 25000;
    out.printLine(n);
    auto sign = [&]() -> int {
        if (gen(rd) % 2) {
            return gen(rd);
        } else {
            return -gen(rd);
        }
    };
    for (int i : range(n)) {
        out.printLine(gen(rd), gen(rd), sign(), sign(), gen(rd));
    }
    out.flush();
}
