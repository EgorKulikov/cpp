#pragma once

#include "../../general.h"
#include "../../collections/arr.h"
#include "../graph.h"

template <class Edge>
void centroidDecomposition(Graph<Edge>& graph, const function<void(int, const arr<bool>&, const vi&)>& callback) {
    int n = graph.vertexCount;
    arr<bool> forb(n, false);
    arri size(n);
    function<void(int)> doWork = [&](int vert) {
        vi part;
        function<void(int, int)> dfs = [&](int vert, int last) {
            size[vert] = 1;
            part.push_back(vert);
            for (auto* e : graph[vert]) {
                int next = e->to;
                if (next == last || forb[next]) {
                    continue;
                }
                dfs(next, vert);
                size[vert] += size[next];
            }
        };
        dfs(vert, -1);
        int end = -1;
        for (int i : part) {
            if (2 * size[i] >= part.size()) {
                bool good = true;
                for (auto* e : graph[i]) {
                    int to = e->to;
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

        callback(end, forb, part);

        forb[end] = true;
        for (auto* e : graph[end]) {
            int to = e->to;
            if (!forb[to]) {
                doWork(to);
            }
        }
    };
    doWork(0);
}

