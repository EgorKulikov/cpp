#pragma once

#include "../general.h"
#include "../collections/arr.h"
#include "graph.h"

struct HLDecomposition {
    vector<vi> paths;
    arri id;
    arri pos;

    template <class Edge>
    explicit HLDecomposition(Graph<Edge>& graph, int root = 0) {
        int n = graph.vertexCount;
        arri size(n);
        function<int(int, int)> calcSize = [&](int vert, int last) -> int {
            size[vert] = 1;
            for (auto* e : graph[vert]) {
                int next = e->to;
                if (next == last) {
                    continue;
                }
                size[vert] += calcSize(next, vert);
            }
            return size[vert];
        };
        calcSize(root, -1);
        id = arri(n);
        pos = arri(n);
        id[root] = 0;
        pos[root] = 0;
        paths.emplace_back(1, root);
        function<void(int, int)> build = [&](int vert, int last) {
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
            for (auto* e : graph[vert]) {
                int next = e->to;
                if (next == last) {
                    continue;
                }
                build(next, vert);
            }
        };
        build(root, -1);
        delete[] size.begin();
    }
};
