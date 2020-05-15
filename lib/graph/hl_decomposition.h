#pragma once

#include "../general.h"
#include "../collections/arr.h"
#include "graph.h"
#include "../recursive_function.h"

struct HLDecomposition {
    vector<vi> paths;
    arri id;
    arri pos;

    template <class Edge>
    explicit HLDecomposition(Graph<Edge>& graph, int root = 0) {
        int n = graph.vertexCount;
        arri size(n);
#if __cplusplus >= 201700L
        RecursiveFunction calcSize = [&](auto& self, int vert, int last) -> int {
#else
        function<int(int, int)> calcSize = [&](int vert, int last) -> int {
#endif
            size[vert] = 1;
            for (auto& e : graph[vert]) {
                int next = e.to;
                if (next == last) {
                    continue;
                }
#if __cplusplus >= 201700L
                size[vert] += self(next, vert);
#else
                size[vert] += calcSize(next, vert);
#endif
            }
            return size[vert];
        };
        calcSize(root, -1);
        id = arri(n);
        pos = arri(n);
        id[root] = 0;
        pos[root] = 0;
        paths.emplace_back(1, root);
#if __cplusplus >= 201700L
        RecursiveFunction build = [&](auto& self, int vert, int last) -> void {
#else
        function<void(int, int)> build = [&](int vert, int last) {
#endif
            if (last != -1) {
                if (2 * size[vert] >= size[last]) {
                    id[vert] = id[last];
                    pos[vert] = pos[last] + 1;
                    paths[id[vert]].push_back(vert);
                } else {
                    id[vert] = paths.size();
                    pos[vert] = 0;
                    paths.emplace_back(1, vert);
                }
            }
            for (auto& e : graph[vert]) {
                int next = e.to;
                if (next == last) {
                    continue;
                }
#if __cplusplus >= 201700L
                self(next, vert);
#else
                build(next, vert);
#endif
            }
        };
        build(root, -1);
        delete[] size.begin();
    }
};
