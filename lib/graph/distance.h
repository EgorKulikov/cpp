#pragma once

#include "../general.h"
#include "graph.h"
#include "../collections/arr.h"
#include "../collections/mdarr.h"
#include "../collections/queue.h"

template <class Edge, typename W>
arr2d<W> floydWarshall(Graph<Edge> graph) {
    int n = graph.vertexCount;
    W inf = numeric_limits<W>().max() / 2;
    arr2d<W> dist(n, n, inf);
    for (int i = 0; i < n; i++) {
        dist(i, i) = 0;
        for (auto edge : graph.edges[i]) {
            minim(dist(i, edge->to), edge->weight);
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

template <class Edge>
arri edgeDistances(Graph<Edge>& graph, int source) {
    arri dist(graph.vertexCount, -1);
    dist[source] = 0;
    que<int> q;
    q.push(source);
    while (!q.empty()) {
        int current = q.pop();
        for (auto edge : graph.edges[current]) {
            int next = edge->to;
            if (dist[next] == -1) {
                dist[next] = dist[current] + 1;
                q.push(next);
            }
        }
    }
    return dist;
}


