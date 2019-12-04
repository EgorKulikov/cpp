#pragma once

#ifndef CPP_MISC_ALGO_H
#define CPP_MISC_ALGO_H

#include "../general.h"
#include "graph.h"

template <class Edge>
vi topologicalSort(const Graph<Edge>& graph) {
    vi result;
    int n = graph.vertexCount;
    result.reserve(n);
    vi degree(n);
    for (int i = 0; i < n; ++i) {
        for (auto edge : graph.edges[i]) {
            degree[edge->to]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int cur = q.front();
        result.push_back(cur);
        q.pop();
        for (auto edge : graph.edges[cur]) {
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
