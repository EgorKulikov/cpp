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

template <class Edge>
vi centers(Graph<Edge>& graph) {
    auto d0 = edgeDistances(graph, 0);
    int first = max_element(all(d0)) - d0.begin();
    auto d1 = edgeDistances(graph, first);
    int second = max_element(all(d1)) - d1.begin();
    auto d2 = edgeDistances(graph, second);
    vi res;
    int r1 = d1[second] / 2;
    int r2 = (d1[second] + 1) / 2;
    for (int i : range(d0.size())) {
        if (d1[i] == r1 && d2[i] == r2 || d1[i] == r2 && d2[i] == r1) {
            res.push_back(i);
        }
    }
    return res;
}