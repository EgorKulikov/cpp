#include "../lib/general.h"
#include "../lib/collections/arr.h"
#include "../lib/io/output.h"

int main() {
    int n = 1'000'000;
    arri k(n);
    for (int i : range(n / 2)) {
        k[i] = 4095;
    }
    for (int i : range(n / 2, n)) {
        k[i] = 4096;
    }
    freopen("../test.out", "w", stdout);
    Output out(cout);
    out.printLine(n);
    out.printLine(k);
}