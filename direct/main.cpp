#include<iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits.h>
#include "../tasks/PrettyPrimes.cpp"
#include "../lib/string/string_utils.h"
#include "../lib/io/output.h"
#include "../lib/bits.h"

using namespace std;

int main() {
    PrettyPrimes pp;
    for (int i : range(1, 100)) {
        for (int j : range(1, 13)) {
            auto t = clock();
            pp.solve(i, j);
            double d = double(clock() - t) / CLOCKS_PER_SEC;
            if (d > 0.5) {
                err.printLine(i, j, d);
            }
        }
    }
}