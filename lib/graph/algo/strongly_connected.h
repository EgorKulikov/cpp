#pragma once

#include "../../general.h"
#include "../graph.h"
#include "../../collections/arr.h"
#include "../../range/rev_range.h"
#include "../edges/base_edge.h"
#include "../../recursive_function.h"

pair<arri, Graph<BaseEdge>> stronglyConnectedComponents(Graph<BaseEdge>& graph) {
    int n = graph.vertexCount;
    vi order;
    arr<bool> visited(n, false);
    arri condensed(n);
    order.reserve(n);
#if __cplusplus >= 201700L
    RecursiveFunction firstDFS = [&](const auto& self, int vert) -> void {
#else
    function<void(int)> firstDFS = [&](int vert) -> void {
#endif
        if (visited[vert]) {
            return;
        }
        visited[vert] = true;
        for (auto& e : graph[vert]) {
#if __cplusplus >= 201700L
            self(e.to);
#else
            firstDFS(e.to);
#endif
        }
        order.push_back(vert);
    };
    for (int i : range(n)) {
        if (!visited[i]) {
            firstDFS(i);
        }
    }
    fill(all(visited), false);
    Graph<BaseEdge> result(0);
    int index = 0;
    arri next(n, -1);
    vi queue;
    int key;
    Graph<BaseEdge> gt(n);
    for (int i : range(n)) {
        for (auto& e : graph[i]) {
            gt.addEdge(e.to, i);
        }
    }
#if __cplusplus >= 201700L
    RecursiveFunction secondDFS = [&](const auto& self, int vert) -> void {
#else
    function<void(int)> secondDFS = [&](int vert) -> void {
#endif
        if (visited[vert]) {
            if (condensed[vert] != index) {
                if (next[condensed[vert]] != key) {
                    next[condensed[vert]] = key;
                    queue.push_back(condensed[vert]);
                }
            }
            return;
        }
        condensed[vert] = index;
        visited[vert] = true;
        for (auto& e : gt[vert]) {
#if __cplusplus >= 201700L
            self(e.to);
#else
            secondDFS(e.to);
#endif
        }
    };
    for (int i : RevRange(n)) {
        if (!visited[order[i]]) {
            key = i;
            queue.clear();
            secondDFS(order[i]);
            result.addVertices(1);
            for (int j : queue) {
                result.addEdge(j, index);
            }
            index++;
        }
    }
    return {condensed, result};
}
