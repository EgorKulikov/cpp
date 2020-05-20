#pragma once

#include "../general.h"
#include "../range/range.h"

template <class Edge>
class Graph {
public:
    int vertexCount;
    int edgeCount = 0;
private:
    vector<vector<Edge>> edges;

public:
    Graph(int vertexCount) : vertexCount(vertexCount), edges(vertexCount, vector<Edge>()) {}

    template <typename...Ts>
    Edge& addEdge(int from, int to, Ts... args) {
#ifdef LOCAL
        if (from < 0 || to < 0 || from >= vertexCount || to >= vertexCount) {
            throw "Out of bounds";
        }
#endif
        edges[from].emplace_back(to, edgeCount, args...);
        Edge& direct = edges[from].back();
        int directId = edges[from].size() - 1;
        if (Edge::reversable) {
            edges[to].push_back(direct.reverseEdge(from));
            Edge& reverse = edges[to].back();
            int revId = edges[to].size() - 1;
            direct.setReverseId(revId);
            reverse.setReverseId(directId);
        }
        edgeCount++;
        return direct;
    }

    vector<Edge>& operator [](int at) {
        return edges[at];
    }

    void addVertices(int count) {
        vertexCount += count;
        edges.resize(vertexCount);
    }

    void clear() {
        edgeCount = 0;
        for (int i : range(vertexCount)) {
            edges[i].clear();
        }
    }
};
