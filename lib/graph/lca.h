#pragma once

#include "../general.h"
#include "../collections/interval_tree.h"
#include "graph.h"

template <class Edge>
class LCA {
private:
    arri order;
    arri position;
    ReadOnlyIntervalTree<int, -1>* lcaTree;
    arri level;

public:
    LCA(Graph<Edge>& graph, int root = 0) {
        int vertexCount = graph.vertexCount;
        order = arri(2 * vertexCount - 1);
        position = arri(vertexCount, -1);
        level = arri(vertexCount);
        level[root] = 0;
        arri index(vertexCount, 0);
        arri last(vertexCount);
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
            while (index[vertex] < graph[vertex].size() && last[vertex] == graph[vertex][index[vertex]]->to) {
                index[vertex]++;
            }
            if (index[vertex] < graph[vertex].size()) {
                stack[size++] = vertex;
                int to = graph[vertex][index[vertex]]->to;
                stack[size++] = graph[vertex][index[vertex]]->to;
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

    int getPosition(int vertex) const { return position[vertex]; }
    int getLCA(int first, int second) const {
        return lcaTree->query(min(position[first], position[second]), max(position[first], position[second]) + 1);
    }
    int getLevel(int vertex) const {
        return level[vertex];
    }
    int getPathLength(int first, int second) const {
        return level[first] + level[second] - 2 * level[getLCA(first, second)];
    }
};
