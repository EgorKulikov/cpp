#include <cstdio>
#include <random>
#include "../lib/io/output.h"
#include "../lib/bits.h"
#include "../lib/collections/dsu.h"
#include "../lib/graph/edges/biedge.h"
#include "../lib/graph/lca.h"
#include "../lib/graph/edges/biweighted_edge.h"
#include "../lib/graph/algo/floyd_warshall.h"

int main() {
    freopen("input.txt", "w", stdout);
    out.printLine(200000);
    for (int i : range(3, 200003)) {
        out.printLine(i);
    }
    out.flush();
}
