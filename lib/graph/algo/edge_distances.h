#pragma once

#include "../../general.h"
#include "../../collections/arr.h"
#include "../../collections/queue.h"
#include "../graph.h"

template <class Edge>
arri edgeDistances(Graph<Edge>& graph, int source) {
    arri dist(graph.vertexCount, -1);
    dist[source] = 0;
    que<int> q;
    q.push(source);
    while (!q.empty()) {
        int current = q.pop();
        for (auto& edge : graph[current]) {
            int next = edge.to;
            if (dist[next] == -1) {
                dist[next] = dist[current] + 1;
                q.push(next);
            }
        }
    }
    return dist;
}
