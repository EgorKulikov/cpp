#pragma once

#include "../../general.h"
#include "../../collections/arr.h"
#include "../graph.h"
#include "../../recursive_function.h"

template <class Edge>
void centroidDecomposition(Graph<Edge>& graph, const function<void(int, int, const arr<bool>&, const vi&)>& callback) {
    int n = graph.vertexCount;
    arr<bool> forb(n, false);
    arri size(n);
#if __cplusplus >= 201700L
    RecursiveFunction doWork = [&](const auto& self, int vert, int last) -> void {
#else
    function<void(int, int)> doWork = [&](int vert, int last) -> void {
#endif
        vi part;
#if __cplusplus >= 201700L
        RecursiveFunction dfs = [&](const auto& self, int vert, int last) -> void {
#else
        function<void(int, int)> dfs = [&](int vert, int last) -> void {
#endif
            size[vert] = 1;
            part.push_back(vert);
            for (auto& e : graph[vert]) {
                int next = e.to;
                if (next == last || forb[next]) {
                    continue;
                }
#if __cplusplus >= 201700L
                self(next, vert);
#else
                dfs(next, vert);
#endif
                size[vert] += size[next];
            }
        };
        dfs(vert, -1);
        int end = -1;
        for (int i : part) {
            if (2 * size[i] >= part.size()) {
                bool good = true;
                for (auto& e : graph[i]) {
                    int to = e.to;
                    if (!forb[to] && size[to] * 2 > part.size() && size[to] < size[i]) {
                        good = false;
                        break;
                    }
                }
                if (good) {
                    end = i;
                    break;
                }
            }
        }

        callback(end, last, forb, part);

        forb[end] = true;
        for (auto& e : graph[end]) {
            int to = e.to;
            if (!forb[to]) {
#if __cplusplus >= 201700L
                self(to, end);
#else
                doWork(to, end);
#endif
            }
        }
    };
    doWork(0, -1);
}

