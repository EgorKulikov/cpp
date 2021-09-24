#include <cstdio>
#include <random>
#include "../lib/io/output.h"
#include "../lib/bits.h"
#include "../lib/collections/dsu.h"
#include "../lib/graph/edges/biedge.h"
#include "../lib/graph/lca.h"
#include "../lib/graph/edges/biweighted_edge.h"
#include "../lib/graph/algo/floyd_warshall.h"

random_device rd;
mt19937_64 gen(rd());

int main() {
    int n = 21;
    arr2d<int> p(n, n);
    for (int i : range(n)) {
        for (int j : range(n)) {
            p(i, j) = gen() % 10000;
        }
    }
    out.printLine(n);
    out.printLine(p);
}
