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
    vi ans;
    using Edge = BiWeightedEdge<int>;
    for (int n = 6; n <= 6; n++) {
        arri edges(n * (n - 1) / 2, 0);
        for (int i : range(edges.size() - n + 1, edges.size())) {
            edges[i] = 1;
        }
        DSU dsu(n);
        do {
            dsu.reset();
            int at = 0;
            for (int i : range(n)) {
                for (int j : range(i)) {
                    if (edges[at++]) {
                        dsu.join(i, j);
                    }
                }
            }
            if (dsu.setCount() != 1) {
                continue;
            }
            out.printLine();
            out.printLine(n, n * (n - 1) * n);
            Graph<BiEdge> tree(n);
            at = 0;
            for (int i : range(n)) {
                for (int j : range(i)) {
                    if (edges[at++]) {
                        tree.addEdge(i, j);
                        out.printLine(i + 1, j + 1);
                    }
                }
            }
            for (int r : range(n)) {
                LCA lca(tree, r);
                Graph<Edge> graph(n);
                at = 0;
                for (int i : range(n)) {
                    for (int j : range(i)) {
                        if (edges[at++]) {
                            graph.addEdge(i, j, 1);
                        }
                        int l = lca.lca(i, j);
                        if (l != i && l != j) {
                            graph.addEdge(i, j, lca.pathLength(l, r));
                        }
                    }
                }
                auto d = floydWarshall<Edge, int>(graph);
                for (int a : range(n)) {
                    for (int b : range(n)) {
                        if (a != b) {
                            out.printLine();
                            out.print(a + 1, b + 1, r + 1);
                            ans.push_back(d(a, b));
                        }
                    }
                }
            }
        } while (next_permutation(all(edges)));
    }
    out.flush();
    freopen("answer.txt", "w", stdout);
    for (int i : ans) {
        out.printLine(i);
    }
    out.flush();
}
