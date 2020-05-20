#include <cstdio>
#include <random>
#include "../lib/io/output.h"
#include "../lib/bits.h"

int main() {
    random_device rd;
    int b = 4;
    uniform_int_distribution gen(0, b - 1);
    freopen("input.txt", "w", stdout);
}
