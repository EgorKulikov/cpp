#pragma once

#include "../general.h"
#include "../collections/segment_tree.h"
#include "graph.h"
#include "../misc.h"
#include "../collections/mdarr.h"
#include "../bits.h"

class LCA {
private:
    arri order;
    arri position;
    arr2d<int> lcaArr;

    int getMin(int a, int b) const {
        if (level[a] < level[b]) {
            return a;
        }
        return b;
    }

public:
    arri level;
    arri parent;

    template <class Edge>
    LCA(Graph<Edge>& graph, int root = 0) {
        int vertexCount = graph.vertexCount;
        order = arri(2 * vertexCount - 1);
        position = arri(vertexCount, -1);
        level = arri(vertexCount);
        level[root] = 0;
        arri index(vertexCount, 0);
        parent = arri(vertexCount);
        arri& last = parent;
        arri stack(vertexCount);
        stack[0] = root;
        int size = 1;
        int j = 0;
        last[root] = -1;
        while (size > 0) {
            int vertex = stack[--size];
            if (position[vertex] == -1) {
                position[vertex] = j;
            }
            order[j++] = vertex;
            if (last[vertex] != -1) {
                level[vertex] = level[last[vertex]] + 1;
            }
            while (index[vertex] < graph[vertex].size() && last[vertex] == graph[vertex][index[vertex]].to) {
                index[vertex]++;
            }
            if (index[vertex] < graph[vertex].size()) {
                stack[size++] = vertex;
                int to = graph[vertex][index[vertex]].to;
                stack[size++] = graph[vertex][index[vertex]].to;
                last[to] = vertex;
                index[vertex]++;
            }
        }
        lcaArr = arr2d<int>(binaryDigits(2 * vertexCount - 1), 2 * vertexCount - 1);
        for (int i : range(2 * vertexCount - 1)) {
            lcaArr(0, i) = order[i];
        }
        for (int i : range(1, lcaArr.dim1())) {
            for (int j : range(2 * vertexCount - 1)) {
                if (j + (1 << (i - 1)) < 2 * vertexCount - 1) {
                    lcaArr(i, j) = getMin(lcaArr(i - 1, j), lcaArr(i - 1, j + (1 << (i - 1))));
                } else {
                    lcaArr(i, j) = lcaArr(i - 1, j);
                }
            }
        }
    }

    int lca(int first, int second) const {
        int from = min(position[first], position[second]);
        int to = max(position[first], position[second]);
        int lv = binaryDigits(to - from) - 1;
        return getMin(lcaArr(lv, from), lcaArr(lv, to + 1 - (1 << lv)));
    }

    int pathLength(int first, int second) const {
        return level[first] + level[second] - 2 * level[lcaArr(first, second)];
    }
};
