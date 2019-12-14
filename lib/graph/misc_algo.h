#pragma once

#include "../general.h"
#include "graph.h"
#include "../collections/arr.h"
#include "../collections/queue.h"

template <class Edge>
vi topologicalSort(const Graph<Edge>& graph) {
    vi result;
    int n = graph.vertexCount;
    result.reserve(n);
    arri degree(n, 0);
    for (int i = 0; i < n; ++i) {
        for (auto edge : graph[i]) {
            degree[edge->to]++;
        }
    }
    que<int> q;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int cur = q.pop();
        result.push_back(cur);
        for (auto edge : graph[cur]) {
            if (--degree[edge->to] == 0) {
                q.push(edge->to);
            }
        }
    }
    if (result.size() != n) {
        return vi(0);
    }
    return result;
}
