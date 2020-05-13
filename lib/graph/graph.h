#pragma once

#include "../general.h"

template <class Edge>
class Graph {
public:
    int vertexCount;
    int edgeCount = 0;
private:
    vector<basic_string<Edge*>> edges;

public:
    Graph(int vertexCount) : vertexCount(vertexCount), edges(vertexCount, basic_string<Edge*>()) {}

    template <typename...Ts>
    Edge* addEdge(int from, int to, Ts... args) {
#ifdef LOCAL
        if (from < 0 || to < 0 || from >= vertexCount || to >= vertexCount) {
            throw "Out of bounds";
        }
#endif
        Edge* edge = new Edge(from, to, args...);
        edge->id = edgeCount;
        edges[from].push_back(edge);
        Edge* reverse = edge->reverse();
        if (reverse != nullptr) {
            reverse->id = edgeCount;
            edges[to].push_back(reverse);
        }
        Edge* transposed = edge->transposed();
        if (transposed != nullptr) {
            edges[to].push_back(transposed);
            transposed->id = edgeCount;
            Edge* transRev = transposed->reverse();
            if (transRev != nullptr) {
                edges[from].push_back(transRev);
                transRev->id = edgeCount;
            }
        }
        edgeCount++;
        return edge;
    }

    basic_string<Edge*>& operator [](int at) {
        return edges[at];
    }

    void addVertices(int count) {
        vertexCount += count;
        edges.resize(vertexCount);
    }
};
