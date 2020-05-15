#pragma once

#include "../../general.h"
#include "../../collections/mdarr.h"
#include "../graph.h"

template <class Edge, typename W>
arr2d<W> floydWarshall(Graph<Edge>& graph) {
    int n = graph.vertexCount;
    W inf = numeric_limits<W>().max() / 2;
    arr2d<W> dist(n, n, inf);
    for (int i = 0; i < n; i++) {
        dist(i, i) = 0;
        for (auto& edge : graph[i]) {
            minim(dist(i, edge.to), edge.weight);
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                minim(dist(i, j), dist(i, k) + dist(k, j));
            }
        }
    }
    return dist;
}
