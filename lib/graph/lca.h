#pragma once

#include "../general.h"
#include "../collections/interval_tree.h"
#include "graph.h"

template <class Edge>
class LCA {
private:
    vi order;
    vi position;
    Graph<Edge>* graph;
    ReadOnlyIntervalTree<int, -1>* lcaTree;
    vi level;

public:
    LCA(Graph<Edge>* graph, int root = 0) : graph(graph) {
        int vertexCount = graph->vertexCount;
        order = vi(2 * vertexCount - 1);
        position = vi(vertexCount, -1);
        level = vi(vertexCount);
        vi index = vi(vertexCount);
        vi last = vi(vertexCount);
        vi stack = vi(vertexCount);
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
            while (index[vertex] < graph->edges[vertex].size() && last[vertex] == graph->edges[vertex][index[vertex]]->to) {
                index[vertex]++;
            }
            if (index[vertex] < graph->edges[vertex].size()) {
                stack[size++] = vertex;
                int to = graph->edges[vertex][index[vertex]]->to;
                stack[size++] = graph->edges[vertex][index[vertex]]->to;
                last[to] = vertex;
                index[vertex]++;
            }
        }
        lcaTree = new ReadOnlyIntervalTree<int, -1>(order, [this](int left, int right) -> int {
            if (left == -1) {
                return right;
            }
            if (right == -1) {
                return left;
            }
            if (level[left] < level[right]) {
                return left;
            }
            return right;
        });
    }

    int getPosition(int vertex) { return position[vertex]; }
    int getLCA(int first, int second) {
        return lcaTree->query(min(position[first], position[second]), max(position[first], position[second]) + 1);
    }
    int getLevel(int vertex) {
        return level[vertex];
    }
    int getPathLength(int first, int second) {
        return level[first] + level[second] - 2 * level[getLCA(first, second)];
    }
};
